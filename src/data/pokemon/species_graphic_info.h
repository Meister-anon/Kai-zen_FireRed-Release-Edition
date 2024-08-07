
#define FRONT_PIC(sprite)                    \
        .frontPic = gMonFrontPic_## sprite                 

#define FRONT_PIC_FEMALE(sprite, width, height)             \
        .frontPicFemale = gMonFrontPic_## sprite##F,        \
        .frontPicSizeFemale = MON_COORDS_SIZE(width, height)

#define BACK_PIC(sprite)                     \
        .backPic = gMonBackPic_## sprite                  

#define FRONT_COORD(size, y_offset)                    \
        .frontCoordSize = size,                 \
        .frontPicYOffset = y_offset

#define BACK_COORD(size, y_offset)                    \
        .backCoordSize = size,                 \
        .backPicYOffset = y_offset

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

#define PAL(pal)  .palette = gMonPalette_## pal

#define SHINYPAL(pal) .shinyPalette = gMonShinyPalette_## pal


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
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(CircledQuestionMark, 0),
      .enemyMonElevation = 0,
    }, //QuestionMark, 
[SPECIES_BULBASAUR] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x64, 0x10),
      PIC_DATA_ICON_INDEX(Bulbasaur, 1),
      .enemyMonElevation = 0,
    }, //Bulbasaur,
[SPECIES_IVYSAUR] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Ivysaur, 1),
      .enemyMonElevation = 0,
    }, //Ivysaur,
[SPECIES_VENUSAUR] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Venusaur, 1),
      .enemyMonElevation = 0,
    }, //Venusaur,
[SPECIES_CHARMANDER] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Charmander, 0),
      .enemyMonElevation = 0,
    }, //Charmander,
[SPECIES_CHARMELEON] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Charmeleon, 0),
      .enemyMonElevation = 0,
    }, //Charmeleon,
[SPECIES_CHARIZARD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Charizard, 0),
      .enemyMonElevation = 0,
    }, //Charizard,
[SPECIES_SQUIRTLE] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x75, 0x0f),
      PIC_DATA_ICON_INDEX(Squirtle, 0),
      .enemyMonElevation = 0,
    }, //Squirtle,
[SPECIES_WARTORTLE] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Wartortle, 2),
      .enemyMonElevation = 0,
    }, //Wartortle,
[SPECIES_BLASTOISE] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Blastoise, 2),
      .enemyMonElevation = 0,
    }, //Blastoise,
[SPECIES_CATERPIE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x55, 0x0f),
      PIC_DATA_ICON_INDEX(Caterpie, 1),
      .enemyMonElevation = 0,
    }, //Caterpie,
[SPECIES_METAPOD] = 
    {  
      FRONT_COORD(0x54, 14),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Metapod, 1),
      .enemyMonElevation = 0,
    }, //Metapod,
[SPECIES_BUTTERFREE] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Butterfree, 0),
      .enemyMonElevation = 8,
    }, //Butterfree,
[SPECIES_WEEDLE] = 
    {  
      FRONT_COORD(0x54, 13),
      BACK_COORD(0x56, 0x0b),
      PIC_DATA_ICON_INDEX(Weedle, 1),
      .enemyMonElevation = 0,
    }, //Weedle,
[SPECIES_KAKUNA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x46, 0x0a),
      PIC_DATA_ICON_INDEX(Kakuna, 2),
      .enemyMonElevation = 0,
    }, //Kakuna,
[SPECIES_BEEDRILL] = 
    {  
      FRONT_COORD(0x86, 5),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Beedrill, 2),
      .enemyMonElevation = 9,
    }, //Beedrill,
[SPECIES_PIDGEY] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Pidgey, 0),
      .enemyMonElevation = 0,
    }, //Pidgey,
[SPECIES_PIDGEOTTO] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Pidgeotto, 0),
      .enemyMonElevation = 0,
    }, //Pidgeotto,
[SPECIES_PIDGEOT] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Pidgeot, 0),
      .enemyMonElevation = 6,
    }, //Pidgeot,
[SPECIES_RATTATA] = 
    {  
      FRONT_COORD(0x44, 13),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Rattata, 2),
      .enemyMonElevation = 0,
    }, //Rattata,
[SPECIES_RATICATE] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Raticate, 1),
      .enemyMonElevation = 0,
    }, //Raticate,
[SPECIES_SPEAROW] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Spearow, 0),
      .enemyMonElevation = 0,
    }, //Spearow,
[SPECIES_FEAROW] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Fearow, 0),
      .enemyMonElevation = 6,
    }, //Fearow,
[SPECIES_EKANS] = 
    {  
      FRONT_COORD(0x65, 10),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Ekans, 2),
      .enemyMonElevation = 0,
    }, //Ekans,
[SPECIES_ARBOK] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Arbok, 2),
      .enemyMonElevation = 0,
    }, //Arbok,
[SPECIES_PIKACHU] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Pikachu, 2),
      .enemyMonElevation = 0,
    }, //Pikachu,
[SPECIES_RAICHU] = 
    {  
      FRONT_COORD(0x67, 3),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Raichu, 0),
      .enemyMonElevation = 0,
    }, //Raichu,
[SPECIES_SANDSHREW] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Sandshrew, 2),
      .enemyMonElevation = 0,
    }, //Sandshrew,
[SPECIES_SANDSLASH] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Sandslash, 2),
      .enemyMonElevation = 0,
    }, //Sandslash,
[SPECIES_NIDORAN_F] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x55, 0x0c),
      PIC_DATA_ICON_INDEX(NidoranF, 2),
      .enemyMonElevation = 0,
    }, //NidoranF,
[SPECIES_NIDORINA] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Nidorina, 2),
      .enemyMonElevation = 0,
    }, //Nidorina,
[SPECIES_NIDOQUEEN] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Nidoqueen, 2),
      .enemyMonElevation = 0,
    }, //Nidoqueen,
[SPECIES_NIDORAN_M] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x56, 0x08),
      PIC_DATA_ICON_INDEX(NidoranM, 2),
      .enemyMonElevation = 0,
    }, //NidoranM,
[SPECIES_NIDORINO] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Nidorino, 2),
      .enemyMonElevation = 0,
    }, //Nidorino,
[SPECIES_NIDOKING] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Nidoking, 2),
      .enemyMonElevation = 0,
    }, //Nidoking,
[SPECIES_CLEFAIRY] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Clefairy, 0),
      .enemyMonElevation = 0,
    }, //Clefairy,
[SPECIES_CLEFABLE] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Clefable, 0),
      .enemyMonElevation = 0,
    }, //Clefable,
[SPECIES_VULPIX] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Vulpix, 2),
      .enemyMonElevation = 0,
    }, //Vulpix,
[SPECIES_NINETALES] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Ninetales, 1),
      .enemyMonElevation = 0,
    }, //Ninetales,
[SPECIES_JIGGLYPUFF] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Jigglypuff, 0),
      .enemyMonElevation = 0,
    }, //Jigglypuff,
[SPECIES_WIGGLYTUFF] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Wigglytuff, 0),
      .enemyMonElevation = 0,
    }, //Wigglytuff,
[SPECIES_ZUBAT] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Zubat, 2),
      .enemyMonElevation = 8,
    }, //Zubat,
[SPECIES_GOLBAT] = 
    {  
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Golbat, 2),
      .enemyMonElevation = 10,
    }, //Golbat,
[SPECIES_ODDISH] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Oddish, 1),
      .enemyMonElevation = 0,
    }, //Oddish,
[SPECIES_GLOOM] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Gloom, 0),
      .enemyMonElevation = 0,
    }, //Gloom,
[SPECIES_VILEPLUME] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Vileplume, 0),
      .enemyMonElevation = 0,
    }, //Vileplume,
[SPECIES_PARAS] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x63, 0x14),
      PIC_DATA_ICON_INDEX(Paras, 0),
      .enemyMonElevation = 0,
    }, //Paras,
[SPECIES_PARASECT] = 
    {  
      FRONT_COORD(0x86, 7),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Parasect, 0),
      .enemyMonElevation = 0,
    }, //Parasect,
[SPECIES_VENONAT] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Venonat, 0),
      .enemyMonElevation = 0,
    }, //Venonat,
[SPECIES_VENOMOTH] = 
    {  
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Venomoth, 2),
      .enemyMonElevation = 11,
    }, //Venomoth,
[SPECIES_DIGLETT] = 
    {  
      FRONT_COORD(0x54, 17),
      BACK_COORD(0x54, 0x10),
      PIC_DATA_ICON_INDEX(Diglett, 2),
      .enemyMonElevation = 0,
    }, //Diglett,
[SPECIES_DUGTRIO] = 
    {  
      FRONT_COORD(0x75, 11),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Dugtrio, 2),
      .enemyMonElevation = 0,
    }, //Dugtrio,
[SPECIES_MEOWTH] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Meowth, 1),
      .enemyMonElevation = 0,
    }, //Meowth,
[SPECIES_PERSIAN] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Persian, 1),
      .enemyMonElevation = 0,
    }, //Persian,
[SPECIES_PSYDUCK] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x67, 0x07),
      PIC_DATA_ICON_INDEX(Psyduck, 1),
      .enemyMonElevation = 0,
    }, //Psyduck,
[SPECIES_GOLDUCK] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Golduck, 2),
      .enemyMonElevation = 0,
    }, //Golduck,
[SPECIES_MANKEY] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Mankey, 1),
      .enemyMonElevation = 0,
    }, //Mankey,
[SPECIES_PRIMEAPE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Primeape, 2),
      .enemyMonElevation = 0,
    }, //Primeape,
[SPECIES_GROWLITHE] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Growlithe, 0),
      .enemyMonElevation = 0,
    }, //Growlithe,
[SPECIES_ARCANINE] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Arcanine, 0),
      .enemyMonElevation = 0,
    }, //Arcanine,
[SPECIES_POLIWAG] = 
    {  
      FRONT_COORD(0x74, 13),
      BACK_COORD(0x74, 0x10),
      PIC_DATA_ICON_INDEX(Poliwag, 0),
      .enemyMonElevation = 0,
    }, //Poliwag,
[SPECIES_POLIWHIRL] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Poliwhirl, 0),
      .enemyMonElevation = 0,
    }, //Poliwhirl,
[SPECIES_POLIWRATH] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Poliwrath, 0),
      .enemyMonElevation = 0,
    }, //Poliwrath,
[SPECIES_ABRA] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x55, 0x0c),
      PIC_DATA_ICON_INDEX(Abra, 2),
      .enemyMonElevation = 0,
    }, //Abra,
[SPECIES_KADABRA] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Kadabra, 2),
      .enemyMonElevation = 0,
    }, //Kadabra,
[SPECIES_ALAKAZAM] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Alakazam, 2),
      .enemyMonElevation = 0,
    }, //Alakazam,
[SPECIES_MACHOP] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Machop, 0),
      .enemyMonElevation = 0,
    }, //Machop,
[SPECIES_MACHOKE] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Machoke, 2),
      .enemyMonElevation = 0,
    }, //Machoke,
[SPECIES_MACHAMP] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x67, 0x04),
      PIC_DATA_ICON_INDEX(Machamp, 0),
      .enemyMonElevation = 0,
    }, //Machamp,
[SPECIES_BELLSPROUT] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Bellsprout, 1),
      .enemyMonElevation = 0,
    }, //Bellsprout,
[SPECIES_WEEPINBELL] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Weepinbell, 1),
      .enemyMonElevation = 0,
    }, //Weepinbell,
[SPECIES_VICTREEBEL] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Victreebel, 1),
      .enemyMonElevation = 0,
    }, //Victreebel,
[SPECIES_TENTACOOL] = 
    {  
      FRONT_COORD(0x46, 7),
      BACK_COORD(0x56, 0x0a),
      PIC_DATA_ICON_INDEX(Tentacool, 2),
      .enemyMonElevation = 0,
    }, //Tentacool,
[SPECIES_TENTACRUEL] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Tentacruel, 2),
      .enemyMonElevation = 0,
    }, //Tentacruel,
[SPECIES_GEODUDE] = 
    {  
      FRONT_COORD(0x54, 10),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Geodude, 1),
      .enemyMonElevation = 16,
    }, //Geodude,
[SPECIES_GRAVELER] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x75, 0x0c),
      PIC_DATA_ICON_INDEX(Graveler, 1),
      .enemyMonElevation = 0,
    }, //Graveler,
[SPECIES_GOLEM] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Golem, 1),
      .enemyMonElevation = 0,
    }, //Golem,
[SPECIES_PONYTA] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Ponyta, 0),
      .enemyMonElevation = 0,
    }, //Ponyta,
[SPECIES_RAPIDASH] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Rapidash, 0),
      .enemyMonElevation = 0,
    }, //Rapidash,
[SPECIES_SLOWPOKE] = 
    {  
      FRONT_COORD(0x66, 16),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Slowpoke, 0),
      .enemyMonElevation = 0,
    }, //Slowpoke,
[SPECIES_SLOWBRO] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Slowbro, 0),
      .enemyMonElevation = 0,
    }, //Slowbro,
[SPECIES_MAGNEMITE] = 
    {  
      FRONT_COORD(0x43, 20),
      BACK_COORD(0x43, 0x14),
      PIC_DATA_ICON_INDEX(Magnemite, 0),
      .enemyMonElevation = 16,
    }, //Magnemite,
[SPECIES_MAGNETON] = 
    {  
      FRONT_COORD(0x76, 7),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Magneton, 0),
      .enemyMonElevation = 11,
    }, //Magneton,
[SPECIES_FARFETCHD] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Farfetchd, 1),
      .enemyMonElevation = 0,
    }, //Farfetchd,
[SPECIES_DODUO] = 
    {  
      FRONT_COORD(0x57, 7),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Doduo, 2),
      .enemyMonElevation = 0,
    }, //Doduo,
[SPECIES_DODRIO] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Dodrio, 2),
      .enemyMonElevation = 0,
    }, //Dodrio,
[SPECIES_SEEL] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Seel, 2),
      .enemyMonElevation = 0,
    }, //Seel,
[SPECIES_DEWGONG] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Dewgong, 2),
      .enemyMonElevation = 0,
    }, //Dewgong,
[SPECIES_GRIMER] = 
    {  
      FRONT_COORD(0x65, 9),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Grimer, 2),
      .enemyMonElevation = 0,
    }, //Grimer,
[SPECIES_MUK] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Muk, 2),
      .enemyMonElevation = 0,
    }, //Muk,
[SPECIES_SHELLDER] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Shellder, 2),
      .enemyMonElevation = 0,
    }, //Shellder,
[SPECIES_CLOYSTER] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Cloyster, 2),
      .enemyMonElevation = 0,
    }, //Cloyster,
[SPECIES_GASTLY] = 
    {  
      FRONT_COORD(0x77, 13),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Gastly, 2),
      .enemyMonElevation = 5,
    }, //Gastly,
[SPECIES_HAUNTER] = 
    {  
      FRONT_COORD(0x77, 13),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Haunter, 2),
      .enemyMonElevation = 4,
    }, //Haunter,
[SPECIES_GENGAR] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Gengar, 2),
      .enemyMonElevation = 1,
    }, //Gengar,
[SPECIES_ONIX] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Onix, 2),
      .enemyMonElevation = 0,
    }, //Onix,
[SPECIES_DROWZEE] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Drowzee, 2),
      .enemyMonElevation = 0,
    }, //Drowzee,
[SPECIES_HYPNO] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Hypno, 1),
      .enemyMonElevation = 0,
    }, //Hypno,
[SPECIES_KRABBY] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Krabby, 2),
      .enemyMonElevation = 0,
    }, //Krabby,
[SPECIES_KINGLER] = 
    {  
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Kingler, 2),
      .enemyMonElevation = 0,
    }, //Kingler,
[SPECIES_VOLTORB] = 
    {  
      FRONT_COORD(0x44, 10),
      BACK_COORD(0x55, 0x0e),
      PIC_DATA_ICON_INDEX(Voltorb, 0),
      .enemyMonElevation = 10,
    }, //Voltorb,
[SPECIES_ELECTRODE] = 
    {  
      FRONT_COORD(0x55, 6),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Electrode, 0),
      .enemyMonElevation = 12,
    }, //Electrode,
[SPECIES_EXEGGCUTE] = 
    {  
      FRONT_COORD(0x87, 12),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Exeggcute, 0),
      .enemyMonElevation = 0,
    }, //Exeggcute,
[SPECIES_EXEGGUTOR] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Exeggutor, 1),
      .enemyMonElevation = 0,
    }, //Exeggutor,
[SPECIES_CUBONE] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Cubone, 1),
      .enemyMonElevation = 0,
    }, //Cubone,
[SPECIES_MAROWAK] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Marowak, 1),
      .enemyMonElevation = 0,
    }, //Marowak,
[SPECIES_HITMONLEE] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Hitmonlee, 2),
      .enemyMonElevation = 0,
    }, //Hitmonlee,
[SPECIES_HITMONCHAN] = 
    {  
      FRONT_COORD(0x67, 3),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Hitmonchan, 2),
      .enemyMonElevation = 0,
    }, //Hitmonchan,
[SPECIES_LICKITUNG] = 
    {  
      FRONT_COORD(0x86, 7),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Lickitung, 1),
      .enemyMonElevation = 0,
    }, //Lickitung,
[SPECIES_KOFFING] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Koffing, 2),
      .enemyMonElevation = 8,
    }, //Koffing,
[SPECIES_WEEZING] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Weezing, 2),
      .enemyMonElevation = 6,
    }, //Weezing,
[SPECIES_RHYHORN] = 
    {  
      FRONT_COORD(0x76, 12),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Rhyhorn, 1),
      .enemyMonElevation = 0,
    }, //Rhyhorn,
[SPECIES_RHYDON] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Rhydon, 1),
      .enemyMonElevation = 0,
    }, //Rhydon,
[SPECIES_CHANSEY] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Chansey, 0),
      .enemyMonElevation = 0,
    }, //Chansey,
[SPECIES_TANGELA] = 
    {  
      FRONT_COORD(0x67, 12),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Tangela, 0),
      .enemyMonElevation = 0,
    }, //Tangela,
[SPECIES_KANGASKHAN] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Kangaskhan, 1),
      .enemyMonElevation = 0,
    }, //Kangaskhan,
[SPECIES_HORSEA] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Horsea, 0),
      .enemyMonElevation = 0,
    }, //Horsea,
[SPECIES_SEADRA] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Seadra, 0),
      .enemyMonElevation = 0,
    }, //Seadra,
[SPECIES_GOLDEEN] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Goldeen, 0),
      .enemyMonElevation = 0,
    }, //Goldeen,
[SPECIES_SEAKING] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Seaking, 0),
      .enemyMonElevation = 0,
    }, //Seaking,
[SPECIES_STARYU] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Staryu, 2),
      .enemyMonElevation = 0,
    }, //Staryu,
[SPECIES_STARMIE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Starmie, 2),
      .enemyMonElevation = 0,
    }, //Starmie,
[SPECIES_MR_MIME] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(MrMime, 0),
      .enemyMonElevation = 0,
    }, //MrMime,
[SPECIES_SCYTHER] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Scyther, 1),
      .enemyMonElevation = 0,
    }, //Scyther,
[SPECIES_JYNX] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Jynx, 2),
      .enemyMonElevation = 0,
    }, //Jynx,
[SPECIES_ELECTABUZZ] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Electabuzz, 1),
      .enemyMonElevation = 0,
    }, //Electabuzz,
[SPECIES_MAGMAR] = 
    {  
      FRONT_COORD(0x77, 4),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Magmar, 0),
      .enemyMonElevation = 0,
    }, //Magmar,
[SPECIES_PINSIR] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Pinsir, 2),
      .enemyMonElevation = 0,
    }, //Pinsir,
[SPECIES_TAUROS] = 
    {  
      FRONT_COORD(0x78, 5),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Tauros, 2),
      .enemyMonElevation = 0,
    }, //Tauros,
[SPECIES_MAGIKARP] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Magikarp, 0),
      .enemyMonElevation = 0,
    }, //Magikarp,
[SPECIES_GYARADOS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Gyarados, 0),
      .enemyMonElevation = 0,
    }, //Gyarados,
[SPECIES_LAPRAS] = 
    {  
      FRONT_COORD(0x85, 2),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Lapras, 2),
      .enemyMonElevation = 0,
    }, //Lapras,
[SPECIES_DITTO] = 
    {  
      FRONT_COORD(0x54, 15),
      BACK_COORD(0x54, 0x11),
      PIC_DATA_ICON_INDEX(Ditto, 2),
      .enemyMonElevation = 0,
    }, //Ditto,
[SPECIES_EEVEE] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Eevee, 2),
      .enemyMonElevation = 0,
    }, //Eevee,
[SPECIES_VAPOREON] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Vaporeon, 0),
      .enemyMonElevation = 0,
    }, //Vaporeon,
[SPECIES_JOLTEON] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Jolteon, 0),
      .enemyMonElevation = 0,
    }, //Jolteon,
[SPECIES_FLAREON] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Flareon, 0),
      .enemyMonElevation = 0,
    }, //Flareon,
[SPECIES_PORYGON] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Porygon, 0),
      .enemyMonElevation = 0,
    }, //Porygon,
[SPECIES_OMANYTE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Omanyte, 0),
      .enemyMonElevation = 0,
    }, //Omanyte,
[SPECIES_OMASTAR] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Omastar, 0),
      .enemyMonElevation = 0,
    }, //Omastar,
[SPECIES_KABUTO] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Kabuto, 2),
      .enemyMonElevation = 0,
    }, //Kabuto,
[SPECIES_KABUTOPS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Kabutops, 2),
      .enemyMonElevation = 0,
    }, //Kabutops,
[SPECIES_AERODACTYL] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Aerodactyl, 0),
      .enemyMonElevation = 7,
    }, //Aerodactyl,
[SPECIES_SNORLAX] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Snorlax, 1),
      .enemyMonElevation = 0,
    }, //Snorlax,
[SPECIES_ARTICUNO] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Articuno, 0),
      .enemyMonElevation = 6,
    }, //Articuno,
[SPECIES_ZAPDOS] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Zapdos, 0),
      .enemyMonElevation = 8,
    }, //Zapdos,
[SPECIES_MOLTRES] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Moltres, 0),
      .enemyMonElevation = 5,
    }, //Moltres,
[SPECIES_DRATINI] = 
    {  
      FRONT_COORD(0x75, 9),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Dratini, 0),
      .enemyMonElevation = 0,
    }, //Dratini,
[SPECIES_DRAGONAIR] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Dragonair, 0),
      .enemyMonElevation = 0,
    }, //Dragonair,
[SPECIES_DRAGONITE] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Dragonite, 2),
      .enemyMonElevation = 2,
    }, //Dragonite,
[SPECIES_MEWTWO] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x01),
      PIC_DATA_ICON_INDEX(Mewtwo, 2),
      .enemyMonElevation = 0,
    }, //Mewtwo,
[SPECIES_MEW] = 
    {  
      FRONT_COORD(0x55, 9),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Mew, 0),
      .enemyMonElevation = 10,
    }, //Mew,
[SPECIES_CHIKORITA] = 
    {  
      FRONT_COORD(0x75, 10),
      BACK_COORD(0x56, 0x0a),
      PIC_DATA_ICON_INDEX(Chikorita, 1),
      .enemyMonElevation = 0,
    }, //Chikorita,
[SPECIES_BAYLEEF] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Bayleef, 1),
      .enemyMonElevation = 0,
    }, //Bayleef,
[SPECIES_MEGANIUM] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Meganium, 1),
      .enemyMonElevation = 0,
    }, //Meganium,
[SPECIES_CYNDAQUIL] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Cyndaquil, 1),
      .enemyMonElevation = 0,
    }, //Cyndaquil,
[SPECIES_QUILAVA] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Quilava, 1),
      .enemyMonElevation = 0,
    }, //Quilava,
[SPECIES_TYPHLOSION] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Typhlosion, 1),
      .enemyMonElevation = 0,
    }, //Typhlosion,
[SPECIES_TOTODILE] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Totodile, 2),
      .enemyMonElevation = 0,
    }, //Totodile,
[SPECIES_CROCONAW] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x67, 0x07),
      PIC_DATA_ICON_INDEX(Croconaw, 2),
      .enemyMonElevation = 0,
    }, //Croconaw,
[SPECIES_FERALIGATOR] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Feraligator, 2),
      .enemyMonElevation = 0,
    }, //Feraligatr,
[SPECIES_SENTRET] = 
    {  
      FRONT_COORD(0x47, 2),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Sentret, 2),
      .enemyMonElevation = 0,
    }, //Sentret,
[SPECIES_FURRET] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Furret, 2),
      .enemyMonElevation = 0,
    }, //Furret,
[SPECIES_HOOTHOOT] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Hoothoot, 2),
      .enemyMonElevation = 0,
    }, //Hoothoot,
[SPECIES_NOCTOWL] = 
    {  
      FRONT_COORD(0x58, 2),
      BACK_COORD(0x68, 0x03),
      PIC_DATA_ICON_INDEX(Noctowl, 2),
      .enemyMonElevation = 0,
    }, //Noctowl,
[SPECIES_LEDYBA] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Ledyba, 0),
      .enemyMonElevation = 8,
    }, //Ledyba,
[SPECIES_LEDIAN] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Ledian, 0),
      .enemyMonElevation = 8,
    }, //Ledian,
[SPECIES_SPINARAK] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x73, 0x15),
      PIC_DATA_ICON_INDEX(Spinarak, 1),
      .enemyMonElevation = 0,
    }, //Spinarak,
[SPECIES_ARIADOS] = 
    {  
      FRONT_COORD(0x87, 6),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Ariados, 0),
      .enemyMonElevation = 0,
    }, //Ariados,
[SPECIES_CROBAT] = 
    {  
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Crobat, 2),
      .enemyMonElevation = 6,
    }, //Crobat,
[SPECIES_CHINCHOU] = 
    {  
      FRONT_COORD(0x75, 12),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Chinchou, 2),
      .enemyMonElevation = 0,
    }, //Chinchou,
[SPECIES_LANTURN] = 
    {  
      FRONT_COORD(0x87, 11),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Lanturn, 0),
      .enemyMonElevation = 0,
    }, //Lanturn,
[SPECIES_PICHU] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Pichu, 0),
      .enemyMonElevation = 0,
    }, //Pichu,
[SPECIES_CLEFFA] = 
    {  
      FRONT_COORD(0x44, 18),
      BACK_COORD(0x65, 0x0f),
      PIC_DATA_ICON_INDEX(Cleffa, 0),
      .enemyMonElevation = 0,
    }, //Cleffa,
[SPECIES_IGGLYBUFF] = 
    {  
      FRONT_COORD(0x44, 17),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Igglybuff, 1),
      .enemyMonElevation = 0,
    }, //Igglybuff,
[SPECIES_TOGEPI] = 
    {  
      FRONT_COORD(0x34, 16),
      BACK_COORD(0x54, 0x10),
      PIC_DATA_ICON_INDEX(Togepi, 2),
      .enemyMonElevation = 0,
    }, //Togepi,
[SPECIES_TOGETIC] = 
    {  
      FRONT_COORD(0x46, 8),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Togetic, 2),
      .enemyMonElevation = 0,
    }, //Togetic,
[SPECIES_NATU] = 
    {  
      FRONT_COORD(0x44, 17),
      BACK_COORD(0x54, 0x11),
      PIC_DATA_ICON_INDEX(Natu, 0),
      .enemyMonElevation = 0,
    }, //Natu,
[SPECIES_XATU] = 
    {  
      FRONT_COORD(0x47, 5),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Xatu, 0),
      .enemyMonElevation = 0,
    }, //Xatu,
[SPECIES_MAREEP] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Mareep, 2),
      .enemyMonElevation = 0,
    }, //Mareep,
[SPECIES_FLAAFFY] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Flaaffy, 0),
      .enemyMonElevation = 0,
    }, //Flaaffy,
[SPECIES_AMPHAROS] = 
    {  
      FRONT_COORD(0x77, 2),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Ampharos, 0),
      .enemyMonElevation = 0,
    }, //Ampharos,
[SPECIES_BELLOSSOM] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Bellossom, 1),
      .enemyMonElevation = 0,
    }, //Bellossom,
[SPECIES_MARILL] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x75, 0x0c),
      PIC_DATA_ICON_INDEX(Marill, 2),
      .enemyMonElevation = 0,
    }, //Marill,
[SPECIES_AZUMARILL] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Azumarill, 2),
      .enemyMonElevation = 0,
    }, //Azumarill,
[SPECIES_SUDOWOODO] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Sudowoodo, 1),
      .enemyMonElevation = 0,
    }, //Sudowoodo,
[SPECIES_POLITOED] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Politoed, 1),
      .enemyMonElevation = 0,
    }, //Politoed,
[SPECIES_HOPPIP] = 
    {  
      FRONT_COORD(0x66, 14),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Hoppip, 1),
      .enemyMonElevation = 11,
    }, //Hoppip,
[SPECIES_SKIPLOOM] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Skiploom, 1),
      .enemyMonElevation = 12,
    }, //Skiploom,
[SPECIES_JUMPLUFF] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Jumpluff, 2),
      .enemyMonElevation = 9,
    }, //Jumpluff,
[SPECIES_AIPOM] = 
    {  
      FRONT_COORD(0x58, 1),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Aipom, 2),
      .enemyMonElevation = 0,
    }, //Aipom,
[SPECIES_SUNKERN] = 
    {  
      FRONT_COORD(0x44, 17),
      BACK_COORD(0x56, 0x0a),
      PIC_DATA_ICON_INDEX(Sunkern, 1),
      .enemyMonElevation = 0,
    }, //Sunkern,
[SPECIES_SUNFLORA] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Sunflora, 1),
      .enemyMonElevation = 0,
    }, //Sunflora,
[SPECIES_YANMA] = 
    {  
      FRONT_COORD(0x86, 14),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Yanma, 1),
      .enemyMonElevation = 12,
    }, //Yanma,
[SPECIES_WOOPER] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Wooper, 0),
      .enemyMonElevation = 0,
    }, //Wooper,
[SPECIES_QUAGSIRE] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Quagsire, 0),
      .enemyMonElevation = 0,
    }, //Quagsire,
[SPECIES_ESPEON] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Espeon, 2),
      .enemyMonElevation = 0,
    }, //Espeon,
[SPECIES_UMBREON] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Umbreon, 2),
      .enemyMonElevation = 0,
    }, //Umbreon,
[SPECIES_MURKROW] = 
    {  
      FRONT_COORD(0x66, 15),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Murkrow, 2),
      .enemyMonElevation = 0,
    }, //Murkrow,
[SPECIES_SLOWKING] = 
    {  
      FRONT_COORD(0x58, 1),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Slowking, 0),
      .enemyMonElevation = 0,
    }, //Slowking,
[SPECIES_MISDREAVUS] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Misdreavus, 0),
      .enemyMonElevation = 8,
    }, //Misdreavus,
[SPECIES_UNOWN] = 
    {  
      FRONT_COORD(0x35, 15),
      BACK_COORD(0x36, 0x08),
      PIC_DATA_ICON_INDEX(Unown, 0),
      .enemyMonElevation = 14,
    }, //Unown,
[SPECIES_WOBBUFFET] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x75, 0x0c),
      PIC_DATA_ICON_INDEX(Wobbuffet, 0),
      .enemyMonElevation = 0,
    }, //Wobbuffet,
[SPECIES_GIRAFARIG] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Girafarig, 1),
      .enemyMonElevation = 0,
    }, //Girafarig,
[SPECIES_PINECO] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x65, 0x0f),
      PIC_DATA_ICON_INDEX(Pineco, 0),
      .enemyMonElevation = 0,
    }, //Pineco,
[SPECIES_FORRETRESS] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Forretress, 2),
      .enemyMonElevation = 0,
    }, //Forretress,
[SPECIES_DUNSPARCE] = 
    {  
      FRONT_COORD(0x74, 9),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Dunsparce, 2),
      .enemyMonElevation = 0,
    }, //Dunsparce,
[SPECIES_GLIGAR] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Gligar, 2),
      .enemyMonElevation = 6,
    }, //Gligar,
[SPECIES_STEELIX] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Steelix, 0),
      .enemyMonElevation = 0,
    }, //Steelix,
[SPECIES_SNUBBULL] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Snubbull, 0),
      .enemyMonElevation = 0,
    }, //Snubbull,
[SPECIES_GRANBULL] = 
    {  
      FRONT_COORD(0x57, 4),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Granbull, 2),
      .enemyMonElevation = 0,
    }, //Granbull,
[SPECIES_QWILFISH] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Qwilfish, 0),
      .enemyMonElevation = 0,
    }, //Qwilfish,
[SPECIES_SCIZOR] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Scizor, 0),
      .enemyMonElevation = 4,
    }, //Scizor,
[SPECIES_SHUCKLE] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x56, 0x0b),
      PIC_DATA_ICON_INDEX(Shuckle, 1),
      .enemyMonElevation = 0,
    }, //Shuckle,
[SPECIES_HERACROSS] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Heracross, 2),
      .enemyMonElevation = 0,
    }, //Heracross,
[SPECIES_SNEASEL] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Sneasel, 0),
      .enemyMonElevation = 0,
    }, //Sneasel,
[SPECIES_TEDDIURSA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Teddiursa, 0),
      .enemyMonElevation = 0,
    }, //Teddiursa,
[SPECIES_URSARING] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Ursaring, 2),
      .enemyMonElevation = 0,
    }, //Ursaring,
[SPECIES_SLUGMA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Slugma, 0),
      .enemyMonElevation = 0,
    }, //Slugma,
[SPECIES_MAGCARGO] = 
    {  
      FRONT_COORD(0x57, 6),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Magcargo, 0),
      .enemyMonElevation = 0,
    }, //Magcargo,
[SPECIES_SWINUB] = 
    {  
      FRONT_COORD(0x43, 18),
      BACK_COORD(0x63, 0x15),
      PIC_DATA_ICON_INDEX(Swinub, 2),
      .enemyMonElevation = 0,
    }, //Swinub,
[SPECIES_PILOSWINE] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Piloswine, 2),
      .enemyMonElevation = 0,
    }, //Piloswine,
[SPECIES_CORSOLA] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Corsola, 0),
      .enemyMonElevation = 0,
    }, //Corsola,
[SPECIES_REMORAID] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Remoraid, 0),
      .enemyMonElevation = 0,
    }, //Remoraid,
[SPECIES_OCTILLERY] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Octillery, 0),
      .enemyMonElevation = 0,
    }, //Octillery,
[SPECIES_DELIBIRD] = 
    {  
      FRONT_COORD(0x56, 7),
      BACK_COORD(0x67, 0x06),
      PIC_DATA_ICON_INDEX(Delibird, 0),
      .enemyMonElevation = 0,
    }, //Delibird,
[SPECIES_MANTINE] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Mantine, 2),
      .enemyMonElevation = 0,
    }, //Mantine,
[SPECIES_SKARMORY] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Skarmory, 0),
      .enemyMonElevation = 0,
    }, //Skarmory,
[SPECIES_HOUNDOUR] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x55, 0x0c),
      PIC_DATA_ICON_INDEX(Houndour, 0),
      .enemyMonElevation = 0,
    }, //Houndour,
[SPECIES_HOUNDOOM] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Houndoom, 0),
      .enemyMonElevation = 0,
    }, //Houndoom,
[SPECIES_KINGDRA] = 
    {  
      FRONT_COORD(0x78, 1),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Kingdra, 0),
      .enemyMonElevation = 0,
    }, //Kingdra,
[SPECIES_PHANPY] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x65, 0x0e),
      PIC_DATA_ICON_INDEX(Phanpy, 0),
      .enemyMonElevation = 0,
    }, //Phanpy,
[SPECIES_DONPHAN] = 
    {  
      FRONT_COORD(0x86, 9),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Donphan, 0),
      .enemyMonElevation = 0,
    }, //Donphan,
[SPECIES_PORYGON2] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Porygon2, 0),
      .enemyMonElevation = 4,
    }, //Porygon2,
[SPECIES_STANTLER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x03),
      PIC_DATA_ICON_INDEX(Stantler, 2),
      .enemyMonElevation = 0,
    }, //Stantler,
[SPECIES_SMEARGLE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Smeargle, 1),
      .enemyMonElevation = 0,
    }, //Smeargle,
[SPECIES_TYROGUE] = 
    {  
      FRONT_COORD(0x46, 9),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Tyrogue, 2),
      .enemyMonElevation = 0,
    }, //Tyrogue,
[SPECIES_HITMONTOP] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Hitmontop, 2),
      .enemyMonElevation = 0,
    }, //Hitmontop,
[SPECIES_SMOOCHUM] = 
    {  
      FRONT_COORD(0x35, 13),
      BACK_COORD(0x56, 0x09),
      PIC_DATA_ICON_INDEX(Smoochum, 1),
      .enemyMonElevation = 0,
    }, //Smoochum,
[SPECIES_ELEKID] = 
    {  
      FRONT_COORD(0x76, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Elekid, 1),
      .enemyMonElevation = 0,
    }, //Elekid,
[SPECIES_MAGBY] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Magby, 1),
      .enemyMonElevation = 0,
    }, //Magby,
[SPECIES_MILTANK] = 
    {  
      FRONT_COORD(0x77, 8),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Miltank, 1),
      .enemyMonElevation = 0,
    }, //Miltank,
[SPECIES_BLISSEY] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Blissey, 1),
      .enemyMonElevation = 0,
    }, //Blissey,
[SPECIES_RAIKOU] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Raikou, 0),
      .enemyMonElevation = 0,
    }, //Raikou,
[SPECIES_ENTEI] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Entei, 2),
      .enemyMonElevation = 0,
    }, //Entei,
[SPECIES_SUICUNE] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Suicune, 0),
      .enemyMonElevation = 0,
    }, //Suicune,
[SPECIES_LARVITAR] = 
    {  
      FRONT_COORD(0x46, 10),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Larvitar, 1),
      .enemyMonElevation = 0,
    }, //Larvitar,
[SPECIES_PUPITAR] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Pupitar, 0),
      .enemyMonElevation = 0,
    }, //Pupitar,
[SPECIES_TYRANITAR] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Tyranitar, 1),
      .enemyMonElevation = 0,
    }, //Tyranitar,
[SPECIES_LUGIA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Lugia, 0),
      .enemyMonElevation = 8,
    }, //Lugia,
[SPECIES_HO_OH] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(HoOh, 1),
      .enemyMonElevation = 8,
    }, //HoOh,
[SPECIES_CELEBI] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Celebi, 1),
      .enemyMonElevation = 15,
    }, //Celebi,
    
[SPECIES_TREECKO] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Treecko, 1),
      .enemyMonElevation = 0,
    }, //Treecko,
[SPECIES_GROVYLE] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Grovyle, 0),
      .enemyMonElevation = 0,
    }, //Grovyle,
[SPECIES_SCEPTILE] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Sceptile, 1),
      .enemyMonElevation = 0,
    }, //Sceptile,
[SPECIES_TORCHIC] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Torchic, 0),
      .enemyMonElevation = 0,
    }, //Torchic,
[SPECIES_COMBUSKEN] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Combusken, 0),
      .enemyMonElevation = 0,
    }, //Combusken,
[SPECIES_BLAZIKEN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Blaziken, 0),
      .enemyMonElevation = 0,
    }, //Blaziken,
[SPECIES_MUDKIP] = 
    {  
      FRONT_COORD(0x56, 13),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Mudkip, 0),
      .enemyMonElevation = 0,
    }, //Mudkip,
[SPECIES_MARSHTOMP] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Marshtomp, 0),
      .enemyMonElevation = 0,
    }, //Marshtomp,
[SPECIES_SWAMPERT] = 
    {  
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Swampert, 0),
      .enemyMonElevation = 0,
    }, //Swampert,
[SPECIES_POOCHYENA] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Poochyena, 2),
      .enemyMonElevation = 0,
    }, //Poochyena,
[SPECIES_MIGHTYENA] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Mightyena, 2),
      .enemyMonElevation = 0,
    }, //Mightyena,
[SPECIES_ZIGZAGOON] = 
    {  
      FRONT_COORD(0x85, 12),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Zigzagoon, 2),
      .enemyMonElevation = 0,
    }, //Zigzagoon,
[SPECIES_LINOONE] = 
    {  
      FRONT_COORD(0x78, 13),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Linoone, 2),
      .enemyMonElevation = 0,
    }, //Linoone,
[SPECIES_WURMPLE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Wurmple, 0),
      .enemyMonElevation = 0,
    }, //Wurmple,
[SPECIES_SILCOON] = 
    {  
      FRONT_COORD(0x75, 10),
      BACK_COORD(0x83, 0x15),
      PIC_DATA_ICON_INDEX(Silcoon, 2),
      .enemyMonElevation = 0,
    }, //Silcoon,
[SPECIES_BEAUTIFLY] = 
    {  
      FRONT_COORD(0x86, 9),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Beautifly, 0),
      .enemyMonElevation = 8,
    }, //Beautifly,
[SPECIES_CASCOON] = 
    {  
      FRONT_COORD(0x74, 10),
      BACK_COORD(0x73, 0x14),
      PIC_DATA_ICON_INDEX(Cascoon, 2),
      .enemyMonElevation = 0,
    }, //Cascoon,
[SPECIES_DUSTOX] = 
    {  
      FRONT_COORD(0x86, 12),
      BACK_COORD(0x83, 0x14),
      PIC_DATA_ICON_INDEX(Dustox, 1),
      .enemyMonElevation = 10,
    }, //Dustox,
[SPECIES_LOTAD] = 
    {  
      FRONT_COORD(0x65, 13),
      BACK_COORD(0x75, 0x0f),
      PIC_DATA_ICON_INDEX(Lotad, 1),
      .enemyMonElevation = 0,
    }, //Lotad,
[SPECIES_LOMBRE] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Lombre, 1),
      .enemyMonElevation = 0,
    }, //Lombre,
[SPECIES_LUDICOLO] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Ludicolo, 1),
      .enemyMonElevation = 0,
    }, //Ludicolo,
[SPECIES_SEEDOT] = 
    {  
      FRONT_COORD(0x46, 12),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Seedot, 1),
      .enemyMonElevation = 0,
    }, //Seedot,
[SPECIES_NUZLEAF] = 
    {  
      FRONT_COORD(0x56, 7),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Nuzleaf, 1),
      .enemyMonElevation = 0,
    }, //Nuzleaf,
[SPECIES_SHIFTRY] = 
    {  
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Shiftry, 0),
      .enemyMonElevation = 0,
    }, //Shiftry,
[SPECIES_NINCADA] = 
    {  
      FRONT_COORD(0x74, 16),
      BACK_COORD(0x83, 0x14),
      PIC_DATA_ICON_INDEX(Nincada, 1),
      .enemyMonElevation = 0,
    }, //Nincada,
[SPECIES_NINJASK] = 
    {  
      FRONT_COORD(0x86, 11),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Ninjask, 1),
      .enemyMonElevation = 10,
    }, //Ninjask,
[SPECIES_SHEDINJA] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Shedinja, 1),
      .enemyMonElevation = 8,
    }, //Shedinja,
[SPECIES_TAILLOW] = 
    {  
      FRONT_COORD(0x64, 11),
      BACK_COORD(0x64, 0x11),
      PIC_DATA_ICON_INDEX(Taillow, 2),
      .enemyMonElevation = 0,
    }, //Taillow,
[SPECIES_SWELLOW] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Swellow, 2),
      .enemyMonElevation = 0,
    }, //Swellow,
[SPECIES_SHROOMISH] = 
    {  
      FRONT_COORD(0x54, 14),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Shroomish, 1),
      .enemyMonElevation = 0,
    }, //Shroomish,
[SPECIES_BRELOOM] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Breloom, 1),
      .enemyMonElevation = 0,
    }, //Breloom,
[SPECIES_SPINDA] = 
    {  
      FRONT_COORD(0x68, 8),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Spinda, 1),
      .enemyMonElevation = 0,
    }, //Spinda,
[SPECIES_WINGULL] = 
    {  
      FRONT_COORD(0x84, 11),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Wingull, 0),
      .enemyMonElevation = 16,
    }, //Wingull,
[SPECIES_PELIPPER] = 
    {  
      FRONT_COORD(0x77, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Pelipper, 0),
      .enemyMonElevation = 8,
    }, //Pelipper,
[SPECIES_SURSKIT] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Surskit, 2),
      .enemyMonElevation = 0,
    }, //Surskit,
[SPECIES_MASQUERAIN] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Masquerain, 0),
      .enemyMonElevation = 10,
    }, //Masquerain,
[SPECIES_WAILMER] = 
    {  
      FRONT_COORD(0x75, 10),
      BACK_COORD(0x83, 0x15),
      PIC_DATA_ICON_INDEX(Wailmer, 2),
      .enemyMonElevation = 0,
    }, //Wailmer,
[SPECIES_WAILORD] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x83, 0x16),
      PIC_DATA_ICON_INDEX(Wailord, 0),
      .enemyMonElevation = 0,
    }, //Wailord,
[SPECIES_SKITTY] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Skitty, 0),
      .enemyMonElevation = 0,
    }, //Skitty,
[SPECIES_DELCATTY] = 
    {  
      FRONT_COORD(0x66, 4),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Delcatty, 2),
      .enemyMonElevation = 0,
    }, //Delcatty,
[SPECIES_KECLEON] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Kecleon, 1),
      .enemyMonElevation = 0,
    }, //Kecleon,
[SPECIES_BALTOY] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Baltoy, 1),
      .enemyMonElevation = 7,
    }, //Baltoy,
[SPECIES_CLAYDOL] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Claydol, 0),
      .enemyMonElevation = 10,
    }, //Claydol,
[SPECIES_NOSEPASS] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Nosepass, 0),
      .enemyMonElevation = 0,
    }, //Nosepass,
[SPECIES_TORKOAL] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Torkoal, 1),
      .enemyMonElevation = 0,
    }, //Torkoal,
[SPECIES_SABLEYE] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Sableye, 2),
      .enemyMonElevation = 0,
    }, //Sableye,
[SPECIES_BARBOACH] = 
    {  
      FRONT_COORD(0x46, 12),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Barboach, 0),
      .enemyMonElevation = 0,
    }, //Barboach,
[SPECIES_WHISCASH] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Whiscash, 0),
      .enemyMonElevation = 0,
    }, //Whiscash,
[SPECIES_LUVDISC] = 
    {  
      FRONT_COORD(0x46, 14),
      BACK_COORD(0x46, 0x0a),
      PIC_DATA_ICON_INDEX(Luvdisc, 0),
      .enemyMonElevation = 0,
    }, //Luvdisc,
[SPECIES_CORPHISH] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Corphish, 0),
      .enemyMonElevation = 0,
    }, //Corphish,
[SPECIES_CRAWDAUNT] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Crawdaunt, 0),
      .enemyMonElevation = 0,
    }, //Crawdaunt,
[SPECIES_FEEBAS] = 
    {  
      FRONT_COORD(0x46, 10),
      BACK_COORD(0x67, 0x07),
      PIC_DATA_ICON_INDEX(Feebas, 2),
      .enemyMonElevation = 0,
    }, //Feebas,
[SPECIES_MILOTIC] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x68, 0x02),
      PIC_DATA_ICON_INDEX(Milotic, 0),
      .enemyMonElevation = 0,
    }, //Milotic,
[SPECIES_CARVANHA] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Carvanha, 0),
      .enemyMonElevation = 0,
    }, //Carvanha,
[SPECIES_SHARPEDO] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 0x02),
      PIC_DATA_ICON_INDEX(Sharpedo, 0),
      .enemyMonElevation = 0,
    }, //Sharpedo,
[SPECIES_TRAPINCH] = 
    {  
      FRONT_COORD(0x54, 12),
      BACK_COORD(0x75, 0x0e),
      PIC_DATA_ICON_INDEX(Trapinch, 1),
      .enemyMonElevation = 0,
    }, //Trapinch,
[SPECIES_VIBRAVA] = 
    {  
      FRONT_COORD(0x86, 10),
      BACK_COORD(0x74, 0x11),
      PIC_DATA_ICON_INDEX(Vibrava, 1),
      .enemyMonElevation = 0,
    }, //Vibrava,
[SPECIES_FLYGON] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0x02),
      PIC_DATA_ICON_INDEX(Flygon, 1),
      .enemyMonElevation = 7,
    }, //Flygon,
[SPECIES_MAKUHITA] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Makuhita, 2),
      .enemyMonElevation = 0,
    }, //Makuhita,
[SPECIES_HARIYAMA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Hariyama, 1),
      .enemyMonElevation = 0,
    }, //Hariyama,
[SPECIES_ELECTRIKE] = 
    {  
      FRONT_COORD(0x64, 14),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Electrike, 1),
      .enemyMonElevation = 0,
    }, //Electrike,
[SPECIES_MANECTRIC] = 
    {  
      FRONT_COORD(0x67, 2),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Manectric, 0),
      .enemyMonElevation = 0,
    }, //Manectric,
[SPECIES_NUMEL] = 
    {  
      FRONT_COORD(0x65, 9),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Numel, 1),
      .enemyMonElevation = 0,
    }, //Numel,
[SPECIES_CAMERUPT] = 
    {  
      FRONT_COORD(0x87, 6),
      BACK_COORD(0x84, 0x13),
      PIC_DATA_ICON_INDEX(Camerupt, 0),
      .enemyMonElevation = 0,
    }, //Camerupt,
[SPECIES_SPHEAL] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x64, 0x12),
      PIC_DATA_ICON_INDEX(Spheal, 2),
      .enemyMonElevation = 0,
    }, //Spheal,
[SPECIES_SEALEO] = 
    {  
      FRONT_COORD(0x86, 10),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Sealeo, 2),
      .enemyMonElevation = 0,
    }, //Sealeo,
[SPECIES_WALREIN] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Walrein, 0),
      .enemyMonElevation = 0,
    }, //Walrein,
[SPECIES_CACNEA] = 
    {  
      FRONT_COORD(0x74, 13),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Cacnea, 1),
      .enemyMonElevation = 0,
    }, //Cacnea,
[SPECIES_CACTURNE] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Cacturne, 1),
      .enemyMonElevation = 0,
    }, //Cacturne,
[SPECIES_SNORUNT] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Snorunt, 2),
      .enemyMonElevation = 0,
    }, //Snorunt,
[SPECIES_GLALIE] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Glalie, 0),
      .enemyMonElevation = 12,
    }, //Glalie,
[SPECIES_LUNATONE] = 
    {  
      FRONT_COORD(0x66, 9),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Lunatone, 1),
      .enemyMonElevation = 13,
    }, //Lunatone,
[SPECIES_SOLROCK] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Solrock, 0),
      .enemyMonElevation = 4,
    }, //Solrock,
[SPECIES_AZURILL] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Azurill, 2),
      .enemyMonElevation = 0,
    }, //Azurill,
[SPECIES_SPOINK] = 
    {  
      FRONT_COORD(0x46, 9),
      BACK_COORD(0x56, 0x0b),
      PIC_DATA_ICON_INDEX(Spoink, 0),
      .enemyMonElevation = 0,
    }, //Spoink,
[SPECIES_GRUMPIG] = 
    {  
      FRONT_COORD(0x77, 2),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Grumpig, 2),
      .enemyMonElevation = 0,
    }, //Grumpig,
[SPECIES_PLUSLE] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Plusle, 0),
      .enemyMonElevation = 0,
    }, //Plusle,
[SPECIES_MINUN] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Minun, 0),
      .enemyMonElevation = 0,
    }, //Minun,
[SPECIES_MAWILE] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Mawile, 2),
      .enemyMonElevation = 0,
    }, //Mawile,
[SPECIES_MEDITITE] = 
    {  
      FRONT_COORD(0x65, 10),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Meditite, 0),
      .enemyMonElevation = 0,
    }, //Meditite,
[SPECIES_MEDICHAM] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x68, 0x03),
      PIC_DATA_ICON_INDEX(Medicham, 0),
      .enemyMonElevation = 0,
    }, //Medicham,
[SPECIES_SWABLU] = 
    {  
      FRONT_COORD(0x76, 14),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Swablu, 0),
      .enemyMonElevation = 12,
    }, //Swablu,
[SPECIES_ALTARIA] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Altaria, 0),
      .enemyMonElevation = 8,
    }, //Altaria,
[SPECIES_WYNAUT] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Wynaut, 0),
      .enemyMonElevation = 0,
    }, //Wynaut,
[SPECIES_DUSKULL] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Duskull, 0),
      .enemyMonElevation = 9,
    }, //Duskull,
[SPECIES_DUSCLOPS] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Dusclops, 0),
      .enemyMonElevation = 0,
    }, //Dusclops,
[SPECIES_ROSELIA] = 
    {  
      FRONT_COORD(0x76, 11),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Roselia, 0),
      .enemyMonElevation = 0,
    }, //Roselia,
[SPECIES_SLAKOTH] = 
    {  
      FRONT_COORD(0x74, 15),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Slakoth, 2),
      .enemyMonElevation = 0,
    }, //Slakoth,
[SPECIES_VIGOROTH] = 
    {  
      FRONT_COORD(0x78, 7),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Vigoroth, 2),
      .enemyMonElevation = 0,
    }, //Vigoroth,
[SPECIES_SLAKING] = 
    {  
      FRONT_COORD(0x86, 7),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Slaking, 1),
      .enemyMonElevation = 0,
    }, //Slaking,
[SPECIES_GULPIN] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Gulpin, 1),
      .enemyMonElevation = 0,
    }, //Gulpin,
[SPECIES_SWALOT] = 
    {  
      FRONT_COORD(0x66, 5),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Swalot, 2),
      .enemyMonElevation = 0,
    }, //Swalot,
[SPECIES_TROPIUS] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Tropius, 1),
      .enemyMonElevation = 0,
    }, //Tropius,
[SPECIES_WHISMUR] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Whismur, 0),
      .enemyMonElevation = 0,
    }, //Whismur,
[SPECIES_LOUDRED] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Loudred, 2),
      .enemyMonElevation = 0,
    }, //Loudred,
[SPECIES_EXPLOUD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Exploud, 2),
      .enemyMonElevation = 0,
    }, //Exploud,
[SPECIES_CLAMPERL] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Clamperl, 0),
      .enemyMonElevation = 0,
    }, //Clamperl,
[SPECIES_HUNTAIL] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x68, 0x02),
      PIC_DATA_ICON_INDEX(Huntail, 0),
      .enemyMonElevation = 0,
    }, //Huntail,
[SPECIES_GOREBYSS] = 
    {  
      FRONT_COORD(0x86, 6),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Gorebyss, 0),
      .enemyMonElevation = 0,
    }, //Gorebyss,
[SPECIES_ABSOL] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x78, 0x03),
      PIC_DATA_ICON_INDEX(Absol, 0),
      .enemyMonElevation = 0,
    }, //Absol,
[SPECIES_SHUPPET] = 
    {  
      FRONT_COORD(0x56, 13),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Shuppet, 0),
      .enemyMonElevation = 12,
    }, //Shuppet,
[SPECIES_BANETTE] = 
    {  
      FRONT_COORD(0x55, 7),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Banette, 0),
      .enemyMonElevation = 10,
    }, //Banette,
[SPECIES_SEVIPER] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Seviper, 2),
      .enemyMonElevation = 0,
    }, //Seviper,
[SPECIES_ZANGOOSE] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Zangoose, 0),
      .enemyMonElevation = 0,
    }, //Zangoose,
[SPECIES_RELICANTH] = 
    {  
      FRONT_COORD(0x77, 10),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Relicanth, 1),
      .enemyMonElevation = 0,
    }, //Relicanth,
[SPECIES_ARON] = 
    {  
      FRONT_COORD(0x43, 14),
      BACK_COORD(0x54, 0x11),
      PIC_DATA_ICON_INDEX(Aron, 2),
      .enemyMonElevation = 0,
    }, //Aron,
[SPECIES_LAIRON] = 
    {  
      FRONT_COORD(0x75, 8),
      BACK_COORD(0x84, 0x11),
      PIC_DATA_ICON_INDEX(Lairon, 2),
      .enemyMonElevation = 0,
    }, //Lairon,
[SPECIES_AGGRON] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Aggron, 2),
      .enemyMonElevation = 0,
    }, //Aggron,
[SPECIES_CASTFORM] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x45, 0x0d),
      PIC_DATA_ICON_INDEX(Castform, 0),
      .enemyMonElevation = 16,
    }, //Castform,
[SPECIES_VOLBEAT] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Volbeat, 0),
      .enemyMonElevation = 3,
    }, //Volbeat,
[SPECIES_ILLUMISE] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x67, 0x06),
      PIC_DATA_ICON_INDEX(Illumise, 2),
      .enemyMonElevation = 7,
    }, //Illumise,
[SPECIES_LILEEP] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Lileep, 2),
      .enemyMonElevation = 0,
    }, //Lileep,
[SPECIES_CRADILY] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Cradily, 0),
      .enemyMonElevation = 0,
    }, //Cradily,
[SPECIES_ANORITH] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x83, 0x17),
      PIC_DATA_ICON_INDEX(Anorith, 0),
      .enemyMonElevation = 0,
    }, //Anorith,
[SPECIES_ARMALDO] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Armaldo, 0),
      .enemyMonElevation = 0,
    }, //Armaldo,
[SPECIES_RALTS] = 
    {  
      FRONT_COORD(0x35, 12),
      BACK_COORD(0x45, 0x0d),
      PIC_DATA_ICON_INDEX(Ralts, 1),
      .enemyMonElevation = 0,
    }, //Ralts,
[SPECIES_KIRLIA] = 
    {  
      FRONT_COORD(0x47, 6),
      BACK_COORD(0x57, 0x06),
      PIC_DATA_ICON_INDEX(Kirlia, 1),
      .enemyMonElevation = 0,
    }, //Kirlia,
[SPECIES_GARDEVOIR] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Gardevoir, 1),
      .enemyMonElevation = 0,
    }, //Gardevoir,
[SPECIES_BAGON] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Bagon, 2),
      .enemyMonElevation = 0,
    }, //Bagon,
[SPECIES_SHELGON] = 
    {  
      FRONT_COORD(0x66, 9),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Shelgon, 2),
      .enemyMonElevation = 0,
    }, //Shelgon,
[SPECIES_SALAMENCE] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Salamence, 0),
      .enemyMonElevation = 0,
    }, //Salamence,
[SPECIES_BELDUM] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Beldum, 0),
      .enemyMonElevation = 8,
    }, //Beldum,
[SPECIES_METANG] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Metang, 0),
      .enemyMonElevation = 0,
    }, //Metang,
[SPECIES_METAGROSS] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x83, 0x14),
      PIC_DATA_ICON_INDEX(Metagross, 0),
      .enemyMonElevation = 0,
    }, //Metagross,
[SPECIES_REGIROCK] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Regirock, 2),
      .enemyMonElevation = 0,
    }, //Regirock,
[SPECIES_REGICE] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Regice, 2),
      .enemyMonElevation = 0,
    }, //Regice,
[SPECIES_REGISTEEL] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Registeel, 2),
      .enemyMonElevation = 0,
    }, //Registeel,
[SPECIES_KYOGRE] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x84, 0x13),
      PIC_DATA_ICON_INDEX(Kyogre, 2),
      .enemyMonElevation = 0,
    }, //Kyogre,
[SPECIES_GROUDON] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Groudon, 0),
      .enemyMonElevation = 0,
    }, //Groudon,
[SPECIES_RAYQUAZA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Rayquaza, 1),
      .enemyMonElevation = 6,
    }, //Rayquaza,
[SPECIES_LATIAS] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0x02),
      PIC_DATA_ICON_INDEX(Latias, 0),
      .enemyMonElevation = 7,
    }, //Latias,
[SPECIES_LATIOS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Latios, 2),
      .enemyMonElevation = 6,
    }, //Latios,
[SPECIES_JIRACHI] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Jirachi, 0),
      .enemyMonElevation = 12,
    }, //Jirachi,
[SPECIES_DEOXYS] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Deoxys, 0),
      .enemyMonElevation = 8,
    }, //Deoxys,
[SPECIES_CHIMECHO] = 
    {  
      FRONT_COORD(0x37, 6),
      BACK_COORD(0x47, 0x07),
      PIC_DATA_ICON_INDEX(Chimecho, 0),
      .enemyMonElevation = 10,
    }, //Chimecho,
[SPECIES_EGG] = 
    {  
      FRONT_PIC(Egg),
      FRONT_COORD(0x33, 20),
      BACK_COORD(0x36, 10),
      .palette = gMonPalette_Egg,
      ICON(Egg, 1),
      .enemyMonElevation = 0,
    }, //Egg,
[SPECIES_UNOWN_B] = 
    {  
      FRONT_PIC(UnownB),
      FRONT_COORD(0x34, 16),
      BACK_PIC(UnownB),
      BACK_COORD(0x56, 9),
      PALETTES(Unown),
      ICON(UnownB, 0),
      .enemyMonElevation = 0,
    }, //UnownB,
[SPECIES_UNOWN_C] = 
    {  
      FRONT_PIC(UnownC),
      FRONT_COORD(0x44, 16),
      BACK_PIC(UnownC),
      BACK_COORD(0x67, 6),
      PALETTES(Unown),
      ICON(UnownC, 0),
      .enemyMonElevation = 0,
    }, //UnownC,
[SPECIES_UNOWN_D] = 
    {  
      FRONT_PIC(UnownD),
      FRONT_COORD(0x44, 16),
      BACK_PIC(UnownD),
      BACK_COORD(0x56, 8),
      PALETTES(Unown),
      ICON(UnownD, 0),
      .enemyMonElevation = 0,
    }, //UnownD,
[SPECIES_UNOWN_E] = 
    {  
      FRONT_PIC(UnownE),
      FRONT_COORD(0x44, 17),
      BACK_PIC(UnownE),
      BACK_COORD(0x56, 10),
      PALETTES(Unown),
      ICON(UnownE, 0),
      .enemyMonElevation = 0,
    }, //UnownE,
[SPECIES_UNOWN_F] = 
    {  
      FRONT_PIC(UnownF),
      FRONT_COORD(0x44, 17),
      BACK_PIC(UnownF),
      BACK_COORD(0x66, 10),
      PALETTES(Unown),
      ICON(UnownF, 0),
      .enemyMonElevation = 0,
    }, //UnownF,
[SPECIES_UNOWN_G] = 
    {  
      FRONT_PIC(UnownG),
      FRONT_COORD(0x35, 14),
      BACK_PIC(UnownG),
      BACK_COORD(0x57, 5),
      PALETTES(Unown),
      ICON(UnownG, 0),
      .enemyMonElevation = 0,
    }, //UnownG,
[SPECIES_UNOWN_H] = 
    {  
      FRONT_PIC(UnownH),
      FRONT_COORD(0x44, 16),
      BACK_PIC(UnownH),
      BACK_COORD(0x66, 8),
      PALETTES(Unown),
      ICON(UnownH, 0),
      .enemyMonElevation = 0,
    }, //UnownH,
[SPECIES_UNOWN_I] = 
    {  
      FRONT_PIC(UnownI),
      FRONT_COORD(0x34, 16),
      BACK_PIC(UnownI),
      BACK_COORD(0x37, 7),
      PALETTES(Unown),
      ICON(UnownI, 0),
      .enemyMonElevation = 0,
    }, //UnownI,
[SPECIES_UNOWN_J] = 
    {  
      FRONT_PIC(UnownJ),
      FRONT_COORD(0x34, 17),
      BACK_PIC(UnownJ),
      BACK_COORD(0x46, 9),
      PALETTES(Unown),
      ICON(UnownJ, 0),
      .enemyMonElevation = 0,
    }, //UnownJ,
[SPECIES_UNOWN_K] = 
    {  
      FRONT_PIC(UnownK),
      FRONT_COORD(0x44, 17),
      BACK_PIC(UnownK),
      BACK_COORD(0x57, 7),
      PALETTES(Unown),
      ICON(UnownK, 0),
      .enemyMonElevation = 0,
    }, //UnownK,
[SPECIES_UNOWN_L] = 
    {  
      FRONT_PIC(UnownL),
      FRONT_COORD(0x34, 19),
      BACK_PIC(UnownL),
      BACK_COORD(0x46, 10),
      PALETTES(Unown),
      ICON(UnownL, 0),
      .enemyMonElevation = 0,
    }, //UnownL,
[SPECIES_UNOWN_M] = 
    {  
      FRONT_PIC(UnownM),
      FRONT_COORD(0x44, 19),
      BACK_PIC(UnownM),
      BACK_COORD(0x65, 13),
      PALETTES(Unown),
      ICON(UnownM, 0),
      .enemyMonElevation = 0,
    }, //UnownM,
[SPECIES_UNOWN_N] = 
    {  
      FRONT_PIC(UnownN),
      FRONT_COORD(0x43, 20),
      BACK_PIC(UnownN),
      BACK_COORD(0x65, 13),
      PALETTES(Unown),
      ICON(UnownN, 0),
      .enemyMonElevation = 0,
    }, //UnownN,
[SPECIES_UNOWN_O] = 
    {  
      FRONT_PIC(UnownO),
      FRONT_COORD(0x44, 16),
      BACK_PIC(UnownO),
      BACK_COORD(0x66, 8),
      PALETTES(Unown),
      ICON(UnownO, 0),
      .enemyMonElevation = 0,
    }, //UnownO,
[SPECIES_UNOWN_P] = 
    {  
      FRONT_PIC(UnownP),
      FRONT_COORD(0x34, 19),
      BACK_PIC(UnownP),
      BACK_COORD(0x46, 10),
      PALETTES(Unown),
      ICON(UnownP, 0),
      .enemyMonElevation = 0,
    }, //UnownP,
[SPECIES_UNOWN_Q] = 
    {  
      FRONT_PIC(UnownQ),
      FRONT_COORD(0x43, 21),
      BACK_PIC(UnownQ),
      BACK_COORD(0x55, 15),
      PALETTES(Unown),
      ICON(UnownQ, 0),
      .enemyMonElevation = 0,
    }, //UnownQ,
[SPECIES_UNOWN_R] = 
    {  
      FRONT_PIC(UnownR),
      FRONT_COORD(0x34, 19),
      BACK_PIC(UnownR),
      BACK_COORD(0x45, 12),
      PALETTES(Unown),
      ICON(UnownR, 0),
      .enemyMonElevation = 0,
    }, //UnownR,
[SPECIES_UNOWN_S] = 
    {  
      FRONT_PIC(UnownS),
      FRONT_COORD(0x45, 12),
      BACK_PIC(UnownS),
      BACK_COORD(0x57, 4),
      PALETTES(Unown),
      ICON(UnownS, 0),
      .enemyMonElevation = 0,
    }, //UnownS,
[SPECIES_UNOWN_T] = 
    {  
      FRONT_PIC(UnownT),
      FRONT_COORD(0x34, 18),
      BACK_PIC(UnownT),
      BACK_COORD(0x45, 13),
      PALETTES(Unown),
      ICON(UnownT, 0),
      .enemyMonElevation = 0,
    }, //UnownT,
[SPECIES_UNOWN_U] = 
    {  
      FRONT_PIC(UnownU),
      FRONT_COORD(0x44, 18),
      BACK_PIC(UnownU),
      BACK_COORD(0x65, 13),
      PALETTES(Unown),
      ICON(UnownU, 0),
      .enemyMonElevation = 0,
    }, //UnownU,
[SPECIES_UNOWN_V] = 
    {  
      FRONT_PIC(UnownV),
      FRONT_COORD(0x44, 18),
      BACK_PIC(UnownV),
      BACK_COORD(0x56, 11),
      PALETTES(Unown),
      ICON(UnownV, 0),
      .enemyMonElevation = 0,
    }, //UnownV,
[SPECIES_UNOWN_W] = 
    {  
      FRONT_PIC(UnownW),
      FRONT_COORD(0x44, 19),
      BACK_PIC(UnownW),
      BACK_COORD(0x55, 13),
      PALETTES(Unown),
      ICON(UnownW, 0),
      .enemyMonElevation = 0,
    }, //UnownW,
[SPECIES_UNOWN_X] = 
    {  
      FRONT_PIC(UnownX),
      FRONT_COORD(0x33, 21),
      BACK_PIC(UnownX),
      BACK_COORD(0x55, 15),
      PALETTES(Unown),
      ICON(UnownX, 0),
      .enemyMonElevation = 0,
    }, //UnownX,
[SPECIES_UNOWN_Y] = 
    {  
      FRONT_PIC(UnownY),
      FRONT_COORD(0x34, 17),
      BACK_PIC(UnownY),
      BACK_COORD(0x46, 10),
      PALETTES(Unown),
      ICON(UnownY, 0),
      .enemyMonElevation = 0,
    }, //UnownY,
[SPECIES_UNOWN_Z] = 
    {  
      FRONT_PIC(UnownZ),
      FRONT_COORD(0x34, 16),
      BACK_PIC(UnownZ),
      BACK_COORD(0x46, 10),
      PALETTES(Unown),
      ICON(UnownZ, 0),
      .enemyMonElevation = 0,
    }, //UnownZ,
[SPECIES_UNOWN_EMARK] = 
    {  
      FRONT_PIC(UnownExclamationMark),
      FRONT_COORD(0x35, 15),
      BACK_PIC(UnownExclamationMark),
      BACK_COORD(0x37, 6),
      PALETTES(Unown),
      ICON(UnownExclamationMark, 0),
      .enemyMonElevation = 0,
    }, //UnownExclamationMark,
[SPECIES_UNOWN_QMARK] = 
    {  
      FRONT_PIC(UnownQuestionMark),
      FRONT_COORD(0x35, 13),
      BACK_PIC(UnownQuestionMark),
      BACK_COORD(0x47, 6),
      PALETTES(Unown),
      ICON(UnownQuestionMark, 0),
      .enemyMonElevation = 0,
    }, //UnownQuestionMark, //ok I see now part of problem, this doeesn't have a comma and others are misaligned.
[SPECIES_TURTWIG] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 6),
      PIC_DATA_ICON_INDEX(Turtwig, 1),
      .enemyMonElevation = 0,
    }, //Turtwig,
[SPECIES_GROTLE] = 
    {  
      FRONT_COORD(0x56, 7),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Grotle, 1),
      .enemyMonElevation = 0,
    }, //Grotle,
[SPECIES_TORTERRA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Torterra, 1),
      .enemyMonElevation = 0,
    }, //Torterra,
[SPECIES_CHIMCHAR] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Chimchar, 1),
      .enemyMonElevation = 0,
    }, //Chimchar,
[SPECIES_MONFERNO] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Monferno, 0),
      .enemyMonElevation = 0,
    }, //Monferno,
[SPECIES_INFERNAPE] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Infernape, 0),
      .enemyMonElevation = 0,
    }, //Infernape,
[SPECIES_PIPLUP] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x56, 10),
      PIC_DATA_ICON_INDEX(Piplup, 0),
      .enemyMonElevation = 0,
    }, //Piplup,
[SPECIES_PRINPLUP] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Prinplup, 0),
      .enemyMonElevation = 0,
    }, //Prinplup,
[SPECIES_EMPOLEON] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Empoleon, 0),
      .enemyMonElevation = 0,
    }, //Empoleon,
[SPECIES_STARLY] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Starly, 0),
      .enemyMonElevation = 0,
    }, //Starly,
[SPECIES_STARAVIA] = 
    {  
      FRONT_COORD(0x54, 8),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Staravia, 0),
      .enemyMonElevation = 0,
    }, //Staravia,
[SPECIES_STARAPTOR] = 
    {  
      FRONT_COORD(0x76, 3),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Staraptor, 0),
      .enemyMonElevation = 0,
    }, //Staraptor,
[SPECIES_BIDOOF] = 
    {  
      FRONT_COORD(0x54, 12),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Bidoof, 2),
      .enemyMonElevation = 0,
    }, //Bidoof,
[SPECIES_BIBAREL] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Bibarel, 2),
      .enemyMonElevation = 0,
    }, //Bibarel,
[SPECIES_KRICKETOT] = 
    {  
      FRONT_COORD(0x86, 11),
      BACK_COORD(0x67, 6),
      PIC_DATA_ICON_INDEX(Kricketot, 2),
      .enemyMonElevation = 0,
    }, //Kricketot,
[SPECIES_KRICKETUNE] = 
    {  
      FRONT_COORD(0x65, 7),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Kricketune, 2),
      .enemyMonElevation = 0,
    }, //Kricketune,
[SPECIES_SHINX] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Shinx, 0),
      .enemyMonElevation = 0,
    }, //Shinx,
[SPECIES_LUXIO] = 
    {  
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Luxio, 0),
      .enemyMonElevation = 0,
    }, //Luxio,
[SPECIES_LUXRAY] = 
    {  
      FRONT_COORD(0x44, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Luxray, 0),
      .enemyMonElevation = 0,
    }, //Luxray,
[SPECIES_BUDEW] = 
    {  
      FRONT_COORD(0x66, 14),
      BACK_COORD(0x57, 11),
      PIC_DATA_ICON_INDEX(Budew, 1),
      .enemyMonElevation = 0,
    }, //Budew,
[SPECIES_ROSERADE] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Roserade, 0),
      .enemyMonElevation = 0,
    }, //Roserade,
[SPECIES_CRANIDOS] = 
    {  
      FRONT_COORD(0x78, 10),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Cranidos, 0),
      .enemyMonElevation = 0,
    }, //Cranidos,
[SPECIES_RAMPARDOS] = 
    {  
      FRONT_COORD(0x65, 3),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Rampardos, 0),
      .enemyMonElevation = 0,
    }, //Rampardos,
[SPECIES_SHIELDON] = 
    {  
      FRONT_COORD(0x88, 15),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Shieldon, 1),
      .enemyMonElevation = 0,
    }, //Shieldon,
[SPECIES_BASTIODON] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Bastiodon, 1),
      .enemyMonElevation = 0,
    }, //Bastiodon,
[SPECIES_BURMY] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x57, 6),
      PIC_DATA_ICON_INDEX(Burmy, 1),
      .enemyMonElevation = 0,
    }, //Burmy,
[SPECIES_WORMADAM] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Wormadam, 1),
      .enemyMonElevation = 0,
    }, //Wormadam,
[SPECIES_MOTHIM] = 
    {  
      FRONT_COORD(0x76, 12),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Mothim, 0),
      .enemyMonElevation = 10,
    }, //Mothim,
[SPECIES_COMBEE] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x86, 22),
      PIC_DATA_ICON_INDEX(Combee, 0),
      .enemyMonElevation = 8,
    }, //Combee,
[SPECIES_VESPIQUEN] = 
    {  
      FRONT_COORD(0x66, 4),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Vespiquen, 0),
      .enemyMonElevation = 4,
    }, //Vespiquen,
[SPECIES_PACHIRISU] = 
    {  
      FRONT_COORD(0x78, 12),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Pachirisu, 0),
      .enemyMonElevation = 0,
    }, //Pachirisu,
[SPECIES_BUIZEL] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Buizel, 0),
      .enemyMonElevation = 0,
    }, //Buizel,
[SPECIES_FLOATZEL] = 
    {  
      FRONT_COORD(0x66, 3),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Floatzel, 0),
      .enemyMonElevation = 0,
    }, //Floatzel,
[SPECIES_CHERUBI] = 
    {  
      FRONT_COORD(0x78, 16),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Cherubi, 1),
      .enemyMonElevation = 0,
    }, //Cherubi,
[SPECIES_CHERRIM] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x57, 9),
      PIC_DATA_ICON_INDEX(Cherrim, 0),
      .enemyMonElevation = 0,
    }, //Cherrim,
[SPECIES_SHELLOS] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x57, 8),
      PIC_DATA_ICON_INDEX(Shellos, 0),
      .enemyMonElevation = 0,
    }, //Shellos,
[SPECIES_GASTRODON] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Gastrodon, 0),
      .enemyMonElevation = 0,
    }, //Gastrodon,
[SPECIES_AMBIPOM] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Ambipom, 2),
      .enemyMonElevation = 0,
    }, //Ambipom,
[SPECIES_DRIFLOON] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x58, 0),
      PIC_DATA_ICON_INDEX(Drifloon, 2),
      .enemyMonElevation = 5,
    }, //Drifloon,
[SPECIES_DRIFBLIM] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Drifblim, 2),
      .enemyMonElevation = 7,
    }, //Drifblim,
[SPECIES_BUNEARY] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Buneary, 2),
      .enemyMonElevation = 0,
    }, //Buneary,
[SPECIES_LOPUNNY] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Lopunny, 2),
      .enemyMonElevation = 0,
    }, //Lopunny,
[SPECIES_MISMAGIUS] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Mismagius, 2),
      .enemyMonElevation = 3,
    }, //Mismagius,
[SPECIES_HONCHKROW] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Honchkrow, 2),
      .enemyMonElevation = 0,
    }, //Honchkrow,
[SPECIES_GLAMEOW] = 
    {  
      FRONT_COORD(0x77, 8),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Glameow, 0),
      .enemyMonElevation = 0,
    }, //Glameow,
[SPECIES_PURUGLY] = 
    {  
      FRONT_COORD(0x55, 5),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Purugly, 0),
      .enemyMonElevation = 0,
    }, //Purugly,
[SPECIES_CHINGLING] = 
    {  
      FRONT_COORD(0x86, 15),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(Chingling, 1),
      .enemyMonElevation = 0,
    }, //Chingling,
[SPECIES_STUNKY] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Stunky, 2),
      .enemyMonElevation = 0,
    }, //Stunky,
[SPECIES_SKUNTANK] = 
    {  
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Skuntank, 2),
      .enemyMonElevation = 0,
    }, //Skuntank,
[SPECIES_BRONZOR] = 
    {  
      FRONT_COORD(0x54, 14),
      BACK_COORD(0x56, 9),
      PIC_DATA_ICON_INDEX(Bronzor, 0),
      .enemyMonElevation = 0,
    }, //Bronzor,
[SPECIES_BRONZONG] = 
    {  
      FRONT_COORD(0x75, 6),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Bronzong, 0),
      .enemyMonElevation = 4,
    }, //Bronzong,
[SPECIES_BONSLY] = 
    {  
      FRONT_COORD(0x55, 9),
      BACK_COORD(0x58, 6),
      PIC_DATA_ICON_INDEX(Bonsly, 1),
      .enemyMonElevation = 0,
    }, //Bonsly,
[SPECIES_MIME_JR] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(MimeJr, 0),
      .enemyMonElevation = 0,
    }, //MimeJr,
[SPECIES_HAPPINY] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Happiny, 0),
      .enemyMonElevation = 0,
    }, //Happiny,
[SPECIES_CHATOT] = 
    {  
      FRONT_COORD(0x78, 11),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(Chatot, 0),
      .enemyMonElevation = 0,
    }, //Chatot,
[SPECIES_SPIRITOMB] = 
    {  
      FRONT_COORD(0x65, 6),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Spiritomb, 2),
      .enemyMonElevation = 0,
    }, //Spiritomb,
[SPECIES_GIBLE] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Gible, 0),
      .enemyMonElevation = 0,
    }, //Gible,
[SPECIES_GABITE] = 
    {  
      FRONT_COORD(0x66, 2),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Gabite, 0),
      .enemyMonElevation = 0,
    }, //Gabite,
[SPECIES_GARCHOMP] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Garchomp, 0),
      .enemyMonElevation = 0,
    }, //Garchomp,
[SPECIES_MUNCHLAX] = 
    {  
      FRONT_COORD(0x74, 10),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Munchlax, 2),
      .enemyMonElevation = 0,
    }, //Munchlax,
[SPECIES_RIOLU] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Riolu, 2),
      .enemyMonElevation = 0,
    }, //Riolu,
[SPECIES_LUCARIO] = 
    {  
      FRONT_COORD(0x76, 7),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Lucario, 2),
      .enemyMonElevation = 0,
    }, //Lucario,
[SPECIES_HIPPOPOTAS] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Hippopotas, 1),
      .enemyMonElevation = 0,
    }, //Hippopotas,
[SPECIES_HIPPOWDON] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Hippowdon, 1),
      .enemyMonElevation = 0,
    }, //Hippowdon,
[SPECIES_SKORUPI] = 
    {  
      FRONT_COORD(0x87, 11),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Skorupi, 0),
      .enemyMonElevation = 0,
    }, //Skorupi,
[SPECIES_DRAPION] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Drapion, 2),
      .enemyMonElevation = 0,
    }, //Drapion,
[SPECIES_CROAGUNK] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Croagunk, 0),
      .enemyMonElevation = 0,
    }, //Croagunk,
[SPECIES_TOXICROAK] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Toxicroak, 0),
      .enemyMonElevation = 0,
    }, //Toxicroak,
[SPECIES_CARNIVINE] = 
    {  
      FRONT_COORD(0x65, 10),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Carnivine, 1),
      .enemyMonElevation = 0,
    }, //Carnivine,
[SPECIES_FINNEON] = 
    {  
      FRONT_COORD(0x66, 14),
      BACK_COORD(0x75, 13),
      PIC_DATA_ICON_INDEX(Finneon, 0),
      .enemyMonElevation = 0,
    }, //Finneon,
[SPECIES_LUMINEON] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Lumineon, 0),
      .enemyMonElevation = 0,
    }, //Lumineon,
[SPECIES_MANTYKE] = 
    {  
      FRONT_COORD(0x46, 12),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Mantyke, 0),
      .enemyMonElevation = 0,
    }, //Mantyke,
[SPECIES_SNOVER] = 
    {  
      FRONT_COORD(0x87, 10),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Snover, 1),
      .enemyMonElevation = 0,
    }, //Snover,
[SPECIES_ABOMASNOW] = 
    {  
      FRONT_COORD(0x54, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Abomasnow, 1),
      .enemyMonElevation = 0,
    }, //Abomasnow,
[SPECIES_WEAVILE] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Weavile, 0),
      .enemyMonElevation = 0,
    }, //Weavile,
[SPECIES_MAGNEZONE] = 
    {  
      FRONT_COORD(0x77, 4),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Magnezone, 0),
      .enemyMonElevation = 4,
    }, //Magnezone,
[SPECIES_LICKILICKY] = 
    {  
      FRONT_COORD(0x66, 2),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Lickilicky, 1),
      .enemyMonElevation = 0,
    }, //Lickilicky,
[SPECIES_RHYPERIOR] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Rhyperior, 0),
      .enemyMonElevation = 0,
    }, //Rhyperior,
[SPECIES_TANGROWTH] = 
    {  
      FRONT_COORD(0x66, 2),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Tangrowth, 0),
      .enemyMonElevation = 0,
    }, //Tangrowth,
[SPECIES_ELECTIVIRE] = 
    {  
      FRONT_COORD(0x86, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Electivire, 1),
      .enemyMonElevation = 0,
    }, //Electivire,
[SPECIES_MAGMORTAR] = 
    {  
      FRONT_COORD(0x43, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Magmortar, 0),
      .enemyMonElevation = 0,
    }, //Magmortar,
[SPECIES_TOGEKISS] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Togekiss, 2),
      .enemyMonElevation = 14,
    }, //Togekiss,
[SPECIES_YANMEGA] = 
    {  
      FRONT_COORD(0x66, 5),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Yanmega, 1),
      .enemyMonElevation = 6,
    }, //Yanmega,
[SPECIES_LEAFEON] = 
    {  
      FRONT_COORD(0x57, 9),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Leafeon, 1),
      .enemyMonElevation = 0,
    }, //Leafeon,
[SPECIES_GLACEON] = 
    {  
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x78, 6),
      PIC_DATA_ICON_INDEX(Glaceon, 0),
      .enemyMonElevation = 0,
    }, //Glaceon,
[SPECIES_GLISCOR] = 
    {  
      FRONT_COORD(0x76, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Gliscor, 2),
      .enemyMonElevation = 6,
    }, //Gliscor,
[SPECIES_MAMOSWINE] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Mamoswine, 2),
      .enemyMonElevation = 0,
    }, //Mamoswine,
[SPECIES_PORYGON_Z] = 
    {  
      FRONT_COORD(0x65, 6),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(PorygonZ, 0),
      .enemyMonElevation = 0,
    }, //Porygon_Z,
[SPECIES_GALLADE] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Gallade, 1),
      .enemyMonElevation = 0,
    }, //Gallade,
[SPECIES_PROBOPASS] = 
    {  
      FRONT_COORD(0x55, 4),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Probopass, 0),
      .enemyMonElevation = 0,
    }, //Probopass,
[SPECIES_DUSKNOIR] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Dusknoir, 2),
      .enemyMonElevation = 0,
    }, //Dusknoir,
[SPECIES_FROSLASS] = 
    {  
      FRONT_COORD(0x77, 8),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Froslass, 0),
      .enemyMonElevation = 0,
    }, //Froslass,
[SPECIES_ROTOM] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Rotom, 0),
      .enemyMonElevation = 10,
    }, //Rotom,
[SPECIES_UXIE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Uxie, 0),
      .enemyMonElevation = 6,
    }, //Uxie,
[SPECIES_MESPRIT] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Mesprit, 0),
      .enemyMonElevation = 6,
    }, //Mesprit,
[SPECIES_AZELF] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Azelf, 0),
      .enemyMonElevation = 6,
    }, //Azelf,
[SPECIES_DIALGA] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Dialga, 2),
      .enemyMonElevation = 0,
    }, //Dialga,
[SPECIES_PALKIA] = 
    {  
      FRONT_COORD(0x65, 0),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Palkia, 2),
      .enemyMonElevation = 0,
    }, //Palkia,
[SPECIES_HEATRAN] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Heatran, 0),
      .enemyMonElevation = 0,
    }, //Heatran,
[SPECIES_REGIGIGAS] = 
    {  
      FRONT_COORD(0x44, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Regigigas, 0),
      .enemyMonElevation = 0,
    }, //Regigigas,
[SPECIES_GIRATINA] = 
    {  
      FRONT_COORD(0x55, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Giratina, 0),
      .enemyMonElevation = 0,
    }, //Giratina,
[SPECIES_CRESSELIA] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Cresselia, 0),
      .enemyMonElevation = 3,
    }, //Cresselia,
[SPECIES_PHIONE] = 
    {  
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Phione, 0),
      .enemyMonElevation = 0,
    }, //Phione,
[SPECIES_MANAPHY] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Manaphy, 0),
      .enemyMonElevation = 0,
    }, //Manaphy,
[SPECIES_DARKRAI] = 
    {  
      FRONT_COORD(0x76, 3),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Darkrai, 0),
      .enemyMonElevation = 4,
    }, //Darkrai,
[SPECIES_SHAYMIN] = 
    {  
      FRONT_COORD(0x87, 16),
      BACK_COORD(0x75, 15),
      PIC_DATA_ICON_INDEX(Shaymin, 1),
      .enemyMonElevation = 0,
    }, //Shaymin,
[SPECIES_ARCEUS] = 
    {  
      FRONT_COORD(0x67, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_VICTINI] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x58, 7),
      PIC_DATA_ICON_INDEX(Victini, 0),
      .enemyMonElevation = 0,
    }, //Victini,
[SPECIES_SNIVY] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Snivy, 1),
      .enemyMonElevation = 0,
    }, //Snivy,
[SPECIES_SERVINE] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(Servine, 1),
      .enemyMonElevation = 0,
    }, //Servine,
[SPECIES_SERPERIOR] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Serperior, 1),
      .enemyMonElevation = 0,
    }, //Serperior,
[SPECIES_TEPIG] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Tepig, 0),
      .enemyMonElevation = 0,
    }, //Tepig,
[SPECIES_PIGNITE] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Pignite, 0),
      .enemyMonElevation = 0,
    }, //Pignite,
[SPECIES_EMBOAR] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Emboar, 0),
      .enemyMonElevation = 0,
    }, //Emboar,
[SPECIES_OSHAWOTT] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 14),
      PIC_DATA_ICON_INDEX(Oshawott, 0),
      .enemyMonElevation = 0,
    }, //Oshawott,
[SPECIES_DEWOTT] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Dewott, 0),
      .enemyMonElevation = 0,
    }, //Dewott,
[SPECIES_SAMUROTT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Samurott, 2),
      .enemyMonElevation = 0,
    }, //Samurott,
[SPECIES_PATRAT] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Patrat, 2),
      .enemyMonElevation = 0,
    }, //Patrat,
[SPECIES_WATCHOG] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Watchog, 2),
      .enemyMonElevation = 0,
    }, //Watchog,
[SPECIES_LILLIPUP] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 12),
      PIC_DATA_ICON_INDEX(Lillipup, 2),
      .enemyMonElevation = 0,
    }, //Lillipup,
[SPECIES_HERDIER] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x67, 10),
      PIC_DATA_ICON_INDEX(Herdier, 2),
      .enemyMonElevation = 0,
    }, //Herdier,
[SPECIES_STOUTLAND] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Stoutland, 2),
      .enemyMonElevation = 0,
    }, //Stoutland,
[SPECIES_PURRLOIN] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Purrloin, 0),
      .enemyMonElevation = 0,
    }, //Purrloin,
[SPECIES_LIEPARD] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Liepard, 0),
      .enemyMonElevation = 0,
    }, //Liepard,
[SPECIES_PANSAGE] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(Pansage, 1),
      .enemyMonElevation = 0,
    }, //Pansage,
[SPECIES_SIMISAGE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x78, 6),
      PIC_DATA_ICON_INDEX(Simisage, 1),
      .enemyMonElevation = 0,
    }, //Simisage,
[SPECIES_PANSEAR] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 10),
      PIC_DATA_ICON_INDEX(Pansear, 2),
      .enemyMonElevation = 0,
    }, //Pansear,
[SPECIES_SIMISEAR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Simisear, 2),
      .enemyMonElevation = 0,
    }, //Simisear,
[SPECIES_PANPOUR] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(Panpour, 2),
      .enemyMonElevation = 0,
    }, //Panpour,
[SPECIES_SIMIPOUR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Simipour, 2),
      .enemyMonElevation = 0,
    }, //Simipour,
[SPECIES_MUNNA] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x64, 16),
      PIC_DATA_ICON_INDEX(Munna, 0),
      .enemyMonElevation = 0,
    }, //Munna,
[SPECIES_MUSHARNA] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Musharna, 0),
      .enemyMonElevation = 0,
    }, //Musharna,
[SPECIES_PIDOVE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Pidove, 0),
      .enemyMonElevation = 0,
    }, //Pidove,
[SPECIES_TRANQUILL] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Tranquill, 0),
      .enemyMonElevation = 0,
    }, //Tranquill,
[SPECIES_UNFEZANT_MALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(UnfezantMale, 1),
      .enemyMonElevation = 0,
    }, //Unfezant,
[SPECIES_BLITZLE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Blitzle, 2),
      .enemyMonElevation = 0,
    }, //Blitzle,
[SPECIES_ZEBSTRIKA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Zebstrika, 2),
      .enemyMonElevation = 0,
    }, //Zebstrika,
[SPECIES_ROGGENROLA] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 13),
      PIC_DATA_ICON_INDEX(Roggenrola, 2),
      .enemyMonElevation = 0,
    }, //Roggenrola,
[SPECIES_BOLDORE] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x85, 16),
      PIC_DATA_ICON_INDEX(Boldore, 0),
      .enemyMonElevation = 0,
    }, //Boldore,
[SPECIES_GIGALITH] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Gigalith, 0),
      .enemyMonElevation = 0,
    }, //Gigalith,
[SPECIES_WOOBAT] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Woobat, 0),
      .enemyMonElevation = 19,
    }, //Woobat,
[SPECIES_SWOOBAT] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Swoobat, 0),
      .enemyMonElevation = 12,
    }, //Swoobat,
[SPECIES_DRILBUR] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Drilbur, 0),
      .enemyMonElevation = 0,
    }, //Drilbur,
[SPECIES_EXCADRILL] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Excadrill, 0),
      .enemyMonElevation = 0,
    }, //Excadrill,
[SPECIES_AUDINO] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x77, 9),
      PIC_DATA_ICON_INDEX(Audino, 1),
      .enemyMonElevation = 0,
    }, //Audino,
[SPECIES_TIMBURR] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Timburr, 1),
      .enemyMonElevation = 0,
    }, //Timburr,
[SPECIES_GURDURR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Gurdurr, 1),
      .enemyMonElevation = 0,
    }, //Gurdurr,
[SPECIES_CONKELDURR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 13),
      PIC_DATA_ICON_INDEX(Conkeldurr, 1),
      .enemyMonElevation = 0,
    }, //Conkeldurr,
[SPECIES_TYMPOLE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x54, 17),
      PIC_DATA_ICON_INDEX(Tympole, 2),
      .enemyMonElevation = 0,
    }, //Tympole,
[SPECIES_PALPITOAD] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Palpitoad, 2),
      .enemyMonElevation = 0,
    }, //Palpitoad,
[SPECIES_SEISMITOAD] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Seismitoad, 0),
      .enemyMonElevation = 0,
    }, //Seismitoad,
[SPECIES_THROH] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Throh, 0),
      .enemyMonElevation = 0,
    }, //Throh,
[SPECIES_SAWK] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Sawk, 0),
      .enemyMonElevation = 0,
    }, //Sawk,
[SPECIES_SEWADDLE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 13),
      PIC_DATA_ICON_INDEX(Sewaddle, 1),
      .enemyMonElevation = 0,
    }, //Sewaddle,
[SPECIES_SWADLOON] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 10),
      PIC_DATA_ICON_INDEX(Swadloon, 1),
      .enemyMonElevation = 0,
    }, //Swadloon,
[SPECIES_LEAVANNY] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Leavanny, 1),
      .enemyMonElevation = 0,
    }, //Leavanny,
[SPECIES_VENIPEDE] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Venipede, 1),
      .enemyMonElevation = 0,
    }, //Venipede,
[SPECIES_WHIRLIPEDE] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Whirlipede, 2),
      .enemyMonElevation = 0,
    }, //Whirlipede,
[SPECIES_SCOLIPEDE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Scolipede, 2),
      .enemyMonElevation = 0,
    }, //Scolipede,
[SPECIES_COTTONEE] = 
    {  
      FRONT_COORD(0x45, 18),
      BACK_COORD(0x84, 18),
      PIC_DATA_ICON_INDEX(Cottonee, 1),
      .enemyMonElevation = 0,
    }, //Cottonee,
[SPECIES_WHIMSICOTT] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Whimsicott, 1),
      .enemyMonElevation = 0,
    }, //Whimsicott,
[SPECIES_PETILIL] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x57, 9),
      PIC_DATA_ICON_INDEX(Petilil, 1),
      .enemyMonElevation = 7,
    }, //Petilil,
[SPECIES_LILLIGANT] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Lilligant, 1),
      .enemyMonElevation = 0,
    }, //Lilligant,
[SPECIES_BASCULIN] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 16),
      PIC_DATA_ICON_INDEX(Basculin, 1),
      .enemyMonElevation = 0,
    }, //Basculin,
[SPECIES_SANDILE] = 
    {  
      FRONT_COORD(0x45, 18),
      BACK_COORD(0x84, 18),
      PIC_DATA_ICON_INDEX(Sandile, 1),
      .enemyMonElevation = 0,
    }, //Sandile,
[SPECIES_KROKOROK] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Krokorok, 1),
      .enemyMonElevation = 0,
    }, //Krokorok,
[SPECIES_KROOKODILE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Krookodile, 0),
      .enemyMonElevation = 0,
    }, //Krookodile,
[SPECIES_DARUMAKA] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x76, 12),
      PIC_DATA_ICON_INDEX(Darumaka, 0),
      .enemyMonElevation = 0,
    }, //Darumaka,
[SPECIES_DARMANITAN] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Darmanitan, 0),
      .enemyMonElevation = 0,
    }, //Darmanitan,
[SPECIES_MARACTUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Maractus, 1),
      .enemyMonElevation = 0,
    }, //Maractus,
[SPECIES_DWEBBLE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x74, 17),
      PIC_DATA_ICON_INDEX(Dwebble, 0),
      .enemyMonElevation = 0,
    }, //Dwebble,
[SPECIES_CRUSTLE] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Crustle, 2),
      .enemyMonElevation = 0,
    }, //Crustle,
[SPECIES_SCRAGGY] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Scraggy, 2),
      .enemyMonElevation = 0,
    }, //Scraggy,
[SPECIES_SCRAFTY] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(Scrafty, 0),
      .enemyMonElevation = 0,
    }, //Scrafty,
[SPECIES_SIGILYPH] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Sigilyph, 0),
      .enemyMonElevation = 7,
    }, //Sigilyph,
[SPECIES_YAMASK] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x55, 14),
      PIC_DATA_ICON_INDEX(Yamask, 0),
      .enemyMonElevation = 10,
    }, //Yamask,
[SPECIES_COFAGRIGUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Cofagrigus, 0),
      .enemyMonElevation = 0,
    }, //Cofagrigus,
[SPECIES_TIRTOUGA] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Tirtouga, 2),
      .enemyMonElevation = 0,
    }, //Tirtouga,
[SPECIES_CARRACOSTA] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Carracosta, 2),
      .enemyMonElevation = 0,
    }, //Carracosta,
[SPECIES_ARCHEN] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Archen, 0),
      .enemyMonElevation = 0,
    }, //Archen,
[SPECIES_ARCHEOPS] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Archeops, 0),
      .enemyMonElevation = 8,
    }, //Archeops,
[SPECIES_TRUBBISH] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(Trubbish, 1),
      .enemyMonElevation = 0,
    }, //Trubbish,
[SPECIES_GARBODOR] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Garbodor, 1),
      .enemyMonElevation = 0,
    }, //Garbodor,
[SPECIES_ZORUA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Zorua, 0),
      .enemyMonElevation = 0,
    }, //Zorua,
[SPECIES_ZOROARK] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Zoroark, 0),
      .enemyMonElevation = 0,
    }, //Zoroark,
[SPECIES_MINCCINO] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Minccino, 0),
      .enemyMonElevation = 0,
    }, //Minccino,
[SPECIES_CINCCINO] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Cinccino, 0),
      .enemyMonElevation = 0,
    }, //Cinccino,
[SPECIES_GOTHITA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 10),
      PIC_DATA_ICON_INDEX(Gothita, 2),
      .enemyMonElevation = 0,
    }, //Gothita,
[SPECIES_GOTHORITA] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Gothorita, 2),
      .enemyMonElevation = 0,
    }, //Gothorita,
[SPECIES_GOTHITELLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Gothitelle, 2),
      .enemyMonElevation = 0,
    }, //Gothitelle,
[SPECIES_SOLOSIS] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x64, 19),
      PIC_DATA_ICON_INDEX(Solosis, 1),
      .enemyMonElevation = 14,
    }, //Solosis,
[SPECIES_DUOSION] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 13),
      PIC_DATA_ICON_INDEX(Duosion, 1),
      .enemyMonElevation = 7,
    }, //Duosion,
[SPECIES_REUNICLUS] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x86, 13),
      PIC_DATA_ICON_INDEX(Reuniclus, 1),
      .enemyMonElevation = 3,
    }, //Reuniclus,
[SPECIES_DUCKLETT] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 10),
      PIC_DATA_ICON_INDEX(Ducklett, 0),
      .enemyMonElevation = 0,
    }, //Ducklett,
[SPECIES_SWANNA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Swanna, 2),
      .enemyMonElevation = 0,
    }, //Swanna,
[SPECIES_VANILLITE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 9),
      PIC_DATA_ICON_INDEX(Vanillite, 0),
      .enemyMonElevation = 0,
    }, //Vanillite,
[SPECIES_VANILLISH] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Vanillish, 2),
      .enemyMonElevation = 0,
    }, //Vanillish,
[SPECIES_VANILLUXE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Vanilluxe, 2),
      .enemyMonElevation = 0,
    }, //Vanilluxe,
[SPECIES_DEERLING] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Deerling, 1),
      .enemyMonElevation = 0,
    }, //Deerling,
[SPECIES_SAWSBUCK] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(Sawsbuck, 1),
      .enemyMonElevation = 0,
    }, //Sawsbuck,
[SPECIES_EMOLGA] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x75, 16),
      PIC_DATA_ICON_INDEX(Emolga, 2),
      .enemyMonElevation = 19,
    }, //Emolga,
[SPECIES_KARRABLAST] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x66, 14),
      PIC_DATA_ICON_INDEX(Karrablast, 0),
      .enemyMonElevation = 0,
    }, //Karrablast,
[SPECIES_ESCAVALIER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Escavalier, 0),
      .enemyMonElevation = 0,
    }, //Escavalier,
[SPECIES_FOONGUS] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Foongus, 0),
      .enemyMonElevation = 0,
    }, //Foongus,
[SPECIES_AMOONGUSS] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Amoonguss, 1),
      .enemyMonElevation = 0,
    }, //Amoonguss,
[SPECIES_FRILLISH_MALE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x57, 7),
      PIC_DATA_ICON_INDEX(FrillishMale, 0),
      .enemyMonElevation = 0,
    }, //Frillish,
[SPECIES_JELLICENT_MALE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(JellicentMale, 0),
      .enemyMonElevation = 0,
    }, //Jellicent,
[SPECIES_ALOMOMOLA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Alomomola, 0),
      .enemyMonElevation = 0,
    }, //Alomomola,
[SPECIES_JOLTIK] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x64, 19),
      PIC_DATA_ICON_INDEX(Joltik, 0),
      .enemyMonElevation = 0,
    }, //Joltik,
[SPECIES_GALVANTULA] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x85, 18),
      PIC_DATA_ICON_INDEX(Galvantula, 2),
      .enemyMonElevation = 0,
    }, //Galvantula,
[SPECIES_FERROSEED] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 15),
      PIC_DATA_ICON_INDEX(Ferroseed, 1),
      .enemyMonElevation = 0,
    }, //Ferroseed,
[SPECIES_FERROTHORN] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Ferrothorn, 1),
      .enemyMonElevation = 0,
    }, //Ferrothorn,
[SPECIES_KLINK] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(Klink, 0),
      .enemyMonElevation = 0,
    }, //Klink,
[SPECIES_KLANG] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Klang, 0),
      .enemyMonElevation = 0,
    }, //Klang,
[SPECIES_KLINKLANG] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Klinklang, 0),
      .enemyMonElevation = 0,
    }, //Klinklang,
[SPECIES_TYNAMO] = 
    {  
      FRONT_COORD(0x45, 22),
      BACK_COORD(0x83, 21),
      PIC_DATA_ICON_INDEX(Tynamo, 0),
      .enemyMonElevation = 16,
    }, //Tynamo,
[SPECIES_EELEKTRIK] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(Eelektrik, 0),
      .enemyMonElevation = 8,
    }, //Eelektrik,
[SPECIES_EELEKTROSS] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Eelektross, 0),
      .enemyMonElevation = 8,
    }, //Eelektross,
[SPECIES_ELGYEM] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 10),
      PIC_DATA_ICON_INDEX(Elgyem, 0),
      .enemyMonElevation = 0,
    }, //Elgyem,
[SPECIES_BEHEEYEM] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Beheeyem, 2),
      .enemyMonElevation = 0,
    }, //Beheeyem,
[SPECIES_LITWICK] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x55, 14),
      PIC_DATA_ICON_INDEX(Litwick, 2),
      .enemyMonElevation = 0,
    }, //Litwick,
[SPECIES_LAMPENT] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x76, 12),
      PIC_DATA_ICON_INDEX(Lampent, 2),
      .enemyMonElevation = 0,
    }, //Lampent,
[SPECIES_CHANDELURE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Chandelure, 2),
      .enemyMonElevation = 0,
    }, //Chandelure,
[SPECIES_AXEW] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Axew, 1),
      .enemyMonElevation = 0,
    }, //Axew,
[SPECIES_FRAXURE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x86, 13),
      PIC_DATA_ICON_INDEX(Fraxure, 1),
      .enemyMonElevation = 0,
    }, //Fraxure,
[SPECIES_HAXORUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Haxorus, 2),
      .enemyMonElevation = 0,
    }, //Haxorus,
[SPECIES_CUBCHOO] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x55, 12),
      PIC_DATA_ICON_INDEX(Cubchoo, 0),
      .enemyMonElevation = 0,
    }, //Cubchoo,
[SPECIES_BEARTIC] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Beartic, 0),
      .enemyMonElevation = 0,
    }, //Beartic,
[SPECIES_CRYOGONAL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(Cryogonal, 0),
      .enemyMonElevation = 0,
    }, //Cryogonal,
[SPECIES_SHELMET] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x84, 19),
      PIC_DATA_ICON_INDEX(Shelmet, 1),
      .enemyMonElevation = 0,
    }, //Shelmet,
[SPECIES_ACCELGOR] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Accelgor, 1),
      .enemyMonElevation = 0,
    }, //Accelgor,
[SPECIES_STUNFISK] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x83, 22),
      PIC_DATA_ICON_INDEX(Stunfisk, 2),
      .enemyMonElevation = 0,
    }, //Stunfisk,
[SPECIES_MIENFOO] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(Mienfoo, 1),
      .enemyMonElevation = 0,
    }, //Mienfoo,
[SPECIES_MIENSHAO] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Mienshao, 2),
      .enemyMonElevation = 0,
    }, //Mienshao,
[SPECIES_DRUDDIGON] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Druddigon, 0),
      .enemyMonElevation = 0,
    }, //Druddigon,
[SPECIES_GOLETT] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Golett, 0),
      .enemyMonElevation = 0,
    }, //Golett,
[SPECIES_GOLURK] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Golurk, 0),
      .enemyMonElevation = 0,
    }, //Golurk,
[SPECIES_PAWNIARD] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Pawniard, 0),
      .enemyMonElevation = 0,
    }, //Pawniard,
[SPECIES_BISHARP] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Bisharp, 0),
      .enemyMonElevation = 0,
    }, //Bisharp,
[SPECIES_BOUFFALANT] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Bouffalant, 2),
      .enemyMonElevation = 0,
    }, //Bouffalant,
[SPECIES_RUFFLET] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Rufflet, 2),
      .enemyMonElevation = 0,
    }, //Rufflet,
[SPECIES_BRAVIARY] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Braviary, 0),
      .enemyMonElevation = 8,
    }, //Braviary,
[SPECIES_VULLABY] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x86, 14),
      PIC_DATA_ICON_INDEX(Vullaby, 0),
      .enemyMonElevation = 0,
    }, //Vullaby,
[SPECIES_MANDIBUZZ] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Mandibuzz, 1),
      .enemyMonElevation = 0,
    }, //Mandibuzz,
[SPECIES_HEATMOR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x83, 21),
      PIC_DATA_ICON_INDEX(Heatmor, 2),
      .enemyMonElevation = 0,
    }, //Heatmor,
[SPECIES_DURANT] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x84, 17),
      PIC_DATA_ICON_INDEX(Durant, 0),
      .enemyMonElevation = 0,
    }, //Durant,
[SPECIES_DEINO] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x66, 14),
      PIC_DATA_ICON_INDEX(Deino, 2),
      .enemyMonElevation = 0,
    }, //Deino,
[SPECIES_ZWEILOUS] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Zweilous, 2),
      .enemyMonElevation = 0,
    }, //Zweilous,
[SPECIES_HYDREIGON] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Hydreigon, 2),
      .enemyMonElevation = 3,
    }, //Hydreigon,
[SPECIES_LARVESTA] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Larvesta, 0),
      .enemyMonElevation = 0,
    }, //Larvesta,
[SPECIES_VOLCARONA] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Volcarona, 0),
      .enemyMonElevation = 0,
    }, //Volcarona,
[SPECIES_COBALION] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 6),
      PIC_DATA_ICON_INDEX(Cobalion, 0),
      .enemyMonElevation = 0,
    }, //Cobalion,
[SPECIES_TERRAKION] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Terrakion, 2),
      .enemyMonElevation = 0,
    }, //Terrakion,
[SPECIES_VIRIZION] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Virizion, 1),
      .enemyMonElevation = 0,
    }, //Virizion,
[SPECIES_TORNADUS] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Tornadus, 1),
      .enemyMonElevation = 7,
    }, //Tornadus,
[SPECIES_THUNDURUS] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Thundurus, 0),
      .enemyMonElevation = 7,
    }, //Thundurus,
[SPECIES_RESHIRAM] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Reshiram, 0),
      .enemyMonElevation = 0,
    }, //Reshiram,
[SPECIES_ZEKROM] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Zekrom, 2),
      .enemyMonElevation = 0,
    }, //Zekrom,
[SPECIES_LANDORUS] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Landorus, 0),
      .enemyMonElevation = 7,
    }, //Landorus,
[SPECIES_KYUREM] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Kyurem, 0),
      .enemyMonElevation = 0,
    }, //Kyurem,
[SPECIES_KELDEO] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(Keldeo, 0),
      .enemyMonElevation = 0,
    }, //Keldeo,
[SPECIES_MELOETTA] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Meloetta, 4),
      .enemyMonElevation = 0,
    }, //Meloetta,
[SPECIES_GENESECT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Genesect, 2),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_CHESPIN] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x78, 6),
      PIC_DATA_ICON_INDEX(Chespin, 1),
      .enemyMonElevation = 0,
    }, //Chespin,
[SPECIES_QUILLADIN] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Quilladin, 1),
      .enemyMonElevation = 0,
    }, //Quilladin,
[SPECIES_CHESNAUGHT] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Chesnaught, 1),
      .enemyMonElevation = 0,
    }, //Chesnaught,
[SPECIES_FENNEKIN] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Fennekin, 0),
      .enemyMonElevation = 0,
    }, //Fennekin,
[SPECIES_BRAIXEN] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Braixen, 0),
      .enemyMonElevation = 0,
    }, //Braixen,
[SPECIES_DELPHOX] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Delphox, 0),
      .enemyMonElevation = 0,
    }, //Delphox,
[SPECIES_FROAKIE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Froakie, 0),
      .enemyMonElevation = 0,
    }, //Froakie,
[SPECIES_FROGADIER] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Frogadier, 0),
      .enemyMonElevation = 0,
    }, //Frogadier,
[SPECIES_GRENINJA] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Greninja, 0),
      .enemyMonElevation = 0,
    }, //Greninja,
[SPECIES_BUNNELBY] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Bunnelby, 2),
      .enemyMonElevation = 0,
    }, //Bunnelby,
[SPECIES_DIGGERSBY] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Diggersby, 2),
      .enemyMonElevation = 0,
    }, //Diggersby,
[SPECIES_FLETCHLING] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Fletchling, 2),
      .enemyMonElevation = 0,
    }, //Fletchling,
[SPECIES_FLETCHINDER] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Fletchinder, 2),
      .enemyMonElevation = 9,
    }, //Fletchinder,
[SPECIES_TALONFLAME] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Talonflame, 2),
      .enemyMonElevation = 7,
    }, //Talonflame,
[SPECIES_SCATTERBUG] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x57, 12),
      PIC_DATA_ICON_INDEX(Scatterbug, 1),
      .enemyMonElevation = 0,
    }, //Scatterbug,
[SPECIES_SPEWPA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 12),
      PIC_DATA_ICON_INDEX(Spewpa, 1),
      .enemyMonElevation = 0,
    }, //Spewpa,
[SPECIES_VIVILLON_SNOW] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSnow, 0),
      .enemyMonElevation = 9,
    }, //Vivillon,
[SPECIES_LITLEO] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Litleo, 2),
      .enemyMonElevation = 0,
    }, //Litleo,
[SPECIES_PYROAR_MALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(PyroarMale, 2),
      .enemyMonElevation = 0,
    }, //Pyroar,
[SPECIES_FLABEBE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Flabebe, 1),
      .enemyMonElevation = 0,
    }, //Flabebe,
[SPECIES_FLOETTE] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Floette, 1),
      .enemyMonElevation = 0,
    }, //Floette,
[SPECIES_FLORGES] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Florges, 0),
      .enemyMonElevation = 0,
    }, //Florges,
[SPECIES_SKIDDO] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Skiddo, 1),
      .enemyMonElevation = 0,
    }, //Skiddo,
[SPECIES_GOGOAT] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Gogoat, 1),
      .enemyMonElevation = 0,
    }, //Gogoat,
[SPECIES_PANCHAM] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Pancham, 1),
      .enemyMonElevation = 0,
    }, //Pancham,
[SPECIES_PANGORO] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Pangoro, 1),
      .enemyMonElevation = 0,
    }, //Pangoro,
[SPECIES_FURFROU] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Furfrou, 0),
      .enemyMonElevation = 0,
    }, //Furfrou,
[SPECIES_ESPURR] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Espurr, 2),
      .enemyMonElevation = 0,
    }, //Espurr,
[SPECIES_MEOWSTIC_MALE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(MeowsticMale, 0),
      .enemyMonElevation = 0,
    }, //Meowstic,
[SPECIES_HONEDGE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Honedge, 2),
      .enemyMonElevation = 0,
    }, //Honedge,
[SPECIES_DOUBLADE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Doublade, 2),
      .enemyMonElevation = 0,
    }, //Doublade,
[SPECIES_AEGISLASH] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Aegislash, 2),
      .enemyMonElevation = 0,
    }, //Aegislash,
[SPECIES_SPRITZEE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Spritzee, 0),
      .enemyMonElevation = 0,
    }, //Spritzee,
[SPECIES_AROMATISSE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Aromatisse, 0),
      .enemyMonElevation = 0,
    }, //Aromatisse,
[SPECIES_SWIRLIX] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Swirlix, 1),
      .enemyMonElevation = 0,
    }, //Swirlix,
[SPECIES_SLURPUFF] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Slurpuff, 1),
      .enemyMonElevation = 0,
    }, //Slurpuff,
[SPECIES_INKAY] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x78, 9),
      PIC_DATA_ICON_INDEX(Inkay, 0),
      .enemyMonElevation = 0,
    }, //Inkay,
[SPECIES_MALAMAR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Malamar, 2),
      .enemyMonElevation = 0,
    }, //Malamar,
[SPECIES_BINACLE] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Binacle, 2),
      .enemyMonElevation = 0,
    }, //Binacle,
[SPECIES_BARBARACLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Barbaracle, 2),
      .enemyMonElevation = 0,
    }, //Barbaracle,
[SPECIES_SKRELP] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Skrelp, 2),
      .enemyMonElevation = 0,
    }, //Skrelp,
[SPECIES_DRAGALGE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Dragalge, 5),
      .enemyMonElevation = 0,
    }, //Dragalge,
[SPECIES_CLAUNCHER] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Clauncher, 0),
      .enemyMonElevation = 0,
    }, //Clauncher,
[SPECIES_CLAWITZER] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Clawitzer, 0),
      .enemyMonElevation = 0,
    }, //Clawitzer,
[SPECIES_HELIOPTILE] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Helioptile, 2),
      .enemyMonElevation = 0,
    }, //Helioptile,
[SPECIES_HELIOLISK] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Heliolisk, 2),
      .enemyMonElevation = 0,
    }, //Heliolisk,
[SPECIES_TYRUNT] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Tyrunt, 2),
      .enemyMonElevation = 0,
    }, //Tyrunt,
[SPECIES_TYRANTRUM] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Tyrantrum, 0),
      .enemyMonElevation = 0,
    }, //Tyrantrum,
[SPECIES_AMAURA] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x58, 3),
      PIC_DATA_ICON_INDEX(Amaura, 0),
      .enemyMonElevation = 0,
    }, //Amaura,
[SPECIES_AURORUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Aurorus, 0),
      .enemyMonElevation = 0,
    }, //Aurorus,
[SPECIES_SYLVEON] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Sylveon, 0),
      .enemyMonElevation = 0,
    }, //Sylveon,
[SPECIES_HAWLUCHA] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Hawlucha, 0),
      .enemyMonElevation = 0,
    }, //Hawlucha,
[SPECIES_DEDENNE] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Dedenne, 0),
      .enemyMonElevation = 0,
    }, //Dedenne,
[SPECIES_CARBINK] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Carbink, 2),
      .enemyMonElevation = 0,
    }, //Carbink,
[SPECIES_GOOMY] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Goomy, 5),
      .enemyMonElevation = 0,
    }, //Goomy,
[SPECIES_SLIGGOO] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Sliggoo, 5),
      .enemyMonElevation = 0,
    }, //Sliggoo,
[SPECIES_GOODRA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Goodra, 5),
      .enemyMonElevation = 0,
    }, //Goodra,
[SPECIES_KLEFKI] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x78, 8),
      PIC_DATA_ICON_INDEX(Klefki, 0),
      .enemyMonElevation = 0,
    }, //Klefki,
[SPECIES_PHANTUMP] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Phantump, 1),
      .enemyMonElevation = 0,
    }, //Phantump,
[SPECIES_TREVENANT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Trevenant, 1),
      .enemyMonElevation = 0,
    }, //Trevenant,
[SPECIES_PUMPKABOO_AVERAGE_SIZE] = 
    {  
      FRONT_PIC(PumpkabooAverageSize),
      FRONT_COORD(0x45, 13),
      BACK_PIC(PumpkabooAverageSize),
      BACK_COORD(0x76, 13),
      PALETTES(Pumpkaboo),
      ICON(Pumpkaboo, 2),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_GOURGEIST_AVERAGE_SIZE] = 
    {  
      FRONT_PIC(GourgeistAverageSize),
      FRONT_COORD(0x45, 4),
      BACK_PIC(GourgeistAverageSize),
      BACK_COORD(0x68, 3),
      PALETTES(Gourgeist),
      ICON(Gourgeist, 2),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_BERGMITE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x76, 13),
      PIC_DATA_ICON_INDEX(Bergmite, 0),
      .enemyMonElevation = 0,
    }, //Bergmite,
[SPECIES_AVALUGG] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Avalugg, 0),
      .enemyMonElevation = 0,
    }, //Avalugg,
[SPECIES_NOIBAT] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x78, 7),
      PIC_DATA_ICON_INDEX(Noibat, 2),
      .enemyMonElevation = 8,
    }, //Noibat,
[SPECIES_NOIVERN] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Noivern, 2),
      .enemyMonElevation = 0,
    }, //Noivern,
[SPECIES_XERNEAS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Xerneas, 0),
      .enemyMonElevation = 0,
    }, //Xerneas,
[SPECIES_YVELTAL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Yveltal, 0),
      .enemyMonElevation = 0,
    }, //Yveltal,
[SPECIES_ZYGARDE_10] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 9),
      PIC_DATA_ICON_INDEX(Zygarde10, 1),
      .enemyMonElevation = 0,
    }, //Zygarde,
[SPECIES_DIANCIE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Diancie, 1),
      .enemyMonElevation = 0,
    }, //Diancie,
[SPECIES_HOOPA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Hoopa, 0),
      .enemyMonElevation = 13,
    }, //Hoopa,
[SPECIES_VOLCANION] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Volcanion, 0),
      .enemyMonElevation = 0,
    }, //Volcanion,
[SPECIES_ROWLET] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 15),
      PIC_DATA_ICON_INDEX(Rowlet, 0),
      .enemyMonElevation = 0,
    }, //Rowlet,
[SPECIES_DARTRIX] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x77, 4),
      PIC_DATA_ICON_INDEX(Dartrix, 1),
      .enemyMonElevation = 0,
    }, //Dartrix,
[SPECIES_DECIDUEYE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Decidueye, 1),
      .enemyMonElevation = 0,
    }, //Decidueye,
[SPECIES_LITTEN] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Litten, 0),
      .enemyMonElevation = 0,
    }, //Litten,
[SPECIES_TORRACAT] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Torracat, 0),
      .enemyMonElevation = 0,
    }, //Torracat,
[SPECIES_INCINEROAR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Incineroar, 0),
      .enemyMonElevation = 0,
    }, //Incineroar,
[SPECIES_POPPLIO] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 11),
      PIC_DATA_ICON_INDEX(Popplio, 0),
      .enemyMonElevation = 0,
    }, //Popplio,
[SPECIES_BRIONNE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Brionne, 0),
      .enemyMonElevation = 0,
    }, //Brionne,
[SPECIES_PRIMARINA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Primarina, 0),
      .enemyMonElevation = 0,
    }, //Primarina,
[SPECIES_PIKIPEK] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(Pikipek, 2),
      .enemyMonElevation = 0,
    }, //Pikipek,
[SPECIES_TRUMBEAK] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Trumbeak, 0),
      .enemyMonElevation = 0,
    }, //Trumbeak,
[SPECIES_TOUCANNON] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Toucannon, 0),
      .enemyMonElevation = 0,
    }, //Toucannon,
[SPECIES_YUNGOOS] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 14),
      PIC_DATA_ICON_INDEX(Yungoos, 2),
      .enemyMonElevation = 0,
    }, //Yungoos,
[SPECIES_GUMSHOOS] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Gumshoos, 2),
      .enemyMonElevation = 0,
    }, //Gumshoos,
[SPECIES_GRUBBIN] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Grubbin, 0),
      .enemyMonElevation = 0,
    }, //Grubbin,
[SPECIES_CHARJABUG] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Charjabug, 1),
      .enemyMonElevation = 0,
    }, //Charjabug,
[SPECIES_VIKAVOLT] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Vikavolt, 0),
      .enemyMonElevation = 8,
    }, //Vikavolt,
[SPECIES_CRABRAWLER] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Crabrawler, 2),
      .enemyMonElevation = 0,
    }, //Crabrawler,
[SPECIES_CRABOMINABLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Crabominable, 2),
      .enemyMonElevation = 0,
    }, //Crabominable,
[SPECIES_ORICORIO_BAILE] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioBaile, 0),
      .enemyMonElevation = 0,
    }, //Oricorio_Baile,
[SPECIES_CUTIEFLY] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x76, 15),
      PIC_DATA_ICON_INDEX(Cutiefly, 2),
      .enemyMonElevation = 10,
    }, //Cutiefly,
[SPECIES_RIBOMBEE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Ribombee, 2),
      .enemyMonElevation = 0,
    }, //Ribombee,
[SPECIES_ROCKRUFF] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Rockruff, 2),
      .enemyMonElevation = 0,
    }, //Rockruff,
[SPECIES_LYCANROC_MIDDAY] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(LycanrocMidday, 2),
      .enemyMonElevation = 0,
    }, //Lycanroc,
[SPECIES_WISHIWASHI] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x74, 18),
      PIC_DATA_ICON_INDEX(Wishiwashi, 2),
      .enemyMonElevation = 0,
    }, //Wishiwashi,
[SPECIES_MAREANIE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x86, 15),
      PIC_DATA_ICON_INDEX(Mareanie, 2),
      .enemyMonElevation = 0,
    }, //Mareanie,
[SPECIES_TOXAPEX] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Toxapex, 0),
      .enemyMonElevation = 0,
    }, //Toxapex,
[SPECIES_MUDBRAY] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Mudbray, 2),
      .enemyMonElevation = 0,
    }, //Mudbray,
[SPECIES_MUDSDALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Mudsdale, 0),
      .enemyMonElevation = 0,
    }, //Mudsdale,
[SPECIES_DEWPIDER] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x56, 8),
      PIC_DATA_ICON_INDEX(Dewpider, 0),
      .enemyMonElevation = 0,
    }, //Dewpider,
[SPECIES_ARAQUANID] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Araquanid, 2),
      .enemyMonElevation = 0,
    }, //Araquanid,
[SPECIES_FOMANTIS] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x57, 5),
      PIC_DATA_ICON_INDEX(Fomantis, 1),
      .enemyMonElevation = 0,
    }, //Fomantis,
[SPECIES_LURANTIS] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x78, 1),
      PIC_DATA_ICON_INDEX(Lurantis, 1),
      .enemyMonElevation = 0,
    }, //Lurantis,
[SPECIES_MORELULL] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x56, 9),
      PIC_DATA_ICON_INDEX(Morelull, 0),
      .enemyMonElevation = 0,
    }, //Morelull,
[SPECIES_SHIINOTIC] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Shiinotic, 1),
      .enemyMonElevation = 0,
    }, //Shiinotic,
[SPECIES_SALANDIT] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Salandit, 2),
      .enemyMonElevation = 0,
    }, //Salandit,
[SPECIES_SALAZZLE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x68, 3),
      PIC_DATA_ICON_INDEX(Salazzle, 0),
      .enemyMonElevation = 0,
    }, //Salazzle,
[SPECIES_STUFFUL] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Stufful, 0),
      .enemyMonElevation = 0,
    }, //Stufful,
[SPECIES_BEWEAR] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Bewear, 0),
      .enemyMonElevation = 0,
    }, //Bewear,
[SPECIES_BOUNSWEET] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x65, 14),
      PIC_DATA_ICON_INDEX(Bounsweet, 1),
      .enemyMonElevation = 0,
    }, //Bounsweet,
[SPECIES_STEENEE] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(Steenee, 1),
      .enemyMonElevation = 0,
    }, //Steenee,
[SPECIES_TSAREENA] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Tsareena, 1),
      .enemyMonElevation = 0,
    }, //Tsareena,
[SPECIES_COMFEY] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Comfey, 1),
      .enemyMonElevation = 0,
    }, //Comfey,
[SPECIES_ORANGURU] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Oranguru, 0),
      .enemyMonElevation = 0,
    }, //Oranguru,
[SPECIES_PASSIMIAN] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Passimian, 1),
      .enemyMonElevation = 0,
    }, //Passimian,
[SPECIES_WIMPOD] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Wimpod, 2),
      .enemyMonElevation = 0,
    }, //Wimpod,
[SPECIES_GOLISOPOD] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Golisopod, 2),
      .enemyMonElevation = 0,
    }, //Golisopod,
[SPECIES_SANDYGAST] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x56, 11),
      PIC_DATA_ICON_INDEX(Sandygast, 1),
      .enemyMonElevation = 0,
    }, //Sandygast,
[SPECIES_PALOSSAND] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Palossand, 2),
      .enemyMonElevation = 0,
    }, //Palossand,
[SPECIES_PYUKUMUKU] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x64, 16),
      PIC_DATA_ICON_INDEX(Pyukumuku, 0),
      .enemyMonElevation = 0,
    }, //Pyukumuku,
[SPECIES_TYPE_NULL] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x78, 1),
      PIC_DATA_ICON_INDEX(TypeNull, 0),
      .enemyMonElevation = 0,
    }, //TypeNull,
[SPECIES_SILVALLY] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_MINIOR] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 17,
    }, //Minior,
[SPECIES_KOMALA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Komala, 2),
      .enemyMonElevation = 0,
    }, //Komala,
[SPECIES_TURTONATOR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Turtonator, 0),
      .enemyMonElevation = 0,
    }, //Turtonator,
[SPECIES_TOGEDEMARU] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x86, 13),
      PIC_DATA_ICON_INDEX(Togedemaru, 2),
      .enemyMonElevation = 0,
    }, //Togedemaru,
[SPECIES_MIMIKYU] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Mimikyu, 3),
      .enemyMonElevation = 0,
    }, //Mimikyu,
[SPECIES_BRUXISH] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 14),
      PIC_DATA_ICON_INDEX(Bruxish, 0),
      .enemyMonElevation = 0,
    }, //Bruxish,
[SPECIES_DRAMPA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Drampa, 0),
      .enemyMonElevation = 0,
    }, //Drampa,
[SPECIES_DHELMISE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Dhelmise, 1),
      .enemyMonElevation = 0,
    }, //Dhelmise,
[SPECIES_JANGMO_O] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(JangmoO, 2),
      .enemyMonElevation = 0,
    }, //Jangmoo,
[SPECIES_HAKAMO_O] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(HakamoO, 2),
      .enemyMonElevation = 0,
    }, //Hakamoo,
[SPECIES_KOMMO_O] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(KommoO, 2),
      .enemyMonElevation = 0,
    }, //Kommoo,
[SPECIES_TAPU_KOKO] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(TapuKoko, 0),
      .enemyMonElevation = 0,
    }, //TapuKoko,
[SPECIES_TAPU_LELE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(TapuLele, 0),
      .enemyMonElevation = 0,
    }, //TapuLele,
[SPECIES_TAPU_BULU] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(TapuBulu, 2),
      .enemyMonElevation = 0,
    }, //TapuBulu,
[SPECIES_TAPU_FINI] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(TapuFini, 0),
      .enemyMonElevation = 0,
    }, //TapuFini,
[SPECIES_COSMOG] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Cosmog, 2),
      .enemyMonElevation = 0,
    }, //Cosmog,
[SPECIES_COSMOEM] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x85, 17),
      PIC_DATA_ICON_INDEX(Cosmoem, 0),
      .enemyMonElevation = 0,
    }, //Cosmoem,
[SPECIES_SOLGALEO] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Solgaleo, 0),
      .enemyMonElevation = 0,
    }, //Solgaleo,
[SPECIES_LUNALA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Lunala, 2),
      .enemyMonElevation = 0,
    }, //Lunala,
[SPECIES_NIHILEGO] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Nihilego, 0),
      .enemyMonElevation = 0,
    }, //Nihilego,
[SPECIES_BUZZWOLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 14),
      PIC_DATA_ICON_INDEX(Buzzwole, 0),
      .enemyMonElevation = 0,
    }, //Buzzwole,
[SPECIES_PHEROMOSA] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Pheromosa, 2),
      .enemyMonElevation = 0,
    }, //Pheromosa,
[SPECIES_XURKITREE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Xurkitree, 0),
      .enemyMonElevation = 0,
    }, //Xurkitree,
[SPECIES_CELESTEELA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Celesteela, 0),
      .enemyMonElevation = 0,
    }, //Celesteela,
[SPECIES_KARTANA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Kartana, 0),
      .enemyMonElevation = 0,
    }, //Kartana,
[SPECIES_GUZZLORD] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Guzzlord, 0),
      .enemyMonElevation = 0,
    }, //Guzzlord,
[SPECIES_NECROZMA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Necrozma, 0),
      .enemyMonElevation = 0,
    }, //Necrozma,
[SPECIES_MAGEARNA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Magearna, 0),
      .enemyMonElevation = 0,
    }, //Magearna,
[SPECIES_MARSHADOW] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x57, 6),
      PIC_DATA_ICON_INDEX(Marshadow, 0),
      .enemyMonElevation = 0,
    }, //Marshadow,
[SPECIES_POIPOLE] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x67, 6),
      PIC_DATA_ICON_INDEX(Poipole, 0),
      .enemyMonElevation = 0,
    }, //Poipole,
[SPECIES_NAGANADEL] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Naganadel, 0),
      .enemyMonElevation = 0,
    }, //Naganadel,
[SPECIES_STAKATAKA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Stakataka, 0),
      .enemyMonElevation = 0,
    }, //Stakataka,
[SPECIES_BLACEPHALON] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Blacephalon, 0),
      .enemyMonElevation = 0,
    }, //Blacephalon,
[SPECIES_ZERAORA] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Zeraora, 0),
      .enemyMonElevation = 0,
    }, //Zeraora,
[SPECIES_MELTAN] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x55, 12),
      PIC_DATA_ICON_INDEX(Meltan, 2),
      .enemyMonElevation = 0,
    }, //Meltan,
[SPECIES_MELMETAL] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Melmetal, 2),
      .enemyMonElevation = 0,
    }, //Melmetal,
[SPECIES_GROOKEY] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Grookey, 1),
      .enemyMonElevation = 0,
    }, //Grookey,
[SPECIES_THWACKEY] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Thwackey, 1),
      .enemyMonElevation = 0,
    }, //Thwackey,
[SPECIES_RILLABOOM] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Rillaboom, 1),
      .enemyMonElevation = 0,
    }, //Rillaboom,
[SPECIES_SCORBUNNY] = 
    {  
      FRONT_COORD(0x57, 8),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Scorbunny, 1),
      .enemyMonElevation = 0,
    }, //Scorbunny,
[SPECIES_RABOOT] = 
    {  
      FRONT_COORD(0x57, 7),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Raboot, 2),
      .enemyMonElevation = 0,
    }, //Raboot,
[SPECIES_CINDERACE] = 
    {  
      FRONT_COORD(0x58, 0),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Cinderace, 0),
      .enemyMonElevation = 0,
    }, //Cinderace,
[SPECIES_SOBBLE] = 
    {  
      FRONT_COORD(0x57, 11),
      BACK_COORD(0x57, 8),
      PIC_DATA_ICON_INDEX(Sobble, 2),
      .enemyMonElevation = 0,
    }, //Sobble,
[SPECIES_DRIZZILE] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Drizzile, 2),
      .enemyMonElevation = 0,
    }, //Drizzile,
[SPECIES_INTELEON] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Inteleon, 0),
      .enemyMonElevation = 0,
    }, //Inteleon,
[SPECIES_SKWOVET] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Skwovet, 2),
      .enemyMonElevation = 0,
    }, //Skwovet,
[SPECIES_GREEDENT] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Greedent, 2),
      .enemyMonElevation = 0,
    }, //Greedent,
[SPECIES_ROOKIDEE] = 
    {  
      FRONT_COORD(0x55, 16),
      BACK_COORD(0x84, 17),
      PIC_DATA_ICON_INDEX(Rookidee, 0),
      .enemyMonElevation = 0,
    }, //Rookidee,
[SPECIES_CORVISQUIRE] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Corvisquire, 0),
      .enemyMonElevation = 6,
    }, //Corvisquire,
[SPECIES_CORVIKNIGHT] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Corviknight, 0),
      .enemyMonElevation = 0,
    }, //Corviknight,
[SPECIES_BLIPBUG] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x57, 7),
      PIC_DATA_ICON_INDEX(Blipbug, 0),
      .enemyMonElevation = 0,
    }, //Blipbug,
[SPECIES_DOTTLER] = 
    {  
      FRONT_COORD(0x65, 13),
      BACK_COORD(0x74, 17),
      PIC_DATA_ICON_INDEX(Dottler, 2),
      .enemyMonElevation = 0,
    }, //Dottler,
[SPECIES_ORBEETLE] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Orbeetle, 0),
      .enemyMonElevation = 0,
    }, //Orbeetle,
[SPECIES_NICKIT] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Nickit, 0),
      .enemyMonElevation = 0,
    }, //Nickit,
[SPECIES_THIEVUL] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Thievul, 0),
      .enemyMonElevation = 0,
    }, //Thievul,
[SPECIES_GOSSIFLEUR] = 
    {  
      FRONT_COORD(0x67, 11),
      BACK_COORD(0x76, 15),
      PIC_DATA_ICON_INDEX(Gossifleur, 0),
      .enemyMonElevation = 0,
    }, //Gossifleur,
[SPECIES_ELDEGOSS] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Eldegoss, 1),
      .enemyMonElevation = 0,
    }, //Eldegoss,
[SPECIES_WOOLOO] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x74, 18),
      PIC_DATA_ICON_INDEX(Wooloo, 0),
      .enemyMonElevation = 0,
    }, //Wooloo,
[SPECIES_DUBWOOL] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Dubwool, 0),
      .enemyMonElevation = 0,
    }, //Dubwool,
[SPECIES_CHEWTLE] = 
    {  
      FRONT_COORD(0x46, 13),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(Chewtle, 0),
      .enemyMonElevation = 0,
    }, //Chewtle,
[SPECIES_DREDNAW] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x85, 18),
      PIC_DATA_ICON_INDEX(Drednaw, 0),
      .enemyMonElevation = 0,
    }, //Drednaw,
[SPECIES_YAMPER] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(Yamper, 1),
      .enemyMonElevation = 0,
    }, //Yamper,
[SPECIES_BOLTUND] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Boltund, 1),
      .enemyMonElevation = 0,
    }, //Boltund,
[SPECIES_ROLYCOLY] = 
    {  
      FRONT_COORD(0x55, 16),
      BACK_COORD(0x84, 17),
      PIC_DATA_ICON_INDEX(Rolycoly, 0),
      .enemyMonElevation = 0,
    }, //Rolycoly,
[SPECIES_CARKOL] = 
    {  
      FRONT_COORD(0x67, 8),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Carkol, 0),
      .enemyMonElevation = 0,
    }, //Carkol,
[SPECIES_COALOSSAL] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Coalossal, 0),
      .enemyMonElevation = 0,
    }, //Coalossal,
[SPECIES_APPLIN] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x56, 15),
      PIC_DATA_ICON_INDEX(Applin, 1),
      .enemyMonElevation = 0,
    }, //Applin,
[SPECIES_FLAPPLE] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Flapple, 1),
      .enemyMonElevation = 0,
    }, //Flapple,
[SPECIES_APPLETUN] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Appletun, 1),
      .enemyMonElevation = 0,
    }, //Appletun,
[SPECIES_SILICOBRA] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x76, 10),
      PIC_DATA_ICON_INDEX(Silicobra, 1),
      .enemyMonElevation = 0,
    }, //Silicobra,
[SPECIES_SANDACONDA] = 
    {  
      FRONT_COORD(0x85, 12),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Sandaconda, 1),
      .enemyMonElevation = 0,
    }, //Sandaconda,
[SPECIES_CRAMORANT] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 1),
      PIC_DATA_ICON_INDEX(Cramorant, 0),
      .enemyMonElevation = 0,
    }, //Cramorant,
[SPECIES_ARROKUDA] = 
    {  
      FRONT_COORD(0x74, 17),
      BACK_COORD(0x65, 15),
      PIC_DATA_ICON_INDEX(Arrokuda, 2),
      .enemyMonElevation = 0,
    }, //Arrokuda,
[SPECIES_BARRASKEWDA] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Barraskewda, 2),
      .enemyMonElevation = 0,
    }, //Barraskewda,
[SPECIES_TOXEL] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Toxel, 2),
      .enemyMonElevation = 0,
    }, //Toxel,
[SPECIES_TOXTRICITY] = 
    {  
      FRONT_COORD(0x68, 1),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Toxtricity, 2),
      .enemyMonElevation = 0,
    }, //Toxtricity,
[SPECIES_SIZZLIPEDE] = 
    {  
      FRONT_COORD(0x64, 17),
      BACK_COORD(0x54, 16),
      PIC_DATA_ICON_INDEX(Sizzlipede, 0),
      .enemyMonElevation = 0,
    }, //Sizzlipede,
[SPECIES_CENTISKORCH] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Centiskorch, 0),
      .enemyMonElevation = 0,
    }, //Centiskorch,
[SPECIES_CLOBBOPUS] = 
    {  
      FRONT_COORD(0x65, 15),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Clobbopus, 0),
      .enemyMonElevation = 0,
    }, //Clobbopus,
[SPECIES_GRAPPLOCT] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Grapploct, 2),
      .enemyMonElevation = 0,
    }, //Grapploct,
[SPECIES_SINISTEA] = 
    {  
      FRONT_COORD(0x54, 17),
      BACK_COORD(0x64, 16),
      PIC_DATA_ICON_INDEX(Sinistea, 2),
      .enemyMonElevation = 0,
    }, //Sinistea,
[SPECIES_POLTEAGEIST] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Polteageist, 2),
      .enemyMonElevation = 0,
    }, //Polteageist,
[SPECIES_HATENNA] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x55, 12),
      PIC_DATA_ICON_INDEX(Hatenna, 0),
      .enemyMonElevation = 0,
    }, //Hatenna,
[SPECIES_HATTREM] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Hattrem, 0),
      .enemyMonElevation = 0,
    }, //Hattrem,
[SPECIES_HATTERENE] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Hatterene, 0),
      .enemyMonElevation = 0,
    }, //Hatterene,
[SPECIES_IMPIDIMP] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Impidimp, 0),
      .enemyMonElevation = 0,
    }, //Impidimp,
[SPECIES_MORGREM] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Morgrem, 0),
      .enemyMonElevation = 0,
    }, //Morgrem,
[SPECIES_GRIMMSNARL] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Grimmsnarl, 0),
      .enemyMonElevation = 0,
    }, //Grimmsnarl,
[SPECIES_OBSTAGOON] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Obstagoon, 0),
      .enemyMonElevation = 0,
    }, //Obstagoon,
[SPECIES_PERRSERKER] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Perrserker, 2),
      .enemyMonElevation = 0,
    }, //Perrserker,
[SPECIES_CURSOLA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Cursola, 0),
      .enemyMonElevation = 0,
    }, //Cursola,
[SPECIES_SIRFETCHD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Sirfetchd, 1),
      .enemyMonElevation = 0,
    }, //Sirfetchd,
[SPECIES_MR_RIME] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(MrRime, 0),
      .enemyMonElevation = 0,
    }, //MrRime,
[SPECIES_RUNERIGUS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Runerigus, 0),
      .enemyMonElevation = 0,
    }, //Runerigus,
[SPECIES_MILCERY] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x76, 16),
      PIC_DATA_ICON_INDEX(Milcery, 1),
      .enemyMonElevation = 0,
    }, //Milcery,
[SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryVanillaCream),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,
[SPECIES_FALINKS] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Falinks, 0),
      .enemyMonElevation = 0,
    }, //Falinks,
[SPECIES_PINCURCHIN] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x75, 13),
      PIC_DATA_ICON_INDEX(Pincurchin, 0),
      .enemyMonElevation = 0,
    }, //Pincurchin,
[SPECIES_SNOM] = 
    {  
      FRONT_COORD(0x54, 20),
      BACK_COORD(0x64, 17),
      PIC_DATA_ICON_INDEX(Snom, 0),
      .enemyMonElevation = 0,
    }, //Snom,
[SPECIES_FROSMOTH] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Frosmoth, 0),
      .enemyMonElevation = 3,
    }, //Frosmoth,
[SPECIES_STONJOURNER] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Stonjourner, 2),
      .enemyMonElevation = 0,
    }, //Stonjourner,
[SPECIES_EISCUE] = 
    {  
      FRONT_COORD(0x58, 0),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Eiscue, 0),
      .enemyMonElevation = 0,
    }, //Eiscue,
[SPECIES_INDEEDEE_MALE] = 
    {  
      FRONT_COORD(0x57, 9),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(IndeedeeMale, 2),
      .enemyMonElevation = 0,
    }, //Indeedee,
[SPECIES_MORPEKO] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Morpeko, 2),
      .enemyMonElevation = 0,
    }, //Morpeko,
[SPECIES_CUFANT] = 
    {  
      FRONT_COORD(0x76, 11),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Cufant, 0),
      .enemyMonElevation = 0,
    }, //Cufant,
[SPECIES_COPPERAJAH] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Copperajah, 0),
      .enemyMonElevation = 0,
    }, //Copperajah,
[SPECIES_DRACOZOLT] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Dracozolt, 0),
      .enemyMonElevation = 0,
    }, //Dracozolt,
[SPECIES_ARCTOZOLT] = 
    {  
      FRONT_COORD(0x78, 1),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Arctozolt, 0),
      .enemyMonElevation = 0,
    }, //Arctozolt,
[SPECIES_DRACOVISH] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Dracovish, 0),
      .enemyMonElevation = 0,
    }, //Dracovish,
[SPECIES_ARCTOVISH] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Arctovish, 2),
      .enemyMonElevation = 0,
    }, //Arctovish,
[SPECIES_DURALUDON] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Duraludon, 0),
      .enemyMonElevation = 0,
    }, //Duraludon,
[SPECIES_DREEPY] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x75, 15),
      PIC_DATA_ICON_INDEX(Dreepy, 0),
      .enemyMonElevation = 0,
    }, //Dreepy,
[SPECIES_DRAKLOAK] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Drakloak, 0),
      .enemyMonElevation = 0,
    }, //Drakloak,
[SPECIES_DRAGAPULT] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Dragapult, 0),
      .enemyMonElevation = 3,
    }, //Dragapult,
[SPECIES_ZACIAN] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Zacian, 2),
      .enemyMonElevation = 0,
    }, //Zacian,
[SPECIES_ZAMAZENTA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Zamazenta, 2),
      .enemyMonElevation = 0,
    }, //Zamazenta,
[SPECIES_ETERNATUS] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Eternatus, 0),
      .enemyMonElevation = 0,
    }, //Eternatus,
[SPECIES_KUBFU] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Kubfu, 0),
      .enemyMonElevation = 0,
    }, //Kubfu,
[SPECIES_URSHIFU_SINGLE_STRIKE_STYLE] = 
    {  
      FRONT_PIC(UrshifuSingleStrikeStyle),
      FRONT_COORD(0x78, 0),
      BACK_PIC(UrshifuSingleStrikeStyle),
      BACK_COORD(0x87, 4),
      PALETTES(UrshifuSingleStrikeStyle),
      ICON(Urshifu, 2),
      .enemyMonElevation = 0,
    }, //Urshifu,
[SPECIES_ZARUDE] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Zarude, 5),
      .enemyMonElevation = 0,
    }, //Zarude,
[SPECIES_REGIELEKI] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 11),
      PIC_DATA_ICON_INDEX(Regieleki, 0),
      .enemyMonElevation = 0,
    }, //Regieleki,
[SPECIES_REGIDRAGO] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Regidrago, 0),
      .enemyMonElevation = 0,
    }, //Regidrago,
[SPECIES_GLASTRIER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Glastrier, 0),
      .enemyMonElevation = 0,
    }, //Glastrier,
[SPECIES_SPECTRIER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Spectrier, 0),
      .enemyMonElevation = 0,
    }, //Spectrier,
[SPECIES_CALYREX] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x76, 10),
      PIC_DATA_ICON_INDEX(Calyrex, 0),
      .enemyMonElevation = 0,
    }, //Calyrex,
[SPECIES_WYRDEER] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Wyrdeer, 1),
      .enemyMonElevation = 0,
    }, //Wyrdeer,
[SPECIES_KLEAVOR] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Kleavor, 2),
      .enemyMonElevation = 0,
    }, //Kleavor,
[SPECIES_URSALUNA] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 14),
      PIC_DATA_ICON_INDEX(Ursaluna, 2),
      .enemyMonElevation = 0,
    }, //Ursaluna,
[SPECIES_BASCULEGION_MALE] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x72, 1),
      PIC_DATA_ICON_INDEX(BasculegionMale, 4),
      .enemyMonElevation = 0,
    }, //Basculegion,
[SPECIES_SNEASLER] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x76, 1),
      PIC_DATA_ICON_INDEX(Sneasler, 2),
      .enemyMonElevation = 0,
    }, //Sneasler,
[SPECIES_OVERQWIL] = 
    {  
      FRONT_COORD(0x62, 5),
      BACK_COORD(0x62, 12),
      PIC_DATA_ICON_INDEX(Overqwil, 2),
      .enemyMonElevation = 0,
    }, //Overqwil,
[SPECIES_ENAMORUS] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x68, 1),
      PIC_DATA_ICON_INDEX(Enamorus, 1),
      .enemyMonElevation = 0,
    }, //Enamorus,
    [SPECIES_CEFIREON] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,0),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      .enemyMonElevation = 0,
    }, //Enamorus,
    [SPECIES_FRAEYJTA] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,0),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      .enemyMonElevation = 0,
    }, //Enamorus,
[SPECIES_SPRIGATITO] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Sprigatito, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_FLORAGATO] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Floragato, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_MEOWSCARADA] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Meowscarada, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_FUECOCO] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Fuecoco, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_CROCALOR] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Crocalor, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_SKELEDIRGE] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Skeledirge, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_QUAXLY] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Quaxly, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_QUAXWELL] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Quaxwell, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_QUAQUAVAL] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Quaquaval, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_LECHONK] =
    {
      FRONT_COORD(0x88, 12),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Lechonk, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_OINKOLOGNE_MALE] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(OinkologneMale, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_OINKOLOGNE_FEMALE] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(OinkologneFemale, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TAROUNTULA] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Tarountula, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_SPIDOPS] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Spidops, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_NYMBLE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Nymble, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_LOKIX] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Lokix, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_PAWMI] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Pawmi, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_PAWMO] =
    {
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Pawmo, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_PAWMOT] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Pawmot, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TANDEMAUS] =
    {
      FRONT_COORD(0x88, 15),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(Tandemaus, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_MAUSHOLD_FAMILY_OF_THREE] =
    {
      FRONT_PIC(MausholdFamilyOfThree),
      FRONT_COORD(0x88, 15),
      BACK_PIC(MausholdFamilyOfThree),
      BACK_COORD(0x88, 15),
      ICON(MausholdFamilyOfThree, 0),
      PALETTES(Maushold),
      .enemyMonElevation = 0,
    },
[SPECIES_MAUSHOLD_FAMILY_OF_FOUR] =
    {
      FRONT_PIC(MausholdFamilyOfFour),
      FRONT_COORD(0x88, 15),
      BACK_PIC(MausholdFamilyOfFour),
      BACK_COORD(0x88, 15),
      ICON(MausholdFamilyOfFour, 0),
      PALETTES(Maushold),
      .enemyMonElevation = 0,
    },

[SPECIES_FIDOUGH] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(Fidough, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_DACHSBUN] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Dachsbun, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_SMOLIV] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Smoliv, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_DOLLIV] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Dolliv, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_ARBOLIVA] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Arboliva, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_SQUAWKABILLY_GREEN_PLUMAGE] =
    {
      FRONT_PIC(Squawkabilly),
      FRONT_COORD(0x88, 4),
      BACK_PIC(Squawkabilly),
      BACK_COORD(0x88, 4),
      ICON(SquawkabillyGreenPlumage, 1),
      PALETTES(SquawkabillyGreenPlumage),
      .enemyMonElevation = 0,
    },

[SPECIES_SQUAWKABILLY_BLUE_PLUMAGE] =
    {
      FRONT_PIC(Squawkabilly),
      FRONT_COORD(0x88, 4),
      BACK_PIC(Squawkabilly),
      BACK_COORD(0x88, 4),
      ICON(SquawkabillyBluePlumage, 0),
      PALETTES(SquawkabillyBluePlumage),
      .enemyMonElevation = 0,
    },

[SPECIES_SQUAWKABILLY_YELLOW_PLUMAGE] =
    {
      FRONT_PIC(Squawkabilly),
      FRONT_COORD(0x88, 4),
      BACK_PIC(Squawkabilly),
      BACK_COORD(0x88, 4),
      ICON(SquawkabillyYellowPlumage, 1),
      PALETTES(SquawkabillyYellowPlumage),
      .enemyMonElevation = 0,
    },

[SPECIES_SQUAWKABILLY_WHITE_PLUMAGE] =
    {
      FRONT_PIC(Squawkabilly),
      FRONT_COORD(0x88, 4),
      BACK_PIC(Squawkabilly),
      BACK_COORD(0x88, 4),
      ICON(SquawkabillyWhitePlumage, 0),
      PALETTES(SquawkabillyWhitePlumage),
      .enemyMonElevation = 0,
    },

[SPECIES_NACLI] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Nacli, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_NACLSTACK] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Naclstack, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_GARGANACL] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Garganacl, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_CHARCADET] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Charcadet, 5),
      .enemyMonElevation = 0,
    },//vsonic

[SPECIES_ARMAROUGE] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Armarouge, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_CERULEDGE] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Ceruledge, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_TADBULB] =
    {
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Tadbulb, 0),
      .enemyMonElevation = 12,
    },

[SPECIES_BELLIBOLT] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Bellibolt, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_WATTREL] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Wattrel, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_KILOWATTREL] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Kilowattrel, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_MASCHIFF] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Maschiff, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_MABOSSTIFF] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Mabosstiff, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_SHROODLE] =
    {
      FRONT_COORD(0x88, 17),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(Shroodle, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_GRAFAIAI] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(Grafaiai, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_BRAMBLIN] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Bramblin, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_BRAMBLEGHAST] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Brambleghast, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_TOEDSCOOL] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Toedscool, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TOEDSCRUEL] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Toedscruel, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_KLAWF] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 20),
      PIC_DATA_ICON_INDEX(Klawf, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_CAPSAKID] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(Capsakid, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_SCOVILLAIN] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Scovillain, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_RELLOR] =
    {
      FRONT_COORD(0x88, 17),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Rellor, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_RABSCA] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Rabsca, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_FLITTLE] =
    {
      FRONT_COORD(0x88, 12),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Flittle, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_ESPATHRA] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Espathra, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TINKATINK] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Tinkatink, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_TINKATUFF] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Tinkatuff, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_TINKATON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Tinkaton, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_WIGLETT] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Wiglett, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_WUGTRIO] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Wugtrio, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_BOMBIRDIER] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Bombirdier, 0),
      .enemyMonElevation = 8,
    },

[SPECIES_FINIZEN] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(Finizen, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_PALAFIN_ZERO] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(PalafinZero, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_PALAFIN_HERO] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(PalafinHero, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_VAROOM] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Varoom, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_REVAVROOM] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(Revavroom, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_CYCLIZAR] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Cyclizar, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_ORTHWORM] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Orthworm, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_GLIMMET] =
    {
      FRONT_COORD(0x88, 16),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Glimmet, 0),
      .enemyMonElevation = 11,
    },

[SPECIES_GLIMMORA] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Glimmora, 0),
      .enemyMonElevation = 8,
    },

[SPECIES_GREAVARD] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Greavard, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_HOUNDSTONE] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Houndstone, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_FLAMIGO] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Flamigo, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_CETODDLE] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(Cetoddle, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_CETITAN] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Cetitan, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_VELUZA] =
    {
      FRONT_COORD(0x88, 11),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Veluza, 1),
      .enemyMonElevation = 5,
    },

[SPECIES_DONDOZO] =
    {
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Dondozo, 0),
      .enemyMonElevation = 1,
    },

[SPECIES_TATSUGIRI_CURLY] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(TatsugiriCurly, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TATSUGIRI_DROOPY] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(TatsugiriDroopy, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TATSUGIRI_STRETCHY] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(TatsugiriStretchy, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_ANNIHILAPE] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Annihilape, 0),
      .enemyMonElevation = 0,
    },
    

[SPECIES_CLODSIRE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(Clodsire, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_FARIGIRAF] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Farigiraf, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_DUDUNSPARCE_TWO_SEGMENT] =
    {
      FRONT_PIC(DudunsparceTwoSegment),
      FRONT_COORD(0x88, 10),
      BACK_PIC(DudunsparceTwoSegment),
      BACK_COORD(0x88, 11),
      ICON(Dudunsparce, 0),
      PALETTES(Dudunsparce),
      .enemyMonElevation = 0,
    },

[SPECIES_DUDUNSPARCE_THREE_SEGMENT] =
    {
      FRONT_PIC(DudunsparceThreeSegment),
      FRONT_COORD(0x88, 10),
      BACK_PIC(DudunsparceThreeSegment),
      BACK_COORD(0x88, 11),
      ICON(Dudunsparce, 0),
      PALETTES(Dudunsparce),
      .enemyMonElevation = 0,
    },

[SPECIES_KINGAMBIT] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Kingambit, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_GREAT_TUSK] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(GreatTusk, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_SCREAM_TAIL] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(ScreamTail, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_BRUTE_BONNET] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(BruteBonnet, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_FLUTTER_MANE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(FlutterMane, 2),
      .enemyMonElevation = 18,
    },

[SPECIES_SLITHER_WING] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(SlitherWing, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_SANDY_SHOCKS] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(SandyShocks, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_TREADS] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(IronTreads, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_BUNDLE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(IronBundle, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_HANDS] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(IronHands, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_JUGULIS] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11), //back sprite not great
      PIC_DATA_ICON_INDEX(IronJugulis, 0),
      .enemyMonElevation = 7,
    },//vsonic

[SPECIES_IRON_MOTH] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(IronMoth, 3),
      .enemyMonElevation = 8,
    },

[SPECIES_IRON_THORNS] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(IronThorns,1),
      .enemyMonElevation = 0,
    },

[SPECIES_FRIGIBAX] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Frigibax, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_ARCTIBAX] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Arctibax, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_BAXCALIBUR] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Baxcalibur, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_GIMMIGHOUL_CHEST] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(GimmighoulChest, 0),
      .enemyMonElevation = 0,
    },//will make money based evolution I guess 70k poke, kinda griny but make gimmighoul better to use pre evo
    //and counter is you can evolve it at any level - brought down because u16 param

[SPECIES_GIMMIGHOUL_ROAMING] =
    {
      FRONT_COORD(0x88, 11),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(GimmighoulRoaming, 0),
      .enemyMonElevation = 0,
    }, //not gonna use this form

[SPECIES_GHOLDENGO] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Gholdengo, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_WO_CHIEN] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(WoChien, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_CHIEN_PAO] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(ChienPao, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TING_LU] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(TingLu, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_CHI_YU] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(ChiYu, 0),
      .enemyMonElevation = 15,
    },

[SPECIES_ROARING_MOON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(RoaringMoon, 0),
      .enemyMonElevation = 6,
    },

[SPECIES_IRON_VALIANT] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(IronValiant, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_KORAIDON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Koraidon, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_MIRAIDON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Miraidon, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_TAUROS_PALDEAN_COMBAT_BREED] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(TaurosPaldeanCombatBreed, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TAUROS_PALDEAN_BLAZE_BREED] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(TaurosPaldeanBlazeBreed, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TAUROS_PALDEAN_AQUA_BREED] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(TaurosPaldeanAquaBreed, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_WOOPER_PALDEAN] =
    {
      FRONT_COORD(0x88, 16),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(WooperPaldean, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_WALKING_WAKE] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(WalkingWake, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_LEAVES] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(IronLeaves, 1),
      .enemyMonElevation = 0,
    },
[SPECIES_DIPPLIN] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Dipplin, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_POLTCHAGEIST_COUNTERFEIT] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Poltchageist, 1),
      .enemyMonElevation = 10,
    },//vsonic

[SPECIES_POLTCHAGEIST_ARTISAN] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Poltchageist, 1),
      .enemyMonElevation = 10,
    },//vsonic

[SPECIES_SINISTCHA_UNREMARKABLE] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 13), //sprites came out bad? especially back
      PIC_DATA_ICON_INDEX(Sinistcha, 1), //low res
      .enemyMonElevation = 10,
    },
[SPECIES_SINISTCHA_MASTERPIECE] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Sinistcha, 1),
      .enemyMonElevation = 10,
    },

[SPECIES_OKIDOGI] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 13), //back looks better w/o tail, check model may remove
      PIC_DATA_ICON_INDEX(Okidogi, 1),
      .enemyMonElevation = 0,
    },

[SPECIES_MUNKIDORI] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 3), //maybe 2?
      PIC_DATA_ICON_INDEX(Munkidori, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_FEZANDIPITI] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Fezandipiti, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_OGERPON_TEAL_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponTealMask, 1),
      .enemyMonElevation = 0,
    },
[SPECIES_OGERPON_WELLSPRING_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponWellspringMask, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_OGERPON_HEARTHFLAME_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponHearthflameMask, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_OGERPON_CORNERSTONE_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponCornerstoneMask, 0),
      .enemyMonElevation = 0,
    },//need grahpics for tera forms
[SPECIES_URSALUNA_BLOODMOON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(UrsalunaBloodmoon, 2), //icon is off, think source is problem
      .enemyMonElevation = 0,
    },//vsonic

[SPECIES_ARCHALUDON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Archaludon, 0),
      .enemyMonElevation = 0,
    },

//missing archaludon and hydrapple flapple evo
[SPECIES_HYDRAPPLE] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Hydrapple, 5),
      .enemyMonElevation = 0,
    },



[SPECIES_GOUGING_FIRE] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(GougingFire, 5),
      .enemyMonElevation = 0,
    },

[SPECIES_RAGING_BOLT] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(RagingBolt, 2),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_BOULDER] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(IronBoulder, 5),
      .enemyMonElevation = 0,
    },

[SPECIES_IRON_CROWN] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(IronCrown, 3),
      .enemyMonElevation = 0,
    },

[SPECIES_TERAPAGOS_NORMAL] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Terapagos, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TERAPAGOS_TERASTAL] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(TerapagosTerastal, 0),
      .enemyMonElevation = 0,
    },

[SPECIES_TERAPAGOS_STELLAR] =
    {
      FRONT_PIC(TerapagosTerastal), //dosen't exist yet replace later
      FRONT_COORD(0x88, 0),
      BACK_PIC(TerapagosTerastal),
      BACK_COORD(0x88, 0),
      ICON(TerapagosStellar, 0),
      PALETTES(TerapagosTerastal),
      .enemyMonElevation = 0,
    },

[SPECIES_PECHARUNT] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Pecharunt, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_VENUSAUR_MEGA] = 
    {  
      FRONT_COORD(0, 6),
      BACK_COORD(0, 10),
      PIC_DATA_ICON_INDEX(VenusaurMega, 4),
      .enemyMonElevation = 0,
    }, //VenusaurMega,
[SPECIES_CHARIZARD_MEGA_X] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 2),
      PIC_DATA_ICON_INDEX(CharizardMegaX, 0),
      .enemyMonElevation = 0,
    }, //CharizardMegaX,
[SPECIES_CHARIZARD_MEGA_Y] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(CharizardMegaY, 0),
      .enemyMonElevation = 0,
    }, //CharizardMegaY,
[SPECIES_BLASTOISE_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(BlastoiseMega, 2),
      .enemyMonElevation = 0,
    }, //BlastoiseMega,
[SPECIES_BEEDRILL_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 5),
      PIC_DATA_ICON_INDEX(BeedrillMega, 2),
      .enemyMonElevation = 5,
    }, //BeedrillMega,
[SPECIES_PIDGEOT_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 7),
      PIC_DATA_ICON_INDEX(PidgeotMega, 0),
      .enemyMonElevation = 8,
    }, //PidgeotMega,
[SPECIES_ALAKAZAM_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(AlakazamMega, 2),
      .enemyMonElevation = 7,
    }, //AlakazamMega,
[SPECIES_SLOWBRO_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 9),
      PIC_DATA_ICON_INDEX(SlowbroMega, 0),
      .enemyMonElevation = 0,
    }, //SlowbroMega,
[SPECIES_GENGAR_MEGA] = 
    {  
      FRONT_COORD(0, 8),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(GengarMega, 2),
      .enemyMonElevation = 0,
    }, //GengarMega,
[SPECIES_KANGASKHAN_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(KangaskhanMega, 2),
      .enemyMonElevation = 0,
    }, //KangaskhanMega,
[SPECIES_PINSIR_MEGA] = 
    {  
      FRONT_COORD(0, 4),
      BACK_COORD(0, 7),
      PIC_DATA_ICON_INDEX(PinsirMega, 2),
      .enemyMonElevation = 4,
    }, //PinsirMega,
[SPECIES_GYARADOS_MEGA] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(GyaradosMega, 0),
      .enemyMonElevation = 6,
    }, //GyaradosMega,
[SPECIES_AERODACTYL_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 8),
      PIC_DATA_ICON_INDEX(AerodactylMega, 2),
      .enemyMonElevation = 3,
    }, //AerodactylMega,
[SPECIES_MEWTWO_MEGA_X] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(MewtwoMegaX, 2),
      .enemyMonElevation = 0,
    }, //MewtwoMegaX,
[SPECIES_MEWTWO_MEGA_Y] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 2),
      PIC_DATA_ICON_INDEX(MewtwoMegaY, 2),
      .enemyMonElevation = 3,
    }, //MewtwoMegaY,
[SPECIES_AMPHAROS_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(AmpharosMega, 0),
      .enemyMonElevation = 0,
    }, //AmpharosMega,
[SPECIES_STEELIX_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(SteelixMega, 0),
      .enemyMonElevation = 0,
    }, //SteelixMega,
[SPECIES_SCIZOR_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 4),
      PIC_DATA_ICON_INDEX(ScizorMega, 2),
      .enemyMonElevation = 0,
    }, //ScizorMega,
[SPECIES_HERACROSS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(HeracrossMega, 0),
      .enemyMonElevation = 0,
    }, //HeracrossMega,
[SPECIES_HOUNDOOM_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(HoundoomMega, 0),
      .enemyMonElevation = 0,
    }, //HoundoomMega,
[SPECIES_TYRANITAR_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(TyranitarMega, 1),
      .enemyMonElevation = 0,
    }, //TyranitarMega,
[SPECIES_SCEPTILE_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(SceptileMega, 4),
      .enemyMonElevation = 0,
    }, //SceptileMega,
[SPECIES_BLAZIKEN_MEGA] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(BlazikenMega, 0),
      .enemyMonElevation = 0,
    }, //BlazikenMega,
[SPECIES_SWAMPERT_MEGA] = 
    {  
      FRONT_COORD(0, 4),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(SwampertMega, 0),
      .enemyMonElevation = 0,
    }, //SwampertMega,
[SPECIES_GARDEVOIR_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(GardevoirMega, 1),
      .enemyMonElevation = 0,
    }, //GardevoirMega,
[SPECIES_SABLEYE_MEGA] = 
    {  
      FRONT_COORD(0, 7),
      BACK_COORD(0, 13),
      PIC_DATA_ICON_INDEX(SableyeMega, 5),
      .enemyMonElevation = 0,
    }, //SableyeMega,
[SPECIES_MAWILE_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(MawileMega, 0),
      .enemyMonElevation = 0,
    }, //MawileMega,
[SPECIES_AGGRON_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 7),
      PIC_DATA_ICON_INDEX(AggronMega, 2),
      .enemyMonElevation = 0,
    }, //AggronMega,
[SPECIES_MEDICHAM_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 2),
      PIC_DATA_ICON_INDEX(MedichamMega, 0),
      .enemyMonElevation = 0,
    }, //MedichamMega,
[SPECIES_MANECTRIC_MEGA] = 
    {  
      FRONT_COORD(0, 3),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(ManectricMega, 0),
      .enemyMonElevation = 0,
    }, //ManectricMega,
[SPECIES_SHARPEDO_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(SharpedoMega, 0),
      .enemyMonElevation = 1,
    }, //SharpedoMega,
[SPECIES_CAMERUPT_MEGA] = 
    {  
      FRONT_COORD(0, 6),
      BACK_COORD(0, 9),
      PIC_DATA_ICON_INDEX(CameruptMega, 0),
      .enemyMonElevation = 0,
    }, //CameruptMega,
[SPECIES_ALTARIA_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 10),
      PIC_DATA_ICON_INDEX(AltariaMega, 0),
      .enemyMonElevation = 6,
    }, //AltariaMega,
[SPECIES_BANETTE_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(BanetteMega, 0),
      .enemyMonElevation = 5,
    }, //BanetteMega,
[SPECIES_ABSOL_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(AbsolMega, 0),
      .enemyMonElevation = 0,
    }, //AbsolMega,
[SPECIES_GLALIE_MEGA] = 
    {  
      FRONT_COORD(0, 4),
      BACK_COORD(0, 10),
      PIC_DATA_ICON_INDEX(GlalieMega, 0),
      .enemyMonElevation = 8,
    }, //GlalieMega,
[SPECIES_SALAMENCE_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(SalamenceMega, 0),
      .enemyMonElevation = 0,
    }, //SalamenceMega,
[SPECIES_METAGROSS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6), //back sprite bad check for updated versionin EE
      PIC_DATA_ICON_INDEX(MetagrossMega, 0),
      .enemyMonElevation = 4,
    }, //MetagrossMega, //vsonic
[SPECIES_LATIAS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(LatiasMega, 2),
      .enemyMonElevation = 8,
    }, //LatiasMega,
[SPECIES_LATIOS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(LatiosMega, 2),
      .enemyMonElevation = 8,
    }, //LatiosMega,
[SPECIES_LOPUNNY_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 4),
      PIC_DATA_ICON_INDEX(LopunnyMega, 2),
      .enemyMonElevation = 0,
    }, //LopunnyMega,
[SPECIES_GARCHOMP_MEGA] = 
    {  
      FRONT_COORD(0, 3),
      BACK_COORD(0, 4),
      PIC_DATA_ICON_INDEX(GarchompMega, 0),
      .enemyMonElevation = 0,
    }, //GarchompMega,
[SPECIES_LUCARIO_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(LucarioMega, 2),
      .enemyMonElevation = 0,
    }, //LucarioMega,
[SPECIES_ABOMASNOW_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(AbomasnowMega, 1),
      .enemyMonElevation = 0,
    }, //AbomasnowMega,
[SPECIES_GALLADE_MEGA] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(GalladeMega, 1),
      .enemyMonElevation = 0,
    }, //GalladeMega,
[SPECIES_AUDINO_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(AudinoMega, 1),
      .enemyMonElevation = 0,
    }, //AudinoMega,
[SPECIES_DIANCIE_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(DiancieMega, 0),
      .enemyMonElevation = 0,
    }, //DiancieMega,
[SPECIES_RAYQUAZA_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(RayquazaMega, 1),
      .enemyMonElevation = 0,
    }, //RayquazaMega,
[SPECIES_KYOGRE_PRIMAL] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x84, 18),
      PIC_DATA_ICON_INDEX(KyogrePrimal, 0),
      .enemyMonElevation = 0,
    }, //KyogrePrimal,
[SPECIES_GROUDON_PRIMAL] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(GroudonPrimal, 0),
      .enemyMonElevation = 0,
    }, //GroudonPrimal,
[SPECIES_RATTATA_ALOLAN] = 
    {  
      FRONT_COORD(0x44, 13),
      BACK_COORD(0x65, 7),
      PIC_DATA_ICON_INDEX(RattataAlolan, 2),
      .enemyMonElevation = 0,
    }, //RattataAlolan,
[SPECIES_RATICATE_ALOLAN] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x75, 10),
      PIC_DATA_ICON_INDEX(RaticateAlolan, 2),
      .enemyMonElevation = 0,
    }, //RaticateAlolan,
[SPECIES_RAICHU_ALOLAN] = 
    {  
      FRONT_COORD(0x67, 3),
      BACK_COORD(0x66, 6),
      PIC_DATA_ICON_INDEX(RaichuAlolan, 2),
      .enemyMonElevation = 0,
    }, //RaichuAlolan,
[SPECIES_SANDSHREW_ALOLAN] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(SandshrewAlolan, 0),
      .enemyMonElevation = 0,
    }, //SandshrewAlolan,
[SPECIES_SANDSLASH_ALOLAN] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 18),//11, 6, 18
      PIC_DATA_ICON_INDEX(SandslashAlolan, 0),
      .enemyMonElevation = 0,
    }, //SandslashAlolan,
[SPECIES_VULPIX_ALOLAN] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(VulpixAlolan, 2),
      .enemyMonElevation = 0,
    }, //VulpixAlolan,
[SPECIES_NINETALES_ALOLAN] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(NinetalesAlolan, 2),
      .enemyMonElevation = 0,
    }, //NinetalesAlolan,
[SPECIES_DIGLETT_ALOLAN] = 
    {  
      FRONT_COORD(0x54, 17),
      BACK_COORD(0x54, 14),
      PIC_DATA_ICON_INDEX(DiglettAlolan, 2),
      .enemyMonElevation = 0,
    }, //DiglettAlolan,
[SPECIES_DUGTRIO_ALOLAN] = 
    {  
      FRONT_COORD(0x75, 11),
      BACK_COORD(0x66, 17),
      PIC_DATA_ICON_INDEX(DugtrioAlolan, 2),
      .enemyMonElevation = 0,
    }, //DugtrioAlolan,
[SPECIES_MEOWTH_ALOLAN] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x65, 7),
      PIC_DATA_ICON_INDEX(MeowthAlolan, 2),
      .enemyMonElevation = 0,
    }, //MeowthAlolan,
[SPECIES_PERSIAN_ALOLAN] = 
    {  
      FRONT_COORD(0x77, 4),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(PersianAlolan, 2),
      .enemyMonElevation = 0,
    }, //PersianAlolan,
[SPECIES_GEODUDE_ALOLAN] = 
    {  
      FRONT_COORD(0x54, 10),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(GeodudeAlolan, 2),
      .enemyMonElevation = 0,
    }, //GeodudeAlolan,
[SPECIES_GRAVELER_ALOLAN] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x75, 10),
      PIC_DATA_ICON_INDEX(GravelerAlolan, 2),
      .enemyMonElevation = 0,
    }, //GravelerAlolan,
[SPECIES_GOLEM_ALOLAN] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x84, 13),
      PIC_DATA_ICON_INDEX(GolemAlolan, 2),
      .enemyMonElevation = 0,
    }, //GolemAlolan,
[SPECIES_GRIMER_ALOLAN] = 
    {  
      FRONT_COORD(0x65, 9),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(GrimerAlolan, 1),
      .enemyMonElevation = 0,
    }, //GrimerAlolan,
[SPECIES_MUK_ALOLAN] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(MukAlolan, 0),
      .enemyMonElevation = 0,
    }, //MukAlolan,
[SPECIES_EXEGGUTOR_ALOLAN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(ExeggutorAlolan, 1),
      .enemyMonElevation = 0,
    }, //ExeggutorAlolan,
[SPECIES_MAROWAK_ALOLAN] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(MarowakAlolan, 4),
      .enemyMonElevation = 0,
    }, //MarowakAlolan,
[SPECIES_MEOWTH_GALARIAN] = 
    {  
      FRONT_COORD(0x66, 9),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(MeowthGalarian, 0),
      .enemyMonElevation = 0,
    }, //MeowthGalarian,
[SPECIES_PONYTA_GALARIAN] = 
    {  
      FRONT_COORD(0x87, 8),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PonytaGalarian, 2),
      .enemyMonElevation = 0,
    }, //PonytaGalarian,
[SPECIES_RAPIDASH_GALARIAN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(RapidashGalarian, 2),
      .enemyMonElevation = 0,
    }, //RapidashGalarian,
[SPECIES_SLOWPOKE_GALARIAN] = 
    {  
      FRONT_COORD(0x74, 19),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(SlowpokeGalarian, 0),
      .enemyMonElevation = 0,
    }, //SlowpokeGalarian,
[SPECIES_SLOWBRO_GALARIAN] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(SlowbroGalarian, 0),
      .enemyMonElevation = 0,
    }, //SlowbroGalarian,
[SPECIES_FARFETCHD_GALARIAN] = 
    {  
      FRONT_COORD(0x86, 9),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(FarfetchdGalarian, 1),
      .enemyMonElevation = 0,
    }, //FarfetchdGalarian,
[SPECIES_WEEZING_GALARIAN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(WeezingGalarian, 1),
      .enemyMonElevation = 3,
    }, //WeezingGalarian,
[SPECIES_MR_MIME_GALARIAN] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(MrMimeGalarian, 0),
      .enemyMonElevation = 0,
    }, //MrMimeGalarian,
[SPECIES_ARTICUNO_GALARIAN] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(ArticunoGalarian, 2),
      .enemyMonElevation = 0,
    }, //ArticunoGalarian,
[SPECIES_ZAPDOS_GALARIAN] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(ZapdosGalarian, 0),
      .enemyMonElevation = 0,
    }, //ZapdosGalarian,
[SPECIES_MOLTRES_GALARIAN] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(MoltresGalarian, 0),
      .enemyMonElevation = 0,
    }, //MoltresGalarian,
[SPECIES_SLOWKING_GALARIAN] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(SlowkingGalarian, 0),
      .enemyMonElevation = 0,
    }, //SlowkingGalarian,
[SPECIES_CORSOLA_GALARIAN] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(CorsolaGalarian, 0),
      .enemyMonElevation = 0,
    }, //CorsolaGalarian,
[SPECIES_ZIGZAGOON_GALARIAN] = 
    {  
      FRONT_COORD(0x75, 13),
      BACK_COORD(0x76, 12),
      PIC_DATA_ICON_INDEX(ZigzagoonGalarian, 0),
      .enemyMonElevation = 0,
    }, //ZigzagoonGalarian,
[SPECIES_LINOONE_GALARIAN] = 
    {  
      FRONT_COORD(0x85, 13),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(LinooneGalarian, 0),
      .enemyMonElevation = 0,
    }, //LinooneGalarian,
[SPECIES_DARUMAKA_GALARIAN] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(DarumakaGalarian, 0),
      .enemyMonElevation = 0,
    }, //DarumakaGalarian,
[SPECIES_DARMANITAN_GALARIAN] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(DarmanitanGalarian, 0),
      .enemyMonElevation = 0,
    }, //DarmanitanGalarian,
[SPECIES_YAMASK_GALARIAN] = 
    {  
      FRONT_COORD(0x65, 13),
      BACK_COORD(0x55, 13),
      PIC_DATA_ICON_INDEX(YamaskGalarian, 2),
      .enemyMonElevation = 4,
    }, //YamaskGalarian,
[SPECIES_STUNFISK_GALARIAN] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x83, 23),
      PIC_DATA_ICON_INDEX(StunfiskGalarian, 1),
      .enemyMonElevation = 0,
    }, //StunfiskGalarian,
[SPECIES_GROWLITHE_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(GrowlitheHisuian, 0),
      .enemyMonElevation = 0,
    }, //GrowlitheHisuian,
[SPECIES_ARCANINE_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 2),
      BACK_COORD(0x87, 3),
      PIC_DATA_ICON_INDEX(ArcanineHisuian, 0),
      .enemyMonElevation = 0,
    }, //ArcanineHisuian,
[SPECIES_VOLTORB_HISUIAN] = 
    {  
      FRONT_COORD(0x65, 0),
      BACK_COORD(0x76, 10),
      PIC_DATA_ICON_INDEX(VoltorbHisuian, 0),
      .enemyMonElevation = 0,
    }, //VoltorbHisuian,
[SPECIES_ELECTRODE_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(ElectrodeHisuian, 3),
      .enemyMonElevation = 0,
    }, //ElectrodeHisuian,
[SPECIES_TYPHLOSION_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 2),
      PIC_DATA_ICON_INDEX(TyphlosionHisuian, 1),
      .enemyMonElevation = 0,
    }, //TyphlosionHisuian,
[SPECIES_QWILFISH_HISUIAN] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x55, 6),
      PIC_DATA_ICON_INDEX(QwilfishHisuian, 0),
      .enemyMonElevation = 0,
    }, //QwilfishHisuian,
[SPECIES_SNEASEL_HISUIAN] = 
    {  
      FRONT_COORD(0x65, 7),
      BACK_COORD(0x87, 3),
      PIC_DATA_ICON_INDEX(SneaselHisuian, 2),
      .enemyMonElevation = 0,
    }, //SneaselHisuian,
[SPECIES_SAMUROTT_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(SamurottHisuian, 0),
      .enemyMonElevation = 0,
    }, //SamurottHisuian,
[SPECIES_LILLIGANT_HISUIAN] = 
    {  
      FRONT_COORD(0x65, 1),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(LilligantHisuian, 1),
      .enemyMonElevation = 0,
    }, //LilligantHisuian,
[SPECIES_ZORUA_HISUIAN] = 
    {  
      FRONT_COORD(0x55, 2),
      BACK_COORD(0x55, 1),
      PIC_DATA_ICON_INDEX(ZoruaHisuian, 0),
      .enemyMonElevation = 0,
    }, //ZoruaHisuian,
[SPECIES_ZOROARK_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 1),
      BACK_COORD(0x87, 0),
      PIC_DATA_ICON_INDEX(ZoroarkHisuian, 0),
      .enemyMonElevation = 0,
    }, //ZoroarkHisuian,
[SPECIES_BRAVIARY_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(BraviaryHisuian, 2),
      .enemyMonElevation = 0,
    }, //BraviaryHisuian,
[SPECIES_SLIGGOO_HISUIAN] = 
    {  
      FRONT_COORD(0x55, 6),
      BACK_COORD(0x55, 1),
      PIC_DATA_ICON_INDEX(SliggooHisuian, 2),
      .enemyMonElevation = 0,
    }, //SliggooHisuian,
[SPECIES_GOODRA_HISUIAN] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x87, 0),
      PIC_DATA_ICON_INDEX(GoodraHisuian, 2),
      .enemyMonElevation = 0,
    }, //GoodraHisuian,
[SPECIES_AVALUGG_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 5),
      BACK_COORD(0x87, 16),
      PIC_DATA_ICON_INDEX(AvaluggHisuian, 5),
      .enemyMonElevation = 0,
    }, //AvaluggHisuian,
[SPECIES_DECIDUEYE_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 0),
      PIC_DATA_ICON_INDEX(DecidueyeHisuian, 0),
      .enemyMonElevation = 0,
    }, //DecidueyeHisuian,
[SPECIES_PIKACHU_COSPLAY] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuCosplay, 2),
      .enemyMonElevation = 0,
    }, //PikachuCosplay,
[SPECIES_PIKACHU_ROCK_STAR] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuRockStar, 1),
      .enemyMonElevation = 0,
    }, //PikachuRockStar,
[SPECIES_PIKACHU_BELLE] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuBelle, 0),
      .enemyMonElevation = 0,
    }, //PikachuBelle,
[SPECIES_PIKACHU_POP_STAR] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuPopStar, 0),
      .enemyMonElevation = 0,
    }, //PikachuPopStar,
[SPECIES_PIKACHU_PH_D] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuPhD, 1),
      .enemyMonElevation = 0,
    }, //PikachuPhD,
[SPECIES_PIKACHU_LIBRE] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuLibre, 0),
      .enemyMonElevation = 0,
    }, //PikachuLibre,
[SPECIES_PIKACHU_ORIGINAL_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuOriginalCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuOriginalCap,
[SPECIES_PIKACHU_HOENN_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuHoennCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuHoennCap,
[SPECIES_PIKACHU_SINNOH_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuSinnohCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuSinnohCap,
[SPECIES_PIKACHU_UNOVA_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuUnovaCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuUnovaCap,
[SPECIES_PIKACHU_KALOS_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuKalosCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuKalosCap,
[SPECIES_PIKACHU_ALOLA_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuAlolaCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuAlolaCap,
[SPECIES_PIKACHU_PARTNER_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4), //vsonic palett off for this one
      PIC_DATA_ICON_INDEX(PikachuPartnerCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuPartnerCap,
[SPECIES_PIKACHU_WORLD_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuWorldCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuWorldCap,
[SPECIES_PICHU_SPIKY_EARED] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(PichuSpikyEared, 1),
      .enemyMonElevation = 0,
    }, //PichuSpikyEared,
[SPECIES_CASTFORM_SUNNY] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x48, 0),
      PIC_DATA_ICON_INDEX(CastformSunny, 0),
      .enemyMonElevation = 0,
    }, //CastformSunny,
[SPECIES_CASTFORM_RAINY] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x48, 0),
      PIC_DATA_ICON_INDEX(CastformRainy, 0),
      .enemyMonElevation = 0,
    }, //CastformRainy,
[SPECIES_CASTFORM_SNOWY] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x48, 0),
      PIC_DATA_ICON_INDEX(CastformSnowy, 0),
      .enemyMonElevation = 0,
    }, //CastformSnowy,
[SPECIES_DEOXYS_ATTACK] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 2),
      PIC_DATA_ICON_INDEX(DeoxysAttack,0),
      .enemyMonElevation = 0,
    }, //DeoxysAttack,
[SPECIES_DEOXYS_DEFENSE] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(DeoxysDefense,0),
      .enemyMonElevation = 0,
    }, //DeoxysDefense,
[SPECIES_DEOXYS_SPEED] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 1),
      PIC_DATA_ICON_INDEX(DeoxysSpeed,0),
      .enemyMonElevation = 0,
    }, //DeoxysSpeed,
[SPECIES_BURMY_SANDY_CLOAK] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x57, 6),
      PIC_DATA_ICON_INDEX(BurmySandyCloak, 1),
      .enemyMonElevation = 0,
    }, //BurmySandyCloak,
[SPECIES_BURMY_TRASH_CLOAK] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x57, 1),
      PIC_DATA_ICON_INDEX(BurmyTrashCloak, 0),
      .enemyMonElevation = 0,
    }, //BurmyTrashCloak,
[SPECIES_WORMADAM_SANDY_CLOAK] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(WormadamSandyCloak, 1),
      .enemyMonElevation = 0,
    }, //WormadamSandyCloak,
[SPECIES_WORMADAM_TRASH_CLOAK] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(WormadamTrashCloak, 0),
      .enemyMonElevation = 0,
    }, //WormadamTrashCloak,
[SPECIES_CHERRIM_SUNSHINE] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x57, 9),
      PIC_DATA_ICON_INDEX(CherrimSunshine, 1),
      .enemyMonElevation = 0,
    }, //CherrimSunshine,
[SPECIES_SHELLOS_EAST_SEA] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x57, 8),
      PIC_DATA_ICON_INDEX(ShellosEastSea, 0),
      .enemyMonElevation = 0,
    }, //ShellosEastSea,
[SPECIES_GASTRODON_EAST_SEA] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(GastrodonEastSea, 0),
      .enemyMonElevation = 0,
    }, //GastrodonEastSea,
[SPECIES_ROTOM_HEAT] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 12),
      PIC_DATA_ICON_INDEX(RotomHeat, 0),
      .enemyMonElevation = 0,
    }, //RotomHeat,
[SPECIES_ROTOM_WASH] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 11),
      PIC_DATA_ICON_INDEX(RotomWash, 0),
      .enemyMonElevation = 0,
    }, //RotomWash,
[SPECIES_ROTOM_FROST] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(RotomFrost, 5),
      .enemyMonElevation = 0,
    }, //RotomFrost,
[SPECIES_ROTOM_FAN] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(RotomFan, 0),
      .enemyMonElevation = 0,
    }, //RotomFan,
[SPECIES_ROTOM_MOW] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 11),
      PIC_DATA_ICON_INDEX(RotomMow, 0),
      .enemyMonElevation = 0,
    }, //RotomMow,
[SPECIES_GIRATINA_ORIGIN] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x65, 5),
      PIC_DATA_ICON_INDEX(GiratinaOrigin, 0),
      .enemyMonElevation = 7,
    }, //GiratinaOrigin,
[SPECIES_SHAYMIN_SKY] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x65, 2),
      PIC_DATA_ICON_INDEX(ShayminSky, 1),
      .enemyMonElevation = 0,
    }, //ShayminSky,
[SPECIES_ARCEUS_FIGHTING] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusFighting),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_FLYING] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusFlying),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_POISON] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusPoison),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_GROUND] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusGround),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_ROCK] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusRock),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_BUG] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusBug),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_GHOST] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusGhost),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_STEEL] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusSteel),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_FIRE] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusFire),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_WATER] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusWater),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_GRASS] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusGrass),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_ELECTRIC] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusElectric),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_PSYCHIC] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusPsychic),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_ICE] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusIce),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_DRAGON] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusDragon),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_DARK] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusDark),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_FAIRY] = 
    {  
      FRONT_PIC(Arceus),
      FRONT_COORD(0x67, 0),
      BACK_PIC(Arceus),
      BACK_COORD(0x88, 3),
      PALETTES(ArceusFairy),
      ICON(Arceus, 1),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_BASCULIN_BLUE_STRIPED] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 16),
      PIC_DATA_ICON_INDEX(BasculinBlueStriped, 0),
      .enemyMonElevation = 0,
    }, //BasculinBlueStriped,
[SPECIES_BASCULIN_WHITE_STRIPED] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 16),
      PIC_DATA_ICON_INDEX(BasculinWhiteStriped, 0),
      .enemyMonElevation = 0,
    }, //BasculinWhiteStriped,
[SPECIES_DARMANITAN_ZEN_MODE] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x66, 18),
      PIC_DATA_ICON_INDEX(DarmanitanZenMode, 0),
      .enemyMonElevation = 0,
    }, //DarmanitanZenMode,
[SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(DarmanitanZenModeGalarian, 0),
      .enemyMonElevation = 0,
    }, //DarmanitanZenModeGalarian,
[SPECIES_DEERLING_SUMMER] = 
    {  
      FRONT_PIC(Deerling),
      FRONT_COORD(0x45, 11),
      BACK_PIC(Deerling),
      BACK_COORD(0x67, 9),
      PALETTES(DeerlingSummer),
      ICON(DeerlingSummer, 1),
      .enemyMonElevation = 0,
    }, //DeerlingSummer,
[SPECIES_DEERLING_AUTUMN] = 
    {  
      FRONT_PIC(Deerling),
      FRONT_COORD(0x45, 11),
      BACK_PIC(Deerling),
      BACK_COORD(0x67, 9),
      PALETTES(DeerlingAutumn),
      ICON(DeerlingAutumn, 0),
      .enemyMonElevation = 0,
    }, //DeerlingAutumn,
[SPECIES_DEERLING_WINTER] = 
    {  
      FRONT_PIC(Deerling),
      FRONT_COORD(0x45, 11),
      BACK_PIC(Deerling),
      BACK_COORD(0x67, 9),
      PALETTES(DeerlingWinter),
      ICON(DeerlingWinter, 2),
      .enemyMonElevation = 0,
    }, //DeerlingWinter,
[SPECIES_SAWSBUCK_SUMMER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(SawsbuckSummer, 1),
      .enemyMonElevation = 0,
    }, //SawsbuckSummer,
[SPECIES_SAWSBUCK_AUTUMN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(SawsbuckAutumn, 1),
      .enemyMonElevation = 0,
    }, //SawsbuckAutumn,
[SPECIES_SAWSBUCK_WINTER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(SawsbuckWinter, 1),
      .enemyMonElevation = 0,
    }, //SawsbuckWinter,
[SPECIES_TORNADUS_THERIAN] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x66, 3),
      PIC_DATA_ICON_INDEX(TornadusTherian, 1),
      .enemyMonElevation = 0,
    }, //TornadusTherian,
[SPECIES_THUNDURUS_THERIAN] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x66, 7),
      PIC_DATA_ICON_INDEX(ThundurusTherian, 0),
      .enemyMonElevation = 7,
    }, //ThundurusTherian,
[SPECIES_LANDORUS_THERIAN] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x66, 7),
      PIC_DATA_ICON_INDEX(LandorusTherian, 0),
      .enemyMonElevation = 0,
    }, //LandorusTherian,
[SPECIES_ENAMORUS_THERIAN] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x68, 7),
      PIC_DATA_ICON_INDEX(EnamorusTherian, 1),
      .enemyMonElevation = 0,
    }, //EnamorusTherian,
[SPECIES_KYUREM_WHITE] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x66, 3),
      PIC_DATA_ICON_INDEX(KyuremWhite, 0),
      .enemyMonElevation = 0,
    }, //KyuremWhite,
[SPECIES_KYUREM_BLACK] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x66, 3),
      PIC_DATA_ICON_INDEX(KyuremBlack, 0),
      .enemyMonElevation = 0,
    }, //KyuremBlack,
[SPECIES_KELDEO_RESOLUTE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(KeldeoResolute, 0),
      .enemyMonElevation = 0,
    }, //KeldeoResolute,
[SPECIES_MELOETTA_PIROUETTE] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(MeloettaPirouette, 0),
      .enemyMonElevation = 0,
    }, //MeloettaPirouette,
[SPECIES_GENESECT_DOUSE_DRIVE] = 
    {  
      FRONT_PIC(Genesect),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Genesect),
      BACK_COORD(0x86, 8),
      PALETTES(GenesectDouseDrive),
      ICON(Genesect, 2),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GENESECT_SHOCK_DRIVE] = 
    {  
      FRONT_PIC(Genesect),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Genesect),
      BACK_COORD(0x86, 8),
      PALETTES(GenesectShockDrive),
      ICON(Genesect, 2),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GENESECT_BURN_DRIVE] = 
    {  
      FRONT_PIC(Genesect),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Genesect),
      BACK_COORD(0x86, 8),
      PALETTES(GenesectBurnDrive),
      ICON(Genesect, 2),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GENESECT_CHILL_DRIVE] = 
    {  
      FRONT_PIC(Genesect),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Genesect),
      BACK_COORD(0x86, 8),
      PALETTES(GenesectChillDrive),
      ICON(Genesect, 2),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GRENINJA_ASH] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(GreninjaAsh, 0),
      .enemyMonElevation = 0,
    }, //GreninjaAsh,
[SPECIES_VIVILLON_POLAR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonPolar, 0),
      .enemyMonElevation = 0,
    }, //VivillonPolar,
[SPECIES_VIVILLON_TUNDRA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonTundra, 0),
      .enemyMonElevation = 0,
    }, //VivillonTundra,
[SPECIES_VIVILLON_CONTINENTAL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonContinental, 2),
      .enemyMonElevation = 0,
    }, //VivillonContinental,
[SPECIES_VIVILLON_GARDEN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonGarden, 1),
      .enemyMonElevation = 0,
    }, //VivillonGarden,
[SPECIES_VIVILLON_ELEGANT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonElegant, 0),
      .enemyMonElevation = 0,
    }, //VivillonElegant,
[SPECIES_VIVILLON_MEADOW] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonMeadow, 0),
      .enemyMonElevation = 0,
    }, //VivillonMeadow,
[SPECIES_VIVILLON_MODERN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonModern, 2),
      .enemyMonElevation = 0,
    }, //VivillonModern,
[SPECIES_VIVILLON_MARINE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonMarine, 0),
      .enemyMonElevation = 0,
    }, //VivillonMarine,
[SPECIES_VIVILLON_ARCHIPELAGO] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonArchipelago, 0),
      .enemyMonElevation = 0,
    }, //VivillonArchipelago,
[SPECIES_VIVILLON_HIGH_PLAINS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonHighPlains, 0),
      .enemyMonElevation = 0,
    }, //VivillonHighPlains,
[SPECIES_VIVILLON_SANDSTORM] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSandstorm, 1),
      .enemyMonElevation = 0,
    }, //VivillonSandstorm,
[SPECIES_VIVILLON_RIVER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonRiver, 2),
      .enemyMonElevation = 0,
    }, //VivillonRiver,
[SPECIES_VIVILLON_MONSOON] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonMonsoon, 0),
      .enemyMonElevation = 0,
    }, //VivillonMonsoon,
[SPECIES_VIVILLON_SAVANNA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSavanna, 0),
      .enemyMonElevation = 0,
    }, //VivillonSavanna,
[SPECIES_VIVILLON_SUN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSun, 0),
      .enemyMonElevation = 0,
    }, //VivillonSun,
[SPECIES_VIVILLON_OCEAN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonOcean, 0),
      .enemyMonElevation = 0,
    }, //VivillonOcean,
[SPECIES_VIVILLON_JUNGLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonJungle, 0),
      .enemyMonElevation = 0,
    }, //VivillonJungle,
[SPECIES_VIVILLON_FANCY] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonFancy, 1),
      .enemyMonElevation = 0,
    }, //VivillonFancy,
[SPECIES_VIVILLON_POKE_BALL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonPokeBall, 2),
      .enemyMonElevation = 0,
    }, //VivillonPokeBall,
[SPECIES_UNFEZANT_FEMALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(UnfezantFemale, 1),
      .enemyMonElevation = 0,
    }, //Unfezant_Female
[SPECIES_PYROAR_FEMALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88,3),
      PIC_DATA_ICON_INDEX(PyroarFemale, 2),
      .enemyMonElevation = 0,
    }, //Pyroar_Female,
[SPECIES_FLABEBE_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(Flabebe),
      FRONT_COORD(0x45, 6),
      BACK_PIC(Flabebe),
      BACK_COORD(0x85, 12),
      PALETTES(FlabebeYellowFlower),
      ICON(FlabebeYellowFlower, 1),
      .enemyMonElevation = 0,
    }, //FlabebeYellowFlower,
[SPECIES_FLABEBE_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(Flabebe),
      FRONT_COORD(0x45, 6),
      BACK_PIC(Flabebe),
      BACK_COORD(0x85, 12),
      PALETTES(FlabebeOrangeFlower),
      ICON(FlabebeOrangeFlower, 0),
      .enemyMonElevation = 0,
    }, //FlabebeOrangeFlower,
[SPECIES_FLABEBE_BLUE_FLOWER] = 
    {  
      FRONT_PIC(Flabebe),
      FRONT_COORD(0x45, 6),
      BACK_PIC(Flabebe),
      BACK_COORD(0x85, 12),
      PALETTES(FlabebeBlueFlower),
      ICON(FlabebeBlueFlower, 0),
      .enemyMonElevation = 0,
    }, //FlabebeBlueFlower,
[SPECIES_FLABEBE_WHITE_FLOWER] = 
    {  
      FRONT_PIC(Flabebe),
      FRONT_COORD(0x45, 6),
      BACK_PIC(Flabebe),
      BACK_COORD(0x85, 12),
      PALETTES(FlabebeWhiteFlower),
      ICON(FlabebeWhiteFlower, 1),
      .enemyMonElevation = 0,
    }, //FlabebeWhiteFlower,
[SPECIES_FLOETTE_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(Floette),
      FRONT_COORD(0x45, 3),
      BACK_PIC(Floette),
      BACK_COORD(0x88, 2),
      PALETTES(FloetteYellowFlower),
      ICON(FloetteYellowFlower, 1),
      .enemyMonElevation = 0,
    }, //FloetteYellowFlower,
[SPECIES_FLOETTE_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(Floette),
      FRONT_COORD(0x45, 3),
      BACK_PIC(Floette),
      BACK_COORD(0x88, 2),
      PALETTES(FloetteOrangeFlower),
      ICON(FloetteOrangeFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteOrangeFlower,
[SPECIES_FLOETTE_BLUE_FLOWER] = 
    {  
      FRONT_PIC(Floette),
      FRONT_COORD(0x45, 3),
      BACK_PIC(Floette),
      BACK_COORD(0x88, 2),
      PALETTES(FloetteBlueFlower),
      ICON(FloetteBlueFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteBlueFlower,
[SPECIES_FLOETTE_WHITE_FLOWER] = 
    {  
      FRONT_PIC(Floette),
      FRONT_COORD(0x45, 3),
      BACK_PIC(Floette),
      BACK_COORD(0x88, 2),
      PALETTES(FloetteWhiteFlower),
      ICON(FloetteWhiteFlower, 1),
      .enemyMonElevation = 0,
    }, //FloetteWhiteFlower,
[SPECIES_FLOETTE_ETERNAL_FLOWER] = 
    {  
      FRONT_PIC(Floette),
      FRONT_COORD(0x45, 3),//sprite ro palette is off
      BACK_PIC(Floette),//for both front andback
      BACK_COORD(0x88, 2),
      PALETTES(FloetteEternalFlower),
      ICON(FloetteEternalFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteEternalFlower,
[SPECIES_FLORGES_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(Florges),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Florges),
      BACK_COORD(0x86, 9),
      PALETTES(FlorgesYellowFlower),
      ICON(FlorgesYellowFlower, 1),
      .enemyMonElevation = 0,
    }, //FlorgesYellowFlower,
[SPECIES_FLORGES_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(Florges),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Florges),
      BACK_COORD(0x86, 9),
      PALETTES(FlorgesOrangeFlower),
      ICON(FlorgesOrangeFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesOrangeFlower,
[SPECIES_FLORGES_BLUE_FLOWER] = 
    {  
      FRONT_PIC(Florges),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Florges),
      BACK_COORD(0x86, 9),
      PALETTES(FlorgesBlueFlower),
      ICON(FlorgesBlueFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesBlueFlower,
[SPECIES_FLORGES_WHITE_FLOWER] = 
    {  
      FRONT_PIC(Florges),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Florges),
      BACK_COORD(0x86, 9),
      PALETTES(FlorgesWhiteFlower),
      ICON(FlorgesWhiteFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesWhiteFlower,
[SPECIES_FURFROU_HEART_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouHeartTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouHeartTrim,
[SPECIES_FURFROU_STAR_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouStarTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouStarTrim,
[SPECIES_FURFROU_DIAMOND_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouDiamondTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouDiamondTrim,
[SPECIES_FURFROU_DEBUTANTE_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouDebutanteTrim, 2),
      .enemyMonElevation = 0,
    }, //FurfrouDebutanteTrim,
[SPECIES_FURFROU_MATRON_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouMatronTrim, 2),
      .enemyMonElevation = 0,
    }, //FurfrouMatronTrim,
[SPECIES_FURFROU_DANDY_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouDandyTrim, 1),
      .enemyMonElevation = 0,
    }, //FurfrouDandyTrim,
[SPECIES_FURFROU_LA_REINE_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouLaReineTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouLaReineTrim,
[SPECIES_FURFROU_KABUKI_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouKabukiTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouKabukiTrim,
[SPECIES_FURFROU_PHARAOH_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouPharaohTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouPharaohTrim,
[SPECIES_MEOWSTIC_FEMALE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(MeowsticFemale, 0),
      .enemyMonElevation = 0,
    }, //Meowstic_Female,
[SPECIES_AEGISLASH_BLADE] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(AegislashBlade, 2),
      .enemyMonElevation = 0,
    }, //AegislashBlade,
[SPECIES_PUMPKABOO_SMALL] = 
    {  
      FRONT_PIC(PumpkabooSmall),
      FRONT_COORD(0x45, 13),
      BACK_PIC(PumpkabooSmall),
      BACK_COORD(0x76, 13),
      PALETTES(Pumpkaboo),
      ICON(Pumpkaboo, 2),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_PUMPKABOO_LARGE] = 
    {  
      FRONT_PIC(PumpkabooLarge),
      FRONT_COORD(0x45, 13),
      BACK_PIC(PumpkabooLarge),
      BACK_COORD(0x76, 13),
      PALETTES(Pumpkaboo),
      ICON(Pumpkaboo, 2),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_PUMPKABOO_SUPER] = 
    {  
      FRONT_PIC(PumpkabooSuper),
      FRONT_COORD(0x45, 13),
      BACK_PIC(PumpkabooSuper),
      BACK_COORD(0x76, 13),
      PALETTES(Pumpkaboo),
      ICON(Pumpkaboo, 2),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_GOURGEIST_SMALL] = 
    {  
      FRONT_PIC(GourgeistSmall),
      FRONT_COORD(0x45, 4),
      BACK_PIC(GourgeistSmall),
      BACK_COORD(0x68, 3),
      PALETTES(Gourgeist),
      ICON(Gourgeist, 2),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_GOURGEIST_LARGE] = 
    {  
      FRONT_PIC(GourgeistLarge),
      FRONT_COORD(0x45, 4),
      BACK_PIC(GourgeistLarge),
      BACK_COORD(0x68, 3),
      PALETTES(Gourgeist),
      ICON(Gourgeist, 2),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_GOURGEIST_SUPER] = 
    {  
      FRONT_PIC(GourgeistSuper),
      FRONT_COORD(0x45, 4),
      BACK_PIC(GourgeistSuper),
      BACK_COORD(0x68, 3),
      PALETTES(Gourgeist),
      ICON(Gourgeist, 2),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_XERNEAS_ACTIVE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(XerneasActive, 0),
      .enemyMonElevation = 0,
    }, //XerneasActive,
[SPECIES_ZYGARDE_50] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Zygarde50, 1),
      .enemyMonElevation = 0,
    }, //Zygarde,
[SPECIES_ZYGARDE_COMPLETE] = 
    {  
      FRONT_COORD(0x55, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(ZygardeComplete, 1),
      .enemyMonElevation = 0,
    }, //ZygardeComplete,
[SPECIES_HOOPA_UNBOUND] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x66, 4),
      PIC_DATA_ICON_INDEX(HoopaUnbound, 0),
      .enemyMonElevation = 0,
    }, //HoopaUnbound,
[SPECIES_ORICORIO_POM_POM] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioPomPom, 1),
      .enemyMonElevation = 0,
    }, //OricorioPomPom,
[SPECIES_ORICORIO_PAU] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioPau, 1),
      .enemyMonElevation = 0,
    }, //OricorioPau,
[SPECIES_ORICORIO_SENSU] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioSensu, 0),
      .enemyMonElevation = 0,
    }, //OricorioSensu,
[SPECIES_LYCANROC_MIDNIGHT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(LycanrocMidnight, 2),
      .enemyMonElevation = 0,
    }, //LycanrocMidnight,
[SPECIES_LYCANROC_DUSK] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(LycanrocDusk, 0),
      .enemyMonElevation = 0,
    }, //LycanrocDusk,
[SPECIES_WISHIWASHI_SCHOOL] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(WishiwashiSchool, 0),
      .enemyMonElevation = 0,
    }, //WishiwashiSchool,
[SPECIES_SILVALLY_FIGHTING] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyFighting),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_FLYING] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyFlying),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_POISON] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyPoison),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_GROUND] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyGround),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_ROCK] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyRock),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_BUG] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyBug),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_GHOST] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyGhost),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_STEEL] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallySteel),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_FIRE] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyFire),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_WATER] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyWater),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_GRASS] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyGrass),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_ELECTRIC] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyElectric),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_PSYCHIC] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyPsychic),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_ICE] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyIce),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_DRAGON] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyDragon),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_DARK] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyDark),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_FAIRY] = 
    {  
      FRONT_PIC(Silvally),
      FRONT_COORD(0x45, 0),
      BACK_PIC(Silvally),
      BACK_COORD(0x78, 0),
      PALETTES(SilvallyFairy),
      ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_MINIOR_METEOR_ORANGE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_YELLOW] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_GREEN] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_BLUE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_INDIGO] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_VIOLET] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_CORE_RED] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreRed),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreRed, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreRed,
[SPECIES_MINIOR_CORE_ORANGE] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreOrange),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreOrange, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreOrange,
[SPECIES_MINIOR_CORE_YELLOW] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreYellow),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreYellow, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreYellow,
[SPECIES_MINIOR_CORE_GREEN] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreGreen),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreGreen, 1),
      .enemyMonElevation = 0,
    }, //MiniorCoreGreen,
[SPECIES_MINIOR_CORE_BLUE] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreBlue),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreBlue, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreBlue,
[SPECIES_MINIOR_CORE_INDIGO] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreIndigo),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreIndigo, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreIndigo,
[SPECIES_MINIOR_CORE_VIOLET] = 
    {  
      FRONT_PIC(MiniorCore),
      FRONT_COORD(0x87, 9),
      BACK_PIC(MiniorCore),
      BACK_COORD(0x66, 18),
      PAL(MiniorCoreViolet),
      SHINYPAL(MiniorCore),
      ICON(MiniorCoreViolet, 2),
      .enemyMonElevation = 0,
    }, //MiniorCoreViolet,
[SPECIES_MIMIKYU_BUSTED] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x77, 15),
      PIC_DATA_ICON_INDEX(MimikyuBusted, 3),
      .enemyMonElevation = 0,
    }, //MimikyuBusted,
[SPECIES_NECROZMA_DUSK_MANE] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(NecrozmaDuskMane, 0),
      .enemyMonElevation = 0,
    }, //NecrozmaDuskMane,
[SPECIES_NECROZMA_DAWN_WINGS] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(NecrozmaDawnWings, 0),
      .enemyMonElevation = 0,
    }, //NecrozmaDawnWings,
[SPECIES_NECROZMA_ULTRA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(NecrozmaUltra, 2),
      .enemyMonElevation = 0,
    }, //NecrozmaUltra,
[SPECIES_MAGEARNA_ORIGINAL_COLOR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(MagearnaOriginalColor, 0),
      .enemyMonElevation = 0,
    }, //MagearnaOriginalColor,
[SPECIES_CRAMORANT_GULPING] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(CramorantGulping, 0),
      .enemyMonElevation = 0,
    }, //Cramorant_Gulping,
[SPECIES_CRAMORANT_GORGING] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(CramorantGorging, 0),
      .enemyMonElevation = 0,
    }, //Cramorant_Gorging,
[SPECIES_TOXTRICITY_LOW_KEY] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(ToxtricityLowKey, 2),
      .enemyMonElevation = 0,
    }, //Toxtricity_Low_key,
[SPECIES_SINISTEA_ANTIQUE]  =
{
  FRONT_COORD(0x54, 17),
  BACK_COORD(0x64, 16),
  PIC_DATA_ICON_INDEX(Sinistea, 0),
  .enemyMonElevation = 0,

},
[SPECIES_POLTEAGEIST_ANTIQUE]  =
{
  FRONT_COORD(0x66, 11),
  BACK_COORD(0x85, 13),
  PIC_DATA_ICON_INDEX(Polteageist, 0),
  .enemyMonElevation = 0,

},
    //Alcremie forms
[SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryRubyCream),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 1),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryMatchaCream),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 1),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryMintCream),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 3),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryLemonCream),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 2),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberrySaltedCream),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryRubySwirl),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 1),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryCaramelSwirl),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 2),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieStrawberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStrawberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStrawberryRainbowSwirl),
      SHINYPAL(AlcremieStrawberry),
      ICON(Alcremie, 2),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryVanillaCream),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryRubyCream),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryMatchaCream),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryMintCream),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryLemonCream),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberrySaltedCream),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryRubySwirl),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryCaramelSwirl),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieBlueberry),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieBlueberry),
      BACK_COORD(0x67, 9),
      PAL(AlcremieBlueberryRainbowSwirl),
      SHINYPAL(AlcremieBlueberry),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveVanillaCream),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveRubyCream),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveMatchaCream),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveMintCream),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveLemonCream),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveSaltedCream),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveRubySwirl),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveCaramelSwirl),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieLove),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieLove),
      BACK_COORD(0x67, 9),
      PAL(AlcremieLoveRainbowSwirl),
      SHINYPAL(AlcremieLove),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarVanillaCream),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarRubyCream),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarMatchaCream),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarMintCream),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarLemonCream),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarSaltedCream),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarRubySwirl),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarCaramelSwirl),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieStar),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieStar),
      BACK_COORD(0x67, 9),
      PAL(AlcremieStarRainbowSwirl),
      SHINYPAL(AlcremieStar),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerVanillaCream),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerRubyCream),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerMatchaCream),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerMintCream),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerLemonCream),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerSaltedCream),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerRubySwirl),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerCaramelSwirl),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieFlower),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieFlower),
      BACK_COORD(0x67, 9),
      PAL(AlcremieFlowerRainbowSwirl),
      SHINYPAL(AlcremieFlower),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonVanillaCream),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonRubyCream),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonMatchaCream),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonMintCream),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonLemonCream),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonSaltedCream),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonRubySwirl),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonCaramelSwirl),
      SHINYPAL(AlcremieRibbon),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieRibbon),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieRibbon),
      BACK_COORD(0x67, 9),
      PAL(AlcremieRibbonRainbowSwirl),
      SHINYPAL(AlcremieRibbon),
      ////PIC_DATA_ICON_INDEX(AlcremieRibbon,0), //gMonIcon_Alcremie
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    

[SPECIES_EISCUE_NOICE_FACE] = 
    {  
      FRONT_COORD(0x58, 0),
      BACK_COORD(0x58, 0),
      PIC_DATA_ICON_INDEX(EiscueNoiceFace, 0),
      .enemyMonElevation = 0,
    }, //Eiscue_noice_face,
[SPECIES_INDEEDEE_FEMALE] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(IndeedeeFemale, 2),
      .enemyMonElevation = 0,
    }, //Indeedee_Female,
[SPECIES_MORPEKO_HANGRY] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(MorpekoHangry, 2),
      .enemyMonElevation = 0,
    }, //Morpeko_Hangry,
[SPECIES_ZACIAN_CROWNED_SWORD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(ZacianCrownedSword, 2),
      .enemyMonElevation = 0,
    }, //Zacian_Crowned_Sword,
[SPECIES_ZAMAZENTA_CROWNED_SHIELD] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(ZamazentaCrownedShield, 2),
      .enemyMonElevation = 0,
    }, //Zamazenta_Crowned_Shield,
[SPECIES_ETERNATUS_ETERNAMAX] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 11),
      PIC_DATA_ICON_INDEX(EternatusEternamax, 0),
      .enemyMonElevation = 4,
    }, //Eternatus_Eternamax,
[SPECIES_URSHIFU_RAPID_STRIKE_STYLE] = 
    {  
      FRONT_PIC(UrshifuRapidStrikeStyle),
      FRONT_COORD(0x78, 0),
      BACK_PIC(UrshifuRapidStrikeStyle),
      BACK_COORD(0x87, 4),
      PALETTES(UrshifuRapidStrikeStyle),
      ICON(Urshifu, 2),
      .enemyMonElevation = 0,
    }, //Urshifu_Rapid, //think last value needs no comma, nope doesn't matter but using comma is better in case you plan to add more
[SPECIES_ZARUDE_DADA] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(ZarudeDada, 1),
      .enemyMonElevation = 0,
    }, //Zarude_Dada,
[SPECIES_CALYREX_ICE_RIDER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(CalyrexIceRider, 0),
      .enemyMonElevation = 0,
    }, //Calyrex_Ice_Rider,
[SPECIES_CALYREX_SHADOW_RIDER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(CalyrexShadowRider, 0),
      .enemyMonElevation = 0,
    }, //Calyrex_Shadow_Rider,
[SPECIES_BASCULEGION_FEMALE] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x72, 1),
      PIC_DATA_ICON_INDEX(BasculegionFemale, 0),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
[SPECIES_FRILLISH_FEMALE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x57, 7),
      PIC_DATA_ICON_INDEX(FrillishFemale, 1),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
[SPECIES_JELLICENT_FEMALE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(JellicentFemale, 4),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
};
