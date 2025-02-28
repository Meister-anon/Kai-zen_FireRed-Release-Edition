#include "global.h"
#include "gflib.h"
#include "pokemon_storage_system_internal.h"
#include "event_data.h"

static void ApplyOakRanchExperience(struct Pokemon *mon); //ohop make work



void BackupPokemonStorage(struct PokemonStorage * dest)
{
    *dest = *gPokemonStoragePtr;
}

void RestorePokemonStorage(struct PokemonStorage * src)
{
    *gPokemonStoragePtr = *src;
}

// Functions here are general utility functions.
u8 StorageGetCurrentBox(void)
{
    return gPokemonStoragePtr->currentBox;
}

void SetCurrentBox(u8 boxId)
{
    if (boxId < TOTAL_BOXES_COUNT)
        gPokemonStoragePtr->currentBox = boxId;
}

u32 GetBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        return GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], request);
    else
        return 0;
}

void SetBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request, const void *value)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        SetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], request, value);
}

u32 GetCurrentBoxMonData(u8 boxPosition, s32 request)
{
    return GetBoxMonDataAt(gPokemonStoragePtr->currentBox, boxPosition, request);
}

void SetCurrentBoxMonData(u8 boxPosition, s32 request, const void *value)
{
    SetBoxMonDataAt(gPokemonStoragePtr->currentBox, boxPosition, request, value);
}

void GetBoxMonNickAt(u8 boxId, u8 boxPosition, u8 *dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_NICKNAME, dst);
    else
        *dst = EOS;
}

void SetBoxMonNickAt(u8 boxId, u8 boxPosition, const u8 *nick)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        SetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_NICKNAME, nick);
}

u32 GetAndCopyBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request, void *dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        return GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], request, dst);
    else
        return 0;
}

void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon * src)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        gPokemonStoragePtr->boxes[boxId][boxPosition] = *src;
}

void CopyBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon * dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        *dst = gPokemonStoragePtr->boxes[boxId][boxPosition];
}

void CreateBoxMonAt(u8 boxId, u8 boxPosition, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 personality, u8 otIDType, u32 otID)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
    {
        CreateBoxMon(&gPokemonStoragePtr->boxes[boxId][boxPosition],
                     species,
                     level,
                     fixedIV,
                     hasFixedPersonality, personality,
                     otIDType, otID);
    }
}//appears unused?

//used for release mon and apparenlty storing/moving in pc?
void ZeroBoxMonAt(u8 boxId, u8 boxPosition)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        ZeroBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition]);
}

//idk may be able to use this for something else
static u8 ReturnLevelBasedOnExp(u32 currExp, u16 species)
{
    u32 lvl;
    u8 Level;

    for (lvl = 1; gExperienceTables[gBaseStats[species].growthRate][lvl] <= currExp; lvl++)
    {
        Level = lvl;
    }
    
    return Level;

}

#define BOX_EXP_GAIN
void BoxMonAtGainExp(struct BoxPokemon * mon, u16 species, u32 currExperience)
{
    u32 Augmentedexperience;
    //u8 CurrLevel;
    //struct Pokemon dst;
    //BoxMonToMon(mon, &dst);
    //u32 Currexperience = currExperience;
    //experience <= gExperienceTables[gBaseStats[species].growthRate][12])
    //since oak ranch no longer using stat recalc
    //just make its own version of tryincrementmonlevel
    //that takes all the argument

    if (currExperience == 0) //if CanBoxMonGainExp returns false
        return;

    if (IsNuzlockeModeOn() && (GetMonData(mon, MON_DATA_BOX_HP, NULL) == 0)
        && FlagGet(FLAG_SYS_POKEDEX_GET)) //should be block exp gain for dead mon,to prevent level up
        return;

    //currExperience -= 1; //sub 1 to get back to real value //actually don't need this even at lvl 1 exp is still above 0

    //CurrLevel = ReturnLevelBasedOnExp(currExperience, species);
    //level set byitself so apparently don't need this, ro to set level
    //meaning wouldn't need applyoakranchexperience function


        if (currExperience < gExperienceTables[gBaseStats[species].growthRate][100])
        {
            if (currExperience <= gExperienceTables[gBaseStats[species].growthRate][11]) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                Augmentedexperience = currExperience + (gSaveBlock1Ptr->oakRanchStepCounter); //nvm didn't work for some reason because didn't use constant
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);  //replaced setup, now use 17 value wrap around var before counter increments, will need rebalance here
                //ApplyOakRanchExperience(mon);
            }
            else if (currExperience <= gExperienceTables[gBaseStats[species].growthRate][25]) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                Augmentedexperience = currExperience + (gSaveBlock1Ptr->oakRanchStepCounter * 3);
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);
                //ApplyOakRanchExperience(&dst);
            }
            else if (currExperience <= gExperienceTables[gBaseStats[species].growthRate][30]) //keep an eye on this one, may shift to 35 and next to 45
            {
                Augmentedexperience = currExperience + (gSaveBlock1Ptr->oakRanchStepCounter * 5);
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);
                //ApplyOakRanchExperience(&dst);
            }
            else if (currExperience <= gExperienceTables[gBaseStats[species].growthRate][40]) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                Augmentedexperience = currExperience + (gSaveBlock1Ptr->oakRanchStepCounter * 8);
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);
                //ApplyOakRanchExperience(&dst);
            }
            else if (currExperience <= gExperienceTables[gBaseStats[species].growthRate][55]) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                Augmentedexperience = currExperience + (gSaveBlock1Ptr->oakRanchStepCounter * 16);
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);
                //ApplyOakRanchExperience(&dst);
            }
            else if (currExperience <= gExperienceTables[gBaseStats[species].growthRate][75]) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                Augmentedexperience = currExperience + ((gSaveBlock1Ptr->oakRanchStepCounter * gSaveBlock1Ptr->oakRanchStepCounter) / 2);
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);
                //ApplyOakRanchExperience(&dst);
            }
            else if (currExperience < gExperienceTables[gBaseStats[species].growthRate][100])
            {
                Augmentedexperience = currExperience + (gSaveBlock1Ptr->oakRanchStepCounter * gSaveBlock1Ptr->oakRanchStepCounter);
                
                if (Augmentedexperience > gExperienceTables[gBaseStats[species].growthRate][100])
                    Augmentedexperience = gExperienceTables[gBaseStats[species].growthRate][100];
                SetBoxMonData(mon, MON_DATA_EXP, &Augmentedexperience);
                //ApplyOakRanchExperience(mon); //using this is irrelvant for some reason not setting exp evenly to each slot
            } //but it does or seemingly does if I  use struc Pokemon *mon; ?  but it ignores rule and sets to lvl 100 with FAR more lag for unkown reasons
        }        

        
}

//since this is just doing increment level, make its own version of that
//that takes passes all arguments rather than needing to use getmondata calls
static void ApplyOakRanchExperience(struct Pokemon *mon)
{

    //hmm actually I think I can for loop above function to return levle
    //nah will still need it to set level and that only

    //looks like this is olny thing that would need to run
    //boxmontomon, so put extra condition over it, to only run if actually increasing level

    

    TryIncrementMonLevel(mon); //increment level if less than max level, commented out move learn
    
    // Re-calculate the mons stats at its new level.
    //CalculateMonStats(mon);
}

void AssignMonOrBoxMon(struct Pokemon *mon, struct BoxPokemon *boxmon, u8 monId, u8 boxId)
{
    boxmon = NULL;
    mon = NULL;

    if ((VarGet(VAR_0x8014) != GetBoxMonData(&gPlayerParty[monId].box, MON_DATA_PERSONALITY)) && (VarGet(VAR_RESULT) != GetBoxMonData(&gPlayerParty[monId].box, MON_DATA_SPECIES)))
            boxmon =  &gPokemonStoragePtr->boxes[boxId][monId];
        else
            mon = &gPlayerParty[monId];
}

void BoxMonAtToMon(u8 boxId, u8 boxPosition, struct Pokemon * dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        BoxMonToMon(&gPokemonStoragePtr->boxes[boxId][boxPosition], dst);
}

struct BoxPokemon * GetBoxedMonPtr(u8 boxId, u8 boxPosition)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        return &gPokemonStoragePtr->boxes[boxId][boxPosition];
    else
        return NULL;
}

u8 *GetBoxNamePtr(u8 boxId)
{
    if (boxId < TOTAL_BOXES_COUNT)
        return gPokemonStoragePtr->boxNames[boxId];
    else
        return NULL;
}

u8 GetBoxWallpaper(u8 boxId)
{
    if (boxId < TOTAL_BOXES_COUNT)
        return gPokemonStoragePtr->boxWallpapers[boxId];
    else
        return 0;
}

void SetBoxWallpaper(u8 boxId, u8 wallpaperId)
{
    if (boxId < TOTAL_BOXES_COUNT && wallpaperId < WALLPAPER_COUNT)
        gPokemonStoragePtr->boxWallpapers[boxId] = wallpaperId;
}

s16 SeekToNextMonInBox(struct BoxPokemon * boxMons, s8 curIndex, u8 maxIndex, u8 flags)
{
    // flags:
    // bit 0: Allow eggs
    // bit 1: Search backwards
    s16 i;
    s16 adder;
    if (flags == 0 || flags == 1)
        adder = 1;
    else
        adder = -1;

    if (flags == 1 || flags == 3)
    {
        for (i = curIndex + adder; i >= 0 && i <= maxIndex; i += adder)
        {
            if (GetBoxMonData(&boxMons[i], MON_DATA_SPECIES) != SPECIES_NONE)
                return i;
        }
    }
    else
    {
        for (i = curIndex + adder; i >= 0 && i <= maxIndex; i += adder)
        {
            if (GetBoxMonData(&boxMons[i], MON_DATA_SPECIES) != SPECIES_NONE
                && !GetBoxMonData(&boxMons[i], MON_DATA_IS_EGG))
                return i;
        }
    }

    return -1;
}
