#include "global.h"
#include "gflib.h"
#include "data.h"
#include "item.h"
#include "event_data.h"
#include "mail_data.h"
#include "pokemon_storage_system_internal.h"
#include "pokemon_summary_screen.h"
#include "strings.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "constants/songs.h"
#include "constants/items.h"
#include "constants/moves.h"

static EWRAM_DATA struct Pokemon gUnknown_20397BC = {};
static EWRAM_DATA s8 sBoxCursorArea = 0;
//renamed as seems used for both party and box
static EWRAM_DATA s8 sCursorPosition = 0;
static EWRAM_DATA bool8 sIsMonBeingMoved = FALSE;
static EWRAM_DATA u8 sMovingMonOrigBoxId = 0;
static EWRAM_DATA u8 sMovingMonOrigBoxPos = 0;
static EWRAM_DATA bool8 sCanOnlyMove = FALSE;
static EWRAM_DATA u8 gUnknown_2039826 = 0;

static void sub_80929B0(void);
static bool8 MonPlaceChange_Move(void);
static bool8 MonPlaceChange_Place(void);
static bool8 MonPlaceChange_Shift(void);
static bool8 sub_8092E00(void);
static bool8 sub_8092E10(void);
static bool8 sub_8092E20(void);
static bool8 sub_8092E54(void);
static void MoveMon(void);
static void PlaceMon(void);
static void SetMovedMonData(u8 boxId, u8 cursorPos);
static void SetPlacedMonData(u8 boxId, u8 cursorPos);
static void PurgeMonOrBoxMon(u8 boxId, u8 cursorPos);
static void SetShiftedMonData(u8 boxId, u8 cursorPos);
static void sub_8093A10(void);
static void SetCursorMonData(void * cursorMon, u8 mode);
static void sub_8093AAC(void);
static u8 InBoxInput_Normal(void);
static u8 InBoxInput_GrabbingMultiple(void);
static u8 InBoxInput_MovingMultiple(void);
static void AddBoxMenu(void);
static bool8 sub_8094924(void);
static bool8 SetMenuTexts_Mon(void);
static bool8 sub_8094A0C(void);
static void CreateCursorSprites(void);
static void ToggleCursorMultiMoveMode(void);

static const u16 sHandCursorPalette[] = INCBIN_U16("graphics/interface/pss_unk_83D2BCC.gbapal");
static const u16 sHandCursorTiles[] = INCBIN_U16("graphics/interface/pss_unk_83D2BEC.4bpp");
static const u16 sHandCursorShadowTiles[] = INCBIN_U16("graphics/interface/pss_unk_83D33EC.4bpp");

void sub_80922C0(void)
{
    if (gPSSData->boxOption != BOX_OPTION_DEPOSIT)
        sBoxCursorArea = CURSOR_AREA_IN_BOX;
    else
        sBoxCursorArea = CURSOR_AREA_IN_PARTY;

    sCursorPosition = 0;
    sIsMonBeingMoved = FALSE;
    sMovingMonOrigBoxId = 0;
    sMovingMonOrigBoxPos = 0;
    sCanOnlyMove = FALSE;
    ClearSavedCursorPos();
    CreateCursorSprites();
    gPSSData->field_CD6 = 1;
    gPSSData->inBoxMovingMode = 0;
    sub_8093A10();
}

void sub_8092340(void)
{
    CreateCursorSprites();
    sub_8093AAC();
    gPSSData->field_CD6 = 1;
    gPSSData->inBoxMovingMode = 0;
    if (sIsMonBeingMoved)
    {
        gPSSData->movingMon = gUnknown_20397BC;
        CreateMovingMonIcon();
    }
}

static void sub_8092398(u8 cursorArea, u8 cursorPosition, u16 *x, u16 *y)
{
    switch (cursorArea)
    {
    case CURSOR_AREA_IN_BOX:
        *x = (cursorPosition % IN_BOX_COLUMNS) * 24 + 100;
        *y = (cursorPosition / IN_BOX_COLUMNS) * 24 +  32;
        break;
    case CURSOR_AREA_IN_PARTY:
        if (cursorPosition == 0)
        {
            *x = 0x68;
            *y = 0x34;
        }
        else if (cursorPosition == PARTY_SIZE)
        {
            *x = 0x98;
            *y = 0x84;
        }
        else
        {
            *x = 0x98;
            *y = (cursorPosition - 1) * 24 + 4;
        }
        break;
    case CURSOR_AREA_BOX_TITLE:
        *x = 0xa2;
        *y = 0x0c;
        break;
    case CURSOR_AREA_BUTTONS:
        *y = sIsMonBeingMoved ? 8 : 14;
        *x = cursorPosition * 0x58 + 0x78;
        break;
    case 4:
        *x = 0xa0;
        *y = 0x60;
        break;
    }
}

static u16 GetSpeciesAtCursorPosition(void)
{
    switch (sBoxCursorArea)
    {
    case CURSOR_AREA_IN_PARTY:
        return GetMonData(&gPlayerParty[sCursorPosition], MON_DATA_SPECIES);
    case CURSOR_AREA_IN_BOX:
        return GetCurrentBoxMonData(sCursorPosition, MON_DATA_SPECIES);
    default:
        return SPECIES_NONE;
    }
}

bool8 sub_80924A8(void)
{
    s16 tmp;

    if (gPSSData->field_CD0 == 0)
    {
        if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
            return FALSE;
        else
            return IsItemIconAnimActive();
    }
    else if (--gPSSData->field_CD0 != 0)
    {
        gPSSData->field_CBC += gPSSData->field_CC4;
        gPSSData->field_CC0 += gPSSData->field_CC8;
        gPSSData->field_CB4->pos1.x = gPSSData->field_CBC >> 8;
        gPSSData->field_CB4->pos1.y = gPSSData->field_CC0 >> 8;
        if (gPSSData->field_CB4->pos1.x > 0x100)
        {
            tmp = gPSSData->field_CB4->pos1.x - 0x100;
            gPSSData->field_CB4->pos1.x = tmp + 0x40;
        }
        if (gPSSData->field_CB4->pos1.x < 0x40)
        {
            tmp = 0x40 - gPSSData->field_CB4->pos1.x;
            gPSSData->field_CB4->pos1.x = 0x100 - tmp;
        }
        if (gPSSData->field_CB4->pos1.y > 0xb0)
        {
            tmp = gPSSData->field_CB4->pos1.y - 0xb0;
            gPSSData->field_CB4->pos1.y = tmp - 0x10;
        }
        if (gPSSData->field_CB4->pos1.y < -0x10)
        {
            tmp = -0x10 - gPSSData->field_CB4->pos1.y;
            gPSSData->field_CB4->pos1.y = 0xb0 - tmp;
        }
        if (gPSSData->field_CD7 && --gPSSData->field_CD7 == 0)
            gPSSData->field_CB4->vFlip = (gPSSData->field_CB4->vFlip == FALSE);
    }
    else
    {
        gPSSData->field_CB4->pos1.x = gPSSData->field_CCC;
        gPSSData->field_CB4->pos1.y = gPSSData->field_CCE;
        sub_80929B0();
    }

    return TRUE;
}

static void sub_8092604(u8 newCurosrArea, u8 newCursorPosition)
{
    u16 x, y;

    sub_8092398(newCurosrArea, newCursorPosition, &x, &y);
    gPSSData->field_CD4 = newCurosrArea;
    gPSSData->field_CD5 = newCursorPosition;
    gPSSData->field_CCC = x;
    gPSSData->field_CCE = y;
}

static void sub_8092660(void)
{
    int r7, r0;

    if (gPSSData->field_CD2 != 0 || gPSSData->field_CD3 != 0)
        gPSSData->field_CD0 = 12;
    else
        gPSSData->field_CD0 = 6;

    if (gPSSData->field_CD7)
        gPSSData->field_CD7 = gPSSData->field_CD0 >> 1;

    switch (gPSSData->field_CD2)
    {
    default:
        r7 = gPSSData->field_CCE - gPSSData->field_CB4->pos1.y;
        break;
    case -1:
        r7 = gPSSData->field_CCE - 0xc0 - gPSSData->field_CB4->pos1.y;
        break;
    case 1:
        r7 = gPSSData->field_CCE + 0xc0 - gPSSData->field_CB4->pos1.y;
        break;
    }

    switch (gPSSData->field_CD3)
    {
    default:
        r0 = gPSSData->field_CCC - gPSSData->field_CB4->pos1.x;
        break;
    case -1:
        r0 = gPSSData->field_CCC - 0xc0 - gPSSData->field_CB4->pos1.x;
        break;
    case 1:
        r0 = gPSSData->field_CCC + 0xc0 - gPSSData->field_CB4->pos1.x;
        break;
    }

    r7 <<= 8;
    r0 <<= 8;
    gPSSData->field_CC4 = r0 / gPSSData->field_CD0;
    gPSSData->field_CC8 = r7 / gPSSData->field_CD0;
    gPSSData->field_CBC = gPSSData->field_CB4->pos1.x << 8;
    gPSSData->field_CC0 = gPSSData->field_CB4->pos1.y << 8;
}

static void SetCursorPosition(u8 newCurosrArea, u8 newCursorPosition)
{
    sub_8092604(newCurosrArea, newCursorPosition);
    sub_8092660();
    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
    {
        if (gPSSData->inBoxMovingMode == 0 && !sIsMonBeingMoved)
            StartSpriteAnim(gPSSData->field_CB4, 1);
    }
    else
    {
        if (!IsActiveItemMoving())
            StartSpriteAnim(gPSSData->field_CB4, 1);
    }

    if (gPSSData->boxOption == BOX_OPTION_MOVE_ITEMS)
    {
        if (sBoxCursorArea == CURSOR_AREA_IN_BOX)
            TryHideItemIconAtPos(CURSOR_AREA_IN_BOX, sCursorPosition);
        else if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
            TryHideItemIconAtPos(CURSOR_AREA_IN_PARTY, sCursorPosition);

        if (newCurosrArea == CURSOR_AREA_IN_BOX)
            TryLoadItemIconAtPos(newCurosrArea, newCursorPosition);
        else if (newCurosrArea == CURSOR_AREA_IN_PARTY)
            TryLoadItemIconAtPos(newCurosrArea, newCursorPosition);
    }

    if (newCurosrArea == CURSOR_AREA_IN_PARTY && sBoxCursorArea != CURSOR_AREA_IN_PARTY)
    {
        gPSSData->field_CD6 = newCurosrArea;
        gPSSData->field_CB8->invisible = TRUE;
    }

    switch (newCurosrArea)
    {
    case CURSOR_AREA_IN_PARTY:
    case CURSOR_AREA_BOX_TITLE:
    case CURSOR_AREA_BUTTONS:
        gPSSData->field_CB4->oam.priority = 1;
        gPSSData->field_CB8->invisible = TRUE;
        gPSSData->field_CB8->oam.priority = 1;
        break;
    case CURSOR_AREA_IN_BOX:
        if (gPSSData->inBoxMovingMode != 0)
        {
            gPSSData->field_CB4->oam.priority = 0;
            gPSSData->field_CB8->invisible = TRUE;
        }
        else
        {
            gPSSData->field_CB4->oam.priority = 2;
            if (sBoxCursorArea == CURSOR_AREA_IN_BOX && sIsMonBeingMoved)
                SetMovingMonPriority(2);
        }
        break;
    }
}

static void sub_80929B0(void)
{
    sBoxCursorArea = gPSSData->field_CD4;
    sCursorPosition = gPSSData->field_CD5;
    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
    {
        if (gPSSData->inBoxMovingMode == 0 && !sIsMonBeingMoved)
            StartSpriteAnim(gPSSData->field_CB4, 1);
    }
    else
    {
        if (!IsActiveItemMoving())
            StartSpriteAnim(gPSSData->field_CB4, 1);
    }

    sub_8093A10();
    switch (sBoxCursorArea)
    {
    case CURSOR_AREA_BUTTONS:
        SetMovingMonPriority(1);
        break;
    case CURSOR_AREA_BOX_TITLE:
        sub_80920FC(TRUE);
        break;
    case CURSOR_AREA_IN_PARTY:
        gPSSData->field_CB8->subpriority = 13;
        SetMovingMonPriority(1);
        break;
    case CURSOR_AREA_IN_BOX:
        if (gPSSData->inBoxMovingMode == 0)
        {
            gPSSData->field_CB4->oam.priority = 1;
            gPSSData->field_CB8->oam.priority = 2;
            gPSSData->field_CB8->subpriority = 21;
            gPSSData->field_CB8->invisible = FALSE;
            SetMovingMonPriority(2);
        }
        break;
    }
}

void sub_8092AE4(void)
{
    u8 partyCount;

    if (!sIsMonBeingMoved)
    {
        partyCount = 0;
    }
    else
    {
        partyCount = CalculatePlayerPartyCount();
        if (partyCount >= PARTY_SIZE)
            partyCount = PARTY_SIZE - 1;
    }
    if (gPSSData->field_CB4->vFlip)
        gPSSData->field_CD7 = 1;
    SetCursorPosition(CURSOR_AREA_IN_PARTY, partyCount);
}

void sub_8092B3C(u8 cursorBoxPosition)
{
    SetCursorPosition(CURSOR_AREA_IN_BOX, cursorBoxPosition);
}

void ClearSavedCursorPos(void)
{
    gUnknown_2039826 = 0;
}

void sub_8092B5C(void)
{
    gUnknown_2039826 = sCursorPosition;
}

u8 sub_8092B70(void)
{
    return gUnknown_2039826;
}

void InitMonPlaceChange(u8 a0)
{
    static bool8 (*const placeChangeFuncs[])(void) = {
        MonPlaceChange_Move,
        MonPlaceChange_Place,
        MonPlaceChange_Shift,
    };

    gPSSData->monPlaceChangeFunc = placeChangeFuncs[a0];
    gPSSData->monPlaceChangeState = 0;
}

void sub_8092BAC(bool8 arg0)
{
    if (!arg0)
        gPSSData->monPlaceChangeFunc = sub_8092E00;
    else
        gPSSData->monPlaceChangeFunc = sub_8092E10;

    gPSSData->monPlaceChangeState = 0;
}

bool8 DoMonPlaceChange(void)
{
    return gPSSData->monPlaceChangeFunc();
}

static bool8 MonPlaceChange_Move(void)
{
    switch (gPSSData->monPlaceChangeState)
    {
    case 0:
        if (sIsMonBeingMoved)
            return FALSE;
        StartSpriteAnim(gPSSData->field_CB4, 2);
        gPSSData->monPlaceChangeState++;
        break;
    case 1:
        if (!sub_8092E20())
        {
            StartSpriteAnim(gPSSData->field_CB4, 3);
            MoveMon();
            gPSSData->monPlaceChangeState++;
        }
        break;
    case 2:
        if (!sub_8092E54())
            gPSSData->monPlaceChangeState++;
        break;
    case 3:
        return FALSE;
    }

    return TRUE;
}

static bool8 MonPlaceChange_Place(void)
{
    switch (gPSSData->monPlaceChangeState)
    {
    case 0:
        if (!sub_8092E20())
        {
            StartSpriteAnim(gPSSData->field_CB4, 2);
            PlaceMon();
            gPSSData->monPlaceChangeState++;
        }
        break;
    case 1:
        if (!sub_8092E54())
        {
            StartSpriteAnim(gPSSData->field_CB4, 0);
            gPSSData->monPlaceChangeState++;
        }
        break;
    case 2:
        return FALSE;
    }

    return TRUE;
}

static bool8 MonPlaceChange_Shift(void)
{
    switch (gPSSData->monPlaceChangeState)
    {
    case 0:
        switch (sBoxCursorArea)
        {
        case CURSOR_AREA_IN_PARTY:
            gPSSData->field_D91 = TOTAL_BOXES_COUNT;
            //gPSSData->cursorMonSpecies =
            //leave for now dont know what to do with
            break;
        case CURSOR_AREA_IN_BOX:
            gPSSData->field_D91 = StorageGetCurrentBox();
            break;
        default:
            return FALSE;
        }
        StartSpriteAnim(gPSSData->field_CB4, 2);
        sub_8090E08(gPSSData->field_D91, sCursorPosition);
        gPSSData->monPlaceChangeState++;
        break;
    case 1:
        if (!sub_8090E74())
        {
            StartSpriteAnim(gPSSData->field_CB4, 3);
            SetShiftedMonData(gPSSData->field_D91, sCursorPosition);
            gPSSData->monPlaceChangeState++;
        }
        break;
    case 2:
        return FALSE;
    }

    return TRUE;
}

static bool8 sub_8092E00(void)
{
    return sub_8092E20();
}

static bool8 sub_8092E10(void)
{
    return sub_8092E54();
}

static bool8 sub_8092E20(void)
{
    switch (gPSSData->field_CB4->pos2.y)
    {
    default:
        gPSSData->field_CB4->pos2.y++;
        break;
    case 0:
        gPSSData->field_CB4->pos2.y++;
        break;
    case 8:
        return FALSE;
    }

    return TRUE;
}

static bool8 sub_8092E54(void)
{
    switch (gPSSData->field_CB4->pos2.y)
    {
    case 0:
        return FALSE;
    default:
        gPSSData->field_CB4->pos2.y--;
        break;
    }

    return TRUE;
}

static void MoveMon(void)
{
    switch (sBoxCursorArea)//believe split process move graphic and move data
    {
    case CURSOR_AREA_IN_PARTY:
        SetMovedMonData(TOTAL_BOXES_COUNT, sCursorPosition);
        sub_8090CC0(MODE_PARTY, sCursorPosition);
        break;
    case CURSOR_AREA_IN_BOX:
        if (gPSSData->inBoxMovingMode == 0)
        {
            SetMovedMonData(StorageGetCurrentBox(), sCursorPosition);
            sub_8090CC0(MODE_BOX, sCursorPosition);
        }
        break;
    default:
        return;
    }

    sIsMonBeingMoved = TRUE;
}

static void PlaceMon(void) //think this a good place for form stuff?
{
    u8 boxId;

    switch (sBoxCursorArea)
    {
    case CURSOR_AREA_IN_PARTY:
        SetPlacedMonData(TOTAL_BOXES_COUNT, sCursorPosition);  //ok total_boxes_count is usually used for partymon /in party
        sub_8090D58(TOTAL_BOXES_COUNT, sCursorPosition);
        
        break;
    case CURSOR_AREA_IN_BOX:
        boxId = StorageGetCurrentBox();
        SetPlacedMonData(boxId, sCursorPosition);
        sub_8090D58(boxId, sCursorPosition);
        break;
    default:
        return;
    }

    sIsMonBeingMoved = FALSE;
}

void sub_8092F54(void)
{
    sub_8093A10();
}

static void SetMovedMonData(u8 boxId, u8 position)
{
    if (boxId == TOTAL_BOXES_COUNT)
    {
       gPSSData->movingMon = gPlayerParty[sCursorPosition];
    }
        
    else    //clears stats sets maxhp to 0, runs calcstat
        BoxMonAtToMon(boxId, position, &gPSSData->movingMon);


    PurgeMonOrBoxMon(boxId, position);//see what this do = /seems without this clones mon? stil heals in box, but doesn't remove mon from party
    sMovingMonOrigBoxId = boxId; //for some reason removing the burge breaks fainting mon?
    sMovingMonOrigBoxPos = position; //ok nvm that's not what broke it...
}//position is sboxcursorpos    /ISSUE was calculatebasestats change, since that is called in faint mon function

static void SetPlacedMonData(u8 boxId, u8 position)
{
    if (boxId == TOTAL_BOXES_COUNT)
    {
        gPlayerParty[position] = gPSSData->movingMon;
    }
    else
    {
        BoxMonRestorePP(&gPSSData->movingMon.box);
        SetBoxMonAt(boxId, position, &gPSSData->movingMon.box);
    }
}

//not 100% but believe this is just for moving mon,
//removed data at old position moves to new position
//as without this duplicate mon are created one at original
//and another at new position
static void PurgeMonOrBoxMon(u8 boxId, u8 position)
{
    if (boxId == TOTAL_BOXES_COUNT) //selection from in party, otherwise in box
        ZeroMonData(&gPlayerParty[position]);
    else
        ZeroBoxMonAt(boxId, position);
}

static void SetShiftedMonData(u8 boxId, u8 position)
{
    if (boxId == TOTAL_BOXES_COUNT)//believe field2108 is mon position, this just means use party data for that
        gPSSData->field_2108 = gPlayerParty[position];
    else    //clears stats sets maxhp to 0, runs calcstat
        BoxMonAtToMon(boxId, position, &gPSSData->field_2108);

    SetPlacedMonData(boxId, position);
    gPSSData->movingMon = gPSSData->field_2108;
    SetCursorMonData(&gPSSData->movingMon, MODE_PARTY);
    sMovingMonOrigBoxId = boxId;
    sMovingMonOrigBoxPos = position;
}

bool8 TryStorePartyMonInBox(u8 boxId) //think this one place for moving mon form change  vsonic
{
    s16 boxPosition = GetFirstFreeBoxSpot(boxId);
    if (boxPosition == -1)
        return FALSE;

    if (sIsMonBeingMoved)
    {
        SetPlacedMonData(boxId, boxPosition);
        DestroyMovingMonIcon();
        sIsMonBeingMoved = FALSE;
    }
    else
    {
        SetMovedMonData(TOTAL_BOXES_COUNT, sCursorPosition);
        SetPlacedMonData(boxId, boxPosition);
        DestroyPartyMonIcon(sCursorPosition);
    }

    if (boxId == StorageGetCurrentBox())
        CreateBoxMonIconAtPos(boxPosition); //seems is create sprite in box, based on personality

    StartSpriteAnim(gPSSData->field_CB4, 1);
    return TRUE;
}

void sub_8093174(void)
{
    StartSpriteAnim(gPSSData->field_CB4, 0);
    sub_8093A10();
}

void sub_8093194(void)
{
    u8 mode;

    if (sIsMonBeingMoved)
        mode = MODE_MOVE;
    else if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
        mode = MODE_PARTY;
    else
        mode = MODE_BOX;

    sub_8090FC4(mode, sCursorPosition);
    StringCopy(gPSSData->field_21E0, gPSSData->cursorMonNick);
}

bool8 sub_80931EC(void)
{
    if (!sub_8091084())
    {
        StartSpriteAnim(gPSSData->field_CB4, 0);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void ReleaseMon(void)
{
    u8 boxId;

    sub_80910CC();
    if (sIsMonBeingMoved)
    {
        sIsMonBeingMoved = FALSE;
    }
    else
    {
        if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
            boxId = TOTAL_BOXES_COUNT;
        else
            boxId = StorageGetCurrentBox();

        PurgeMonOrBoxMon(boxId, sCursorPosition);
    }
    sub_8093A10();
}

void sub_8093264(void)
{
    if (sIsMonBeingMoved)
        StartSpriteAnim(gPSSData->field_CB4, 3);
}

void InitCanReleaseMonVars(void)
{
    u16 knownIdx;
    if (sIsMonBeingMoved)
    {
        gPSSData->field_2108 = gPSSData->movingMon;
        gPSSData->field_2170 = -1;
        gPSSData->field_2171 = -1;
    }
    else
    {
        if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
        {
            gPSSData->field_2108 = gPlayerParty[sCursorPosition];
            gPSSData->field_2170 = TOTAL_BOXES_COUNT;
        }
        else
        {
            BoxMonAtToMon(StorageGetCurrentBox(), sCursorPosition, &gPSSData->field_2108);
            gPSSData->field_2170 = StorageGetCurrentBox();
        }
        gPSSData->field_2171 = sCursorPosition;
    }

    gPSSData->isSurfMon = FALSE;
    gPSSData->isDiveMon = FALSE;
    gPSSData->field_2176[0] = MOVE_SURF;
    gPSSData->field_2176[1] = MOVE_DIVE;
    gPSSData->field_2176[2] = MOVES_COUNT;
    knownIdx = GetMonData(&gPSSData->field_2108, MON_DATA_KNOWN_MOVES, (u8*)gPSSData->field_2176);
    gPSSData->isSurfMon = knownIdx & 1;
    gPSSData->isDiveMon = (knownIdx >> 1) & 1;
    if (gPSSData->isSurfMon || gPSSData->isDiveMon)
    {
        gPSSData->field_216D = 0;
    }
    else
    {
        gPSSData->field_216D = 1;
        gPSSData->field_216C = 1;
    }//vsonic IMPORTANT look into believe is hm prevent release mon

    gPSSData->field_2172 = 0;
}

s8 RunCanReleaseMon(void)
{
    u16 i;
    u16 knownMoves;

    if (gPSSData->field_216D)
        return gPSSData->field_216C;

    switch (gPSSData->field_2172)
    {
    case 0:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (gPSSData->field_2170 != TOTAL_BOXES_COUNT || gPSSData->field_2171 != i)
            {
                knownMoves = GetMonData(gPlayerParty + i, MON_DATA_KNOWN_MOVES, (u8*)gPSSData->field_2176);
                if (knownMoves & 1)
                    gPSSData->isSurfMon = FALSE;
                if (knownMoves & 2)
                    gPSSData->isDiveMon = FALSE;
            }
        }
        if (!(gPSSData->isSurfMon || gPSSData->isDiveMon))
        {
            gPSSData->field_216D = 1;
            gPSSData->field_216C = 1;
        }
        else
        {
            gPSSData->field_216E = 0;
            gPSSData->field_216F = 0;
            gPSSData->field_2172++;
        }
        break;
    case 1:
        for (i = 0; i < 5; i++)
        {
            knownMoves = GetAndCopyBoxMonDataAt(gPSSData->field_216E, gPSSData->field_216F, MON_DATA_KNOWN_MOVES, (u8*)gPSSData->field_2176);
            if (knownMoves != 0
                && !(gPSSData->field_2170 == gPSSData->field_216E && gPSSData->field_2171 == gPSSData->field_216F))
            {
                if (knownMoves & 1)
                    gPSSData->isSurfMon = FALSE;
                if (knownMoves & 2)
                    gPSSData->isDiveMon = FALSE;
            }
            if (++gPSSData->field_216F >= IN_BOX_COUNT)
            {
                gPSSData->field_216F = 0;
                if (++gPSSData->field_216E >= TOTAL_BOXES_COUNT)
                {
                    gPSSData->field_216D = 1;
                    gPSSData->field_216C = 0;
                    break;
                }
            }
        }
        if (!(gPSSData->isSurfMon || gPSSData->isDiveMon))
        {
            gPSSData->field_216D = 1;
            gPSSData->field_216C = 1;
        }
        break;
    }

    return -1;
}

void sub_8093630(void)
{
    if (sIsMonBeingMoved)
        gUnknown_20397BC = gPSSData->movingMon;
}

void sub_8093660(void)
{
    if (sIsMonBeingMoved)
    {
        if (sMovingMonOrigBoxId == TOTAL_BOXES_COUNT)
            gPSSData->movingMon = gUnknown_20397BC;
        else
            gPSSData->movingMon.box = gUnknown_20397BC.box;
    }
}

void sub_80936B8(void)
{
    if (sIsMonBeingMoved)
    {
        sub_8093630();
        gPSSData->field_218C.mon = &gUnknown_20397BC;
        gPSSData->field_2187 = 0;
        gPSSData->field_2186 = 0;
        gPSSData->field_2188 = 0;
    }
    else if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
    {
        gPSSData->field_218C.mon = gPlayerParty;
        gPSSData->field_2187 = sCursorPosition;
        gPSSData->field_2186 = CountPartyMons() - 1;
        gPSSData->field_2188 = 0;
    }
    else
    {
        gPSSData->field_218C.box = GetBoxedMonPtr(StorageGetCurrentBox(), 0);
        gPSSData->field_2187 = sCursorPosition;
        gPSSData->field_2186 = IN_BOX_COUNT - 1;
        gPSSData->field_2188 = 5;
    }
}

void sub_80937B4(void)
{
    if (sIsMonBeingMoved)
        sub_8093660();
    else
        sCursorPosition = GetLastViewedMonIndex();
}

// file boundary maybe?

s16 CompactPartySlots(void)
{
    s16 retVal = -1;
    u16 i, last;

    for (i = 0, last = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(gPlayerParty + i, MON_DATA_SPECIES);
        if (species != SPECIES_NONE)
        {
            if (i != last)
                gPlayerParty[last] = gPlayerParty[i];
            last++;
        }
        else if (retVal == -1)
        {
            retVal = i;
        }
    }
    for (; last < PARTY_SIZE; last++)
        ZeroMonData(gPlayerParty + last);

    return retVal;
}

/*void SetMonMarkings(u8 markings)
{
    gPSSData->cursorMonMarkings = markings;
    if (sIsMonBeingMoved)
    {
        SetMonData(&gPSSData->movingMon, MON_DATA_MARKINGS, &markings);
    }
    else
    {
        if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
            SetMonData(gPlayerParty + sCursorPosition, MON_DATA_MARKINGS, &markings);
        if (sBoxCursorArea == CURSOR_AREA_IN_BOX)
            SetCurrentBoxMonData(sCursorPosition, MON_DATA_MARKINGS, &markings);
    }
}*/

bool8 CanMovePartyMon(void)
{
    if (sBoxCursorArea == CURSOR_AREA_IN_PARTY && !sIsMonBeingMoved && CountPartyAliveNonEggMonsExcept(sCursorPosition) == 0)
        return TRUE;
    else
        return FALSE;
}

bool8 CanShiftMon(void)
{
    if (sIsMonBeingMoved)
    {
        if (sBoxCursorArea == CURSOR_AREA_IN_PARTY && CountPartyAliveNonEggMonsExcept(sCursorPosition) == 0)
        {
            if (gPSSData->cursorMonIsEgg)// || GetMonData(&gPSSData->movingMon, MON_DATA_HP) == 0) //what does this mean?
                return FALSE;
        }
        return TRUE;//think is swap position with control select?
    }
    return FALSE;
}

bool8 IsMonBeingMoved(void)
{
    return sIsMonBeingMoved;
}

bool8 IsCursorOnBox(void)
{
    return (sBoxCursorArea == CURSOR_AREA_BOX_TITLE);
}

bool8 IsCursorOnCloseBox(void)
{
    return (sBoxCursorArea == CURSOR_AREA_BUTTONS && sCursorPosition == 1);
}

bool8 IsCursorInBox(void)
{
    return (sBoxCursorArea == CURSOR_AREA_IN_BOX);
}

static void sub_8093A10(void)
{
    gPSSData->setMosaic = (sIsMonBeingMoved == FALSE);
    if (!sIsMonBeingMoved)
    {
        switch (sBoxCursorArea)
        {
        case CURSOR_AREA_IN_PARTY:
            if (sCursorPosition < PARTY_SIZE)
            {
                SetCursorMonData(&gPlayerParty[sCursorPosition], MODE_PARTY);
                break;
            }
            // fallthrough
        case CURSOR_AREA_BUTTONS:
        case CURSOR_AREA_BOX_TITLE:
            SetCursorMonData(NULL, MODE_MOVE);
            break;
        case CURSOR_AREA_IN_BOX:
            SetCursorMonData(GetBoxedMonPtr(StorageGetCurrentBox(), sCursorPosition), MODE_BOX);
            break;
        }
    }
}

static void sub_8093AAC(void)
{
    if (sIsMonBeingMoved)
        SetCursorMonData(&gUnknown_20397BC, MODE_PARTY);
    else
        sub_8093A10();
}

static void SetCursorMonData(void *pokemon, u8 mode)
{
    u8 *txtPtr;
    u16 gender;
    bool8 sanityIsBagEgg;

    gPSSData->cursorMonItem = 0;
    gender = MON_MALE;
    sanityIsBagEgg = FALSE;
    if (mode == MODE_PARTY)
    {
        struct Pokemon *mon = (struct Pokemon *)pokemon;

        gPSSData->cursorMonSpecies = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
       
        //strange seems formchange withdrawn only used for hoopa?
        if (gPSSData->cursorMonSpecies != SPECIES_NONE)
        {
            if (sanityIsBagEgg)
                gPSSData->cursorMonIsEgg = TRUE;
            else
                gPSSData->cursorMonIsEgg = GetMonData(mon, MON_DATA_IS_EGG);

            GetMonData(mon, MON_DATA_NICKNAME, gPSSData->cursorMonNick);
            StringGet_Nickname(gPSSData->cursorMonNick);
            gPSSData->cursorMonLevel = GetMonData(mon, MON_DATA_LEVEL);
            //gPSSData->cursorMonMarkings = GetMonData(mon, MON_DATA_MARKINGS);
            gPSSData->cursorMonPersonality = GetMonData(mon, MON_DATA_PERSONALITY);
            //checked this all I noticed is the party menu pallets
            //being affected
            gPSSData->cursorMonPalette = GetMonSpritePal(mon);
            gender = GetMonGender(mon);
            gPSSData->cursorMonItem = GetMonData(mon, MON_DATA_HELD_ITEM);

            if (IsNuzlockeModeOn() && (GetMonData(mon, MON_DATA_BOX_HP, NULL) == 0)
            && FlagGet(FLAG_SYS_POKEDEX_GET))
            {
                u8 boxHP = 0;
                SetMonData(mon, MON_DATA_HP, &boxHP);
            }
        
        }
    }
    else if (mode == MODE_BOX)
    {
        struct BoxPokemon *boxMon = (struct BoxPokemon *)pokemon;

        gPSSData->cursorMonSpecies = GetBoxMonData(pokemon, MON_DATA_SPECIES_OR_EGG);

        if (gPSSData->cursorMonSpecies != SPECIES_NONE)
        {
            u32 otId = GetBoxMonData(boxMon, MON_DATA_OT_ID);
            bool32 isShiny;
            if (sanityIsBagEgg)
                gPSSData->cursorMonIsEgg = TRUE;
            else
                gPSSData->cursorMonIsEgg = GetBoxMonData(boxMon, MON_DATA_IS_EGG);


            GetBoxMonData(boxMon, MON_DATA_NICKNAME, gPSSData->cursorMonNick);
            StringGet_Nickname(gPSSData->cursorMonNick);
            gPSSData->cursorMonLevel = GetLevelFromBoxMonExp(boxMon);
            //gPSSData->cursorMonMarkings = GetBoxMonData(boxMon, MON_DATA_MARKINGS);
            gPSSData->cursorMonPersonality = GetBoxMonData(boxMon, MON_DATA_PERSONALITY);

            //rn doesn't matter base game
            //can't display shiny sprite in box
            isShiny = IsBoxMonShiny(boxMon);
            gPSSData->cursorMonPalette = GetMonSpritePalFromSpeciesAndPersonality(gPSSData->cursorMonSpecies, isShiny, gPSSData->cursorMonPersonality);
            gender = GetGenderFromSpeciesAndPersonality(gPSSData->cursorMonSpecies, gPSSData->cursorMonPersonality);
            gPSSData->cursorMonItem = GetBoxMonData(boxMon, MON_DATA_HELD_ITEM);
        }
    }
    else
    {
        gPSSData->cursorMonSpecies = SPECIES_NONE;
        gPSSData->cursorMonItem = 0;
    }

    if (gPSSData->cursorMonSpecies == SPECIES_NONE)
    {
        StringFill(gPSSData->cursorMonNick, CHAR_SPACE, 5);
        StringFill(gPSSData->cursorMonTexts[0], CHAR_SPACE, 8);
        StringFill(gPSSData->cursorMonTexts[1], CHAR_SPACE, 8);
        StringFill(gPSSData->cursorMonTexts[2], CHAR_SPACE, 8);
        StringFill(gPSSData->cursorMonTexts[3], CHAR_SPACE, 8);
    }
    else if (gPSSData->cursorMonIsEgg)
    {
        if (sanityIsBagEgg)
            StringCopyPadded(gPSSData->cursorMonTexts[0], gPSSData->cursorMonNick, CHAR_SPACE, 5);
        else
            StringCopyPadded(gPSSData->cursorMonTexts[0], gText_EggNickname, CHAR_SPACE, 8);

        StringFill(gPSSData->cursorMonTexts[1], CHAR_SPACE, 8);
        StringFill(gPSSData->cursorMonTexts[2], CHAR_SPACE, 8);
        StringFill(gPSSData->cursorMonTexts[3], CHAR_SPACE, 8);
    }
    else
    {
        if (gPSSData->cursorMonSpecies == SPECIES_NIDORAN_F || gPSSData->cursorMonSpecies == SPECIES_NIDORAN_M)
            gender = MON_GENDERLESS;

        //changed, to remove redundancy now replaces nickname field w back slash
        //if no nickname given
        if (StringCompare(gBaseStats[gPSSData->cursorMonSpecies].speciesName, gPSSData->cursorMonNick) == IDENTICAL) //if not nicknamed reassign tempStr to speciesname, making it update capitalization
        {
            StringFill(gPSSData->cursorMonTexts[0], CHAR_SPACE, 8);
            txtPtr = gPSSData->cursorMonTexts[0];
            *(txtPtr)++ = CHAR_SLASH;

        }
        else
            StringCopyPadded(gPSSData->cursorMonTexts[0], gPSSData->cursorMonNick, CHAR_SPACE, 5);

        
        txtPtr = gPSSData->cursorMonTexts[1];
        GetSpeciesName(gStringVar1,gPSSData->cursorMonSpecies);
        StringCopyPadded(txtPtr, gStringVar1, CHAR_SPACE, 5);

        txtPtr = gPSSData->cursorMonTexts[2];
        *(txtPtr)++ = EXT_CTRL_CODE_BEGIN;
        *(txtPtr)++ = EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW;
        switch (gender)
        {
        case MON_MALE:
            *(txtPtr)++ = TEXT_COLOR_RED;
            *(txtPtr)++ = TEXT_COLOR_WHITE;
            *(txtPtr)++ = TEXT_COLOR_LIGHT_RED;
            *(txtPtr)++ = CHAR_MALE;
            break;
        case MON_FEMALE:
            *(txtPtr)++ = TEXT_COLOR_GREEN;
            *(txtPtr)++ = TEXT_COLOR_WHITE;
            *(txtPtr)++ = TEXT_COLOR_LIGHT_GREEN;
            *(txtPtr)++ = CHAR_FEMALE;
            break;
        default:
            *(txtPtr)++ = TEXT_COLOR_DARK_GREY;
            *(txtPtr)++ = TEXT_COLOR_WHITE;
            *(txtPtr)++ = TEXT_COLOR_LIGHT_GREY;
            *(txtPtr)++ = CHAR_SPACE;
            break;
        }

        *(txtPtr++) = EXT_CTRL_CODE_BEGIN;
        *(txtPtr++) = EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW;
        *(txtPtr++) = TEXT_COLOR_DARK_GREY;
        *(txtPtr++) = TEXT_COLOR_WHITE;
        *(txtPtr++) = TEXT_COLOR_LIGHT_GREY;
        *(txtPtr++) = CHAR_SPACE;
        *(txtPtr++) = CHAR_EXTRA_SYMBOL;
        *(txtPtr++) = 5; // LV_2

        txtPtr = ConvertIntToDecimalStringN(txtPtr, gPSSData->cursorMonLevel, STR_CONV_MODE_LEFT_ALIGN, 3);
        txtPtr[0] = CHAR_SPACE;
        txtPtr[1] = EOS;

        if (gPSSData->cursorMonItem != 0)
            StringCopyPadded(gPSSData->cursorMonTexts[3], ItemId_GetName(gPSSData->cursorMonItem), CHAR_SPACE, 8);
        else
            StringFill(gPSSData->cursorMonTexts[3], CHAR_SPACE, 8);
    }
}

static u8 HandleInput_InBox(void)
{
    switch (gPSSData->inBoxMovingMode)
    {
    case 0:
    default:
        return InBoxInput_Normal();
    case 1:
        return InBoxInput_GrabbingMultiple();
    case 2:
        return InBoxInput_MovingMultiple();
    }
}

static u8 InBoxInput_Normal(void)
{
    u8 input;
    s8 cursorArea;
    s8 cursorPosition;

    do
    {
        cursorArea = sBoxCursorArea;
        cursorPosition = sCursorPosition;
        gPSSData->field_CD2 = 0;
        gPSSData->field_CD3 = 0;
        gPSSData->field_CD7 = 0;
        if (JOY_REPT(DPAD_UP))
        {
            input = TRUE;
            if (sCursorPosition >= IN_BOX_COLUMNS)
            {
                cursorPosition -= IN_BOX_COLUMNS;
            }
            else
            {
                cursorArea = CURSOR_AREA_BOX_TITLE;
                cursorPosition = 0;
            }
            break;
        }
        else if (JOY_REPT(DPAD_DOWN))
        {
            input = TRUE;
            cursorPosition += IN_BOX_COLUMNS;
            if (cursorPosition >= IN_BOX_COUNT)
            {
                cursorArea = CURSOR_AREA_BUTTONS;
                cursorPosition -= IN_BOX_COUNT;
                cursorPosition /= 3;
                gPSSData->field_CD2 = 1;
                gPSSData->field_CD7 = 1;
            }
            break;
        }
        else if (JOY_REPT(DPAD_LEFT))
        {
            input = TRUE;
            if (sCursorPosition % IN_BOX_COLUMNS != 0)
            {
                cursorPosition--;
            }
            else
            {
                gPSSData->field_CD3 = -1;
                cursorPosition += (IN_BOX_COLUMNS - 1);
            }
            break;
        }
        else if (JOY_REPT(DPAD_RIGHT))
        {
            input = TRUE;
            if ((sCursorPosition + 1) % IN_BOX_COLUMNS != 0)
            {
                cursorPosition++;
            }
            else
            {
                gPSSData->field_CD3 = 1;
                cursorPosition -= (IN_BOX_COLUMNS - 1);
            }
            break;
        }
        else if (JOY_NEW(START_BUTTON))
        {
            u8 value = GetBoxMonData(GetBoxedMonPtr(StorageGetCurrentBox(), sCursorPosition), MON_DATA_BLOCK_BOX_EXP_GAIN) ? FALSE : TRUE;
            //testing - works
            if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
            {
                SetBoxMonData(GetBoxedMonPtr(StorageGetCurrentBox(), sCursorPosition), MON_DATA_BLOCK_BOX_EXP_GAIN, &value);
                if (GetBoxMonDataAt(StorageGetCurrentBox(), sCursorPosition, MON_DATA_BLOCK_BOX_EXP_GAIN))
                    gPSSData->boxMonsSprites[sCursorPosition]->oam.objMode = ST_OAM_OBJ_BLEND;
                else
                    gPSSData->boxMonsSprites[sCursorPosition]->oam.objMode = ST_OAM_OBJ_NORMAL;
            }
            break;
        }
        //believe can replace this for set block exp box
        //just use L R for quick box change

        if ((JOY_NEW(A_BUTTON)) && sub_8094924())
        {
            if (!sCanOnlyMove)
                return 8;

            if (gPSSData->boxOption != BOX_OPTION_MOVE_MONS || sIsMonBeingMoved == TRUE)
            {
                switch (sub_8094E50(0))
                {
                case PC_TEXT_STORE:
                    return INPUT_DEPOSIT;
                case PC_TEXT_WITHDRAW:
                    return INPUT_WITHDRAW;
                case PC_TEXT_MOVE:
                    return INPUT_MOVE_MON;
                case PC_TEXT_SHIFT:
                    return INPUT_SHIFT_MON;
                case PC_TEXT_PLACE:
                    return INPUT_PLACE_MON;
                case PC_TEXT_TAKE_ITEM:
                    return INPUT_TAKE_ITEM;
                case PC_TEXT_GIVE_ITEM:
                    return INPUT_GIVE_ITEM;
                case PC_TEXT_SWITCH_ITEM:
                    return INPUT_SWITCH_ITEMS;
                case PC_TEXT_SELECT:
                    return INPUT_SELECT_MON;
                }
            }
            else
            {
                gPSSData->inBoxMovingMode = 1;
                return 20;
            }
        }

        if (JOY_NEW(B_BUTTON))
            return 19;

        if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR)
        {
            if (JOY_HELD(L_BUTTON))
                return 10;
            if (JOY_HELD(R_BUTTON))
                return 9;
        }

        if (JOY_NEW(SELECT_BUTTON))
        {
            ToggleCursorMultiMoveMode();
            return 0;
        }

        input = 0;

    } while (0);

    if (input)
        SetCursorPosition(cursorArea, cursorPosition);

    return input;
}

static u8 InBoxInput_GrabbingMultiple(void)
{
    if (JOY_HELD(A_BUTTON))
    {
        if (JOY_REPT(DPAD_UP))
        {
            if (sCursorPosition / IN_BOX_COLUMNS != 0)
            {
                SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition - IN_BOX_COLUMNS);
                return 21;
            }
            else
            {
                return 24;
            }
        }
        else if (JOY_REPT(DPAD_DOWN))
        {
            if (sCursorPosition + IN_BOX_COLUMNS < IN_BOX_COUNT)
            {
                SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition + IN_BOX_COLUMNS);
                return 21;
            }
            else
            {
                return 24;
            }
        }
        else if (JOY_REPT(DPAD_LEFT))
        {
            if (sCursorPosition % IN_BOX_COLUMNS != 0)
            {
                SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition - 1);
                return 21;
            }
            else
            {
                return 24;
            }
        }
        else if (JOY_REPT(DPAD_RIGHT))
        {
            if ((sCursorPosition + 1) % IN_BOX_COLUMNS != 0)
            {
                SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition + 1);
                return 21;
            }
            else
            {
                return 24;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (sub_8095AA0() == sCursorPosition)
        {
            gPSSData->inBoxMovingMode = 0;
            gPSSData->field_CB8->invisible = FALSE;
            return 22;
        }
        else
        {
            sIsMonBeingMoved = (gPSSData->cursorMonSpecies != SPECIES_NONE);
            gPSSData->inBoxMovingMode = 2;
            sMovingMonOrigBoxId = StorageGetCurrentBox();
            return 23;
        }
    }
}

static u8 InBoxInput_MovingMultiple(void)
{
    if (JOY_REPT(DPAD_UP))
    {
        if (sub_8095474(0))
        {
            SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition - IN_BOX_COLUMNS);
            return 25;
        }
        else
        {
            return 24;
        }
    }
    else if (JOY_REPT(DPAD_DOWN))
    {
        if (sub_8095474(1))
        {
            SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition + IN_BOX_COLUMNS);
            return 25;
        }
        else
        {
            return 24;
        }
    }
    else if (JOY_REPT(DPAD_LEFT))
    {
        if (sub_8095474(2))
        {
            SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition - 1);
            return 25;
        }
        else
        {
            return 10;
        }
    }
    else if (JOY_REPT(DPAD_RIGHT))
    {
        if (sub_8095474(3))
        {
            SetCursorPosition(CURSOR_AREA_IN_BOX, sCursorPosition + 1);
            return 25;
        }
        else
        {
            return 9;
        }
    }
    else if (JOY_NEW(A_BUTTON))
    {
        if (sub_8095ABC())
        {
            sIsMonBeingMoved = FALSE;
            gPSSData->inBoxMovingMode = 0;
            return 26;
        }
        else
        {
            return 24;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        return 24;
    }
    else
    {
        if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR)
        {
            if (JOY_HELD(L_BUTTON))
                return 10;
            if (JOY_HELD(R_BUTTON))
                return 9;
        }

        return 0;
    }
}

static u8 HandleInput_InParty(void)
{
    u8 input;
    bool8 gotoBox;
    s8 cursorArea;
    s8 cursorPosition;

    do
    {
        cursorArea = sBoxCursorArea;
        cursorPosition = sCursorPosition;
        gPSSData->field_CD3 = 0;
        gPSSData->field_CD2 = 0;
        gPSSData->field_CD7 = 0;
        gotoBox = FALSE;
        input = 0;

        if (JOY_REPT(DPAD_UP))
        {
            if (--cursorPosition < 0)
                cursorPosition = PARTY_SIZE;
            if (cursorPosition != sCursorPosition)
                input = 1;
            break;
        }
        else if (JOY_REPT(DPAD_DOWN))
        {
            if (++cursorPosition > PARTY_SIZE)
                cursorPosition = 0;
            if (cursorPosition != sCursorPosition)
                input = 1;
            break;
        }
        else if (JOY_REPT(DPAD_LEFT) && sCursorPosition != 0)
        {
            input = 1;
            gPSSData->field_CD6 = sCursorPosition;
            cursorPosition = 0;
            break;
        }
        else if (JOY_REPT(DPAD_RIGHT))
        {
            if (sCursorPosition == 0)
            {
                input = 1;
                cursorPosition = gPSSData->field_CD6;
            }
            else
            {
                input = INPUT_HIDE_PARTY;
                cursorArea = CURSOR_AREA_IN_BOX;
                cursorPosition = 0;
            }
            break;
        }
        else if (JOY_NEW(START_BUTTON))
        {
            u8 value = GetBoxMonData(&gPlayerParty[sCursorPosition].box, MON_DATA_BLOCK_BOX_EXP_GAIN) ? FALSE : TRUE;
            //testing - works
            if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
            {
                SetBoxMonData(&gPlayerParty[sCursorPosition].box, MON_DATA_BLOCK_BOX_EXP_GAIN, &value);
                if (GetBoxMonData(&gPlayerParty[sCursorPosition].box, MON_DATA_BLOCK_BOX_EXP_GAIN))
                    gPSSData->partySprites[sCursorPosition]->oam.objMode = ST_OAM_OBJ_BLEND;
                else
                    gPSSData->partySprites[sCursorPosition]->oam.objMode = ST_OAM_OBJ_NORMAL;
            }    
            break;
        }

        if (JOY_NEW(A_BUTTON))
        {
            if (sCursorPosition == PARTY_SIZE)
            {
                if (gPSSData->boxOption == BOX_OPTION_DEPOSIT)
                    return 4;

                gotoBox = TRUE;
            }
            else if (sub_8094924())
            {
                if (!sCanOnlyMove)
                    return 8;

                switch (sub_8094E50(0))
                {
                case PC_TEXT_STORE:
                    return INPUT_DEPOSIT;
                case PC_TEXT_WITHDRAW:
                    return INPUT_WITHDRAW;
                case PC_TEXT_MOVE:
                    return INPUT_MOVE_MON;
                case PC_TEXT_SHIFT:
                    return INPUT_SHIFT_MON;
                case PC_TEXT_PLACE:
                    return INPUT_PLACE_MON;
                case PC_TEXT_TAKE_ITEM:
                    return INPUT_TAKE_ITEM;
                case PC_TEXT_GIVE_ITEM:
                    return INPUT_GIVE_ITEM;
                case PC_TEXT_SWITCH_ITEM:
                    return INPUT_SWITCH_ITEMS;
                case PC_TEXT_SELECT:
                    return INPUT_SELECT_MON;
                }
            }
        }

        if (JOY_NEW(B_BUTTON))
        {
            if (gPSSData->boxOption == BOX_OPTION_DEPOSIT)
                return INPUT_PRESSED_B;

            gotoBox = TRUE;
        }

        if (gotoBox)
        {
            input = INPUT_HIDE_PARTY;
            cursorArea = CURSOR_AREA_IN_BOX;
            cursorPosition = 0;
        }
        else if (JOY_NEW(SELECT_BUTTON))
        {
            ToggleCursorMultiMoveMode();
            return 0;
        }

    } while (0);

    if (input != 0)
    {
        if (input != 6)
            SetCursorPosition(cursorArea, cursorPosition);
    }

    return input;
}

static u8 HandleInput_OnBox(void)
{
    u8 input;
    s8 cursorArea;
    s8 cursorPosition;

    do
    {
        gPSSData->field_CD3 = 0;
        gPSSData->field_CD2 = 0;
        gPSSData->field_CD7 = 0;

        if (JOY_REPT(DPAD_UP))
        {
            input = 1;
            cursorArea = CURSOR_AREA_BUTTONS;
            cursorPosition = 0;
            gPSSData->field_CD7 = 1;
            break;
        }
        else if (JOY_REPT(DPAD_DOWN))
        {
            input = 1;
            cursorArea = CURSOR_AREA_IN_BOX;
            cursorPosition = 2;
            break;
        }

        if (JOY_HELD(DPAD_LEFT))
            return 10;
        if (JOY_HELD(DPAD_RIGHT))
            return 9;

        if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR)
        {
            if (JOY_HELD(L_BUTTON))
                return 10;
            if (JOY_HELD(R_BUTTON))
                return 9;
        }

        if (JOY_NEW(A_BUTTON))
        {
            sub_80920FC(FALSE);
            AddBoxMenu();
            return 7;
        }

        if (JOY_NEW(B_BUTTON))
            return 19;

        if (JOY_NEW(SELECT_BUTTON))
        {
            ToggleCursorMultiMoveMode();
            return 0;
        }

        input = 0;

    } while (0);

    if (input)
    {
        if (cursorArea != CURSOR_AREA_BOX_TITLE)
            sub_80920FC(FALSE);
        SetCursorPosition(cursorArea, cursorPosition);
    }

    return input;
}

static u8 HandleInput_OnButtons(void)
{
    u8 input;
    s8 cursorArea;
    s8 cursorPosition;
    s8 prevPos;

    do
    {
        cursorArea = sBoxCursorArea;
        cursorPosition = sCursorPosition;
        gPSSData->field_CD3 = 0;
        gPSSData->field_CD2 = 0;
        gPSSData->field_CD7 = 0;

        if (JOY_REPT(DPAD_UP))
        {
            input = 1;
            cursorArea = CURSOR_AREA_IN_BOX;
            gPSSData->field_CD2 = -1;
            if (sCursorPosition == 0)
                cursorPosition = IN_BOX_COUNT - 1 - 5;
            else
                cursorPosition = IN_BOX_COUNT - 1;
            gPSSData->field_CD7 = 1;
            break;
        }
        else if (JOY_REPT(DPAD_DOWN | START_BUTTON))
        {
            input = 1;
            cursorArea = CURSOR_AREA_BOX_TITLE;
            cursorPosition = 0;
            gPSSData->field_CD7 = 1;
            break;
        }

        if (JOY_REPT(DPAD_LEFT))
        {
            input = 1;
            if (--cursorPosition < 0)
                cursorPosition = 1;
            break;
        }
        else if (JOY_REPT(DPAD_RIGHT))
        {
            input = 1;
            if (++cursorPosition > 1)
                cursorPosition = 0;
            break;
        }

        if (JOY_NEW(A_BUTTON))
        {
            return cursorPosition == 0 ? 5 : 4;
        }
        if (JOY_NEW(B_BUTTON))
            return 19;

        if (JOY_NEW(SELECT_BUTTON))
        {
            ToggleCursorMultiMoveMode();
            return 0;
        }

        input = 0;
    } while (0);

    if (input != 0)
        SetCursorPosition(cursorArea, cursorPosition);

    return input;
}

u8 HandleInput(void)
{
    struct
    {
        u8 (*func)(void);
        s8 area;
    }
    static const inputFuncs[] = {
        {HandleInput_InBox, CURSOR_AREA_IN_BOX},
        {HandleInput_InParty, CURSOR_AREA_IN_PARTY},
        {HandleInput_OnBox, CURSOR_AREA_BOX_TITLE},
        {HandleInput_OnButtons, CURSOR_AREA_BUTTONS},
        {NULL, 0},
    };

    u16 i = 0;
    while (inputFuncs[i].func != NULL)
    {
        if (inputFuncs[i].area == sBoxCursorArea)
            return inputFuncs[i].func();
        i++;
    }

    return 0;
}

static void AddBoxMenu(void)
{
    InitMenu();
    SetMenuText(PC_TEXT_JUMP);
    SetMenuText(PC_TEXT_WALLPAPER);
    SetMenuText(PC_TEXT_NAME);
    SetMenuText(PC_TEXT_CANCEL);
}

static bool8 sub_8094924(void)
{
    InitMenu();
    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return SetMenuTexts_Mon();
    else
        return sub_8094A0C();
}

static bool8 SetMenuTexts_Mon(void)
{
    u16 species = GetSpeciesAtCursorPosition();

    switch (gPSSData->boxOption)
    {
    case BOX_OPTION_DEPOSIT:
        if (species)
            SetMenuText(PC_TEXT_STORE);
        else
            return FALSE;
        break;
    case BOX_OPTION_WITHDRAW:
        if (species)
            SetMenuText(PC_TEXT_WITHDRAW);
        else
            return FALSE;
        break;
    case BOX_OPTION_MOVE_MONS:
        if (sIsMonBeingMoved)
        {
            if (species)
                SetMenuText(PC_TEXT_SHIFT);
            else
                SetMenuText(PC_TEXT_PLACE);
        }
        else
        {
            if (species)
                SetMenuText(PC_TEXT_MOVE);
            else
                return FALSE;
        }
        break;
    case BOX_OPTION_SELECT_MON:
        if (species != SPECIES_NONE)
            SetMenuText(PC_TEXT_SELECT);
        else
            return FALSE;
        break;
    case BOX_OPTION_MOVE_ITEMS:
    default:
        return FALSE;
    }

    SetMenuText(PC_TEXT_SUMMARY);
    if (gPSSData->boxOption == BOX_OPTION_MOVE_MONS)
    {
        if (!sBoxCursorArea)
            SetMenuText(PC_TEXT_WITHDRAW);
        else
            SetMenuText(PC_TEXT_STORE);
    }

    SetMenuText(PC_TEXT_MARK);    
    if (gPSSData->boxOption != BOX_OPTION_SELECT_MON)
        SetMenuText(PC_TEXT_RELEASE);
    SetMenuText(PC_TEXT_CANCEL);
    return TRUE;
}

static bool8 sub_8094A0C(void)
{
    if (gPSSData->cursorMonSpecies == SPECIES_EGG)
        return FALSE;

    if (!IsActiveItemMoving())
    {
        if (gPSSData->cursorMonItem == ITEM_NONE)
        {
            if (gPSSData->cursorMonSpecies == SPECIES_NONE)
                return FALSE;

            SetMenuText(PC_TEXT_GIVE_ITEM2);
        }
        else
        {
            if (!ItemIsMail(gPSSData->cursorMonItem))
            {
                SetMenuText(PC_TEXT_TAKE_ITEM);
                SetMenuText(PC_TEXT_BAG);
            }
            SetMenuText(PC_TEXT_ITEM_INFO);
        }
    }
    else
    {
        if (gPSSData->cursorMonItem == ITEM_NONE)
        {
            if (gPSSData->cursorMonSpecies == SPECIES_NONE)
                return FALSE;

            SetMenuText(PC_TEXT_GIVE_ITEM);
        }
        else
        {
            if (ItemIsMail(gPSSData->cursorMonItem) == TRUE)
                return FALSE;

            SetMenuText(PC_TEXT_SWITCH_ITEM);
        }
    }

    SetMenuText(PC_TEXT_CANCEL);
    return TRUE;
}

static void SpriteCB_CursorShadow(struct Sprite *sprite)
{
    sprite->pos1.x = gPSSData->field_CB4->pos1.x;
    sprite->pos1.y = gPSSData->field_CB4->pos1.y + 20;
}

static void CreateCursorSprites(void)
{
    u16 x, y;
    u8 spriteId;
    u8 priority, subpriority;
    struct SpriteSheet spriteSheets[] = {
        {sHandCursorTiles, 0x800, TAG_TILE_0},
        {sHandCursorShadowTiles, 0x80, TAG_TILE_1},
        {}
    };

    struct SpritePalette spritePalettes[] = {
        {sHandCursorPalette, TAG_PAL_DAC7},
        {}
    };

    static const struct OamData sOamData_857BA0C = {
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .priority = 1,
    };
    static const struct OamData sOamData_857BA14 = {
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .priority = 1,
    };

    static const union AnimCmd sSpriteAnim_857BA1C[] = {
        ANIMCMD_FRAME(0, 30),
        ANIMCMD_FRAME(16, 30),
        ANIMCMD_JUMP(0)
    };
    static const union AnimCmd sSpriteAnim_857BA28[] = {
        ANIMCMD_FRAME(0, 5),
        ANIMCMD_END
    };
    static const union AnimCmd sSpriteAnim_857BA30[] = {
        ANIMCMD_FRAME(32, 5),
        ANIMCMD_END
    };
    static const union AnimCmd sSpriteAnim_857BA38[] = {
        ANIMCMD_FRAME(48, 5),
        ANIMCMD_END
    };

    static const union AnimCmd *const sSpriteAnimTable_857BA40[] = {
        sSpriteAnim_857BA1C,
        sSpriteAnim_857BA28,
        sSpriteAnim_857BA30,
        sSpriteAnim_857BA38
    };

    static const struct SpriteTemplate gSpriteTemplate_857BA50 = {
        .tileTag = TAG_TILE_0,
        .paletteTag = TAG_PAL_WAVEFORM,
        .oam = &sOamData_857BA0C,
        .anims = sSpriteAnimTable_857BA40,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    };

    static const struct SpriteTemplate gSpriteTemplate_857BA68 = {
        .tileTag = TAG_TILE_1,
        .paletteTag = TAG_PAL_WAVEFORM,
        .oam = &sOamData_857BA14,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_CursorShadow,
    };

    LoadSpriteSheets(spriteSheets);
    LoadSpritePalettes(spritePalettes);
    gPSSData->field_CD8[0] = IndexOfSpritePaletteTag(TAG_PAL_WAVEFORM);
    gPSSData->field_CD8[1] = IndexOfSpritePaletteTag(TAG_PAL_DAC7);

    sub_8092398(sBoxCursorArea, sCursorPosition, &x, &y);
    spriteId = CreateSprite(&gSpriteTemplate_857BA50, x, y, 6);
    if (spriteId != MAX_SPRITES)
    {
        gPSSData->field_CB4 = &gSprites[spriteId];
        gPSSData->field_CB4->oam.paletteNum = gPSSData->field_CD8[sCanOnlyMove];
        gPSSData->field_CB4->oam.priority = 1;
        if (sIsMonBeingMoved)
            StartSpriteAnim(gPSSData->field_CB4, 3);
    }
    else
    {
        gPSSData->field_CB4 = NULL;
    }

    if (sBoxCursorArea == CURSOR_AREA_IN_PARTY)
    {
        subpriority = 13;
        priority = 1;
    }
    else
    {
        subpriority = 21;
        priority = 2;
    }

    spriteId = CreateSprite(&gSpriteTemplate_857BA68, 0, 0, subpriority);
    if (spriteId != MAX_SPRITES)
    {
        gPSSData->field_CB8 = &gSprites[spriteId];
        gPSSData->field_CB8->oam.priority = priority;
        if (sBoxCursorArea)
            gPSSData->field_CB8->invisible = 1;
    }
    else
    {
        gPSSData->field_CB8 = NULL;
    }
}

static void ToggleCursorMultiMoveMode(void)
{
    sCanOnlyMove = !sCanOnlyMove;
    gPSSData->field_CB4->oam.paletteNum = gPSSData->field_CD8[sCanOnlyMove];
}

u8 GetBoxCursorPosition(void)
{
    return sCursorPosition;
}

void GetCursorBoxColumnAndRow(u8 *arg0, u8 *arg1)
{
    if (sBoxCursorArea == CURSOR_AREA_IN_BOX)
    {
        *arg0 = sCursorPosition % IN_BOX_COLUMNS;
        *arg1 = sCursorPosition / IN_BOX_COLUMNS;
    }
    else
    {
        *arg0 = 0;
        *arg1 = 0;
    }
}

void StartCursorAnim(u8 animNum)
{
    StartSpriteAnim(gPSSData->field_CB4, animNum);
}

u8 sub_8094D34(void)
{
    return sMovingMonOrigBoxId;
}

void sub_8094D40(void)
{
    gPSSData->field_CB4->oam.priority = 1;
}

void TryHideItemAtCursor(void)
{
    if (sBoxCursorArea == CURSOR_AREA_IN_BOX)
        TryHideItemIconAtPos(CURSOR_AREA_IN_BOX, sCursorPosition);
}

void TryShowItemAtCursor(void)
{
    if (sBoxCursorArea == CURSOR_AREA_IN_BOX)
        TryLoadItemIconAtPos(CURSOR_AREA_IN_BOX, sCursorPosition);
}

void InitMenu(void)
{
    gPSSData->menuItemsCount = 0;
    gPSSData->menuWidth = 0;
    gPSSData->menuWindow.bg = 0;
    gPSSData->menuWindow.paletteNum = 15;
    gPSSData->menuWindow.baseBlock = 92;
}

static const u8 *const sMenuTexts[] = {
    [PC_TEXT_CANCEL]     = gPCText_Cancel,
    [PC_TEXT_STORE]      = gPCText_Store,
    [PC_TEXT_WITHDRAW]   = gPCText_Withdraw,
    [PC_TEXT_MOVE]       = gPCText_Move,
    [PC_TEXT_SHIFT]      = gPCText_Shift,
    [PC_TEXT_PLACE]      = gPCText_Place,
    [PC_TEXT_SUMMARY]    = gPCText_Summary,
    [PC_TEXT_RELEASE]    = gPCText_Release,
    [PC_TEXT_MARK]       = gPCText_Mark,
    [PC_TEXT_JUMP]       = gPCText_Jump,
    [PC_TEXT_WALLPAPER]  = gPCText_Wallpaper,
    [PC_TEXT_NAME]       = gPCText_Name,
    [PC_TEXT_TAKE_ITEM]  = gPCText_Take,
    [PC_TEXT_GIVE_ITEM]  = gPCText_Give,
    [PC_TEXT_GIVE_ITEM2] = gPCText_Give,
    [PC_TEXT_SWITCH_ITEM] = gPCText_Switch,
    [PC_TEXT_BAG]        = gPCText_Bag,
    [PC_TEXT_ITEM_INFO]  = gPCText_Info,
    [PC_TEXT_SCENERY1]   = gPCText_Scenery1,
    [PC_TEXT_SCENERY2]   = gPCText_Scenery2,
    [PC_TEXT_SCENERY3]   = gPCText_Scenery3,
    [PC_TEXT_ETCETERA]   = gPCText_Etcetera,
    [PC_TEXT_FOREST]     = gPCText_Forest,
    [PC_TEXT_CITY]       = gPCText_City,
    [PC_TEXT_DESERT]     = gPCText_Desert,
    [PC_TEXT_SAVANNA]    = gPCText_Savanna,
    [PC_TEXT_CRAG]       = gPCText_Crag,
    [PC_TEXT_VOLCANO]    = gPCText_Volcano,
    [PC_TEXT_SNOW]       = gPCText_Snow,
    [PC_TEXT_CAVE]       = gPCText_Cave,
    [PC_TEXT_BEACH]      = gPCText_Beach,
    [PC_TEXT_SEAFLOOR]   = gPCText_Seafloor,
    [PC_TEXT_RIVER]      = gPCText_River,
    [PC_TEXT_SKY]        = gPCText_Sky,
    [PC_TEXT_POLKADOT]   = gPCText_PolkaDot,
    [PC_TEXT_POKECENTER] = gPCText_Pokecenter,
    [PC_TEXT_MACHINE]    = gPCText_Machine,
    [PC_TEXT_SIMPLE]     = gPCText_Simple,
    [PC_TEXT_SELECT]     = COMPOUND_STRING("SELECT"),
};

void SetMenuText(u8 textId)
{
    if (gPSSData->menuItemsCount < MAX_MENU_ITEMS)
    {
        u8 len;
        struct StorageMenu *menu = &gPSSData->menuItems[gPSSData->menuItemsCount];

        menu->text = sMenuTexts[textId];
        menu->textId = textId;
        len = StringLength(menu->text);
        if (len > gPSSData->menuWidth)
            gPSSData->menuWidth = len;

        gPSSData->menuItemsCount++;
    }
}

s8 sub_8094E50(u8 arg0)
{
    if (arg0 >= gPSSData->menuItemsCount)
        return -1;
    else
        return gPSSData->menuItems[arg0].textId;
}

void AddMenu(void)
{
    gPSSData->menuWindow.width = gPSSData->menuWidth + 2;
    gPSSData->menuWindow.height = 2 * gPSSData->menuItemsCount;
    gPSSData->menuWindow.tilemapLeft = 29 - gPSSData->menuWindow.width;
    gPSSData->menuWindow.tilemapTop = 15 - gPSSData->menuWindow.height;
    gPSSData->field_CB0 = AddWindow(&gPSSData->menuWindow);
    ClearWindowTilemap(gPSSData->field_CB0);
    DrawStdFrameWithCustomTileAndPalette(gPSSData->field_CB0, FALSE, 0x00b, 14);
    PrintTextArray(gPSSData->field_CB0, 1, 8, 2, 16, gPSSData->menuItemsCount, (void*)gPSSData->menuItems);
    Menu_InitCursor(gPSSData->field_CB0, 1, 0, 2, 16, gPSSData->menuItemsCount, 0);
    ScheduleBgCopyTilemapToVram(0);
}

bool8 sub_8094F90(void)
{
    // Some debug flag?
    return FALSE;
}

s16 sub_8094F94(void)
{
    s32 textId = -2;

    do
    {
        if (JOY_NEW(A_BUTTON))
        {
            textId = Menu_GetCursorPos();
            break;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            textId = -1;
        }

        if (JOY_NEW(DPAD_UP))
        {
            PlaySE(SE_SELECT);
            Menu_MoveCursor(-1);
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            PlaySE(SE_SELECT);
            Menu_MoveCursor(1);
        }
    } while (0);

    if (textId != -2)
        sub_8095024();

    if (textId >= 0)
        textId = gPSSData->menuItems[textId].textId;

    return textId;
}

void sub_8095024(void)
{
    ClearStdWindowAndFrameToTransparent(gPSSData->field_CB0, TRUE);
    RemoveWindow(gPSSData->field_CB0);
}
