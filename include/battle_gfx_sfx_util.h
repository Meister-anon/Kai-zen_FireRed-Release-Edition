#ifndef GUARD_BATTLE_GFX_SFX_UTIL_H
#define GUARD_BATTLE_GFX_SFX_UTIL_H

void AllocateBattleSpritesData(void);
void FreeBattleSpritesData(void);
void SpriteCB_WaitForBattlerBallReleaseAnim(struct Sprite *sprite);
void SpriteCB_TrainerSlideIn(struct Sprite *sprite);
void InitAndLaunchChosenStatusAnimation(enum BattlerId battler, bool32 isVolatile, u32 status);
bool8 TryHandleLaunchBattleTableAnimation(u8 activeBattler, u8 atkBattler, u8 defBattler, u8 tableId, u16 argument);
void InitAndLaunchSpecialAnimation(u8 activeBattler, u8 atkBattler, u8 defBattler, u8 tableId);
bool8 IsMoveWithoutAnimation(u16 moveId, u8 animationTurn);
bool8 IsBattleSEPlaying(enum BattlerId battlerId);
void BattleLoadMonSpriteGfx(struct Pokemon *mon, enum BattlerId battler);
void DecompressGhostFrontPic(struct Pokemon *unused, enum BattlerId battlerId);
void DecompressTrainerFrontPic(u16 frontPicId, enum BattlerId battlerId);
void DecompressTrainerBackPalette(u16 a1, u8 a2);
void BattleGfxSfxDummy3(u8 a1);
void FreeTrainerFrontPicPalette(u16 frontPicId);
void FreeTrainerFrontPicPaletteAndTile(u16 frontPicId);
bool8 BattleLoadAllHealthBoxesGfx(u8 state);
void LoadBattleBarGfx(u8 arg0);
bool8 BattleInitAllSprites(u8 *state, u8 *battlerId);
void ClearSpritesHealthboxAnimData(void);
void CopyAllBattleSpritesInvisibilities(void);
void CopyBattleSpriteInvisibility(enum BattlerId battlerId);
void HandleSpeciesGfxDataChange(enum BattlerId battlerAtk, enum BattlerId battlerDef, u8 notTransform);
void BattleLoadSubstituteOrMonSpriteGfx(enum BattlerId battlerId, bool8 loadMonSprite);
void LoadBattleMonGfxAndAnimate(enum BattlerId battlerId, bool8 loadMonSprite, u8 spriteId);
void TrySetBehindSubstituteSpriteBit(enum BattlerId battler, enum Move move);
void ClearBehindSubstituteBit(enum BattlerId battlerId);
void HandleLowHpMusicChange(struct Pokemon *mon, enum BattlerId battlerId);
void BattleStopLowHpSound(void);
void HandleBattleLowHpMusicChange(void);
void SetBattlerSpriteAffineMode(u8 affineMode);
void CreateEnemyShadowSprite(enum BattlerId battler);
void LoadAndCreateEnemyShadowSprites(void);
void SpriteCB_SetInvisible(struct Sprite *sprite);
void SetBattlerShadowSpriteCallback(enum BattlerId battler, u16 species);
void HideBattlerShadowSprite(enum BattlerId battler);
void BattleInterfaceSetWindowPals(void);
void ClearTemporarySpeciesSpriteData(enum BattlerId battlerId, bool8 dontClearSubstitute);
void AllocateMonSpritesGfx(void);
void FreeMonSpritesGfx(void);
bool32 ShouldPlayNormalPokeCry(struct Pokemon *mon);

#endif // GUARD_BATTLE_GFX_SFX_UTIL_H
