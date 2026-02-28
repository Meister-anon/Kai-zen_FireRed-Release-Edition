#ifndef GUARD_BATTLE_SETUP_H
#define GUARD_BATTLE_SETUP_H

#include "global.h"

#define REMATCHES_COUNT 5

struct RematchTrainer
{
    u16 trainerIds[REMATCHES_COUNT];
    u16 mapGroup;
    u16 mapNum;
};

/*
the layout of the first byte can be confusing here
isDoubleBattle is the least lsb. msb is in the mode.
*/
typedef union PACKED TrainerBattleParameter
{
    struct PACKED _TrainerBattleParameter
    {
        u8 isDoubleBattle:1;
        u8 isRematch:1;
        u8 playMusicA:1;
        u8 playMusicB:1;
        u8 mode:4; //battle mode singles doubles etc.
        u8 objEventLocalIdA;
        u16 opponentA;
        u8 *introTextA;
        u8 *defeatTextA;
        u8 *battleScriptRetAddrA;
        u8 objEventLocalIdB;
        u16 opponentB;
        u8 *introTextB;
        u8 *defeatTextB;
        u8 *battleScriptRetAddrB;
        u8 *victoryText;
        u8 *cannotBattleText;
        u8 rivalBattleFlags;
    } params;
    u8 data[sizeof(struct _TrainerBattleParameter)];
} TrainerBattleParameter;

//rework see if can setup dynamic rematch
//can give every trainer mon 6 mon
//major mon and just use party size and limited scaling
//to simulate new teams
//for rematch can randomize team position 
//to potentially bring in new mon
//will need to make new fields to make sure 
//my lvl cap stuff isn't broken
//give every trainer an initial party size field
//so it can expand over time
//that way can use base party size so lvl cap stays consistent
//with base game
//ok looked into this is not trainer struct
//need to put my change there not here idk how will use for now
extern const struct RematchTrainer gRematchTable[50];

extern TrainerBattleParameter gTrainerBattleParameter;
extern u16 gPartnerTrainerId;

#define TRAINER_BATTLE_PARAM gTrainerBattleParameter.params

void BattleSetup_StartWildBattle(void);
void BattleSetup_StartRoamerBattle(void);
void StartOldManTutorialBattle(void);
void BattleSetup_StartScriptedWildBattle(void);
void StartMarowakBattle(void);
void StartSouthernIslandBattle(void);
void StartLegendaryBattle(void);
void StartGroudonKyogreBattle(void);
void StartRegiBattle(void);
//
void BattleSetup_StartDoubleWildBattle(void);
void BattleSetup_StartBattlePikeWildBattle(void);
//void StartWallyTutorialBattle(void);
void BattleSetup_StartScriptedDoubleWildBattle(void);
void BattleSetup_StartLatiBattle(void);
u8 BattleSetup_GetEnvironmentId(void);
u8 BattleSetup_GetBattleTowerBattleTransition(void);
u8 GetWildBattleTransition(void);
u8 GetTrainerBattleTransition(void);
u8 GetSpecialBattleTransition(s32 id);
void ChooseStarter(void);
void ResetTrainerOpponentIds(void);
void SetMapVarsToTrainerA(void);
void SetMapVarsToTrainerB(void);
const u8 *BattleSetup_ConfigureTrainerBattle(const u8 *data);
void ConfigureAndSetUpOneTrainerBattle(u8 trainerEventObjId, const u8 *trainerScript);
bool32 GetTrainerFlagFromScriptPointer(const u8 *data);
void SetTrainerFacingDirection(void);
u8 GetTrainerBattleMode(void);
u16 GetRivalBattleFlags(void);
void SetBattledTrainerFlags(void);
bool8 HasTrainerBeenFought(u16 trainerId);
void SetTrainerFlag(u16 trainerId);
void ClearTrainerFlag(u16 trainerId);
void StartTrainerBattle(void);
void BattleSetup_StartTrainerBattle(void);
void StartRematchBattle(void);
void ShowTrainerIntroSpeech(void);
const u8 *BattleSetup_GetScriptAddrAfterBattle(void);
const u8 *BattleSetup_GetTrainerPostBattleScript(void);
void ShowTrainerCantBattleSpeech(void);
void PlayTrainerEncounterMusic(void);
const u8 *GetTrainerALoseText(void);
const u8 *GetTrainerBLoseText(void);
const u8 *GetTrainerWonSpeech(void);

//stuff from EE //wont need rematch stuff
void UpdateRematchIfDefeated(s32 rematchTableId);
void IncrementRematchStepCounter(void);
void TryUpdateRandomTrainerRematches(u16 mapGroup, u16 mapNum);
bool32 DoesSomeoneWantRematchIn(u16 mapGroup, u16 mapNum);
bool32 IsRematchTrainerIn(u16 mapGroup, u16 mapNum);
u16 GetLastBeatenRematchTrainerId(u16 trainerId);
bool8 ShouldTryRematchBattle(void);
bool8 IsTrainerReadyForRematch(void);
void ShouldTryGetTrainerScript(void);
u16 CountBattledRematchTeams(u16 trainerId);
void TrainerBattleLoadArgs(const u8 *data);
void TrainerBattleLoadArgsTrainerA(const u8 *data);
void TrainerBattleLoadArgsTrainerB(const u8 *data);
void TrainerBattleLoadArgsSecondTrainer(const u8 *data);
void InitTrainerBattleParameter(void);

void DoStandardWildBattle_Debug(void);
void BattleSetup_StartTrainerBattle_Debug(void);
s32 TrainerIdToRematchTableId(const struct RematchTrainer *table, u16 trainerId);
s32 FirstBattleTrainerIdToRematchTableId(const struct RematchTrainer *table, u16 trainerId);
u16 GetRematchTrainerIdFromTable(const struct RematchTrainer *table, u16 firstBattleTrainerId);

#endif // GUARD_BATTLE_SETUP_H
