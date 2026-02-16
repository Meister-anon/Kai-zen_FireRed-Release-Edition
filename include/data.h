#ifndef GUARD_DATA_H
#define GUARD_DATA_H

#include "global.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/opponents.h" //to get to battle partner file gbattlepartner stuff
#include "debug.h"

#define SPECIES_SHINY_TAG 500
#define TRAINER_ENCOUNTER_MUSIC(trainer)((gTrainers[trainer].encounterMusic_gender & 0x7F))

#define MAX_TRAINER_AI_FLAGS 64
#define MAX_TRAINER_ITEMS 4
#define MAX_MON_TAGS 32

#define TRAINER_PIC_WIDTH 64
#define TRAINER_PIC_HEIGHT 64
#define TRAINER_PIC_SIZE (TRAINER_PIC_WIDTH * TRAINER_PIC_HEIGHT / 2)

enum {
    BATTLER_AFFINE_NORMAL,
    BATTLER_AFFINE_EMERGE,
    BATTLER_AFFINE_RETURN,
};
struct MonCoords
{
    // This would use a bitfield, but some function
    // uses it as a u8 and casting won't match.
    u8 size; // u8 width:4, height:4;
    u8 y_offset;
};

#define GET_MON_COORDS_WIDTH(size)((size >> 4) * 8)
#define GET_MON_COORDS_HEIGHT(size)((size & 0xF) * 8)

#define UNPACK_STARTING_STATUSES_STRUCT(_enum, _fieldName, _typeMaxValue, ...) INVOKE_WITH_(UNPACK_STARTING_STATUSES_STRUCT_, _fieldName, UNPACK_B(_typeMaxValue));
#define UNPACK_STARTING_STATUSES_STRUCT_(_fieldName, _type, ...) _type FIRST(__VA_OPT__(_fieldName:BIT_SIZE(FIRST(__VA_ARGS__)),) _fieldName)

struct StartingStatuses
{
    STARTING_STATUS_DEFINITIONS(UNPACK_STARTING_STATUSES_STRUCT)
    // Expands to:
    // u32 electricTerrain:1;
    // u32 mistyTerrain:1;
    // u32 grassyTerrain:1;
    // u32 psychicTerrain:1;
    // u32 trickRoom:1;
    // u32 magicRoom:1;
    // u32 wonderRoom:1;
    // u32 tailwindPlayer:1;
    // u32 tailwindOpponent:1;
    // u32 rainbowPlayer:1;
    // u32 rainbowOpponent:1;
    // u32 seaOfFirePlayer:1;
    // u32 seaOfFireOpponent:1;
    // u32 swampPlayer:1;
    // u32 swampOpponent:1;
};

#define SRC_DATA_DEFINES

//extern const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1];
//extern const u8 gSpeciesNamesUpperCase[][POKEMON_NAME_LENGTH + 1];

//extern const u8 gMoveNames[][MOVE_NAME_LENGTH + 1];   //had data file issues think can't use a define for this have to write out number for some reason
//extern const u8 gLowerMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1]; //if I use lowercase moves replace instances of above name w this one
//extern const u8 *const gMoveDescriptionPointers[MOVES_COUNT];
//extern const u8 *const gAbilityDescriptionPointers[ABILITIES_COUNT];
//extern const u8 gAbilityNames[ABILITIES_COUNT][ABILITY_NAME_LENGTH + 1]; //longest ability is 16, 17 w string terminator
extern const u16 gUnknown_8251CB8[];    //lowercase move file is arranged differently so it can prob use array becuase of that
extern const u16 gUnknown_8251FEE[];
extern const u16 gUnknown_8252324[];
extern const u16 gUnknown_82539D4[];


extern const u8 gTrainerClassNames[][13];

//extern const struct MonCoords gMonFrontPicCoords[];
//extern const struct CompressedSpriteSheet gMonFrontPicTable[];
//extern const struct MonCoords gMonBackPicCoords[];
//extern const struct CompressedSpriteSheet gMonBackPicTable[];
//extern const struct SpritePalette gMonPaletteTable[];
//extern const struct SpritePalette gMonShinyPaletteTable[];
extern const union AnimCmd *const *const gTrainerFrontAnimsPtrTable[];
extern const struct MonCoords gTrainerFrontPicCoords[];
extern const struct CompressedSpriteSheet gTrainerFrontPicTable[];
extern const struct SpritePalette gTrainerFrontPicPaletteTable[];
extern const union AnimCmd *const *const gTrainerBackAnimsPtrTable[];
extern const struct MonCoords gTrainerBackPicCoords[];
extern const struct SpritePalette gTrainerBackPicPaletteTable[];

extern const struct CompressedSpriteSheet gSpriteSheet_EnemyShadow;
extern const struct SpriteTemplate gSpriteTemplate_EnemyShadow;

//extern const u8 gEnemyMonElevation[NUM_SPECIES];

//extern const u8 *const gBattleAnims_General[];
//extern const u8 *const gBattleAnims_Special[];

extern const struct OamData gUnknown_824F010;
extern const struct OamData gUnknown_824F018;
extern const union AnimCmd *const gSpriteAnimTable_82349BC[];
extern const union AffineAnimCmd *const gSpriteAffineAnimTable_BattlerPlayer[];
extern const union AffineAnimCmd *const gSpriteAffineAnimTable_BattlerOpponent[];
extern const struct SpriteFrameImage gSpriteImages_BattlerPlayerLeft[];
extern const struct SpriteFrameImage gSpriteImages_BattlerOpponentLeft[];
extern const struct SpriteFrameImage gSpriteImages_BattlerPlayerRight[];
extern const struct SpriteFrameImage gSpriteImages_BattlerOpponentRight[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Red[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Leaf[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Pokedude[];
extern const struct SpriteFrameImage gTrainerBackPicTable_OldMan[];
extern const struct SpriteFrameImage gTrainerBackPicTable_RSBrendan[];
extern const struct SpriteFrameImage gTrainerBackPicTable_RSMay[];

#define TRAINER_PARTY(partyArray) partyArray, .partySize = ARRAY_COUNT(partyArray)


enum TrainerBattleType
{
    TRAINER_BATTLE_TYPE_SINGLES,
    TRAINER_BATTLE_TYPE_DOUBLES,
};


struct Formdata
{
    u16 species;
    u16 FormChangeMoveset[4];
    u16 evs[6];
};//to match what player do potentailly need add ability and evs field
//if change moves reset pp i.e only reset pp if move slot move has changed
//vsonic
//attempt simplify call for form info in trainer party
//unsure how to write this
//think may need to rework trainer party
//will need acount for both form change data
//AND learned abilities
//idea check list if given ability is not within learned
//ability list default to random inate ability


struct TrainerMon
{
    u16 species;
    u16 heldItem;
    u8 abilityNum;
    u8 padding;
    u16 evs[6];
    u8 iv;    
    u8 lvl;    
    u16 moves[4];
    struct Formdata FormInfo;
};

/*struct TrainerMonFormChangeFullCustom
{
    u8 iv;
    u16 evs[6];
    u8 lvl;
    u8 abilityNum;
    u16 species;
    u16 heldItem;
    u16 moves[4];
    struct Formdata FormInfo;
};*/
//need store both form species and form moveset
//think do with an array instead?
//FormChangeMoveSet won't be triggered at battle start
//it'll just be a place I refer to for the moves when it form changes
//mid battle.
//thing I'm unsure of is if I can properly trace the mon placement
//from this?
//idea is if I have identical species etc.
//but mon switch, if I can correctly track
//what moves it would have for form given switching
//check form change logic in EE to see how it knows 
//which to transform but prob only one has mega stone etc.
//and I've removed the need for mega stones...

struct Trainer
{
    /*0x00*/ //u8 partyFlags; //since unifying trainer party struct don't need flags
    /*0x00*/ u8 battleType; //with addition fo triple & rotation change this from bool, to just a constant value to represent each battle type
    /*0x01*/ u8 trainerClass;
    /*0x02*/ u8 encounterMusic_gender; // last bit is gender
    /*0x03*/ u8 trainerPic;
    /*0x04*/ u8 trainerName[12];
             //const u8 *trainerName;  not implemented but idea for space saving from Josh, use to take place of text strings that get reused i.e rematches or same name ex rocket GRUNT
    /*0x10*/ u16 items[4];  //don't use 12 for above, I think?  can make limiter in compount string define
    /*0x1C*/ u64 aiFlags;
    /*0x18*/ u8 padding; //with addition fo triple & rotation change this from bool, to just a constant value to represent each battle type
    /*0x20*/ u8 partySize;
             u8 initialPartysize; //default party size before changes my field
    /*0x24*/ const struct TrainerMon *party;
    struct StartingStatuses startingStatus; // this trainer starts a battle with a given status. see include/constants/battle.h for values
};//unsure what this should be exactly pointer or no?

struct TrainerClass
{
    u8 name[13];
    u8 money;
    u16 ball;
};

extern const struct Trainer gTrainers[];
extern const struct Trainer gBattlePartners[PARTNER_COUNT];
extern const struct TrainerClass gTrainerClasses[TRAINER_CLASS_COUNT];

static inline bool8 IsPartnerTrainerId(u16 trainerId)
{
    if (trainerId >= TRAINER_PARTNER(PARTNER_NONE) && trainerId < TRAINER_PARTNER(PARTNER_COUNT))
        return TRUE;
    return FALSE;
}

static inline u16 SanitizeTrainerId(u16 trainerId)
{
    switch (trainerId)
    {
    case TRAINER_RECORD_MIXING_FRIEND:
    case TRAINER_RECORD_MIXING_APPRENTICE:
    case TRAINER_EREADER:
    case TRAINER_FRONTIER_BRAIN:
    case TRAINER_PLAYER:
    case TRAINER_SECRET_BASE:
    case TRAINER_LINK_OPPONENT:
    case TRAINER_UNION_ROOM:
        return TRAINER_NONE;
    }

    /*assertf(trainerId < TRAINERS_COUNT || IsPartnerTrainerId(trainerId), "invalid trainer: %d", trainerId)
    {
        return TRAINER_NONE;
    }*/

    return trainerId;
}

static inline const struct Trainer *GetTrainerStructFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = 0;
    if (gIsDebugBattle) return GetDebugAiTrainer();
    sanitizedTrainerId = SanitizeTrainerId(trainerId);

    if (IsPartnerTrainerId(trainerId))
        return &gBattlePartners[sanitizedTrainerId - TRAINER_PARTNER(PARTNER_NONE)];
    else
        return &gTrainers[sanitizedTrainerId];
}

static inline const enum TrainerClassID GetTrainerClassFromId(u16 trainerId)
{
    const struct Trainer *trainer = GetTrainerStructFromId(trainerId);

    return trainer->trainerClass;
}

//think not bother with gtrainerClasses
//isn't storing trainer class is meant to hold data
//that would shift based on trainer class
//i.e money recieved from beating them, or is it money lost?
//think money lost is fixed so yeah money gained,
//name of traienr class as well as poke ball that
//class would use
//hmm actually may be good to use,
//class id, class name and class pic are all separate files and arrays rn
//yeah will use, idk what will do with pokeball
//guess leave blank feels like makes more sense to put that
//direclty onto trainer party struct than class
//think my preference would be put on class
//but weight towards trainer party struct
//use default class based ball only if nothing set for mon
//in trainer data
//anyway got sidetracked default uses gTrainerMoneyTable
//EE wraps it all into gtrainerclasses
static inline const u8 *GetTrainerClassNameFromId(u16 trainerId)
{

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
        return gTrainerClasses[gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerClass].name;
    return gTrainerClasses[GetTrainerClassFromId(trainerId)].name;
}

static inline const u8 *GetTrainerNameFromId(u16 trainerId)
{
    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
    {
        return gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName;
    }
    return GetTrainerStructFromId(trainerId)->trainerName;
}

static inline const enum TrainerPicID GetTrainerPicFromId(u16 trainerId)
{

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
        return gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerPic;

    return GetTrainerStructFromId(trainerId)->trainerPic;
}

/*static inline const u8 GetTrainerBackPicFromId(u16 trainerId)
{
    enum DifficultyLevel partnerDifficulty = GetBattlePartnerDifficultyLevel(trainerId);

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
        return gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerBackPic;

    return GetTrainerStructFromId(trainerId)->trainerBackPic;
}
*/
static inline const struct StartingStatuses GetTrainerStartingStatusFromId(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->startingStatus;
}

static inline const enum TrainerBattleType GetTrainerBattleType(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->battleType;
}

static inline const u8 GetTrainerPartySizeFromId(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->partySize;
}

/*static inline const bool32 DoesTrainerHaveMugshot(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->mugshotColor;
}

static inline const u8 GetTrainerMugshotColorFromId(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->mugshotColor;
}*/

static inline const u16 *GetTrainerItemsFromId(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->items;
}

static inline const struct TrainerMon *GetTrainerPartyFromId(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->party;
}

static inline const u64 GetTrainerAIFlagsFromId(u16 trainerId)
{
    return GetTrainerStructFromId(trainerId)->aiFlags;
}

#endif // GUARD_DATA_H
