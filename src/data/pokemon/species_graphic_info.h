
#define FRONT_PIC(sprite)                    \
        .frontPic = gMonFrontPic_## sprite,                 \
        .frontPicSize = 0x800

#define FRONT_PIC_FEMALE(sprite, width, height)             \
        .frontPicFemale = gMonFrontPic_## sprite##F,        \
        .frontPicSizeFemale = MON_COORDS_SIZE(width, height)

#define BACK_PIC(sprite)                     \
        .backPic = gMonBackPic_## sprite,                   \
        .backPicSize = 0x800

#define FRONT_COORD(size, y_offset)                    \
        .frontCoordSize = size,                 \
        .frontPicYOffset = y_offset

#define BACK_COORD(size, y_offset)                    \
        .backCoordSize = size,                 \
        .backPicYOffset = y_offset

#define TAG(species)    \
        .tag = species

#define PIC_DATA_ICON_INDEX(sprite, palId) \
        .frontPic = gMonFrontPic_## sprite,                 \
        .backPic = gMonBackPic_## sprite,                   \
        .palette = gMonPalette_## sprite,                      \
        .shinyPalette = gMonShinyPalette_## sprite,      \
        .iconSprite = gMonIcon_## sprite,                   \
        .iconPalIndex = palId



#define PALETTES(pal)                                       \
        .palette = gMonPalette_## pal,                      \
        .shinyPalette = gMonShinyPalette_## pal


#define ICON(sprite, palId)                                 \
        .iconSprite = gMonIcon_## sprite,                   \
        .iconPalIndex = palId


//looked at EE setup don't need 0x800 part?
//in that case can prob consolidate most fields
//don't need tag
//can put front pic back pic and both pals in one macro
//then just have one for front/back coords and the icon
//well leave palette separete things like alcremie can have
//diff names for pic palette

//most are same so can make macro but use other ones if need break apart
//or just right out values

//if works checked emerald and won't need to list all teh graphics in 
//externs for them to work, can just pull directly from table here

//tag equals species constant
//can put that in functinon rather than needing to put in table
//use get tag and have it just set to species
const struct SpeciesGraphicInfo gSpeciesGraphics[] =
{
[SPECIES_NONE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //QuestionMark, 
[SPECIES_BULBASAUR] = 
    {  
      //PIC_DATA(Bulbasaur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bulbasaur),
      BACK_COORD(0x88,0),
      //PALETTES(Bulbasaur),
      PIC_DATA_ICON_INDEX(Bulbasaur,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bulbasaur,
[SPECIES_IVYSAUR] = 
    {  
      //PIC_DATA(Ivysaur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ivysaur),
      BACK_COORD(0x88,0),
      //PALETTES(Ivysaur),
      PIC_DATA_ICON_INDEX(Ivysaur,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ivysaur,
[SPECIES_VENUSAUR] = 
    {  
      //PIC_DATA(Venusaur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Venusaur),
      BACK_COORD(0x88,0),
      //PALETTES(Venusaur),
      PIC_DATA_ICON_INDEX(Venusaur,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Venusaur,
[SPECIES_CHARMANDER] = 
    {  
      //PIC_DATA(Charmander),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charmander),
      BACK_COORD(0x88,0),
      //PALETTES(Charmander),
      PIC_DATA_ICON_INDEX(Charmander,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Charmander,
[SPECIES_CHARMELEON] = 
    {  
      //PIC_DATA(Charmeleon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charmeleon),
      BACK_COORD(0x88,0),
      //PALETTES(Charmeleon),
      PIC_DATA_ICON_INDEX(Charmeleon,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Charmeleon,
[SPECIES_CHARIZARD] = 
    {  
      //PIC_DATA(Charizard),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charizard),
      BACK_COORD(0x88,0),
      //PALETTES(Charizard),
      PIC_DATA_ICON_INDEX(Charizard,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Charizard,
[SPECIES_SQUIRTLE] = 
    {  
      //PIC_DATA(Squirtle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Squirtle),
      BACK_COORD(0x88,0),
      //PALETTES(Squirtle),
      PIC_DATA_ICON_INDEX(Squirtle,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Squirtle,
[SPECIES_WARTORTLE] = 
    {  
      //PIC_DATA(Wartortle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wartortle),
      BACK_COORD(0x88,0),
      //PALETTES(Wartortle),
      PIC_DATA_ICON_INDEX(Wartortle,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wartortle,
[SPECIES_BLASTOISE] = 
    {  
      //PIC_DATA(Blastoise),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blastoise),
      BACK_COORD(0x88,0),
      //PALETTES(Blastoise),
      PIC_DATA_ICON_INDEX(Blastoise,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Blastoise,
[SPECIES_CATERPIE] = 
    {  
      //PIC_DATA(Caterpie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Caterpie),
      BACK_COORD(0x88,0),
      //PALETTES(Caterpie),
      PIC_DATA_ICON_INDEX(Caterpie,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Caterpie,
[SPECIES_METAPOD] = 
    {  
      //PIC_DATA(Metapod),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Metapod),
      BACK_COORD(0x88,0),
      //PALETTES(Metapod),
      PIC_DATA_ICON_INDEX(Metapod,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Metapod,
[SPECIES_BUTTERFREE] = 
    {  
      //PIC_DATA(Butterfree),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Butterfree),
      BACK_COORD(0x88,0),
      //PALETTES(Butterfree),
      PIC_DATA_ICON_INDEX(Butterfree,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Butterfree,
[SPECIES_WEEDLE] = 
    {  
      //PIC_DATA(Weedle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Weedle),
      BACK_COORD(0x88,0),
      //PALETTES(Weedle),
      PIC_DATA_ICON_INDEX(Weedle,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Weedle,
[SPECIES_KAKUNA] = 
    {  
      //PIC_DATA(Kakuna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kakuna),
      BACK_COORD(0x88,0),
      //PALETTES(Kakuna),
      PIC_DATA_ICON_INDEX(Kakuna,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kakuna,
[SPECIES_BEEDRILL] = 
    {  
      //PIC_DATA(Beedrill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Beedrill),
      BACK_COORD(0x88,0),
      //PALETTES(Beedrill),
      PIC_DATA_ICON_INDEX(Beedrill,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Beedrill,
[SPECIES_PIDGEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pidgey,
[SPECIES_PIDGEOTTO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pidgeotto,
[SPECIES_PIDGEOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pidgeot,
[SPECIES_RATTATA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rattata,
[SPECIES_RATICATE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Raticate,
[SPECIES_SPEAROW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spearow,
[SPECIES_FEAROW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Fearow,
[SPECIES_EKANS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ekans,
[SPECIES_ARBOK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arbok,
[SPECIES_PIKACHU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pikachu,
[SPECIES_RAICHU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Raichu,
[SPECIES_SANDSHREW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sandshrew,
[SPECIES_SANDSLASH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sandslash,
[SPECIES_NIDORAN_F] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //NidoranF,
[SPECIES_NIDORINA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nidorina,
[SPECIES_NIDOQUEEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nidoqueen,
[SPECIES_NIDORAN_M] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //NidoranM,
[SPECIES_NIDORINO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nidorino,
[SPECIES_NIDOKING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nidoking,
[SPECIES_CLEFAIRY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Clefairy,
[SPECIES_CLEFABLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Clefable,
[SPECIES_VULPIX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vulpix,
[SPECIES_NINETALES] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ninetales,
[SPECIES_JIGGLYPUFF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jigglypuff,
[SPECIES_WIGGLYTUFF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wigglytuff,
[SPECIES_ZUBAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zubat,
[SPECIES_GOLBAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Golbat,
[SPECIES_ODDISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Oddish,
[SPECIES_GLOOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gloom,
[SPECIES_VILEPLUME] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vileplume,
[SPECIES_PARAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Paras,
[SPECIES_PARASECT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Parasect,
[SPECIES_VENONAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Venonat,
[SPECIES_VENOMOTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Venomoth,
[SPECIES_DIGLETT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Diglett,
[SPECIES_DUGTRIO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dugtrio,
[SPECIES_MEOWTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meowth,
[SPECIES_PERSIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Persian,
[SPECIES_PSYDUCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Psyduck,
[SPECIES_GOLDUCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Golduck,
[SPECIES_MANKEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mankey,
[SPECIES_PRIMEAPE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Primeape,
[SPECIES_GROWLITHE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Growlithe,
[SPECIES_ARCANINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arcanine,
[SPECIES_POLIWAG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Poliwag,
[SPECIES_POLIWHIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Poliwhirl,
[SPECIES_POLIWRATH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Poliwrath,
[SPECIES_ABRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Abra,
[SPECIES_KADABRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kadabra,
[SPECIES_ALAKAZAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Alakazam,
[SPECIES_MACHOP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Machop,
[SPECIES_MACHOKE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Machoke,
[SPECIES_MACHAMP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Machamp,
[SPECIES_BELLSPROUT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bellsprout,
[SPECIES_WEEPINBELL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Weepinbell,
[SPECIES_VICTREEBEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Victreebel,
[SPECIES_TENTACOOL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tentacool,
[SPECIES_TENTACRUEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tentacruel,
[SPECIES_GEODUDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Geodude,
[SPECIES_GRAVELER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Graveler,
[SPECIES_GOLEM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Golem,
[SPECIES_PONYTA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ponyta,
[SPECIES_RAPIDASH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rapidash,
[SPECIES_SLOWPOKE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slowpoke,
[SPECIES_SLOWBRO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slowbro,
[SPECIES_MAGNEMITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magnemite,
[SPECIES_MAGNETON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magneton,
[SPECIES_FARFETCHD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Farfetchd,
[SPECIES_DODUO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Doduo,
[SPECIES_DODRIO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dodrio,
[SPECIES_SEEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Seel,
[SPECIES_DEWGONG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dewgong,
[SPECIES_GRIMER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grimer,
[SPECIES_MUK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Muk,
[SPECIES_SHELLDER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shellder,
[SPECIES_CLOYSTER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cloyster,
[SPECIES_GASTLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gastly,
[SPECIES_HAUNTER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Haunter,
[SPECIES_GENGAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gengar,
[SPECIES_ONIX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Onix,
[SPECIES_DROWZEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drowzee,
[SPECIES_HYPNO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hypno,
[SPECIES_KRABBY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Krabby,
[SPECIES_KINGLER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kingler,
[SPECIES_VOLTORB] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Voltorb,
[SPECIES_ELECTRODE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Electrode,
[SPECIES_EXEGGCUTE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Exeggcute,
[SPECIES_EXEGGUTOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Exeggutor,
[SPECIES_CUBONE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cubone,
[SPECIES_MAROWAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Marowak,
[SPECIES_HITMONLEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hitmonlee,
[SPECIES_HITMONCHAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hitmonchan,
[SPECIES_LICKITUNG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lickitung,
[SPECIES_KOFFING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Koffing,
[SPECIES_WEEZING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Weezing,
[SPECIES_RHYHORN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rhyhorn,
[SPECIES_RHYDON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rhydon,
[SPECIES_CHANSEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chansey,
[SPECIES_TANGELA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tangela,
[SPECIES_KANGASKHAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kangaskhan,
[SPECIES_HORSEA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Horsea,
[SPECIES_SEADRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Seadra,
[SPECIES_GOLDEEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Goldeen,
[SPECIES_SEAKING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Seaking,
[SPECIES_STARYU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Staryu,
[SPECIES_STARMIE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Starmie,
[SPECIES_MR_MIME] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MrMime,
[SPECIES_SCYTHER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scyther,
[SPECIES_JYNX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jynx,
[SPECIES_ELECTABUZZ] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Electabuzz,
[SPECIES_MAGMAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magmar,
[SPECIES_PINSIR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pinsir,
[SPECIES_TAUROS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tauros,
[SPECIES_MAGIKARP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magikarp,
[SPECIES_GYARADOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gyarados,
[SPECIES_LAPRAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lapras,
[SPECIES_DITTO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ditto,
[SPECIES_EEVEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eevee,
[SPECIES_VAPOREON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vaporeon,
[SPECIES_JOLTEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jolteon,
[SPECIES_FLAREON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Flareon,
[SPECIES_PORYGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Porygon,
[SPECIES_OMANYTE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Omanyte,
[SPECIES_OMASTAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Omastar,
[SPECIES_KABUTO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kabuto,
[SPECIES_KABUTOPS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kabutops,
[SPECIES_AERODACTYL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aerodactyl,
[SPECIES_SNORLAX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Snorlax,
[SPECIES_ARTICUNO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Articuno,
[SPECIES_ZAPDOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zapdos,
[SPECIES_MOLTRES] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Moltres,
[SPECIES_DRATINI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dratini,
[SPECIES_DRAGONAIR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dragonair,
[SPECIES_DRAGONITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dragonite,
[SPECIES_MEWTWO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mewtwo,
[SPECIES_MEW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mew,
[SPECIES_CHIKORITA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chikorita,
[SPECIES_BAYLEEF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bayleef,
[SPECIES_MEGANIUM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meganium,
[SPECIES_CYNDAQUIL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cyndaquil,
[SPECIES_QUILAVA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Quilava,
[SPECIES_TYPHLOSION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Typhlosion,
[SPECIES_TOTODILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Totodile,
[SPECIES_CROCONAW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Croconaw,
[SPECIES_FERALIGATOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Feraligatr,
[SPECIES_SENTRET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sentret,
[SPECIES_FURRET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Furret,
[SPECIES_HOOTHOOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hoothoot,
[SPECIES_NOCTOWL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Noctowl,
[SPECIES_LEDYBA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ledyba,
[SPECIES_LEDIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ledian,
[SPECIES_SPINARAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spinarak,
[SPECIES_ARIADOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ariados,
[SPECIES_CROBAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Crobat,
[SPECIES_CHINCHOU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chinchou,
[SPECIES_LANTURN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lanturn,
[SPECIES_PICHU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pichu,
[SPECIES_CLEFFA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cleffa,
[SPECIES_IGGLYBUFF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Igglybuff,
[SPECIES_TOGEPI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Togepi,
[SPECIES_TOGETIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Togetic,
[SPECIES_NATU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Natu,
[SPECIES_XATU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Xatu,
[SPECIES_MAREEP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mareep,
[SPECIES_FLAAFFY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Flaaffy,
[SPECIES_AMPHAROS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ampharos,
[SPECIES_BELLOSSOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bellossom,
[SPECIES_MARILL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Marill,
[SPECIES_AZUMARILL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Azumarill,
[SPECIES_SUDOWOODO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sudowoodo,
[SPECIES_POLITOED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Politoed,
[SPECIES_HOPPIP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hoppip,
[SPECIES_SKIPLOOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skiploom,
[SPECIES_JUMPLUFF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jumpluff,
[SPECIES_AIPOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aipom,
[SPECIES_SUNKERN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sunkern,
[SPECIES_SUNFLORA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sunflora,
[SPECIES_YANMA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Yanma,
[SPECIES_WOOPER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wooper,
[SPECIES_QUAGSIRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Quagsire,
[SPECIES_ESPEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Espeon,
[SPECIES_UMBREON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Umbreon,
[SPECIES_MURKROW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Murkrow,
[SPECIES_SLOWKING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slowking,
[SPECIES_MISDREAVUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Misdreavus,
[SPECIES_UNOWN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Unown,
[SPECIES_WOBBUFFET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wobbuffet,
[SPECIES_GIRAFARIG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Girafarig,
[SPECIES_PINECO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pineco,
[SPECIES_FORRETRESS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Forretress,
[SPECIES_DUNSPARCE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dunsparce,
[SPECIES_GLIGAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gligar,
[SPECIES_STEELIX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Steelix,
[SPECIES_SNUBBULL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Snubbull,
[SPECIES_GRANBULL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Granbull,
[SPECIES_QWILFISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Qwilfish,
[SPECIES_SCIZOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scizor,
[SPECIES_SHUCKLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shuckle,
[SPECIES_HERACROSS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Heracross,
[SPECIES_SNEASEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sneasel,
[SPECIES_TEDDIURSA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Teddiursa,
[SPECIES_URSARING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ursaring,
[SPECIES_SLUGMA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slugma,
[SPECIES_MAGCARGO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magcargo,
[SPECIES_SWINUB] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swinub,
[SPECIES_PILOSWINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Piloswine,
[SPECIES_CORSOLA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Corsola,
[SPECIES_REMORAID] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Remoraid,
[SPECIES_OCTILLERY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Octillery,
[SPECIES_DELIBIRD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Delibird,
[SPECIES_MANTINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mantine,
[SPECIES_SKARMORY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skarmory,
[SPECIES_HOUNDOUR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Houndour,
[SPECIES_HOUNDOOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Houndoom,
[SPECIES_KINGDRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kingdra,
[SPECIES_PHANPY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Phanpy,
[SPECIES_DONPHAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Donphan,
[SPECIES_PORYGON2] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Porygon2,
[SPECIES_STANTLER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stantler,
[SPECIES_SMEARGLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Smeargle,
[SPECIES_TYROGUE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tyrogue,
[SPECIES_HITMONTOP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hitmontop,
[SPECIES_SMOOCHUM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Smoochum,
[SPECIES_ELEKID] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Elekid,
[SPECIES_MAGBY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magby,
[SPECIES_MILTANK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Miltank,
[SPECIES_BLISSEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Blissey,
[SPECIES_RAIKOU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Raikou,
[SPECIES_ENTEI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Entei,
[SPECIES_SUICUNE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Suicune,
[SPECIES_LARVITAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Larvitar,
[SPECIES_PUPITAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pupitar,
[SPECIES_TYRANITAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tyranitar,
[SPECIES_LUGIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lugia,
[SPECIES_HO_OH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //HoOh,
[SPECIES_CELEBI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Celebi,
    
[SPECIES_TREECKO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Treecko,
[SPECIES_GROVYLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grovyle,
[SPECIES_SCEPTILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sceptile,
[SPECIES_TORCHIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Torchic,
[SPECIES_COMBUSKEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Combusken,
[SPECIES_BLAZIKEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Blaziken,
[SPECIES_MUDKIP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mudkip,
[SPECIES_MARSHTOMP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Marshtomp,
[SPECIES_SWAMPERT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swampert,
[SPECIES_POOCHYENA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Poochyena,
[SPECIES_MIGHTYENA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mightyena,
[SPECIES_ZIGZAGOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zigzagoon,
[SPECIES_LINOONE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Linoone,
[SPECIES_WURMPLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wurmple,
[SPECIES_SILCOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silcoon,
[SPECIES_BEAUTIFLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Beautifly,
[SPECIES_CASCOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cascoon,
[SPECIES_DUSTOX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dustox,
[SPECIES_LOTAD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lotad,
[SPECIES_LOMBRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lombre,
[SPECIES_LUDICOLO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ludicolo,
[SPECIES_SEEDOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Seedot,
[SPECIES_NUZLEAF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nuzleaf,
[SPECIES_SHIFTRY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shiftry,
[SPECIES_NINCADA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nincada,
[SPECIES_NINJASK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ninjask,
[SPECIES_SHEDINJA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shedinja,
[SPECIES_TAILLOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Taillow,
[SPECIES_SWELLOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swellow,
[SPECIES_SHROOMISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shroomish,
[SPECIES_BRELOOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Breloom,
[SPECIES_SPINDA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spinda,
[SPECIES_WINGULL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wingull,
[SPECIES_PELIPPER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pelipper,
[SPECIES_SURSKIT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Surskit,
[SPECIES_MASQUERAIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Masquerain,
[SPECIES_WAILMER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wailmer,
[SPECIES_WAILORD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wailord,
[SPECIES_SKITTY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skitty,
[SPECIES_DELCATTY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Delcatty,
[SPECIES_KECLEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kecleon,
[SPECIES_BALTOY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Baltoy,
[SPECIES_CLAYDOL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Claydol,
[SPECIES_NOSEPASS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nosepass,
[SPECIES_TORKOAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Torkoal,
[SPECIES_SABLEYE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sableye,
[SPECIES_BARBOACH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Barboach,
[SPECIES_WHISCASH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Whiscash,
[SPECIES_LUVDISC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Luvdisc,
[SPECIES_CORPHISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Corphish,
[SPECIES_CRAWDAUNT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Crawdaunt,
[SPECIES_FEEBAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Feebas,
[SPECIES_MILOTIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Milotic,
[SPECIES_CARVANHA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Carvanha,
[SPECIES_SHARPEDO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sharpedo,
[SPECIES_TRAPINCH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Trapinch,
[SPECIES_VIBRAVA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vibrava,
[SPECIES_FLYGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Flygon,
[SPECIES_MAKUHITA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Makuhita,
[SPECIES_HARIYAMA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hariyama,
[SPECIES_ELECTRIKE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Electrike,
[SPECIES_MANECTRIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Manectric,
[SPECIES_NUMEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Numel,
[SPECIES_CAMERUPT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Camerupt,
[SPECIES_SPHEAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spheal,
[SPECIES_SEALEO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sealeo,
[SPECIES_WALREIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Walrein,
[SPECIES_CACNEA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cacnea,
[SPECIES_CACTURNE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cacturne,
[SPECIES_SNORUNT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Snorunt,
[SPECIES_GLALIE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Glalie,
[SPECIES_LUNATONE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lunatone,
[SPECIES_SOLROCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Solrock,
[SPECIES_AZURILL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Azurill,
[SPECIES_SPOINK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spoink,
[SPECIES_GRUMPIG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grumpig,
[SPECIES_PLUSLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Plusle,
[SPECIES_MINUN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minun,
[SPECIES_MAWILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mawile,
[SPECIES_MEDITITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meditite,
[SPECIES_MEDICHAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Medicham,
[SPECIES_SWABLU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swablu,
[SPECIES_ALTARIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Altaria,
[SPECIES_WYNAUT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wynaut,
[SPECIES_DUSKULL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Duskull,
[SPECIES_DUSCLOPS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dusclops,
[SPECIES_ROSELIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Roselia,
[SPECIES_SLAKOTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slakoth,
[SPECIES_VIGOROTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vigoroth,
[SPECIES_SLAKING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slaking,
[SPECIES_GULPIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gulpin,
[SPECIES_SWALOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swalot,
[SPECIES_TROPIUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tropius,
[SPECIES_WHISMUR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Whismur,
[SPECIES_LOUDRED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Loudred,
[SPECIES_EXPLOUD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Exploud,
[SPECIES_CLAMPERL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Clamperl,
[SPECIES_HUNTAIL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Huntail,
[SPECIES_GOREBYSS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gorebyss,
[SPECIES_ABSOL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Absol,
[SPECIES_SHUPPET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shuppet,
[SPECIES_BANETTE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Banette,
[SPECIES_SEVIPER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Seviper,
[SPECIES_ZANGOOSE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zangoose,
[SPECIES_RELICANTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Relicanth,
[SPECIES_ARON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aron,
[SPECIES_LAIRON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lairon,
[SPECIES_AGGRON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aggron,
[SPECIES_CASTFORM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Castform,
[SPECIES_VOLBEAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Volbeat,
[SPECIES_ILLUMISE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Illumise,
[SPECIES_LILEEP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lileep,
[SPECIES_CRADILY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cradily,
[SPECIES_ANORITH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Anorith,
[SPECIES_ARMALDO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Armaldo,
[SPECIES_RALTS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ralts,
[SPECIES_KIRLIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kirlia,
[SPECIES_GARDEVOIR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gardevoir,
[SPECIES_BAGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bagon,
[SPECIES_SHELGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shelgon,
[SPECIES_SALAMENCE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Salamence,
[SPECIES_BELDUM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Beldum,
[SPECIES_METANG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Metang,
[SPECIES_METAGROSS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Metagross,
[SPECIES_REGIROCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Regirock,
[SPECIES_REGICE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Regice,
[SPECIES_REGISTEEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Registeel,
[SPECIES_KYOGRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kyogre,
[SPECIES_GROUDON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Groudon,
[SPECIES_RAYQUAZA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rayquaza,
[SPECIES_LATIAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Latias,
[SPECIES_LATIOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Latios,
[SPECIES_JIRACHI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jirachi,
[SPECIES_DEOXYS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Deoxys,
[SPECIES_CHIMECHO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chimecho,
[SPECIES_EGG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Egg,
[SPECIES_UNOWN_B] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownB,
[SPECIES_UNOWN_C] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownC,
[SPECIES_UNOWN_D] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownD,
[SPECIES_UNOWN_E] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownE,
[SPECIES_UNOWN_F] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownF,
[SPECIES_UNOWN_G] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownG,
[SPECIES_UNOWN_H] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownH,
[SPECIES_UNOWN_I] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownI,
[SPECIES_UNOWN_J] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownJ,
[SPECIES_UNOWN_K] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownK,
[SPECIES_UNOWN_L] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownL,
[SPECIES_UNOWN_M] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownM,
[SPECIES_UNOWN_N] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownN,
[SPECIES_UNOWN_O] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownO,
[SPECIES_UNOWN_P] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownP,
[SPECIES_UNOWN_Q] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownQ,
[SPECIES_UNOWN_R] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownR,
[SPECIES_UNOWN_S] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownS,
[SPECIES_UNOWN_T] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownT,
[SPECIES_UNOWN_U] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownU,
[SPECIES_UNOWN_V] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownV,
[SPECIES_UNOWN_W] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownW,
[SPECIES_UNOWN_X] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownX,
[SPECIES_UNOWN_Y] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownY,
[SPECIES_UNOWN_Z] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownZ,
[SPECIES_UNOWN_EMARK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownExclamationMark,
[SPECIES_UNOWN_QMARK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //UnownQuestionMark, //ok I see now part of problem, this doeesn't have a comma and others are misaligned.
[SPECIES_TURTWIG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Turtwig,
[SPECIES_GROTLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grotle,
[SPECIES_TORTERRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Torterra,
[SPECIES_CHIMCHAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chimchar,
[SPECIES_MONFERNO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Monferno,
[SPECIES_INFERNAPE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Infernape,
[SPECIES_PIPLUP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Piplup,
[SPECIES_PRINPLUP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Prinplup,
[SPECIES_EMPOLEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Empoleon,
[SPECIES_STARLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Starly,
[SPECIES_STARAVIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Staravia,
[SPECIES_STARAPTOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Staraptor,
[SPECIES_BIDOOF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bidoof,
[SPECIES_BIBAREL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bibarel,
[SPECIES_KRICKETOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kricketot,
[SPECIES_KRICKETUNE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kricketune,
[SPECIES_SHINX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shinx,
[SPECIES_LUXIO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Luxio,
[SPECIES_LUXRAY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Luxray,
[SPECIES_BUDEW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Budew,
[SPECIES_ROSERADE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Roserade,
[SPECIES_CRANIDOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cranidos,
[SPECIES_RAMPARDOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rampardos,
[SPECIES_SHIELDON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shieldon,
[SPECIES_BASTIODON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bastiodon,
[SPECIES_BURMY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Burmy,
[SPECIES_WORMADAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wormadam,
[SPECIES_MOTHIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mothim,
[SPECIES_COMBEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Combee,
[SPECIES_VESPIQUEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vespiquen,
[SPECIES_PACHIRISU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pachirisu,
[SPECIES_BUIZEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Buizel,
[SPECIES_FLOATZEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Floatzel,
[SPECIES_CHERUBI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cherubi,
[SPECIES_CHERRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cherrim,
[SPECIES_SHELLOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shellos,
[SPECIES_GASTRODON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gastrodon,
[SPECIES_AMBIPOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ambipom,
[SPECIES_DRIFLOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drifloon,
[SPECIES_DRIFBLIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drifblim,
[SPECIES_BUNEARY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Buneary,
[SPECIES_LOPUNNY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lopunny,
[SPECIES_MISMAGIUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mismagius,
[SPECIES_HONCHKROW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Honchkrow,
[SPECIES_GLAMEOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Glameow,
[SPECIES_PURUGLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Purugly,
[SPECIES_CHINGLING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chingling,
[SPECIES_STUNKY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stunky,
[SPECIES_SKUNTANK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skuntank,
[SPECIES_BRONZOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bronzor,
[SPECIES_BRONZONG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bronzong,
[SPECIES_BONSLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bonsly,
[SPECIES_MIME_JR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MimeJr,
[SPECIES_HAPPINY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Happiny,
[SPECIES_CHATOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chatot,
[SPECIES_SPIRITOMB] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spiritomb,
[SPECIES_GIBLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gible,
[SPECIES_GABITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gabite,
[SPECIES_GARCHOMP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Garchomp,
[SPECIES_MUNCHLAX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Munchlax,
[SPECIES_RIOLU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Riolu,
[SPECIES_LUCARIO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lucario,
[SPECIES_HIPPOPOTAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hippopotas,
[SPECIES_HIPPOWDON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hippowdon,
[SPECIES_SKORUPI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skorupi,
[SPECIES_DRAPION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drapion,
[SPECIES_CROAGUNK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Croagunk,
[SPECIES_TOXICROAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Toxicroak,
[SPECIES_CARNIVINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Carnivine,
[SPECIES_FINNEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Finneon,
[SPECIES_LUMINEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lumineon,
[SPECIES_MANTYKE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mantyke,
[SPECIES_SNOVER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Snover,
[SPECIES_ABOMASNOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Abomasnow,
[SPECIES_WEAVILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Weavile,
[SPECIES_MAGNEZONE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magnezone,
[SPECIES_LICKILICKY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lickilicky,
[SPECIES_RHYPERIOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rhyperior,
[SPECIES_TANGROWTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tangrowth,
[SPECIES_ELECTIVIRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Electivire,
[SPECIES_MAGMORTAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magmortar,
[SPECIES_TOGEKISS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Togekiss,
[SPECIES_YANMEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Yanmega,
[SPECIES_LEAFEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Leafeon,
[SPECIES_GLACEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Glaceon,
[SPECIES_GLISCOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gliscor,
[SPECIES_MAMOSWINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mamoswine,
[SPECIES_PORYGON_Z] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Porygon_Z,
[SPECIES_GALLADE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gallade,
[SPECIES_PROBOPASS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Probopass,
[SPECIES_DUSKNOIR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dusknoir,
[SPECIES_FROSLASS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Froslass,
[SPECIES_ROTOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rotom,
[SPECIES_UXIE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Uxie,
[SPECIES_MESPRIT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mesprit,
[SPECIES_AZELF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Azelf,
[SPECIES_DIALGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dialga,
[SPECIES_PALKIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Palkia,
[SPECIES_HEATRAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Heatran,
[SPECIES_REGIGIGAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Regigigas,
[SPECIES_GIRATINA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Giratina,
[SPECIES_CRESSELIA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cresselia,
[SPECIES_PHIONE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Phione,
[SPECIES_MANAPHY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Manaphy,
[SPECIES_DARKRAI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Darkrai,
[SPECIES_SHAYMIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shaymin,
[SPECIES_ARCEUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_VICTINI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Victini,
[SPECIES_SNIVY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Snivy,
[SPECIES_SERVINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Servine,
[SPECIES_SERPERIOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Serperior,
[SPECIES_TEPIG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tepig,
[SPECIES_PIGNITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pignite,
[SPECIES_EMBOAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Emboar,
[SPECIES_OSHAWOTT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Oshawott,
[SPECIES_DEWOTT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dewott,
[SPECIES_SAMUROTT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Samurott,
[SPECIES_PATRAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Patrat,
[SPECIES_WATCHOG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Watchog,
[SPECIES_LILLIPUP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lillipup,
[SPECIES_HERDIER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Herdier,
[SPECIES_STOUTLAND] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stoutland,
[SPECIES_PURRLOIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Purrloin,
[SPECIES_LIEPARD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Liepard,
[SPECIES_PANSAGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pansage,
[SPECIES_SIMISAGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Simisage,
[SPECIES_PANSEAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pansear,
[SPECIES_SIMISEAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Simisear,
[SPECIES_PANPOUR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Panpour,
[SPECIES_SIMIPOUR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Simipour,
[SPECIES_MUNNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Munna,
[SPECIES_MUSHARNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Musharna,
[SPECIES_PIDOVE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pidove,
[SPECIES_TRANQUILL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tranquill,
[SPECIES_UNFEZANT_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Unfezant,
[SPECIES_BLITZLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Blitzle,
[SPECIES_ZEBSTRIKA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zebstrika,
[SPECIES_ROGGENROLA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Roggenrola,
[SPECIES_BOLDORE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Boldore,
[SPECIES_GIGALITH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gigalith,
[SPECIES_WOOBAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Woobat,
[SPECIES_SWOOBAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swoobat,
[SPECIES_DRILBUR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drilbur,
[SPECIES_EXCADRILL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Excadrill,
[SPECIES_AUDINO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Audino,
[SPECIES_TIMBURR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Timburr,
[SPECIES_GURDURR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gurdurr,
[SPECIES_CONKELDURR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Conkeldurr,
[SPECIES_TYMPOLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tympole,
[SPECIES_PALPITOAD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Palpitoad,
[SPECIES_SEISMITOAD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Seismitoad,
[SPECIES_THROH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Throh,
[SPECIES_SAWK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sawk,
[SPECIES_SEWADDLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sewaddle,
[SPECIES_SWADLOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swadloon,
[SPECIES_LEAVANNY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Leavanny,
[SPECIES_VENIPEDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Venipede,
[SPECIES_WHIRLIPEDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Whirlipede,
[SPECIES_SCOLIPEDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scolipede,
[SPECIES_COTTONEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cottonee,
[SPECIES_WHIMSICOTT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Whimsicott,
[SPECIES_PETILIL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Petilil,
[SPECIES_LILLIGANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lilligant,
[SPECIES_BASCULIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Basculin,
[SPECIES_SANDILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sandile,
[SPECIES_KROKOROK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Krokorok,
[SPECIES_KROOKODILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Krookodile,
[SPECIES_DARUMAKA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Darumaka,
[SPECIES_DARMANITAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Darmanitan,
[SPECIES_MARACTUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Maractus,
[SPECIES_DWEBBLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dwebble,
[SPECIES_CRUSTLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Crustle,
[SPECIES_SCRAGGY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scraggy,
[SPECIES_SCRAFTY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scrafty,
[SPECIES_SIGILYPH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sigilyph,
[SPECIES_YAMASK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Yamask,
[SPECIES_COFAGRIGUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cofagrigus,
[SPECIES_TIRTOUGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tirtouga,
[SPECIES_CARRACOSTA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Carracosta,
[SPECIES_ARCHEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Archen,
[SPECIES_ARCHEOPS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Archeops,
[SPECIES_TRUBBISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Trubbish,
[SPECIES_GARBODOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Garbodor,
[SPECIES_ZORUA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zorua,
[SPECIES_ZOROARK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zoroark,
[SPECIES_MINCCINO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minccino,
[SPECIES_CINCCINO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cinccino,
[SPECIES_GOTHITA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gothita,
[SPECIES_GOTHORITA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gothorita,
[SPECIES_GOTHITELLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gothitelle,
[SPECIES_SOLOSIS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Solosis,
[SPECIES_DUOSION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Duosion,
[SPECIES_REUNICLUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Reuniclus,
[SPECIES_DUCKLETT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ducklett,
[SPECIES_SWANNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swanna,
[SPECIES_VANILLITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vanillite,
[SPECIES_VANILLISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vanillish,
[SPECIES_VANILLUXE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vanilluxe,
[SPECIES_DEERLING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Deerling,
[SPECIES_SAWSBUCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sawsbuck,
[SPECIES_EMOLGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Emolga,
[SPECIES_KARRABLAST] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Karrablast,
[SPECIES_ESCAVALIER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Escavalier,
[SPECIES_FOONGUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Foongus,
[SPECIES_AMOONGUSS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Amoonguss,
[SPECIES_FRILLISH_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Frillish,
[SPECIES_JELLICENT_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jellicent,
[SPECIES_ALOMOMOLA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Alomomola,
[SPECIES_JOLTIK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Joltik,
[SPECIES_GALVANTULA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Galvantula,
[SPECIES_FERROSEED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ferroseed,
[SPECIES_FERROTHORN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ferrothorn,
[SPECIES_KLINK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Klink,
[SPECIES_KLANG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Klang,
[SPECIES_KLINKLANG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Klinklang,
[SPECIES_TYNAMO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tynamo,
[SPECIES_EELEKTRIK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eelektrik,
[SPECIES_EELEKTROSS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eelektross,
[SPECIES_ELGYEM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Elgyem,
[SPECIES_BEHEEYEM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Beheeyem,
[SPECIES_LITWICK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Litwick,
[SPECIES_LAMPENT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lampent,
[SPECIES_CHANDELURE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chandelure,
[SPECIES_AXEW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Axew,
[SPECIES_FRAXURE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Fraxure,
[SPECIES_HAXORUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Haxorus,
[SPECIES_CUBCHOO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cubchoo,
[SPECIES_BEARTIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Beartic,
[SPECIES_CRYOGONAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cryogonal,
[SPECIES_SHELMET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shelmet,
[SPECIES_ACCELGOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Accelgor,
[SPECIES_STUNFISK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stunfisk,
[SPECIES_MIENFOO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mienfoo,
[SPECIES_MIENSHAO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mienshao,
[SPECIES_DRUDDIGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Druddigon,
[SPECIES_GOLETT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Golett,
[SPECIES_GOLURK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Golurk,
[SPECIES_PAWNIARD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pawniard,
[SPECIES_BISHARP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bisharp,
[SPECIES_BOUFFALANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bouffalant,
[SPECIES_RUFFLET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rufflet,
[SPECIES_BRAVIARY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Braviary,
[SPECIES_VULLABY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vullaby,
[SPECIES_MANDIBUZZ] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mandibuzz,
[SPECIES_HEATMOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Heatmor,
[SPECIES_DURANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Durant,
[SPECIES_DEINO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Deino,
[SPECIES_ZWEILOUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zweilous,
[SPECIES_HYDREIGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hydreigon,
[SPECIES_LARVESTA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Larvesta,
[SPECIES_VOLCARONA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Volcarona,
[SPECIES_COBALION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cobalion,
[SPECIES_TERRAKION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Terrakion,
[SPECIES_VIRIZION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Virizion,
[SPECIES_TORNADUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tornadus,
[SPECIES_THUNDURUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Thundurus,
[SPECIES_RESHIRAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Reshiram,
[SPECIES_ZEKROM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zekrom,
[SPECIES_LANDORUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Landorus,
[SPECIES_KYUREM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kyurem,
[SPECIES_KELDEO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Keldeo,
[SPECIES_MELOETTA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meloetta,
[SPECIES_GENESECT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_CHESPIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chespin,
[SPECIES_QUILLADIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Quilladin,
[SPECIES_CHESNAUGHT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chesnaught,
[SPECIES_FENNEKIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Fennekin,
[SPECIES_BRAIXEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Braixen,
[SPECIES_DELPHOX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Delphox,
[SPECIES_FROAKIE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Froakie,
[SPECIES_FROGADIER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Frogadier,
[SPECIES_GRENINJA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Greninja,
[SPECIES_BUNNELBY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bunnelby,
[SPECIES_DIGGERSBY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Diggersby,
[SPECIES_FLETCHLING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Fletchling,
[SPECIES_FLETCHINDER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Fletchinder,
[SPECIES_TALONFLAME] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Talonflame,
[SPECIES_SCATTERBUG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scatterbug,
[SPECIES_SPEWPA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spewpa,
[SPECIES_VIVILLON_SNOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vivillon,
[SPECIES_LITLEO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Litleo,
[SPECIES_PYROAR_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pyroar,
[SPECIES_FLABEBE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Flabebe,
[SPECIES_FLOETTE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Floette,
[SPECIES_FLORGES] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Florges,
[SPECIES_SKIDDO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skiddo,
[SPECIES_GOGOAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gogoat,
[SPECIES_PANCHAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pancham,
[SPECIES_PANGORO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pangoro,
[SPECIES_FURFROU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Furfrou,
[SPECIES_ESPURR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Espurr,
[SPECIES_MEOWSTIC_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meowstic,
[SPECIES_HONEDGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Honedge,
[SPECIES_DOUBLADE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Doublade,
[SPECIES_AEGISLASH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aegislash,
[SPECIES_SPRITZEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spritzee,
[SPECIES_AROMATISSE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aromatisse,
[SPECIES_SWIRLIX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Swirlix,
[SPECIES_SLURPUFF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Slurpuff,
[SPECIES_INKAY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Inkay,
[SPECIES_MALAMAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Malamar,
[SPECIES_BINACLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Binacle,
[SPECIES_BARBARACLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Barbaracle,
[SPECIES_SKRELP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skrelp,
[SPECIES_DRAGALGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dragalge,
[SPECIES_CLAUNCHER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Clauncher,
[SPECIES_CLAWITZER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Clawitzer,
[SPECIES_HELIOPTILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Helioptile,
[SPECIES_HELIOLISK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Heliolisk,
[SPECIES_TYRUNT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tyrunt,
[SPECIES_TYRANTRUM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tyrantrum,
[SPECIES_AMAURA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Amaura,
[SPECIES_AURORUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Aurorus,
[SPECIES_SYLVEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sylveon,
[SPECIES_HAWLUCHA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hawlucha,
[SPECIES_DEDENNE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dedenne,
[SPECIES_CARBINK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Carbink,
[SPECIES_GOOMY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Goomy,
[SPECIES_SLIGGOO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sliggoo,
[SPECIES_GOODRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Goodra,
[SPECIES_KLEFKI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Klefki,
[SPECIES_PHANTUMP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Phantump,
[SPECIES_TREVENANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Trevenant,
[SPECIES_PUMPKABOO_AVERAGE_SIZE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_GOURGEIST_AVERAGE_SIZE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_BERGMITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bergmite,
[SPECIES_AVALUGG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Avalugg,
[SPECIES_NOIBAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Noibat,
[SPECIES_NOIVERN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Noivern,
[SPECIES_XERNEAS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Xerneas,
[SPECIES_YVELTAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Yveltal,
[SPECIES_ZYGARDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zygarde,
[SPECIES_DIANCIE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Diancie,
[SPECIES_HOOPA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hoopa,
[SPECIES_VOLCANION] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Volcanion,
[SPECIES_ROWLET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rowlet,
[SPECIES_DARTRIX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dartrix,
[SPECIES_DECIDUEYE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Decidueye,
[SPECIES_LITTEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Litten,
[SPECIES_TORRACAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Torracat,
[SPECIES_INCINEROAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Incineroar,
[SPECIES_POPPLIO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Popplio,
[SPECIES_BRIONNE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Brionne,
[SPECIES_PRIMARINA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Primarina,
[SPECIES_PIKIPEK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pikipek,
[SPECIES_TRUMBEAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Trumbeak,
[SPECIES_TOUCANNON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Toucannon,
[SPECIES_YUNGOOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Yungoos,
[SPECIES_GUMSHOOS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gumshoos,
[SPECIES_GRUBBIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grubbin,
[SPECIES_CHARJABUG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Charjabug,
[SPECIES_VIKAVOLT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Vikavolt,
[SPECIES_CRABRAWLER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Crabrawler,
[SPECIES_CRABOMINABLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Crabominable,
[SPECIES_ORICORIO_BAILE] = 
    {  
      //PIC_DATA(Oricorio_Baile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Oricorio_Baile),
      BACK_COORD(0x88,0),
      //PALETTES(Oricorio_Baile),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Oricorio_Baile,
[SPECIES_CUTIEFLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cutiefly,
[SPECIES_RIBOMBEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ribombee,
[SPECIES_ROCKRUFF] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rockruff,
[SPECIES_LYCANROC_MIDDAY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lycanroc,
[SPECIES_WISHIWASHI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wishiwashi,
[SPECIES_MAREANIE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mareanie,
[SPECIES_TOXAPEX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Toxapex,
[SPECIES_MUDBRAY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mudbray,
[SPECIES_MUDSDALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mudsdale,
[SPECIES_DEWPIDER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dewpider,
[SPECIES_ARAQUANID] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Araquanid,
[SPECIES_FOMANTIS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Fomantis,
[SPECIES_LURANTIS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lurantis,
[SPECIES_MORELULL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Morelull,
[SPECIES_SHIINOTIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Shiinotic,
[SPECIES_SALANDIT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Salandit,
[SPECIES_SALAZZLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Salazzle,
[SPECIES_STUFFUL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stufful,
[SPECIES_BEWEAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bewear,
[SPECIES_BOUNSWEET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bounsweet,
[SPECIES_STEENEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Steenee,
[SPECIES_TSAREENA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Tsareena,
[SPECIES_COMFEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Comfey,
[SPECIES_ORANGURU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Oranguru,
[SPECIES_PASSIMIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Passimian,
[SPECIES_WIMPOD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wimpod,
[SPECIES_GOLISOPOD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Golisopod,
[SPECIES_SANDYGAST] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sandygast,
[SPECIES_PALOSSAND] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Palossand,
[SPECIES_PYUKUMUKU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pyukumuku,
[SPECIES_TYPE_NULL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TypeNull,
[SPECIES_SILVALLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_MINIOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_KOMALA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Komala,
[SPECIES_TURTONATOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Turtonator,
[SPECIES_TOGEDEMARU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Togedemaru,
[SPECIES_MIMIKYU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Mimikyu,
[SPECIES_BRUXISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Bruxish,
[SPECIES_DRAMPA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drampa,
[SPECIES_DHELMISE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dhelmise,
[SPECIES_JANGMO_O] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Jangmoo,
[SPECIES_HAKAMO_O] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hakamoo,
[SPECIES_KOMMO_O] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kommoo,
[SPECIES_TAPU_KOKO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TapuKoko,
[SPECIES_TAPU_LELE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TapuLele,
[SPECIES_TAPU_BULU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TapuBulu,
[SPECIES_TAPU_FINI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TapuFini,
[SPECIES_COSMOG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cosmog,
[SPECIES_COSMOEM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cosmoem,
[SPECIES_SOLGALEO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Solgaleo,
[SPECIES_LUNALA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Lunala,
[SPECIES_NIHILEGO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nihilego,
[SPECIES_BUZZWOLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Buzzwole,
[SPECIES_PHEROMOSA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pheromosa,
[SPECIES_XURKITREE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Xurkitree,
[SPECIES_CELESTEELA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Celesteela,
[SPECIES_KARTANA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kartana,
[SPECIES_GUZZLORD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Guzzlord,
[SPECIES_NECROZMA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Necrozma,
[SPECIES_MAGEARNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Magearna,
[SPECIES_MARSHADOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Marshadow,
[SPECIES_POIPOLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Poipole,
[SPECIES_NAGANADEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Naganadel,
[SPECIES_STAKATAKA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stakataka,
[SPECIES_BLACEPHALON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Blacephalon,
[SPECIES_ZERAORA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zeraora,
[SPECIES_MELTAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meltan,
[SPECIES_MELMETAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Melmetal,
[SPECIES_GROOKEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grookey,
[SPECIES_THWACKEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Thwackey,
[SPECIES_RILLABOOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rillaboom,
[SPECIES_SCORBUNNY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Scorbunny,
[SPECIES_RABOOT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Raboot,
[SPECIES_CINDERACE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cinderace,
[SPECIES_SOBBLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sobble,
[SPECIES_DRIZZILE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drizzile,
[SPECIES_INTELEON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Inteleon,
[SPECIES_SKWOVET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Skwovet,
[SPECIES_GREEDENT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Greedent,
[SPECIES_ROOKIDEE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rookidee,
[SPECIES_CORVISQUIRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Corvisquire,
[SPECIES_CORVIKNIGHT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Corviknight,
[SPECIES_BLIPBUG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Blipbug,
[SPECIES_DOTTLER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dottler,
[SPECIES_ORBEETLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Orbeetle,
[SPECIES_NICKIT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Nickit,
[SPECIES_THIEVUL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Thievul,
[SPECIES_GOSSIFLEUR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gossifleur,
[SPECIES_ELDEGOSS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eldegoss,
[SPECIES_WOOLOO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wooloo,
[SPECIES_DUBWOOL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dubwool,
[SPECIES_CHEWTLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Chewtle,
[SPECIES_DREDNAW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drednaw,
[SPECIES_YAMPER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Yamper,
[SPECIES_BOLTUND] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Boltund,
[SPECIES_ROLYCOLY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Rolycoly,
[SPECIES_CARKOL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Carkol,
[SPECIES_COALOSSAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Coalossal,
[SPECIES_APPLIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Applin,
[SPECIES_FLAPPLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Flapple,
[SPECIES_APPLETUN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Appletun,
[SPECIES_SILICOBRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silicobra,
[SPECIES_SANDACONDA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sandaconda,
[SPECIES_CRAMORANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cramorant,
[SPECIES_ARROKUDA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arrokuda,
[SPECIES_BARRASKEWDA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Barraskewda,
[SPECIES_TOXEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Toxel,
[SPECIES_TOXTRICITY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Toxtricity,
[SPECIES_SIZZLIPEDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sizzlipede,
[SPECIES_CENTISKORCH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Centiskorch,
[SPECIES_CLOBBOPUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Clobbopus,
[SPECIES_GRAPPLOCT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grapploct,
[SPECIES_SINISTEA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sinistea,
[SPECIES_POLTEAGEIST] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Polteageist,
[SPECIES_HATENNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hatenna,
[SPECIES_HATTREM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hattrem,
[SPECIES_HATTERENE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Hatterene,
[SPECIES_IMPIDIMP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Impidimp,
[SPECIES_MORGREM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Morgrem,
[SPECIES_GRIMMSNARL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Grimmsnarl,
[SPECIES_OBSTAGOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Obstagoon,
[SPECIES_PERRSERKER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Perrserker,
[SPECIES_CURSOLA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cursola,
[SPECIES_SIRFETCHD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sirfetchd,
[SPECIES_MR_RIME] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MrRime,
[SPECIES_RUNERIGUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Runerigus,
[SPECIES_MILCERY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Milcery,
[SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,
[SPECIES_FALINKS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Falinks,
[SPECIES_PINCURCHIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pincurchin,
[SPECIES_SNOM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Snom,
[SPECIES_FROSMOTH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Frosmoth,
[SPECIES_STONJOURNER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Stonjourner,
[SPECIES_EISCUE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eiscue,
[SPECIES_INDEEDEE_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Indeedee,
[SPECIES_MORPEKO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Morpeko,
[SPECIES_CUFANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cufant,
[SPECIES_COPPERAJAH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Copperajah,
[SPECIES_DRACOZOLT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dracozolt,
[SPECIES_ARCTOZOLT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arctozolt,
[SPECIES_DRACOVISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dracovish,
[SPECIES_ARCTOVISH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arctovish,
[SPECIES_DURALUDON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Duraludon,
[SPECIES_DREEPY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dreepy,
[SPECIES_DRAKLOAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Drakloak,
[SPECIES_DRAGAPULT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Dragapult,
[SPECIES_ZACIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zacian,
[SPECIES_ZAMAZENTA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zamazenta,
[SPECIES_ETERNATUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eternatus,
[SPECIES_KUBFU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kubfu,
[SPECIES_URSHIFU_SINGLE_STRIKE_STYLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Urshifu,
[SPECIES_ZARUDE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zarude,
[SPECIES_REGIELEKI] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Regieleki,
[SPECIES_REGIDRAGO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Regidrago,
[SPECIES_GLASTRIER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Glastrier,
[SPECIES_SPECTRIER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Spectrier,
[SPECIES_CALYREX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Calyrex,
[SPECIES_WYRDEER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Wyrdeer,
[SPECIES_KLEAVOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Kleavor,
[SPECIES_URSALUNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Ursaluna,
[SPECIES_BASCULEGION_MALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Basculegion,
[SPECIES_SNEASLER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Sneasler,
[SPECIES_OVERQWIL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Overqwil,
[SPECIES_ENAMORUS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Enamorus,
  [SPECIES_SPRIGATITO] =
    {
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              61,
              54,
              65,
              45,
              45
       ),
        MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 62,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE  },
        .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Sprigatito"),
        .cryId = CRY_SPRIGATITO,
        .natDexNum = NATIONAL_DEX_SPRIGATITO,
        .categoryName = _("Grass Cat"),
        .height = 4,
        .weight = 41,
        .description = COMPOUND_STRING(
            "The sweet scent its body gives off\n"
            "mesmerizes those around it. The\n"
            "scent grows stronger when this\n"
            "Pokémon is in the sun."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sprigatito,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_Sprigatito,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Sprigatito,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sprigatito,
        .shinyPalette = gMonShinyPalette_Sprigatito,
        .iconSprite = gMonIcon_Sprigatito,
        .iconPalIndex = 1,
        //FOOTPRINT(Sprigatito)
        */
        //.levelUpLearnset = sSprigatitoLevelUpLearnset,
        //.teachableLearnset = sSprigatitoTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 16, 0,  SPECIES_FLORAGATO}),
      .enemyMonElevation = 0,
    },

    [SPECIES_FLORAGATO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              61,
              80,
              63,
              83,
              60,
              63
       ),
        MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 144,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE },
        .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Floragato"),
        .cryId = CRY_FLORAGATO,
        .natDexNum = NATIONAL_DEX_FLORAGATO,
        .categoryName = _("Grass Cat"),
        .height = 9,
        .weight = 122,
        .description = COMPOUND_STRING(
            "Floragato deftly wields the vine\n"
            "hidden beneath its long fur, slamming\n"
            "the hard flower bud against its\n"
            "opponents."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Floragato,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Floragato,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Floragato,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Floragato,
        .shinyPalette = gMonShinyPalette_Floragato,
        .iconSprite = gMonIcon_Floragato,
        .iconPalIndex = 1,
        //FOOTPRINT(Floragato)
        */
        //.levelUpLearnset = sFloragatoLevelUpLearnset,
        //.teachableLearnset = sFloragatoTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 36, 0,  SPECIES_MEOWSCARADA}),
      .enemyMonElevation = 0,
    },

    [SPECIES_MEOWSCARADA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              76,
              110,
              70,
              123,
              81,
              70
       ),
        MON_TYPES(TYPE_GRASS, TYPE_DARK),
        .catchRate = 45,
        .expYield = 265,
       // .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Meowscarad"),
        .cryId = CRY_MEOWSCARADA,
        .natDexNum = NATIONAL_DEX_MEOWSCARADA,
        .categoryName = _("Magician"),
        .height = 15,
        .weight = 312,
        .description = COMPOUND_STRING(
            "This Pokémon uses the reflective\n"
            "fur lining its cape to camouflage the\n"
            "stem of its flower, creating the\n"
            "illusion that the flower is floating."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Meowscarada,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Meowscarada,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Meowscarada,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Meowscarada,
        .shinyPalette = gMonShinyPalette_Meowscarada,
        .iconSprite = gMonIcon_Meowscarada,
        .iconPalIndex = 1,
        //FOOTPRINT(Meowscarada)
        */
        //.levelUpLearnset = sMeowscaradaLevelUpLearnset,
        //.teachableLearnset = sMeowscaradaTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SPRIGATITO

//#if p_fAMILY_FUECOCO
    [SPECIES_FUECOCO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              67,
              45,
              59,
              36,
              63,
              40
       ),
        MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 62,
       // .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE},
         .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Fuecoco"),
        .cryId = CRY_FUECOCO,
        .natDexNum = NATIONAL_DEX_FUECOCO,
        .categoryName = _("Fire Croc"),
        .height = 4,
        .weight = 98,
        .description = COMPOUND_STRING(
            "Its flame sac is small, so energy is\n"
            "always leaking out. This energy is\n"
            "released from the dent atop\n"
            "Fuecoco's head and flickers to and fro."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fuecoco,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_Fuecoco,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Fuecoco,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fuecoco,
        .shinyPalette = gMonShinyPalette_Fuecoco,
        .iconSprite = gMonIcon_Fuecoco,
        .iconPalIndex = 2,
        //FOOTPRINT(Fuecoco)
        */
        //.levelUpLearnset = sFuecocoLevelUpLearnset,
        //.teachableLearnset = sFuecocoTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 16, 0,  SPECIES_CROCALOR}),
      .enemyMonElevation = 0,
    },

    [SPECIES_CROCALOR] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              81,
              55,
              78,
              49,
              90,
              58
       ),
        MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 144,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Crocalor"),
        .cryId = CRY_CROCALOR,
        .natDexNum = NATIONAL_DEX_CROCALOR,
        .categoryName = _("Fire Croc"),
        .height = 10,
        .weight = 307,
        .description = COMPOUND_STRING(
            "The combination of Crocalor's fire\n"
            "energy and overflowing vitality has\n"
            "caused an egg-shaped fireball to\n"
            "appear on the Pokémon's head."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Crocalor,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Crocalor,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Crocalor,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Crocalor,
        .shinyPalette = gMonShinyPalette_Crocalor,
        .iconSprite = gMonIcon_Crocalor,
        .iconPalIndex = 0,
        //FOOTPRINT(Crocalor)
        */
        //.levelUpLearnset = sCrocalorLevelUpLearnset,
        //.teachableLearnset = sCrocalorTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 36, 0,  SPECIES_SKELEDIRGE}),
      .enemyMonElevation = 0,
    },

    [SPECIES_SKELEDIRGE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              104,
              75,
              100,
              66,
              110,
              75
       ),
        MON_TYPES(TYPE_FIRE, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 265,
       // .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE },
        .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Skeledirge"),
        .cryId = CRY_SKELEDIRGE,
        .natDexNum = NATIONAL_DEX_SKELEDIRGE,
        .categoryName = _("Singer"),
        .height = 16,
        .weight = 3265,
        .description = COMPOUND_STRING(
            "Skeledirge's gentle singing\n"
            "soothes the souls of all that hear it. It\n"
            "burns its enemies to a crisp with\n"
            "flames of over 5,400 degrees Fahrenheit."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skeledirge,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_Skeledirge,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skeledirge,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skeledirge,
        .shinyPalette = gMonShinyPalette_Skeledirge,
        .iconSprite = gMonIcon_Skeledirge,
        .iconPalIndex = 0,
        //FOOTPRINT(Skeledirge)
        */
        //.levelUpLearnset = sSkeledirgeLevelUpLearnset,
        //.teachableLearnset = sSkeledirgeTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FUECOCO

//#if p_fAMILY_QUAXLY
    [SPECIES_QUAXLY] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              55,
              65,
              45,
              50,
              50,
              45
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield =  62,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE },
        .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Quaxly"),
        .cryId = CRY_QUAXLY,
        .natDexNum = NATIONAL_DEX_QUAXLY,
        .categoryName = _("Duckling"),
        .height = 5,
        .weight = 61,
        .description = COMPOUND_STRING(
            "Its strong legs let it easily swim\n"
            "around in even fast-flowing rivers.\n"
            "It likes to keep things tidy and is\n"
            "prone to overthinking things."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Quaxly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Quaxly,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Quaxly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Quaxly,
        .shinyPalette = gMonShinyPalette_Quaxly,
        .iconSprite = gMonIcon_Quaxly,
        .iconPalIndex = 0,
        //FOOTPRINT(Quaxly)
        */
        //.levelUpLearnset = sQuaxlyLevelUpLearnset,
        //.teachableLearnset = sQuaxlyTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 16, 0,  SPECIES_QUAXWELL}),
      .enemyMonElevation = 0,
    },

    [SPECIES_QUAXWELL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              85,
              65,
              65,
              65,
              60
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 144,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE },
        .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Quaxwell"),
        .cryId = CRY_QUAXWELL,
        .natDexNum = NATIONAL_DEX_QUAXWELL,
        .categoryName = _("Practicing"),
        .height = 12,
        .weight = 215,
        .description = COMPOUND_STRING(
            "The hardworking Quaxwell observes\n"
            "people and Pokémon from various\n"
            "regions and incorporates their\n"
            "movements into its own dance routines."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Quaxwell,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Quaxwell,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Quaxwell,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Quaxwell,
        .shinyPalette = gMonShinyPalette_Quaxwell,
        .iconSprite = gMonIcon_Quaxwell,
        .iconPalIndex = 0,
        //FOOTPRINT(Quaxwell)
        */
        //.levelUpLearnset = sQuaxwellLevelUpLearnset,
        //.teachableLearnset = sQuaxwellTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 36, 0,  SPECIES_QUAQUAVAL}),
      .enemyMonElevation = 0,
    },

    [SPECIES_QUAQUAVAL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              85,
              120,
              80,
              85,
              85,
              75
       ),
        MON_TYPES(TYPE_WATER, TYPE_FIGHTING),
        .catchRate = 45,
        .expYield = 265,
       // .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE },
        .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Quaquaval"),
        .cryId = CRY_QUAQUAVAL,
        .natDexNum = NATIONAL_DEX_QUAQUAVAL,
        .categoryName = _("Dancer"),
        .height = 18,
        .weight = 619,
        .description = COMPOUND_STRING(
            "A single kick from a Quaquaval can\n"
            "send a truck rolling. This Pokémon\n"
            "uses its powerful legs to perform\n"
            "striking dances from far-off lands."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Quaquaval,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Quaquaval,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Quaquaval,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Quaquaval,
        .shinyPalette = gMonShinyPalette_Quaquaval,
        .iconSprite = gMonIcon_Quaquaval,
        .iconPalIndex = 0,
        //FOOTPRINT(Quaquaval)
        */
        //.levelUpLearnset = sQuaquavalLevelUpLearnset,
        //.teachableLearnset = sQuaquavalTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_QUAXLY

//#if p_fAMILY_LECHONK
    [SPECIES_LECHONK] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              54,
              45,
              40,
              35,
              35,
              45
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 51,
       // .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_AROMA_VEIL, ABILITY_GLUTTONY  },
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Lechonk"),
        .cryId = CRY_LECHONK,
        .natDexNum = NATIONAL_DEX_LECHONK,
        .categoryName = _("Hog"),
        .height = 5,
        .weight = 102,
        .description = COMPOUND_STRING(
            "It searches for food all day. It\n"
            "possesses a keen sense of smell but\n"
            "doesn't use it for anything other\n"
            "than foraging."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Lechonk,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_Lechonk,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Lechonk,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Lechonk,
        .shinyPalette = gMonShinyPalette_Lechonk,
        .iconSprite = gMonIcon_Lechonk,
        .iconPalIndex = 1,
        //FOOTPRINT(Lechonk)
        */
        //.levelUpLearnset = sLechonkLevelUpLearnset,
        //.teachableLearnset = sLechonkTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL_MALE, 18, 0,  SPECIES_OINKOLOGNE_MALE},
              //                  {EVO_LEVEL_FEMALE, 18, 0,  SPECIES_OINKOLOGNE_FEMALE}),
      .enemyMonElevation = 0,
    },

    [SPECIES_OINKOLOGNE_MALE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              110,
              100,
              75,
              65,
              59,
              80
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 100,
        .expYield = 171,
       // .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(0),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LINGERING_AROMA, ABILITY_GLUTTONY },
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Oinkologne"),
        .cryId = CRY_OINKOLOGNE_MALE,
        .natDexNum = NATIONAL_DEX_OINKOLOGNE,
        .categoryName = _("Hog"),
        .height = 10,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "Oinkologne is proud of its fine,\n"
            "glossy skin. It emits a concentrated\n"
            "scent from the tip of its tail."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_OinkologneMale,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Oinkologne,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_OinkologneMale,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_OinkologneMale,
        .shinyPalette = gMonShinyPalette_OinkologneMale,
        .iconSprite = gMonIcon_OinkologneMale,
        .iconPalIndex = 1,
        //FOOTPRINT(Oinkologne)
        */
        //.levelUpLearnset = sOinkologneMaleLevelUpLearnset,
        //.teachableLearnset = sOinkologneTeachableLearnset,
        //.formSpeciesIdTable = sOinkologneFormSpeciesIdTable,
        
      .enemyMonElevation = 0,
    },

    [SPECIES_OINKOLOGNE_FEMALE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              115,
              90,
              70,
              65,
              59,
              90
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 100,
        .expYield = 171,
       // .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(100),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_AROMA_VEIL, ABILITY_GLUTTONY },
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Oinkologne"),
        .cryId = CRY_OINKOLOGNE_FEMALE,
        .natDexNum = NATIONAL_DEX_OINKOLOGNE,
        .categoryName = _("Hog"),
        .height = 10,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "This is a meticulous Pokémon that\n"
            "likes to keep things tidy. It\n"
            "shrouds itself in a floral aroma that\n"
            "soothes the Pokémon around it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_OinkologneFemale,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Oinkologne,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_OinkologneFemale,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_OinkologneFemale,
        .shinyPalette = gMonShinyPalette_OinkologneFemale,
        .iconSprite = gMonIcon_OinkologneFemale,
        .iconPalIndex = 0,
        //FOOTPRINT(Oinkologne)
        */
        //.levelUpLearnset = sOinkologneFemaleLevelUpLearnset,
        //.teachableLearnset = sOinkologneTeachableLearnset,
        //.formSpeciesIdTable = sOinkologneFormSpeciesIdTable,
        
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_LECHONK

//#if p_fAMILY_TAROUNTULA
    [SPECIES_TAROUNTULA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              35,
              41,
              45,
              20,
              29,
              40
       ),
        MON_TYPES(TYPE_BUG),
        .catchRate = 255,
        .expYield = 42,
       // .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_INSOMNIA, ABILITY_NONE},
        .abilityHidden = {ABILITY_STAKEOUT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tarountula"),
        .cryId = CRY_TAROUNTULA,
        .natDexNum = NATIONAL_DEX_TAROUNTULA,
        .categoryName = _("String Ball"),
        .height = 3,
        .weight = 40,
        .description = COMPOUND_STRING(
            "The thread it secretes from its\n"
            "rear is as strong as wire. The secret\n"
            "behind the thread's strength is the\n"
            "topic of ongoing research."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tarountula,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Tarountula,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tarountula,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tarountula,
        .shinyPalette = gMonShinyPalette_Tarountula,
        .iconSprite = gMonIcon_Tarountula,
        .iconPalIndex = 1,
        //FOOTPRINT(Tarountula)
        */
        //.levelUpLearnset = sTarountulaLevelUpLearnset,
        //.teachableLearnset = sTarountulaTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 15, 0,  SPECIES_SPIDOPS}),
      .enemyMonElevation = 0,
    },

    [SPECIES_SPIDOPS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              60,
              79,
              92,
              35,
              52,
              86
       ),
        MON_TYPES(TYPE_BUG),
        .catchRate = 120,
        .expYield = 141,
       // .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_INSOMNIA, ABILITY_NONE },
        .abilityHidden = {ABILITY_STAKEOUT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Spidops"),
        .cryId = CRY_SPIDOPS,
        .natDexNum = NATIONAL_DEX_SPIDOPS,
        .categoryName = _("Trap"),
        .height = 10,
        .weight = 165,
        .description = COMPOUND_STRING(
            "It clings to branches and ceilings\n"
            "using its threads and moves without\n"
            "a sound. It takes out its prey\n"
            "before the prey even notices it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Spidops,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_Spidops,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Spidops,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Spidops,
        .shinyPalette = gMonShinyPalette_Spidops,
        .iconSprite = gMonIcon_Spidops,
        .iconPalIndex = 1,
        //FOOTPRINT(Spidops)
        */
        //.levelUpLearnset = sSpidopsLevelUpLearnset,
        //.teachableLearnset = sSpidopsTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TAROUNTULA

//#if p_fAMILY_NYMBLE
    [SPECIES_NYMBLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              33,
              46,
              40,
              45,
              21,
              25
       ),
        MON_TYPES(TYPE_BUG),
        .catchRate = 190,
        .expYield = 42,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 20,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SWARM, ABILITY_NONE  },
        .abilityHidden = {ABILITY_TINTED_LENS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Nymble"),
        .cryId = CRY_NYMBLE,
        .natDexNum = NATIONAL_DEX_NYMBLE,
        .categoryName = _("Grasshopper"),
        .height = 2,
        .weight = 10,
        .description = COMPOUND_STRING(
            "It has its third set of legs folded\n"
            "up. When it's in a tough spot, this\n"
            "Pokémon jumps over 30 feet using the\n"
            "strength of its legs."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Nymble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_Nymble,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Nymble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Nymble,
        .shinyPalette = gMonShinyPalette_Nymble,
        .iconSprite = gMonIcon_Nymble,
        .iconPalIndex = 0,
        //FOOTPRINT(Nymble)
        */
        //.levelUpLearnset = sNymbleLevelUpLearnset,
        //.teachableLearnset = sNymbleTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 24, 0,  SPECIES_LOKIX}),
      .enemyMonElevation = 0,
    },

    [SPECIES_LOKIX] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              71,
              102,
              78,
              92,
              52,
              55
       ),
        MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 30,
        .expYield = 158,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SWARM, ABILITY_NONE },
        .abilityHidden = {ABILITY_TINTED_LENS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Lokix"),
        .cryId = CRY_LOKIX,
        .natDexNum = NATIONAL_DEX_LOKIX,
        .categoryName = _("Grasshopper"),
        .height = 10,
        .weight = 175,
        .description = COMPOUND_STRING(
            "When it decides to fight all out, it\n"
            "stands on its previously folded\n"
            "legs to enter Showdown Mode. It\n"
            "neutralizes its enemies in short order."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Lokix,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Lokix,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Lokix,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Lokix,
        .shinyPalette = gMonShinyPalette_Lokix,
        .iconSprite = gMonIcon_Lokix,
        .iconPalIndex = 0,
        //FOOTPRINT(Lokix)
        */
        //.levelUpLearnset = sLokixLevelUpLearnset,
        //.teachableLearnset = sLokixTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_NYMBLE

//#if p_fAMILY_PAWMI
    [SPECIES_PAWMI] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              45,
              50,
              20,
              60,
              40,
              25
       ),
        MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 190,
        .expYield = 48,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_STATIC, ABILITY_NATURAL_CURE },
        .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Pawmi"),
        .cryId = CRY_PAWMI,
        .natDexNum = NATIONAL_DEX_PAWMI,
        .categoryName = _("Mouse"),
        .height = 3,
        .weight = 25,
        .description = COMPOUND_STRING(
            "The pads of its paws are\n"
            "electricity-discharging organs. Pawmi fires\n"
            "electricity from its forepaws while\n"
            "standing unsteadily on its hind legs."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Pawmi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Pawmi,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pawmi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pawmi,
        .shinyPalette = gMonShinyPalette_Pawmi,
        .iconSprite = gMonIcon_Pawmi,
        .iconPalIndex = 0,
        //FOOTPRINT(Pawmi)
        */
        //.levelUpLearnset = sPawmiLevelUpLearnset,
        //.teachableLearnset = sPawmiTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 18, 0,  SPECIES_PAWMO}),
      .enemyMonElevation = 0,
    },

    [SPECIES_PAWMO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              60,
              75,
              40,
              85,
              50,
              40
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_FIGHTING),
        .catchRate = 80,
        .expYield = 123,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_VOLT_ABSORB, ABILITY_NATURAL_CURE},
        .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Pawmo"),
        .cryId = CRY_PAWMO,
        .natDexNum = NATIONAL_DEX_PAWMO,
        .categoryName = _("Mouse"),
        .height = 4,
        .weight = 65,
        .description = COMPOUND_STRING(
            "When its group is attacked, Pawmo\n"
            "is the first to leap into battle,\n"
            "defeating enemies with a fighting\n"
            "technique that utilizes electric shocks."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Pawmo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Pawmo,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pawmo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pawmo,
        .shinyPalette = gMonShinyPalette_Pawmo,
        .iconSprite = gMonIcon_Pawmo,
        .iconPalIndex = 0,
        //FOOTPRINT(Pawmo)
        */
        //.levelUpLearnset = sPawmoLevelUpLearnset,
        //.teachableLearnset = sPawmoTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_NONE, 0, 0,  SPECIES_PAWMOT}),
      .enemyMonElevation = 0,
    },

    [SPECIES_PAWMOT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              115,
              70,
              105,
              70,
              60
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_FIGHTING),
        .catchRate = 45,
        .expYield = 245,
       // .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_VOLT_ABSORB, ABILITY_NATURAL_CURE },
        .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Pawmot"),
        .cryId = CRY_PAWMOT,
        .natDexNum = NATIONAL_DEX_PAWMOT,
        .categoryName = _("Hands-On"),
        .height = 9,
        .weight = 410,
        .description = COMPOUND_STRING(
            "This Pokémon normally is slow to\n"
            "react, but once it enters battle, it\n"
            "will strike down its enemies with\n"
            "lightning-fast movements."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Pawmot,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Pawmot,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pawmot,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pawmot,
        .shinyPalette = gMonShinyPalette_Pawmot,
        .iconSprite = gMonIcon_Pawmot,
        .iconPalIndex = 0,
        //FOOTPRINT(Pawmot)
        */
        //.levelUpLearnset = sPawmotLevelUpLearnset,
        //.teachableLearnset = sPawmotTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_PAWMI

//#if p_fAMILY_TANDEMAUS
    [SPECIES_TANDEMAUS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              50,
              50,
              45,
              75,
              40,
              45
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 150,
        .expYield = 61,
       // .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_PICKUP },
        .abilityHidden = {ABILITY_OWN_TEMPO, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tandemaus"),
        .cryId = CRY_TANDEMAUS,
        .natDexNum = NATIONAL_DEX_TANDEMAUS,
        .categoryName = _("Couple"),
        .height = 3,
        .weight = 18,
        .description = COMPOUND_STRING(
            "Exhibiting great teamwork, they\n"
            "use their incisors to cut pieces out\n"
            "of any material that might be useful\n"
            "for a nest, then make off with them."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tandemaus,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = sAnims_Tandemaus,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tandemaus,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tandemaus,
        .shinyPalette = gMonShinyPalette_Tandemaus,
        .iconSprite = gMonIcon_Tandemaus,
        .iconPalIndex = 1,
        //FOOTPRINT(Tandemaus)
        */
        //.levelUpLearnset = sTandemausLevelUpLearnset,
        //.teachableLearnset = sTandemausTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL_FAMILY_OF_FOUR, 25, 0,  SPECIES_MAUSHOLD_FAMILY_OF_FOUR},
       //                         {EVO_LEVEL_FAMILY_OF_THREE, 25, 0,  SPECIES_MAUSHOLD_FAMILY_OF_THREE}),
      .enemyMonElevation = 0,
    },

    [SPECIES_MAUSHOLD_FAMILY_OF_THREE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              74,
              75,
              70,
              111,
              65,
              75
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 75,
        .expYield = 165,
       // .evYield_Speed = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_FRIEND_GUARD, ABILITY_CHEEK_POUCH  },
        .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Maushold"),
        .cryId = CRY_MAUSHOLD_FAMILY_OF_THREE,
        .natDexNum = NATIONAL_DEX_MAUSHOLD,
        .categoryName = _("Family"),
        .height = 3,
        .weight = 23,
        .description = COMPOUND_STRING(
            "The little one just appeared one\n"
            "day. They all live together like a\n"
            "family, but the relationship between\n"
            "the three is still unclear."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MausholdFamilyOfThree,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = sAnims_Maushold,

        .backPic = gMonBackPic_MausholdFamilyOfThree,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,

        .palette = gMonPalette_Maushold,
        .shinyPalette = gMonShinyPalette_Maushold,
        .iconSprite = gMonIcon_MausholdFamilyOfThree,
        .iconPalIndex = 1,

        */
        //.levelUpLearnset = sMausholdLevelUpLearnset,
        //.teachableLearnset = sMausholdTeachableLearnset,
        //.formSpeciesIdTable = sMausholdFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },
    [SPECIES_MAUSHOLD_FAMILY_OF_FOUR] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              74,
              75,
              70,
              111,
              65,
              75
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 75,
        .expYield = 165,
       // .evYield_Speed = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_FRIEND_GUARD, ABILITY_CHEEK_POUCH },
        .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Maushold"),
        .cryId = CRY_MAUSHOLD_FAMILY_OF_FOUR,
        .natDexNum = NATIONAL_DEX_MAUSHOLD,
        .categoryName = _("Family"),
        .height = 3,
        .weight = 28,
        .description = COMPOUND_STRING(
            "The larger pair protects the little\n"
            "ones during battles. When facing\n"
            "strong opponents, the whole group\n"
            "will join the fight."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MausholdFamilyOfFour,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = sAnims_Maushold,
        .backPic = gMonBackPic_MausholdFamilyOfFour,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        .palette = gMonPalette_Maushold,
        .shinyPalette = gMonShinyPalette_Maushold,
        .iconSprite = gMonIcon_MausholdFamilyOfFour,
        .iconPalIndex = 1,
        */
        //.levelUpLearnset = sMausholdLevelUpLearnset,
        //.teachableLearnset = sMausholdTeachableLearnset,
        //.formSpeciesIdTable = sMausholdFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TANDEMAUS

//#if p_fAMILY_FIDOUGH
    [SPECIES_FIDOUGH] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              37,
              55,
              70,
              65,
              30,
              55
       ),
        MON_TYPES(TYPE_FAIRY),
        .catchRate = 190,
        .expYield = 62,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_OWN_TEMPO, ABILITY_NONE  },
        .abilityHidden = {ABILITY_KLUTZ, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Fidough"),
        .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH,
        .categoryName = _("Puppy"),
        .height = 3,
        .weight = 109,
        .description = COMPOUND_STRING(
            "This Pokémon is smooth and moist\n"
            "to the touch. Yeast in Fidough's\n"
            "breath induces fermentation in the\n"
            "Pokémon's vicinity."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fidough,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Fidough,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Fidough,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fidough,
        .shinyPalette = gMonShinyPalette_Fidough,
        .iconSprite = gMonIcon_Fidough,
        .iconPalIndex = 1,
        //FOOTPRINT(Fidough)
        */
        //.levelUpLearnset = sFidoughLevelUpLearnset,
        //.teachableLearnset = sFidoughTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 26, 0,  SPECIES_DACHSBUN}),
      .enemyMonElevation = 0,
    },

    [SPECIES_DACHSBUN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              57,
              80,
              115,
              95,
              50,
              80
       ),
        MON_TYPES(TYPE_FAIRY),
        .catchRate = 90,
        .expYield = 167,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE  },
        .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Dachsbun"),
        .cryId = CRY_DACHSBUN,
        .natDexNum = NATIONAL_DEX_DACHSBUN,
        .categoryName = _("Dog"),
        .height = 5,
        .weight = 149,
        .description = COMPOUND_STRING(
            "The pleasant aroma that emanates\n"
            "from this Pokémon's body helps\n"
            "wheat grow, so Dachsbun has been\n"
            "treasured by farming villages."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dachsbun,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Dachsbun,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Dachsbun,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dachsbun,
        .shinyPalette = gMonShinyPalette_Dachsbun,
        .iconSprite = gMonIcon_Dachsbun,
        .iconPalIndex = 0,
        //FOOTPRINT(Dachsbun)
        */
        //.levelUpLearnset = sDachsbunLevelUpLearnset,
        //.teachableLearnset = sDachsbunTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FIDOUGH

//#if p_fAMILY_SMOLIV
    [SPECIES_SMOLIV] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              41,
              35,
              45,
              30,
              58,
              51
       ),
        MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 52,
       // .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_EARLY_BIRD, ABILITY_NONE  },
        .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Smoliv"),
        .cryId = CRY_SMOLIV,
        .natDexNum = NATIONAL_DEX_SMOLIV,
        .categoryName = _("Olive"),
        .height = 3,
        .weight = 65,
        .description = COMPOUND_STRING(
            "This Pokémon converts nutrients\n"
            "into oil, which it stores in the fruit\n"
            "on its head. It can easily go a whole\n"
            "week without eating or drinking."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Smoliv,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Smoliv,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Smoliv,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Smoliv,
        .shinyPalette = gMonShinyPalette_Smoliv,
        .iconSprite = gMonIcon_Smoliv,
        .iconPalIndex = 1,
        //FOOTPRINT(Smoliv)
        */
        //.levelUpLearnset = sSmolivLevelUpLearnset,
        //.teachableLearnset = sSmolivTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 25, 0,  SPECIES_DOLLIV}),
      .enemyMonElevation = 0,
    },

    [SPECIES_DOLLIV] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              52,
              53,
              60,
              33,
              78,
              78
       ),
        MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 120,
        .expYield = 124,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_EARLY_BIRD, ABILITY_NONE },
        .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Dolliv"),
        .cryId = CRY_DOLLIV,
        .natDexNum = NATIONAL_DEX_DOLLIV,
        .categoryName = _("Olive"),
        .height = 6,
        .weight = 119,
        .description = COMPOUND_STRING(
            "Dolliv shares its tasty, fresh-\n"
            "scented oil with others. This species\n"
            "has coexisted with humans since\n"
            "times long gone."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dolliv,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Dolliv,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Dolliv,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dolliv,
        .shinyPalette = gMonShinyPalette_Dolliv,
        .iconSprite = gMonIcon_Dolliv,
        .iconPalIndex = 1,
        //FOOTPRINT(Dolliv)
        */
        //.levelUpLearnset = sDollivLevelUpLearnset,
        //.teachableLearnset = sDollivTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 35, 0,  SPECIES_ARBOLIVA}),
      .enemyMonElevation = 0,
    },

    [SPECIES_ARBOLIVA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              78,
              69,
              90,
              39,
              125,
              109
       ),
        MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 45,
        .expYield = 255,
       // .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_SEED_SOWER, ABILITY_NONE },
        .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Arboliva"),
        .cryId = CRY_ARBOLIVA,
        .natDexNum = NATIONAL_DEX_ARBOLIVA,
        .categoryName = _("Olive"),
        .height = 14,
        .weight = 482,
        .description = COMPOUND_STRING(
            "This Pokémon drives back enemies\n"
            "by launching its rich, aromatic oil at\n"
            "them with enough force to smash a\n"
            "boulder."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Arboliva,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Arboliva,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Arboliva,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Arboliva,
        .shinyPalette = gMonShinyPalette_Arboliva,
        .iconSprite = gMonIcon_Arboliva,
        .iconPalIndex = 1,
        //FOOTPRINT(Arboliva)
        */
        //.levelUpLearnset = sArbolivaLevelUpLearnset,
        //.teachableLearnset = sArbolivaTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SMOLIV

//#if p_fAMILY_SQUAWKABILLY
    [SPECIES_SQUAWKABILLY_GREEN_PLUMAGE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              82,
              96,
              51,
              92,
              45,
              51
       ),
        MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE  },
        .abilityHidden = {ABILITY_GUTS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Sqawkabily"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Parrot"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "Green-feathered flocks hold the\n"
            "most sway. When they're out\n"
            "searching for food in the mornings and\n"
            "evenings, it gets very noisy."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Squawkabilly,
        
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        
        .palette = gMonPalette_SquawkabillyGreenPlumage,
        .shinyPalette = gMonShinyPalette_SquawkabillyGreenPlumage,
        .iconSprite = gMonIcon_SquawkabillyGreenPlumage,
        .iconPalIndex = 1,
        //FOOTPRINT(Squawkabilly)
        */
        //.levelUpLearnset = sSquawkabillyLevelUpLearnset,
        //.teachableLearnset = sSquawkabillyTeachableLearnset,
        //.formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_SQUAWKABILLY_BLUE_PLUMAGE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              82,
              96,
              51,
              92,
              45,
              51
       ),
        MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE },
        .abilityHidden = {ABILITY_GUTS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Sqawkabily"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Parrot"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "The largest of their flocks can\n"
            "contain more than 50 individuals. They\n"
            "fly around towns and forests,\n"
            "searching for food and making a racket."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Squawkabilly,
        
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        
        .palette = gMonPalette_SquawkabillyBluePlumage,
        .shinyPalette = gMonShinyPalette_SquawkabillyBluePlumage,
        .iconSprite = gMonIcon_SquawkabillyBluePlumage,
        .iconPalIndex = 0,
        //FOOTPRINT(Squawkabilly)
        */
        //.levelUpLearnset = sSquawkabillyLevelUpLearnset,
        //.teachableLearnset = sSquawkabillyTeachableLearnset,
        //.formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_SQUAWKABILLY_YELLOW_PLUMAGE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              82,
              96,
              51,
              92,
              45,
              51
       ),
        MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE },
        .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Sqawkabily"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Parrot"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "These Squawkabilly are hotheaded,\n"
            "and their fighting style is vicious.\n"
            "They'll leap within reach of their\n"
            "foes to engage in close combat."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Squawkabilly,
        
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        
        .palette = gMonPalette_SquawkabillyYellowPlumage,
        .shinyPalette = gMonShinyPalette_SquawkabillyYellowPlumage,
        .iconSprite = gMonIcon_SquawkabillyYellowPlumage,
        .iconPalIndex = 1,
        //FOOTPRINT(Squawkabilly)
        */
        //.levelUpLearnset = sSquawkabillyLevelUpLearnset,
        //.teachableLearnset = sSquawkabillyTeachableLearnset,
        //.formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_SQUAWKABILLY_WHITE_PLUMAGE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              82,
              96,
              51,
              92,
              45,
              51
       ),
        MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE },
        .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Sqawkabily"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Parrot"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "Though these Squawkabilly are the\n"
            "fewest in number, they have no\n"
            "trouble living in towns since they blend\n"
            "in with the white buildings."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Squawkabilly,
        
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        
        .palette = gMonPalette_SquawkabillyWhitePlumage,
        .shinyPalette = gMonShinyPalette_SquawkabillyWhitePlumage,
        .iconSprite = gMonIcon_SquawkabillyWhitePlumage,
        .iconPalIndex = 0,
        //FOOTPRINT(Squawkabilly)
        */
        //.levelUpLearnset = sSquawkabillyLevelUpLearnset,
        //.teachableLearnset = sSquawkabillyTeachableLearnset,
        //.formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SQUAWKABILLY

//#if p_fAMILY_NACLI
    [SPECIES_NACLI] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              55,
              55,
              75,
              25,
              35,
              35
       ),
        MON_TYPES(TYPE_ROCK),
        .catchRate = 255,
        .expYield = 56,
       // .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_PURIFYING_SALT, ABILITY_STURDY  },
        .abilityHidden = {ABILITY_CLEAR_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Nacli"),
        .cryId = CRY_NACLI,
        .natDexNum = NATIONAL_DEX_NACLI,
        .categoryName = _("Rock Salt"),
        .height = 4,
        .weight = 160,
        .description = COMPOUND_STRING(
            "The ground scrapes its body as it\n"
            "travels, causing it to leave salt\n"
            "behind. Salt is constantly being created\n"
            "and replenished inside Nacli's body."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Nacli,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_Nacli,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Nacli,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Nacli,
        .shinyPalette = gMonShinyPalette_Nacli,
        .iconSprite = gMonIcon_Nacli,
        .iconPalIndex = 2,
        //FOOTPRINT(Nacli)
        */
        //.levelUpLearnset = sNacliLevelUpLearnset,
        //.teachableLearnset = sNacliTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 24, 0,  SPECIES_NACLSTACK}),
      .enemyMonElevation = 0,
    },

    [SPECIES_NACLSTACK] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              60,
              60,
              100,
              35,
              35,
              65
       ),
        MON_TYPES(TYPE_ROCK),
        .catchRate = 120,
        .expYield = 124,
       // .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_PURIFYING_SALT, ABILITY_STURDY },
        .abilityHidden = {ABILITY_CLEAR_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Naclstack"),
        .cryId = CRY_NACLSTACK,
        .natDexNum = NATIONAL_DEX_NACLSTACK,
        .categoryName = _("Rock Salt"),
        .height = 6,
        .weight = 1050,
        .description = COMPOUND_STRING(
            "It compresses rock salt inside its\n"
            "body and shoots out hardened salt\n"
            "pellets with enough force to\n"
            "perforate an iron sheet."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Naclstack,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Naclstack,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Naclstack,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Naclstack,
        .shinyPalette = gMonShinyPalette_Naclstack,
        .iconSprite = gMonIcon_Naclstack,
        .iconPalIndex = 2,
        //FOOTPRINT(Naclstack)
        */
        //.levelUpLearnset = sNaclstackLevelUpLearnset,
        //.teachableLearnset = sNaclstackTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 38, 0,  SPECIES_GARGANACL}),
      .enemyMonElevation = 0,
    },

    [SPECIES_GARGANACL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              100,
              130,
              35,
              45,
              90
       ),
        MON_TYPES(TYPE_ROCK),
        .catchRate = 45,
        .expYield = 250,
       // .evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_PURIFYING_SALT, ABILITY_STURDY },
        .abilityHidden = {ABILITY_CLEAR_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Garganacl"),
        .cryId = CRY_GARGANACL,
        .natDexNum = NATIONAL_DEX_GARGANACL,
        .categoryName = _("Rock Salt"),
        .height = 23,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "Garganacl will rub its fingertips\n"
            "together and sprinkle injured\n"
            "Pokémon with salt. Even severe wounds will\n"
            "promptly heal afterward."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Garganacl,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Garganacl,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Garganacl,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Garganacl,
        .shinyPalette = gMonShinyPalette_Garganacl,
        .iconSprite = gMonIcon_Garganacl,
        .iconPalIndex = 2,
        //FOOTPRINT(Garganacl)
        */
        //.levelUpLearnset = sGarganaclLevelUpLearnset,
        //.teachableLearnset = sGarganaclTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_NACLI

//#if p_fAMILY_CHARCADET
    [SPECIES_CHARCADET] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              50,
              40,
              35,
              50,
              40
       ),
        MON_TYPES(TYPE_FIRE),
        .catchRate = 90,
        .expYield = 51,
       // .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE  },
        .abilityHidden = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Charcadet"),
        .cryId = CRY_CHARCADET,
        .natDexNum = NATIONAL_DEX_CHARCADET,
        .categoryName = _("Fire Child"),
        .height = 6,
        .weight = 105,
        .description = COMPOUND_STRING(
            "Burnt charcoal came to life and\n"
            "became a Pokémon. Possessing a fiery\n"
            "fighting spirit, Charcadet will\n"
            "battle even tough opponents."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Charcadet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_Charcadet,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Charcadet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Charcadet,
        .shinyPalette = gMonShinyPalette_Charcadet,
        .iconSprite = gMonIcon_Charcadet,
        .iconPalIndex = 0,
        //FOOTPRINT(Charcadet)
        */
        //.levelUpLearnset = sCharcadetLevelUpLearnset,
        //.teachableLearnset = sCharcadetTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_ITEM, 0/*ITEM_AUSPICIOUS_ARMOR*/, 0,  SPECIES_ARMAROUGE},
          //                      {EVO_ITEM, 0/*ITEM_MALICIOUS_ARMOR*/, 0,  SPECIES_CERULEDGE}),
      .enemyMonElevation = 0,
    },//vsonic

    [SPECIES_ARMAROUGE] =
    {
      //PIC_DATA(Armarouge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(Armarouge,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              85,
              60,
              100,
              75,
              125,
              80
       ),
        MON_TYPES(TYPE_FIRE, TYPE_PSYCHIC),
        .catchRate = 25,
        .expYield = 263,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 20,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE  },
        .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Armarouge"),
        .cryId = CRY_ARMAROUGE,
        .natDexNum = NATIONAL_DEX_ARMAROUGE,
        .categoryName = _("Fire Warrior"),
        .height = 15,
        .weight = 850,
        .description = COMPOUND_STRING(
            "Armarouge evolved through the use\n"
            "of a set of armor that belonged to\n"
            "a distinguished warrior. This\n"
            "Pokémon is incredibly loyal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Armarouge,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Armarouge,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Armarouge,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Armarouge,
        .shinyPalette = gMonShinyPalette_Armarouge,
        .iconSprite = gMonIcon_Armarouge,
        .iconPalIndex = 0,
        //FOOTPRINT(Armarouge)
        */
        //.levelUpLearnset = sArmarougeLevelUpLearnset,
        //.teachableLearnset = sArmarougeTeachableLearnset,
      .enemyMonElevation = 0,
    },

    [SPECIES_CERULEDGE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              75,
              125,
              80,
              85,
              60,
              100
       ),
        MON_TYPES(TYPE_FIRE, TYPE_GHOST),
        .catchRate = 25,
        .expYield = 263,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 20,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE },
        .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Ceruledge"),
        .cryId = CRY_CERULEDGE,
        .natDexNum = NATIONAL_DEX_CERULEDGE,
        .categoryName = _("Fire Blades"),
        .height = 16,
        .weight = 620,
        .description = COMPOUND_STRING(
            "The fiery blades on its arms burn\n"
            "fiercely with the lingering\n"
            "resentment of a sword wielder who fell\n"
            "before accomplishing their goal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Ceruledge,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Ceruledge,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Ceruledge,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Ceruledge,
        .shinyPalette = gMonShinyPalette_Ceruledge,
        .iconSprite = gMonIcon_Ceruledge,
        .iconPalIndex = 2,
        //FOOTPRINT(Ceruledge)
        */
        //.levelUpLearnset = sCeruledgeLevelUpLearnset,
        //.teachableLearnset = sCeruledgeTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_CHARCADET

//#if p_fAMILY_TADBULB
    [SPECIES_TADBULB] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              61,
              31,
              41,
              45,
              59,
              35
       ),
        MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 190,
        .expYield = 54,
       // .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_OWN_TEMPO, ABILITY_STATIC  },
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tadbulb"),
        .cryId = CRY_TADBULB,
        .natDexNum = NATIONAL_DEX_TADBULB,
        .categoryName = _("EleTadpole"),
        .height = 3,
        .weight = 4,
        .description = COMPOUND_STRING(
            "Tadbulb shakes its tail to\n"
            "generate electricity. If it senses danger,\n"
            "it will make its head blink on and off\n"
            "to alert its allies."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tadbulb,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Tadbulb,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 12,
        .backPic = gMonBackPic_Tadbulb,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tadbulb,
        .shinyPalette = gMonShinyPalette_Tadbulb,
        .iconSprite = gMonIcon_Tadbulb,
        .iconPalIndex = 0,
        //FOOTPRINT(Tadbulb)
        */
        //.levelUpLearnset = sTadbulbLevelUpLearnset,
        //.teachableLearnset = sTadbulbTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_ITEM, ITEM_THUNDER_STONE, 0,  SPECIES_BELLIBOLT}),
      .enemyMonElevation = 0,
    },

    [SPECIES_BELLIBOLT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              109,
              64,
              91,
              45,
              103,
              83
       ),
        MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 50,
        .expYield = 173,
       // .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_ELECTROMORPHOSIS, ABILITY_STATIC },
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Bellibolt"),
        .cryId = CRY_BELLIBOLT,
        .natDexNum = NATIONAL_DEX_BELLIBOLT,
        .categoryName = _("EleFrog"),
        .height = 12,
        .weight = 1130,
        .description = COMPOUND_STRING(
            "When this Pokémon expands and\n"
            "contracts its wobbly body, the belly-\n"
            "button dynamo in its stomach\n"
            "produces a huge amount of electricity."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bellibolt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Bellibolt,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Bellibolt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Bellibolt,
        .shinyPalette = gMonShinyPalette_Bellibolt,
        .iconSprite = gMonIcon_Bellibolt,
        .iconPalIndex = 0,
        //FOOTPRINT(Bellibolt)
        */
        //.levelUpLearnset = sBelliboltLevelUpLearnset,
        //.teachableLearnset = sBelliboltTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TADBULB

//#if p_fAMILY_WATTREL
    [SPECIES_WATTREL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              40,
              35,
              70,
              55,
              40
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_FLYING),
        .catchRate = 180,
        .expYield = 56,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FLYING),
        .abilities = { ABILITY_WIND_POWER, ABILITY_VOLT_ABSORB },
        .abilityHidden = {ABILITY_COMPETITIVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Wattrel"),
        .cryId = CRY_WATTREL,
        .natDexNum = NATIONAL_DEX_WATTREL,
        .categoryName = _("Storm Petrel"),
        .height = 4,
        .weight = 36,
        .description = COMPOUND_STRING(
            "When its wings catch the wind, the\n"
            "bones within produce electricity.\n"
            "This Pokémon dives into the ocean,\n"
            "catching prey by electrocuting them."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Wattrel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Wattrel,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Wattrel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Wattrel,
        .shinyPalette = gMonShinyPalette_Wattrel,
        .iconSprite = gMonIcon_Wattrel,
        .iconPalIndex = 0,
        //FOOTPRINT(Wattrel)
        */
        //.levelUpLearnset = sWattrelLevelUpLearnset,
        //.teachableLearnset = sWattrelTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 25, 0,  SPECIES_KILOWATTREL}),
      .enemyMonElevation = 0,
    },

    [SPECIES_KILOWATTREL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              70,
              60,
              125,
              105,
              60
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_FLYING),
        .catchRate = 90,
        .expYield = 172,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FLYING),
        .abilities = { ABILITY_WIND_POWER, ABILITY_VOLT_ABSORB },
        .abilityHidden = {ABILITY_COMPETITIVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Kilowatrel"),
        .cryId = CRY_KILOWATTREL,
        .natDexNum = NATIONAL_DEX_KILOWATTREL,
        .categoryName = _("Frigatebird"),
        .height = 14,
        .weight = 386,
        .description = COMPOUND_STRING(
            "It uses its throat sac to store\n"
            "electricity generated by its wings.\n"
            "There's hardly any oil in its feathers,\n"
            "so it is a poor swimmer."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Kilowattrel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Kilowattrel,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Kilowattrel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Kilowattrel,
        .shinyPalette = gMonShinyPalette_Kilowattrel,
        .iconSprite = gMonIcon_Kilowattrel,
        .iconPalIndex = 0,
        //FOOTPRINT(Kilowattrel)
        */
        //.levelUpLearnset = sKilowattrelLevelUpLearnset,
        //.teachableLearnset = sKilowattrelTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_WATTREL

//#if p_fAMILY_MASCHIFF
    [SPECIES_MASCHIFF] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              60,
              78,
              60,
              51,
              40,
              51
       ),
        MON_TYPES(TYPE_DARK),
        .catchRate = 150,
        .expYield = 68,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_RUN_AWAY  },
        .abilityHidden = {ABILITY_STAKEOUT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Maschiff"),
        .cryId = CRY_MASCHIFF,
        .natDexNum = NATIONAL_DEX_MASCHIFF,
        .categoryName = _("Rascal"),
        .height = 5,
        .weight = 160,
        .description = COMPOUND_STRING(
            "Its well-developed jaw and fangs\n"
            "are strong enough to crunch through\n"
            "boulders, and its thick fat makes\n"
            "for an excellent defense."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Maschiff,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_Maschiff,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Maschiff,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Maschiff,
        .shinyPalette = gMonShinyPalette_Maschiff,
        .iconSprite = gMonIcon_Maschiff,
        .iconPalIndex = 0,
        //FOOTPRINT(Maschiff)
        */
        //.levelUpLearnset = sMaschiffLevelUpLearnset,
        //.teachableLearnset = sMaschiffTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 30, 0,  SPECIES_MABOSSTIFF}),
      .enemyMonElevation = 0,
    },

    [SPECIES_MABOSSTIFF] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              80,
              120,
              90,
              85,
              60,
              70
       ),
        MON_TYPES(TYPE_DARK),
        .catchRate = 75,
        .expYield = 177,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_GUARD_DOG },
        .abilityHidden = {ABILITY_STAKEOUT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Mabosstiff"),
        .cryId = CRY_MABOSSTIFF,
        .natDexNum = NATIONAL_DEX_MABOSSTIFF,
        .categoryName = _("Boss"),
        .height = 11,
        .weight = 610,
        .description = COMPOUND_STRING(
            "Mabosstiff loves playing with\n"
            "children. Though usually gentle, it\n"
            "takes on an intimidating look when\n"
            "protecting its family."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Mabosstiff,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_Mabosstiff,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Mabosstiff,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Mabosstiff,
        .shinyPalette = gMonShinyPalette_Mabosstiff,
        .iconSprite = gMonIcon_Mabosstiff,
        .iconPalIndex = 0,
        //FOOTPRINT(Mabosstiff)
        */
        //.levelUpLearnset = sMabosstiffLevelUpLearnset,
        //.teachableLearnset = sMabosstiffTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_MASCHIFF

//#if p_fAMILY_SHROODLE
    [SPECIES_SHROODLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              65,
              35,
              75,
              40,
              35
       ),
        MON_TYPES(TYPE_POISON, TYPE_NORMAL),
        .catchRate = 190,
        .expYield = 58,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_UNBURDEN, ABILITY_PICKPOCKET  },
        .abilityHidden = {ABILITY_PRANKSTER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Shroodle"),
        .cryId = CRY_SHROODLE,
        .natDexNum = NATIONAL_DEX_SHROODLE,
        .categoryName = _("Toxic Mouse"),
        .height = 2,
        .weight = 7,
        .description = COMPOUND_STRING(
            "To keep enemies away from its\n"
            "territory, it paints markings around its\n"
            "nest using a poisonous liquid that\n"
            "has an acrid odor."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Shroodle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 17,
        .frontAnimFrames = sAnims_Shroodle,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Shroodle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Shroodle,
        .shinyPalette = gMonShinyPalette_Shroodle,
        .iconSprite = gMonIcon_Shroodle,
        .iconPalIndex = 0,
        //FOOTPRINT(Shroodle)
        */
        //.levelUpLearnset = sShroodleLevelUpLearnset,
        //.teachableLearnset = sShroodleTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 28, 0,  SPECIES_GRAFAIAI}),
      .enemyMonElevation = 0,
    },

    [SPECIES_GRAFAIAI] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              63,
              95,
              65,
              110,
              80,
              72
       ),
        MON_TYPES(TYPE_POISON, TYPE_NORMAL),
        .catchRate = 90,
        .expYield = 170,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_UNBURDEN, ABILITY_POISON_TOUCH },
        .abilityHidden = {ABILITY_PRANKSTER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Grafaiai"),
        .cryId = CRY_GRAFAIAI,
        .natDexNum = NATIONAL_DEX_GRAFAIAI,
        .categoryName = _("Toxic Monkey"),
        .height = 7,
        .weight = 272,
        .description = COMPOUND_STRING(
            "Each Grafaiai paints its own\n"
            "individual pattern, and it will paint that\n"
            "same pattern over and over again\n"
            "throughout its life."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Grafaiai,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_Grafaiai,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Grafaiai,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Grafaiai,
        .shinyPalette = gMonShinyPalette_Grafaiai,
        .iconSprite = gMonIcon_Grafaiai,
        .iconPalIndex = 0,
        //FOOTPRINT(Grafaiai)
        */
        //.levelUpLearnset = sGrafaiaiLevelUpLearnset,
        //.teachableLearnset = sGrafaiaiTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SHROODLE

//#if p_fAMILY_BRAMBLIN
    [SPECIES_BRAMBLIN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              65,
              30,
              60,
              45,
              35
       ),
        MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 190,
        .expYield = 55,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_WIND_RIDER, ABILITY_NONE  },
        .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Bramblin"),
        .cryId = CRY_BRAMBLIN,
        .natDexNum = NATIONAL_DEX_BRAMBLIN,
        .categoryName = _("Tumbleweed"),
        .height = 6,
        .weight = 6,
        .description = COMPOUND_STRING(
            "A soul unable to move on to the\n"
            "afterlife was blown around by the wind\n"
            "until it got tangled up with dried\n"
            "grass and became a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bramblin,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Bramblin,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Bramblin,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Bramblin,
        .shinyPalette = gMonShinyPalette_Bramblin,
        .iconSprite = gMonIcon_Bramblin,
        .iconPalIndex = 1,
        //FOOTPRINT(Bramblin)
        */
        //.levelUpLearnset = sBramblinLevelUpLearnset,
        //.teachableLearnset = sBramblinTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_NONE, 0, 0,  SPECIES_BRAMBLEGHAST}),
      .enemyMonElevation = 0,
    },

    [SPECIES_BRAMBLEGHAST] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              55,
              115,
              70,
              90,
              80,
              70
       ),
        MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 168,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_WIND_RIDER, ABILITY_NONE },
        .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Brmblghast"),
        .cryId = CRY_BRAMBLEGHAST,
        .natDexNum = NATIONAL_DEX_BRAMBLEGHAST,
        .categoryName = _("Tumbleweed"),
        .height = 12,
        .weight = 60,
        .description = COMPOUND_STRING(
            "It will open the branches of its\n"
            "head to envelop its prey. Once it\n"
            "absorbs all the life energy it needs, it\n"
            "expels the prey and discards it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Brambleghast,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Brambleghast,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Brambleghast,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Brambleghast,
        .shinyPalette = gMonShinyPalette_Brambleghast,
        .iconSprite = gMonIcon_Brambleghast,
        .iconPalIndex = 2,
        //FOOTPRINT(Brambleghast)
        */
        //.levelUpLearnset = sBrambleghastLevelUpLearnset,
        //.teachableLearnset = sBrambleghastTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_BRAMBLIN

//#if p_fAMILY_TOEDSCOOL
    [SPECIES_TOEDSCOOL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              40,
              35,
              70,
              50,
              100
       ),
        MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 190,
        .expYield = 67,
       // .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_MYCELIUM_MIGHT, ABILITY_NONE  },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,//ability makes go last in priority but ignore ability negates
        /*.speciesName = _("Toedscool"), //boost further by making ignore ability type checks
        .cryId = CRY_TOEDSCOOL, //will need to add ability jumps in script
        .natDexNum = NATIONAL_DEX_TOEDSCOOL, //vsonic
        .categoryName = _("Woodear"),
        .height = 9,
        .weight = 330,
        .description = COMPOUND_STRING(
            "Though it looks like Tentacool,\n"
            "Toedscool is a completely different\n"
            "species. Its legs may be thin, but it\n"
            "can run at a speed of 30 mph."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Toedscool,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Toedscool,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Toedscool,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Toedscool,
        .shinyPalette = gMonShinyPalette_Toedscool,
        .iconSprite = gMonIcon_Toedscool,
        .iconPalIndex = 0,
        //FOOTPRINT(Toedscool)
        */
        //.levelUpLearnset = sToedscoolLevelUpLearnset,
        //.teachableLearnset = sToedscoolTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 30, 0,  SPECIES_TOEDSCRUEL}),
      .enemyMonElevation = 0,
    },

    [SPECIES_TOEDSCRUEL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              80,
              70,
              65,
              100,
              80,
              120
       ),
        MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 90,
        .expYield = 180,
       // .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_MYCELIUM_MIGHT, ABILITY_NONE  },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Toedscruel"),
        .cryId = CRY_TOEDSCRUEL,
        .natDexNum = NATIONAL_DEX_TOEDSCRUEL,
        .categoryName = _("Woodear"),
        .height = 19,
        .weight = 580,
        .description = COMPOUND_STRING(
            "These Pokémon gather into groups\n"
            "and form colonies deep within\n"
            "forests. They absolutely hate it when\n"
            "strangers approach."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Toedscruel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Toedscruel,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Toedscruel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Toedscruel,
        .shinyPalette = gMonShinyPalette_Toedscruel,
        .iconSprite = gMonIcon_Toedscruel,
        .iconPalIndex = 0,
        //FOOTPRINT(Toedscruel)
        */
        //.levelUpLearnset = sToedscruelLevelUpLearnset,
        //.teachableLearnset = sToedscruelTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TOEDSCOOL

//#if p_fAMILY_KLAWF
    [SPECIES_KLAWF] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              100,
              115,
              75,
              35,
              55
       ),
        MON_TYPES(TYPE_ROCK),
        .catchRate = 120,
        .expYield = 158,
       // .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_ANGER_SHELL, ABILITY_SHELL_ARMOR  },
        .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Klawf"),
        .cryId = CRY_KLAWF,
        .natDexNum = NATIONAL_DEX_KLAWF,
        .categoryName = _("Ambush"),
        .height = 13,
        .weight = 790,
        .description = COMPOUND_STRING(
            "Klawf hangs upside-down from\n"
            "cliffs, waiting for prey. But Klawf can't\n"
            "remain in this position for long\n"
            "because its blood rushes to its head."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Klawf,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_Klawf,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Klawf,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 20,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Klawf,
        .shinyPalette = gMonShinyPalette_Klawf,
        .iconSprite = gMonIcon_Klawf,
        .iconPalIndex = 0,
        //FOOTPRINT(Klawf)
        */
        //.levelUpLearnset = sKlawfLevelUpLearnset,
        //.teachableLearnset = sKlawfTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_KLAWF

//#if p_fAMILY_CAPSAKID
    [SPECIES_CAPSAKID] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              50,
              62,
              40,
              50,
              62,
              40
       ),
        MON_TYPES(TYPE_GRASS),
        .catchRate = 190,
        .expYield = 61,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_INSOMNIA  },
        .abilityHidden = {ABILITY_KLUTZ, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Capsakid"),
        .cryId = CRY_CAPSAKID,
        .natDexNum = NATIONAL_DEX_CAPSAKID,
        .categoryName = _("Spicy Pepper"),
        .height = 3,
        .weight = 30,
        .description = COMPOUND_STRING(
            "The more sunlight this Pokémon\n"
            "bathes in, the more spicy chemicals are\n"
            "produced by its body, and thus the\n"
            "spicier its moves become."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Capsakid,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Capsakid,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Capsakid,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Capsakid,
        .shinyPalette = gMonShinyPalette_Capsakid,
        .iconSprite = gMonIcon_Capsakid,
        .iconPalIndex = 1,
        //FOOTPRINT(Capsakid)
        */
        //.levelUpLearnset = sCapsakidLevelUpLearnset,
        //.teachableLearnset = sCapsakidTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_ITEM, ITEM_FIRE_STONE, 0,  SPECIES_SCOVILLAIN}),
      .enemyMonElevation = 0,
    },

    [SPECIES_SCOVILLAIN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              65,
              108,
              65,
              75,
              108,
              65
       ),
        MON_TYPES(TYPE_GRASS, TYPE_FIRE),
        .catchRate = 75,
        .expYield = 170,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_INSOMNIA  },
        .abilityHidden = {ABILITY_MOODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Scovillain"),
        .cryId = CRY_SCOVILLAIN,
        .natDexNum = NATIONAL_DEX_SCOVILLAIN,
        .categoryName = _("Spicy Pepper"),
        .height = 9,
        .weight = 150,
        .description = COMPOUND_STRING(
            "The green head has turned vicious\n"
            "due to the spicy chemicals\n"
            "stimulating its brain. Once it goes on a\n"
            "rampage, there is no stopping it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Scovillain,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Scovillain,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Scovillain,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Scovillain,
        .shinyPalette = gMonShinyPalette_Scovillain,
        .iconSprite = gMonIcon_Scovillain,
        .iconPalIndex = 1,
        //FOOTPRINT(Scovillain)
        */
        //.levelUpLearnset = sScovillainLevelUpLearnset,
        //.teachableLearnset = sScovillainTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_CAPSAKID

//#if p_fAMILY_RELLOR
    [SPECIES_RELLOR] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              41,
              50,
              60,
              30,
              31,
              58
       ),
        MON_TYPES(TYPE_BUG),
        .catchRate = 190,
        .expYield = 54,
       // .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_FAST,
        MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_COMPOUND_EYES, ABILITY_NONE  },
        .abilityHidden = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Rellor"),
        .cryId = CRY_RELLOR,
        .natDexNum = NATIONAL_DEX_RELLOR,
        .categoryName = _("Rolling"),
        .height = 2,
        .weight = 10,
        .description = COMPOUND_STRING(
            "This Pokémon creates a mud ball by\n"
            "mixing sand and dirt with psychic\n"
            "energy. It treasures its mud ball more\n"
            "than its own life."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Rellor,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 17,
        .frontAnimFrames = sAnims_Rellor,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Rellor,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Rellor,
        .shinyPalette = gMonShinyPalette_Rellor,
        .iconSprite = gMonIcon_Rellor,
        .iconPalIndex = 0,
        //FOOTPRINT(Rellor)
        */
        //.levelUpLearnset = sRellorLevelUpLearnset,
        //.teachableLearnset = sRellorTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_NONE, 0, 0,  SPECIES_RABSCA}),
      .enemyMonElevation = 0,
    },

    [SPECIES_RABSCA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              75,
              50,
              85,
              45,
              115,
              100
       ),
        MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),
        .catchRate = 45,
        .expYield = 165,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_FAST,
        MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SYNCHRONIZE, ABILITY_NONE  },
        .abilityHidden = {ABILITY_TELEPATHY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Rabsca"),
        .cryId = CRY_RABSCA,
        .natDexNum = NATIONAL_DEX_RABSCA,
        .categoryName = _("Rolling"),
        .height = 3,
        .weight = 35,
        .description = COMPOUND_STRING(
            "The body that supports the ball\n"
            "barely moves. Therefore, it is thought\n"
            "that the true body of this Pokémon\n"
            "is actually inside the ball."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Rabsca,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Rabsca,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Rabsca,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Rabsca,
        .shinyPalette = gMonShinyPalette_Rabsca,
        .iconSprite = gMonIcon_Rabsca,
        .iconPalIndex = 0,
        //FOOTPRINT(Rabsca)
        */
        //.levelUpLearnset = sRabscaLevelUpLearnset,
        //.teachableLearnset = sRabscaTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_RELLOR

//#if p_fAMILY_FLITTLE
    [SPECIES_FLITTLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              30,
              35,
              30,
              75,
              55,
              30
       ),
        MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 120,
        .expYield = 51,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_ANTICIPATION, ABILITY_FRISK  },
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Flittle"),
        .cryId = CRY_FLITTLE,
        .natDexNum = NATIONAL_DEX_FLITTLE,
        .categoryName = _("Frill"),
        .height = 2,
        .weight = 15,
        .description = COMPOUND_STRING(
            "Flittle's toes levitate about half\n"
            "an inch above the ground because of\n"
            "the psychic power emitted from the\n"
            "frills on the Pokémon's belly."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Flittle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_Flittle,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Flittle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Flittle,
        .shinyPalette = gMonShinyPalette_Flittle,
        .iconSprite = gMonIcon_Flittle,
        .iconPalIndex = 1,
        //FOOTPRINT(Flittle)
        */
        //.levelUpLearnset = sFlittleLevelUpLearnset,
        //.teachableLearnset = sFlittleTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 35, 0,  SPECIES_ESPATHRA}),
      .enemyMonElevation = 0,
    },

    [SPECIES_ESPATHRA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              95,
              60,
              60,
              105,
              101,
              60
       ),
        MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 60,
        .expYield = 168,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_OPPORTUNIST, ABILITY_FRISK},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Espathra"),
        .cryId = CRY_ESPATHRA,
        .natDexNum = NATIONAL_DEX_ESPATHRA,
        .categoryName = _("Ostrich"),
        .height = 19,
        .weight = 900,
        .description = COMPOUND_STRING(
            "It immobilizes opponents by\n"
            "bathing them in psychic power from its\n"
            "large eyes. Despite its appearance, it\n"
            "has a vicious temperament."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Espathra,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Espathra,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Espathra,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Espathra,
        .shinyPalette = gMonShinyPalette_Espathra,
        .iconSprite = gMonIcon_Espathra,
        .iconPalIndex = 0,
        //FOOTPRINT(Espathra)
        */
        //.levelUpLearnset = sEspathraLevelUpLearnset,
        //.teachableLearnset = sEspathraTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FLITTLE

//#if p_fAMILY_TINKATINK
    [SPECIES_TINKATINK] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              50,
              45,
              45,
              58,
              35,
              64
       ),
        MON_TYPES(TYPE_FAIRY, TYPE_STEEL),
        .catchRate = 190,
        .expYield = 59,
       // .evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_OWN_TEMPO  },
        .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tinkatink"),
        .cryId = CRY_TINKATINK,
        .natDexNum = NATIONAL_DEX_TINKATINK,
        .categoryName = _("Metalsmith"),
        .height = 4,
        .weight = 89,
        .description = COMPOUND_STRING(
            "This Pokémon pounds iron scraps\n"
            "together to make a hammer. It will\n"
            "remake the hammer again and again until\n"
            "it's satisfied with the result."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tinkatink,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Tinkatink,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tinkatink,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tinkatink,
        .shinyPalette = gMonShinyPalette_Tinkatink,
        .iconSprite = gMonIcon_Tinkatink,
        .iconPalIndex = 1,
        //FOOTPRINT(Tinkatink)
        */
        //.levelUpLearnset = sTinkatinkLevelUpLearnset,
        //.teachableLearnset = sTinkatinkTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 24, 0,  SPECIES_TINKATUFF}),
      .enemyMonElevation = 0,
    },

    [SPECIES_TINKATUFF] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              65,
              55,
              55,
              78,
              45,
              82
       ),
        MON_TYPES(TYPE_FAIRY, TYPE_STEEL),
        .catchRate = 90,
        .expYield = 133,
       // .evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_OWN_TEMPO },
        .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tinkatuff"),
        .cryId = CRY_TINKATUFF,
        .natDexNum = NATIONAL_DEX_TINKATUFF,
        .categoryName = _("Hammer"),
        .height = 7,
        .weight = 591,
        .description = COMPOUND_STRING(
            "These Pokémon make their homes in\n"
            "piles of scrap metal. They test the\n"
            "strength of each other's hammers by\n"
            "smashing them together."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tinkatuff,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_Tinkatuff,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tinkatuff,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tinkatuff,
        .shinyPalette = gMonShinyPalette_Tinkatuff,
        .iconSprite = gMonIcon_Tinkatuff,
        .iconPalIndex = 1,
        //FOOTPRINT(Tinkatuff)
        */
        //.levelUpLearnset = sTinkatuffLevelUpLearnset,
        //.teachableLearnset = sTinkatuffTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 38, 0,  SPECIES_TINKATON}),
      .enemyMonElevation = 0,
    },

    [SPECIES_TINKATON] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              85,
              75,
              77,
              94,
              70,
              105
       ),
        MON_TYPES(TYPE_FAIRY, TYPE_STEEL),
        .catchRate = 45,
        .expYield = 253,
       // .evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_OWN_TEMPO  },
        .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tinkaton"),
        .cryId = CRY_TINKATON,
        .natDexNum = NATIONAL_DEX_TINKATON,
        .categoryName = _("Hammer"),
        .height = 7,
        .weight = 1128,
        .description = COMPOUND_STRING(
            "The hammer tops 220 pounds, yet it\n"
            "gets swung around easily by\n"
            "Tinkaton as it steals whatever it pleases\n"
            "and carries its plunder back home."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tinkaton,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Tinkaton,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tinkaton,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tinkaton,
        .shinyPalette = gMonShinyPalette_Tinkaton,
        .iconSprite = gMonIcon_Tinkaton,
        .iconPalIndex = 1,
        //FOOTPRINT(Tinkaton)
        */
        //.levelUpLearnset = sTinkatonLevelUpLearnset,
        //.teachableLearnset = sTinkatonTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TINKATINK

//#if p_fAMILY_WIGLETT
    [SPECIES_WIGLETT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              10,
              55,
              25,
              95,
              35,
              25
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 255,
        .expYield = 49,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_GOOEY, ABILITY_RATTLED  },
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Wiglett"),
        .cryId = CRY_WIGLETT,
        .natDexNum = NATIONAL_DEX_WIGLETT,
        .categoryName = _("Garden Eel"),
        .height = 12,
        .weight = 18,
        .description = COMPOUND_STRING(
            "This Pokémon can pick up the scent\n"
            "of a Veluza just over 65 feet away\n"
            "and will hide itself in the sand."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Wiglett,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Wiglett,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Wiglett,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Wiglett,
        .shinyPalette = gMonShinyPalette_Wiglett,
        .iconSprite = gMonIcon_Wiglett,
        .iconPalIndex = 0,
        //FOOTPRINT(Wiglett)
        */
        //.levelUpLearnset = sWiglettLevelUpLearnset,
        //.teachableLearnset = sWiglettTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 26, 0,  SPECIES_WUGTRIO}),
      .enemyMonElevation = 0,
    },

    [SPECIES_WUGTRIO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              35,
              100,
              50,
              120,
              50,
              70
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 50,
        .expYield = 149,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_GOOEY, ABILITY_RATTLED },
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Wugtrio"),
        .cryId = CRY_WUGTRIO,
        .natDexNum = NATIONAL_DEX_WUGTRIO,
        .categoryName = _("Garden Eel"),
        .height = 12,
        .weight = 54,
        .description = COMPOUND_STRING(
            "A variety of fish Pokémon, Wugtrio\n"
            "was once considered to be a\n"
            "regional form of Dugtrio."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Wugtrio,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Wugtrio,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Wugtrio,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Wugtrio,
        .shinyPalette = gMonShinyPalette_Wugtrio,
        .iconSprite = gMonIcon_Wugtrio,
        .iconPalIndex = 0,
        //FOOTPRINT(Wugtrio)
        */
        //.levelUpLearnset = sWugtrioLevelUpLearnset,
        //.teachableLearnset = sWugtrioTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_WIGLETT

//#if p_fAMILY_BOMBIRDIER
    [SPECIES_BOMBIRDIER] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              103,
              85,
              82,
              60,
              85
       ),
        MON_TYPES(TYPE_FLYING, TYPE_DARK),
        .catchRate = 25,
        .expYield = 243,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_BIG_PECKS, ABILITY_KEEN_EYE  },
        .abilityHidden = {ABILITY_ROCKY_PAYLOAD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Bombirdier"),
        .cryId = CRY_BOMBIRDIER,
        .natDexNum = NATIONAL_DEX_BOMBIRDIER,
        .categoryName = _("Item Drop"),
        .height = 15,
        .weight = 429,
        .description = COMPOUND_STRING(
            "Bombirdier uses the apron on its\n"
            "chest to bundle up food, which it\n"
            "carries back to its nest. It enjoys\n"
            "dropping things that make loud noises."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bombirdier,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Bombirdier,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_Bombirdier,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Bombirdier,
        .shinyPalette = gMonShinyPalette_Bombirdier,
        .iconSprite = gMonIcon_Bombirdier,
        .iconPalIndex = 0,
        //FOOTPRINT(Bombirdier)
        */
        //.levelUpLearnset = sBombirdierLevelUpLearnset,
        //.teachableLearnset = sBombirdierTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_BOMBIRDIER

//#if p_fAMILY_FINIZEN
    [SPECIES_FINIZEN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              45,
              40,
              75,
              45,
              40
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 200,
        .expYield = 63,
       // .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_2),
        .abilities = { ABILITY_WATER_VEIL, ABILITY_NONE  },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Finizen"),
        .cryId = CRY_FINIZEN,
        .natDexNum = NATIONAL_DEX_FINIZEN,
        .categoryName = _("Dolphin"),
        .height = 13,
        .weight = 602,
        .description = COMPOUND_STRING(
            "Its water ring is made from\n"
            "seawater mixed with a sticky fluid that\n"
            "Finizen secretes from its blowhole."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Finizen,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Finizen,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Finizen,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Finizen,
        .shinyPalette = gMonShinyPalette_Finizen,
        .iconSprite = gMonIcon_Finizen,
        .iconPalIndex = 0,
        //FOOTPRINT(Finizen)
        */
        //.levelUpLearnset = sFinizenLevelUpLearnset,
        //.teachableLearnset = sFinizenTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 38, 0,  SPECIES_PALAFIN_ZERO}),
      .enemyMonElevation = 0,
    },

    [SPECIES_PALAFIN_ZERO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              70,
              72,
              100,
              53,
              62
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 160,
       // .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_2),
        .abilities = { ABILITY_ZERO_TO_HERO, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Palafin"),
        .cryId = CRY_PALAFIN_ZERO,
        .natDexNum = NATIONAL_DEX_PALAFIN,
        .categoryName = _("Dolphin"),
        .height = 13,
        .weight = 602,
        .description = COMPOUND_STRING(
            "This Pokémon changes its\n"
            "appearance if it hears its allies calling for\n"
            "help. Palafin will never show\n"
            "anybody its moment of transformation."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PalafinZero,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Palafin,
        
        .backPic = gMonBackPic_PalafinZero,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_PalafinZero,
        .shinyPalette = gMonShinyPalette_PalafinZero,
        .iconSprite = gMonIcon_PalafinZero,
        .iconPalIndex = 0,
        //FOOTPRINT(Palafin)
        */
        //.levelUpLearnset = sPalafinLevelUpLearnset,
        //.teachableLearnset = sPalafinTeachableLearnset,
        //.formSpeciesIdTable = sPalafinFormSpeciesIdTable,
        //.formChangeTable = sPalafinZeroFormChangeTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_PALAFIN_HERO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              160,
              97,
              100,
              106,
              87
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 228,
       // .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_2),
        .abilities = { ABILITY_ZERO_TO_HERO, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Palafin"),
        .cryId = CRY_PALAFIN_HERO,
        .natDexNum = NATIONAL_DEX_PALAFIN,
        .categoryName = _("Hero"),
        .height = 18,
        .weight = 974,
        .description = COMPOUND_STRING(
            "This Pokémon's ancient genes have\n"
            "awakened. It is now so\n"
            "extraordinarily strong that it can easily lift a\n"
            "cruise ship with one fin."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PalafinHero,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Palafin,
        
        .backPic = gMonBackPic_PalafinHero,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_PalafinHero,
        .shinyPalette = gMonShinyPalette_PalafinHero,
        .iconSprite = gMonIcon_PalafinHero,
        .iconPalIndex = 0,
        //FOOTPRINT(Palafin)
        */
        //.levelUpLearnset = sPalafinLevelUpLearnset,
        //.teachableLearnset = sPalafinTeachableLearnset,
        //.formSpeciesIdTable = sPalafinFormSpeciesIdTable,
        //.formChangeTable = sPalafinZeroFormChangeTable,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FINIZEN

//#if p_fAMILY_VAROOM
    [SPECIES_VAROOM] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              45,
              70,
              63,
              47,
              30,
              45
       ),
        MON_TYPES(TYPE_STEEL, TYPE_POISON),
        .catchRate = 190,
        .expYield = 60,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_OVERCOAT, ABILITY_NONE  },
        .abilityHidden = {ABILITY_SLOW_START, ABILITY_SPEED_BOOST},
        //.floating = TRUE,
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        /*.speciesName = _("Varoom"), //why on god's earth did pokemon decide to give another mon slowstart??
        .cryId = CRY_VAROOM,
        .natDexNum = NATIONAL_DEX_VAROOM,
        .categoryName = _("Single-Cyl"),
        .height = 10,
        .weight = 350,
        .description = COMPOUND_STRING(
            "The steel section is Varoom's\n"
            "actual body. This Pokémon clings to\n"
            "rocks and converts the minerals within\n"
            "into energy to fuel its activities."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Varoom,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_Varoom,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Varoom,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Varoom,
        .shinyPalette = gMonShinyPalette_Varoom,
        .iconSprite = gMonIcon_Varoom,
        .iconPalIndex = 2,
        //FOOTPRINT(Varoom)
        */
        //.levelUpLearnset = sVaroomLevelUpLearnset,
        //.teachableLearnset = sVaroomTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 40, 0,  SPECIES_REVAVROOM}),
      .enemyMonElevation = 0,
    },

    [SPECIES_REVAVROOM] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              80,
              119,
              90,
              90,
              54,
              67
       ),
        MON_TYPES(TYPE_STEEL, TYPE_POISON),
        .catchRate = 75,
        .expYield = 175,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_OVERCOAT, ABILITY_NONE },
        .abilityHidden = {ABILITY_FILTER, ABILITY_SPEED_BOOST},
        //.floating = TRUE,
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        /*.speciesName = _("Revavroom"),
        .cryId = CRY_REVAVROOM,
        .natDexNum = NATIONAL_DEX_REVAVROOM,
        .categoryName = _("Multi-Cyl"),
        .height = 18,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "It creates a gas out of poison and\n"
            "minerals from rocks. It then\n"
            "detonates the gas in its cylinders- now\n"
            "numbering eight-to generate energy."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Revavroom,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_Revavroom,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Revavroom,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Revavroom,
        .shinyPalette = gMonShinyPalette_Revavroom,
        .iconSprite = gMonIcon_Revavroom,
        .iconPalIndex = 0,
        //FOOTPRINT(Revavroom)
        */
        //.levelUpLearnset = sRevavroomLevelUpLearnset,
        //.teachableLearnset = sRevavroomTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_VAROOM

//#if p_fAMILY_CYCLIZAR
    [SPECIES_CYCLIZAR] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              95,
              65,
              121,
              85,
              65
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_NORMAL),
        .catchRate = 190,
        .expYield = 175,
       // .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SHED_SKIN, ABILITY_NONE  },
        .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Cyclizar"),
        .cryId = CRY_CYCLIZAR,
        .natDexNum = NATIONAL_DEX_CYCLIZAR,
        .categoryName = _("Mount"),
        .height = 16,
        .weight = 630,
        .description = COMPOUND_STRING(
            "It can sprint at over 70 mph while\n"
            "carrying a human. The rider's body\n"
            "heat warms Cyclizar's back and lifts\n"
            "the Pokémon's spirit."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cyclizar,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Cyclizar,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cyclizar,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cyclizar,
        .shinyPalette = gMonShinyPalette_Cyclizar,
        .iconSprite = gMonIcon_Cyclizar,
        .iconPalIndex = 1,
        //FOOTPRINT(Cyclizar)
        */
        //.levelUpLearnset = sCyclizarLevelUpLearnset,
        //.teachableLearnset = sCyclizarTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_CYCLIZAR

//#if p_fAMILY_ORTHWORM
    [SPECIES_ORTHWORM] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              70,
              85,
              145,
              65,
              60,
              55
       ),
        MON_TYPES(TYPE_STEEL),
        .catchRate = 25,
        .expYield = 240,
       // .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_EARTH_EATER, ABILITY_NONE  },
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Orthworm"),
        .cryId = CRY_ORTHWORM,
        .natDexNum = NATIONAL_DEX_ORTHWORM,
        .categoryName = _("Earthworm"),
        .height = 25,
        .weight = 3100,
        .description = COMPOUND_STRING(
            "When attacked, this Pokémon will\n"
            "wield the tendrils on its body like\n"
            "fists and pelt the opponent with a\n"
            "storm of punches."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Orthworm,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Orthworm,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Orthworm,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Orthworm,
        .shinyPalette = gMonShinyPalette_Orthworm,
        .iconSprite = gMonIcon_Orthworm,
        .iconPalIndex = 0,
        //FOOTPRINT(Orthworm)
        */
        //.levelUpLearnset = sOrthwormLevelUpLearnset,
        //.teachableLearnset = sOrthwormTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_ORTHWORM

//#if p_fAMILY_GLIMMET
    [SPECIES_GLIMMET] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
        48,
        35,
        42,
        60,
        105,
        60
       ),
        MON_TYPES(TYPE_ROCK, TYPE_POISON),
        .catchRate = 70,
        .expYield = 70,
       // .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_TOXIC_DEBRIS, ABILITY_NONE  },
        .abilityHidden = {ABILITY_CORROSION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Glimmet"),
        .cryId = CRY_GLIMMET,
        .natDexNum = NATIONAL_DEX_GLIMMET,
        .categoryName = _("Ore"),
        .height = 7,
        .weight = 80,
        .description = COMPOUND_STRING(
            "Glimmet's toxic mineral crystals\n"
            "look just like flower petals. This\n"
            "Pokémon scatters poisonous powder like\n"
            "pollen to protect itself."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Glimmet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 16,
        .frontAnimFrames = sAnims_Glimmet,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 11,
        .backPic = gMonBackPic_Glimmet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Glimmet,
        .shinyPalette = gMonShinyPalette_Glimmet,
        .iconSprite = gMonIcon_Glimmet,
        .iconPalIndex = 0,
        //FOOTPRINT(Glimmet)
        */
        //.levelUpLearnset = sGlimmetLevelUpLearnset,
        //.teachableLearnset = sGlimmetTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 35, 0,  SPECIES_GLIMMORA}),
      .enemyMonElevation = 0,
    },

    [SPECIES_GLIMMORA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              83,
              55,
              90,
              86,
              130,
              81
       ),
        MON_TYPES(TYPE_ROCK, TYPE_POISON),
        .catchRate = 25,
        .expYield = 184,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_TOXIC_DEBRIS, ABILITY_NONE},
        .abilityHidden = {ABILITY_CORROSION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Glimmora"),
        .cryId = CRY_GLIMMORA,
        .natDexNum = NATIONAL_DEX_GLIMMORA,
        .categoryName = _("Ore"),
        .height = 15,
        .weight = 450,
        .description = COMPOUND_STRING(
            "Glimmora's petals are made of\n"
            "crystallized poison energy. It has\n"
            "recently become evident that these\n"
            "petals resemble Tera Jewels."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Glimmora,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Glimmora,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_Glimmora,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Glimmora,
        .shinyPalette = gMonShinyPalette_Glimmora,
        .iconSprite = gMonIcon_Glimmora,
        .iconPalIndex = 0,
        //FOOTPRINT(Glimmora)
        */
        //.levelUpLearnset = sGlimmoraLevelUpLearnset,
        //.teachableLearnset = sGlimmoraTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_GLIMMET

//#if p_fAMILY_GREAVARD
    [SPECIES_GREAVARD] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              50,
              61,
              60,
              34,
              30,
              55
       ),
        MON_TYPES(TYPE_GHOST),//think may make normal ghost
        .catchRate = 120,
        .expYield = 58,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_PICKUP, ABILITY_NONE  },
        .abilityHidden = {ABILITY_FLUFFY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Greavard"),
        .cryId = CRY_GREAVARD,
        .natDexNum = NATIONAL_DEX_GREAVARD,
        .categoryName = _("Ghost Dog"),
        .height = 6,
        .weight = 350,
        .description = COMPOUND_STRING(
            "This friendly Pokémon doesn't like\n"
            "being alone. Pay it even the\n"
            "slightest bit of attention, and it will\n"
            "follow you forever."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Greavard,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Greavard,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Greavard,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Greavard,
        .shinyPalette = gMonShinyPalette_Greavard,
        .iconSprite = gMonIcon_Greavard,
        .iconPalIndex = 0,
        //FOOTPRINT(Greavard)
        */
        //.levelUpLearnset = sGreavardLevelUpLearnset,
        //.teachableLearnset = sGreavardTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL_NIGHT, 30, 0,  SPECIES_HOUNDSTONE}),
      .enemyMonElevation = 0,
    },

    [SPECIES_HOUNDSTONE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              72,
              101,
              100,
              68,
              50,
              97
       ),
        MON_TYPES(TYPE_GHOST),
        .catchRate = 60,
        .expYield = 171,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SAND_RUSH, ABILITY_NONE},
        .abilityHidden = {ABILITY_FLUFFY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Houndstone"),
        .cryId = CRY_HOUNDSTONE,
        .natDexNum = NATIONAL_DEX_HOUNDSTONE,
        .categoryName = _("Ghost Dog"),
        .height = 20,
        .weight = 150,
        .description = COMPOUND_STRING(
            "Houndstone spends most of its\n"
            "time sleeping in graveyards. Among all\n"
            "the dog Pokémon, this one is most\n"
            "loyal to its master."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Houndstone,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Houndstone,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Houndstone,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Houndstone,
        .shinyPalette = gMonShinyPalette_Houndstone,
        .iconSprite = gMonIcon_Houndstone,
        .iconPalIndex = 2,
        //FOOTPRINT(Houndstone)
        */
        //.levelUpLearnset = sHoundstoneLevelUpLearnset,
        //.teachableLearnset = sHoundstoneTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_GREAVARD

//#if p_fAMILY_FLAMIGO
    [SPECIES_FLAMIGO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              82,
              115,
              74,
              90,
              75,
              64
       ),
        MON_TYPES(TYPE_FLYING, TYPE_FIGHTING),
        .catchRate = 100,
        .expYield = 175,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_SCRAPPY, ABILITY_TANGLED_FEET  },
        .abilityHidden = {ABILITY_COSTAR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Flamigo"),
        .cryId = CRY_FLAMIGO,
        .natDexNum = NATIONAL_DEX_FLAMIGO,
        .categoryName = _("Synchronize"),
        .height = 16,
        .weight = 370,
        .description = COMPOUND_STRING(
            "Thanks to a behavior of theirs\n"
            "known as “synchronizing,” an entire\n"
            "flock of these Pokémon can attack\n"
            "simultaneously in perfect harmony."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Flamigo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Flamigo,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Flamigo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Flamigo,
        .shinyPalette = gMonShinyPalette_Flamigo,
        .iconSprite = gMonIcon_Flamigo,
        .iconPalIndex = 1,
        //FOOTPRINT(Flamigo)
        */
        //.levelUpLearnset = sFlamigoLevelUpLearnset,
        //.teachableLearnset = sFlamigoTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FLAMIGO

//#if p_fAMILY_CETODDLE
    [SPECIES_CETODDLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              108,
              68,
              45,
              43,
              30,
              40
       ),
        MON_TYPES(TYPE_ICE),
        .catchRate = 150,
        .expYield = 67,
       // .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SNOW_CLOAK  },
        .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Cetoddle"),
        .cryId = CRY_CETODDLE,
        .natDexNum = NATIONAL_DEX_CETODDLE,
        .categoryName = _("Terra Whale"),
        .height = 12,
        .weight = 450,
        .description = COMPOUND_STRING(
            "This species left the ocean and\n"
            "began living on land a very long time\n"
            "ago. It seems to be closely related\n"
            "to Wailmer."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cetoddle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_Cetoddle,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cetoddle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cetoddle,
        .shinyPalette = gMonShinyPalette_Cetoddle,
        .iconSprite = gMonIcon_Cetoddle,
        .iconPalIndex = 0,
        //FOOTPRINT(Cetoddle)
        */
        //.levelUpLearnset = sCetoddleLevelUpLearnset,
        //.teachableLearnset = sCetoddleTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_ITEM, ITEM_ICE_STONE, 0,  SPECIES_CETITAN}),
      .enemyMonElevation = 0,
    },

    [SPECIES_CETITAN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              170,
              113,
              65,
              73,
              45,
              55
       ),
        MON_TYPES(TYPE_ICE),
        .catchRate = 50,
        .expYield = 182,
       // .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SLUSH_RUSH },
        .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Cetitan"),
        .cryId = CRY_CETITAN,
        .natDexNum = NATIONAL_DEX_CETITAN,
        .categoryName = _("Terra Whale"),
        .height = 45,
        .weight = 7000,
        .description = COMPOUND_STRING(
            "Ice energy builds up in the horn on\n"
            "its upper jaw, causing the horn to\n"
            "reach cryogenic temperatures that\n"
            "freeze its surroundings."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cetitan,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_Cetitan,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cetitan,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cetitan,
        .shinyPalette = gMonShinyPalette_Cetitan,
        .iconSprite = gMonIcon_Cetitan,
        .iconPalIndex = 0,
        //FOOTPRINT(Cetitan)
        */
        //.levelUpLearnset = sCetitanLevelUpLearnset,
        //.teachableLearnset = sCetitanTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_CETODDLE

//#if p_fAMILY_VELUZA
    [SPECIES_VELUZA] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              102,
              73,
              70,
              78,
              65
       ),
        MON_TYPES(TYPE_WATER, TYPE_PSYCHIC),
        .catchRate = 100,
        .expYield = 167,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_NONE },
        .abilityHidden = {ABILITY_SHARPNESS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Veluza"),
        .cryId = CRY_VELUZA,
        .natDexNum = NATIONAL_DEX_VELUZA,
        .categoryName = _("Jettison"),
        .height = 25,
        .weight = 900,
        .description = COMPOUND_STRING(
            "Veluza has excellent regenerative\n"
            "capabilities. It sheds spare flesh\n"
            "from its body to boost its agility,\n"
            "then charges at its prey."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Veluza,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_Veluza,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 5,
        .backPic = gMonBackPic_Veluza,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Veluza,
        .shinyPalette = gMonShinyPalette_Veluza,
        .iconSprite = gMonIcon_Veluza,
        .iconPalIndex = 1,
        //FOOTPRINT(Veluza)
        */
        //.levelUpLearnset = sVeluzaLevelUpLearnset,
        //.teachableLearnset = sVeluzaTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_VELUZA

//#if p_fAMILY_DONDOZO
    [SPECIES_DONDOZO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              150,
              100,
              115,
              35,
              65,
              65
       ),
        MON_TYPES(TYPE_WATER),
        .catchRate = 25,
        .expYield = 265,
       // .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_UNAWARE, ABILITY_OBLIVIOUS  },
        .abilityHidden = {ABILITY_WATER_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Dondozo"),
        .cryId = CRY_DONDOZO,
        .natDexNum = NATIONAL_DEX_DONDOZO,
        .categoryName = _("Big Catfish"),
        .height = 120,
        .weight = 2200,
        .description = COMPOUND_STRING(
            "It treats Tatsugiri like its boss\n"
            "and follows it loyally. Though\n"
            "powerful, Dondozo is apparently not very\n"
            "smart."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dondozo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_Dondozo,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 1,
        .backPic = gMonBackPic_Dondozo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dondozo,
        .shinyPalette = gMonShinyPalette_Dondozo,
        .iconSprite = gMonIcon_Dondozo,
        .iconPalIndex = 0,
        //FOOTPRINT(Dondozo)
        */
        //.levelUpLearnset = sDondozoLevelUpLearnset,
        //.teachableLearnset = sDondozoTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_DONDOZO

//#if p_fAMILY_TATSUGIRI
    [SPECIES_TATSUGIRI_CURLY] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              68,
              50,
              60,
              82,
              120,
              95
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_COMMANDER, ABILITY_NONE  },
        .abilityHidden = {ABILITY_STORM_DRAIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tatsugiri"),
        .cryId = CRY_TATSUGIRI_CURLY,
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimicry"),
        .height = 3,
        .weight = 80,
        .description = COMPOUND_STRING(
            "This is a small dragon Pokémon. It\n"
            "lives inside the mouth of Dondozo to\n"
            "protect itself from enemies on the\n"
            "outside."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TatsugiriCurly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_Tatsugiri,
        
        .backPic = gMonBackPic_TatsugiriCurly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        
        .palette = gMonPalette_TatsugiriCurly,
        .shinyPalette = gMonShinyPalette_TatsugiriCurly,
        .iconSprite = gMonIcon_TatsugiriCurly,
        .iconPalIndex = 0,
        //FOOTPRINT(Tatsugiri)
        */
        //.levelUpLearnset = sTatsugiriLevelUpLearnset,
        //.teachableLearnset = sTatsugiriTeachableLearnset,
        //.formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_TATSUGIRI_DROOPY] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              68,
              50,
              60,
              82,
              120,
              95
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_COMMANDER, ABILITY_NONE },
        .abilityHidden = {ABILITY_STORM_DRAIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tatsugiri"),
        .cryId = CRY_TATSUGIRI_DROOPY,
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimicry"),
        .height = 3,
        .weight = 80,
        .description = COMPOUND_STRING(
            "This Pokémon tricks its opponents\n"
            "by playing dead. It is small and\n"
            "weak, but it uses its smarts to survive."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TatsugiriDroopy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_Tatsugiri,
        
        .backPic = gMonBackPic_TatsugiriDroopy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        
        .palette = gMonPalette_TatsugiriDroopy,
        .shinyPalette = gMonShinyPalette_TatsugiriDroopy,
        .iconSprite = gMonIcon_TatsugiriDroopy,
        .iconPalIndex = 0,
        //FOOTPRINT(Tatsugiri)
        */
        //.levelUpLearnset = sTatsugiriLevelUpLearnset,
        //.teachableLearnset = sTatsugiriTeachableLearnset,
        //.formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_TATSUGIRI_STRETCHY] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              68,
              50,
              60,
              82,
              120,
              95
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
       // .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_COMMANDER, ABILITY_NONE },
        .abilityHidden = {ABILITY_STORM_DRAIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Tatsugiri"),
        .cryId = CRY_TATSUGIRI_STRETCHY,
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimicry"),
        .height = 3,
        .weight = 80,
        .description = COMPOUND_STRING(
            "It's one of the most intelligent\n"
            "dragon Pokémon. It camouflages itself\n"
            "by inflating its throat sac."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TatsugiriStretchy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_Tatsugiri,
        
        .backPic = gMonBackPic_TatsugiriStretchy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        
        .palette = gMonPalette_TatsugiriStretchy,
        .shinyPalette = gMonShinyPalette_TatsugiriStretchy,
        .iconSprite = gMonIcon_TatsugiriStretchy,
        .iconPalIndex = 0,
        //FOOTPRINT(Tatsugiri)
        */
        //.levelUpLearnset = sTatsugiriLevelUpLearnset,
        //.teachableLearnset = sTatsugiriTeachableLearnset,
        //.formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TATSUGIRI
    [SPECIES_ANNIHILAPE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              110,
              115,
              80,
              90,
              50,
              90
        ),
        MON_TYPES(TYPE_FIGHTING, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 268,
      //  .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_VITAL_SPIRIT, ABILITY_INNER_FOCUS },
        .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
      /*   .speciesName = _("Annihilape"),
        .cryId = CRY_ANNIHILAPE,
        .natDexNum = NATIONAL_DEX_ANNIHILAPE,
        .categoryName = _("Rage Monkey"),
        .height = 12,
        .weight = 560,
        .description = COMPOUND_STRING(
            "When its anger rose beyond a\n"
            "critical point, this Pokémon gained power\n"
            "that is unfettered by the limits of\n"
            "its physical body."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Annihilape,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Annihilape,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Annihilape,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Annihilape,
        .shinyPalette = gMonShinyPalette_Annihilape,
        .iconSprite = gMonIcon_Annihilape,
        .iconPalIndex = 0,
        //FOOTPRINT(Annihilape)
       */
        //.levelUpLearnset = sAnnihilapeLevelUpLearnset,
        //.teachableLearnset = sAnnihilapeTeachableLearnset,
      .enemyMonElevation = 0,
    },
    

    [SPECIES_CLODSIRE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              130,
              75,
              60,
              20,
              45,
              100
        ),
        MON_TYPES(TYPE_POISON, TYPE_GROUND),
        .catchRate = 90,
        .expYield = 151,
      //  .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_POISON_POINT, ABILITY_WATER_ABSORB  },
        .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
      /*   .speciesName = _("Clodsire"),
        .cryId = CRY_CLODSIRE,
        .natDexNum = NATIONAL_DEX_CLODSIRE,
        .categoryName = _("Spiny Fish"),
        .height = 18,
        .weight = 2230,
        .description = COMPOUND_STRING(
            "When attacked, this Pokémon will\n"
            "retaliate by sticking thick spines out\n"
            "from its body. It's a risky move\n"
            "that puts everything on the line."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Clodsire,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_Clodsire,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Clodsire,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Clodsire,
        .shinyPalette = gMonShinyPalette_Clodsire,
        .iconSprite = gMonIcon_Clodsire,
        .iconPalIndex = 0,
        //FOOTPRINT(Clodsire)
       */
        //.levelUpLearnset = sClodsireLevelUpLearnset,
        //.teachableLearnset = sClodsireTeachableLearnset,
      .enemyMonElevation = 0,
    },

    [SPECIES_FARIGIRAF] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              120,
              90,
              70,
              60,
              110,
              70
        ),
        MON_TYPES(TYPE_NORMAL, TYPE_PSYCHIC),
        .catchRate = 45,
        .expYield = 260,
      //  .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_CUD_CHEW, ABILITY_ARMOR_TAIL  },
        .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
      /*   .speciesName = _("Farigiraf"),
        .cryId = CRY_FARIGIRAF,
        .natDexNum = NATIONAL_DEX_FARIGIRAF,
        .categoryName = _("Long Neck"),
        .height = 32,
        .weight = 1600,
        .description = COMPOUND_STRING(
            "Now that the brain waves from the\n"
            "head and tail are synced up, the\n"
            "psychic power of this Pokémon is 10\n"
            "times stronger than Girafarig's."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Farigiraf,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Farigiraf,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Farigiraf,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Farigiraf,
        .shinyPalette = gMonShinyPalette_Farigiraf,
        .iconSprite = gMonIcon_Farigiraf,
        .iconPalIndex = 0,
        //FOOTPRINT(Farigiraf)
       */
        //.levelUpLearnset = sFarigirafLevelUpLearnset,
        //.teachableLearnset = sFarigirafTeachableLearnset,
      .enemyMonElevation = 0,
    },

    [SPECIES_DUDUNSPARCE_TWO_SEGMENT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              125,
              100,
              80,
              55,
              85,
              75
        ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 45,
        .expYield = 182,
      //  .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SERENE_GRACE, ABILITY_RUN_AWAY  },
        .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
      /*   .speciesName = _("Dudunsprce"),
        .cryId = CRY_DUDUNSPARCE,
        .natDexNum = NATIONAL_DEX_DUDUNSPARCE,
        .categoryName = _("Land Snake"),
        .height = 36,
        .weight = 392,
        .description = COMPOUND_STRING(
            "This Pokémon uses its hard tail to\n"
            "make its nest by boring holes into\n"
            "bedrock deep underground. The nest\n"
            "can reach lengths of over six miles."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_DudunsparceTwoSegment,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Dudunsparce,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_DudunsparceTwoSegment,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dudunsparce,
        .shinyPalette = gMonShinyPalette_Dudunsparce,
        .iconSprite = gMonIcon_Dudunsparce,
        .iconPalIndex = 0,
        //FOOTPRINT(Dudunsparce)
       */
        //.levelUpLearnset = sDudunsparceLevelUpLearnset,
        //.teachableLearnset = sDudunsparceTeachableLearnset,
      //  .formSpeciesIdTable = sDudunsparceFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_DUDUNSPARCE_THREE_SEGMENT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              125,
              100,
              80,
              55,
              85,
              75
        ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 45,
        .expYield = 182,
      //  .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SERENE_GRACE, ABILITY_RUN_AWAY },
        .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
      /*   .speciesName = _("Dudunsprce"),
        .cryId = CRY_DUDUNSPARCE,
        .natDexNum = NATIONAL_DEX_DUDUNSPARCE,
        .categoryName = _("Land Snake"),
        .height = 45,
        .weight = 474,
        .description = COMPOUND_STRING(
            "A recent study uncovered that the\n"
            "number of segments a\n"
            "Dudunsparce's body has is determined by the\n"
            "Pokémon's genes."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_DudunsparceThreeSegment,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Dudunsparce,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_DudunsparceThreeSegment,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dudunsparce,
        .shinyPalette = gMonShinyPalette_Dudunsparce,
        .iconSprite = gMonIcon_Dudunsparce,
        .iconPalIndex = 0,
        //FOOTPRINT(Dudunsparce)
       */
        //.levelUpLearnset = sDudunsparceLevelUpLearnset,
        //.teachableLearnset = sDudunsparceTeachableLearnset,
      //  .formSpeciesIdTable = sDudunsparceFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_KINGAMBIT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              135,
              120,
              50,
              60,
              85
        ),
        MON_TYPES(TYPE_DARK, TYPE_STEEL),
        .catchRate = 25,
        .expYield = 275,
      //  .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_DEFIANT, ABILITY_SUPREME_OVERLORD  },
        .abilityHidden = {ABILITY_PRESSURE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
      /*   .speciesName = _("Kingambit"),
        .cryId = CRY_KINGAMBIT,
        .natDexNum = NATIONAL_DEX_KINGAMBIT,
        .categoryName = _("Big Blade"),
        .height = 20,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "Though it commands a massive army\n"
            "in battle, it's not skilled at\n"
            "devising complex strategies. It just uses\n"
            "brute strength to keep pushing."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Kingambit,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Kingambit,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Kingambit,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Kingambit,
        .shinyPalette = gMonShinyPalette_Kingambit,
        .iconSprite = gMonIcon_Kingambit,
        .iconPalIndex = 0,
        //FOOTPRINT(Kingambit)
       */
        //.levelUpLearnset = sKingambitLevelUpLearnset,
        //.teachableLearnset = sKingambitTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#if p_fAMILY_GREAT_TUSK
    [SPECIES_GREAT_TUSK] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              115,
              131,
              131,
              87,
              53,
              53
       ),
        MON_TYPES(TYPE_GROUND, TYPE_FIGHTING),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE  },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Great Tusk"),
        .cryId = CRY_GREAT_TUSK,
        .natDexNum = NATIONAL_DEX_GREAT_TUSK,
        .categoryName = _("Paradox"),
        .height = 22,
        .weight = 3200,
        .description = COMPOUND_STRING(
            "Sightings of this Pokémon have\n"
            "occurred in recent years. The name\n"
            "Great Tusk was taken from a creature\n"
            "listed in a certain book."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GreatTusk,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_GreatTusk,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GreatTusk,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GreatTusk,
        .shinyPalette = gMonShinyPalette_GreatTusk,
        .iconSprite = gMonIcon_GreatTusk,
        .iconPalIndex = 0,
        //FOOTPRINT(GreatTusk)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sGreatTuskLevelUpLearnset,
        //.teachableLearnset = sGreatTuskTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_GREAT_TUSK

//#if p_fAMILY_SCREAM_TAIL
    [SPECIES_SCREAM_TAIL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              115,
              65,
              99,
              111,
              65,
              115
       ),
        MON_TYPES(TYPE_FAIRY, TYPE_PSYCHIC),
        .catchRate = 50,
        .expYield = 285,
       // .evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("ScreamTail"),
        .cryId = CRY_SCREAM_TAIL,
        .natDexNum = NATIONAL_DEX_SCREAM_TAIL,
        .categoryName = _("Paradox"),
        .height = 12,
        .weight = 80,
        .description = COMPOUND_STRING(
            "There has been only one reported\n"
            "sighting of this Pokémon. It\n"
            "resembles a mysterious creature depicted\n"
            "in an old expedition journal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ScreamTail,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_ScreamTail,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ScreamTail,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ScreamTail,
        .shinyPalette = gMonShinyPalette_ScreamTail,
        .iconSprite = gMonIcon_ScreamTail,
        .iconPalIndex = 0,
        //FOOTPRINT(ScreamTail)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sScreamTailLevelUpLearnset,
        //.teachableLearnset = sScreamTailTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SCREAM_TAIL

//#if p_fAMILY_BRUTE_BONNET
    [SPECIES_BRUTE_BONNET] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              111,
              127,
              99,
              55,
              79,
              99
       ),
        MON_TYPES(TYPE_GRASS, TYPE_DARK),
        .catchRate = 50,
        .expYield = 285,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("BruteBonet"),
        .cryId = CRY_BRUTE_BONNET,
        .natDexNum = NATIONAL_DEX_BRUTE_BONNET,
        .categoryName = _("Paradox"),
        .height = 12,
        .weight = 210,
        .description = COMPOUND_STRING(
            "It bears a slight resemblance to a\n"
            "Pokémon described in a dubious\n"
            "magazine as a cross between a dinosaur\n"
            "and a mushroom."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_BruteBonnet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_BruteBonnet,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_BruteBonnet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_BruteBonnet,
        .shinyPalette = gMonShinyPalette_BruteBonnet,
        .iconSprite = gMonIcon_BruteBonnet,
        .iconPalIndex = 1,
        //FOOTPRINT(BruteBonnet)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sBruteBonnetLevelUpLearnset,
        //.teachableLearnset = sBruteBonnetTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_BRUTE_BONNET

//#if p_fAMILY_FLUTTER_MANE
    [SPECIES_FLUTTER_MANE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              55,
              55,
              55,
              135,
              135,
              135
       ),
        MON_TYPES(TYPE_GHOST, TYPE_FAIRY),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_Speed = 1,
       // .evYield_SpAttack = 1,
       // .evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("FluttrMane"),
        .cryId = CRY_FLUTTER_MANE,
        .natDexNum = NATIONAL_DEX_FLUTTER_MANE,
        .categoryName = _("Paradox"),
        .height = 14,
        .weight = 40,
        .description = COMPOUND_STRING(
            "It has similar features to a\n"
            "ghostly pterosaur that was covered in a\n"
            "paranormal magazine, but the two\n"
            "have little else in common."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_FlutterMane,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_FlutterMane,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 18,
        .backPic = gMonBackPic_FlutterMane,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_FlutterMane,
        .shinyPalette = gMonShinyPalette_FlutterMane,
        .iconSprite = gMonIcon_FlutterMane,
        .iconPalIndex = 2,
        //FOOTPRINT(FlutterMane)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sFlutterManeLevelUpLearnset,
        //.teachableLearnset = sFlutterManeTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FLUTTER_MANE

//#if p_fAMILY_SLITHER_WING
    [SPECIES_SLITHER_WING] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              85,
              135,
              79,
              81,
              85,
              105
       ),
        MON_TYPES(TYPE_BUG, TYPE_FIGHTING),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("SlithrWing"),
        .cryId = CRY_SLITHER_WING,
        .natDexNum = NATIONAL_DEX_SLITHER_WING,
        .categoryName = _("Paradox"),
        .height = 32,
        .weight = 920,
        .description = COMPOUND_STRING(
            "This mysterious Pokémon has some\n"
            "similarities to a creature that an\n"
            "old book introduced as Slither Wing."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SlitherWing,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SlitherWing,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_SlitherWing,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_SlitherWing,
        .shinyPalette = gMonShinyPalette_SlitherWing,
        .iconSprite = gMonIcon_SlitherWing,
        .iconPalIndex = 1,
        //FOOTPRINT(SlitherWing)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sSlitherWingLevelUpLearnset,
        //.teachableLearnset = sSlitherWingTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SLITHER_WING

//#if p_fAMILY_SANDY_SHOCKS
    [SPECIES_SANDY_SHOCKS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              85,
              81,
              97,
              101,
              121,
              85
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_GROUND),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("SndyShocks"),
        .cryId = CRY_SANDY_SHOCKS,
        .natDexNum = NATIONAL_DEX_SANDY_SHOCKS,
        .categoryName = _("Paradox"),
        .height = 23,
        .weight = 600,
        .description = COMPOUND_STRING(
            "It slightly resembles a Magneton\n"
            "that lived for 10,000 years and was\n"
            "featured in an article in a\n"
            "paranormal magazine."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SandyShocks,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SandyShocks,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_SandyShocks,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_SandyShocks,
        .shinyPalette = gMonShinyPalette_SandyShocks,
        .iconSprite = gMonIcon_SandyShocks,
        .iconPalIndex = 0,
        //FOOTPRINT(SandyShocks)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sSandyShocksLevelUpLearnset,
        //.teachableLearnset = sSandyShocksTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_SANDY_SHOCKS

//#if p_fAMILY_IRON_TREADS
    [SPECIES_IRON_TREADS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              112,
              120,
              106,
              72,
              70
       ),
        MON_TYPES(TYPE_GROUND, TYPE_STEEL),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("IronTreads"),
        .cryId = CRY_IRON_TREADS,
        .natDexNum = NATIONAL_DEX_IRON_TREADS,
        .categoryName = _("Paradox"),
        .height = 9,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "Sightings of this Pokémon have\n"
            "occurred in recent years. It resembles\n"
            "a mysterious object described in an\n"
            "old expedition journal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronTreads,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_IronTreads,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronTreads,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronTreads,
        .shinyPalette = gMonShinyPalette_IronTreads,
        .iconSprite = gMonIcon_IronTreads,
        .iconPalIndex = 1,
        //FOOTPRINT(IronTreads)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronTreadsLevelUpLearnset,
        //.teachableLearnset = sIronTreadsTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_TREADS

//#if p_fAMILY_IRON_BUNDLE
    [SPECIES_IRON_BUNDLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              56,
              80,
              114,
              136,
              124,
              60
       ),
        MON_TYPES(TYPE_ICE, TYPE_WATER),
        .catchRate = 50,
        .expYield = 285,
       // .evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("IronBundle"),
        .cryId = CRY_IRON_BUNDLE,
        .natDexNum = NATIONAL_DEX_IRON_BUNDLE,
        .categoryName = _("Paradox"),
        .height = 6,
        .weight = 110,
        .description = COMPOUND_STRING(
            "Its shape is similar to a robot\n"
            "featured in a paranormal magazine\n"
            "article. The robot was said to have been\n"
            "created by an ancient civilization."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronBundle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_IronBundle,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronBundle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronBundle,
        .shinyPalette = gMonShinyPalette_IronBundle,
        .iconSprite = gMonIcon_IronBundle,
        .iconPalIndex = 0,
        //FOOTPRINT(IronBundle)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronBundleLevelUpLearnset,
        //.teachableLearnset = sIronBundleTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_BUNDLE

//#if p_fAMILY_IRON_HANDS
    [SPECIES_IRON_HANDS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              154,
              140,
              108,
              50,
              50,
              68
       ),
        MON_TYPES(TYPE_FIGHTING, TYPE_ELECTRIC),
        .catchRate = 50,
        .expYield = 285,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Iron Hands"),
        .cryId = CRY_IRON_HANDS,
        .natDexNum = NATIONAL_DEX_IRON_HANDS,
        .categoryName = _("Paradox"),
        .height = 18,
        .weight = 3807,
        .description = COMPOUND_STRING(
            "It is very similar to a cyborg\n"
            "covered exclusively by a paranormal\n"
            "magazine. The cyborg was said to be the\n"
            "modified form of a certain athlete."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronHands,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_IronHands,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronHands,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronHands,
        .shinyPalette = gMonShinyPalette_IronHands,
        .iconSprite = gMonIcon_IronHands,
        .iconPalIndex = 0,
        //FOOTPRINT(IronHands)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronHandsLevelUpLearnset,
        //.teachableLearnset = sIronHandsTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_HANDS

//#if p_fAMILY_IRON_JUGULIS
    [SPECIES_IRON_JUGULIS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              94,
              80,
              86,
              108,
              122,
              80
       ),
        MON_TYPES(TYPE_DARK, TYPE_FLYING),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("IronJuguls"),
        .cryId = CRY_IRON_JUGULIS,
        .natDexNum = NATIONAL_DEX_IRON_JUGULIS,
        .categoryName = _("Paradox"),
        .height = 13,
        .weight = 1110,
        .description = COMPOUND_STRING(
            "It resembles a certain Pokémon\n"
            "introduced in a paranormal magazine,\n"
            "described as the offspring of a\n"
            "Hydreigon that fell in love with a robot."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronJugulis,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_IronJugulis,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 7,
        .backPic = gMonBackPic_IronJugulis,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronJugulis,
        .shinyPalette = gMonShinyPalette_IronJugulis,
        .iconSprite = gMonIcon_IronJugulis,
        .iconPalIndex = 0,
        //FOOTPRINT(IronJugulis)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronJugulisLevelUpLearnset,
        //.teachableLearnset = sIronJugulisTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_JUGULIS

//#if p_fAMILY_IRON_MOTH
    [SPECIES_IRON_MOTH] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              80,
              70,
              60,
              110,
              140,
              110
       ),
        MON_TYPES(TYPE_FIRE, TYPE_POISON),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Iron Moth"),
        .cryId = CRY_IRON_MOTH,
        .natDexNum = NATIONAL_DEX_IRON_MOTH,
        .categoryName = _("Paradox"),
        .height = 12,
        .weight = 360,
        .description = COMPOUND_STRING(
            "No records exist of this species\n"
            "being caught. Data is lacking, but\n"
            "the Pokémon's traits match up with an\n"
            "object described in an old book."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronMoth,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_IronMoth,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_IronMoth,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronMoth,
        .shinyPalette = gMonShinyPalette_IronMoth,
        .iconSprite = gMonIcon_IronMoth,
        .iconPalIndex = 3,
        //FOOTPRINT(IronMoth)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronMothLevelUpLearnset,
        //.teachableLearnset = sIronMothTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_MOTH

//#if p_fAMILY_IRON_THORNS
    [SPECIES_IRON_THORNS] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              134,
              110,
              72,
              70,
              84
       ),
        MON_TYPES(TYPE_ROCK, TYPE_ELECTRIC),
        .catchRate = 30,
        .expYield = 285,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("IronThorns"),
        .cryId = CRY_IRON_THORNS,
        .natDexNum = NATIONAL_DEX_IRON_THORNS,
        .categoryName = _("Paradox"),
        .height = 16,
        .weight = 3030,
        .description = COMPOUND_STRING(
            "It has some similarities to a\n"
            "Pokémon introduced in a dubious magazine\n"
            "as a Tyranitar from one billion\n"
            "years into the future."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronThorns,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_IronThorns,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronThorns,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronThorns,
        .shinyPalette = gMonShinyPalette_IronThorns,
        .iconSprite = gMonIcon_IronThorns,
        .iconPalIndex = 1,
        //FOOTPRINT(IronThorns)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronThornsLevelUpLearnset,
        //.teachableLearnset = sIronThornsTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_THORNS

//#if p_fAMILY_FRIGIBAX
    [SPECIES_FRIGIBAX] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              65,
              75,
              45,
              55,
              35,
              45
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 45,
        .expYield = 64,
       // .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE  },
        .abilityHidden = {ABILITY_ICE_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Frigibax"),
        .cryId = CRY_FRIGIBAX,
        .natDexNum = NATIONAL_DEX_FRIGIBAX,
        .categoryName = _("Ice Fin"),
        .height = 5,
        .weight = 170,
        .description = COMPOUND_STRING(
            "This Pokémon lives in forests and\n"
            "craggy areas. Using the power of its\n"
            "dorsal fin, it cools the inside of its\n"
            "nest like a refrigerator."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Frigibax,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Frigibax,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Frigibax,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Frigibax,
        .shinyPalette = gMonShinyPalette_Frigibax,
        .iconSprite = gMonIcon_Frigibax,
        .iconPalIndex = 0,
        //FOOTPRINT(Frigibax)
        */
        //.levelUpLearnset = sFrigibaxLevelUpLearnset,
        //.teachableLearnset = sFrigibaxTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 35, 0,  SPECIES_ARCTIBAX}),
      .enemyMonElevation = 0,
    },

    [SPECIES_ARCTIBAX] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              95,
              66,
              62,
              45,
              65
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 25,
        .expYield = 148,
       // .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE },
        .abilityHidden = {ABILITY_ICE_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Arctibax"),
        .cryId = CRY_ARCTIBAX,
        .natDexNum = NATIONAL_DEX_ARCTIBAX,
        .categoryName = _("Ice Fin"),
        .height = 8,
        .weight = 300,
        .description = COMPOUND_STRING(
            "Arctibax freezes the air around it,\n"
            "protecting its face with an ice\n"
            "mask and turning its dorsal fin into a\n"
            "blade of ice."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Arctibax,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_Arctibax,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Arctibax,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Arctibax,
        .shinyPalette = gMonShinyPalette_Arctibax,
        .iconSprite = gMonIcon_Arctibax,
        .iconPalIndex = 0,
        //FOOTPRINT(Arctibax)
        */
        //.levelUpLearnset = sArctibaxLevelUpLearnset,
        //.teachableLearnset = sArctibaxTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_LEVEL, 54, 0,  SPECIES_BAXCALIBUR}),
      .enemyMonElevation = 0,
    },

    [SPECIES_BAXCALIBUR] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              115,
              145,
              92,
              87,
              75,
              86
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 10,
        .expYield = 300,
       // .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE },
        .abilityHidden = {ABILITY_ICE_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Baxcalibur"),
        .cryId = CRY_BAXCALIBUR,
        .natDexNum = NATIONAL_DEX_BAXCALIBUR,
        .categoryName = _("Ice Dragon"),
        .height = 21,
        .weight = 2100,
        .description = COMPOUND_STRING(
            "It launches itself into battle by\n"
            "flipping upside down and spewing\n"
            "frigid air from its mouth. It finishes\n"
            "opponents off with its dorsal blade."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Baxcalibur,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Baxcalibur,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Baxcalibur,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Baxcalibur,
        .shinyPalette = gMonShinyPalette_Baxcalibur,
        .iconSprite = gMonIcon_Baxcalibur,
        .iconPalIndex = 0,
        //FOOTPRINT(Baxcalibur)
        */
        //.levelUpLearnset = sBaxcaliburLevelUpLearnset,
        //.teachableLearnset = sBaxcaliburTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_FRIGIBAX

//#if p_fAMILY_GIMMIGHOUL
    [SPECIES_GIMMIGHOUL_CHEST] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              45,
              30,
              70,
              10,
              75,
              70
       ),
        MON_TYPES(TYPE_GHOST),
        .catchRate = 45,
        .expYield = 60,
       // .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_RATTLED, ABILITY_NONE  },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Gimmighoul"),
        .cryId = CRY_GIMMIGHOUL,
        .natDexNum = NATIONAL_DEX_GIMMIGHOUL,
        .categoryName = _("Coin Chest"),
        .height = 3,
        .weight = 50,
        .description = COMPOUND_STRING(
            "It lives inside an old treasure\n"
            "chest. Sometimes it gets left in shop\n"
            "corners since no one realizes it's\n"
            "actually a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GimmighoulChest,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Gimmighoul,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GimmighoulChest,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GimmighoulChest,
        .shinyPalette = gMonShinyPalette_GimmighoulChest,
        .iconSprite = gMonIcon_GimmighoulChest,
        .iconPalIndex = 0,
        //FOOTPRINT(Gimmighoul)
        */
        //.levelUpLearnset = sGimmighoulLevelUpLearnset,
        //.teachableLearnset = sGimmighoulTeachableLearnset,
        //.formSpeciesIdTable = sGimmighoulFormSpeciesIdTable,
        //.evolutions = EVOLUTION({EVO_HIGH_RICHES, 65000, FILL,  SPECIES_GHOLDENGO}),
      .enemyMonElevation = 0,
    },//will make money based evolution I guess 70k poke, kinda griny but make gimmighoul better to use pre evo
    //and counter is you can evolve it at any level - brought down because u16 param

    [SPECIES_GIMMIGHOUL_ROAMING] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              45,
              30,
              25,
              80,
              75,
              45
       ),
        MON_TYPES(TYPE_GHOST),
        .catchRate = 45,
        .expYield = 60,
       // .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Gimmighoul"),
        .cryId = CRY_GIMMIGHOUL,
        .natDexNum = NATIONAL_DEX_GIMMIGHOUL,
        .categoryName = _("Coin Hunter"),
        .height = 1,
        .weight = 1,
        .description = COMPOUND_STRING(
            "It wanders around, carrying an old\n"
            "coin on its back. It survives by\n"
            "draining the life-force from humans who\n"
            "try to pick up its coin."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GimmighoulRoaming,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_Gimmighoul,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GimmighoulRoaming,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GimmighoulRoaming,
        .shinyPalette = gMonShinyPalette_GimmighoulRoaming,
        .iconSprite = gMonIcon_GimmighoulRoaming,
        .iconPalIndex = 0,
        //FOOTPRINT(Gimmighoul)
        */
        //.levelUpLearnset = sGimmighoulLevelUpLearnset,
        //.teachableLearnset = sGimmighoulTeachableLearnset,
        //.formSpeciesIdTable = sGimmighoulFormSpeciesIdTable,
        //.evolutions = EVOLUTION({EVO_NONE, 0, 0,  SPECIES_GHOLDENGO}),
      .enemyMonElevation = 0,
    }, //not gonna use this form

    [SPECIES_GHOLDENGO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              87,
              60,
              95,
              84,
              133,
              91
       ),
        MON_TYPES(TYPE_STEEL, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 275,
       // .evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_GOOD_AS_GOLD, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Gholdengo"),
        .cryId = CRY_GHOLDENGO,
        .natDexNum = NATIONAL_DEX_GHOLDENGO,
        .categoryName = _("Coin Entity"),
        .height = 12,
        .weight = 300,
        .description = COMPOUND_STRING(
            "It has a sturdy body made up of\n"
            "stacked coins. Gholdengo overwhelms\n"
            "its enemies by firing coin after coin\n"
            "at them in quick succession."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Gholdengo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Gholdengo,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Gholdengo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Gholdengo,
        .shinyPalette = gMonShinyPalette_Gholdengo,
        .iconSprite = gMonIcon_Gholdengo,
        .iconPalIndex = 0,
        //FOOTPRINT(Gholdengo)
        */
        //.levelUpLearnset = sGholdengoLevelUpLearnset,
        //.teachableLearnset = sGholdengoTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_GIMMIGHOUL

//#if p_fAMILY_WO_CHIEN
    [SPECIES_WO_CHIEN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              105,
              85,
              100,
              70,
              95,
              135
       ),
        MON_TYPES(TYPE_DARK, TYPE_GRASS),
        .catchRate = 6,
        .expYield = 285,
       // .evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TABLETS_OF_RUIN, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN, //based on wolfyvgc vid redid ability drops speed instead of attack
        /*.speciesName = _("Wo-Chien"),
        .cryId = CRY_WO_CHIEN,
        .natDexNum = NATIONAL_DEX_WO_CHIEN,
        .categoryName = _("Ruinous"),
        .height = 15,
        .weight = 742,
        .description = COMPOUND_STRING(
            "The grudge of a person punished\n"
            "for writing the king's evil deeds upon\n"
            "wooden tablets has clad itself in\n"
            "dead leaves to become a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WoChien,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_WoChien,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_WoChien,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_WoChien,
        .shinyPalette = gMonShinyPalette_WoChien,
        .iconSprite = gMonIcon_WoChien,
        .iconPalIndex = 1,
        //FOOTPRINT(WoChien)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sWoChienLevelUpLearnset,
        //.teachableLearnset = sWoChienTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_WO_CHIEN

//#if p_fAMILY_CHIEN_PAO
    [SPECIES_CHIEN_PAO] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              80,
              120,
              80,
              135,
              90,
              65
       ),
        MON_TYPES(TYPE_DARK, TYPE_ICE),
        .catchRate = 6,
        .expYield = 285,
       // .evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_SWORD_OF_RUIN, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Chien-Pao"),
        .cryId = CRY_CHIEN_PAO,
        .natDexNum = NATIONAL_DEX_CHIEN_PAO,
        .categoryName = _("Ruinous"),
        .height = 19,
        .weight = 1522,
        .description = COMPOUND_STRING(
            "This Pokémon can control 100 tons\n"
            "of fallen snow. It plays around\n"
            "innocently by leaping in and out of\n"
            "avalanches it has caused."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ChienPao,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_ChienPao,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ChienPao,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ChienPao,
        .shinyPalette = gMonShinyPalette_ChienPao,
        .iconSprite = gMonIcon_ChienPao,
        .iconPalIndex = 0,
        //FOOTPRINT(ChienPao)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sChienPaoLevelUpLearnset,
        //.teachableLearnset = sChienPaoTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_CHIEN_PAO

//#if p_fAMILY_TING_LU
    [SPECIES_TING_LU] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              155,
              110,
              125,
              45,
              55,
              80
       ),
        MON_TYPES(TYPE_DARK, TYPE_GROUND),
        .catchRate = 6,
        .expYield = 285,
       // .evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_VESSEL_OF_RUIN, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Ting-Lu"),
        .cryId = CRY_TING_LU,
        .natDexNum = NATIONAL_DEX_TING_LU,
        .categoryName = _("Ruinous"),
        .height = 27,
        .weight = 6997,
        .description = COMPOUND_STRING(
            "It slowly brings its exceedingly\n"
            "heavy head down upon the ground,\n"
            "splitting the earth open with huge\n"
            "fissures that run over 160 feet deep."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TingLu,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_TingLu,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TingLu,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TingLu,
        .shinyPalette = gMonShinyPalette_TingLu,
        .iconSprite = gMonIcon_TingLu,
        .iconPalIndex = 0,
        //FOOTPRINT(TingLu)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sTingLuLevelUpLearnset,
        //.teachableLearnset = sTingLuTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_TING_LU

//#if p_fAMILY_CHI_YU
    [SPECIES_CHI_YU] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              55,
              80,
              80,
              100,
              135,
              120
       ),
        MON_TYPES(TYPE_DARK, TYPE_FIRE),
        .catchRate = 6,
        .expYield = 285,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_BEADS_OF_RUIN, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Chi-Yu"),
        .cryId = CRY_CHI_YU,
        .natDexNum = NATIONAL_DEX_CHI_YU,
        .categoryName = _("Ruinous"),
        .height = 4,
        .weight = 49,
        .description = COMPOUND_STRING(
            "It controls flames burning at over\n"
            "5,400 degrees Fahrenheit. It\n"
            "casually swims through the sea of lava it\n"
            "creates by melting rock and sand."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ChiYu,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_ChiYu,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 15,
        .backPic = gMonBackPic_ChiYu,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ChiYu,
        .shinyPalette = gMonShinyPalette_ChiYu,
        .iconSprite = gMonIcon_ChiYu,
        .iconPalIndex = 0,
        //FOOTPRINT(ChiYu)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sChiYuLevelUpLearnset,
        //.teachableLearnset = sChiYuTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_CHI_YU

//#if p_fAMILY_ROARING_MOON
    [SPECIES_ROARING_MOON] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              105,
              139,
              71,
              119,
              55,
              101
       ),
        MON_TYPES(TYPE_DRAGON, TYPE_DARK),
        .catchRate = 10,
        .expYield = 295,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("RoarngMoon"),
        .cryId = CRY_ROARING_MOON,
        .natDexNum = NATIONAL_DEX_ROARING_MOON,
        .categoryName = _("Paradox"),
        .height = 20,
        .weight = 3800,
        .description = COMPOUND_STRING(
            "According to an article in a\n"
            "dubious magazine, this Pokémon has some\n"
            "connection to Mega Evolution that\n"
            "occurs in Hoenn."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_RoaringMoon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_RoaringMoon,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 6,
        .backPic = gMonBackPic_RoaringMoon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_RoaringMoon,
        .shinyPalette = gMonShinyPalette_RoaringMoon,
        .iconSprite = gMonIcon_RoaringMoon,
        .iconPalIndex = 0,
        //FOOTPRINT(RoaringMoon)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sRoaringMoonLevelUpLearnset,
        //.teachableLearnset = sRoaringMoonTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_ROARING_MOON

//#if p_fAMILY_IRON_VALIANT
    [SPECIES_IRON_VALIANT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              74,
              130,
              90,
              116,
              120,
              60
       ),
        MON_TYPES(TYPE_FAIRY, TYPE_FIGHTING),
        .catchRate = 10,
        .expYield = 295,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("IronVliant"),
        .cryId = CRY_IRON_VALIANT,
        .natDexNum = NATIONAL_DEX_IRON_VALIANT,
        .categoryName = _("Paradox"),
        .height = 14,
        .weight = 350,
        .description = COMPOUND_STRING(
            "It has some similarities to a mad\n"
            "scientist's invention covered in a\n"
            "paranormal magazine."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronValiant,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_IronValiant,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronValiant,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronValiant,
        .shinyPalette = gMonShinyPalette_IronValiant,
        .iconSprite = gMonIcon_IronValiant,
        .iconPalIndex = 1,
        //FOOTPRINT(IronValiant)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronValiantLevelUpLearnset,
        //.teachableLearnset = sIronValiantTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_VALIANT

//#if p_fAMILY_KORAIDON
    [SPECIES_KORAIDON] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              135,
              115,
              135,
              85,
              100
       ),
        MON_TYPES(TYPE_FIGHTING, TYPE_DRAGON),
        .catchRate = 3,
        .expYield = 335,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_ORICHALCUM_PULSE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Koraidon"),
        .cryId = CRY_KORAIDON,
        .natDexNum = NATIONAL_DEX_KORAIDON,
        .categoryName = _("Paradox"),
        .height = 25,
        .weight = 3030,
        .description = COMPOUND_STRING(
            "This Pokémon resembles Cyclizar,\n"
            "but it is far burlier and more\n"
            "ferocious. Nothing is known about its\n"
            "ecology or other features."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Koraidon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Koraidon,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Koraidon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Koraidon,
        .shinyPalette = gMonShinyPalette_Koraidon,
        .iconSprite = gMonIcon_Koraidon,
        .iconPalIndex = 0,
        //FOOTPRINT(Koraidon)
        .isLegendary = TRUE,
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sKoraidonLevelUpLearnset,
        //.teachableLearnset = sKoraidonTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_KORAIDON

//#if p_fAMILY_MIRAIDON
    [SPECIES_MIRAIDON] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              100,
              85,
              100,
              135,
              135,
              115
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_DRAGON),
        .catchRate = 3,
        .expYield = 335,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_HADRON_ENGINE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Miraidon"),
        .cryId = CRY_MIRAIDON,
        .natDexNum = NATIONAL_DEX_MIRAIDON,
        .categoryName = _("Paradox"),
        .height = 35,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "This seems to be the Iron Serpent\n"
            "mentioned in an Violet Book. The\n"
            "Iron Serpent is said to have turned the\n"
            "land to ash with its lightning."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Miraidon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Miraidon,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Miraidon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Miraidon,
        .shinyPalette = gMonShinyPalette_Miraidon,
        .iconSprite = gMonIcon_Miraidon,
        .iconPalIndex = 2,
        //FOOTPRINT(Miraidon)
        .isLegendary = TRUE,
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sMiraidonLevelUpLearnset,
        //.teachableLearnset = sMiraidonTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_MIRAIDON

//Paldean Forms Start
//changed to main dark, as makes much more sense than fighting,
//all of these barely get fighting moves as well
//plus combat breed already made more sense as a dark type
//than pure fighting based on moveset patterns
//w loss of stab w most of its moveset boosted attack
[SPECIES_TAUROS_PALDEAN_COMBAT_BREED] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              75,
              120,
              105,
              100,
              30,
              70
        ),
        MON_TYPES(TYPE_DARK,TYPE_FIGHTING), //need decide if make raging bull type dark or fighting
        .catchRate = 45,
        .expYield = 211,
      //  .evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_ANGER_POINT  },
        .abilityHidden = {ABILITY_CUD_CHEW, ABILITY_EARLY_BIRD}, 
        .bodyColor = BODY_COLOR_BLACK, //INSTEAD of muscle magic give early bird, MM can be the special
      /*   .speciesName = _("Tauros"),  //give rest
        .cryId = CRY_TAUROS,
        .natDexNum = NATIONAL_DEX_TAUROS,
        .categoryName = _("Wild Bull"),
        .height = 14,
        .weight = 1150,
        .description = COMPOUND_STRING(
            "This Pokémon has a muscular body\n"
            "and excels at close-quarters combat.\n"
            "It uses its short horns to strike\n"
            "the opponent’s weak spots."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TaurosPaldeanCombatBreed,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_TaurosPaldean,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TaurosPaldeanCombatBreed,
        .backPicSize = MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_TaurosPaldeanCombatBreed,
        .shinyPalette = gMonShinyPalette_TaurosPaldeanCombatBreed,
        .iconSprite = gMonIcon_TaurosPaldeanCombatBreed,
        .iconPalIndex = 0,
        FOOTPRINT(Tauros)
        .isPaldeanForm = TRUE,*/
       // .levelUpLearnset = sTaurosPaldeanCombatBreedLevelUpLearnset,
        //.teachableLearnset = sTaurosPaldeanCombatBreedTeachableLearnset,
      //  .formSpeciesIdTable = sTaurosFormSpeciesIdTable,
        //.flags = F_PALDEAN_FORM,
      .enemyMonElevation = 0,
    },

    [SPECIES_TAUROS_PALDEAN_BLAZE_BREED] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              75,
              120,
              105,
              100,
              30,
              70
        ),
        MON_TYPES(TYPE_DARK, TYPE_FIRE),
        .catchRate = 45,
        .expYield = 211,
      //  .evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_ANGER_POINT },
        .abilityHidden = {ABILITY_CUD_CHEW, ABILITY_EARLY_BIRD},
        .bodyColor = BODY_COLOR_BLACK,
      /*   .speciesName = _("Tauros"),
        .cryId = CRY_TAUROS,
        .natDexNum = NATIONAL_DEX_TAUROS,
        .categoryName = _("Wild Bull"),
        .height = 14,
        .weight = 850,
        .description = COMPOUND_STRING(
            "When heated by fire energy, its horns can\n"
            "get hotter than 1,800 degrees Fahrenheit.\n"
            "Those gored by them will suffer\n"
            "both wounds and burns."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TaurosPaldeanBlazeBreed,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_TaurosPaldean,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,//
        .backPic = gMonBackPic_TaurosPaldeanBlazeBreed,
        .backPicSize = MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_TaurosPaldeanBlazeBreed,
        .shinyPalette = gMonShinyPalette_TaurosPaldeanBlazeBreed,
        .iconSprite = gMonIcon_TaurosPaldeanBlazeBreed,
        .iconPalIndex = 0,
        FOOTPRINT(Tauros)
        .isPaldeanForm = TRUE,
        .levelUpLearnset = sTaurosPaldeanBlazeBreedLevelUpLearnset,
        .teachableLearnset = sTaurosPaldeanBlazeBreedTeachableLearnset,
      //  .formSpeciesIdTable = sTaurosFormSpeciesIdTable,*/
        //.flags = F_PALDEAN_FORM,
      .enemyMonElevation = 0,
    },

    [SPECIES_TAUROS_PALDEAN_AQUA_BREED] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              75,
              120,
              105,
              100,
              30,
              70
        ),
        MON_TYPES(TYPE_DARK, TYPE_WATER),
        .catchRate = 45,
        .expYield = 211,
      //  .evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_ANGER_POINT},
        .abilityHidden = {ABILITY_CUD_CHEW, ABILITY_EARLY_BIRD},
        .bodyColor = BODY_COLOR_BLACK,
      /*   .speciesName = _("Tauros"),
        .cryId = CRY_TAUROS,
        .natDexNum = NATIONAL_DEX_TAUROS,
        .categoryName = _("Wild Bull"),
        .height = 14,
        .weight = 1100,
        .description = COMPOUND_STRING(
            "This Pokémon blasts water from holes on\n"
            "the tips of its horns--the high-pressure\n"
            "jets pierce right through\n"
            "Tauros’s enemies."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TaurosPaldeanAquaBreed,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_TaurosPaldean,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,//
        .backPic = gMonBackPic_TaurosPaldeanAquaBreed,
        .backPicSize = MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_TaurosPaldeanAquaBreed,
        .shinyPalette = gMonShinyPalette_TaurosPaldeanAquaBreed,
        .iconSprite = gMonIcon_TaurosPaldeanAquaBreed,
        .iconPalIndex = 0,
        FOOTPRINT(Tauros)
        .isPaldeanForm = TRUE,
        .levelUpLearnset = sTaurosPaldeanAquaBreedLevelUpLearnset,
        .teachableLearnset = sTaurosPaldeanAquaBreedTeachableLearnset,
      //  .formSpeciesIdTable = sTaurosFormSpeciesIdTable,*/
        //.flags = F_PALDEAN_FORM,
      .enemyMonElevation = 0,
    },

    [SPECIES_WOOPER_PALDEAN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              55,
              45,
              45,
              15,
              25,
              25
        ),
        MON_TYPES(TYPE_POISON, TYPE_GROUND),
        .catchRate = 255,
        .expYield = 42,
      //  .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_POISON_POINT, ABILITY_WATER_ABSORB  },
        .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
      /*   .speciesName = _("Wooper"),
        .cryId = CRY_WOOPER,
        .natDexNum = NATIONAL_DEX_WOOPER,
        .categoryName = _("Poison Fish"),
        .height = 4,
        .weight = 110,
        .description = COMPOUND_STRING(
            "After losing a territorial struggle,\n"
            "Wooper began living on land.\n"
            "The Pokémon changed over time, developing\n"
            "a poisonous film to protect its body."),
        .pokemonScale = 479,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WooperPaldean,
        .frontPicSize = MON_COORDS_SIZE(40, 32),
        .frontPicYOffset = 16,
        .frontAnimFrames = sAnims_WooperPaldean,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_WooperPaldean,
        .backPicSize = MON_COORDS_SIZE(64, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_WooperPaldean,
        .shinyPalette = gMonShinyPalette_WooperPaldean,
        .iconSprite = gMonIcon_WooperPaldean,
        .iconPalIndex = 2,
        FOOTPRINT(Wooper)
        .isPaldeanForm = TRUE,
        .levelUpLearnset = sWooperPaldeanLevelUpLearnset,
        .teachableLearnset = sWooperPaldeanTeachableLearnset,
      //  .formSpeciesIdTable = sWooperFormSpeciesIdTable,*/
        //.evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_CLODSIRE}),
        //.flags = F_PALDEAN_FORM,
      .enemyMonElevation = 0,
    },

//#if p_fAMILY_WALKING_WAKE
    [SPECIES_WALKING_WAKE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              99,
              83,
              91,
              109,
              125,
              83
       ),
        MON_TYPES(TYPE_WATER, TYPE_DRAGON),
        .catchRate = 5,
        .expYield = 295,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("WalkngWake"),
        .cryId = CRY_WALKING_WAKE,
        .natDexNum = NATIONAL_DEX_WALKING_WAKE,
        .categoryName = _("Paradox"),
        .height = 35,
        .weight = 2800,
        .description = COMPOUND_STRING(
            "This ferocious creature is shrouded in\n"
            "mystery. It's named after an aquatic\n"
            "monster mentioned in an old journal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WalkingWake,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_WalkingWake,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_WalkingWake,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_WalkingWake,
        .shinyPalette = gMonShinyPalette_WalkingWake,
        .iconSprite = gMonIcon_WalkingWake,
        .iconPalIndex = 2,
        //FOOTPRINT(WalkingWake)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sWalkingWakeLevelUpLearnset,
        //.teachableLearnset = sWalkingWakeTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_WALKING_WAKE

//#if p_fAMILY_IRON_LEAVES - vsonic do something with this
    [SPECIES_IRON_LEAVES] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              130,
              88,
              104,
              70,
              108
       ),
        MON_TYPES(TYPE_GRASS, TYPE_PSYCHIC),
        .catchRate = 5,
        .expYield = 295,
       // .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("IronLeaves"),
        .cryId = CRY_IRON_LEAVES,
        .natDexNum = NATIONAL_DEX_IRON_LEAVES,
        .categoryName = _("Paradox"),
        .height = 15,
        .weight = 1250,
        .description = COMPOUND_STRING(
            "According to the few eyewitness accounts\n"
            "that exist, it used its shining blades\n"
            "to julienne large trees and boulders."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronLeaves,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_IronLeaves,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronLeaves,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronLeaves,
        .shinyPalette = gMonShinyPalette_IronLeaves,
        .iconSprite = gMonIcon_IronLeaves,
        .iconPalIndex = 1,
        //FOOTPRINT(IronLeaves)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronLeavesLevelUpLearnset,
        //.teachableLearnset = sIronLeavesTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_LEAVES
[SPECIES_DIPPLIN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              80,
              80,
              110,
              40,
              95,
              80
        ),
        MON_TYPES(TYPE_GRASS, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 170,
      //  .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_SUPERSWEET_SYRUP, ABILITY_GLUTTONY  },
        .abilityHidden = {ABILITY_STICKY_HOLD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
      /*   .speciesName = _("Dipplin"),
        .cryId = CRY_DIPPLIN,
        .natDexNum = NATIONAL_DEX_DIPPLIN,
        .categoryName = _("Candy Apple"),
        .height = 4,
        .weight = 44,
        .description = COMPOUND_STRING(
            "Dipplin is two creatures in one Pokémon.\n"
            "Its evolution was triggered by a special\n"
            "apple grown only in one place."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dipplin,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_Dipplin,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Dipplin,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dipplin,
        .shinyPalette = gMonShinyPalette_Dipplin,
        .iconSprite = gMonIcon_Dipplin,
        .iconPalIndex = 1,
        //FOOTPRINT(Dipplin)
       */
        //.levelUpLearnset = sDipplinLevelUpLearnset,
        //.teachableLearnset = sDipplinTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_MOVE, MOVE_DRAGON_CHEER, 0, SPECIES_HYDRAPPLE}),
      .enemyMonElevation = 0,
    },

//#if p_fAMILY_POLTCHAGEIST
    [SPECIES_POLTCHAGEIST_COUNTERFEIT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              45,
              45,
              50,
              74,
              54
       ),
        MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 120,
        .expYield = 62,
       // .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE },
        .abilityHidden = {ABILITY_HEATPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Ptchageist"),
        .cryId = CRY_POLTCHAGEIST,
        .natDexNum = NATIONAL_DEX_POLTCHAGEIST,
        .categoryName = _("Matcha"),
        .height = 1,
        .weight = 11,
        .description = COMPOUND_STRING(
            "Supposedly, the regrets of a tea\n"
            "ceremony master who died before\n"
            "perfecting his craft lingered in some\n"
            "matcha and became a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Poltchageist,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Poltchageist,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Poltchageist,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Poltchageist,
        .shinyPalette = gMonShinyPalette_Poltchageist,
        .iconSprite = gMonIcon_Poltchageist,
        .iconPalIndex = 1,
        //FOOTPRINT(Poltchageist)
        */
        //.levelUpLearnset = sPoltchageistLevelUpLearnset,
        //.teachableLearnset = sPoltchageistTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_ITEM, 0/*ITEM_UNREMARKABLE_TEACUP*/, 0,  SPECIES_SINISTCHA_UNREMARKABLE}),
      .enemyMonElevation = 0,
    },//vsonic

    [SPECIES_POLTCHAGEIST_ARTISAN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              40,
              45,
              45,
              50,
              74,
              54
       ),
        MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 120,
        .expYield = 62,
       // .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE },
        .abilityHidden = {ABILITY_HEATPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Ptchageist"),
        .cryId = CRY_POLTCHAGEIST,
        .natDexNum = NATIONAL_DEX_POLTCHAGEIST,
        .categoryName = _("Matcha"),
        .height = 1,
        .weight = 11,
        .description = COMPOUND_STRING(
            "It has taken up residence in a very\n"
            "expensive tea caddy. It takes an\n"
            "expert to distinguish the expensive\n"
            "tea caddies from the cheap ones."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Poltchageist,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Poltchageist,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Poltchageist,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Poltchageist,
        .shinyPalette = gMonShinyPalette_Poltchageist,
        .iconSprite = gMonIcon_Poltchageist,
        .iconPalIndex = 1,
        //FOOTPRINT(Poltchageist)
        */
        //.levelUpLearnset = sPoltchageistLevelUpLearnset,
        //.teachableLearnset = sPoltchageistTeachableLearnset,
        //.evolutions = EVOLUTION({EVO_ITEM, 0/*ITEM_MASTERPIECE_TEACUP*/, 0,  SPECIES_SINISTCHA_MASTERPIECE}),
      .enemyMonElevation = 0,
    },//vsonic

    [SPECIES_SINISTCHA_UNREMARKABLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              71,
              60,
              106,
              70,
              121,
              80
       ),
        MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 60,
        .expYield = 178,
       // .evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE },
        .abilityHidden = {ABILITY_HEATPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Sinistcha"),
        .cryId = CRY_SINISTCHA,
        .natDexNum = NATIONAL_DEX_SINISTCHA,
        .categoryName = _("Matcha"),
        .height = 2,
        .weight = 22,
        .description = COMPOUND_STRING(
            "It pretends to be tea, trying to fool\n"
            "people into drinking it so it can\n"
            "drain their life-force. Its ruse is\n"
            "generally unsuccessful."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sinistcha,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Sinistcha,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Sinistcha,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sinistcha,
        .shinyPalette = gMonShinyPalette_Sinistcha,
        .iconSprite = gMonIcon_Sinistcha,
        .iconPalIndex = 1,
        //FOOTPRINT(Sinistcha)
        */
        //.levelUpLearnset = sSinistchaLevelUpLearnset,
        //.teachableLearnset = sSinistchaTeachableLearnset,
      .enemyMonElevation = 0,
    },
    [SPECIES_SINISTCHA_MASTERPIECE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              71,
              60,
              106,
              70,
              121,
              80
       ),
        MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 60,
        .expYield = 178,
       // .evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE },
        .abilityHidden = {ABILITY_HEATPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Sinistcha"),
        .cryId = CRY_SINISTCHA,
        .natDexNum = NATIONAL_DEX_SINISTCHA,
        .categoryName = _("Matcha"),
        .height = 2,
        .weight = 22,
        .description = COMPOUND_STRING(
            "The more stirring it does with the\n"
            "tea whisk on its head, the more\n"
            "energy it builds up. It does this to\n"
            "prepare for battle."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sinistcha,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_Sinistcha,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Sinistcha,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sinistcha,
        .shinyPalette = gMonShinyPalette_Sinistcha,
        .iconSprite = gMonIcon_Sinistcha,
        .iconPalIndex = 1,
        //FOOTPRINT(Sinistcha)
        */
        //.levelUpLearnset = sSinistchaLevelUpLearnset,
        //.teachableLearnset = sSinistchaTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_POLTCHAGEIST

//#if p_fAMILY_OKIDOGI
    [SPECIES_OKIDOGI] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              88,
              128,
              115,
              80,
              58,
              86
       ),
        MON_TYPES(TYPE_POISON, TYPE_FIGHTING),
        .catchRate = 3,
        .expYield = 278,
       // .evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TOXIC_CHAIN, ABILITY_NONE  },
        .abilityHidden = {ABILITY_GUARD_DOG, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Okidogi"),
        .cryId = CRY_OKIDOGI,
        .natDexNum = NATIONAL_DEX_OKIDOGI,
        .categoryName = _("Retainer"),
        .height = 18,
        .weight = 920,
        .description = COMPOUND_STRING(
            "After all its muscles were stimulated\n"
            "by the toxic chain around its neck,\n"
            "Okidogi transformed and gained\n"
            "a powerful physique."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Okidogi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Okidogi,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Okidogi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Okidogi,
        .shinyPalette = gMonShinyPalette_Okidogi,
        .iconSprite = gMonIcon_Okidogi,
        .iconPalIndex = 1,
        //FOOTPRINT(Okidogi)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sOkidogiLevelUpLearnset,
        //.teachableLearnset = sOkidogiTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_OKIDOGI

//#if p_fAMILY_MUNKIDORI //vsonic need rework apparently complete dogshit
    //think will attempt to buff with moves over stats don't feel like there's really  much 
    //to do here, think signature move poison uturn?  baneful bunker
    //over max power,
    [SPECIES_MUNKIDORI] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              88,
              75,
              66,
              106,
              130,
              90
       ),
        MON_TYPES(TYPE_POISON, TYPE_PSYCHIC),
        .catchRate = 3,
        .expYield = 278,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TOXIC_CHAIN, ABILITY_NONE },
        .abilityHidden = {ABILITY_FRISK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Munkidori"),
        .cryId = CRY_MUNKIDORI,
        .natDexNum = NATIONAL_DEX_MUNKIDORI,
        .categoryName = _("Retainer"),
        .height = 10,
        .weight = 122,
        .description = COMPOUND_STRING(
            "The chain is made from toxins that\n"
            "enhance capabilities. It stimulated\n"
            "Munkidori's brain and caused the\n"
            "Pokémon's psychic powers to bloom."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Munkidori,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_Munkidori,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Munkidori,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Munkidori,
        .shinyPalette = gMonShinyPalette_Munkidori,
        .iconSprite = gMonIcon_Munkidori,
        .iconPalIndex = 0,
        //FOOTPRINT(Munkidori)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sMunkidoriLevelUpLearnset,
        //.teachableLearnset = sMunkidoriTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_MUNKIDORI

//#if p_fAMILY_FEZANDIPITI
    [SPECIES_FEZANDIPITI] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              88,
              91,
              82,
              99,
              70,
              125
       ),
        MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = 3,
        .expYield = 278,
       // .evYield_SpDefense = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TOXIC_CHAIN, ABILITY_NONE  },
        .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Fezndipiti"),
        .cryId = CRY_FEZANDIPITI,
        .natDexNum = NATIONAL_DEX_FEZANDIPITI,
        .categoryName = _("Retainer"),
        .height = 14,
        .weight = 301,
        .description = COMPOUND_STRING(
            "Fezandipiti owes its beautiful looks and\n"
            "lovely voice to the toxic stimulants\n"
            "emanating from the chain wrapped around\n"
            "its body."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fezandipiti,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_Fezandipiti,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Fezandipiti,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fezandipiti,
        .shinyPalette = gMonShinyPalette_Fezandipiti,
        .iconSprite = gMonIcon_Fezandipiti,
        .iconPalIndex = 0,
        //FOOTPRINT(Fezandipiti)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sFezandipitiLevelUpLearnset,
        //.teachableLearnset = sFezandipitiTeachableLearnset,
      .enemyMonElevation = 0,
    },

    [SPECIES_OGERPON_TEAL_MASK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    },
    [SPECIES_OGERPON_WELLSPRING_MASK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    },
    [SPECIES_OGERPON_HEARTHFLAME_MASK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    },
    [SPECIES_OGERPON_CORNERSTONE_MASK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    },
    [SPECIES_URSALUNA_BLOODMOON] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
        /*//hp, atk, def, spd, spatk, spdef
        STATS(
              113,
              70,
              120,
              52,
              135,
              65
        ),
        MON_TYPES(TYPE_GROUND, TYPE_NORMAL),
        .catchRate = 5,
        .expYield = 275,
      //  .evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_MINDS_EYE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
      /*   .speciesName = _("Ursaluna"),
        .cryId = CRY_URSALUNA,
        .natDexNum = NATIONAL_DEX_URSALUNA,
        .categoryName = _("Peat"),
        .height = 27,
        .weight = 3330,
        .description = COMPOUND_STRING(
            "It crossed the sea and drifted\n"
            "ashore in a new land. Surviving in this\n"
            "place led it to take on a unique\n"
            "appearance and gain special powers."),
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 369,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_UrsalunaBloodmoon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        //.frontPicYOffset = 0,
        .frontAnimFrames = sAnims_UrsalunaBloodmoon,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_UrsalunaBloodmoon,
        .backPicSize = MON_COORDS_SIZE(64, 40),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_UrsalunaBloodmoon,
        .shinyPalette = gMonShinyPalette_UrsalunaBloodmoon,
        .iconSprite = gMonIcon_UrsalunaBloodmoon,
        .iconPalIndex = 2,
        //FOOTPRINT(UrsalunaBloodmoon)
       */
        //.levelUpLearnset = sUrsalunaBloodmoonLevelUpLearnset,
        //.teachableLearnset = sUrsalunaBloodmoonTeachableLearnset,
      //  .formSpeciesIdTable = sUrsalunaFormSpeciesIdTable,
      .enemyMonElevation = 0,
    },//thought about making an evo, think will give an item
    //to shift form one way, well doesn't need tobe one way.
    //but moxie2D brought up interesting idea
    //that this is actually a paradox mon.
    //since nothing evolves into it, and theres lore wise only one,
    //that really makes sense
    //so I won't change this into an evo vsonic

[SPECIES_ARCHALUDON] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              105,
              130,
              85,
              125,
              65
       ),
        MON_TYPES(TYPE_STEEL, TYPE_DRAGON),
        .catchRate = 10,
        .expYield = 300,
        //.evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_MEDIUM_FAST,
        MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_STAMINA, ABILITY_STURDY  },
        .abilityHidden = {ABILITY_STALWART, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        /*.speciesName = _("Archaludon"),
        .cryId = CRY_ARCHALUDON,
        .natDexNum = NATIONAL_DEX_ARCHALUDON,
        .categoryName = _("Alloy"),
        .height = 20,
        .weight = 600,
        .description = COMPOUND_STRING(
            "It gathers static electricity\n"
            "from its surroundings. The beams\n"
            "it launches when down on all fours\n"
            "are tremendously powerful."),
        .pokemonScale = 267,
        .pokemonOffset = 2,
        .trainerScale = 286,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_Archaludon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Archaludon,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Archaludon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Archaludon,
        .shinyPalette = gMonShinyPalette_Archaludon,
        .iconSprite = gMonIcon_Archaludon,
        .iconPalIndex = 0,
        //FOOTPRINT(Archaludon)
       */
        //.levelUpLearnset = sArchaludonLevelUpLearnset,
        //.teachableLearnset = sArchaludonTeachableLearnset,*/
      .enemyMonElevation = 0,
    },

//#endif //P_FAMILY_OGERPON
//missing archaludon and hydrapple flapple evo
[SPECIES_HYDRAPPLE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              106,
              80,
              110,
              44,
              120,
              80
       ),
        MON_TYPES(TYPE_GRASS, TYPE_DRAGON),
        .catchRate = 10,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_ERRATIC,
        MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_SUPERSWEET_SYRUP, ABILITY_REGENERATOR  },
        .abilityHidden = {ABILITY_STICKY_HOLD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        /*.speciesName = _("Hydrapple"),
        .cryId = CRY_HYDRAPPLE,
        .natDexNum = NATIONAL_DEX_HYDRAPPLE,
        .categoryName = _("Apple Hydra"),
        .height = 18,
        .weight = 930,
        .description = COMPOUND_STRING(
            "These capricious syrpents have\n"
            "banded together. On the rare\n"
            "occasion that their moods align,\n"
            "their true power is unleashed."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Hydrapple,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_Hydrapple,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Hydrapple,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Hydrapple,
        .shinyPalette = gMonShinyPalette_Hydrapple,
        .iconSprite = gMonIcon_Hydrapple,
        .iconPalIndex = 5,
        //FOOTPRINT(Hydrapple)
       
        .levelUpLearnset = sHydrappleLevelUpLearnset,
        .teachableLearnset = sHydrappleTeachableLearnset,*/
      .enemyMonElevation = 0,
    },



//#if p_fAMILY_GOUGING_FIRE
    [SPECIES_GOUGING_FIRE] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              105,
              115,
              121,
              91,
              65,
              93
       ),
        MON_TYPES(TYPE_FIRE, TYPE_DRAGON),
        .catchRate = 10,
        .expYield = 295,
       // .evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("GouginFire"),
        .cryId = CRY_GOUGING_FIRE,
        .natDexNum = NATIONAL_DEX_GOUGING_FIRE,
        .categoryName = _("Paradox"),
        .height = 35,
        .weight = 5900,
        .description = COMPOUND_STRING(
            "There are scant few reports of\n"
            "this creature being sighted.\n"
            "One short video shows it rampaging,\n"
            "and spouting pillars of flame."),
        .pokemonScale = 259,
        .pokemonOffset = 0,
        .trainerScale = 345,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_GougingFire,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_GougingFire,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GougingFire,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GougingFire,
        .shinyPalette = gMonShinyPalette_GougingFire,
        .iconSprite = gMonIcon_GougingFire,
        .iconPalIndex = 5,
        //FOOTPRINT(GougingFire)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sGougingFireLevelUpLearnset,
        //.teachableLearnset = sGougingFireTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_GOUGING_FIRE

//#if p_fAMILY_RAGING_BOLT
    [SPECIES_RAGING_BOLT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              125,
              73,
              91,
              75,
              137,
              89
       ),
        MON_TYPES(TYPE_ELECTRIC, TYPE_DRAGON),
        .catchRate = 10,
        .expYield = 295,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("RagingBolt"),
        .cryId = CRY_RAGING_BOLT,
        .natDexNum = NATIONAL_DEX_RAGING_BOLT,
        .categoryName = _("Paradox"),
        .height = 52,
        .weight = 4800,
        .description = COMPOUND_STRING(
            "It bears resemblance to a Pokémon\n"
            "that became a hot topic for a short\n"
            "while after a paranomal magazine\n"
            "touted it as Raikou's ancestor."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 345,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_RagingBolt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_RagingBolt,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_RagingBolt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_RagingBolt,
        .shinyPalette = gMonShinyPalette_RagingBolt,
        .iconSprite = gMonIcon_RagingBolt,
        .iconPalIndex = 2,
        //FOOTPRINT(RagingBolt)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sRagingBoltLevelUpLearnset,
        //.teachableLearnset = sRagingBoltTeachableLearnset,
      .enemyMonElevation = 0,
    },  //alt entei/rakou 100%  not using
//#endif //P_FAMILY_RAGING_BOLT

//#if p_fAMILY_IRON_BOULDER
    [SPECIES_IRON_BOULDER] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              120,
              80,
              124,
              68,
              108
       ),
        MON_TYPES(TYPE_ROCK, TYPE_PSYCHIC),
        .catchRate = 10,
        .expYield = 295,
       // .evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("IronBouldr"),
        .cryId = CRY_IRON_BOULDER,
        .natDexNum = NATIONAL_DEX_IRON_BOULDER,
        .categoryName = _("Paradox"),
        .height = 15,
        .weight = 1625,
        .description = COMPOUND_STRING(
            "It was named after a mysterious\n"
            "object recorded in an old book.\n"
            "Its body seems to be metallic."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 336,
        .trainerOffset = 4,
        .frontPic = gMonFrontPic_IronBoulder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_IronBoulder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronBoulder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronBoulder,
        .shinyPalette = gMonShinyPalette_IronBoulder,
        .iconSprite = gMonIcon_IronBoulder,
        .iconPalIndex = 5,
        //FOOTPRINT(IronBoulder)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronBoulderLevelUpLearnset,
        //.teachableLearnset = sIronBoulderTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_BOULDER

//#if p_fAMILY_IRON_CROWN
    [SPECIES_IRON_CROWN] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              72,
              100,
              98,
              122,
              108
       ),
        MON_TYPES(TYPE_STEEL, TYPE_PSYCHIC),
        .catchRate = 10,
        .expYield = 295,
       // .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Iron Crown"),
        .cryId = CRY_IRON_CROWN,
        .natDexNum = NATIONAL_DEX_IRON_CROWN,
        .categoryName = _("Paradox"),
        .height = 16,
        .weight = 1560,
        .description = COMPOUND_STRING(
            "It resembles a mysterious object\n"
            "introduced in a paranormal magazine\n"
            "as a cutting-edge weapon\n"
            "shaped like Cobalion."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_IronCrown,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_IronCrown,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronCrown,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronCrown,
        .shinyPalette = gMonShinyPalette_IronCrown,
        .iconSprite = gMonIcon_IronCrown,
        .iconPalIndex = 3,
        //FOOTPRINT(IronCrown)
        .isParadoxForm = TRUE,
        */
        //.levelUpLearnset = sIronCrownLevelUpLearnset,
        //.teachableLearnset = sIronCrownTeachableLearnset,
      .enemyMonElevation = 0,
    },
//#endif //P_FAMILY_IRON_CROWN

//#if p_fAMILY_TERAPAGOS
    [SPECIES_TERAPAGOS_NORMAL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              90,
              65,
              85,
              60,
              65,
              85
       ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 90,
       // .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TERA_SHIFT, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = FALSE,
        /*.speciesName = _("Terapagos"),
        .cryId = CRY_TERAPAGOS,
        .natDexNum = NATIONAL_DEX_TERAPAGOS,
        .categoryName = _("Tera"),
        .height = 2,
        .weight = 65,
        .description = COMPOUND_STRING(
            "Terapagos protects itself using its\n"
            "power to transform energy into hard\n"
            "crystals. This Pokémon is the source\n"
            "of the Terastal phenomenon."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        //.frontPic = gMonFrontPic_TerapagosNormal,
        //.frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_TerapagosNormal,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        //.backPic = gMonBackPic_TerapagosNormal,
        //.backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        //.palette = gMonPalette_TerapagosNormal,
        //.shinyPalette = gMonShinyPalette_TerapagosNormal,
        .iconSprite = gMonIcon_TerapagosNormal,
        .iconPalIndex = 0,
        //FOOTPRINT(Terapagos)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sTerapagosLevelUpLearnset,
        //.teachableLearnset = sTerapagosTeachableLearnset,
        //.formSpeciesIdTable = sTerapagosFormSpeciesIdTable,
        //.formChangeTable = sTerapagosFormChangeTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_TERAPAGOS_TERASTAL] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              95,
              95,
              110,
              85,
              105,
              110
        ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 120,
       // .evYield_Defense = 2,
       // .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TERA_SHELL, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Terapagos"),
        .cryId = CRY_TERAPAGOS,
        .natDexNum = NATIONAL_DEX_TERAPAGOS,
        .categoryName = _("Tera"),
        .height = 3,
        .weight = 160,
        .description = COMPOUND_STRING(
            "The shell is made of crystallized\n"
            "Terastal energy. When struck by a move,\n"
            "this shell absorbs the move's energy\n"
            "and transfers it to Terapagos."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        //.frontPic = gMonFrontPic_TerapagosTerastal,
        //.frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_TerapagosTerastal,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        //.backPic = gMonBackPic_TerapagosTerastal,
        //.backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        //.palette = gMonPalette_TerapagosTerastal,
        //.shinyPalette = gMonShinyPalette_TerapagosTerastal,
        .iconSprite = gMonIcon_TerapagosTerastal,
        .iconPalIndex = 0,
        //FOOTPRINT(Terapagos)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sTerapagosLevelUpLearnset,
        //.teachableLearnset = sTerapagosTeachableLearnset,
        //.formSpeciesIdTable = sTerapagosFormSpeciesIdTable,
        //.formChangeTable = sTerapagosFormChangeTable,
      .enemyMonElevation = 0,
    },

    [SPECIES_TERAPAGOS_STELLAR] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              160,
              105,
              110,
              85,
              130,
              110
        ),
        MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 140,
       // .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = FRIENDSHIP_STANDARD,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_TERAFORM_ZERO, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Terapagos"),
        .cryId = CRY_TERAPAGOS,
        .natDexNum = NATIONAL_DEX_TERAPAGOS,
        .categoryName = _("Tera"),
        .height = 17,
        .weight = 770,
        .description = COMPOUND_STRING(
            "An old expedition journal describes the\n"
            "sight of this Pokémon buried in the,\n"
            "depths of the earth as resembling a\n"
            "planet floating in space."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        //.frontPic = gMonFrontPic_TerapagosStellar,
        //.frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_TerapagosStellar,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        //.backPic = gMonBackPic_TerapagosStellar,
        //.backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        //.palette = gMonPalette_TerapagosStellar,
        //.shinyPalette = gMonShinyPalette_TerapagosStellar,
        .iconSprite = gMonIcon_TerapagosStellar,
        .iconPalIndex = 0,
        //FOOTPRINT(Terapagos)
        .isLegendary = TRUE,
        */
        //.levelUpLearnset = sTerapagosLevelUpLearnset,
        //.teachableLearnset = sTerapagosTeachableLearnset,
        //.formSpeciesIdTable = sTerapagosFormSpeciesIdTable,
        //.formChangeTable = sTerapagosFormChangeTable,
      .enemyMonElevation = 0,
    },//since stellar type is a bad version of my own normal buffs I'll just scrap it
    //will only allow stellar form for terapagos and treat it like shadow pokemon,
    //where it keeps a permanent stellar tera blast that is super to everything
    //stellar type for terapagos will give stab on all moves
    //change, don't remove enemy terra, just prevent other mon from using terra if this is on the field
    //based on ability  stellar will still be super against other terra
    //vsonic
//#endif //P_FAMILY_TERAPAGOS

////#if p_fAMILY_PECHARUNT
    [SPECIES_PECHARUNT] =
    {
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
            /*//hp, atk, def, spd, spatk, spdef
        STATS(
              88,
              88,
              160,
              88,
              88,
              88
        ),
        MON_TYPES(TYPE_POISON, TYPE_GHOST),
        .catchRate = 3,
        .expYield = 300,
       // .evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = FRIENDSHIP_LEGENDARY,
        .growthRate = GROWTH_SLOW,
        MON_EGG_GROUPS(EGG_GROUP_UNDISCOVERED),
        .abilities = { ABILITY_POISON_PUPPETEER, ABILITY_NONE },
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,*/
        //.floating = TRUE,
        /*.speciesName = _("Pecharunt"),
        .cryId = CRY_PECHARUNT,
        .natDexNum = NATIONAL_DEX_PECHARUNT,
        .categoryName = _("Subjugation"),
        .height = 3,
        .weight = 3,
        .description = COMPOUND_STRING(
            "It feeds others toxic mochi that\n"
            "draw out desires and capabilities.\n"
            "Those who eat the mochi fall under\n"
            "Pecharunt's control, chained to its will."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_Pecharunt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_Pecharunt,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pecharunt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pecharunt,
        .shinyPalette = gMonShinyPalette_Pecharunt,
        .iconSprite = gMonIcon_Pecharunt,
        .iconPalIndex = 0,
        //FOOTPRINT(Pecharunt)
        .isMythical = TRUE,
        */
        //.levelUpLearnset = sPecharuntLevelUpLearnset,
        //.teachableLearnset = sPecharuntTeachableLearnset,
      .enemyMonElevation = 0,
    },
  [SPECIES_VENUSAUR_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VenusaurMega,
  [SPECIES_CHARIZARD_MEGA_X] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CharizardMegaX,
  [SPECIES_CHARIZARD_MEGA_Y] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CharizardMegaY,
  [SPECIES_BLASTOISE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BlastoiseMega,
  [SPECIES_BEEDRILL_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BeedrillMega,
  [SPECIES_PIDGEOT_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PidgeotMega,
  [SPECIES_ALAKAZAM_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlakazamMega,
  [SPECIES_SLOWBRO_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SlowbroMega,
  [SPECIES_GENGAR_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GengarMega,
  [SPECIES_KANGASKHAN_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //KangaskhanMega,
  [SPECIES_PINSIR_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PinsirMega,
  [SPECIES_GYARADOS_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GyaradosMega,
  [SPECIES_AERODACTYL_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AerodactylMega,
  [SPECIES_MEWTWO_MEGA_X] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MewtwoMegaX,
  [SPECIES_MEWTWO_MEGA_Y] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MewtwoMegaY,
  [SPECIES_AMPHAROS_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AmpharosMega,
  [SPECIES_STEELIX_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SteelixMega,
  [SPECIES_SCIZOR_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ScizorMega,
  [SPECIES_HERACROSS_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //HeracrossMega,
  [SPECIES_HOUNDOOM_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //HoundoomMega,
  [SPECIES_TYRANITAR_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TyranitarMega,
  [SPECIES_SCEPTILE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SceptileMega,
  [SPECIES_BLAZIKEN_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BlazikenMega,
  [SPECIES_SWAMPERT_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SwampertMega,
  [SPECIES_GARDEVOIR_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GardevoirMega,
  [SPECIES_SABLEYE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SableyeMega,
  [SPECIES_MAWILE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MawileMega,
  [SPECIES_AGGRON_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AggronMega,
  [SPECIES_MEDICHAM_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MedichamMega,
  [SPECIES_MANECTRIC_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ManectricMega,
  [SPECIES_SHARPEDO_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SharpedoMega,
  [SPECIES_CAMERUPT_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CameruptMega,
  [SPECIES_ALTARIA_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AltariaMega,
  [SPECIES_BANETTE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BanetteMega,
  [SPECIES_ABSOL_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AbsolMega,
  [SPECIES_GLALIE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GlalieMega,
  [SPECIES_SALAMENCE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SalamenceMega,
  [SPECIES_METAGROSS_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MetagrossMega,
  [SPECIES_LATIAS_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LatiasMega,
  [SPECIES_LATIOS_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LatiosMega,
  [SPECIES_LOPUNNY_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LopunnyMega,
  [SPECIES_GARCHOMP_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GarchompMega,
  [SPECIES_LUCARIO_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LucarioMega,
  [SPECIES_ABOMASNOW_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AbomasnowMega,
  [SPECIES_GALLADE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GalladeMega,
  [SPECIES_AUDINO_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AudinoMega,
  [SPECIES_DIANCIE_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DiancieMega,
  [SPECIES_RAYQUAZA_MEGA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RayquazaMega,
  [SPECIES_KYOGRE_PRIMAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //KyogrePrimal,
  [SPECIES_GROUDON_PRIMAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GroudonPrimal,
  [SPECIES_RATTATA_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RattataAlolan,
  [SPECIES_RATICATE_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RaticateAlolan,
  [SPECIES_RAICHU_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RaichuAlolan,
  [SPECIES_SANDSHREW_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SandshrewAlolan,
  [SPECIES_SANDSLASH_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SandslashAlolan,
  [SPECIES_VULPIX_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VulpixAlolan,
  [SPECIES_NINETALES_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //NinetalesAlolan,
  [SPECIES_DIGLETT_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DiglettAlolan,
  [SPECIES_DUGTRIO_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DugtrioAlolan,
  [SPECIES_MEOWTH_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MeowthAlolan,
  [SPECIES_PERSIAN_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PersianAlolan,
  [SPECIES_GEODUDE_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GeodudeAlolan,
  [SPECIES_GRAVELER_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GravelerAlolan,
  [SPECIES_GOLEM_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GolemAlolan,
  [SPECIES_GRIMER_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GrimerAlolan,
  [SPECIES_MUK_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MukAlolan,
  [SPECIES_EXEGGUTOR_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ExeggutorAlolan,
  [SPECIES_MAROWAK_ALOLAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MarowakAlolan,
  [SPECIES_MEOWTH_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MeowthGalarian,
  [SPECIES_PONYTA_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PonytaGalarian,
  [SPECIES_RAPIDASH_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RapidashGalarian,
  [SPECIES_SLOWPOKE_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SlowpokeGalarian,
  [SPECIES_SLOWBRO_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SlowbroGalarian,
  [SPECIES_FARFETCHD_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FarfetchdGalarian,
  [SPECIES_WEEZING_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //WeezingGalarian,
  [SPECIES_MR_MIME_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MrMimeGalarian,
  [SPECIES_ARTICUNO_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ArticunoGalarian,
  [SPECIES_ZAPDOS_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ZapdosGalarian,
  [SPECIES_MOLTRES_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MoltresGalarian,
  [SPECIES_SLOWKING_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SlowkingGalarian,
  [SPECIES_CORSOLA_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CorsolaGalarian,
  [SPECIES_ZIGZAGOON_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ZigzagoonGalarian,
  [SPECIES_LINOONE_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LinooneGalarian,
  [SPECIES_DARUMAKA_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DarumakaGalarian,
  [SPECIES_DARMANITAN_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DarmanitanGalarian,
  [SPECIES_YAMASK_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //YamaskGalarian,
  [SPECIES_STUNFISK_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //StunfiskGalarian,
  [SPECIES_GROWLITHE_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GrowlitheHisuian,
  [SPECIES_ARCANINE_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ArcanineHisuian,
  [SPECIES_VOLTORB_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VoltorbHisuian,
  [SPECIES_ELECTRODE_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ElectrodeHisuian,
  [SPECIES_TYPHLOSION_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TyphlosionHisuian,
  [SPECIES_QWILFISH_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //QwilfishHisuian,
  [SPECIES_SNEASEL_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SneaselHisuian,
  [SPECIES_SAMUROTT_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SamurottHisuian,
  [SPECIES_LILLIGANT_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LilligantHisuian,
  [SPECIES_ZORUA_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ZoruaHisuian,
  [SPECIES_ZOROARK_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ZoroarkHisuian,
  [SPECIES_BRAVIARY_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BraviaryHisuian,
  [SPECIES_SLIGGOO_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SliggooHisuian,
  [SPECIES_GOODRA_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GoodraHisuian,
  [SPECIES_AVALUGG_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AvaluggHisuian,
  [SPECIES_DECIDUEYE_HISUIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DecidueyeHisuian,
  [SPECIES_PIKACHU_COSPLAY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuCosplay,
  [SPECIES_PIKACHU_ROCK_STAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuRockStar,
  [SPECIES_PIKACHU_BELLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuBelle,
  [SPECIES_PIKACHU_POP_STAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuPopStar,
  [SPECIES_PIKACHU_PH_D] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuPhD,
  [SPECIES_PIKACHU_LIBRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuLibre,
  [SPECIES_PIKACHU_ORIGINAL_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuOriginalCap,
  [SPECIES_PIKACHU_HOENN_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuHoennCap,
  [SPECIES_PIKACHU_SINNOH_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuSinnohCap,
  [SPECIES_PIKACHU_UNOVA_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuUnovaCap,
  [SPECIES_PIKACHU_KALOS_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuKalosCap,
  [SPECIES_PIKACHU_ALOLA_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuAlolaCap,
  [SPECIES_PIKACHU_PARTNER_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuPartnerCap,
  [SPECIES_PIKACHU_WORLD_CAP] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PikachuWorldCap,
  [SPECIES_PICHU_SPIKY_EARED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //PichuSpikyEared,
  [SPECIES_CASTFORM_SUNNY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CastformSunny,
  [SPECIES_CASTFORM_RAINY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CastformRainy,
  [SPECIES_CASTFORM_SNOWY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CastformSnowy,
  [SPECIES_DEOXYS_ATTACK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DeoxysAttack,
  [SPECIES_DEOXYS_DEFENSE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DeoxysDefense,
  [SPECIES_DEOXYS_SPEED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DeoxysSpeed,
  [SPECIES_BURMY_SANDY_CLOAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BurmySandyCloak,
  [SPECIES_BURMY_TRASH_CLOAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BurmyTrashCloak,
  [SPECIES_WORMADAM_SANDY_CLOAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //WormadamSandyCloak,
  [SPECIES_WORMADAM_TRASH_CLOAK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //WormadamTrashCloak,
  [SPECIES_CHERRIM_SUNSHINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //CherrimSunshine,
  [SPECIES_SHELLOS_EAST_SEA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ShellosEastSea,
  [SPECIES_GASTRODON_EAST_SEA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GastrodonEastSea,
  [SPECIES_ROTOM_HEAT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RotomHeat,
  [SPECIES_ROTOM_WASH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RotomWash,
  [SPECIES_ROTOM_FROST] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RotomFrost,
  [SPECIES_ROTOM_FAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RotomFan,
  [SPECIES_ROTOM_MOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //RotomMow,
  [SPECIES_GIRATINA_ORIGIN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GiratinaOrigin,
  [SPECIES_SHAYMIN_SKY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ShayminSky,
  [SPECIES_ARCEUS_FIGHTING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_FLYING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_POISON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_GROUND] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_ROCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_BUG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_GHOST] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_STEEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_FIRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_WATER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_GRASS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_ELECTRIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_PSYCHIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_ICE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_DRAGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_DARK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_ARCEUS_FAIRY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Arceus,
  [SPECIES_BASCULIN_BLUE_STRIPED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BasculinBlueStriped,
  [SPECIES_BASCULIN_WHITE_STRIPED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //BasculinWhiteStriped,
  [SPECIES_DARMANITAN_ZEN_MODE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DarmanitanZenMode,
  [SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DarmanitanZenModeGalarian,
  [SPECIES_DEERLING_SUMMER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DeerlingSummer,
  [SPECIES_DEERLING_AUTUMN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DeerlingAutumn,
  [SPECIES_DEERLING_WINTER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //DeerlingWinter,
  [SPECIES_SAWSBUCK_SUMMER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SawsbuckSummer,
  [SPECIES_SAWSBUCK_AUTUMN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SawsbuckAutumn,
  [SPECIES_SAWSBUCK_WINTER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //SawsbuckWinter,
  [SPECIES_TORNADUS_THERIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //TornadusTherian,
  [SPECIES_THUNDURUS_THERIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ThundurusTherian,
  [SPECIES_LANDORUS_THERIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LandorusTherian,
  [SPECIES_ENAMORUS_THERIAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //EnamorusTherian,
  [SPECIES_KYUREM_WHITE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //KyuremWhite,
  [SPECIES_KYUREM_BLACK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //KyuremBlack,
  [SPECIES_KELDEO_RESOLUTE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //KeldeoResolute,
  [SPECIES_MELOETTA_PIROUETTE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MeloettaPirouette,
  [SPECIES_GENESECT_DOUSE_DRIVE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Genesect,
  [SPECIES_GENESECT_SHOCK_DRIVE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Genesect,
  [SPECIES_GENESECT_BURN_DRIVE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Genesect,
  [SPECIES_GENESECT_CHILL_DRIVE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Genesect,
  [SPECIES_GRENINJA_ASH] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //GreninjaAsh,
  [SPECIES_VIVILLON_POLAR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonPolar,
  [SPECIES_VIVILLON_TUNDRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonTundra,
  [SPECIES_VIVILLON_CONTINENTAL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonContinental,
  [SPECIES_VIVILLON_GARDEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonGarden,
  [SPECIES_VIVILLON_ELEGANT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonElegant,
  [SPECIES_VIVILLON_MEADOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonMeadow,
  [SPECIES_VIVILLON_MODERN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonModern,
  [SPECIES_VIVILLON_MARINE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonMarine,
  [SPECIES_VIVILLON_ARCHIPELAGO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonArchipelago,
  [SPECIES_VIVILLON_HIGH_PLAINS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonHighPlains,
  [SPECIES_VIVILLON_SANDSTORM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonSandstorm,
  [SPECIES_VIVILLON_RIVER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonRiver,
  [SPECIES_VIVILLON_MONSOON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonMonsoon,
  [SPECIES_VIVILLON_SAVANNA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonSavanna,
  [SPECIES_VIVILLON_SUN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonSun,
  [SPECIES_VIVILLON_OCEAN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonOcean,
  [SPECIES_VIVILLON_JUNGLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonJungle,
  [SPECIES_VIVILLON_FANCY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonFancy,
  [SPECIES_VIVILLON_POKE_BALL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //VivillonPokeBall,
  [SPECIES_UNFEZANT_FEMALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Unfezant_Female
  [SPECIES_PYROAR_FEMALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pyroar_Female,
  [SPECIES_FLABEBE_YELLOW_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlabebeYellowFlower,
  [SPECIES_FLABEBE_ORANGE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlabebeOrangeFlower,
  [SPECIES_FLABEBE_BLUE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlabebeBlueFlower,
  [SPECIES_FLABEBE_WHITE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlabebeWhiteFlower,
  [SPECIES_FLOETTE_YELLOW_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FloetteYellowFlower,
  [SPECIES_FLOETTE_ORANGE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FloetteOrangeFlower,
  [SPECIES_FLOETTE_BLUE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FloetteBlueFlower,
  [SPECIES_FLOETTE_WHITE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FloetteWhiteFlower,
  [SPECIES_FLOETTE_ETERNAL_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FloetteEternalFlower,
  [SPECIES_FLORGES_YELLOW_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlorgesYellowFlower,
  [SPECIES_FLORGES_ORANGE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlorgesOrangeFlower,
  [SPECIES_FLORGES_BLUE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlorgesBlueFlower,
  [SPECIES_FLORGES_WHITE_FLOWER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FlorgesWhiteFlower,
  [SPECIES_FURFROU_HEART_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouHeartTrim,
  [SPECIES_FURFROU_STAR_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouStarTrim,
  [SPECIES_FURFROU_DIAMOND_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouDiamondTrim,
  [SPECIES_FURFROU_DEBUTANTE_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouDebutanteTrim,
  [SPECIES_FURFROU_MATRON_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouMatronTrim,
  [SPECIES_FURFROU_DANDY_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouDandyTrim,
  [SPECIES_FURFROU_LA_REINE_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouLaReineTrim,
  [SPECIES_FURFROU_KABUKI_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouKabukiTrim,
  [SPECIES_FURFROU_PHARAOH_TRIM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //FurfrouPharaohTrim,
  [SPECIES_MEOWSTIC_FEMALE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Meowstic_Female,
  [SPECIES_AEGISLASH_BLADE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AegislashBlade,
  [SPECIES_PUMPKABOO_SMALL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
  [SPECIES_PUMPKABOO_LARGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
  [SPECIES_PUMPKABOO_SUPER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
  [SPECIES_GOURGEIST_SMALL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gourgeist,
  [SPECIES_GOURGEIST_LARGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gourgeist,
  [SPECIES_GOURGEIST_SUPER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Gourgeist,
  [SPECIES_XERNEAS_ACTIVE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //XerneasActive,
  [SPECIES_ZYGARDE_10] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zygarde10,
  [SPECIES_ZYGARDE_10_POWER_CONSTRUCT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zygarde10,
  [SPECIES_ZYGARDE_50_POWER_CONSTRUCT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zygarde,
  [SPECIES_ZYGARDE_COMPLETE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //ZygardeComplete,
  [SPECIES_HOOPA_UNBOUND] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //HoopaUnbound,
  [SPECIES_ORICORIO_POM_POM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //OricorioPomPom,
  [SPECIES_ORICORIO_PAU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //OricorioPau,
  [SPECIES_ORICORIO_SENSU] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //OricorioSensu,
  [SPECIES_LYCANROC_MIDNIGHT] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LycanrocMidnight,
  [SPECIES_LYCANROC_DUSK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //LycanrocDusk,
  [SPECIES_WISHIWASHI_SCHOOL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //WishiwashiSchool,
  [SPECIES_SILVALLY_FIGHTING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_FLYING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_POISON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_GROUND] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_ROCK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_BUG] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_GHOST] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_STEEL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_FIRE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_WATER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_GRASS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_ELECTRIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_PSYCHIC] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_ICE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_DRAGON] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_DARK] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_SILVALLY_FAIRY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Silvally,
  [SPECIES_MINIOR_METEOR_ORANGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
  [SPECIES_MINIOR_METEOR_YELLOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
  [SPECIES_MINIOR_METEOR_GREEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
  [SPECIES_MINIOR_METEOR_BLUE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
  [SPECIES_MINIOR_METEOR_INDIGO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
  [SPECIES_MINIOR_METEOR_VIOLET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Minior,
  [SPECIES_MINIOR_CORE_RED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreRed,
  [SPECIES_MINIOR_CORE_ORANGE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreOrange,
  [SPECIES_MINIOR_CORE_YELLOW] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreYellow,
  [SPECIES_MINIOR_CORE_GREEN] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreGreen,
  [SPECIES_MINIOR_CORE_BLUE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreBlue,
  [SPECIES_MINIOR_CORE_INDIGO] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreIndigo,
  [SPECIES_MINIOR_CORE_VIOLET] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MiniorCoreViolet,
  [SPECIES_MIMIKYU_BUSTED] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MimikyuBusted,
  [SPECIES_NECROZMA_DUSK_MANE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //NecrozmaDuskMane,
  [SPECIES_NECROZMA_DAWN_WINGS] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //NecrozmaDawnWings,
  [SPECIES_NECROZMA_ULTRA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //NecrozmaUltra,
  [SPECIES_MAGEARNA_ORIGINAL_COLOR] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //MagearnaOriginalColor,
  [SPECIES_CRAMORANT_GULPING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cramorant_Gulping,
  [SPECIES_CRAMORANT_GORGING] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Cramorant_Gorging,
  [SPECIES_TOXTRICITY_LOW_KEY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Toxtricity_Low_key,
      //[SPECIES_SINISTEA_ANTIQUE]                = gMonIcon_Sinistea_Antique,
      //[SPECIES_POLTEAGEIST_ANTIQUE]             = gMonIcon_PolteaGeist_Antique,
      
    //Alcremie forms
    [SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_BLUEBERRY_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_RUBY_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_MINT_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_LEMON_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_SALTED_CREAM] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    [SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0), //gMonIcon_Alcremie
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    

    [SPECIES_EISCUE_NOICE_FACE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eiscue_noice_face,
    [SPECIES_INDEEDEE_FEMALE] = 
    {  
      //PIC_DATA(Indeedee_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Indeedee_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Indeedee_Female),
      PIC_DATA_ICON_INDEX(Indeedee_Female,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Indeedee_Female,
    [SPECIES_MORPEKO_HANGRY] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Morpeko_Hangry,
    [SPECIES_ZACIAN_CROWNED_SWORD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zacian_Crowned_Sword,
    [SPECIES_ZAMAZENTA_CROWNED_SHIELD] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zamazenta_Crowned_Shield,
    [SPECIES_ETERNATUS_ETERNAMAX] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Eternatus_Eternamax,
    [SPECIES_URSHIFU_RAPID_STRIKE_STYLE] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Urshifu_Rapid, //think last value needs no comma, nope doesn't matter but using comma is better in case you plan to add more
    [SPECIES_ZARUDE_DADA] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Zarude_Dada,
    [SPECIES_CALYREX_ICE_RIDER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CircledQuestionMark),
      PIC_DATA_ICON_INDEX(CalyrexIceRider,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Calyrex_Ice_Rider,
    [SPECIES_CALYREX_SHADOW_RIDER] = 
    {  
      //PIC_DATA(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      //PALETTES(CalyrexShadowRider),
      PIC_DATA_ICON_INDEX(CalyrexShadowRider,0), //names w dashes are in icons only, can be pushsed to pallete and front/back pics
      .enemyMonElevation = 0,
    }, //Calyrex_Shadow_Rider,
    [SPECIES_BASCULEGION_FEMALE] = 
    {  
      //PIC_DATA(Basculegion_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculegion_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Basculegion_Female),
      PIC_DATA_ICON_INDEX(Basculegion_Female,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
    [SPECIES_FRILLISH_FEMALE] = 
    {  
      //PIC_DATA(Basculegion_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculegion_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Basculegion_Female),
      PIC_DATA_ICON_INDEX(Basculegion_Female,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
    [SPECIES_JELLICENT_FEMALE] = 
    {  
      //PIC_DATA(Basculegion_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculegion_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Basculegion_Female),
      PIC_DATA_ICON_INDEX(Basculegion_Female,0),
      //TAG(SPECIES_NONE),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
};
