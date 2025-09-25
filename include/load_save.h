#ifndef GUARD_LOAD_SAVE_H
#define GUARD_LOAD_SAVE_H

#include "global.h"


#define SAVEBLOCK_MOVE_RANGE    128

/**
 * These structs are to prevent them from being reordered on newer or modern
 * toolchains. If this is not done, the ClearSav functions will end up erasing
 * the wrong memory leading to various glitches.
 */
struct SaveBlock2ASLR {
    struct SaveBlock2 block;
    u8 aslr[SAVEBLOCK_MOVE_RANGE];
};

struct SaveBlock1ASLR {
    struct SaveBlock1 block;
    u8 aslr[SAVEBLOCK_MOVE_RANGE];
};

struct PokemonStorageASLR {
    struct PokemonStorage block;
    u8 aslr[SAVEBLOCK_MOVE_RANGE];
};

extern struct SaveBlock1ASLR gSaveBlock1;
extern struct SaveBlock2ASLR gSaveBlock2;
extern struct PokemonStorageASLR gPokemonStorage;
extern bool32 gFlashMemoryPresent;

void ClearSav2(void);
void ClearSav1(void);
void CheckForFlashMemory(void);
void MoveSaveBlocks_ResetHeap(void);
bool32 GetSecretBase2Field_9(void);
void ClearSecretBase2Field_9(void);
void SetSecretBase2Field_9(void);
void SetSecretBase2Field_9_AndHideBG(void);
void ClearSecretBase2Field_9_2(void);
void SavePlayerParty(void);
void LoadPlayerParty(void);
void SaveSerializedGame(void);
void LoadSerializedGame(void);
void LoadPlayerBag(void);
void SavePlayerBag(void);
void SetSaveBlocksPointers(void);
void MoveSaveBlocks_ResetHeap(void);
void ApplyNewEncryptionKeyToAllEncryptedData(u32 encryptionKey);
void ApplyNewEncryptionKeyToBagItems(u32 encryptionKey);
void ApplyNewEncryptionKeyToWord(u32 * word, u32 encryptionKey);
void ApplyNewEncryptionKeyToHword(u16 * hword, u32 encryptionKey);
void ClearContinueGameWarpStatus2(void);
void SetContinueGameWarpStatusToDynamicWarp(void);
void SetContinueGameWarpStatus(void);
bool32 UseContinueGameWarp(void);
void ClearContinueGameWarpStatus();

#endif // GUARD_LOAD_SAVE_H
