#ifndef GUARD_MALLOC_H
#define GUARD_MALLOC_H

#include "global.h"

#define HEAP_SIZE 0x1C000
#define malloc Alloc
#define calloc(ct, sz) AllocZeroed((ct) * (sz))
#define free Free

#define FREE_AND_SET_NULL(ptr)          \
{                                       \
    free(ptr);                          \
    ptr = NULL;                         \
}

#define MALLOC_SYSTEM_ID 0xA3A3

struct MemBlock {
    // Whether this block is currently allocated.
    bool16 flag:1;

    u16 unused_00:4;

    // High 11 bits of location pointer.
    u16 locationHi:11;

    // Magic number used for error checking. Should equal MALLOC_SYSTEM_ID.
    u16 magic_number;

    // Size of the block (not including this header struct).
    u32 size:18;

    // Low 14 bits of location pointer.
    u32 locationLo:14;

    // Previous block pointer. Equals sHeapStart if this is the first block.
    struct MemBlock *prev;

    // Next block pointer. Equals sHeapStart if this is the last block.
    struct MemBlock *next;

    // Data in the memory block. (Arrays of length 0 are a GNU extension.)
    u8 data[0];
};

#if TESTING || !defined(NDEBUG)

#define Alloc(size) Alloc_(size, __FILE__ ":" STR(__LINE__))
#define AllocZeroed(size) AllocZeroed_(size, __FILE__ ":" STR(__LINE__))

/*#else

#define Alloc(size) Alloc_(size, NULL)
#define AllocZeroed(size) AllocZeroed_(size, NULL)
*/
#endif


extern u8 gHeap[];
void *Alloc(u32 size);
void *AllocZeroed(u32 size);
void Free(void *pointer);
void InitHeap(void *pointer, u32 size);

const struct MemBlock *HeapHead(void);
const char *MemBlockLocation(const struct MemBlock *block);

#endif // GUARD_MALLOC_H
