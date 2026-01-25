#ifndef GUARD_DECOMPRESS_H
#define GUARD_DECOMPRESS_H

#include "global.h"

#include "sprite.h"

//extern u8 gDecompressionBuffer[0x4000];
#define MAX_DECOMPRESSION_BUFFER_SIZE 0x4000

void LZDecompressWram(const void *src, void *dest);
void LZDecompressVram(const void *src, void *dest);

//  Default Decompression functions are below here
u32 IsLZ77Data(const void *ptr, u32 minSize, u32 maxSize);

u32 LoadCompressedSpriteSheet(const struct CompressedSpriteSheet *src);
u32 LoadCompressedSpriteSheetOverrideBuffer(const struct CompressedSpriteSheet *src, void *buffer);
u32 LoadCompressedSpriteSheetByTemplate(const struct SpriteTemplate *template, s32 offset);
bool8 LoadCompressedSpriteSheetUsingHeap(const struct CompressedSpriteSheet* src);

void DecompressPicFromTable(const struct CompressedSpriteSheet *src, void* buffer, s32 species);
void DecompressPicFromTable_2(const struct CompressedSpriteSheet *src, void* buffer, s32 species);
void DecompressPicFromTable_DontHandleDeoxys(const struct CompressedSpriteSheet *src, void* buffer, s32 species);

void HandleLoadSpecialPokePic(bool32 isFrontPic,void *dest, s32 species, u32 personality);
void HandleLoadSpecialPokePic_DontHandleDeoxys(bool32 isFrontPic,void *dest, s32 species, u32 personality);

void LoadSpecialPokePic(void *dest, s32 species, u32 personality, bool8 isFrontPic);
void LoadSpecialPokePic_2(const struct CompressedSpriteSheet *src, void *dest, s32 species, u32 personality, bool8 isFrontPic);
void LoadSpecialPokePic_DontHandleDeoxys(void *dest, s32 species, u32 personality, bool8 isFrontPic);

u32 GetDecompressedDataSize(const u8 *ptr);

#endif // GUARD_DECOMPRESS_H
