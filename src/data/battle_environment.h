#include "battle_anim_scripts.h"

const u16 gBattleEnvironmentPalette_Grass[] = INCBIN_U16("graphics/battle/unk_8248400.gbapal");
const u32 gBattleEnvironmentTiles_Grass[] = INCBIN_U32("graphics/battle/unk_824844C.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Grass[] = INCBIN_U32("graphics/battle/Grass_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Grass_Doubles[] = INCBIN_U32("graphics/battle/Grass_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Grass[] = INCBIN_U32("graphics/battle/unk_8248C68.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Grass[] = INCBIN_U32("graphics/battle/unk_8248F58.bin.lz");

const u16 gBattleEnvironmentPalette_LongGrass[] = INCBIN_U16("graphics/battle/unk_8249074.gbapal");
const u32 gBattleEnvironmentTiles_LongGrass[] = INCBIN_U32("graphics/battle/unk_82490C4.4bpp.lz");
const u32 gBattleEnvironmentTilemap_LongGrass[] = INCBIN_U32("graphics/battle/LongGrass_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_LongGrass_Doubles[] = INCBIN_U32("graphics/battle/LongGrass_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_LongGrass[] = INCBIN_U32("graphics/battle/unk_82498DC.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_LongGrass[] = INCBIN_U32("graphics/battle/unk_8249E10.bin.lz");

const u16 gBattleEnvironmentPalette_Sand[] = INCBIN_U16("graphics/battle/unk_8249F98.gbapal");
const u32 gBattleEnvironmentTiles_Sand[] = INCBIN_U32("graphics/battle/unk_8249FE4.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Sand[] = INCBIN_U32("graphics/battle/Sand_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Sand_Doubles[] = INCBIN_U32("graphics/battle/Sand_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Sand[] = INCBIN_U32("graphics/battle/unk_824A618.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Sand[] = INCBIN_U32("graphics/battle/unk_824A844.bin.lz");

const u16 gBattleEnvironmentPalette_Underwater[] = INCBIN_U16("graphics/battle/unk_824A940.gbapal");
const u32 gBattleEnvironmentTiles_Underwater[] = INCBIN_U32("graphics/battle/unk_824A990.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Underwater[] = INCBIN_U32("graphics/battle/Underwater_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Underwater_Doubles[] = INCBIN_U32("graphics/battle/Underwater_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Underwater[] = INCBIN_U32("graphics/battle/unk_824AF70.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Underwater[] = INCBIN_U32("graphics/battle/unk_824B0DC.bin.lz");

const u16 gBattleEnvironmentPalette_Water[] = INCBIN_U16("graphics/battle/unk_824B19C.gbapal");
const u32 gBattleEnvironmentTiles_Water[] = INCBIN_U32("graphics/battle/unk_824B1EC.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Water[] = INCBIN_U32("graphics/battle/Water_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Water_Doubles[] = INCBIN_U32("graphics/battle/Water_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Water[] = INCBIN_U32("graphics/battle/unk_824B8A8.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Water[] = INCBIN_U32("graphics/battle/unk_824BBE0.bin.lz");

const u16 gBattleEnvironmentPalette_Pond[] = INCBIN_U16("graphics/battle/unk_824BCE0.gbapal");
const u32 gBattleEnvironmentTiles_Pond[] = INCBIN_U32("graphics/battle/unk_824BD38.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Pond[] = INCBIN_U32("graphics/battle/Pond_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Pond_Doubles[] = INCBIN_U32("graphics/battle/Pond_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Pond[] = INCBIN_U32("graphics/battle/unk_824C314.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Pond[] = INCBIN_U32("graphics/battle/unk_824C520.bin.lz");

const u16 gBattleEnvironmentPalette_Mountain[] = INCBIN_U16("graphics/battle/unk_824C5D8.gbapal");
const u32 gBattleEnvironmentTiles_Mountain[] = INCBIN_U32("graphics/battle/unk_824C624.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Mountain[] = INCBIN_U32("graphics/battle/Mountain_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Mountain_Doubles[] = INCBIN_U32("graphics/battle/Mountain_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Mountain[] = INCBIN_U32("graphics/battle/unk_824CBF8.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Mountain[] = INCBIN_U32("graphics/battle/unk_824CEC8.bin.lz");

const u16 gBattleEnvironmentPalette_Cave[] = INCBIN_U16("graphics/battle/unk_824CF98.gbapal");
const u32 gBattleEnvironmentTiles_Cave[] = INCBIN_U32("graphics/battle/unk_824CFEC.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Cave[] = INCBIN_U32("graphics/battle/Cave_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Cave_Doubles[] = INCBIN_U32("graphics/battle/Cave_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Cave[] = INCBIN_U32("graphics/battle/unk_824D6B8.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Cave[] = INCBIN_U32("graphics/battle/unk_824DC98.bin.lz");

const u16 gBattleEnvironmentPalette_Building[] = INCBIN_U16("graphics/battle/unk_824DDF0.gbapal");
const u32 gBattleEnvironmentTiles_Building[] = INCBIN_U32("graphics/battle/unk_824DE34.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Building[] = INCBIN_U32("graphics/battle/Building_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Building_Doubles[] = INCBIN_U32("graphics/battle/Building_Terrain_Doubles.bin.lz");

const u32 gBattleEnvironmentAnimTiles_Building[] = INCBIN_U32("graphics/battle/unk_824E410.4bpp.lz");
const u32 gBattleEnvironmentAnimTilemap_Building[] = INCBIN_U32("graphics/battle/unk_824E490.bin.lz");

const u16 gBattleEnvironmentPalette_Link[] = INCBIN_U16("graphics/battle/unk_824E528.gbapal");
const u16 gBattleEnvironmentPalette_Gym[] = INCBIN_U16("graphics/battle/unk_824E56C.gbapal");
const u16 gBattleEnvironmentPalette_Leader[] = INCBIN_U16("graphics/battle/unk_824E5B8.gbapal");
const u16 gBattleEnvironmentPalette_Indoor2[] = INCBIN_U16("graphics/battle/unk_824E604.gbapal");
const u16 gBattleEnvironmentPalette_Indoor1[] = INCBIN_U16("graphics/battle/unk_824E650.gbapal");
const u16 gBattleEnvironmentPalette_Lorelei[] = INCBIN_U16("graphics/battle/unk_824E6A4.gbapal");
const u16 gBattleEnvironmentPalette_Bruno[] = INCBIN_U16("graphics/battle/unk_824E6F0.gbapal");
const u16 gBattleEnvironmentPalette_Agatha[] = INCBIN_U16("graphics/battle/unk_824E740.gbapal");
const u16 gBattleEnvironmentPalette_Lance[] = INCBIN_U16("graphics/battle/unk_824E78C.gbapal");
const u16 gBattleEnvironmentPalette_Champion[] = INCBIN_U16("graphics/battle/unk_824E7DC.gbapal");
const u16 gBattleEnvironmentPalette_Plain[] = INCBIN_U16("graphics/battle/unk_824E81C.gbapal");
const u32 gBattleEnvironmentTiles_Indoor[] = INCBIN_U32("graphics/battle/unk_824E858.4bpp.lz");
const u32 gBattleEnvironmentTilemap_Indoor[] = INCBIN_U32("graphics/battle/Indoor_Terrain.bin.lz");
const u32 gBattleEnvironmentTilemap_Indoor_Doubles[] = INCBIN_U32("graphics/battle/Indoor_Terrain_Doubles.bin.lz");

//file takes values that were in battle_bg.c previously
//need add doubles to this
#define ENVIRONMENT_BACKGROUND(background)                      \
{                                                               \
    .tileset = gBattleEnvironmentTiles_##background,            \
    .tilemap = gBattleEnvironmentTilemap_##background,          \
    .tilemap2 = gBattleEnvironmentTilemap_##background_Doubles, \
    .entryTileset = gBattleEnvironmentAnimTiles_##background,   \
    .entryTilemap = gBattleEnvironmentAnimTilemap_##background, \
    .palette = gBattleEnvironmentPalette_##background,          \
}

#define ENVINRONMENT_TILEMAP_INFO(background)                   \
{                                                               \
    .tilemap = gBattleEnvironmentTilemap_##background,          \
    .tilemap2 = gBattleEnvironmentTilemap_##background_Doubles, \
}

#define DEFAULT_CAMOUFLAGE_BLEND RGB_WHITE

// Cave values. Used for BATTLE_ENVIRONMENT_CAVE as well as BATTLE_ENVIRONMENT_GROUDON and BATTLE_ENVIRONMENT_KYOGRE
#if B_NATURE_POWER_MOVES >= GEN_6
    #define CAVE_NATURE_POWER MOVE_POWER_GEM
#elif B_NATURE_POWER_MOVES >= GEN_4
    #define CAVE_NATURE_POWER MOVE_ROCK_SLIDE
#else
    #define CAVE_NATURE_POWER MOVE_SHADOW_BALL
#endif
#define CAVE_SECRET_POWER_ANIMATION B_SECRET_POWER_ANIMATION >= GEN_4 ? gBattleAnimMove_RockThrow : gBattleAnimMove_Bite
#define CAVE_SECRET_POWER_EFFECT    MOVE_EFFECT_FLINCH
#define CAVE_CAMOUFLAGE_TYPE        TYPE_ROCK
#define CAVE_CAMOUFLAGE_BLEND       RGB(14, 9, 3)
#define CAVE_BATTLE_INTRO_SLIDE     BattleIntroSlide1

// Building values. Used for BATTLE_ENVIRONMENT_BUILDING as well as the environments that come from the vanilla MAP_BATTLE_SCENEs: BATTLE_ENVIRONMENT_PLAIN, BATTLE_ENVIRONMENT_FRONTIER, BATTLE_ENVIRONMENT_GYM, BATTLE_ENVIRONMENT_LEADER, BATTLE_ENVIRONMENT_MAGMA, BATTLE_ENVIRONMENT_AQUA, BATTLE_ENVIRONMENT_SIDNEY, BATTLE_ENVIRONMENT_PHOEBE, BATTLE_ENVIRONMENT_GLACIA, BATTLE_ENVIRONMENT_DRAKE, BATTLE_ENVIRONMENT_CHAMPION
#define BUILDING_NATURE_POWER        B_NATURE_POWER_MOVES >= GEN_4 ? MOVE_TRI_ATTACK : MOVE_SWIFT
#if B_SECRET_POWER_ANIMATION >= GEN_7
    #define BUILDING_SECRET_POWER_ANIMATION gBattleAnimMove_SpitUp
#elif B_SECRET_POWER_ANIMATION >= GEN_4
    #define BUILDING_SECRET_POWER_ANIMATION gBattleAnimMove_BodySlam
#else
    #define BUILDING_SECRET_POWER_ANIMATION gBattleAnimMove_Strength
#endif
#define BUILDING_SECRET_POWER_EFFECT MOVE_EFFECT_PARALYSIS
#define BUILDING_CAMOUFLAGE_TYPE     TYPE_NORMAL
#define BUILDING_CAMOUFLAGE_BLEND    RGB_WHITE
#define BUILDING_BATTLE_INTRO_SLIDE  BattleIntroSlide3

// Plain values. USED for BATTLE_ENVIRONMENT_PLAIN as well as BATTLE_ENVIRONMENT_RAYQUAZA
// (BATTLE_ENVIRONMENT_SKY_PILLAR wasn't introduced until Gen6, so Sky Pillar's roof counts as a Route which uses Plain)
#if B_NATURE_POWER_MOVES >= GEN_6
    #define PLAIN_NATURE_POWER MOVE_TRI_ATTACK
#elif B_NATURE_POWER_MOVES >= GEN_4
    #define PLAIN_NATURE_POWER MOVE_EARTHQUAKE
#else
    #define PLAIN_NATURE_POWER MOVE_SWIFT
#endif
#if B_SECRET_POWER_ANIMATION >= GEN_7
    #define PLAIN_SECRET_POWER_ANIMATION gBattleAnimMove_SpitUp
#elif B_SECRET_POWER_ANIMATION == GEN_6
    #define PLAIN_SECRET_POWER_ANIMATION gBattleAnimMove_BodySlam
#elif B_SECRET_POWER_ANIMATION >= GEN_4
    #define PLAIN_SECRET_POWER_ANIMATION gBattleAnimMove_MudSlap
#else
    #define PLAIN_SECRET_POWER_ANIMATION gBattleAnimMove_Slam
#endif
#define PLAIN_SECRET_POWER_EFFECT (B_SECRET_POWER_EFFECT == GEN_4 || B_SECRET_POWER_EFFECT == GEN_5) ? MOVE_EFFECT_ACC_MINUS_1 : MOVE_EFFECT_PARALYSIS
#define PLAIN_CAMOUFLAGE_TYPE     (B_CAMOUFLAGE_TYPES == GEN_4 || B_CAMOUFLAGE_TYPES == GEN_5) ? TYPE_GROUND : TYPE_NORMAL
#define PLAIN_CAMOUFLAGE_BLEND    RGB_WHITE
#define PLAIN_BATTLE_INTRO_SLIDE  BattleIntroSlide3

//nature power moves are all special now, is 
//special equivalent of secret power
//replaces sBattleTerrainTable need update that for pokemon_debug file
const struct BattleEnvironment gBattleEnvironmentInfo[BATTLE_ENVIRONMENT_COUNT] =
{
    [BATTLE_ENVIRONMENT_GRASS] =
    {
        .name = _("Grass"),
    #if B_NATURE_POWER_MOVES >= GEN_6
        .naturePower = MOVE_ENERGY_BALL,
    #elif B_NATURE_POWER_MOVES >= GEN_4
        .naturePower = MOVE_SEED_BOMB,
    #else
        .naturePower = MOVE_STUN_SPORE,
    #endif
        .secretPowerAnimation = gBattleAnimMove_NeedleArm,
        .secretPowerEffect = MOVE_EFFECT_POISON,
        .camouflageType = TYPE_GRASS,
        .camouflageBlend = RGB(12, 24, 2),
        .background = ENVIRONMENT_BACKGROUND(TallGrass),
        .battleIntroSlide = BattleIntroSlide1,
    },

    [BATTLE_ENVIRONMENT_LONG_GRASS] =
    {
        .name = _("Long Grass"),
    #if B_NATURE_POWER_MOVES >= GEN_6
        .naturePower = MOVE_ENERGY_BALL,
    #elif B_NATURE_POWER_MOVES >= GEN_4
        .naturePower = MOVE_SEED_BOMB,
    #else
        .naturePower = MOVE_RAZOR_LEAF,
    #endif
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_4 ? gBattleAnimMove_NeedleArm : gBattleAnimMove_MagicalLeaf,
        .secretPowerEffect = MOVE_EFFECT_SLEEP,
        .camouflageType = TYPE_GRASS,
        .camouflageBlend = RGB(0, 15, 2),
        .background = ENVIRONMENT_BACKGROUND(LongGrass),
        .battleIntroSlide = BattleIntroSlide1,
    },

    [BATTLE_ENVIRONMENT_SAND] =
    {
        .name = _("Sand"),
        .naturePower = B_NATURE_POWER_MOVES >= GEN_6 ? MOVE_EARTH_POWER : MOVE_EARTHQUAKE,
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_4 ? gBattleAnimMove_MudSlap : gBattleAnimMove_MudShot,
        .secretPowerEffect = MOVE_EFFECT_ACC_MINUS_1,
        .camouflageType = TYPE_GROUND,
        .camouflageBlend = RGB(30, 24, 11),
        .background = ENVIRONMENT_BACKGROUND(Sand),
        .battleIntroSlide = BattleIntroSlide2,
    },

    [BATTLE_ENVIRONMENT_UNDERWATER] =
    {
        .name = _("Underwater"),
        .naturePower = MOVE_HYDRO_PUMP,
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_6 ? gBattleAnimMove_WaterPulse : gBattleAnimMove_Waterfall,
        .secretPowerEffect = B_SECRET_POWER_EFFECT >= GEN_6 ? MOVE_EFFECT_ATK_MINUS_1 : MOVE_EFFECT_DEF_MINUS_1,
        .camouflageType = TYPE_WATER,
        .camouflageBlend = RGB(0, 0, 18),
        .background = ENVIRONMENT_BACKGROUND(Underwater),
        .battleIntroSlide = BattleIntroSlide2,
    },

    [BATTLE_ENVIRONMENT_WATER] =
    {
        .name = _("Water"),
        .naturePower = B_NATURE_POWER_MOVES >= GEN_4 ? MOVE_HYDRO_PUMP : MOVE_SURF,
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_4 ? gBattleAnimMove_WaterPulse : gBattleAnimMove_Surf,
        .secretPowerEffect = MOVE_EFFECT_ATK_MINUS_1,
        .camouflageType = TYPE_WATER,
        .camouflageBlend = RGB(11, 22, 31),
        .background = ENVIRONMENT_BACKGROUND(Water),
        .battleIntroSlide = BattleIntroSlide2,
    },

    [BATTLE_ENVIRONMENT_POND] =
    {
        .name = _("Pond"),
        .naturePower = B_NATURE_POWER_MOVES >= GEN_4 ? MOVE_HYDRO_PUMP : MOVE_BUBBLE_BEAM,
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_4 ? gBattleAnimMove_WaterPulse : gBattleAnimMove_BubbleBeam,
        .secretPowerEffect = B_SECRET_POWER_EFFECT >= GEN_4 ? MOVE_EFFECT_ATK_MINUS_1 : MOVE_EFFECT_SPD_MINUS_1,
        .camouflageType = TYPE_WATER,
        .camouflageBlend = RGB(11, 22, 31),
        .background = ENVIRONMENT_BACKGROUND(PondWater),
        .battleIntroSlide = BattleIntroSlide1,
    },

    [BATTLE_ENVIRONMENT_MOUNTAIN] =
    {
        .name = _("Mountain"),
    #if B_NATURE_POWER_MOVES >= GEN_6
        .naturePower = MOVE_EARTH_POWER,
    #elif B_NATURE_POWER_MOVES >= GEN_5
        .naturePower = MOVE_EARTHQUAKE,
    #else
        .naturePower = MOVE_ROCK_SLIDE,
    #endif
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_5 ? gBattleAnimMove_MudSlap : gBattleAnimMove_RockThrow,
    #if B_SECRET_POWER_EFFECT >= GEN_5
        .secretPowerEffect = MOVE_EFFECT_ACC_MINUS_1,
    #elif B_SECRET_POWER_EFFECT == GEN_4
        .secretPowerEffect = MOVE_EFFECT_FLINCH,
    #else
        .secretPowerEffect = MOVE_EFFECT_CONFUSION,
    #endif
        .camouflageType = B_CAMOUFLAGE_TYPES >= GEN_5 ? TYPE_GROUND : TYPE_ROCK,
        .camouflageBlend = RGB(22, 16, 10),
        .background = ENVIRONMENT_BACKGROUND(Rock),
        .battleIntroSlide = BattleIntroSlide1,
    },

    [BATTLE_ENVIRONMENT_CAVE] =
    {
        .name = _("Cave"),
        .naturePower = CAVE_NATURE_POWER,
        .secretPowerAnimation = CAVE_SECRET_POWER_ANIMATION,
        .secretPowerEffect = CAVE_SECRET_POWER_EFFECT,
        .camouflageType = CAVE_CAMOUFLAGE_TYPE,
        .camouflageBlend = CAVE_CAMOUFLAGE_BLEND,
        .background = ENVIRONMENT_BACKGROUND(Cave),
        .battleIntroSlide = CAVE_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_BUILDING] =
    {
        .name = _("Building"),
        .naturePower = BUILDING_NATURE_POWER,
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background = ENVIRONMENT_BACKGROUND(Building),
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_PLAIN] =
    {
        .name = _("Plain"),
        .naturePower = PLAIN_NATURE_POWER,
        .secretPowerAnimation = PLAIN_SECRET_POWER_ANIMATION,
        .secretPowerEffect = PLAIN_SECRET_POWER_EFFECT,
        .camouflageType = PLAIN_CAMOUFLAGE_TYPE,
        .camouflageBlend = PLAIN_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Building,
            ENVINRONMENT_TILEMAP_INFO(Building),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Plain,
        },
        .battleIntroSlide = PLAIN_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_LINK] =
    {
        .name = _("Link"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Building,
            ENVINRONMENT_TILEMAP_INFO(Building),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Link,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_GYM] =
    {
        .name = _("Gym"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Building,
            ENVINRONMENT_TILEMAP_INFO(Building),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Gym,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_LEADER] =
    {
        .name = _("Leader"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Building,
            ENVINRONMENT_TILEMAP_INFO(Building),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Leader,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_INDOOR_2] =
    {
        .name = _("Indoor 2"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Indoor2,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_INDOOR_1] =
    {
        .name = _("Indoor 1"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Indoor1,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_LORELEI] =
    {
        .name = _("Lorelei"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Lorelei,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_BRUNO] =
    {
        .name = _("Bruno"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Bruno,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_AGATHA] =
    {
        .name = _("Agatha"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Agatha,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_LANCE] =
    {
        .name = _("Lance"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Lance,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_CHAMPION] =
    {
        .name = _("Champion"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Indoor,
            ENVINRONMENT_TILEMAP_INFO(Indoor),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Champion,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    
    [BATTLE_ENVIRONMENT_FRONTIER] =
    {
        .name = _("Frontier"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Building,
            .tilemap = ENVINRONMENT_TILEMAP_INFO(Building),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_Frontier,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_MAGMA] =
    {
        .name = _("Magma"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumMagma,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_AQUA] =
    {
        .name = _("Aqua"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumAqua,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_SIDNEY] =
    {
        .name = _("Sidney"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumSidney,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_PHOEBE] =
    {
        .name = _("Phoebe"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumPhoebe,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_GLACIA] =
    {
        .name = _("Glacia"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumGlacia,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_DRAKE] =
    {
        .name = _("Drake"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumDrake,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_CHAMPION_EM] =
    {
        .name = _("Champion"),
        .secretPowerAnimation = BUILDING_SECRET_POWER_ANIMATION,
        .secretPowerEffect = BUILDING_SECRET_POWER_EFFECT,
        .camouflageType = BUILDING_CAMOUFLAGE_TYPE,
        .camouflageBlend = BUILDING_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Stadium,
            ENVINRONMENT_TILEMAP_INFO(Stadium),
            .entryTileset = gBattleEnvironmentAnimTiles_Building,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Building,
            .palette = gBattleEnvironmentPalette_StadiumWallace,
        },
        .battleIntroSlide = BUILDING_BATTLE_INTRO_SLIDE,
    },//nieghtmare lower offenses

    [BATTLE_ENVIRONMENT_GROUDON] =
    {
        .name = _("Groudon"),
        .naturePower = CAVE_NATURE_POWER,
        .secretPowerAnimation = CAVE_SECRET_POWER_ANIMATION,
        .secretPowerEffect = CAVE_SECRET_POWER_EFFECT,
        .camouflageType = CAVE_CAMOUFLAGE_TYPE,
        .camouflageBlend = CAVE_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Cave,
            ENVINRONMENT_TILEMAP_INFO(Cave),
            .entryTileset = gBattleEnvironmentAnimTiles_Cave,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Cave,
            .palette = gBattleEnvironmentPalette_Groudon,
        },
        .battleIntroSlide = CAVE_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_KYOGRE] =
    {
        .name = _("Kyogre"),
        .naturePower = CAVE_NATURE_POWER,
        .secretPowerAnimation = CAVE_SECRET_POWER_ANIMATION,
        .secretPowerEffect = CAVE_SECRET_POWER_EFFECT,
        .camouflageType = CAVE_CAMOUFLAGE_TYPE,
        .camouflageBlend = CAVE_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Water,
            ENVINRONMENT_TILEMAP_INFO(Water),
            .entryTileset = gBattleEnvironmentAnimTiles_Underwater,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Underwater,
            .palette = gBattleEnvironmentPalette_Kyogre,
        },
        .battleIntroSlide = CAVE_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_RAYQUAZA] =
    {
        .name = _("Rayquaza"),
        .naturePower = PLAIN_NATURE_POWER,
        .secretPowerAnimation = PLAIN_SECRET_POWER_ANIMATION,
        .secretPowerEffect = PLAIN_SECRET_POWER_EFFECT,
        .camouflageType = PLAIN_CAMOUFLAGE_TYPE,
        .camouflageBlend = PLAIN_CAMOUFLAGE_BLEND,
        .background =
        {
            .tileset = gBattleEnvironmentTiles_Rayquaza,
            ENVINRONMENT_TILEMAP_INFO(Rayquaza),
            .entryTileset = gBattleEnvironmentAnimTiles_Rayquaza,
            .entryTilemap = gBattleEnvironmentAnimTilemap_Rayquaza,
            .palette = gBattleEnvironmentPalette_Rayquaza,
        },
        .battleIntroSlide = PLAIN_BATTLE_INTRO_SLIDE,
    },

    [BATTLE_ENVIRONMENT_SOARING] =
    {
        .name = _("Soaring"),
        .naturePower = MOVE_AIR_SLASH,
        .secretPowerAnimation = gBattleAnimMove_Gust,
        .secretPowerEffect = MOVE_EFFECT_SPD_MINUS_1,
        .camouflageType = TYPE_FLYING,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_SKY_PILLAR] =
    {
        .name = _("Sky Pillar"),
        .naturePower = MOVE_AIR_SLASH,
        .secretPowerAnimation = gBattleAnimMove_Gust,
        .secretPowerEffect = MOVE_EFFECT_SPD_MINUS_1,
        .camouflageType = TYPE_FLYING,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_BURIAL_GROUND] =
    {
        .name = _("Burial Ground"),
        .naturePower = MOVE_SHADOW_BALL,
        .secretPowerAnimation = gBattleAnimMove_ShadowSneak,
        .secretPowerEffect = MOVE_EFFECT_FLINCH,
        .camouflageType = TYPE_GHOST,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_PUDDLE] =
    {
        .name = _("Puddle"),
        .naturePower = MOVE_MUD_BOMB,
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_5 ? gBattleAnimMove_MudShot : gBattleAnimMove_MudSlap,
        .secretPowerEffect = B_SECRET_POWER_EFFECT >= GEN_5 ? MOVE_EFFECT_SPD_MINUS_1 : MOVE_EFFECT_ACC_MINUS_1,
        .camouflageType = TYPE_GROUND,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_MARSH] =
    {
        .name = _("Marsh"),
        .naturePower = MOVE_MUD_BOMB,
        .secretPowerAnimation = gBattleAnimMove_MudShot,
        .secretPowerEffect = MOVE_EFFECT_SPD_MINUS_1,
        .camouflageType = TYPE_GROUND,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_SWAMP] =
    {
        .name = _("Swamp"),
        .naturePower = MOVE_MUD_BOMB,
        .secretPowerAnimation = gBattleAnimMove_MudShot,
        .secretPowerEffect = MOVE_EFFECT_SPD_MINUS_1,
        .camouflageType = TYPE_GROUND,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_SNOW] =
    {
        .name = _("Snow"),
    #if B_NATURE_POWER_MOVES >= GEN_7
        .naturePower = MOVE_ICE_BEAM,
    #elif B_NATURE_POWER_MOVES == GEN_6
        .naturePower = MOVE_FROST_BREATH,
    #else
        .naturePower = MOVE_BLIZZARD,
    #endif
        .secretPowerAnimation = B_SECRET_POWER_ANIMATION >= GEN_7 ? gBattleAnimMove_IceShard : gBattleAnimMove_Avalanche,
        .secretPowerEffect = MOVE_EFFECT_FREEZE,
        .camouflageType = TYPE_ICE,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },//unsure what want nature power to be
    //blizzard would be better since terrain would alsmot
    //always be in a place that's snowing/hail
    //depends on how good I want nature power to be

    [BATTLE_ENVIRONMENT_ICE] =
    {
        .name = _("Ice"),
        .naturePower = MOVE_ICE_BEAM,
        .secretPowerAnimation = gBattleAnimMove_IceShard,
        .secretPowerEffect = MOVE_EFFECT_FREEZE,
        .camouflageType = TYPE_ICE,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_VOLCANO] =
    {
        .name = _("Volcano"),
        .naturePower = MOVE_LAVA_PLUME,
        .secretPowerAnimation = gBattleAnimMove_Incinerate,
        .secretPowerEffect = MOVE_EFFECT_BURN,
        .camouflageType = TYPE_FIRE,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_DISTORTION_WORLD] =
    {
        .name = _("Distortion World"),
        .naturePower = MOVE_TRI_ATTACK,
        .secretPowerAnimation = gBattleAnimMove_Pound,
        .secretPowerEffect = MOVE_EFFECT_PARALYSIS,
        .camouflageType = TYPE_NORMAL,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_SPACE] =
    {
        .name = _("Space"),
        .naturePower = MOVE_DRACO_METEOR,
        .secretPowerAnimation = gBattleAnimMove_Swift,
        .secretPowerEffect = MOVE_EFFECT_FLINCH,
        .camouflageType = TYPE_DRAGON,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },

    [BATTLE_ENVIRONMENT_ULTRA_SPACE] =
    {
        .name = _("Ultra Space"),
        .naturePower = MOVE_PSYSHOCK,
        .secretPowerAnimation = gBattleAnimMove_Psywave,
        .secretPowerEffect = MOVE_EFFECT_DEF_MINUS_1,
        .camouflageType = TYPE_PSYCHIC,
        .camouflageBlend = DEFAULT_CAMOUFLAGE_BLEND,
    },
};

static const struct {
    u8 mapScene;
    u8 battleEnvironment;
} sMapBattleSceneMapping[] = {
    {MAP_BATTLE_SCENE_GYM,      BATTLE_ENVIRONMENT_GYM},
    {MAP_BATTLE_SCENE_INDOOR_1, BATTLE_ENVIRONMENT_INDOOR_1},
    {MAP_BATTLE_SCENE_INDOOR_2, BATTLE_ENVIRONMENT_INDOOR_2},
    {MAP_BATTLE_SCENE_LORELEI,  BATTLE_ENVIRONMENT_LORELEI},
    {MAP_BATTLE_SCENE_BRUNO,    BATTLE_ENVIRONMENT_BRUNO},
    {MAP_BATTLE_SCENE_AGATHA,   BATTLE_ENVIRONMENT_AGATHA},
    {MAP_BATTLE_SCENE_LANCE,    BATTLE_ENVIRONMENT_LANCE},
    {MAP_BATTLE_SCENE_LINK,     BATTLE_ENVIRONMENT_LINK}
};