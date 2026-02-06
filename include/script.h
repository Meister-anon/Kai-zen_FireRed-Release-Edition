#ifndef GUARD_SCRIPT_H
#define GUARD_SCRIPT_H

#include "global.h"

struct ScriptContext;

typedef bool8 (*ScrCmdFunc)(struct ScriptContext *);
typedef u8 Script[];

struct ScriptContext
{
    u8 stackDepth;
    u8 mode;
    u8 comparisonResult;
    bool8 breakOnTrainerBattle:1;
    bool8 waitAfterCallNative:1;
    u8 (*nativePtr)(void);
    const u8 *scriptPtr;
    const u8 *stack[20];
    ScrCmdFunc *cmdTable;
    ScrCmdFunc *cmdTableEnd;
    u32 data[4];
};

#define ScriptReadByte(ctx) (*(ctx->scriptPtr++))

void InitScriptContext(struct ScriptContext *ctx, void *cmdTable, void *cmdTableEnd);
u8 SetupBytecodeScript(struct ScriptContext *ctx, const u8 *ptr);
void SetupNativeScript(struct ScriptContext *ctx, bool8 (*ptr)(void));
void StopScript(struct ScriptContext *ctx);
bool8 RunScriptCommand(struct ScriptContext *ctx);
u8 ScriptPush(struct ScriptContext *ctx, const u8 *ptr);
const u8 *ScriptPop(struct ScriptContext *ctx);
void ScriptJump(struct ScriptContext *ctx, const u8 *ptr);
void ScriptCall(struct ScriptContext *ctx, const u8 *ptr);
void ScriptReturn(struct ScriptContext *ctx);
u16 ScriptReadHalfword(struct ScriptContext *ctx);
u16 ScriptPeekHalfword(struct ScriptContext *ctx);
u32 ScriptReadWord(struct ScriptContext *ctx);
u32 ScriptPeekWord(struct ScriptContext *ctx);
void LockPlayerFieldControls(void);
void UnlockPlayerFieldControls(void);
bool8 ArePlayerFieldControlsLocked(void);
void ScriptContext_Init(void);
bool8 ScriptContext_IsScriptSetUp(void);
bool8 ScriptContext_RunScript(void);
void LockForFieldEffect(void);
void ScriptContext_SetupScript(const u8 *ptr);
void ScriptContext_Stop(void);
void ScriptContext_Enable(void);
void RunScriptImmediately(const u8 *ptr);
u8 *mapheader_get_tagged_pointer(u8 tag);
void mapheader_run_script_by_tag(u8 tag);
u8 *mapheader_get_first_match_from_tagged_ptr_list(u8 tag);
void RunOnLoadMapScript(void);
void RunOnTransitionMapScript(void);
void RunOnResumeMapScript(void);
void RunOnReturnToFieldMapScript(void);
void RunOnDiveWarpMapScript(void);
bool8 TryRunOnFrameMapScript(void);
void TryRunOnWarpIntoMapScript(void);
u32 CalculateRamScriptChecksum(void);
void ClearRamScript(void);
bool8 InitRamScript(u8 *script, u16 scriptSize, u8 mapGroup, u8 mapNum, u8 objectId);
const u8 *GetRamScript(u8 objectId, const u8 *script);
bool32 sub_80991F8(void);
u8 *sub_8099244(void);
void sub_80992A0(u8 *script, u16 scriptSize);
bool32 ValidateRamScript(void);
void MEventSetRamScript(u8 * script, u16 scriptSize);
u8 * sub_8069E48(void);
void RegisterQuestLogInput(u8 var);
void ClearMsgBoxCancelableState(void);
void SetQuestLogInputIsDpadFlag(void);
void ClearQuestLogInput(void);
void ClearQuestLogInputIsDpadFlag(void);
void MsgSetSignPost(void);
void MsgSetNotSignPost(void);
bool8 IsMsgSignPost(void);
bool8 IsQuestLogInputDpad(void);
u8 GetRegisteredQuestLogInput(void);
void ResetFacingNpcOrSignPostVars(void);
bool8 CanWalkAwayToCancelMsgBox(void);
void SetWalkingIntoSignVars(void);
bool8 IsMsgBoxWalkawayDisabled(void);

extern const u8 *gRAMScriptPtr;
extern u8 gWalkAwayFromSignInhibitTimer;


/* Script effects analysis.
 *
 * 'RunScriptImmediatelyUntilEffect' executes a script until it reaches
 * the first command which calls 'Script_RequestEffects' with an
 * effect in 'effects' in which case it returns 'TRUE' and stores the
 * current state in 'ctx'; or until it reaches an 'end'/'return' in
 * which case it returns 'FALSE'.
 *
 * 'Script_HasNoEffect' wraps 'RunScriptImmediatelyUntilEffect' and
 * returns 'TRUE' if the script exits without an effect on the save or
 * the hardware, or 'FALSE' if it would have an effect (the effect is
 * not performed).
 *
 * Commands, natives, and specials which call 'Script_RequestEffects'
 * must be explicitly tagged with 'requests_effects=1', and must call
 * the function before any of those effects occur. An untagged function
 * could cause any effect, so execution is stopped to be safe. If the
 * code has no effects it must call 'Script_RequestEffects(SCREFF_V1)'
 * to note that explicitly.
 *
 * Regular variables are in the save (so should use 'SCREFF_SAVE'), but
 * special variables are not in the save, so 'Script_RequestWriteVar' is
 * provided to only request the 'SCREFF_SAVE' effect for a non-special
 * variable.
 *
 * The 'effects' parameter to 'RunScriptImmediatelyUntilEffect' and
 * 'Script_RequestEffects' must be the bitwise or of an effects version
 * (currently 'SCREFF_V1') and any number of effects. For example
 * 'Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE)'. */

enum // effects
{
    SCREFF_SAVE = 1 << 0,          // writes to the save.
    SCREFF_HARDWARE = 1 << 1,      // writes to a hardware register.
    SCREFF_TRAINERBATTLE = 1 << 2, // 'trainerbattle' command.
};

#define SCREFF_ANY (SCREFF_SAVE | SCREFF_HARDWARE | SCREFF_TRAINERBATTLE)

enum // effects versions
{
    SCREFF_V1 = 0xFFFFFFF8,
};

//DONT' know what for don't yet have sruct for this
//as focusin gon building
//appears will need update scripts smh

#endif // GUARD_SCRIPT_H
