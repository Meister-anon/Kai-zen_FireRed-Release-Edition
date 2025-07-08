#include "global.h"
#include "malloc.h"
#if TESTING
#include "test/test.h"
#endif

static void *sHeapStart;
static u32 sHeapSize;

static EWRAM_DATA struct MemBlock *head = NULL;
static EWRAM_DATA struct MemBlock *pos = NULL;
static EWRAM_DATA struct MemBlock *splitBlock = NULL;

#define MALLOC_SYSTEM_ID 0xA3A3



void PutMemBlockHeader(void *block, struct MemBlock *prev, struct MemBlock *next, u32 size)
{
    struct MemBlock *header = (struct MemBlock *)block;

    header->allocated = FALSE;
    header->locationHi = 0;
    header->magic_number = MALLOC_SYSTEM_ID;
    header->size = size;
    header->locationLo = 0;
    header->prev = prev;
    header->next = next;
}

void PutFirstMemBlockHeader(void *block, u32 size)
{
    PutMemBlockHeader(block, (struct MemBlock *)block, (struct MemBlock *)block, size - sizeof(struct MemBlock));
}

void *AllocInternal(void *heapStart, u32 size, const char *location)
{
    struct MemBlock *pos = (struct MemBlock *)heapStart;
    struct MemBlock *head = pos;
    struct MemBlock *splitBlock;
    u32 foundBlockSize;

    // Alignment
    if (size & 3)
        size = 4 * ((size / 4) + 1);

    for (;;)
    {
        // Loop through the blocks looking for unused block that's big enough.

        if (!pos->allocated)
        {
            foundBlockSize = pos->size;

            if (foundBlockSize >= size)
            {
                if (foundBlockSize - size < 2 * sizeof(struct MemBlock))
                {
                    // The block isn't much bigger than the requested size,
                    // so just use it.
                    pos->allocated = TRUE;
                }
                else
                {
                    // The block is significantly bigger than the requested
                    // size, so split the rest into a separate block.
                    foundBlockSize -= sizeof(struct MemBlock);
                    foundBlockSize -= size;

                    splitBlock = (struct MemBlock *)(pos->data + size);

                    pos->allocated = TRUE;
                    pos->size = size;

                    PutMemBlockHeader(splitBlock, pos, pos->next, foundBlockSize);

                    pos->next = splitBlock;

                    if (splitBlock->next != head)
                        splitBlock->next->prev = splitBlock;
                }

                pos->locationHi = ((uintptr_t)location) >> 14;
                pos->locationLo = (uintptr_t)location;

                return pos->data;
            }
        }

        if (pos->next == head)
        {
#if TESTING
            const struct MemBlock *head = HeapHead();
            const struct MemBlock *block = head;
            do
            {
                if (block->allocated)
                {
                    const char *location = MemBlockLocation(block);
                    if (location)
                        Test_MgbaPrintf("%s: %d bytes allocated", location, block->size);
                    else
                        Test_MgbaPrintf("<unknown>: %d bytes allocated", block->size);
                }
                block = block->next;
            }
            while (block != head);
            Test_ExitWithResult(TEST_RESULT_ERROR, SourceLine(0), ":L%s:%d, %s: OOM allocating %d bytes", gTestRunnerState.test->filename, SourceLine(0), location, size);
#endif
            return NULL;
        }

        pos = pos->next;
    }
}

void FreeInternal(void *heapStart, void *p)
{
    AGB_ASSERT_EX(p != NULL, ABSPATH("gflib/malloc.c"), 195);

    if (p) {
        struct MemBlock *head = (struct MemBlock *)heapStart;
        struct MemBlock *pos = (struct MemBlock *)((u8 *)p - sizeof(struct MemBlock));
        AGB_ASSERT_EX(pos->magic_number == MALLOC_SYSTEM_ID, ABSPATH("gflib/malloc.c"), 204);
        AGB_ASSERT_EX(pos->allocated == TRUE, ABSPATH("gflib/malloc.c"), 205);
        pos->allocated = FALSE;

        // If the freed block isn't the last one, merge with the next block
        // if it's not in use.
        if (pos->next != head) {
            if (!pos->next->allocated) {
                AGB_ASSERT_EX(pos->next->magic_number == MALLOC_SYSTEM_ID, ABSPATH("gflib/malloc.c"), 211);
                pos->size += sizeof(struct MemBlock) + pos->next->size;
                pos->next->magic_number = 0;
                pos->next = pos->next->next;
                if (pos->next != head)
                    pos->next->prev = pos;
            }
        }

        // If the freed block isn't the first one, merge with the previous block
        // if it's not in use.
        if (pos != head) {
            if (!pos->prev->allocated) {
                AGB_ASSERT_EX(pos->prev->magic_number == MALLOC_SYSTEM_ID, ABSPATH("gflib/malloc.c"), 228);

                pos->prev->next = pos->next;

                if (pos->next != head)
                    pos->next->prev = pos->prev;

                pos->magic_number = 0;
                pos->prev->size += sizeof(struct MemBlock) + pos->size;
            }
        }
    }
}

void *AllocZeroedInternal(void *heapStart, u32 size, const char *location)
{
    void *mem = AllocInternal(heapStart, size, location);

    if (mem != NULL)
    {
        if (size & 3)
            size = 4 * ((size / 4) + 1);

        CpuFill32(0, mem, size);
    }

    return mem;
}

bool32 CheckMemBlockInternal(void *heapStart, void *pointer)
{
    struct MemBlock *head = (struct MemBlock *)heapStart;
    struct MemBlock *block = (struct MemBlock *)((u8 *)pointer - sizeof(struct MemBlock));

    if (block->magic_number != MALLOC_SYSTEM_ID)
        return FALSE;

    if (block->next->magic_number != MALLOC_SYSTEM_ID)
        return FALSE;

    if (block->next != head && block->next->prev != block)
        return FALSE;

    if (block->prev->magic_number != MALLOC_SYSTEM_ID)
        return FALSE;

    if (block->prev != head && block->prev->next != block)
        return FALSE;

    if (block->next != head && block->next != (struct MemBlock *)(block->data + block->size))
        return FALSE;

    return TRUE;
}

void InitHeap(void *heapStart, u32 heapSize)
{
    sHeapStart = heapStart;
    sHeapSize = heapSize;
    PutFirstMemBlockHeader(heapStart, heapSize);
}

void *Alloc_(u32 size, const char *location)
{
    return AllocInternal(sHeapStart, size, location);
}

void *AllocZeroed_(u32 size, const char *location)
{
    return AllocZeroedInternal(sHeapStart, size, location);
}

void Free(void *pointer)
{
    FreeInternal(sHeapStart, pointer);
}

bool32 CheckMemBlock(void *pointer)
{
    return CheckMemBlockInternal(sHeapStart, pointer);
}

bool32 CheckHeap()
{
    struct MemBlock *pos = (struct MemBlock *)sHeapStart;

    do {
        if (!CheckMemBlockInternal(sHeapStart, pos->data))
            return FALSE;
        pos = pos->next;
    } while (pos != (struct MemBlock *)sHeapStart);

    return TRUE;
}
