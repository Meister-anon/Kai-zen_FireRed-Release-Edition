
#define FRONT_PIC(sprite)                    \
        .frontPic = gMonFrontPic_## sprite,                 \
        //.frontPicSize = 0x800

#define FRONT_PIC_FEMALE(sprite, width, height)             \
        .frontPicFemale = gMonFrontPic_## sprite##F,        \
        .frontPicSizeFemale = MON_COORDS_SIZE(width, height)

#define BACK_PIC(sprite)                     \
        .backPic = gMonBackPic_## sprite,                   \
        //.backPicSize = 0x800

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
      //FRONT_PIC(None),
      FRONT_COORD(0x88,0),
      //BACK_PIC(None),
      BACK_COORD(0x88,0),
      //PALETTES(None),
      PIC_DATA_ICON_INDEX(None,0),
      //ICON(None, 0),
      .enemyMonElevation = 0,
    }, //QuestionMark, 
[SPECIES_BULBASAUR] = 
    {  
      //FRONT_PIC(Bulbasaur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bulbasaur),
      BACK_COORD(0x88,0),
      //PALETTES(Bulbasaur),
      PIC_DATA_ICON_INDEX(Bulbasaur,0),
      //ICON(Bulbasaur, 0),
      .enemyMonElevation = 0,
    }, //Bulbasaur,
[SPECIES_IVYSAUR] = 
    {  
      //FRONT_PIC(Ivysaur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ivysaur),
      BACK_COORD(0x88,0),
      //PALETTES(Ivysaur),
      PIC_DATA_ICON_INDEX(Ivysaur,0),
      //ICON(Ivysaur, 0),
      .enemyMonElevation = 0,
    }, //Ivysaur,
[SPECIES_VENUSAUR] = 
    {  
      //FRONT_PIC(Venusaur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Venusaur),
      BACK_COORD(0x88,0),
      //PALETTES(Venusaur),
      PIC_DATA_ICON_INDEX(Venusaur,0),
      //ICON(Venusaur, 0),
      .enemyMonElevation = 0,
    }, //Venusaur,
[SPECIES_CHARMANDER] = 
    {  
      //FRONT_PIC(Charmander),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charmander),
      BACK_COORD(0x88,0),
      //PALETTES(Charmander),
      PIC_DATA_ICON_INDEX(Charmander,0),
      //ICON(Charmander, 0),
      .enemyMonElevation = 0,
    }, //Charmander,
[SPECIES_CHARMELEON] = 
    {  
      //FRONT_PIC(Charmeleon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charmeleon),
      BACK_COORD(0x88,0),
      //PALETTES(Charmeleon),
      PIC_DATA_ICON_INDEX(Charmeleon,0),
      //ICON(Charmeleon, 0),
      .enemyMonElevation = 0,
    }, //Charmeleon,
[SPECIES_CHARIZARD] = 
    {  
      //FRONT_PIC(Charizard),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charizard),
      BACK_COORD(0x88,0),
      //PALETTES(Charizard),
      PIC_DATA_ICON_INDEX(Charizard,0),
      //ICON(Charizard, 0),
      .enemyMonElevation = 0,
    }, //Charizard,
[SPECIES_SQUIRTLE] = 
    {  
      //FRONT_PIC(Squirtle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Squirtle),
      BACK_COORD(0x88,0),
      //PALETTES(Squirtle),
      PIC_DATA_ICON_INDEX(Squirtle,0),
      //ICON(Squirtle, 0),
      .enemyMonElevation = 0,
    }, //Squirtle,
[SPECIES_WARTORTLE] = 
    {  
      //FRONT_PIC(Wartortle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wartortle),
      BACK_COORD(0x88,0),
      //PALETTES(Wartortle),
      PIC_DATA_ICON_INDEX(Wartortle,0),
      //ICON(Wartortle, 0),
      .enemyMonElevation = 0,
    }, //Wartortle,
[SPECIES_BLASTOISE] = 
    {  
      //FRONT_PIC(Blastoise),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blastoise),
      BACK_COORD(0x88,0),
      //PALETTES(Blastoise),
      PIC_DATA_ICON_INDEX(Blastoise,0),
      //ICON(Blastoise, 0),
      .enemyMonElevation = 0,
    }, //Blastoise,
[SPECIES_CATERPIE] = 
    {  
      //FRONT_PIC(Caterpie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Caterpie),
      BACK_COORD(0x88,0),
      //PALETTES(Caterpie),
      PIC_DATA_ICON_INDEX(Caterpie,0),
      //ICON(Caterpie, 0),
      .enemyMonElevation = 0,
    }, //Caterpie,
[SPECIES_METAPOD] = 
    {  
      //FRONT_PIC(Metapod),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Metapod),
      BACK_COORD(0x88,0),
      //PALETTES(Metapod),
      PIC_DATA_ICON_INDEX(Metapod,0),
      //ICON(Metapod, 0),
      .enemyMonElevation = 0,
    }, //Metapod,
[SPECIES_BUTTERFREE] = 
    {  
      //FRONT_PIC(Butterfree),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Butterfree),
      BACK_COORD(0x88,0),
      //PALETTES(Butterfree),
      PIC_DATA_ICON_INDEX(Butterfree,0),
      //ICON(Butterfree, 0),
      .enemyMonElevation = 0,
    }, //Butterfree,
[SPECIES_WEEDLE] = 
    {  
      //FRONT_PIC(Weedle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Weedle),
      BACK_COORD(0x88,0),
      //PALETTES(Weedle),
      PIC_DATA_ICON_INDEX(Weedle,0),
      //ICON(Weedle, 0),
      .enemyMonElevation = 0,
    }, //Weedle,
[SPECIES_KAKUNA] = 
    {  
      //FRONT_PIC(Kakuna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kakuna),
      BACK_COORD(0x88,0),
      //PALETTES(Kakuna),
      PIC_DATA_ICON_INDEX(Kakuna,0),
      //ICON(Kakuna, 0),
      .enemyMonElevation = 0,
    }, //Kakuna,
[SPECIES_BEEDRILL] = 
    {  
      //FRONT_PIC(Beedrill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Beedrill),
      BACK_COORD(0x88,0),
      //PALETTES(Beedrill),
      PIC_DATA_ICON_INDEX(Beedrill,0),
      //ICON(Beedrill, 0),
      .enemyMonElevation = 0,
    }, //Beedrill,
[SPECIES_PIDGEY] = 
    {  
      //FRONT_PIC(Pidgey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pidgey),
      BACK_COORD(0x88,0),
      //PALETTES(Pidgey),
      PIC_DATA_ICON_INDEX(Pidgey,0),
      //ICON(Pidgey, 0),
      .enemyMonElevation = 0,
    }, //Pidgey,
[SPECIES_PIDGEOTTO] = 
    {  
      //FRONT_PIC(Pidgeotto),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pidgeotto),
      BACK_COORD(0x88,0),
      //PALETTES(Pidgeotto),
      PIC_DATA_ICON_INDEX(Pidgeotto,0),
      //ICON(Pidgeotto, 0),
      .enemyMonElevation = 0,
    }, //Pidgeotto,
[SPECIES_PIDGEOT] = 
    {  
      //FRONT_PIC(Pidgeot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pidgeot),
      BACK_COORD(0x88,0),
      //PALETTES(Pidgeot),
      PIC_DATA_ICON_INDEX(Pidgeot,0),
      //ICON(Pidgeot, 0),
      .enemyMonElevation = 0,
    }, //Pidgeot,
[SPECIES_RATTATA] = 
    {  
      //FRONT_PIC(Rattata),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rattata),
      BACK_COORD(0x88,0),
      //PALETTES(Rattata),
      PIC_DATA_ICON_INDEX(Rattata,0),
      //ICON(Rattata, 0),
      .enemyMonElevation = 0,
    }, //Rattata,
[SPECIES_RATICATE] = 
    {  
      //FRONT_PIC(Raticate),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Raticate),
      BACK_COORD(0x88,0),
      //PALETTES(Raticate),
      PIC_DATA_ICON_INDEX(Raticate,0),
      //ICON(Raticate, 0),
      .enemyMonElevation = 0,
    }, //Raticate,
[SPECIES_SPEAROW] = 
    {  
      //FRONT_PIC(Spearow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spearow),
      BACK_COORD(0x88,0),
      //PALETTES(Spearow),
      PIC_DATA_ICON_INDEX(Spearow,0),
      //ICON(Spearow, 0),
      .enemyMonElevation = 0,
    }, //Spearow,
[SPECIES_FEAROW] = 
    {  
      //FRONT_PIC(Fearow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fearow),
      BACK_COORD(0x88,0),
      //PALETTES(Fearow),
      PIC_DATA_ICON_INDEX(Fearow,0),
      //ICON(Fearow, 0),
      .enemyMonElevation = 0,
    }, //Fearow,
[SPECIES_EKANS] = 
    {  
      //FRONT_PIC(Ekans),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ekans),
      BACK_COORD(0x88,0),
      //PALETTES(Ekans),
      PIC_DATA_ICON_INDEX(Ekans,0),
      //ICON(Ekans, 0),
      .enemyMonElevation = 0,
    }, //Ekans,
[SPECIES_ARBOK] = 
    {  
      //FRONT_PIC(Arbok),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arbok),
      BACK_COORD(0x88,0),
      //PALETTES(Arbok),
      PIC_DATA_ICON_INDEX(Arbok,0),
      //ICON(Arbok, 0),
      .enemyMonElevation = 0,
    }, //Arbok,
[SPECIES_PIKACHU] = 
    {  
      //FRONT_PIC(Pikachu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pikachu),
      BACK_COORD(0x88,0),
      //PALETTES(Pikachu),
      PIC_DATA_ICON_INDEX(Pikachu,0),
      //ICON(Pikachu, 0),
      .enemyMonElevation = 0,
    }, //Pikachu,
[SPECIES_RAICHU] = 
    {  
      //FRONT_PIC(Raichu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Raichu),
      BACK_COORD(0x88,0),
      //PALETTES(Raichu),
      PIC_DATA_ICON_INDEX(Raichu,0),
      //ICON(Raichu, 0),
      .enemyMonElevation = 0,
    }, //Raichu,
[SPECIES_SANDSHREW] = 
    {  
      //FRONT_PIC(Sandshrew),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sandshrew),
      BACK_COORD(0x88,0),
      //PALETTES(Sandshrew),
      PIC_DATA_ICON_INDEX(Sandshrew,0),
      //ICON(Sandshrew, 0),
      .enemyMonElevation = 0,
    }, //Sandshrew,
[SPECIES_SANDSLASH] = 
    {  
      //FRONT_PIC(Sandslash),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sandslash),
      BACK_COORD(0x88,0),
      //PALETTES(Sandslash),
      PIC_DATA_ICON_INDEX(Sandslash,0),
      //ICON(Sandslash, 0),
      .enemyMonElevation = 0,
    }, //Sandslash,
[SPECIES_NIDORAN_F] = 
    {  
      //FRONT_PIC(NidoranF),
      FRONT_COORD(0x88,0),
      //BACK_PIC(NidoranF),
      BACK_COORD(0x88,0),
      //PALETTES(NidoranF),
      PIC_DATA_ICON_INDEX(NidoranF,0),
      //ICON(NidoranF, 0),
      .enemyMonElevation = 0,
    }, //NidoranF,
[SPECIES_NIDORINA] = 
    {  
      //FRONT_PIC(Nidorina),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nidorina),
      BACK_COORD(0x88,0),
      //PALETTES(Nidorina),
      PIC_DATA_ICON_INDEX(Nidorina,0),
      //ICON(Nidorina, 0),
      .enemyMonElevation = 0,
    }, //Nidorina,
[SPECIES_NIDOQUEEN] = 
    {  
      //FRONT_PIC(Nidoqueen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nidoqueen),
      BACK_COORD(0x88,0),
      //PALETTES(Nidoqueen),
      PIC_DATA_ICON_INDEX(Nidoqueen,0),
      //ICON(Nidoqueen, 0),
      .enemyMonElevation = 0,
    }, //Nidoqueen,
[SPECIES_NIDORAN_M] = 
    {  
      //FRONT_PIC(NidoranM),
      FRONT_COORD(0x88,0),
      //BACK_PIC(NidoranM),
      BACK_COORD(0x88,0),
      //PALETTES(NidoranM),
      PIC_DATA_ICON_INDEX(NidoranM,0),
      //ICON(NidoranM, 0),
      .enemyMonElevation = 0,
    }, //NidoranM,
[SPECIES_NIDORINO] = 
    {  
      //FRONT_PIC(Nidorino),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nidorino),
      BACK_COORD(0x88,0),
      //PALETTES(Nidorino),
      PIC_DATA_ICON_INDEX(Nidorino,0),
      //ICON(Nidorino, 0),
      .enemyMonElevation = 0,
    }, //Nidorino,
[SPECIES_NIDOKING] = 
    {  
      //FRONT_PIC(Nidoking),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nidoking),
      BACK_COORD(0x88,0),
      //PALETTES(Nidoking),
      PIC_DATA_ICON_INDEX(Nidoking,0),
      //ICON(Nidoking, 0),
      .enemyMonElevation = 0,
    }, //Nidoking,
[SPECIES_CLEFAIRY] = 
    {  
      //FRONT_PIC(Clefairy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clefairy),
      BACK_COORD(0x88,0),
      //PALETTES(Clefairy),
      PIC_DATA_ICON_INDEX(Clefairy,0),
      //ICON(Clefairy, 0),
      .enemyMonElevation = 0,
    }, //Clefairy,
[SPECIES_CLEFABLE] = 
    {  
      //FRONT_PIC(Clefable),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clefable),
      BACK_COORD(0x88,0),
      //PALETTES(Clefable),
      PIC_DATA_ICON_INDEX(Clefable,0),
      //ICON(Clefable, 0),
      .enemyMonElevation = 0,
    }, //Clefable,
[SPECIES_VULPIX] = 
    {  
      //FRONT_PIC(Vulpix),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vulpix),
      BACK_COORD(0x88,0),
      //PALETTES(Vulpix),
      PIC_DATA_ICON_INDEX(Vulpix,0),
      //ICON(Vulpix, 0),
      .enemyMonElevation = 0,
    }, //Vulpix,
[SPECIES_NINETALES] = 
    {  
      //FRONT_PIC(Ninetales),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ninetales),
      BACK_COORD(0x88,0),
      //PALETTES(Ninetales),
      PIC_DATA_ICON_INDEX(Ninetales,0),
      //ICON(Ninetales, 0),
      .enemyMonElevation = 0,
    }, //Ninetales,
[SPECIES_JIGGLYPUFF] = 
    {  
      //FRONT_PIC(Jigglypuff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Jigglypuff),
      BACK_COORD(0x88,0),
      //PALETTES(Jigglypuff),
      PIC_DATA_ICON_INDEX(Jigglypuff,0),
      //ICON(Jigglypuff, 0),
      .enemyMonElevation = 0,
    }, //Jigglypuff,
[SPECIES_WIGGLYTUFF] = 
    {  
      //FRONT_PIC(Wigglytuff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wigglytuff),
      BACK_COORD(0x88,0),
      //PALETTES(Wigglytuff),
      PIC_DATA_ICON_INDEX(Wigglytuff,0),
      //ICON(Wigglytuff, 0),
      .enemyMonElevation = 0,
    }, //Wigglytuff,
[SPECIES_ZUBAT] = 
    {  
      //FRONT_PIC(Zubat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zubat),
      BACK_COORD(0x88,0),
      //PALETTES(Zubat),
      PIC_DATA_ICON_INDEX(Zubat,0),
      //ICON(Zubat, 0),
      .enemyMonElevation = 0,
    }, //Zubat,
[SPECIES_GOLBAT] = 
    {  
      //FRONT_PIC(Golbat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Golbat),
      BACK_COORD(0x88,0),
      //PALETTES(Golbat),
      PIC_DATA_ICON_INDEX(Golbat,0),
      //ICON(Golbat, 0),
      .enemyMonElevation = 0,
    }, //Golbat,
[SPECIES_ODDISH] = 
    {  
      //FRONT_PIC(Oddish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Oddish),
      BACK_COORD(0x88,0),
      //PALETTES(Oddish),
      PIC_DATA_ICON_INDEX(Oddish,0),
      //ICON(Oddish, 0),
      .enemyMonElevation = 0,
    }, //Oddish,
[SPECIES_GLOOM] = 
    {  
      //FRONT_PIC(Gloom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gloom),
      BACK_COORD(0x88,0),
      //PALETTES(Gloom),
      PIC_DATA_ICON_INDEX(Gloom,0),
      //ICON(Gloom, 0),
      .enemyMonElevation = 0,
    }, //Gloom,
[SPECIES_VILEPLUME] = 
    {  
      //FRONT_PIC(Vileplume),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vileplume),
      BACK_COORD(0x88,0),
      //PALETTES(Vileplume),
      PIC_DATA_ICON_INDEX(Vileplume,0),
      //ICON(Vileplume, 0),
      .enemyMonElevation = 0,
    }, //Vileplume,
[SPECIES_PARAS] = 
    {  
      //FRONT_PIC(Paras),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Paras),
      BACK_COORD(0x88,0),
      //PALETTES(Paras),
      PIC_DATA_ICON_INDEX(Paras,0),
      //ICON(Paras, 0),
      .enemyMonElevation = 0,
    }, //Paras,
[SPECIES_PARASECT] = 
    {  
      //FRONT_PIC(Parasect),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Parasect),
      BACK_COORD(0x88,0),
      //PALETTES(Parasect),
      PIC_DATA_ICON_INDEX(Parasect,0),
      //ICON(Parasect, 0),
      .enemyMonElevation = 0,
    }, //Parasect,
[SPECIES_VENONAT] = 
    {  
      //FRONT_PIC(Venonat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Venonat),
      BACK_COORD(0x88,0),
      //PALETTES(Venonat),
      PIC_DATA_ICON_INDEX(Venonat,0),
      //ICON(Venonat, 0),
      .enemyMonElevation = 0,
    }, //Venonat,
[SPECIES_VENOMOTH] = 
    {  
      //FRONT_PIC(Venomoth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Venomoth),
      BACK_COORD(0x88,0),
      //PALETTES(Venomoth),
      PIC_DATA_ICON_INDEX(Venomoth,0),
      //ICON(Venomoth, 0),
      .enemyMonElevation = 0,
    }, //Venomoth,
[SPECIES_DIGLETT] = 
    {  
      //FRONT_PIC(Diglett),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Diglett),
      BACK_COORD(0x88,0),
      //PALETTES(Diglett),
      PIC_DATA_ICON_INDEX(Diglett,0),
      //ICON(Diglett, 0),
      .enemyMonElevation = 0,
    }, //Diglett,
[SPECIES_DUGTRIO] = 
    {  
      //FRONT_PIC(Dugtrio),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dugtrio),
      BACK_COORD(0x88,0),
      //PALETTES(Dugtrio),
      PIC_DATA_ICON_INDEX(Dugtrio,0),
      //ICON(Dugtrio, 0),
      .enemyMonElevation = 0,
    }, //Dugtrio,
[SPECIES_MEOWTH] = 
    {  
      //FRONT_PIC(Meowth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Meowth),
      BACK_COORD(0x88,0),
      //PALETTES(Meowth),
      PIC_DATA_ICON_INDEX(Meowth,0),
      //ICON(Meowth, 0),
      .enemyMonElevation = 0,
    }, //Meowth,
[SPECIES_PERSIAN] = 
    {  
      //FRONT_PIC(Persian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Persian),
      BACK_COORD(0x88,0),
      //PALETTES(Persian),
      PIC_DATA_ICON_INDEX(Persian,0),
      //ICON(Persian, 0),
      .enemyMonElevation = 0,
    }, //Persian,
[SPECIES_PSYDUCK] = 
    {  
      //FRONT_PIC(Psyduck),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Psyduck),
      BACK_COORD(0x88,0),
      //PALETTES(Psyduck),
      PIC_DATA_ICON_INDEX(Psyduck,0),
      //ICON(Psyduck, 0),
      .enemyMonElevation = 0,
    }, //Psyduck,
[SPECIES_GOLDUCK] = 
    {  
      //FRONT_PIC(Golduck),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Golduck),
      BACK_COORD(0x88,0),
      //PALETTES(Golduck),
      PIC_DATA_ICON_INDEX(Golduck,0),
      //ICON(Golduck, 0),
      .enemyMonElevation = 0,
    }, //Golduck,
[SPECIES_MANKEY] = 
    {  
      //FRONT_PIC(Mankey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mankey),
      BACK_COORD(0x88,0),
      //PALETTES(Mankey),
      PIC_DATA_ICON_INDEX(Mankey,0),
      //ICON(Mankey, 0),
      .enemyMonElevation = 0,
    }, //Mankey,
[SPECIES_PRIMEAPE] = 
    {  
      //FRONT_PIC(Primeape),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Primeape),
      BACK_COORD(0x88,0),
      //PALETTES(Primeape),
      PIC_DATA_ICON_INDEX(Primeape,0),
      //ICON(Primeape, 0),
      .enemyMonElevation = 0,
    }, //Primeape,
[SPECIES_GROWLITHE] = 
    {  
      //FRONT_PIC(Growlithe),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Growlithe),
      BACK_COORD(0x88,0),
      //PALETTES(Growlithe),
      PIC_DATA_ICON_INDEX(Growlithe,0),
      //ICON(Growlithe, 0),
      .enemyMonElevation = 0,
    }, //Growlithe,
[SPECIES_ARCANINE] = 
    {  
      //FRONT_PIC(Arcanine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arcanine),
      BACK_COORD(0x88,0),
      //PALETTES(Arcanine),
      PIC_DATA_ICON_INDEX(Arcanine,0),
      //ICON(Arcanine, 0),
      .enemyMonElevation = 0,
    }, //Arcanine,
[SPECIES_POLIWAG] = 
    {  
      //FRONT_PIC(Poliwag),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Poliwag),
      BACK_COORD(0x88,0),
      //PALETTES(Poliwag),
      PIC_DATA_ICON_INDEX(Poliwag,0),
      //ICON(Poliwag, 0),
      .enemyMonElevation = 0,
    }, //Poliwag,
[SPECIES_POLIWHIRL] = 
    {  
      //FRONT_PIC(Poliwhirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Poliwhirl),
      BACK_COORD(0x88,0),
      //PALETTES(Poliwhirl),
      PIC_DATA_ICON_INDEX(Poliwhirl,0),
      //ICON(Poliwhirl, 0),
      .enemyMonElevation = 0,
    }, //Poliwhirl,
[SPECIES_POLIWRATH] = 
    {  
      //FRONT_PIC(Poliwrath),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Poliwrath),
      BACK_COORD(0x88,0),
      //PALETTES(Poliwrath),
      PIC_DATA_ICON_INDEX(Poliwrath,0),
      //ICON(Poliwrath, 0),
      .enemyMonElevation = 0,
    }, //Poliwrath,
[SPECIES_ABRA] = 
    {  
      //FRONT_PIC(Abra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Abra),
      BACK_COORD(0x88,0),
      //PALETTES(Abra),
      PIC_DATA_ICON_INDEX(Abra,0),
      //ICON(Abra, 0),
      .enemyMonElevation = 0,
    }, //Abra,
[SPECIES_KADABRA] = 
    {  
      //FRONT_PIC(Kadabra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kadabra),
      BACK_COORD(0x88,0),
      //PALETTES(Kadabra),
      PIC_DATA_ICON_INDEX(Kadabra,0),
      //ICON(Kadabra, 0),
      .enemyMonElevation = 0,
    }, //Kadabra,
[SPECIES_ALAKAZAM] = 
    {  
      //FRONT_PIC(Alakazam),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Alakazam),
      BACK_COORD(0x88,0),
      //PALETTES(Alakazam),
      PIC_DATA_ICON_INDEX(Alakazam,0),
      //ICON(Alakazam, 0),
      .enemyMonElevation = 0,
    }, //Alakazam,
[SPECIES_MACHOP] = 
    {  
      //FRONT_PIC(Machop),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Machop),
      BACK_COORD(0x88,0),
      //PALETTES(Machop),
      PIC_DATA_ICON_INDEX(Machop,0),
      //ICON(Machop, 0),
      .enemyMonElevation = 0,
    }, //Machop,
[SPECIES_MACHOKE] = 
    {  
      //FRONT_PIC(Machoke),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Machoke),
      BACK_COORD(0x88,0),
      //PALETTES(Machoke),
      PIC_DATA_ICON_INDEX(Machoke,0),
      //ICON(Machoke, 0),
      .enemyMonElevation = 0,
    }, //Machoke,
[SPECIES_MACHAMP] = 
    {  
      //FRONT_PIC(Machamp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Machamp),
      BACK_COORD(0x88,0),
      //PALETTES(Machamp),
      PIC_DATA_ICON_INDEX(Machamp,0),
      //ICON(Machamp, 0),
      .enemyMonElevation = 0,
    }, //Machamp,
[SPECIES_BELLSPROUT] = 
    {  
      //FRONT_PIC(Bellsprout),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bellsprout),
      BACK_COORD(0x88,0),
      //PALETTES(Bellsprout),
      PIC_DATA_ICON_INDEX(Bellsprout,0),
      //ICON(Bellsprout, 0),
      .enemyMonElevation = 0,
    }, //Bellsprout,
[SPECIES_WEEPINBELL] = 
    {  
      //FRONT_PIC(Weepinbell),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Weepinbell),
      BACK_COORD(0x88,0),
      //PALETTES(Weepinbell),
      PIC_DATA_ICON_INDEX(Weepinbell,0),
      //ICON(Weepinbell, 0),
      .enemyMonElevation = 0,
    }, //Weepinbell,
[SPECIES_VICTREEBEL] = 
    {  
      //FRONT_PIC(Victreebel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Victreebel),
      BACK_COORD(0x88,0),
      //PALETTES(Victreebel),
      PIC_DATA_ICON_INDEX(Victreebel,0),
      //ICON(Victreebel, 0),
      .enemyMonElevation = 0,
    }, //Victreebel,
[SPECIES_TENTACOOL] = 
    {  
      //FRONT_PIC(Tentacool),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tentacool),
      BACK_COORD(0x88,0),
      //PALETTES(Tentacool),
      PIC_DATA_ICON_INDEX(Tentacool,0),
      //ICON(Tentacool, 0),
      .enemyMonElevation = 0,
    }, //Tentacool,
[SPECIES_TENTACRUEL] = 
    {  
      //FRONT_PIC(Tentacruel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tentacruel),
      BACK_COORD(0x88,0),
      //PALETTES(Tentacruel),
      PIC_DATA_ICON_INDEX(Tentacruel,0),
      //ICON(Tentacruel, 0),
      .enemyMonElevation = 0,
    }, //Tentacruel,
[SPECIES_GEODUDE] = 
    {  
      //FRONT_PIC(Geodude),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Geodude),
      BACK_COORD(0x88,0),
      //PALETTES(Geodude),
      PIC_DATA_ICON_INDEX(Geodude,0),
      //ICON(Geodude, 0),
      .enemyMonElevation = 0,
    }, //Geodude,
[SPECIES_GRAVELER] = 
    {  
      //FRONT_PIC(Graveler),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Graveler),
      BACK_COORD(0x88,0),
      //PALETTES(Graveler),
      PIC_DATA_ICON_INDEX(Graveler,0),
      //ICON(Graveler, 0),
      .enemyMonElevation = 0,
    }, //Graveler,
[SPECIES_GOLEM] = 
    {  
      //FRONT_PIC(Golem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Golem),
      BACK_COORD(0x88,0),
      //PALETTES(Golem),
      PIC_DATA_ICON_INDEX(Golem,0),
      //ICON(Golem, 0),
      .enemyMonElevation = 0,
    }, //Golem,
[SPECIES_PONYTA] = 
    {  
      //FRONT_PIC(Ponyta),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ponyta),
      BACK_COORD(0x88,0),
      //PALETTES(Ponyta),
      PIC_DATA_ICON_INDEX(Ponyta,0),
      //ICON(Ponyta, 0),
      .enemyMonElevation = 0,
    }, //Ponyta,
[SPECIES_RAPIDASH] = 
    {  
      //FRONT_PIC(Rapidash),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rapidash),
      BACK_COORD(0x88,0),
      //PALETTES(Rapidash),
      PIC_DATA_ICON_INDEX(Rapidash,0),
      //ICON(Rapidash, 0),
      .enemyMonElevation = 0,
    }, //Rapidash,
[SPECIES_SLOWPOKE] = 
    {  
      //FRONT_PIC(Slowpoke),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slowpoke),
      BACK_COORD(0x88,0),
      //PALETTES(Slowpoke),
      PIC_DATA_ICON_INDEX(Slowpoke,0),
      //ICON(Slowpoke, 0),
      .enemyMonElevation = 0,
    }, //Slowpoke,
[SPECIES_SLOWBRO] = 
    {  
      //FRONT_PIC(Slowbro),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slowbro),
      BACK_COORD(0x88,0),
      //PALETTES(Slowbro),
      PIC_DATA_ICON_INDEX(Slowbro,0),
      //ICON(Slowbro, 0),
      .enemyMonElevation = 0,
    }, //Slowbro,
[SPECIES_MAGNEMITE] = 
    {  
      //FRONT_PIC(Magnemite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magnemite),
      BACK_COORD(0x88,0),
      //PALETTES(Magnemite),
      PIC_DATA_ICON_INDEX(Magnemite,0),
      //ICON(Magnemite, 0),
      .enemyMonElevation = 0,
    }, //Magnemite,
[SPECIES_MAGNETON] = 
    {  
      //FRONT_PIC(Magneton),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magneton),
      BACK_COORD(0x88,0),
      //PALETTES(Magneton),
      PIC_DATA_ICON_INDEX(Magneton,0),
      //ICON(Magneton, 0),
      .enemyMonElevation = 0,
    }, //Magneton,
[SPECIES_FARFETCHD] = 
    {  
      //FRONT_PIC(Farfetchd),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Farfetchd),
      BACK_COORD(0x88,0),
      //PALETTES(Farfetchd),
      PIC_DATA_ICON_INDEX(Farfetchd,0),
      //ICON(Farfetchd, 0),
      .enemyMonElevation = 0,
    }, //Farfetchd,
[SPECIES_DODUO] = 
    {  
      //FRONT_PIC(Doduo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Doduo),
      BACK_COORD(0x88,0),
      //PALETTES(Doduo),
      PIC_DATA_ICON_INDEX(Doduo,0),
      //ICON(Doduo, 0),
      .enemyMonElevation = 0,
    }, //Doduo,
[SPECIES_DODRIO] = 
    {  
      //FRONT_PIC(Dodrio),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dodrio),
      BACK_COORD(0x88,0),
      //PALETTES(Dodrio),
      PIC_DATA_ICON_INDEX(Dodrio,0),
      //ICON(Dodrio, 0),
      .enemyMonElevation = 0,
    }, //Dodrio,
[SPECIES_SEEL] = 
    {  
      //FRONT_PIC(Seel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Seel),
      BACK_COORD(0x88,0),
      //PALETTES(Seel),
      PIC_DATA_ICON_INDEX(Seel,0),
      //ICON(Seel, 0),
      .enemyMonElevation = 0,
    }, //Seel,
[SPECIES_DEWGONG] = 
    {  
      //FRONT_PIC(Dewgong),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dewgong),
      BACK_COORD(0x88,0),
      //PALETTES(Dewgong),
      PIC_DATA_ICON_INDEX(Dewgong,0),
      //ICON(Dewgong, 0),
      .enemyMonElevation = 0,
    }, //Dewgong,
[SPECIES_GRIMER] = 
    {  
      //FRONT_PIC(Grimer),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grimer),
      BACK_COORD(0x88,0),
      //PALETTES(Grimer),
      PIC_DATA_ICON_INDEX(Grimer,0),
      //ICON(Grimer, 0),
      .enemyMonElevation = 0,
    }, //Grimer,
[SPECIES_MUK] = 
    {  
      //FRONT_PIC(Muk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Muk),
      BACK_COORD(0x88,0),
      //PALETTES(Muk),
      PIC_DATA_ICON_INDEX(Muk,0),
      //ICON(Muk, 0),
      .enemyMonElevation = 0,
    }, //Muk,
[SPECIES_SHELLDER] = 
    {  
      //FRONT_PIC(Shellder),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shellder),
      BACK_COORD(0x88,0),
      //PALETTES(Shellder),
      PIC_DATA_ICON_INDEX(Shellder,0),
      //ICON(Shellder, 0),
      .enemyMonElevation = 0,
    }, //Shellder,
[SPECIES_CLOYSTER] = 
    {  
      //FRONT_PIC(Cloyster),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cloyster),
      BACK_COORD(0x88,0),
      //PALETTES(Cloyster),
      PIC_DATA_ICON_INDEX(Cloyster,0),
      //ICON(Cloyster, 0),
      .enemyMonElevation = 0,
    }, //Cloyster,
[SPECIES_GASTLY] = 
    {  
      //FRONT_PIC(Gastly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gastly),
      BACK_COORD(0x88,0),
      //PALETTES(Gastly),
      PIC_DATA_ICON_INDEX(Gastly,0),
      //ICON(Gastly, 0),
      .enemyMonElevation = 0,
    }, //Gastly,
[SPECIES_HAUNTER] = 
    {  
      //FRONT_PIC(Haunter),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Haunter),
      BACK_COORD(0x88,0),
      //PALETTES(Haunter),
      PIC_DATA_ICON_INDEX(Haunter,0),
      //ICON(Haunter, 0),
      .enemyMonElevation = 0,
    }, //Haunter,
[SPECIES_GENGAR] = 
    {  
      //FRONT_PIC(Gengar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gengar),
      BACK_COORD(0x88,0),
      //PALETTES(Gengar),
      PIC_DATA_ICON_INDEX(Gengar,0),
      //ICON(Gengar, 0),
      .enemyMonElevation = 0,
    }, //Gengar,
[SPECIES_ONIX] = 
    {  
      //FRONT_PIC(Onix),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Onix),
      BACK_COORD(0x88,0),
      //PALETTES(Onix),
      PIC_DATA_ICON_INDEX(Onix,0),
      //ICON(Onix, 0),
      .enemyMonElevation = 0,
    }, //Onix,
[SPECIES_DROWZEE] = 
    {  
      //FRONT_PIC(Drowzee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drowzee),
      BACK_COORD(0x88,0),
      //PALETTES(Drowzee),
      PIC_DATA_ICON_INDEX(Drowzee,0),
      //ICON(Drowzee, 0),
      .enemyMonElevation = 0,
    }, //Drowzee,
[SPECIES_HYPNO] = 
    {  
      //FRONT_PIC(Hypno),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hypno),
      BACK_COORD(0x88,0),
      //PALETTES(Hypno),
      PIC_DATA_ICON_INDEX(Hypno,0),
      //ICON(Hypno, 0),
      .enemyMonElevation = 0,
    }, //Hypno,
[SPECIES_KRABBY] = 
    {  
      //FRONT_PIC(Krabby),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Krabby),
      BACK_COORD(0x88,0),
      //PALETTES(Krabby),
      PIC_DATA_ICON_INDEX(Krabby,0),
      //ICON(Krabby, 0),
      .enemyMonElevation = 0,
    }, //Krabby,
[SPECIES_KINGLER] = 
    {  
      //FRONT_PIC(Kingler),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kingler),
      BACK_COORD(0x88,0),
      //PALETTES(Kingler),
      PIC_DATA_ICON_INDEX(Kingler,0),
      //ICON(Kingler, 0),
      .enemyMonElevation = 0,
    }, //Kingler,
[SPECIES_VOLTORB] = 
    {  
      //FRONT_PIC(Voltorb),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Voltorb),
      BACK_COORD(0x88,0),
      //PALETTES(Voltorb),
      PIC_DATA_ICON_INDEX(Voltorb,0),
      //ICON(Voltorb, 0),
      .enemyMonElevation = 0,
    }, //Voltorb,
[SPECIES_ELECTRODE] = 
    {  
      //FRONT_PIC(Electrode),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Electrode),
      BACK_COORD(0x88,0),
      //PALETTES(Electrode),
      PIC_DATA_ICON_INDEX(Electrode,0),
      //ICON(Electrode, 0),
      .enemyMonElevation = 0,
    }, //Electrode,
[SPECIES_EXEGGCUTE] = 
    {  
      //FRONT_PIC(Exeggcute),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Exeggcute),
      BACK_COORD(0x88,0),
      //PALETTES(Exeggcute),
      PIC_DATA_ICON_INDEX(Exeggcute,0),
      //ICON(Exeggcute, 0),
      .enemyMonElevation = 0,
    }, //Exeggcute,
[SPECIES_EXEGGUTOR] = 
    {  
      //FRONT_PIC(Exeggutor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Exeggutor),
      BACK_COORD(0x88,0),
      //PALETTES(Exeggutor),
      PIC_DATA_ICON_INDEX(Exeggutor,0),
      //ICON(Exeggutor, 0),
      .enemyMonElevation = 0,
    }, //Exeggutor,
[SPECIES_CUBONE] = 
    {  
      //FRONT_PIC(Cubone),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cubone),
      BACK_COORD(0x88,0),
      //PALETTES(Cubone),
      PIC_DATA_ICON_INDEX(Cubone,0),
      //ICON(Cubone, 0),
      .enemyMonElevation = 0,
    }, //Cubone,
[SPECIES_MAROWAK] = 
    {  
      //FRONT_PIC(Marowak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Marowak),
      BACK_COORD(0x88,0),
      //PALETTES(Marowak),
      PIC_DATA_ICON_INDEX(Marowak,0),
      //ICON(Marowak, 0),
      .enemyMonElevation = 0,
    }, //Marowak,
[SPECIES_HITMONLEE] = 
    {  
      //FRONT_PIC(Hitmonlee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hitmonlee),
      BACK_COORD(0x88,0),
      //PALETTES(Hitmonlee),
      PIC_DATA_ICON_INDEX(Hitmonlee,0),
      //ICON(Hitmonlee, 0),
      .enemyMonElevation = 0,
    }, //Hitmonlee,
[SPECIES_HITMONCHAN] = 
    {  
      //FRONT_PIC(Hitmonchan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hitmonchan),
      BACK_COORD(0x88,0),
      //PALETTES(Hitmonchan),
      PIC_DATA_ICON_INDEX(Hitmonchan,0),
      //ICON(Hitmonchan, 0),
      .enemyMonElevation = 0,
    }, //Hitmonchan,
[SPECIES_LICKITUNG] = 
    {  
      //FRONT_PIC(Lickitung),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lickitung),
      BACK_COORD(0x88,0),
      //PALETTES(Lickitung),
      PIC_DATA_ICON_INDEX(Lickitung,0),
      //ICON(Lickitung, 0),
      .enemyMonElevation = 0,
    }, //Lickitung,
[SPECIES_KOFFING] = 
    {  
      //FRONT_PIC(Koffing),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Koffing),
      BACK_COORD(0x88,0),
      //PALETTES(Koffing),
      PIC_DATA_ICON_INDEX(Koffing,0),
      //ICON(Koffing, 0),
      .enemyMonElevation = 0,
    }, //Koffing,
[SPECIES_WEEZING] = 
    {  
      //FRONT_PIC(Weezing),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Weezing),
      BACK_COORD(0x88,0),
      //PALETTES(Weezing),
      PIC_DATA_ICON_INDEX(Weezing,0),
      //ICON(Weezing, 0),
      .enemyMonElevation = 0,
    }, //Weezing,
[SPECIES_RHYHORN] = 
    {  
      //FRONT_PIC(Rhyhorn),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rhyhorn),
      BACK_COORD(0x88,0),
      //PALETTES(Rhyhorn),
      PIC_DATA_ICON_INDEX(Rhyhorn,0),
      //ICON(Rhyhorn, 0),
      .enemyMonElevation = 0,
    }, //Rhyhorn,
[SPECIES_RHYDON] = 
    {  
      //FRONT_PIC(Rhydon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rhydon),
      BACK_COORD(0x88,0),
      //PALETTES(Rhydon),
      PIC_DATA_ICON_INDEX(Rhydon,0),
      //ICON(Rhydon, 0),
      .enemyMonElevation = 0,
    }, //Rhydon,
[SPECIES_CHANSEY] = 
    {  
      //FRONT_PIC(Chansey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chansey),
      BACK_COORD(0x88,0),
      //PALETTES(Chansey),
      PIC_DATA_ICON_INDEX(Chansey,0),
      //ICON(Chansey, 0),
      .enemyMonElevation = 0,
    }, //Chansey,
[SPECIES_TANGELA] = 
    {  
      //FRONT_PIC(Tangela),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tangela),
      BACK_COORD(0x88,0),
      //PALETTES(Tangela),
      PIC_DATA_ICON_INDEX(Tangela,0),
      //ICON(Tangela, 0),
      .enemyMonElevation = 0,
    }, //Tangela,
[SPECIES_KANGASKHAN] = 
    {  
      //FRONT_PIC(Kangaskhan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kangaskhan),
      BACK_COORD(0x88,0),
      //PALETTES(Kangaskhan),
      PIC_DATA_ICON_INDEX(Kangaskhan,0),
      //ICON(Kangaskhan, 0),
      .enemyMonElevation = 0,
    }, //Kangaskhan,
[SPECIES_HORSEA] = 
    {  
      //FRONT_PIC(Horsea),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Horsea),
      BACK_COORD(0x88,0),
      //PALETTES(Horsea),
      PIC_DATA_ICON_INDEX(Horsea,0),
      //ICON(Horsea, 0),
      .enemyMonElevation = 0,
    }, //Horsea,
[SPECIES_SEADRA] = 
    {  
      //FRONT_PIC(Seadra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Seadra),
      BACK_COORD(0x88,0),
      //PALETTES(Seadra),
      PIC_DATA_ICON_INDEX(Seadra,0),
      //ICON(Seadra, 0),
      .enemyMonElevation = 0,
    }, //Seadra,
[SPECIES_GOLDEEN] = 
    {  
      //FRONT_PIC(Goldeen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Goldeen),
      BACK_COORD(0x88,0),
      //PALETTES(Goldeen),
      PIC_DATA_ICON_INDEX(Goldeen,0),
      //ICON(Goldeen, 0),
      .enemyMonElevation = 0,
    }, //Goldeen,
[SPECIES_SEAKING] = 
    {  
      //FRONT_PIC(Seaking),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Seaking),
      BACK_COORD(0x88,0),
      //PALETTES(Seaking),
      PIC_DATA_ICON_INDEX(Seaking,0),
      //ICON(Seaking, 0),
      .enemyMonElevation = 0,
    }, //Seaking,
[SPECIES_STARYU] = 
    {  
      //FRONT_PIC(Staryu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Staryu),
      BACK_COORD(0x88,0),
      //PALETTES(Staryu),
      PIC_DATA_ICON_INDEX(Staryu,0),
      //ICON(Staryu, 0),
      .enemyMonElevation = 0,
    }, //Staryu,
[SPECIES_STARMIE] = 
    {  
      //FRONT_PIC(Starmie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Starmie),
      BACK_COORD(0x88,0),
      //PALETTES(Starmie),
      PIC_DATA_ICON_INDEX(Starmie,0),
      //ICON(Starmie, 0),
      .enemyMonElevation = 0,
    }, //Starmie,
[SPECIES_MR_MIME] = 
    {  
      //FRONT_PIC(MrMime),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MrMime),
      BACK_COORD(0x88,0),
      //PALETTES(MrMime),
      PIC_DATA_ICON_INDEX(MrMime,0),
      //ICON(MrMime, 0),
      .enemyMonElevation = 0,
    }, //MrMime,
[SPECIES_SCYTHER] = 
    {  
      //FRONT_PIC(Scyther),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scyther),
      BACK_COORD(0x88,0),
      //PALETTES(Scyther),
      PIC_DATA_ICON_INDEX(Scyther,0),
      //ICON(Scyther, 0),
      .enemyMonElevation = 0,
    }, //Scyther,
[SPECIES_JYNX] = 
    {  
      //FRONT_PIC(Jynx),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Jynx),
      BACK_COORD(0x88,0),
      //PALETTES(Jynx),
      PIC_DATA_ICON_INDEX(Jynx,0),
      //ICON(Jynx, 0),
      .enemyMonElevation = 0,
    }, //Jynx,
[SPECIES_ELECTABUZZ] = 
    {  
      //FRONT_PIC(Electabuzz),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Electabuzz),
      BACK_COORD(0x88,0),
      //PALETTES(Electabuzz),
      PIC_DATA_ICON_INDEX(Electabuzz,0),
      //ICON(Electabuzz, 0),
      .enemyMonElevation = 0,
    }, //Electabuzz,
[SPECIES_MAGMAR] = 
    {  
      //FRONT_PIC(Magmar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magmar),
      BACK_COORD(0x88,0),
      //PALETTES(Magmar),
      PIC_DATA_ICON_INDEX(Magmar,0),
      //ICON(Magmar, 0),
      .enemyMonElevation = 0,
    }, //Magmar,
[SPECIES_PINSIR] = 
    {  
      //FRONT_PIC(Pinsir),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pinsir),
      BACK_COORD(0x88,0),
      //PALETTES(Pinsir),
      PIC_DATA_ICON_INDEX(Pinsir,0),
      //ICON(Pinsir, 0),
      .enemyMonElevation = 0,
    }, //Pinsir,
[SPECIES_TAUROS] = 
    {  
      //FRONT_PIC(Tauros),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tauros),
      BACK_COORD(0x88,0),
      //PALETTES(Tauros),
      PIC_DATA_ICON_INDEX(Tauros,0),
      //ICON(Tauros, 0),
      .enemyMonElevation = 0,
    }, //Tauros,
[SPECIES_MAGIKARP] = 
    {  
      //FRONT_PIC(Magikarp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magikarp),
      BACK_COORD(0x88,0),
      //PALETTES(Magikarp),
      PIC_DATA_ICON_INDEX(Magikarp,0),
      //ICON(Magikarp, 0),
      .enemyMonElevation = 0,
    }, //Magikarp,
[SPECIES_GYARADOS] = 
    {  
      //FRONT_PIC(Gyarados),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gyarados),
      BACK_COORD(0x88,0),
      //PALETTES(Gyarados),
      PIC_DATA_ICON_INDEX(Gyarados,0),
      //ICON(Gyarados, 0),
      .enemyMonElevation = 0,
    }, //Gyarados,
[SPECIES_LAPRAS] = 
    {  
      //FRONT_PIC(Lapras),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lapras),
      BACK_COORD(0x88,0),
      //PALETTES(Lapras),
      PIC_DATA_ICON_INDEX(Lapras,0),
      //ICON(Lapras, 0),
      .enemyMonElevation = 0,
    }, //Lapras,
[SPECIES_DITTO] = 
    {  
      //FRONT_PIC(Ditto),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ditto),
      BACK_COORD(0x88,0),
      //PALETTES(Ditto),
      PIC_DATA_ICON_INDEX(Ditto,0),
      //ICON(Ditto, 0),
      .enemyMonElevation = 0,
    }, //Ditto,
[SPECIES_EEVEE] = 
    {  
      //FRONT_PIC(Eevee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Eevee),
      BACK_COORD(0x88,0),
      //PALETTES(Eevee),
      PIC_DATA_ICON_INDEX(Eevee,0),
      //ICON(Eevee, 0),
      .enemyMonElevation = 0,
    }, //Eevee,
[SPECIES_VAPOREON] = 
    {  
      //FRONT_PIC(Vaporeon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vaporeon),
      BACK_COORD(0x88,0),
      //PALETTES(Vaporeon),
      PIC_DATA_ICON_INDEX(Vaporeon,0),
      //ICON(Vaporeon, 0),
      .enemyMonElevation = 0,
    }, //Vaporeon,
[SPECIES_JOLTEON] = 
    {  
      //FRONT_PIC(Jolteon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Jolteon),
      BACK_COORD(0x88,0),
      //PALETTES(Jolteon),
      PIC_DATA_ICON_INDEX(Jolteon,0),
      //ICON(Jolteon, 0),
      .enemyMonElevation = 0,
    }, //Jolteon,
[SPECIES_FLAREON] = 
    {  
      //FRONT_PIC(Flareon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flareon),
      BACK_COORD(0x88,0),
      //PALETTES(Flareon),
      PIC_DATA_ICON_INDEX(Flareon,0),
      //ICON(Flareon, 0),
      .enemyMonElevation = 0,
    }, //Flareon,
[SPECIES_PORYGON] = 
    {  
      //FRONT_PIC(Porygon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Porygon),
      BACK_COORD(0x88,0),
      //PALETTES(Porygon),
      PIC_DATA_ICON_INDEX(Porygon,0),
      //ICON(Porygon, 0),
      .enemyMonElevation = 0,
    }, //Porygon,
[SPECIES_OMANYTE] = 
    {  
      //FRONT_PIC(Omanyte),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Omanyte),
      BACK_COORD(0x88,0),
      //PALETTES(Omanyte),
      PIC_DATA_ICON_INDEX(Omanyte,0),
      //ICON(Omanyte, 0),
      .enemyMonElevation = 0,
    }, //Omanyte,
[SPECIES_OMASTAR] = 
    {  
      //FRONT_PIC(Omastar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Omastar),
      BACK_COORD(0x88,0),
      //PALETTES(Omastar),
      PIC_DATA_ICON_INDEX(Omastar,0),
      //ICON(Omastar, 0),
      .enemyMonElevation = 0,
    }, //Omastar,
[SPECIES_KABUTO] = 
    {  
      //FRONT_PIC(Kabuto),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kabuto),
      BACK_COORD(0x88,0),
      //PALETTES(Kabuto),
      PIC_DATA_ICON_INDEX(Kabuto,0),
      //ICON(Kabuto, 0),
      .enemyMonElevation = 0,
    }, //Kabuto,
[SPECIES_KABUTOPS] = 
    {  
      //FRONT_PIC(Kabutops),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kabutops),
      BACK_COORD(0x88,0),
      //PALETTES(Kabutops),
      PIC_DATA_ICON_INDEX(Kabutops,0),
      //ICON(Kabutops, 0),
      .enemyMonElevation = 0,
    }, //Kabutops,
[SPECIES_AERODACTYL] = 
    {  
      //FRONT_PIC(Aerodactyl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aerodactyl),
      BACK_COORD(0x88,0),
      //PALETTES(Aerodactyl),
      PIC_DATA_ICON_INDEX(Aerodactyl,0),
      //ICON(Aerodactyl, 0),
      .enemyMonElevation = 0,
    }, //Aerodactyl,
[SPECIES_SNORLAX] = 
    {  
      //FRONT_PIC(Snorlax),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Snorlax),
      BACK_COORD(0x88,0),
      //PALETTES(Snorlax),
      PIC_DATA_ICON_INDEX(Snorlax,0),
      //ICON(Snorlax, 0),
      .enemyMonElevation = 0,
    }, //Snorlax,
[SPECIES_ARTICUNO] = 
    {  
      //FRONT_PIC(Articuno),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Articuno),
      BACK_COORD(0x88,0),
      //PALETTES(Articuno),
      PIC_DATA_ICON_INDEX(Articuno,0),
      //ICON(Articuno, 0),
      .enemyMonElevation = 0,
    }, //Articuno,
[SPECIES_ZAPDOS] = 
    {  
      //FRONT_PIC(Zapdos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zapdos),
      BACK_COORD(0x88,0),
      //PALETTES(Zapdos),
      PIC_DATA_ICON_INDEX(Zapdos,0),
      //ICON(Zapdos, 0),
      .enemyMonElevation = 0,
    }, //Zapdos,
[SPECIES_MOLTRES] = 
    {  
      //FRONT_PIC(Moltres),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Moltres),
      BACK_COORD(0x88,0),
      //PALETTES(Moltres),
      PIC_DATA_ICON_INDEX(Moltres,0),
      //ICON(Moltres, 0),
      .enemyMonElevation = 0,
    }, //Moltres,
[SPECIES_DRATINI] = 
    {  
      //FRONT_PIC(Dratini),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dratini),
      BACK_COORD(0x88,0),
      //PALETTES(Dratini),
      PIC_DATA_ICON_INDEX(Dratini,0),
      //ICON(Dratini, 0),
      .enemyMonElevation = 0,
    }, //Dratini,
[SPECIES_DRAGONAIR] = 
    {  
      //FRONT_PIC(Dragonair),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dragonair),
      BACK_COORD(0x88,0),
      //PALETTES(Dragonair),
      PIC_DATA_ICON_INDEX(Dragonair,0),
      //ICON(Dragonair, 0),
      .enemyMonElevation = 0,
    }, //Dragonair,
[SPECIES_DRAGONITE] = 
    {  
      //FRONT_PIC(Dragonite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dragonite),
      BACK_COORD(0x88,0),
      //PALETTES(Dragonite),
      PIC_DATA_ICON_INDEX(Dragonite,0),
      //ICON(Dragonite, 0),
      .enemyMonElevation = 0,
    }, //Dragonite,
[SPECIES_MEWTWO] = 
    {  
      //FRONT_PIC(Mewtwo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mewtwo),
      BACK_COORD(0x88,0),
      //PALETTES(Mewtwo),
      PIC_DATA_ICON_INDEX(Mewtwo,0),
      //ICON(Mewtwo, 0),
      .enemyMonElevation = 0,
    }, //Mewtwo,
[SPECIES_MEW] = 
    {  
      //FRONT_PIC(Mew),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mew),
      BACK_COORD(0x88,0),
      //PALETTES(Mew),
      PIC_DATA_ICON_INDEX(Mew,0),
      //ICON(Mew, 0),
      .enemyMonElevation = 0,
    }, //Mew,
[SPECIES_CHIKORITA] = 
    {  
      //FRONT_PIC(Chikorita),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chikorita),
      BACK_COORD(0x88,0),
      //PALETTES(Chikorita),
      PIC_DATA_ICON_INDEX(Chikorita,0),
      //ICON(Chikorita, 0),
      .enemyMonElevation = 0,
    }, //Chikorita,
[SPECIES_BAYLEEF] = 
    {  
      //FRONT_PIC(Bayleef),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bayleef),
      BACK_COORD(0x88,0),
      //PALETTES(Bayleef),
      PIC_DATA_ICON_INDEX(Bayleef,0),
      //ICON(Bayleef, 0),
      .enemyMonElevation = 0,
    }, //Bayleef,
[SPECIES_MEGANIUM] = 
    {  
      //FRONT_PIC(Meganium),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Meganium),
      BACK_COORD(0x88,0),
      //PALETTES(Meganium),
      PIC_DATA_ICON_INDEX(Meganium,0),
      //ICON(Meganium, 0),
      .enemyMonElevation = 0,
    }, //Meganium,
[SPECIES_CYNDAQUIL] = 
    {  
      //FRONT_PIC(Cyndaquil),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cyndaquil),
      BACK_COORD(0x88,0),
      //PALETTES(Cyndaquil),
      PIC_DATA_ICON_INDEX(Cyndaquil,0),
      //ICON(Cyndaquil, 0),
      .enemyMonElevation = 0,
    }, //Cyndaquil,
[SPECIES_QUILAVA] = 
    {  
      //FRONT_PIC(Quilava),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Quilava),
      BACK_COORD(0x88,0),
      //PALETTES(Quilava),
      PIC_DATA_ICON_INDEX(Quilava,0),
      //ICON(Quilava, 0),
      .enemyMonElevation = 0,
    }, //Quilava,
[SPECIES_TYPHLOSION] = 
    {  
      //FRONT_PIC(Typhlosion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Typhlosion),
      BACK_COORD(0x88,0),
      //PALETTES(Typhlosion),
      PIC_DATA_ICON_INDEX(Typhlosion,0),
      //ICON(Typhlosion, 0),
      .enemyMonElevation = 0,
    }, //Typhlosion,
[SPECIES_TOTODILE] = 
    {  
      //FRONT_PIC(Totodile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Totodile),
      BACK_COORD(0x88,0),
      //PALETTES(Totodile),
      PIC_DATA_ICON_INDEX(Totodile,0),
      //ICON(Totodile, 0),
      .enemyMonElevation = 0,
    }, //Totodile,
[SPECIES_CROCONAW] = 
    {  
      //FRONT_PIC(Croconaw),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Croconaw),
      BACK_COORD(0x88,0),
      //PALETTES(Croconaw),
      PIC_DATA_ICON_INDEX(Croconaw,0),
      //ICON(Croconaw, 0),
      .enemyMonElevation = 0,
    }, //Croconaw,
[SPECIES_FERALIGATOR] = 
    {  
      //FRONT_PIC(Feraligator),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Feraligator),
      BACK_COORD(0x88,0),
      //PALETTES(Feraligator),
      PIC_DATA_ICON_INDEX(Feraligator,0),
      //ICON(Feraligator, 0),
      .enemyMonElevation = 0,
    }, //Feraligatr,
[SPECIES_SENTRET] = 
    {  
      //FRONT_PIC(Sentret),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sentret),
      BACK_COORD(0x88,0),
      //PALETTES(Sentret),
      PIC_DATA_ICON_INDEX(Sentret,0),
      //ICON(Sentret, 0),
      .enemyMonElevation = 0,
    }, //Sentret,
[SPECIES_FURRET] = 
    {  
      //FRONT_PIC(Furret),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Furret),
      BACK_COORD(0x88,0),
      //PALETTES(Furret),
      PIC_DATA_ICON_INDEX(Furret,0),
      //ICON(Furret, 0),
      .enemyMonElevation = 0,
    }, //Furret,
[SPECIES_HOOTHOOT] = 
    {  
      //FRONT_PIC(Hoothoot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hoothoot),
      BACK_COORD(0x88,0),
      //PALETTES(Hoothoot),
      PIC_DATA_ICON_INDEX(Hoothoot,0),
      //ICON(Hoothoot, 0),
      .enemyMonElevation = 0,
    }, //Hoothoot,
[SPECIES_NOCTOWL] = 
    {  
      //FRONT_PIC(Noctowl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Noctowl),
      BACK_COORD(0x88,0),
      //PALETTES(Noctowl),
      PIC_DATA_ICON_INDEX(Noctowl,0),
      //ICON(Noctowl, 0),
      .enemyMonElevation = 0,
    }, //Noctowl,
[SPECIES_LEDYBA] = 
    {  
      //FRONT_PIC(Ledyba),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ledyba),
      BACK_COORD(0x88,0),
      //PALETTES(Ledyba),
      PIC_DATA_ICON_INDEX(Ledyba,0),
      //ICON(Ledyba, 0),
      .enemyMonElevation = 0,
    }, //Ledyba,
[SPECIES_LEDIAN] = 
    {  
      //FRONT_PIC(Ledian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ledian),
      BACK_COORD(0x88,0),
      //PALETTES(Ledian),
      PIC_DATA_ICON_INDEX(Ledian,0),
      //ICON(Ledian, 0),
      .enemyMonElevation = 0,
    }, //Ledian,
[SPECIES_SPINARAK] = 
    {  
      //FRONT_PIC(Spinarak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spinarak),
      BACK_COORD(0x88,0),
      //PALETTES(Spinarak),
      PIC_DATA_ICON_INDEX(Spinarak,0),
      //ICON(Spinarak, 0),
      .enemyMonElevation = 0,
    }, //Spinarak,
[SPECIES_ARIADOS] = 
    {  
      //FRONT_PIC(Ariados),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ariados),
      BACK_COORD(0x88,0),
      //PALETTES(Ariados),
      PIC_DATA_ICON_INDEX(Ariados,0),
      //ICON(Ariados, 0),
      .enemyMonElevation = 0,
    }, //Ariados,
[SPECIES_CROBAT] = 
    {  
      //FRONT_PIC(Crobat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Crobat),
      BACK_COORD(0x88,0),
      //PALETTES(Crobat),
      PIC_DATA_ICON_INDEX(Crobat,0),
      //ICON(Crobat, 0),
      .enemyMonElevation = 0,
    }, //Crobat,
[SPECIES_CHINCHOU] = 
    {  
      //FRONT_PIC(Chinchou),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chinchou),
      BACK_COORD(0x88,0),
      //PALETTES(Chinchou),
      PIC_DATA_ICON_INDEX(Chinchou,0),
      //ICON(Chinchou, 0),
      .enemyMonElevation = 0,
    }, //Chinchou,
[SPECIES_LANTURN] = 
    {  
      //FRONT_PIC(Lanturn),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lanturn),
      BACK_COORD(0x88,0),
      //PALETTES(Lanturn),
      PIC_DATA_ICON_INDEX(Lanturn,0),
      //ICON(Lanturn, 0),
      .enemyMonElevation = 0,
    }, //Lanturn,
[SPECIES_PICHU] = 
    {  
      //FRONT_PIC(Pichu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pichu),
      BACK_COORD(0x88,0),
      //PALETTES(Pichu),
      PIC_DATA_ICON_INDEX(Pichu,0),
      //ICON(Pichu, 0),
      .enemyMonElevation = 0,
    }, //Pichu,
[SPECIES_CLEFFA] = 
    {  
      //FRONT_PIC(Cleffa),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cleffa),
      BACK_COORD(0x88,0),
      //PALETTES(Cleffa),
      PIC_DATA_ICON_INDEX(Cleffa,0),
      //ICON(Cleffa, 0),
      .enemyMonElevation = 0,
    }, //Cleffa,
[SPECIES_IGGLYBUFF] = 
    {  
      //FRONT_PIC(Igglybuff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Igglybuff),
      BACK_COORD(0x88,0),
      //PALETTES(Igglybuff),
      PIC_DATA_ICON_INDEX(Igglybuff,0),
      //ICON(Igglybuff, 0),
      .enemyMonElevation = 0,
    }, //Igglybuff,
[SPECIES_TOGEPI] = 
    {  
      //FRONT_PIC(Togepi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Togepi),
      BACK_COORD(0x88,0),
      //PALETTES(Togepi),
      PIC_DATA_ICON_INDEX(Togepi,0),
      //ICON(Togepi, 0),
      .enemyMonElevation = 0,
    }, //Togepi,
[SPECIES_TOGETIC] = 
    {  
      //FRONT_PIC(Togetic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Togetic),
      BACK_COORD(0x88,0),
      //PALETTES(Togetic),
      PIC_DATA_ICON_INDEX(Togetic,0),
      //ICON(Togetic, 0),
      .enemyMonElevation = 0,
    }, //Togetic,
[SPECIES_NATU] = 
    {  
      //FRONT_PIC(Natu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Natu),
      BACK_COORD(0x88,0),
      //PALETTES(Natu),
      PIC_DATA_ICON_INDEX(Natu,0),
      //ICON(Natu, 0),
      .enemyMonElevation = 0,
    }, //Natu,
[SPECIES_XATU] = 
    {  
      //FRONT_PIC(Xatu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Xatu),
      BACK_COORD(0x88,0),
      //PALETTES(Xatu),
      PIC_DATA_ICON_INDEX(Xatu,0),
      //ICON(Xatu, 0),
      .enemyMonElevation = 0,
    }, //Xatu,
[SPECIES_MAREEP] = 
    {  
      //FRONT_PIC(Mareep),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mareep),
      BACK_COORD(0x88,0),
      //PALETTES(Mareep),
      PIC_DATA_ICON_INDEX(Mareep,0),
      //ICON(Mareep, 0),
      .enemyMonElevation = 0,
    }, //Mareep,
[SPECIES_FLAAFFY] = 
    {  
      //FRONT_PIC(Flaaffy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flaaffy),
      BACK_COORD(0x88,0),
      //PALETTES(Flaaffy),
      PIC_DATA_ICON_INDEX(Flaaffy,0),
      //ICON(Flaaffy, 0),
      .enemyMonElevation = 0,
    }, //Flaaffy,
[SPECIES_AMPHAROS] = 
    {  
      //FRONT_PIC(Ampharos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ampharos),
      BACK_COORD(0x88,0),
      //PALETTES(Ampharos),
      PIC_DATA_ICON_INDEX(Ampharos,0),
      //ICON(Ampharos, 0),
      .enemyMonElevation = 0,
    }, //Ampharos,
[SPECIES_BELLOSSOM] = 
    {  
      //FRONT_PIC(Bellossom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bellossom),
      BACK_COORD(0x88,0),
      //PALETTES(Bellossom),
      PIC_DATA_ICON_INDEX(Bellossom,0),
      //ICON(Bellossom, 0),
      .enemyMonElevation = 0,
    }, //Bellossom,
[SPECIES_MARILL] = 
    {  
      //FRONT_PIC(Marill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Marill),
      BACK_COORD(0x88,0),
      //PALETTES(Marill),
      PIC_DATA_ICON_INDEX(Marill,0),
      //ICON(Marill, 0),
      .enemyMonElevation = 0,
    }, //Marill,
[SPECIES_AZUMARILL] = 
    {  
      //FRONT_PIC(Azumarill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Azumarill),
      BACK_COORD(0x88,0),
      //PALETTES(Azumarill),
      PIC_DATA_ICON_INDEX(Azumarill,0),
      //ICON(Azumarill, 0),
      .enemyMonElevation = 0,
    }, //Azumarill,
[SPECIES_SUDOWOODO] = 
    {  
      //FRONT_PIC(Sudowoodo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sudowoodo),
      BACK_COORD(0x88,0),
      //PALETTES(Sudowoodo),
      PIC_DATA_ICON_INDEX(Sudowoodo,0),
      //ICON(Sudowoodo, 0),
      .enemyMonElevation = 0,
    }, //Sudowoodo,
[SPECIES_POLITOED] = 
    {  
      //FRONT_PIC(Politoed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Politoed),
      BACK_COORD(0x88,0),
      //PALETTES(Politoed),
      PIC_DATA_ICON_INDEX(Politoed,0),
      //ICON(Politoed, 0),
      .enemyMonElevation = 0,
    }, //Politoed,
[SPECIES_HOPPIP] = 
    {  
      //FRONT_PIC(Hoppip),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hoppip),
      BACK_COORD(0x88,0),
      //PALETTES(Hoppip),
      PIC_DATA_ICON_INDEX(Hoppip,0),
      //ICON(Hoppip, 0),
      .enemyMonElevation = 0,
    }, //Hoppip,
[SPECIES_SKIPLOOM] = 
    {  
      //FRONT_PIC(Skiploom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skiploom),
      BACK_COORD(0x88,0),
      //PALETTES(Skiploom),
      PIC_DATA_ICON_INDEX(Skiploom,0),
      //ICON(Skiploom, 0),
      .enemyMonElevation = 0,
    }, //Skiploom,
[SPECIES_JUMPLUFF] = 
    {  
      //FRONT_PIC(Jumpluff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Jumpluff),
      BACK_COORD(0x88,0),
      //PALETTES(Jumpluff),
      PIC_DATA_ICON_INDEX(Jumpluff,0),
      //ICON(Jumpluff, 0),
      .enemyMonElevation = 0,
    }, //Jumpluff,
[SPECIES_AIPOM] = 
    {  
      //FRONT_PIC(Aipom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aipom),
      BACK_COORD(0x88,0),
      //PALETTES(Aipom),
      PIC_DATA_ICON_INDEX(Aipom,0),
      //ICON(Aipom, 0),
      .enemyMonElevation = 0,
    }, //Aipom,
[SPECIES_SUNKERN] = 
    {  
      //FRONT_PIC(Sunkern),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sunkern),
      BACK_COORD(0x88,0),
      //PALETTES(Sunkern),
      PIC_DATA_ICON_INDEX(Sunkern,0),
      //ICON(Sunkern, 0),
      .enemyMonElevation = 0,
    }, //Sunkern,
[SPECIES_SUNFLORA] = 
    {  
      //FRONT_PIC(Sunflora),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sunflora),
      BACK_COORD(0x88,0),
      //PALETTES(Sunflora),
      PIC_DATA_ICON_INDEX(Sunflora,0),
      //ICON(Sunflora, 0),
      .enemyMonElevation = 0,
    }, //Sunflora,
[SPECIES_YANMA] = 
    {  
      //FRONT_PIC(Yanma),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Yanma),
      BACK_COORD(0x88,0),
      //PALETTES(Yanma),
      PIC_DATA_ICON_INDEX(Yanma,0),
      //ICON(Yanma, 0),
      .enemyMonElevation = 0,
    }, //Yanma,
[SPECIES_WOOPER] = 
    {  
      //FRONT_PIC(Wooper),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wooper),
      BACK_COORD(0x88,0),
      //PALETTES(Wooper),
      PIC_DATA_ICON_INDEX(Wooper,0),
      //ICON(Wooper, 0),
      .enemyMonElevation = 0,
    }, //Wooper,
[SPECIES_QUAGSIRE] = 
    {  
      //FRONT_PIC(Quagsire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Quagsire),
      BACK_COORD(0x88,0),
      //PALETTES(Quagsire),
      PIC_DATA_ICON_INDEX(Quagsire,0),
      //ICON(Quagsire, 0),
      .enemyMonElevation = 0,
    }, //Quagsire,
[SPECIES_ESPEON] = 
    {  
      //FRONT_PIC(Espeon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Espeon),
      BACK_COORD(0x88,0),
      //PALETTES(Espeon),
      PIC_DATA_ICON_INDEX(Espeon,0),
      //ICON(Espeon, 0),
      .enemyMonElevation = 0,
    }, //Espeon,
[SPECIES_UMBREON] = 
    {  
      //FRONT_PIC(Umbreon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Umbreon),
      BACK_COORD(0x88,0),
      //PALETTES(Umbreon),
      PIC_DATA_ICON_INDEX(Umbreon,0),
      //ICON(Umbreon, 0),
      .enemyMonElevation = 0,
    }, //Umbreon,
[SPECIES_MURKROW] = 
    {  
      //FRONT_PIC(Murkrow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Murkrow),
      BACK_COORD(0x88,0),
      //PALETTES(Murkrow),
      PIC_DATA_ICON_INDEX(Murkrow,0),
      //ICON(Murkrow, 0),
      .enemyMonElevation = 0,
    }, //Murkrow,
[SPECIES_SLOWKING] = 
    {  
      //FRONT_PIC(Slowking),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slowking),
      BACK_COORD(0x88,0),
      //PALETTES(Slowking),
      PIC_DATA_ICON_INDEX(Slowking,0),
      //ICON(Slowking, 0),
      .enemyMonElevation = 0,
    }, //Slowking,
[SPECIES_MISDREAVUS] = 
    {  
      //FRONT_PIC(Misdreavus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Misdreavus),
      BACK_COORD(0x88,0),
      //PALETTES(Misdreavus),
      PIC_DATA_ICON_INDEX(Misdreavus,0),
      //ICON(Misdreavus, 0),
      .enemyMonElevation = 0,
    }, //Misdreavus,
[SPECIES_UNOWN] = 
    {  
      //FRONT_PIC(Unown),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Unown),
      BACK_COORD(0x88,0),
      //PALETTES(Unown),
      PIC_DATA_ICON_INDEX(Unown,0),
      //ICON(Unown, 0),
      .enemyMonElevation = 0,
    }, //Unown,
[SPECIES_WOBBUFFET] = 
    {  
      //FRONT_PIC(Wobbuffet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wobbuffet),
      BACK_COORD(0x88,0),
      //PALETTES(Wobbuffet),
      PIC_DATA_ICON_INDEX(Wobbuffet,0),
      //ICON(Wobbuffet, 0),
      .enemyMonElevation = 0,
    }, //Wobbuffet,
[SPECIES_GIRAFARIG] = 
    {  
      //FRONT_PIC(Girafarig),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Girafarig),
      BACK_COORD(0x88,0),
      //PALETTES(Girafarig),
      PIC_DATA_ICON_INDEX(Girafarig,0),
      //ICON(Girafarig, 0),
      .enemyMonElevation = 0,
    }, //Girafarig,
[SPECIES_PINECO] = 
    {  
      //FRONT_PIC(Pineco),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pineco),
      BACK_COORD(0x88,0),
      //PALETTES(Pineco),
      PIC_DATA_ICON_INDEX(Pineco,0),
      //ICON(Pineco, 0),
      .enemyMonElevation = 0,
    }, //Pineco,
[SPECIES_FORRETRESS] = 
    {  
      //FRONT_PIC(Forretress),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Forretress),
      BACK_COORD(0x88,0),
      //PALETTES(Forretress),
      PIC_DATA_ICON_INDEX(Forretress,0),
      //ICON(Forretress, 0),
      .enemyMonElevation = 0,
    }, //Forretress,
[SPECIES_DUNSPARCE] = 
    {  
      //FRONT_PIC(Dunsparce),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dunsparce),
      BACK_COORD(0x88,0),
      //PALETTES(Dunsparce),
      PIC_DATA_ICON_INDEX(Dunsparce,0),
      //ICON(Dunsparce, 0),
      .enemyMonElevation = 0,
    }, //Dunsparce,
[SPECIES_GLIGAR] = 
    {  
      //FRONT_PIC(Gligar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gligar),
      BACK_COORD(0x88,0),
      //PALETTES(Gligar),
      PIC_DATA_ICON_INDEX(Gligar,0),
      //ICON(Gligar, 0),
      .enemyMonElevation = 0,
    }, //Gligar,
[SPECIES_STEELIX] = 
    {  
      //FRONT_PIC(Steelix),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Steelix),
      BACK_COORD(0x88,0),
      //PALETTES(Steelix),
      PIC_DATA_ICON_INDEX(Steelix,0),
      //ICON(Steelix, 0),
      .enemyMonElevation = 0,
    }, //Steelix,
[SPECIES_SNUBBULL] = 
    {  
      //FRONT_PIC(Snubbull),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Snubbull),
      BACK_COORD(0x88,0),
      //PALETTES(Snubbull),
      PIC_DATA_ICON_INDEX(Snubbull,0),
      //ICON(Snubbull, 0),
      .enemyMonElevation = 0,
    }, //Snubbull,
[SPECIES_GRANBULL] = 
    {  
      //FRONT_PIC(Granbull),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Granbull),
      BACK_COORD(0x88,0),
      //PALETTES(Granbull),
      PIC_DATA_ICON_INDEX(Granbull,0),
      //ICON(Granbull, 0),
      .enemyMonElevation = 0,
    }, //Granbull,
[SPECIES_QWILFISH] = 
    {  
      //FRONT_PIC(Qwilfish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Qwilfish),
      BACK_COORD(0x88,0),
      //PALETTES(Qwilfish),
      PIC_DATA_ICON_INDEX(Qwilfish,0),
      //ICON(Qwilfish, 0),
      .enemyMonElevation = 0,
    }, //Qwilfish,
[SPECIES_SCIZOR] = 
    {  
      //FRONT_PIC(Scizor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scizor),
      BACK_COORD(0x88,0),
      //PALETTES(Scizor),
      PIC_DATA_ICON_INDEX(Scizor,0),
      //ICON(Scizor, 0),
      .enemyMonElevation = 0,
    }, //Scizor,
[SPECIES_SHUCKLE] = 
    {  
      //FRONT_PIC(Shuckle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shuckle),
      BACK_COORD(0x88,0),
      //PALETTES(Shuckle),
      PIC_DATA_ICON_INDEX(Shuckle,0),
      //ICON(Shuckle, 0),
      .enemyMonElevation = 0,
    }, //Shuckle,
[SPECIES_HERACROSS] = 
    {  
      //FRONT_PIC(Heracross),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Heracross),
      BACK_COORD(0x88,0),
      //PALETTES(Heracross),
      PIC_DATA_ICON_INDEX(Heracross,0),
      //ICON(Heracross, 0),
      .enemyMonElevation = 0,
    }, //Heracross,
[SPECIES_SNEASEL] = 
    {  
      //FRONT_PIC(Sneasel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sneasel),
      BACK_COORD(0x88,0),
      //PALETTES(Sneasel),
      PIC_DATA_ICON_INDEX(Sneasel,0),
      //ICON(Sneasel, 0),
      .enemyMonElevation = 0,
    }, //Sneasel,
[SPECIES_TEDDIURSA] = 
    {  
      //FRONT_PIC(Teddiursa),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Teddiursa),
      BACK_COORD(0x88,0),
      //PALETTES(Teddiursa),
      PIC_DATA_ICON_INDEX(Teddiursa,0),
      //ICON(Teddiursa, 0),
      .enemyMonElevation = 0,
    }, //Teddiursa,
[SPECIES_URSARING] = 
    {  
      //FRONT_PIC(Ursaring),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ursaring),
      BACK_COORD(0x88,0),
      //PALETTES(Ursaring),
      PIC_DATA_ICON_INDEX(Ursaring,0),
      //ICON(Ursaring, 0),
      .enemyMonElevation = 0,
    }, //Ursaring,
[SPECIES_SLUGMA] = 
    {  
      //FRONT_PIC(Slugma),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slugma),
      BACK_COORD(0x88,0),
      //PALETTES(Slugma),
      PIC_DATA_ICON_INDEX(Slugma,0),
      //ICON(Slugma, 0),
      .enemyMonElevation = 0,
    }, //Slugma,
[SPECIES_MAGCARGO] = 
    {  
      //FRONT_PIC(Magcargo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magcargo),
      BACK_COORD(0x88,0),
      //PALETTES(Magcargo),
      PIC_DATA_ICON_INDEX(Magcargo,0),
      //ICON(Magcargo, 0),
      .enemyMonElevation = 0,
    }, //Magcargo,
[SPECIES_SWINUB] = 
    {  
      //FRONT_PIC(Swinub),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swinub),
      BACK_COORD(0x88,0),
      //PALETTES(Swinub),
      PIC_DATA_ICON_INDEX(Swinub,0),
      //ICON(Swinub, 0),
      .enemyMonElevation = 0,
    }, //Swinub,
[SPECIES_PILOSWINE] = 
    {  
      //FRONT_PIC(Piloswine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Piloswine),
      BACK_COORD(0x88,0),
      //PALETTES(Piloswine),
      PIC_DATA_ICON_INDEX(Piloswine,0),
      //ICON(Piloswine, 0),
      .enemyMonElevation = 0,
    }, //Piloswine,
[SPECIES_CORSOLA] = 
    {  
      //FRONT_PIC(Corsola),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Corsola),
      BACK_COORD(0x88,0),
      //PALETTES(Corsola),
      PIC_DATA_ICON_INDEX(Corsola,0),
      //ICON(Corsola, 0),
      .enemyMonElevation = 0,
    }, //Corsola,
[SPECIES_REMORAID] = 
    {  
      //FRONT_PIC(Remoraid),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Remoraid),
      BACK_COORD(0x88,0),
      //PALETTES(Remoraid),
      PIC_DATA_ICON_INDEX(Remoraid,0),
      //ICON(Remoraid, 0),
      .enemyMonElevation = 0,
    }, //Remoraid,
[SPECIES_OCTILLERY] = 
    {  
      //FRONT_PIC(Octillery),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Octillery),
      BACK_COORD(0x88,0),
      //PALETTES(Octillery),
      PIC_DATA_ICON_INDEX(Octillery,0),
      //ICON(Octillery, 0),
      .enemyMonElevation = 0,
    }, //Octillery,
[SPECIES_DELIBIRD] = 
    {  
      //FRONT_PIC(Delibird),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Delibird),
      BACK_COORD(0x88,0),
      //PALETTES(Delibird),
      PIC_DATA_ICON_INDEX(Delibird,0),
      //ICON(Delibird, 0),
      .enemyMonElevation = 0,
    }, //Delibird,
[SPECIES_MANTINE] = 
    {  
      //FRONT_PIC(Mantine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mantine),
      BACK_COORD(0x88,0),
      //PALETTES(Mantine),
      PIC_DATA_ICON_INDEX(Mantine,0),
      //ICON(Mantine, 0),
      .enemyMonElevation = 0,
    }, //Mantine,
[SPECIES_SKARMORY] = 
    {  
      //FRONT_PIC(Skarmory),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skarmory),
      BACK_COORD(0x88,0),
      //PALETTES(Skarmory),
      PIC_DATA_ICON_INDEX(Skarmory,0),
      //ICON(Skarmory, 0),
      .enemyMonElevation = 0,
    }, //Skarmory,
[SPECIES_HOUNDOUR] = 
    {  
      //FRONT_PIC(Houndour),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Houndour),
      BACK_COORD(0x88,0),
      //PALETTES(Houndour),
      PIC_DATA_ICON_INDEX(Houndour,0),
      //ICON(Houndour, 0),
      .enemyMonElevation = 0,
    }, //Houndour,
[SPECIES_HOUNDOOM] = 
    {  
      //FRONT_PIC(Houndoom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Houndoom),
      BACK_COORD(0x88,0),
      //PALETTES(Houndoom),
      PIC_DATA_ICON_INDEX(Houndoom,0),
      //ICON(Houndoom, 0),
      .enemyMonElevation = 0,
    }, //Houndoom,
[SPECIES_KINGDRA] = 
    {  
      //FRONT_PIC(Kingdra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kingdra),
      BACK_COORD(0x88,0),
      //PALETTES(Kingdra),
      PIC_DATA_ICON_INDEX(Kingdra,0),
      //ICON(Kingdra, 0),
      .enemyMonElevation = 0,
    }, //Kingdra,
[SPECIES_PHANPY] = 
    {  
      //FRONT_PIC(Phanpy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Phanpy),
      BACK_COORD(0x88,0),
      //PALETTES(Phanpy),
      PIC_DATA_ICON_INDEX(Phanpy,0),
      //ICON(Phanpy, 0),
      .enemyMonElevation = 0,
    }, //Phanpy,
[SPECIES_DONPHAN] = 
    {  
      //FRONT_PIC(Donphan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Donphan),
      BACK_COORD(0x88,0),
      //PALETTES(Donphan),
      PIC_DATA_ICON_INDEX(Donphan,0),
      //ICON(Donphan, 0),
      .enemyMonElevation = 0,
    }, //Donphan,
[SPECIES_PORYGON2] = 
    {  
      //FRONT_PIC(Porygon2),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Porygon2),
      BACK_COORD(0x88,0),
      //PALETTES(Porygon2),
      PIC_DATA_ICON_INDEX(Porygon2,0),
      //ICON(Porygon2, 0),
      .enemyMonElevation = 0,
    }, //Porygon2,
[SPECIES_STANTLER] = 
    {  
      //FRONT_PIC(Stantler),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stantler),
      BACK_COORD(0x88,0),
      //PALETTES(Stantler),
      PIC_DATA_ICON_INDEX(Stantler,0),
      //ICON(Stantler, 0),
      .enemyMonElevation = 0,
    }, //Stantler,
[SPECIES_SMEARGLE] = 
    {  
      //FRONT_PIC(Smeargle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Smeargle),
      BACK_COORD(0x88,0),
      //PALETTES(Smeargle),
      PIC_DATA_ICON_INDEX(Smeargle,0),
      //ICON(Smeargle, 0),
      .enemyMonElevation = 0,
    }, //Smeargle,
[SPECIES_TYROGUE] = 
    {  
      //FRONT_PIC(Tyrogue),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tyrogue),
      BACK_COORD(0x88,0),
      //PALETTES(Tyrogue),
      PIC_DATA_ICON_INDEX(Tyrogue,0),
      //ICON(Tyrogue, 0),
      .enemyMonElevation = 0,
    }, //Tyrogue,
[SPECIES_HITMONTOP] = 
    {  
      //FRONT_PIC(Hitmontop),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hitmontop),
      BACK_COORD(0x88,0),
      //PALETTES(Hitmontop),
      PIC_DATA_ICON_INDEX(Hitmontop,0),
      //ICON(Hitmontop, 0),
      .enemyMonElevation = 0,
    }, //Hitmontop,
[SPECIES_SMOOCHUM] = 
    {  
      //FRONT_PIC(Smoochum),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Smoochum),
      BACK_COORD(0x88,0),
      //PALETTES(Smoochum),
      PIC_DATA_ICON_INDEX(Smoochum,0),
      //ICON(Smoochum, 0),
      .enemyMonElevation = 0,
    }, //Smoochum,
[SPECIES_ELEKID] = 
    {  
      //FRONT_PIC(Elekid),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Elekid),
      BACK_COORD(0x88,0),
      //PALETTES(Elekid),
      PIC_DATA_ICON_INDEX(Elekid,0),
      //ICON(Elekid, 0),
      .enemyMonElevation = 0,
    }, //Elekid,
[SPECIES_MAGBY] = 
    {  
      //FRONT_PIC(Magby),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magby),
      BACK_COORD(0x88,0),
      //PALETTES(Magby),
      PIC_DATA_ICON_INDEX(Magby,0),
      //ICON(Magby, 0),
      .enemyMonElevation = 0,
    }, //Magby,
[SPECIES_MILTANK] = 
    {  
      //FRONT_PIC(Miltank),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Miltank),
      BACK_COORD(0x88,0),
      //PALETTES(Miltank),
      PIC_DATA_ICON_INDEX(Miltank,0),
      //ICON(Miltank, 0),
      .enemyMonElevation = 0,
    }, //Miltank,
[SPECIES_BLISSEY] = 
    {  
      //FRONT_PIC(Blissey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blissey),
      BACK_COORD(0x88,0),
      //PALETTES(Blissey),
      PIC_DATA_ICON_INDEX(Blissey,0),
      //ICON(Blissey, 0),
      .enemyMonElevation = 0,
    }, //Blissey,
[SPECIES_RAIKOU] = 
    {  
      //FRONT_PIC(Raikou),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Raikou),
      BACK_COORD(0x88,0),
      //PALETTES(Raikou),
      PIC_DATA_ICON_INDEX(Raikou,0),
      //ICON(Raikou, 0),
      .enemyMonElevation = 0,
    }, //Raikou,
[SPECIES_ENTEI] = 
    {  
      //FRONT_PIC(Entei),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Entei),
      BACK_COORD(0x88,0),
      //PALETTES(Entei),
      PIC_DATA_ICON_INDEX(Entei,0),
      //ICON(Entei, 0),
      .enemyMonElevation = 0,
    }, //Entei,
[SPECIES_SUICUNE] = 
    {  
      //FRONT_PIC(Suicune),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Suicune),
      BACK_COORD(0x88,0),
      //PALETTES(Suicune),
      PIC_DATA_ICON_INDEX(Suicune,0),
      //ICON(Suicune, 0),
      .enemyMonElevation = 0,
    }, //Suicune,
[SPECIES_LARVITAR] = 
    {  
      //FRONT_PIC(Larvitar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Larvitar),
      BACK_COORD(0x88,0),
      //PALETTES(Larvitar),
      PIC_DATA_ICON_INDEX(Larvitar,0),
      //ICON(Larvitar, 0),
      .enemyMonElevation = 0,
    }, //Larvitar,
[SPECIES_PUPITAR] = 
    {  
      //FRONT_PIC(Pupitar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pupitar),
      BACK_COORD(0x88,0),
      //PALETTES(Pupitar),
      PIC_DATA_ICON_INDEX(Pupitar,0),
      //ICON(Pupitar, 0),
      .enemyMonElevation = 0,
    }, //Pupitar,
[SPECIES_TYRANITAR] = 
    {  
      //FRONT_PIC(Tyranitar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tyranitar),
      BACK_COORD(0x88,0),
      //PALETTES(Tyranitar),
      PIC_DATA_ICON_INDEX(Tyranitar,0),
      //ICON(Tyranitar, 0),
      .enemyMonElevation = 0,
    }, //Tyranitar,
[SPECIES_LUGIA] = 
    {  
      //FRONT_PIC(Lugia),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lugia),
      BACK_COORD(0x88,0),
      //PALETTES(Lugia),
      PIC_DATA_ICON_INDEX(Lugia,0),
      //ICON(Lugia, 0),
      .enemyMonElevation = 0,
    }, //Lugia,
[SPECIES_HO_OH] = 
    {  
      //FRONT_PIC(HoOh),
      FRONT_COORD(0x88,0),
      //BACK_PIC(HoOh),
      BACK_COORD(0x88,0),
      //PALETTES(HoOh),
      PIC_DATA_ICON_INDEX(HoOh,0),
      //ICON(HoOh, 0),
      .enemyMonElevation = 0,
    }, //HoOh,
[SPECIES_CELEBI] = 
    {  
      //FRONT_PIC(Celebi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Celebi),
      BACK_COORD(0x88,0),
      //PALETTES(Celebi),
      PIC_DATA_ICON_INDEX(Celebi,0),
      //ICON(Celebi, 0),
      .enemyMonElevation = 0,
    }, //Celebi,
    
[SPECIES_TREECKO] = 
    {  
      //FRONT_PIC(Treecko),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Treecko),
      BACK_COORD(0x88,0),
      //PALETTES(Treecko),
      PIC_DATA_ICON_INDEX(Treecko,0),
      //ICON(Treecko, 0),
      .enemyMonElevation = 0,
    }, //Treecko,
[SPECIES_GROVYLE] = 
    {  
      //FRONT_PIC(Grovyle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grovyle),
      BACK_COORD(0x88,0),
      //PALETTES(Grovyle),
      PIC_DATA_ICON_INDEX(Grovyle,0),
      //ICON(Grovyle, 0),
      .enemyMonElevation = 0,
    }, //Grovyle,
[SPECIES_SCEPTILE] = 
    {  
      //FRONT_PIC(Sceptile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sceptile),
      BACK_COORD(0x88,0),
      //PALETTES(Sceptile),
      PIC_DATA_ICON_INDEX(Sceptile,0),
      //ICON(Sceptile, 0),
      .enemyMonElevation = 0,
    }, //Sceptile,
[SPECIES_TORCHIC] = 
    {  
      //FRONT_PIC(Torchic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Torchic),
      BACK_COORD(0x88,0),
      //PALETTES(Torchic),
      PIC_DATA_ICON_INDEX(Torchic,0),
      //ICON(Torchic, 0),
      .enemyMonElevation = 0,
    }, //Torchic,
[SPECIES_COMBUSKEN] = 
    {  
      //FRONT_PIC(Combusken),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Combusken),
      BACK_COORD(0x88,0),
      //PALETTES(Combusken),
      PIC_DATA_ICON_INDEX(Combusken,0),
      //ICON(Combusken, 0),
      .enemyMonElevation = 0,
    }, //Combusken,
[SPECIES_BLAZIKEN] = 
    {  
      //FRONT_PIC(Blaziken),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blaziken),
      BACK_COORD(0x88,0),
      //PALETTES(Blaziken),
      PIC_DATA_ICON_INDEX(Blaziken,0),
      //ICON(Blaziken, 0),
      .enemyMonElevation = 0,
    }, //Blaziken,
[SPECIES_MUDKIP] = 
    {  
      //FRONT_PIC(Mudkip),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mudkip),
      BACK_COORD(0x88,0),
      //PALETTES(Mudkip),
      PIC_DATA_ICON_INDEX(Mudkip,0),
      //ICON(Mudkip, 0),
      .enemyMonElevation = 0,
    }, //Mudkip,
[SPECIES_MARSHTOMP] = 
    {  
      //FRONT_PIC(Marshtomp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Marshtomp),
      BACK_COORD(0x88,0),
      //PALETTES(Marshtomp),
      PIC_DATA_ICON_INDEX(Marshtomp,0),
      //ICON(Marshtomp, 0),
      .enemyMonElevation = 0,
    }, //Marshtomp,
[SPECIES_SWAMPERT] = 
    {  
      //FRONT_PIC(Swampert),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swampert),
      BACK_COORD(0x88,0),
      //PALETTES(Swampert),
      PIC_DATA_ICON_INDEX(Swampert,0),
      //ICON(Swampert, 0),
      .enemyMonElevation = 0,
    }, //Swampert,
[SPECIES_POOCHYENA] = 
    {  
      //FRONT_PIC(Poochyena),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Poochyena),
      BACK_COORD(0x88,0),
      //PALETTES(Poochyena),
      PIC_DATA_ICON_INDEX(Poochyena,0),
      //ICON(Poochyena, 0),
      .enemyMonElevation = 0,
    }, //Poochyena,
[SPECIES_MIGHTYENA] = 
    {  
      //FRONT_PIC(Mightyena),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mightyena),
      BACK_COORD(0x88,0),
      //PALETTES(Mightyena),
      PIC_DATA_ICON_INDEX(Mightyena,0),
      //ICON(Mightyena, 0),
      .enemyMonElevation = 0,
    }, //Mightyena,
[SPECIES_ZIGZAGOON] = 
    {  
      //FRONT_PIC(Zigzagoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zigzagoon),
      BACK_COORD(0x88,0),
      //PALETTES(Zigzagoon),
      PIC_DATA_ICON_INDEX(Zigzagoon,0),
      //ICON(Zigzagoon, 0),
      .enemyMonElevation = 0,
    }, //Zigzagoon,
[SPECIES_LINOONE] = 
    {  
      //FRONT_PIC(Linoone),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Linoone),
      BACK_COORD(0x88,0),
      //PALETTES(Linoone),
      PIC_DATA_ICON_INDEX(Linoone,0),
      //ICON(Linoone, 0),
      .enemyMonElevation = 0,
    }, //Linoone,
[SPECIES_WURMPLE] = 
    {  
      //FRONT_PIC(Wurmple),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wurmple),
      BACK_COORD(0x88,0),
      //PALETTES(Wurmple),
      PIC_DATA_ICON_INDEX(Wurmple,0),
      //ICON(Wurmple, 0),
      .enemyMonElevation = 0,
    }, //Wurmple,
[SPECIES_SILCOON] = 
    {  
      //FRONT_PIC(Silcoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Silcoon),
      BACK_COORD(0x88,0),
      //PALETTES(Silcoon),
      PIC_DATA_ICON_INDEX(Silcoon,0),
      //ICON(Silcoon, 0),
      .enemyMonElevation = 0,
    }, //Silcoon,
[SPECIES_BEAUTIFLY] = 
    {  
      //FRONT_PIC(Beautifly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Beautifly),
      BACK_COORD(0x88,0),
      //PALETTES(Beautifly),
      PIC_DATA_ICON_INDEX(Beautifly,0),
      //ICON(Beautifly, 0),
      .enemyMonElevation = 0,
    }, //Beautifly,
[SPECIES_CASCOON] = 
    {  
      //FRONT_PIC(Cascoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cascoon),
      BACK_COORD(0x88,0),
      //PALETTES(Cascoon),
      PIC_DATA_ICON_INDEX(Cascoon,0),
      //ICON(Cascoon, 0),
      .enemyMonElevation = 0,
    }, //Cascoon,
[SPECIES_DUSTOX] = 
    {  
      //FRONT_PIC(Dustox),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dustox),
      BACK_COORD(0x88,0),
      //PALETTES(Dustox),
      PIC_DATA_ICON_INDEX(Dustox,0),
      //ICON(Dustox, 0),
      .enemyMonElevation = 0,
    }, //Dustox,
[SPECIES_LOTAD] = 
    {  
      //FRONT_PIC(Lotad),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lotad),
      BACK_COORD(0x88,0),
      //PALETTES(Lotad),
      PIC_DATA_ICON_INDEX(Lotad,0),
      //ICON(Lotad, 0),
      .enemyMonElevation = 0,
    }, //Lotad,
[SPECIES_LOMBRE] = 
    {  
      //FRONT_PIC(Lombre),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lombre),
      BACK_COORD(0x88,0),
      //PALETTES(Lombre),
      PIC_DATA_ICON_INDEX(Lombre,0),
      //ICON(Lombre, 0),
      .enemyMonElevation = 0,
    }, //Lombre,
[SPECIES_LUDICOLO] = 
    {  
      //FRONT_PIC(Ludicolo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ludicolo),
      BACK_COORD(0x88,0),
      //PALETTES(Ludicolo),
      PIC_DATA_ICON_INDEX(Ludicolo,0),
      //ICON(Ludicolo, 0),
      .enemyMonElevation = 0,
    }, //Ludicolo,
[SPECIES_SEEDOT] = 
    {  
      //FRONT_PIC(Seedot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Seedot),
      BACK_COORD(0x88,0),
      //PALETTES(Seedot),
      PIC_DATA_ICON_INDEX(Seedot,0),
      //ICON(Seedot, 0),
      .enemyMonElevation = 0,
    }, //Seedot,
[SPECIES_NUZLEAF] = 
    {  
      //FRONT_PIC(Nuzleaf),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nuzleaf),
      BACK_COORD(0x88,0),
      //PALETTES(Nuzleaf),
      PIC_DATA_ICON_INDEX(Nuzleaf,0),
      //ICON(Nuzleaf, 0),
      .enemyMonElevation = 0,
    }, //Nuzleaf,
[SPECIES_SHIFTRY] = 
    {  
      //FRONT_PIC(Shiftry),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shiftry),
      BACK_COORD(0x88,0),
      //PALETTES(Shiftry),
      PIC_DATA_ICON_INDEX(Shiftry,0),
      //ICON(Shiftry, 0),
      .enemyMonElevation = 0,
    }, //Shiftry,
[SPECIES_NINCADA] = 
    {  
      //FRONT_PIC(Nincada),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nincada),
      BACK_COORD(0x88,0),
      //PALETTES(Nincada),
      PIC_DATA_ICON_INDEX(Nincada,0),
      //ICON(Nincada, 0),
      .enemyMonElevation = 0,
    }, //Nincada,
[SPECIES_NINJASK] = 
    {  
      //FRONT_PIC(Ninjask),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ninjask),
      BACK_COORD(0x88,0),
      //PALETTES(Ninjask),
      PIC_DATA_ICON_INDEX(Ninjask,0),
      //ICON(Ninjask, 0),
      .enemyMonElevation = 0,
    }, //Ninjask,
[SPECIES_SHEDINJA] = 
    {  
      //FRONT_PIC(Shedinja),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shedinja),
      BACK_COORD(0x88,0),
      //PALETTES(Shedinja),
      PIC_DATA_ICON_INDEX(Shedinja,0),
      //ICON(Shedinja, 0),
      .enemyMonElevation = 0,
    }, //Shedinja,
[SPECIES_TAILLOW] = 
    {  
      //FRONT_PIC(Taillow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Taillow),
      BACK_COORD(0x88,0),
      //PALETTES(Taillow),
      PIC_DATA_ICON_INDEX(Taillow,0),
      //ICON(Taillow, 0),
      .enemyMonElevation = 0,
    }, //Taillow,
[SPECIES_SWELLOW] = 
    {  
      //FRONT_PIC(Swellow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swellow),
      BACK_COORD(0x88,0),
      //PALETTES(Swellow),
      PIC_DATA_ICON_INDEX(Swellow,0),
      //ICON(Swellow, 0),
      .enemyMonElevation = 0,
    }, //Swellow,
[SPECIES_SHROOMISH] = 
    {  
      //FRONT_PIC(Shroomish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shroomish),
      BACK_COORD(0x88,0),
      //PALETTES(Shroomish),
      PIC_DATA_ICON_INDEX(Shroomish,0),
      //ICON(Shroomish, 0),
      .enemyMonElevation = 0,
    }, //Shroomish,
[SPECIES_BRELOOM] = 
    {  
      //FRONT_PIC(Breloom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Breloom),
      BACK_COORD(0x88,0),
      //PALETTES(Breloom),
      PIC_DATA_ICON_INDEX(Breloom,0),
      //ICON(Breloom, 0),
      .enemyMonElevation = 0,
    }, //Breloom,
[SPECIES_SPINDA] = 
    {  
      //FRONT_PIC(Spinda),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spinda),
      BACK_COORD(0x88,0),
      //PALETTES(Spinda),
      PIC_DATA_ICON_INDEX(Spinda,0),
      //ICON(Spinda, 0),
      .enemyMonElevation = 0,
    }, //Spinda,
[SPECIES_WINGULL] = 
    {  
      //FRONT_PIC(Wingull),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wingull),
      BACK_COORD(0x88,0),
      //PALETTES(Wingull),
      PIC_DATA_ICON_INDEX(Wingull,0),
      //ICON(Wingull, 0),
      .enemyMonElevation = 0,
    }, //Wingull,
[SPECIES_PELIPPER] = 
    {  
      //FRONT_PIC(Pelipper),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pelipper),
      BACK_COORD(0x88,0),
      //PALETTES(Pelipper),
      PIC_DATA_ICON_INDEX(Pelipper,0),
      //ICON(Pelipper, 0),
      .enemyMonElevation = 0,
    }, //Pelipper,
[SPECIES_SURSKIT] = 
    {  
      //FRONT_PIC(Surskit),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Surskit),
      BACK_COORD(0x88,0),
      //PALETTES(Surskit),
      PIC_DATA_ICON_INDEX(Surskit,0),
      //ICON(Surskit, 0),
      .enemyMonElevation = 0,
    }, //Surskit,
[SPECIES_MASQUERAIN] = 
    {  
      //FRONT_PIC(Masquerain),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Masquerain),
      BACK_COORD(0x88,0),
      //PALETTES(Masquerain),
      PIC_DATA_ICON_INDEX(Masquerain,0),
      //ICON(Masquerain, 0),
      .enemyMonElevation = 0,
    }, //Masquerain,
[SPECIES_WAILMER] = 
    {  
      //FRONT_PIC(Wailmer),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wailmer),
      BACK_COORD(0x88,0),
      //PALETTES(Wailmer),
      PIC_DATA_ICON_INDEX(Wailmer,0),
      //ICON(Wailmer, 0),
      .enemyMonElevation = 0,
    }, //Wailmer,
[SPECIES_WAILORD] = 
    {  
      //FRONT_PIC(Wailord),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wailord),
      BACK_COORD(0x88,0),
      //PALETTES(Wailord),
      PIC_DATA_ICON_INDEX(Wailord,0),
      //ICON(Wailord, 0),
      .enemyMonElevation = 0,
    }, //Wailord,
[SPECIES_SKITTY] = 
    {  
      //FRONT_PIC(Skitty),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skitty),
      BACK_COORD(0x88,0),
      //PALETTES(Skitty),
      PIC_DATA_ICON_INDEX(Skitty,0),
      //ICON(Skitty, 0),
      .enemyMonElevation = 0,
    }, //Skitty,
[SPECIES_DELCATTY] = 
    {  
      //FRONT_PIC(Delcatty),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Delcatty),
      BACK_COORD(0x88,0),
      //PALETTES(Delcatty),
      PIC_DATA_ICON_INDEX(Delcatty,0),
      //ICON(Delcatty, 0),
      .enemyMonElevation = 0,
    }, //Delcatty,
[SPECIES_KECLEON] = 
    {  
      //FRONT_PIC(Kecleon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kecleon),
      BACK_COORD(0x88,0),
      //PALETTES(Kecleon),
      PIC_DATA_ICON_INDEX(Kecleon,0),
      //ICON(Kecleon, 0),
      .enemyMonElevation = 0,
    }, //Kecleon,
[SPECIES_BALTOY] = 
    {  
      //FRONT_PIC(Baltoy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Baltoy),
      BACK_COORD(0x88,0),
      //PALETTES(Baltoy),
      PIC_DATA_ICON_INDEX(Baltoy,0),
      //ICON(Baltoy, 0),
      .enemyMonElevation = 0,
    }, //Baltoy,
[SPECIES_CLAYDOL] = 
    {  
      //FRONT_PIC(Claydol),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Claydol),
      BACK_COORD(0x88,0),
      //PALETTES(Claydol),
      PIC_DATA_ICON_INDEX(Claydol,0),
      //ICON(Claydol, 0),
      .enemyMonElevation = 0,
    }, //Claydol,
[SPECIES_NOSEPASS] = 
    {  
      //FRONT_PIC(Nosepass),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nosepass),
      BACK_COORD(0x88,0),
      //PALETTES(Nosepass),
      PIC_DATA_ICON_INDEX(Nosepass,0),
      //ICON(Nosepass, 0),
      .enemyMonElevation = 0,
    }, //Nosepass,
[SPECIES_TORKOAL] = 
    {  
      //FRONT_PIC(Torkoal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Torkoal),
      BACK_COORD(0x88,0),
      //PALETTES(Torkoal),
      PIC_DATA_ICON_INDEX(Torkoal,0),
      //ICON(Torkoal, 0),
      .enemyMonElevation = 0,
    }, //Torkoal,
[SPECIES_SABLEYE] = 
    {  
      //FRONT_PIC(Sableye),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sableye),
      BACK_COORD(0x88,0),
      //PALETTES(Sableye),
      PIC_DATA_ICON_INDEX(Sableye,0),
      //ICON(Sableye, 0),
      .enemyMonElevation = 0,
    }, //Sableye,
[SPECIES_BARBOACH] = 
    {  
      //FRONT_PIC(Barboach),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Barboach),
      BACK_COORD(0x88,0),
      //PALETTES(Barboach),
      PIC_DATA_ICON_INDEX(Barboach,0),
      //ICON(Barboach, 0),
      .enemyMonElevation = 0,
    }, //Barboach,
[SPECIES_WHISCASH] = 
    {  
      //FRONT_PIC(Whiscash),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Whiscash),
      BACK_COORD(0x88,0),
      //PALETTES(Whiscash),
      PIC_DATA_ICON_INDEX(Whiscash,0),
      //ICON(Whiscash, 0),
      .enemyMonElevation = 0,
    }, //Whiscash,
[SPECIES_LUVDISC] = 
    {  
      //FRONT_PIC(Luvdisc),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Luvdisc),
      BACK_COORD(0x88,0),
      //PALETTES(Luvdisc),
      PIC_DATA_ICON_INDEX(Luvdisc,0),
      //ICON(Luvdisc, 0),
      .enemyMonElevation = 0,
    }, //Luvdisc,
[SPECIES_CORPHISH] = 
    {  
      //FRONT_PIC(Corphish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Corphish),
      BACK_COORD(0x88,0),
      //PALETTES(Corphish),
      PIC_DATA_ICON_INDEX(Corphish,0),
      //ICON(Corphish, 0),
      .enemyMonElevation = 0,
    }, //Corphish,
[SPECIES_CRAWDAUNT] = 
    {  
      //FRONT_PIC(Crawdaunt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Crawdaunt),
      BACK_COORD(0x88,0),
      //PALETTES(Crawdaunt),
      PIC_DATA_ICON_INDEX(Crawdaunt,0),
      //ICON(Crawdaunt, 0),
      .enemyMonElevation = 0,
    }, //Crawdaunt,
[SPECIES_FEEBAS] = 
    {  
      //FRONT_PIC(Feebas),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Feebas),
      BACK_COORD(0x88,0),
      //PALETTES(Feebas),
      PIC_DATA_ICON_INDEX(Feebas,0),
      //ICON(Feebas, 0),
      .enemyMonElevation = 0,
    }, //Feebas,
[SPECIES_MILOTIC] = 
    {  
      //FRONT_PIC(Milotic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Milotic),
      BACK_COORD(0x88,0),
      //PALETTES(Milotic),
      PIC_DATA_ICON_INDEX(Milotic,0),
      //ICON(Milotic, 0),
      .enemyMonElevation = 0,
    }, //Milotic,
[SPECIES_CARVANHA] = 
    {  
      //FRONT_PIC(Carvanha),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Carvanha),
      BACK_COORD(0x88,0),
      //PALETTES(Carvanha),
      PIC_DATA_ICON_INDEX(Carvanha,0),
      //ICON(Carvanha, 0),
      .enemyMonElevation = 0,
    }, //Carvanha,
[SPECIES_SHARPEDO] = 
    {  
      //FRONT_PIC(Sharpedo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sharpedo),
      BACK_COORD(0x88,0),
      //PALETTES(Sharpedo),
      PIC_DATA_ICON_INDEX(Sharpedo,0),
      //ICON(Sharpedo, 0),
      .enemyMonElevation = 0,
    }, //Sharpedo,
[SPECIES_TRAPINCH] = 
    {  
      //FRONT_PIC(Trapinch),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Trapinch),
      BACK_COORD(0x88,0),
      //PALETTES(Trapinch),
      PIC_DATA_ICON_INDEX(Trapinch,0),
      //ICON(Trapinch, 0),
      .enemyMonElevation = 0,
    }, //Trapinch,
[SPECIES_VIBRAVA] = 
    {  
      //FRONT_PIC(Vibrava),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vibrava),
      BACK_COORD(0x88,0),
      //PALETTES(Vibrava),
      PIC_DATA_ICON_INDEX(Vibrava,0),
      //ICON(Vibrava, 0),
      .enemyMonElevation = 0,
    }, //Vibrava,
[SPECIES_FLYGON] = 
    {  
      //FRONT_PIC(Flygon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flygon),
      BACK_COORD(0x88,0),
      //PALETTES(Flygon),
      PIC_DATA_ICON_INDEX(Flygon,0),
      //ICON(Flygon, 0),
      .enemyMonElevation = 0,
    }, //Flygon,
[SPECIES_MAKUHITA] = 
    {  
      //FRONT_PIC(Makuhita),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Makuhita),
      BACK_COORD(0x88,0),
      //PALETTES(Makuhita),
      PIC_DATA_ICON_INDEX(Makuhita,0),
      //ICON(Makuhita, 0),
      .enemyMonElevation = 0,
    }, //Makuhita,
[SPECIES_HARIYAMA] = 
    {  
      //FRONT_PIC(Hariyama),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hariyama),
      BACK_COORD(0x88,0),
      //PALETTES(Hariyama),
      PIC_DATA_ICON_INDEX(Hariyama,0),
      //ICON(Hariyama, 0),
      .enemyMonElevation = 0,
    }, //Hariyama,
[SPECIES_ELECTRIKE] = 
    {  
      //FRONT_PIC(Electrike),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Electrike),
      BACK_COORD(0x88,0),
      //PALETTES(Electrike),
      PIC_DATA_ICON_INDEX(Electrike,0),
      //ICON(Electrike, 0),
      .enemyMonElevation = 0,
    }, //Electrike,
[SPECIES_MANECTRIC] = 
    {  
      //FRONT_PIC(Manectric),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Manectric),
      BACK_COORD(0x88,0),
      //PALETTES(Manectric),
      PIC_DATA_ICON_INDEX(Manectric,0),
      //ICON(Manectric, 0),
      .enemyMonElevation = 0,
    }, //Manectric,
[SPECIES_NUMEL] = 
    {  
      //FRONT_PIC(Numel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Numel),
      BACK_COORD(0x88,0),
      //PALETTES(Numel),
      PIC_DATA_ICON_INDEX(Numel,0),
      //ICON(Numel, 0),
      .enemyMonElevation = 0,
    }, //Numel,
[SPECIES_CAMERUPT] = 
    {  
      //FRONT_PIC(Camerupt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Camerupt),
      BACK_COORD(0x88,0),
      //PALETTES(Camerupt),
      PIC_DATA_ICON_INDEX(Camerupt,0),
      //ICON(Camerupt, 0),
      .enemyMonElevation = 0,
    }, //Camerupt,
[SPECIES_SPHEAL] = 
    {  
      //FRONT_PIC(Spheal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spheal),
      BACK_COORD(0x88,0),
      //PALETTES(Spheal),
      PIC_DATA_ICON_INDEX(Spheal,0),
      //ICON(Spheal, 0),
      .enemyMonElevation = 0,
    }, //Spheal,
[SPECIES_SEALEO] = 
    {  
      //FRONT_PIC(Sealeo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sealeo),
      BACK_COORD(0x88,0),
      //PALETTES(Sealeo),
      PIC_DATA_ICON_INDEX(Sealeo,0),
      //ICON(Sealeo, 0),
      .enemyMonElevation = 0,
    }, //Sealeo,
[SPECIES_WALREIN] = 
    {  
      //FRONT_PIC(Walrein),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Walrein),
      BACK_COORD(0x88,0),
      //PALETTES(Walrein),
      PIC_DATA_ICON_INDEX(Walrein,0),
      //ICON(Walrein, 0),
      .enemyMonElevation = 0,
    }, //Walrein,
[SPECIES_CACNEA] = 
    {  
      //FRONT_PIC(Cacnea),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cacnea),
      BACK_COORD(0x88,0),
      //PALETTES(Cacnea),
      PIC_DATA_ICON_INDEX(Cacnea,0),
      //ICON(Cacnea, 0),
      .enemyMonElevation = 0,
    }, //Cacnea,
[SPECIES_CACTURNE] = 
    {  
      //FRONT_PIC(Cacturne),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cacturne),
      BACK_COORD(0x88,0),
      //PALETTES(Cacturne),
      PIC_DATA_ICON_INDEX(Cacturne,0),
      //ICON(Cacturne, 0),
      .enemyMonElevation = 0,
    }, //Cacturne,
[SPECIES_SNORUNT] = 
    {  
      //FRONT_PIC(Snorunt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Snorunt),
      BACK_COORD(0x88,0),
      //PALETTES(Snorunt),
      PIC_DATA_ICON_INDEX(Snorunt,0),
      //ICON(Snorunt, 0),
      .enemyMonElevation = 0,
    }, //Snorunt,
[SPECIES_GLALIE] = 
    {  
      //FRONT_PIC(Glalie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Glalie),
      BACK_COORD(0x88,0),
      //PALETTES(Glalie),
      PIC_DATA_ICON_INDEX(Glalie,0),
      //ICON(Glalie, 0),
      .enemyMonElevation = 0,
    }, //Glalie,
[SPECIES_LUNATONE] = 
    {  
      //FRONT_PIC(Lunatone),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lunatone),
      BACK_COORD(0x88,0),
      //PALETTES(Lunatone),
      PIC_DATA_ICON_INDEX(Lunatone,0),
      //ICON(Lunatone, 0),
      .enemyMonElevation = 0,
    }, //Lunatone,
[SPECIES_SOLROCK] = 
    {  
      //FRONT_PIC(Solrock),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Solrock),
      BACK_COORD(0x88,0),
      //PALETTES(Solrock),
      PIC_DATA_ICON_INDEX(Solrock,0),
      //ICON(Solrock, 0),
      .enemyMonElevation = 0,
    }, //Solrock,
[SPECIES_AZURILL] = 
    {  
      //FRONT_PIC(Azurill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Azurill),
      BACK_COORD(0x88,0),
      //PALETTES(Azurill),
      PIC_DATA_ICON_INDEX(Azurill,0),
      //ICON(Azurill, 0),
      .enemyMonElevation = 0,
    }, //Azurill,
[SPECIES_SPOINK] = 
    {  
      //FRONT_PIC(Spoink),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spoink),
      BACK_COORD(0x88,0),
      //PALETTES(Spoink),
      PIC_DATA_ICON_INDEX(Spoink,0),
      //ICON(Spoink, 0),
      .enemyMonElevation = 0,
    }, //Spoink,
[SPECIES_GRUMPIG] = 
    {  
      //FRONT_PIC(Grumpig),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grumpig),
      BACK_COORD(0x88,0),
      //PALETTES(Grumpig),
      PIC_DATA_ICON_INDEX(Grumpig,0),
      //ICON(Grumpig, 0),
      .enemyMonElevation = 0,
    }, //Grumpig,
[SPECIES_PLUSLE] = 
    {  
      //FRONT_PIC(Plusle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Plusle),
      BACK_COORD(0x88,0),
      //PALETTES(Plusle),
      PIC_DATA_ICON_INDEX(Plusle,0),
      //ICON(Plusle, 0),
      .enemyMonElevation = 0,
    }, //Plusle,
[SPECIES_MINUN] = 
    {  
      //FRONT_PIC(Minun),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Minun),
      BACK_COORD(0x88,0),
      //PALETTES(Minun),
      PIC_DATA_ICON_INDEX(Minun,0),
      //ICON(Minun, 0),
      .enemyMonElevation = 0,
    }, //Minun,
[SPECIES_MAWILE] = 
    {  
      //FRONT_PIC(Mawile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mawile),
      BACK_COORD(0x88,0),
      //PALETTES(Mawile),
      PIC_DATA_ICON_INDEX(Mawile,0),
      //ICON(Mawile, 0),
      .enemyMonElevation = 0,
    }, //Mawile,
[SPECIES_MEDITITE] = 
    {  
      //FRONT_PIC(Meditite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Meditite),
      BACK_COORD(0x88,0),
      //PALETTES(Meditite),
      PIC_DATA_ICON_INDEX(Meditite,0),
      //ICON(Meditite, 0),
      .enemyMonElevation = 0,
    }, //Meditite,
[SPECIES_MEDICHAM] = 
    {  
      //FRONT_PIC(Medicham),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Medicham),
      BACK_COORD(0x88,0),
      //PALETTES(Medicham),
      PIC_DATA_ICON_INDEX(Medicham,0),
      //ICON(Medicham, 0),
      .enemyMonElevation = 0,
    }, //Medicham,
[SPECIES_SWABLU] = 
    {  
      //FRONT_PIC(Swablu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swablu),
      BACK_COORD(0x88,0),
      //PALETTES(Swablu),
      PIC_DATA_ICON_INDEX(Swablu,0),
      //ICON(Swablu, 0),
      .enemyMonElevation = 0,
    }, //Swablu,
[SPECIES_ALTARIA] = 
    {  
      //FRONT_PIC(Altaria),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Altaria),
      BACK_COORD(0x88,0),
      //PALETTES(Altaria),
      PIC_DATA_ICON_INDEX(Altaria,0),
      //ICON(Altaria, 0),
      .enemyMonElevation = 0,
    }, //Altaria,
[SPECIES_WYNAUT] = 
    {  
      //FRONT_PIC(Wynaut),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wynaut),
      BACK_COORD(0x88,0),
      //PALETTES(Wynaut),
      PIC_DATA_ICON_INDEX(Wynaut,0),
      //ICON(Wynaut, 0),
      .enemyMonElevation = 0,
    }, //Wynaut,
[SPECIES_DUSKULL] = 
    {  
      //FRONT_PIC(Duskull),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Duskull),
      BACK_COORD(0x88,0),
      //PALETTES(Duskull),
      PIC_DATA_ICON_INDEX(Duskull,0),
      //ICON(Duskull, 0),
      .enemyMonElevation = 0,
    }, //Duskull,
[SPECIES_DUSCLOPS] = 
    {  
      //FRONT_PIC(Dusclops),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dusclops),
      BACK_COORD(0x88,0),
      //PALETTES(Dusclops),
      PIC_DATA_ICON_INDEX(Dusclops,0),
      //ICON(Dusclops, 0),
      .enemyMonElevation = 0,
    }, //Dusclops,
[SPECIES_ROSELIA] = 
    {  
      //FRONT_PIC(Roselia),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Roselia),
      BACK_COORD(0x88,0),
      //PALETTES(Roselia),
      PIC_DATA_ICON_INDEX(Roselia,0),
      //ICON(Roselia, 0),
      .enemyMonElevation = 0,
    }, //Roselia,
[SPECIES_SLAKOTH] = 
    {  
      //FRONT_PIC(Slakoth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slakoth),
      BACK_COORD(0x88,0),
      //PALETTES(Slakoth),
      PIC_DATA_ICON_INDEX(Slakoth,0),
      //ICON(Slakoth, 0),
      .enemyMonElevation = 0,
    }, //Slakoth,
[SPECIES_VIGOROTH] = 
    {  
      //FRONT_PIC(Vigoroth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vigoroth),
      BACK_COORD(0x88,0),
      //PALETTES(Vigoroth),
      PIC_DATA_ICON_INDEX(Vigoroth,0),
      //ICON(Vigoroth, 0),
      .enemyMonElevation = 0,
    }, //Vigoroth,
[SPECIES_SLAKING] = 
    {  
      //FRONT_PIC(Slaking),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slaking),
      BACK_COORD(0x88,0),
      //PALETTES(Slaking),
      PIC_DATA_ICON_INDEX(Slaking,0),
      //ICON(Slaking, 0),
      .enemyMonElevation = 0,
    }, //Slaking,
[SPECIES_GULPIN] = 
    {  
      //FRONT_PIC(Gulpin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gulpin),
      BACK_COORD(0x88,0),
      //PALETTES(Gulpin),
      PIC_DATA_ICON_INDEX(Gulpin,0),
      //ICON(Gulpin, 0),
      .enemyMonElevation = 0,
    }, //Gulpin,
[SPECIES_SWALOT] = 
    {  
      //FRONT_PIC(Swalot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swalot),
      BACK_COORD(0x88,0),
      //PALETTES(Swalot),
      PIC_DATA_ICON_INDEX(Swalot,0),
      //ICON(Swalot, 0),
      .enemyMonElevation = 0,
    }, //Swalot,
[SPECIES_TROPIUS] = 
    {  
      //FRONT_PIC(Tropius),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tropius),
      BACK_COORD(0x88,0),
      //PALETTES(Tropius),
      PIC_DATA_ICON_INDEX(Tropius,0),
      //ICON(Tropius, 0),
      .enemyMonElevation = 0,
    }, //Tropius,
[SPECIES_WHISMUR] = 
    {  
      //FRONT_PIC(Whismur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Whismur),
      BACK_COORD(0x88,0),
      //PALETTES(Whismur),
      PIC_DATA_ICON_INDEX(Whismur,0),
      //ICON(Whismur, 0),
      .enemyMonElevation = 0,
    }, //Whismur,
[SPECIES_LOUDRED] = 
    {  
      //FRONT_PIC(Loudred),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Loudred),
      BACK_COORD(0x88,0),
      //PALETTES(Loudred),
      PIC_DATA_ICON_INDEX(Loudred,0),
      //ICON(Loudred, 0),
      .enemyMonElevation = 0,
    }, //Loudred,
[SPECIES_EXPLOUD] = 
    {  
      //FRONT_PIC(Exploud),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Exploud),
      BACK_COORD(0x88,0),
      //PALETTES(Exploud),
      PIC_DATA_ICON_INDEX(Exploud,0),
      //ICON(Exploud, 0),
      .enemyMonElevation = 0,
    }, //Exploud,
[SPECIES_CLAMPERL] = 
    {  
      //FRONT_PIC(Clamperl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clamperl),
      BACK_COORD(0x88,0),
      //PALETTES(Clamperl),
      PIC_DATA_ICON_INDEX(Clamperl,0),
      //ICON(Clamperl, 0),
      .enemyMonElevation = 0,
    }, //Clamperl,
[SPECIES_HUNTAIL] = 
    {  
      //FRONT_PIC(Huntail),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Huntail),
      BACK_COORD(0x88,0),
      //PALETTES(Huntail),
      PIC_DATA_ICON_INDEX(Huntail,0),
      //ICON(Huntail, 0),
      .enemyMonElevation = 0,
    }, //Huntail,
[SPECIES_GOREBYSS] = 
    {  
      //FRONT_PIC(Gorebyss),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gorebyss),
      BACK_COORD(0x88,0),
      //PALETTES(Gorebyss),
      PIC_DATA_ICON_INDEX(Gorebyss,0),
      //ICON(Gorebyss, 0),
      .enemyMonElevation = 0,
    }, //Gorebyss,
[SPECIES_ABSOL] = 
    {  
      //FRONT_PIC(Absol),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Absol),
      BACK_COORD(0x88,0),
      //PALETTES(Absol),
      PIC_DATA_ICON_INDEX(Absol,0),
      //ICON(Absol, 0),
      .enemyMonElevation = 0,
    }, //Absol,
[SPECIES_SHUPPET] = 
    {  
      //FRONT_PIC(Shuppet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shuppet),
      BACK_COORD(0x88,0),
      //PALETTES(Shuppet),
      PIC_DATA_ICON_INDEX(Shuppet,0),
      //ICON(Shuppet, 0),
      .enemyMonElevation = 0,
    }, //Shuppet,
[SPECIES_BANETTE] = 
    {  
      //FRONT_PIC(Banette),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Banette),
      BACK_COORD(0x88,0),
      //PALETTES(Banette),
      PIC_DATA_ICON_INDEX(Banette,0),
      //ICON(Banette, 0),
      .enemyMonElevation = 0,
    }, //Banette,
[SPECIES_SEVIPER] = 
    {  
      //FRONT_PIC(Seviper),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Seviper),
      BACK_COORD(0x88,0),
      //PALETTES(Seviper),
      PIC_DATA_ICON_INDEX(Seviper,0),
      //ICON(Seviper, 0),
      .enemyMonElevation = 0,
    }, //Seviper,
[SPECIES_ZANGOOSE] = 
    {  
      //FRONT_PIC(Zangoose),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zangoose),
      BACK_COORD(0x88,0),
      //PALETTES(Zangoose),
      PIC_DATA_ICON_INDEX(Zangoose,0),
      //ICON(Zangoose, 0),
      .enemyMonElevation = 0,
    }, //Zangoose,
[SPECIES_RELICANTH] = 
    {  
      //FRONT_PIC(Relicanth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Relicanth),
      BACK_COORD(0x88,0),
      //PALETTES(Relicanth),
      PIC_DATA_ICON_INDEX(Relicanth,0),
      //ICON(Relicanth, 0),
      .enemyMonElevation = 0,
    }, //Relicanth,
[SPECIES_ARON] = 
    {  
      //FRONT_PIC(Aron),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aron),
      BACK_COORD(0x88,0),
      //PALETTES(Aron),
      PIC_DATA_ICON_INDEX(Aron,0),
      //ICON(Aron, 0),
      .enemyMonElevation = 0,
    }, //Aron,
[SPECIES_LAIRON] = 
    {  
      //FRONT_PIC(Lairon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lairon),
      BACK_COORD(0x88,0),
      //PALETTES(Lairon),
      PIC_DATA_ICON_INDEX(Lairon,0),
      //ICON(Lairon, 0),
      .enemyMonElevation = 0,
    }, //Lairon,
[SPECIES_AGGRON] = 
    {  
      //FRONT_PIC(Aggron),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aggron),
      BACK_COORD(0x88,0),
      //PALETTES(Aggron),
      PIC_DATA_ICON_INDEX(Aggron,0),
      //ICON(Aggron, 0),
      .enemyMonElevation = 0,
    }, //Aggron,
[SPECIES_CASTFORM] = 
    {  
      //FRONT_PIC(Castform),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Castform),
      BACK_COORD(0x88,0),
      //PALETTES(Castform),
      PIC_DATA_ICON_INDEX(Castform,0),
      //ICON(Castform, 0),
      .enemyMonElevation = 0,
    }, //Castform,
[SPECIES_VOLBEAT] = 
    {  
      //FRONT_PIC(Volbeat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Volbeat),
      BACK_COORD(0x88,0),
      //PALETTES(Volbeat),
      PIC_DATA_ICON_INDEX(Volbeat,0),
      //ICON(Volbeat, 0),
      .enemyMonElevation = 0,
    }, //Volbeat,
[SPECIES_ILLUMISE] = 
    {  
      //FRONT_PIC(Illumise),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Illumise),
      BACK_COORD(0x88,0),
      //PALETTES(Illumise),
      PIC_DATA_ICON_INDEX(Illumise,0),
      //ICON(Illumise, 0),
      .enemyMonElevation = 0,
    }, //Illumise,
[SPECIES_LILEEP] = 
    {  
      //FRONT_PIC(Lileep),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lileep),
      BACK_COORD(0x88,0),
      //PALETTES(Lileep),
      PIC_DATA_ICON_INDEX(Lileep,0),
      //ICON(Lileep, 0),
      .enemyMonElevation = 0,
    }, //Lileep,
[SPECIES_CRADILY] = 
    {  
      //FRONT_PIC(Cradily),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cradily),
      BACK_COORD(0x88,0),
      //PALETTES(Cradily),
      PIC_DATA_ICON_INDEX(Cradily,0),
      //ICON(Cradily, 0),
      .enemyMonElevation = 0,
    }, //Cradily,
[SPECIES_ANORITH] = 
    {  
      //FRONT_PIC(Anorith),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Anorith),
      BACK_COORD(0x88,0),
      //PALETTES(Anorith),
      PIC_DATA_ICON_INDEX(Anorith,0),
      //ICON(Anorith, 0),
      .enemyMonElevation = 0,
    }, //Anorith,
[SPECIES_ARMALDO] = 
    {  
      //FRONT_PIC(Armaldo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Armaldo),
      BACK_COORD(0x88,0),
      //PALETTES(Armaldo),
      PIC_DATA_ICON_INDEX(Armaldo,0),
      //ICON(Armaldo, 0),
      .enemyMonElevation = 0,
    }, //Armaldo,
[SPECIES_RALTS] = 
    {  
      //FRONT_PIC(Ralts),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ralts),
      BACK_COORD(0x88,0),
      //PALETTES(Ralts),
      PIC_DATA_ICON_INDEX(Ralts,0),
      //ICON(Ralts, 0),
      .enemyMonElevation = 0,
    }, //Ralts,
[SPECIES_KIRLIA] = 
    {  
      //FRONT_PIC(Kirlia),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kirlia),
      BACK_COORD(0x88,0),
      //PALETTES(Kirlia),
      PIC_DATA_ICON_INDEX(Kirlia,0),
      //ICON(Kirlia, 0),
      .enemyMonElevation = 0,
    }, //Kirlia,
[SPECIES_GARDEVOIR] = 
    {  
      //FRONT_PIC(Gardevoir),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gardevoir),
      BACK_COORD(0x88,0),
      //PALETTES(Gardevoir),
      PIC_DATA_ICON_INDEX(Gardevoir,0),
      //ICON(Gardevoir, 0),
      .enemyMonElevation = 0,
    }, //Gardevoir,
[SPECIES_BAGON] = 
    {  
      //FRONT_PIC(Bagon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bagon),
      BACK_COORD(0x88,0),
      //PALETTES(Bagon),
      PIC_DATA_ICON_INDEX(Bagon,0),
      //ICON(Bagon, 0),
      .enemyMonElevation = 0,
    }, //Bagon,
[SPECIES_SHELGON] = 
    {  
      //FRONT_PIC(Shelgon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shelgon),
      BACK_COORD(0x88,0),
      //PALETTES(Shelgon),
      PIC_DATA_ICON_INDEX(Shelgon,0),
      //ICON(Shelgon, 0),
      .enemyMonElevation = 0,
    }, //Shelgon,
[SPECIES_SALAMENCE] = 
    {  
      //FRONT_PIC(Salamence),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Salamence),
      BACK_COORD(0x88,0),
      //PALETTES(Salamence),
      PIC_DATA_ICON_INDEX(Salamence,0),
      //ICON(Salamence, 0),
      .enemyMonElevation = 0,
    }, //Salamence,
[SPECIES_BELDUM] = 
    {  
      //FRONT_PIC(Beldum),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Beldum),
      BACK_COORD(0x88,0),
      //PALETTES(Beldum),
      PIC_DATA_ICON_INDEX(Beldum,0),
      //ICON(Beldum, 0),
      .enemyMonElevation = 0,
    }, //Beldum,
[SPECIES_METANG] = 
    {  
      //FRONT_PIC(Metang),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Metang),
      BACK_COORD(0x88,0),
      //PALETTES(Metang),
      PIC_DATA_ICON_INDEX(Metang,0),
      //ICON(Metang, 0),
      .enemyMonElevation = 0,
    }, //Metang,
[SPECIES_METAGROSS] = 
    {  
      //FRONT_PIC(Metagross),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Metagross),
      BACK_COORD(0x88,0),
      //PALETTES(Metagross),
      PIC_DATA_ICON_INDEX(Metagross,0),
      //ICON(Metagross, 0),
      .enemyMonElevation = 0,
    }, //Metagross,
[SPECIES_REGIROCK] = 
    {  
      //FRONT_PIC(Regirock),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Regirock),
      BACK_COORD(0x88,0),
      //PALETTES(Regirock),
      PIC_DATA_ICON_INDEX(Regirock,0),
      //ICON(Regirock, 0),
      .enemyMonElevation = 0,
    }, //Regirock,
[SPECIES_REGICE] = 
    {  
      //FRONT_PIC(Regice),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Regice),
      BACK_COORD(0x88,0),
      //PALETTES(Regice),
      PIC_DATA_ICON_INDEX(Regice,0),
      //ICON(Regice, 0),
      .enemyMonElevation = 0,
    }, //Regice,
[SPECIES_REGISTEEL] = 
    {  
      //FRONT_PIC(Registeel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Registeel),
      BACK_COORD(0x88,0),
      //PALETTES(Registeel),
      PIC_DATA_ICON_INDEX(Registeel,0),
      //ICON(Registeel, 0),
      .enemyMonElevation = 0,
    }, //Registeel,
[SPECIES_KYOGRE] = 
    {  
      //FRONT_PIC(Kyogre),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kyogre),
      BACK_COORD(0x88,0),
      //PALETTES(Kyogre),
      PIC_DATA_ICON_INDEX(Kyogre,0),
      //ICON(Kyogre, 0),
      .enemyMonElevation = 0,
    }, //Kyogre,
[SPECIES_GROUDON] = 
    {  
      //FRONT_PIC(Groudon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Groudon),
      BACK_COORD(0x88,0),
      //PALETTES(Groudon),
      PIC_DATA_ICON_INDEX(Groudon,0),
      //ICON(Groudon, 0),
      .enemyMonElevation = 0,
    }, //Groudon,
[SPECIES_RAYQUAZA] = 
    {  
      //FRONT_PIC(Rayquaza),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rayquaza),
      BACK_COORD(0x88,0),
      //PALETTES(Rayquaza),
      PIC_DATA_ICON_INDEX(Rayquaza,0),
      //ICON(Rayquaza, 0),
      .enemyMonElevation = 0,
    }, //Rayquaza,
[SPECIES_LATIAS] = 
    {  
      //FRONT_PIC(Latias),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Latias),
      BACK_COORD(0x88,0),
      //PALETTES(Latias),
      PIC_DATA_ICON_INDEX(Latias,0),
      //ICON(Latias, 0),
      .enemyMonElevation = 0,
    }, //Latias,
[SPECIES_LATIOS] = 
    {  
      //FRONT_PIC(Latios),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Latios),
      BACK_COORD(0x88,0),
      //PALETTES(Latios),
      PIC_DATA_ICON_INDEX(Latios,0),
      //ICON(Latios, 0),
      .enemyMonElevation = 0,
    }, //Latios,
[SPECIES_JIRACHI] = 
    {  
      //FRONT_PIC(Jirachi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Jirachi),
      BACK_COORD(0x88,0),
      //PALETTES(Jirachi),
      PIC_DATA_ICON_INDEX(Jirachi,0),
      //ICON(Jirachi, 0),
      .enemyMonElevation = 0,
    }, //Jirachi,
[SPECIES_DEOXYS] = 
    {  
      //FRONT_PIC(Deoxys),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Deoxys),
      BACK_COORD(0x88,0),
      //PALETTES(Deoxys),
      PIC_DATA_ICON_INDEX(Deoxys,0),
      //ICON(Deoxys, 0),
      .enemyMonElevation = 0,
    }, //Deoxys,
[SPECIES_CHIMECHO] = 
    {  
      //FRONT_PIC(Chimecho),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chimecho),
      BACK_COORD(0x88,0),
      //PALETTES(Chimecho),
      PIC_DATA_ICON_INDEX(Chimecho,0),
      //ICON(Chimecho, 0),
      .enemyMonElevation = 0,
    }, //Chimecho,
[SPECIES_EGG] = 
    {  
      //FRONT_PIC(Egg),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Egg),
      BACK_COORD(0x88,0),
      //PALETTES(Egg),
      PIC_DATA_ICON_INDEX(Egg,0),
      //ICON(Egg, 0),
      .enemyMonElevation = 0,
    }, //Egg,
[SPECIES_UNOWN_B] = 
    {  
      //FRONT_PIC(UnownB),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownB),
      BACK_COORD(0x88,0),
      //PALETTES(UnownB),
      PIC_DATA_ICON_INDEX(UnownB,0),
      //ICON(UnownB, 0),
      .enemyMonElevation = 0,
    }, //UnownB,
[SPECIES_UNOWN_C] = 
    {  
      //FRONT_PIC(UnownC),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownC),
      BACK_COORD(0x88,0),
      //PALETTES(UnownC),
      PIC_DATA_ICON_INDEX(UnownC,0),
      //ICON(UnownC, 0),
      .enemyMonElevation = 0,
    }, //UnownC,
[SPECIES_UNOWN_D] = 
    {  
      //FRONT_PIC(UnownD),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownD),
      BACK_COORD(0x88,0),
      //PALETTES(UnownD),
      PIC_DATA_ICON_INDEX(UnownD,0),
      //ICON(UnownD, 0),
      .enemyMonElevation = 0,
    }, //UnownD,
[SPECIES_UNOWN_E] = 
    {  
      //FRONT_PIC(UnownE),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownE),
      BACK_COORD(0x88,0),
      //PALETTES(UnownE),
      PIC_DATA_ICON_INDEX(UnownE,0),
      //ICON(UnownE, 0),
      .enemyMonElevation = 0,
    }, //UnownE,
[SPECIES_UNOWN_F] = 
    {  
      //FRONT_PIC(UnownF),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownF),
      BACK_COORD(0x88,0),
      //PALETTES(UnownF),
      PIC_DATA_ICON_INDEX(UnownF,0),
      //ICON(UnownF, 0),
      .enemyMonElevation = 0,
    }, //UnownF,
[SPECIES_UNOWN_G] = 
    {  
      //FRONT_PIC(UnownG),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownG),
      BACK_COORD(0x88,0),
      //PALETTES(UnownG),
      PIC_DATA_ICON_INDEX(UnownG,0),
      //ICON(UnownG, 0),
      .enemyMonElevation = 0,
    }, //UnownG,
[SPECIES_UNOWN_H] = 
    {  
      //FRONT_PIC(UnownH),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownH),
      BACK_COORD(0x88,0),
      //PALETTES(UnownH),
      PIC_DATA_ICON_INDEX(UnownH,0),
      //ICON(UnownH, 0),
      .enemyMonElevation = 0,
    }, //UnownH,
[SPECIES_UNOWN_I] = 
    {  
      //FRONT_PIC(UnownI),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownI),
      BACK_COORD(0x88,0),
      //PALETTES(UnownI),
      PIC_DATA_ICON_INDEX(UnownI,0),
      //ICON(UnownI, 0),
      .enemyMonElevation = 0,
    }, //UnownI,
[SPECIES_UNOWN_J] = 
    {  
      //FRONT_PIC(UnownJ),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownJ),
      BACK_COORD(0x88,0),
      //PALETTES(UnownJ),
      PIC_DATA_ICON_INDEX(UnownJ,0),
      //ICON(UnownJ, 0),
      .enemyMonElevation = 0,
    }, //UnownJ,
[SPECIES_UNOWN_K] = 
    {  
      //FRONT_PIC(UnownK),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownK),
      BACK_COORD(0x88,0),
      //PALETTES(UnownK),
      PIC_DATA_ICON_INDEX(UnownK,0),
      //ICON(UnownK, 0),
      .enemyMonElevation = 0,
    }, //UnownK,
[SPECIES_UNOWN_L] = 
    {  
      //FRONT_PIC(UnownL),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownL),
      BACK_COORD(0x88,0),
      //PALETTES(UnownL),
      PIC_DATA_ICON_INDEX(UnownL,0),
      //ICON(UnownL, 0),
      .enemyMonElevation = 0,
    }, //UnownL,
[SPECIES_UNOWN_M] = 
    {  
      //FRONT_PIC(UnownM),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownM),
      BACK_COORD(0x88,0),
      //PALETTES(UnownM),
      PIC_DATA_ICON_INDEX(UnownM,0),
      //ICON(UnownM, 0),
      .enemyMonElevation = 0,
    }, //UnownM,
[SPECIES_UNOWN_N] = 
    {  
      //FRONT_PIC(UnownN),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownN),
      BACK_COORD(0x88,0),
      //PALETTES(UnownN),
      PIC_DATA_ICON_INDEX(UnownN,0),
      //ICON(UnownN, 0),
      .enemyMonElevation = 0,
    }, //UnownN,
[SPECIES_UNOWN_O] = 
    {  
      //FRONT_PIC(UnownO),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownO),
      BACK_COORD(0x88,0),
      //PALETTES(UnownO),
      PIC_DATA_ICON_INDEX(UnownO,0),
      //ICON(UnownO, 0),
      .enemyMonElevation = 0,
    }, //UnownO,
[SPECIES_UNOWN_P] = 
    {  
      //FRONT_PIC(UnownP),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownP),
      BACK_COORD(0x88,0),
      //PALETTES(UnownP),
      PIC_DATA_ICON_INDEX(UnownP,0),
      //ICON(UnownP, 0),
      .enemyMonElevation = 0,
    }, //UnownP,
[SPECIES_UNOWN_Q] = 
    {  
      //FRONT_PIC(UnownQ),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownQ),
      BACK_COORD(0x88,0),
      //PALETTES(UnownQ),
      PIC_DATA_ICON_INDEX(UnownQ,0),
      //ICON(UnownQ, 0),
      .enemyMonElevation = 0,
    }, //UnownQ,
[SPECIES_UNOWN_R] = 
    {  
      //FRONT_PIC(UnownR),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownR),
      BACK_COORD(0x88,0),
      //PALETTES(UnownR),
      PIC_DATA_ICON_INDEX(UnownR,0),
      //ICON(UnownR, 0),
      .enemyMonElevation = 0,
    }, //UnownR,
[SPECIES_UNOWN_S] = 
    {  
      //FRONT_PIC(UnownS),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownS),
      BACK_COORD(0x88,0),
      //PALETTES(UnownS),
      PIC_DATA_ICON_INDEX(UnownS,0),
      //ICON(UnownS, 0),
      .enemyMonElevation = 0,
    }, //UnownS,
[SPECIES_UNOWN_T] = 
    {  
      //FRONT_PIC(UnownT),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownT),
      BACK_COORD(0x88,0),
      //PALETTES(UnownT),
      PIC_DATA_ICON_INDEX(UnownT,0),
      //ICON(UnownT, 0),
      .enemyMonElevation = 0,
    }, //UnownT,
[SPECIES_UNOWN_U] = 
    {  
      //FRONT_PIC(UnownU),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownU),
      BACK_COORD(0x88,0),
      //PALETTES(UnownU),
      PIC_DATA_ICON_INDEX(UnownU,0),
      //ICON(UnownU, 0),
      .enemyMonElevation = 0,
    }, //UnownU,
[SPECIES_UNOWN_V] = 
    {  
      //FRONT_PIC(UnownV),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownV),
      BACK_COORD(0x88,0),
      //PALETTES(UnownV),
      PIC_DATA_ICON_INDEX(UnownV,0),
      //ICON(UnownV, 0),
      .enemyMonElevation = 0,
    }, //UnownV,
[SPECIES_UNOWN_W] = 
    {  
      //FRONT_PIC(UnownW),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownW),
      BACK_COORD(0x88,0),
      //PALETTES(UnownW),
      PIC_DATA_ICON_INDEX(UnownW,0),
      //ICON(UnownW, 0),
      .enemyMonElevation = 0,
    }, //UnownW,
[SPECIES_UNOWN_X] = 
    {  
      //FRONT_PIC(UnownX),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownX),
      BACK_COORD(0x88,0),
      //PALETTES(UnownX),
      PIC_DATA_ICON_INDEX(UnownX,0),
      //ICON(UnownX, 0),
      .enemyMonElevation = 0,
    }, //UnownX,
[SPECIES_UNOWN_Y] = 
    {  
      //FRONT_PIC(UnownY),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownY),
      BACK_COORD(0x88,0),
      //PALETTES(UnownY),
      PIC_DATA_ICON_INDEX(UnownY,0),
      //ICON(UnownY, 0),
      .enemyMonElevation = 0,
    }, //UnownY,
[SPECIES_UNOWN_Z] = 
    {  
      //FRONT_PIC(UnownZ),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownZ),
      BACK_COORD(0x88,0),
      //PALETTES(UnownZ),
      PIC_DATA_ICON_INDEX(UnownZ,0),
      //ICON(UnownZ, 0),
      .enemyMonElevation = 0,
    }, //UnownZ,
[SPECIES_UNOWN_EMARK] = 
    {  
      //FRONT_PIC(UnownEmark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownEmark),
      BACK_COORD(0x88,0),
      //PALETTES(UnownEmark),
      PIC_DATA_ICON_INDEX(UnownEmark,0),
      //ICON(UnownEmark, 0),
      .enemyMonElevation = 0,
    }, //UnownExclamationMark,
[SPECIES_UNOWN_QMARK] = 
    {  
      //FRONT_PIC(UnownQmark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnownQmark),
      BACK_COORD(0x88,0),
      //PALETTES(UnownQmark),
      PIC_DATA_ICON_INDEX(UnownQmark,0),
      //ICON(UnownQmark, 0),
      .enemyMonElevation = 0,
    }, //UnownQuestionMark, //ok I see now part of problem, this doeesn't have a comma and others are misaligned.
[SPECIES_TURTWIG] = 
    {  
      //FRONT_PIC(Turtwig),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Turtwig),
      BACK_COORD(0x88,0),
      //PALETTES(Turtwig),
      PIC_DATA_ICON_INDEX(Turtwig,0),
      //ICON(Turtwig, 0),
      .enemyMonElevation = 0,
    }, //Turtwig,
[SPECIES_GROTLE] = 
    {  
      //FRONT_PIC(Grotle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grotle),
      BACK_COORD(0x88,0),
      //PALETTES(Grotle),
      PIC_DATA_ICON_INDEX(Grotle,0),
      //ICON(Grotle, 0),
      .enemyMonElevation = 0,
    }, //Grotle,
[SPECIES_TORTERRA] = 
    {  
      //FRONT_PIC(Torterra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Torterra),
      BACK_COORD(0x88,0),
      //PALETTES(Torterra),
      PIC_DATA_ICON_INDEX(Torterra,0),
      //ICON(Torterra, 0),
      .enemyMonElevation = 0,
    }, //Torterra,
[SPECIES_CHIMCHAR] = 
    {  
      //FRONT_PIC(Chimchar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chimchar),
      BACK_COORD(0x88,0),
      //PALETTES(Chimchar),
      PIC_DATA_ICON_INDEX(Chimchar,0),
      //ICON(Chimchar, 0),
      .enemyMonElevation = 0,
    }, //Chimchar,
[SPECIES_MONFERNO] = 
    {  
      //FRONT_PIC(Monferno),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Monferno),
      BACK_COORD(0x88,0),
      //PALETTES(Monferno),
      PIC_DATA_ICON_INDEX(Monferno,0),
      //ICON(Monferno, 0),
      .enemyMonElevation = 0,
    }, //Monferno,
[SPECIES_INFERNAPE] = 
    {  
      //FRONT_PIC(Infernape),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Infernape),
      BACK_COORD(0x88,0),
      //PALETTES(Infernape),
      PIC_DATA_ICON_INDEX(Infernape,0),
      //ICON(Infernape, 0),
      .enemyMonElevation = 0,
    }, //Infernape,
[SPECIES_PIPLUP] = 
    {  
      //FRONT_PIC(Piplup),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Piplup),
      BACK_COORD(0x88,0),
      //PALETTES(Piplup),
      PIC_DATA_ICON_INDEX(Piplup,0),
      //ICON(Piplup, 0),
      .enemyMonElevation = 0,
    }, //Piplup,
[SPECIES_PRINPLUP] = 
    {  
      //FRONT_PIC(Prinplup),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Prinplup),
      BACK_COORD(0x88,0),
      //PALETTES(Prinplup),
      PIC_DATA_ICON_INDEX(Prinplup,0),
      //ICON(Prinplup, 0),
      .enemyMonElevation = 0,
    }, //Prinplup,
[SPECIES_EMPOLEON] = 
    {  
      //FRONT_PIC(Empoleon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Empoleon),
      BACK_COORD(0x88,0),
      //PALETTES(Empoleon),
      PIC_DATA_ICON_INDEX(Empoleon,0),
      //ICON(Empoleon, 0),
      .enemyMonElevation = 0,
    }, //Empoleon,
[SPECIES_STARLY] = 
    {  
      //FRONT_PIC(Starly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Starly),
      BACK_COORD(0x88,0),
      //PALETTES(Starly),
      PIC_DATA_ICON_INDEX(Starly,0),
      //ICON(Starly, 0),
      .enemyMonElevation = 0,
    }, //Starly,
[SPECIES_STARAVIA] = 
    {  
      //FRONT_PIC(Staravia),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Staravia),
      BACK_COORD(0x88,0),
      //PALETTES(Staravia),
      PIC_DATA_ICON_INDEX(Staravia,0),
      //ICON(Staravia, 0),
      .enemyMonElevation = 0,
    }, //Staravia,
[SPECIES_STARAPTOR] = 
    {  
      //FRONT_PIC(Staraptor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Staraptor),
      BACK_COORD(0x88,0),
      //PALETTES(Staraptor),
      PIC_DATA_ICON_INDEX(Staraptor,0),
      //ICON(Staraptor, 0),
      .enemyMonElevation = 0,
    }, //Staraptor,
[SPECIES_BIDOOF] = 
    {  
      //FRONT_PIC(Bidoof),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bidoof),
      BACK_COORD(0x88,0),
      //PALETTES(Bidoof),
      PIC_DATA_ICON_INDEX(Bidoof,0),
      //ICON(Bidoof, 0),
      .enemyMonElevation = 0,
    }, //Bidoof,
[SPECIES_BIBAREL] = 
    {  
      //FRONT_PIC(Bibarel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bibarel),
      BACK_COORD(0x88,0),
      //PALETTES(Bibarel),
      PIC_DATA_ICON_INDEX(Bibarel,0),
      //ICON(Bibarel, 0),
      .enemyMonElevation = 0,
    }, //Bibarel,
[SPECIES_KRICKETOT] = 
    {  
      //FRONT_PIC(Kricketot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kricketot),
      BACK_COORD(0x88,0),
      //PALETTES(Kricketot),
      PIC_DATA_ICON_INDEX(Kricketot,0),
      //ICON(Kricketot, 0),
      .enemyMonElevation = 0,
    }, //Kricketot,
[SPECIES_KRICKETUNE] = 
    {  
      //FRONT_PIC(Kricketune),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kricketune),
      BACK_COORD(0x88,0),
      //PALETTES(Kricketune),
      PIC_DATA_ICON_INDEX(Kricketune,0),
      //ICON(Kricketune, 0),
      .enemyMonElevation = 0,
    }, //Kricketune,
[SPECIES_SHINX] = 
    {  
      //FRONT_PIC(Shinx),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shinx),
      BACK_COORD(0x88,0),
      //PALETTES(Shinx),
      PIC_DATA_ICON_INDEX(Shinx,0),
      //ICON(Shinx, 0),
      .enemyMonElevation = 0,
    }, //Shinx,
[SPECIES_LUXIO] = 
    {  
      //FRONT_PIC(Luxio),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Luxio),
      BACK_COORD(0x88,0),
      //PALETTES(Luxio),
      PIC_DATA_ICON_INDEX(Luxio,0),
      //ICON(Luxio, 0),
      .enemyMonElevation = 0,
    }, //Luxio,
[SPECIES_LUXRAY] = 
    {  
      //FRONT_PIC(Luxray),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Luxray),
      BACK_COORD(0x88,0),
      //PALETTES(Luxray),
      PIC_DATA_ICON_INDEX(Luxray,0),
      //ICON(Luxray, 0),
      .enemyMonElevation = 0,
    }, //Luxray,
[SPECIES_BUDEW] = 
    {  
      //FRONT_PIC(Budew),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Budew),
      BACK_COORD(0x88,0),
      //PALETTES(Budew),
      PIC_DATA_ICON_INDEX(Budew,0),
      //ICON(Budew, 0),
      .enemyMonElevation = 0,
    }, //Budew,
[SPECIES_ROSERADE] = 
    {  
      //FRONT_PIC(Roserade),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Roserade),
      BACK_COORD(0x88,0),
      //PALETTES(Roserade),
      PIC_DATA_ICON_INDEX(Roserade,0),
      //ICON(Roserade, 0),
      .enemyMonElevation = 0,
    }, //Roserade,
[SPECIES_CRANIDOS] = 
    {  
      //FRONT_PIC(Cranidos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cranidos),
      BACK_COORD(0x88,0),
      //PALETTES(Cranidos),
      PIC_DATA_ICON_INDEX(Cranidos,0),
      //ICON(Cranidos, 0),
      .enemyMonElevation = 0,
    }, //Cranidos,
[SPECIES_RAMPARDOS] = 
    {  
      //FRONT_PIC(Rampardos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rampardos),
      BACK_COORD(0x88,0),
      //PALETTES(Rampardos),
      PIC_DATA_ICON_INDEX(Rampardos,0),
      //ICON(Rampardos, 0),
      .enemyMonElevation = 0,
    }, //Rampardos,
[SPECIES_SHIELDON] = 
    {  
      //FRONT_PIC(Shieldon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shieldon),
      BACK_COORD(0x88,0),
      //PALETTES(Shieldon),
      PIC_DATA_ICON_INDEX(Shieldon,0),
      //ICON(Shieldon, 0),
      .enemyMonElevation = 0,
    }, //Shieldon,
[SPECIES_BASTIODON] = 
    {  
      //FRONT_PIC(Bastiodon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bastiodon),
      BACK_COORD(0x88,0),
      //PALETTES(Bastiodon),
      PIC_DATA_ICON_INDEX(Bastiodon,0),
      //ICON(Bastiodon, 0),
      .enemyMonElevation = 0,
    }, //Bastiodon,
[SPECIES_BURMY] = 
    {  
      //FRONT_PIC(Burmy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Burmy),
      BACK_COORD(0x88,0),
      //PALETTES(Burmy),
      PIC_DATA_ICON_INDEX(Burmy,0),
      //ICON(Burmy, 0),
      .enemyMonElevation = 0,
    }, //Burmy,
[SPECIES_WORMADAM] = 
    {  
      //FRONT_PIC(Wormadam),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wormadam),
      BACK_COORD(0x88,0),
      //PALETTES(Wormadam),
      PIC_DATA_ICON_INDEX(Wormadam,0),
      //ICON(Wormadam, 0),
      .enemyMonElevation = 0,
    }, //Wormadam,
[SPECIES_MOTHIM] = 
    {  
      //FRONT_PIC(Mothim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mothim),
      BACK_COORD(0x88,0),
      //PALETTES(Mothim),
      PIC_DATA_ICON_INDEX(Mothim,0),
      //ICON(Mothim, 0),
      .enemyMonElevation = 0,
    }, //Mothim,
[SPECIES_COMBEE] = 
    {  
      //FRONT_PIC(Combee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Combee),
      BACK_COORD(0x88,0),
      //PALETTES(Combee),
      PIC_DATA_ICON_INDEX(Combee,0),
      //ICON(Combee, 0),
      .enemyMonElevation = 0,
    }, //Combee,
[SPECIES_VESPIQUEN] = 
    {  
      //FRONT_PIC(Vespiquen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vespiquen),
      BACK_COORD(0x88,0),
      //PALETTES(Vespiquen),
      PIC_DATA_ICON_INDEX(Vespiquen,0),
      //ICON(Vespiquen, 0),
      .enemyMonElevation = 0,
    }, //Vespiquen,
[SPECIES_PACHIRISU] = 
    {  
      //FRONT_PIC(Pachirisu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pachirisu),
      BACK_COORD(0x88,0),
      //PALETTES(Pachirisu),
      PIC_DATA_ICON_INDEX(Pachirisu,0),
      //ICON(Pachirisu, 0),
      .enemyMonElevation = 0,
    }, //Pachirisu,
[SPECIES_BUIZEL] = 
    {  
      //FRONT_PIC(Buizel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Buizel),
      BACK_COORD(0x88,0),
      //PALETTES(Buizel),
      PIC_DATA_ICON_INDEX(Buizel,0),
      //ICON(Buizel, 0),
      .enemyMonElevation = 0,
    }, //Buizel,
[SPECIES_FLOATZEL] = 
    {  
      //FRONT_PIC(Floatzel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Floatzel),
      BACK_COORD(0x88,0),
      //PALETTES(Floatzel),
      PIC_DATA_ICON_INDEX(Floatzel,0),
      //ICON(Floatzel, 0),
      .enemyMonElevation = 0,
    }, //Floatzel,
[SPECIES_CHERUBI] = 
    {  
      //FRONT_PIC(Cherubi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cherubi),
      BACK_COORD(0x88,0),
      //PALETTES(Cherubi),
      PIC_DATA_ICON_INDEX(Cherubi,0),
      //ICON(Cherubi, 0),
      .enemyMonElevation = 0,
    }, //Cherubi,
[SPECIES_CHERRIM] = 
    {  
      //FRONT_PIC(Cherrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cherrim),
      BACK_COORD(0x88,0),
      //PALETTES(Cherrim),
      PIC_DATA_ICON_INDEX(Cherrim,0),
      //ICON(Cherrim, 0),
      .enemyMonElevation = 0,
    }, //Cherrim,
[SPECIES_SHELLOS] = 
    {  
      //FRONT_PIC(Shellos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shellos),
      BACK_COORD(0x88,0),
      //PALETTES(Shellos),
      PIC_DATA_ICON_INDEX(Shellos,0),
      //ICON(Shellos, 0),
      .enemyMonElevation = 0,
    }, //Shellos,
[SPECIES_GASTRODON] = 
    {  
      //FRONT_PIC(Gastrodon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gastrodon),
      BACK_COORD(0x88,0),
      //PALETTES(Gastrodon),
      PIC_DATA_ICON_INDEX(Gastrodon,0),
      //ICON(Gastrodon, 0),
      .enemyMonElevation = 0,
    }, //Gastrodon,
[SPECIES_AMBIPOM] = 
    {  
      //FRONT_PIC(Ambipom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ambipom),
      BACK_COORD(0x88,0),
      //PALETTES(Ambipom),
      PIC_DATA_ICON_INDEX(Ambipom,0),
      //ICON(Ambipom, 0),
      .enemyMonElevation = 0,
    }, //Ambipom,
[SPECIES_DRIFLOON] = 
    {  
      //FRONT_PIC(Drifloon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drifloon),
      BACK_COORD(0x88,0),
      //PALETTES(Drifloon),
      PIC_DATA_ICON_INDEX(Drifloon,0),
      //ICON(Drifloon, 0),
      .enemyMonElevation = 0,
    }, //Drifloon,
[SPECIES_DRIFBLIM] = 
    {  
      //FRONT_PIC(Drifblim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drifblim),
      BACK_COORD(0x88,0),
      //PALETTES(Drifblim),
      PIC_DATA_ICON_INDEX(Drifblim,0),
      //ICON(Drifblim, 0),
      .enemyMonElevation = 0,
    }, //Drifblim,
[SPECIES_BUNEARY] = 
    {  
      //FRONT_PIC(Buneary),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Buneary),
      BACK_COORD(0x88,0),
      //PALETTES(Buneary),
      PIC_DATA_ICON_INDEX(Buneary,0),
      //ICON(Buneary, 0),
      .enemyMonElevation = 0,
    }, //Buneary,
[SPECIES_LOPUNNY] = 
    {  
      //FRONT_PIC(Lopunny),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lopunny),
      BACK_COORD(0x88,0),
      //PALETTES(Lopunny),
      PIC_DATA_ICON_INDEX(Lopunny,0),
      //ICON(Lopunny, 0),
      .enemyMonElevation = 0,
    }, //Lopunny,
[SPECIES_MISMAGIUS] = 
    {  
      //FRONT_PIC(Mismagius),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mismagius),
      BACK_COORD(0x88,0),
      //PALETTES(Mismagius),
      PIC_DATA_ICON_INDEX(Mismagius,0),
      //ICON(Mismagius, 0),
      .enemyMonElevation = 0,
    }, //Mismagius,
[SPECIES_HONCHKROW] = 
    {  
      //FRONT_PIC(Honchkrow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Honchkrow),
      BACK_COORD(0x88,0),
      //PALETTES(Honchkrow),
      PIC_DATA_ICON_INDEX(Honchkrow,0),
      //ICON(Honchkrow, 0),
      .enemyMonElevation = 0,
    }, //Honchkrow,
[SPECIES_GLAMEOW] = 
    {  
      //FRONT_PIC(Glameow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Glameow),
      BACK_COORD(0x88,0),
      //PALETTES(Glameow),
      PIC_DATA_ICON_INDEX(Glameow,0),
      //ICON(Glameow, 0),
      .enemyMonElevation = 0,
    }, //Glameow,
[SPECIES_PURUGLY] = 
    {  
      //FRONT_PIC(Purugly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Purugly),
      BACK_COORD(0x88,0),
      //PALETTES(Purugly),
      PIC_DATA_ICON_INDEX(Purugly,0),
      //ICON(Purugly, 0),
      .enemyMonElevation = 0,
    }, //Purugly,
[SPECIES_CHINGLING] = 
    {  
      //FRONT_PIC(Chingling),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chingling),
      BACK_COORD(0x88,0),
      //PALETTES(Chingling),
      PIC_DATA_ICON_INDEX(Chingling,0),
      //ICON(Chingling, 0),
      .enemyMonElevation = 0,
    }, //Chingling,
[SPECIES_STUNKY] = 
    {  
      //FRONT_PIC(Stunky),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stunky),
      BACK_COORD(0x88,0),
      //PALETTES(Stunky),
      PIC_DATA_ICON_INDEX(Stunky,0),
      //ICON(Stunky, 0),
      .enemyMonElevation = 0,
    }, //Stunky,
[SPECIES_SKUNTANK] = 
    {  
      //FRONT_PIC(Skuntank),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skuntank),
      BACK_COORD(0x88,0),
      //PALETTES(Skuntank),
      PIC_DATA_ICON_INDEX(Skuntank,0),
      //ICON(Skuntank, 0),
      .enemyMonElevation = 0,
    }, //Skuntank,
[SPECIES_BRONZOR] = 
    {  
      //FRONT_PIC(Bronzor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bronzor),
      BACK_COORD(0x88,0),
      //PALETTES(Bronzor),
      PIC_DATA_ICON_INDEX(Bronzor,0),
      //ICON(Bronzor, 0),
      .enemyMonElevation = 0,
    }, //Bronzor,
[SPECIES_BRONZONG] = 
    {  
      //FRONT_PIC(Bronzong),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bronzong),
      BACK_COORD(0x88,0),
      //PALETTES(Bronzong),
      PIC_DATA_ICON_INDEX(Bronzong,0),
      //ICON(Bronzong, 0),
      .enemyMonElevation = 0,
    }, //Bronzong,
[SPECIES_BONSLY] = 
    {  
      //FRONT_PIC(Bonsly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bonsly),
      BACK_COORD(0x88,0),
      //PALETTES(Bonsly),
      PIC_DATA_ICON_INDEX(Bonsly,0),
      //ICON(Bonsly, 0),
      .enemyMonElevation = 0,
    }, //Bonsly,
[SPECIES_MIME_JR] = 
    {  
      //FRONT_PIC(MimeJr),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MimeJr),
      BACK_COORD(0x88,0),
      //PALETTES(MimeJr),
      PIC_DATA_ICON_INDEX(MimeJr,0),
      //ICON(MimeJr, 0),
      .enemyMonElevation = 0,
    }, //MimeJr,
[SPECIES_HAPPINY] = 
    {  
      //FRONT_PIC(Happiny),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Happiny),
      BACK_COORD(0x88,0),
      //PALETTES(Happiny),
      PIC_DATA_ICON_INDEX(Happiny,0),
      //ICON(Happiny, 0),
      .enemyMonElevation = 0,
    }, //Happiny,
[SPECIES_CHATOT] = 
    {  
      //FRONT_PIC(Chatot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chatot),
      BACK_COORD(0x88,0),
      //PALETTES(Chatot),
      PIC_DATA_ICON_INDEX(Chatot,0),
      //ICON(Chatot, 0),
      .enemyMonElevation = 0,
    }, //Chatot,
[SPECIES_SPIRITOMB] = 
    {  
      //FRONT_PIC(Spiritomb),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spiritomb),
      BACK_COORD(0x88,0),
      //PALETTES(Spiritomb),
      PIC_DATA_ICON_INDEX(Spiritomb,0),
      //ICON(Spiritomb, 0),
      .enemyMonElevation = 0,
    }, //Spiritomb,
[SPECIES_GIBLE] = 
    {  
      //FRONT_PIC(Gible),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gible),
      BACK_COORD(0x88,0),
      //PALETTES(Gible),
      PIC_DATA_ICON_INDEX(Gible,0),
      //ICON(Gible, 0),
      .enemyMonElevation = 0,
    }, //Gible,
[SPECIES_GABITE] = 
    {  
      //FRONT_PIC(Gabite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gabite),
      BACK_COORD(0x88,0),
      //PALETTES(Gabite),
      PIC_DATA_ICON_INDEX(Gabite,0),
      //ICON(Gabite, 0),
      .enemyMonElevation = 0,
    }, //Gabite,
[SPECIES_GARCHOMP] = 
    {  
      //FRONT_PIC(Garchomp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Garchomp),
      BACK_COORD(0x88,0),
      //PALETTES(Garchomp),
      PIC_DATA_ICON_INDEX(Garchomp,0),
      //ICON(Garchomp, 0),
      .enemyMonElevation = 0,
    }, //Garchomp,
[SPECIES_MUNCHLAX] = 
    {  
      //FRONT_PIC(Munchlax),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Munchlax),
      BACK_COORD(0x88,0),
      //PALETTES(Munchlax),
      PIC_DATA_ICON_INDEX(Munchlax,0),
      //ICON(Munchlax, 0),
      .enemyMonElevation = 0,
    }, //Munchlax,
[SPECIES_RIOLU] = 
    {  
      //FRONT_PIC(Riolu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Riolu),
      BACK_COORD(0x88,0),
      //PALETTES(Riolu),
      PIC_DATA_ICON_INDEX(Riolu,0),
      //ICON(Riolu, 0),
      .enemyMonElevation = 0,
    }, //Riolu,
[SPECIES_LUCARIO] = 
    {  
      //FRONT_PIC(Lucario),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lucario),
      BACK_COORD(0x88,0),
      //PALETTES(Lucario),
      PIC_DATA_ICON_INDEX(Lucario,0),
      //ICON(Lucario, 0),
      .enemyMonElevation = 0,
    }, //Lucario,
[SPECIES_HIPPOPOTAS] = 
    {  
      //FRONT_PIC(Hippopotas),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hippopotas),
      BACK_COORD(0x88,0),
      //PALETTES(Hippopotas),
      PIC_DATA_ICON_INDEX(Hippopotas,0),
      //ICON(Hippopotas, 0),
      .enemyMonElevation = 0,
    }, //Hippopotas,
[SPECIES_HIPPOWDON] = 
    {  
      //FRONT_PIC(Hippowdon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hippowdon),
      BACK_COORD(0x88,0),
      //PALETTES(Hippowdon),
      PIC_DATA_ICON_INDEX(Hippowdon,0),
      //ICON(Hippowdon, 0),
      .enemyMonElevation = 0,
    }, //Hippowdon,
[SPECIES_SKORUPI] = 
    {  
      //FRONT_PIC(Skorupi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skorupi),
      BACK_COORD(0x88,0),
      //PALETTES(Skorupi),
      PIC_DATA_ICON_INDEX(Skorupi,0),
      //ICON(Skorupi, 0),
      .enemyMonElevation = 0,
    }, //Skorupi,
[SPECIES_DRAPION] = 
    {  
      //FRONT_PIC(Drapion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drapion),
      BACK_COORD(0x88,0),
      //PALETTES(Drapion),
      PIC_DATA_ICON_INDEX(Drapion,0),
      //ICON(Drapion, 0),
      .enemyMonElevation = 0,
    }, //Drapion,
[SPECIES_CROAGUNK] = 
    {  
      //FRONT_PIC(Croagunk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Croagunk),
      BACK_COORD(0x88,0),
      //PALETTES(Croagunk),
      PIC_DATA_ICON_INDEX(Croagunk,0),
      //ICON(Croagunk, 0),
      .enemyMonElevation = 0,
    }, //Croagunk,
[SPECIES_TOXICROAK] = 
    {  
      //FRONT_PIC(Toxicroak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toxicroak),
      BACK_COORD(0x88,0),
      //PALETTES(Toxicroak),
      PIC_DATA_ICON_INDEX(Toxicroak,0),
      //ICON(Toxicroak, 0),
      .enemyMonElevation = 0,
    }, //Toxicroak,
[SPECIES_CARNIVINE] = 
    {  
      //FRONT_PIC(Carnivine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Carnivine),
      BACK_COORD(0x88,0),
      //PALETTES(Carnivine),
      PIC_DATA_ICON_INDEX(Carnivine,0),
      //ICON(Carnivine, 0),
      .enemyMonElevation = 0,
    }, //Carnivine,
[SPECIES_FINNEON] = 
    {  
      //FRONT_PIC(Finneon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Finneon),
      BACK_COORD(0x88,0),
      //PALETTES(Finneon),
      PIC_DATA_ICON_INDEX(Finneon,0),
      //ICON(Finneon, 0),
      .enemyMonElevation = 0,
    }, //Finneon,
[SPECIES_LUMINEON] = 
    {  
      //FRONT_PIC(Lumineon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lumineon),
      BACK_COORD(0x88,0),
      //PALETTES(Lumineon),
      PIC_DATA_ICON_INDEX(Lumineon,0),
      //ICON(Lumineon, 0),
      .enemyMonElevation = 0,
    }, //Lumineon,
[SPECIES_MANTYKE] = 
    {  
      //FRONT_PIC(Mantyke),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mantyke),
      BACK_COORD(0x88,0),
      //PALETTES(Mantyke),
      PIC_DATA_ICON_INDEX(Mantyke,0),
      //ICON(Mantyke, 0),
      .enemyMonElevation = 0,
    }, //Mantyke,
[SPECIES_SNOVER] = 
    {  
      //FRONT_PIC(Snover),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Snover),
      BACK_COORD(0x88,0),
      //PALETTES(Snover),
      PIC_DATA_ICON_INDEX(Snover,0),
      //ICON(Snover, 0),
      .enemyMonElevation = 0,
    }, //Snover,
[SPECIES_ABOMASNOW] = 
    {  
      //FRONT_PIC(Abomasnow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Abomasnow),
      BACK_COORD(0x88,0),
      //PALETTES(Abomasnow),
      PIC_DATA_ICON_INDEX(Abomasnow,0),
      //ICON(Abomasnow, 0),
      .enemyMonElevation = 0,
    }, //Abomasnow,
[SPECIES_WEAVILE] = 
    {  
      //FRONT_PIC(Weavile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Weavile),
      BACK_COORD(0x88,0),
      //PALETTES(Weavile),
      PIC_DATA_ICON_INDEX(Weavile,0),
      //ICON(Weavile, 0),
      .enemyMonElevation = 0,
    }, //Weavile,
[SPECIES_MAGNEZONE] = 
    {  
      //FRONT_PIC(Magnezone),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magnezone),
      BACK_COORD(0x88,0),
      //PALETTES(Magnezone),
      PIC_DATA_ICON_INDEX(Magnezone,0),
      //ICON(Magnezone, 0),
      .enemyMonElevation = 0,
    }, //Magnezone,
[SPECIES_LICKILICKY] = 
    {  
      //FRONT_PIC(Lickilicky),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lickilicky),
      BACK_COORD(0x88,0),
      //PALETTES(Lickilicky),
      PIC_DATA_ICON_INDEX(Lickilicky,0),
      //ICON(Lickilicky, 0),
      .enemyMonElevation = 0,
    }, //Lickilicky,
[SPECIES_RHYPERIOR] = 
    {  
      //FRONT_PIC(Rhyperior),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rhyperior),
      BACK_COORD(0x88,0),
      //PALETTES(Rhyperior),
      PIC_DATA_ICON_INDEX(Rhyperior,0),
      //ICON(Rhyperior, 0),
      .enemyMonElevation = 0,
    }, //Rhyperior,
[SPECIES_TANGROWTH] = 
    {  
      //FRONT_PIC(Tangrowth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tangrowth),
      BACK_COORD(0x88,0),
      //PALETTES(Tangrowth),
      PIC_DATA_ICON_INDEX(Tangrowth,0),
      //ICON(Tangrowth, 0),
      .enemyMonElevation = 0,
    }, //Tangrowth,
[SPECIES_ELECTIVIRE] = 
    {  
      //FRONT_PIC(Electivire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Electivire),
      BACK_COORD(0x88,0),
      //PALETTES(Electivire),
      PIC_DATA_ICON_INDEX(Electivire,0),
      //ICON(Electivire, 0),
      .enemyMonElevation = 0,
    }, //Electivire,
[SPECIES_MAGMORTAR] = 
    {  
      //FRONT_PIC(Magmortar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magmortar),
      BACK_COORD(0x88,0),
      //PALETTES(Magmortar),
      PIC_DATA_ICON_INDEX(Magmortar,0),
      //ICON(Magmortar, 0),
      .enemyMonElevation = 0,
    }, //Magmortar,
[SPECIES_TOGEKISS] = 
    {  
      //FRONT_PIC(Togekiss),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Togekiss),
      BACK_COORD(0x88,0),
      //PALETTES(Togekiss),
      PIC_DATA_ICON_INDEX(Togekiss,0),
      //ICON(Togekiss, 0),
      .enemyMonElevation = 0,
    }, //Togekiss,
[SPECIES_YANMEGA] = 
    {  
      //FRONT_PIC(Yanmega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Yanmega),
      BACK_COORD(0x88,0),
      //PALETTES(Yanmega),
      PIC_DATA_ICON_INDEX(Yanmega,0),
      //ICON(Yanmega, 0),
      .enemyMonElevation = 0,
    }, //Yanmega,
[SPECIES_LEAFEON] = 
    {  
      //FRONT_PIC(Leafeon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Leafeon),
      BACK_COORD(0x88,0),
      //PALETTES(Leafeon),
      PIC_DATA_ICON_INDEX(Leafeon,0),
      //ICON(Leafeon, 0),
      .enemyMonElevation = 0,
    }, //Leafeon,
[SPECIES_GLACEON] = 
    {  
      //FRONT_PIC(Glaceon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Glaceon),
      BACK_COORD(0x88,0),
      //PALETTES(Glaceon),
      PIC_DATA_ICON_INDEX(Glaceon,0),
      //ICON(Glaceon, 0),
      .enemyMonElevation = 0,
    }, //Glaceon,
[SPECIES_GLISCOR] = 
    {  
      //FRONT_PIC(Gliscor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gliscor),
      BACK_COORD(0x88,0),
      //PALETTES(Gliscor),
      PIC_DATA_ICON_INDEX(Gliscor,0),
      //ICON(Gliscor, 0),
      .enemyMonElevation = 0,
    }, //Gliscor,
[SPECIES_MAMOSWINE] = 
    {  
      //FRONT_PIC(Mamoswine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mamoswine),
      BACK_COORD(0x88,0),
      //PALETTES(Mamoswine),
      PIC_DATA_ICON_INDEX(Mamoswine,0),
      //ICON(Mamoswine, 0),
      .enemyMonElevation = 0,
    }, //Mamoswine,
[SPECIES_PORYGON_Z] = 
    {  
      //FRONT_PIC(PorygonZ),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PorygonZ),
      BACK_COORD(0x88,0),
      //PALETTES(PorygonZ),
      PIC_DATA_ICON_INDEX(PorygonZ,0),
      //ICON(PorygonZ, 0),
      .enemyMonElevation = 0,
    }, //Porygon_Z,
[SPECIES_GALLADE] = 
    {  
      //FRONT_PIC(Gallade),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gallade),
      BACK_COORD(0x88,0),
      //PALETTES(Gallade),
      PIC_DATA_ICON_INDEX(Gallade,0),
      //ICON(Gallade, 0),
      .enemyMonElevation = 0,
    }, //Gallade,
[SPECIES_PROBOPASS] = 
    {  
      //FRONT_PIC(Probopass),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Probopass),
      BACK_COORD(0x88,0),
      //PALETTES(Probopass),
      PIC_DATA_ICON_INDEX(Probopass,0),
      //ICON(Probopass, 0),
      .enemyMonElevation = 0,
    }, //Probopass,
[SPECIES_DUSKNOIR] = 
    {  
      //FRONT_PIC(Dusknoir),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dusknoir),
      BACK_COORD(0x88,0),
      //PALETTES(Dusknoir),
      PIC_DATA_ICON_INDEX(Dusknoir,0),
      //ICON(Dusknoir, 0),
      .enemyMonElevation = 0,
    }, //Dusknoir,
[SPECIES_FROSLASS] = 
    {  
      //FRONT_PIC(Froslass),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Froslass),
      BACK_COORD(0x88,0),
      //PALETTES(Froslass),
      PIC_DATA_ICON_INDEX(Froslass,0),
      //ICON(Froslass, 0),
      .enemyMonElevation = 0,
    }, //Froslass,
[SPECIES_ROTOM] = 
    {  
      //FRONT_PIC(Rotom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rotom),
      BACK_COORD(0x88,0),
      //PALETTES(Rotom),
      PIC_DATA_ICON_INDEX(Rotom,0),
      //ICON(Rotom, 0),
      .enemyMonElevation = 0,
    }, //Rotom,
[SPECIES_UXIE] = 
    {  
      //FRONT_PIC(Uxie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Uxie),
      BACK_COORD(0x88,0),
      //PALETTES(Uxie),
      PIC_DATA_ICON_INDEX(Uxie,0),
      //ICON(Uxie, 0),
      .enemyMonElevation = 0,
    }, //Uxie,
[SPECIES_MESPRIT] = 
    {  
      //FRONT_PIC(Mesprit),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mesprit),
      BACK_COORD(0x88,0),
      //PALETTES(Mesprit),
      PIC_DATA_ICON_INDEX(Mesprit,0),
      //ICON(Mesprit, 0),
      .enemyMonElevation = 0,
    }, //Mesprit,
[SPECIES_AZELF] = 
    {  
      //FRONT_PIC(Azelf),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Azelf),
      BACK_COORD(0x88,0),
      //PALETTES(Azelf),
      PIC_DATA_ICON_INDEX(Azelf,0),
      //ICON(Azelf, 0),
      .enemyMonElevation = 0,
    }, //Azelf,
[SPECIES_DIALGA] = 
    {  
      //FRONT_PIC(Dialga),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dialga),
      BACK_COORD(0x88,0),
      //PALETTES(Dialga),
      PIC_DATA_ICON_INDEX(Dialga,0),
      //ICON(Dialga, 0),
      .enemyMonElevation = 0,
    }, //Dialga,
[SPECIES_PALKIA] = 
    {  
      //FRONT_PIC(Palkia),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Palkia),
      BACK_COORD(0x88,0),
      //PALETTES(Palkia),
      PIC_DATA_ICON_INDEX(Palkia,0),
      //ICON(Palkia, 0),
      .enemyMonElevation = 0,
    }, //Palkia,
[SPECIES_HEATRAN] = 
    {  
      //FRONT_PIC(Heatran),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Heatran),
      BACK_COORD(0x88,0),
      //PALETTES(Heatran),
      PIC_DATA_ICON_INDEX(Heatran,0),
      //ICON(Heatran, 0),
      .enemyMonElevation = 0,
    }, //Heatran,
[SPECIES_REGIGIGAS] = 
    {  
      //FRONT_PIC(Regigigas),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Regigigas),
      BACK_COORD(0x88,0),
      //PALETTES(Regigigas),
      PIC_DATA_ICON_INDEX(Regigigas,0),
      //ICON(Regigigas, 0),
      .enemyMonElevation = 0,
    }, //Regigigas,
[SPECIES_GIRATINA] = 
    {  
      //FRONT_PIC(Giratina),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Giratina),
      BACK_COORD(0x88,0),
      //PALETTES(Giratina),
      PIC_DATA_ICON_INDEX(Giratina,0),
      //ICON(Giratina, 0),
      .enemyMonElevation = 0,
    }, //Giratina,
[SPECIES_CRESSELIA] = 
    {  
      //FRONT_PIC(Cresselia),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cresselia),
      BACK_COORD(0x88,0),
      //PALETTES(Cresselia),
      PIC_DATA_ICON_INDEX(Cresselia,0),
      //ICON(Cresselia, 0),
      .enemyMonElevation = 0,
    }, //Cresselia,
[SPECIES_PHIONE] = 
    {  
      //FRONT_PIC(Phione),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Phione),
      BACK_COORD(0x88,0),
      //PALETTES(Phione),
      PIC_DATA_ICON_INDEX(Phione,0),
      //ICON(Phione, 0),
      .enemyMonElevation = 0,
    }, //Phione,
[SPECIES_MANAPHY] = 
    {  
      //FRONT_PIC(Manaphy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Manaphy),
      BACK_COORD(0x88,0),
      //PALETTES(Manaphy),
      PIC_DATA_ICON_INDEX(Manaphy,0),
      //ICON(Manaphy, 0),
      .enemyMonElevation = 0,
    }, //Manaphy,
[SPECIES_DARKRAI] = 
    {  
      //FRONT_PIC(Darkrai),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Darkrai),
      BACK_COORD(0x88,0),
      //PALETTES(Darkrai),
      PIC_DATA_ICON_INDEX(Darkrai,0),
      //ICON(Darkrai, 0),
      .enemyMonElevation = 0,
    }, //Darkrai,
[SPECIES_SHAYMIN] = 
    {  
      //FRONT_PIC(Shaymin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shaymin),
      BACK_COORD(0x88,0),
      //PALETTES(Shaymin),
      PIC_DATA_ICON_INDEX(Shaymin,0),
      //ICON(Shaymin, 0),
      .enemyMonElevation = 0,
    }, //Shaymin,
[SPECIES_ARCEUS] = 
    {  
      //FRONT_PIC(Arceus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arceus),
      BACK_COORD(0x88,0),
      //PALETTES(Arceus),
      PIC_DATA_ICON_INDEX(Arceus,0),
      //ICON(Arceus, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_VICTINI] = 
    {  
      //FRONT_PIC(Victini),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Victini),
      BACK_COORD(0x88,0),
      //PALETTES(Victini),
      PIC_DATA_ICON_INDEX(Victini,0),
      //ICON(Victini, 0),
      .enemyMonElevation = 0,
    }, //Victini,
[SPECIES_SNIVY] = 
    {  
      //FRONT_PIC(Snivy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Snivy),
      BACK_COORD(0x88,0),
      //PALETTES(Snivy),
      PIC_DATA_ICON_INDEX(Snivy,0),
      //ICON(Snivy, 0),
      .enemyMonElevation = 0,
    }, //Snivy,
[SPECIES_SERVINE] = 
    {  
      //FRONT_PIC(Servine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Servine),
      BACK_COORD(0x88,0),
      //PALETTES(Servine),
      PIC_DATA_ICON_INDEX(Servine,0),
      //ICON(Servine, 0),
      .enemyMonElevation = 0,
    }, //Servine,
[SPECIES_SERPERIOR] = 
    {  
      //FRONT_PIC(Serperior),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Serperior),
      BACK_COORD(0x88,0),
      //PALETTES(Serperior),
      PIC_DATA_ICON_INDEX(Serperior,0),
      //ICON(Serperior, 0),
      .enemyMonElevation = 0,
    }, //Serperior,
[SPECIES_TEPIG] = 
    {  
      //FRONT_PIC(Tepig),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tepig),
      BACK_COORD(0x88,0),
      //PALETTES(Tepig),
      PIC_DATA_ICON_INDEX(Tepig,0),
      //ICON(Tepig, 0),
      .enemyMonElevation = 0,
    }, //Tepig,
[SPECIES_PIGNITE] = 
    {  
      //FRONT_PIC(Pignite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pignite),
      BACK_COORD(0x88,0),
      //PALETTES(Pignite),
      PIC_DATA_ICON_INDEX(Pignite,0),
      //ICON(Pignite, 0),
      .enemyMonElevation = 0,
    }, //Pignite,
[SPECIES_EMBOAR] = 
    {  
      //FRONT_PIC(Emboar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Emboar),
      BACK_COORD(0x88,0),
      //PALETTES(Emboar),
      PIC_DATA_ICON_INDEX(Emboar,0),
      //ICON(Emboar, 0),
      .enemyMonElevation = 0,
    }, //Emboar,
[SPECIES_OSHAWOTT] = 
    {  
      //FRONT_PIC(Oshawott),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Oshawott),
      BACK_COORD(0x88,0),
      //PALETTES(Oshawott),
      PIC_DATA_ICON_INDEX(Oshawott,0),
      //ICON(Oshawott, 0),
      .enemyMonElevation = 0,
    }, //Oshawott,
[SPECIES_DEWOTT] = 
    {  
      //FRONT_PIC(Dewott),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dewott),
      BACK_COORD(0x88,0),
      //PALETTES(Dewott),
      PIC_DATA_ICON_INDEX(Dewott,0),
      //ICON(Dewott, 0),
      .enemyMonElevation = 0,
    }, //Dewott,
[SPECIES_SAMUROTT] = 
    {  
      //FRONT_PIC(Samurott),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Samurott),
      BACK_COORD(0x88,0),
      //PALETTES(Samurott),
      PIC_DATA_ICON_INDEX(Samurott,0),
      //ICON(Samurott, 0),
      .enemyMonElevation = 0,
    }, //Samurott,
[SPECIES_PATRAT] = 
    {  
      //FRONT_PIC(Patrat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Patrat),
      BACK_COORD(0x88,0),
      //PALETTES(Patrat),
      PIC_DATA_ICON_INDEX(Patrat,0),
      //ICON(Patrat, 0),
      .enemyMonElevation = 0,
    }, //Patrat,
[SPECIES_WATCHOG] = 
    {  
      //FRONT_PIC(Watchog),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Watchog),
      BACK_COORD(0x88,0),
      //PALETTES(Watchog),
      PIC_DATA_ICON_INDEX(Watchog,0),
      //ICON(Watchog, 0),
      .enemyMonElevation = 0,
    }, //Watchog,
[SPECIES_LILLIPUP] = 
    {  
      //FRONT_PIC(Lillipup),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lillipup),
      BACK_COORD(0x88,0),
      //PALETTES(Lillipup),
      PIC_DATA_ICON_INDEX(Lillipup,0),
      //ICON(Lillipup, 0),
      .enemyMonElevation = 0,
    }, //Lillipup,
[SPECIES_HERDIER] = 
    {  
      //FRONT_PIC(Herdier),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Herdier),
      BACK_COORD(0x88,0),
      //PALETTES(Herdier),
      PIC_DATA_ICON_INDEX(Herdier,0),
      //ICON(Herdier, 0),
      .enemyMonElevation = 0,
    }, //Herdier,
[SPECIES_STOUTLAND] = 
    {  
      //FRONT_PIC(Stoutland),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stoutland),
      BACK_COORD(0x88,0),
      //PALETTES(Stoutland),
      PIC_DATA_ICON_INDEX(Stoutland,0),
      //ICON(Stoutland, 0),
      .enemyMonElevation = 0,
    }, //Stoutland,
[SPECIES_PURRLOIN] = 
    {  
      //FRONT_PIC(Purrloin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Purrloin),
      BACK_COORD(0x88,0),
      //PALETTES(Purrloin),
      PIC_DATA_ICON_INDEX(Purrloin,0),
      //ICON(Purrloin, 0),
      .enemyMonElevation = 0,
    }, //Purrloin,
[SPECIES_LIEPARD] = 
    {  
      //FRONT_PIC(Liepard),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Liepard),
      BACK_COORD(0x88,0),
      //PALETTES(Liepard),
      PIC_DATA_ICON_INDEX(Liepard,0),
      //ICON(Liepard, 0),
      .enemyMonElevation = 0,
    }, //Liepard,
[SPECIES_PANSAGE] = 
    {  
      //FRONT_PIC(Pansage),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pansage),
      BACK_COORD(0x88,0),
      //PALETTES(Pansage),
      PIC_DATA_ICON_INDEX(Pansage,0),
      //ICON(Pansage, 0),
      .enemyMonElevation = 0,
    }, //Pansage,
[SPECIES_SIMISAGE] = 
    {  
      //FRONT_PIC(Simisage),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Simisage),
      BACK_COORD(0x88,0),
      //PALETTES(Simisage),
      PIC_DATA_ICON_INDEX(Simisage,0),
      //ICON(Simisage, 0),
      .enemyMonElevation = 0,
    }, //Simisage,
[SPECIES_PANSEAR] = 
    {  
      //FRONT_PIC(Pansear),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pansear),
      BACK_COORD(0x88,0),
      //PALETTES(Pansear),
      PIC_DATA_ICON_INDEX(Pansear,0),
      //ICON(Pansear, 0),
      .enemyMonElevation = 0,
    }, //Pansear,
[SPECIES_SIMISEAR] = 
    {  
      //FRONT_PIC(Simisear),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Simisear),
      BACK_COORD(0x88,0),
      //PALETTES(Simisear),
      PIC_DATA_ICON_INDEX(Simisear,0),
      //ICON(Simisear, 0),
      .enemyMonElevation = 0,
    }, //Simisear,
[SPECIES_PANPOUR] = 
    {  
      //FRONT_PIC(Panpour),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Panpour),
      BACK_COORD(0x88,0),
      //PALETTES(Panpour),
      PIC_DATA_ICON_INDEX(Panpour,0),
      //ICON(Panpour, 0),
      .enemyMonElevation = 0,
    }, //Panpour,
[SPECIES_SIMIPOUR] = 
    {  
      //FRONT_PIC(Simipour),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Simipour),
      BACK_COORD(0x88,0),
      //PALETTES(Simipour),
      PIC_DATA_ICON_INDEX(Simipour,0),
      //ICON(Simipour, 0),
      .enemyMonElevation = 0,
    }, //Simipour,
[SPECIES_MUNNA] = 
    {  
      //FRONT_PIC(Munna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Munna),
      BACK_COORD(0x88,0),
      //PALETTES(Munna),
      PIC_DATA_ICON_INDEX(Munna,0),
      //ICON(Munna, 0),
      .enemyMonElevation = 0,
    }, //Munna,
[SPECIES_MUSHARNA] = 
    {  
      //FRONT_PIC(Musharna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Musharna),
      BACK_COORD(0x88,0),
      //PALETTES(Musharna),
      PIC_DATA_ICON_INDEX(Musharna,0),
      //ICON(Musharna, 0),
      .enemyMonElevation = 0,
    }, //Musharna,
[SPECIES_PIDOVE] = 
    {  
      //FRONT_PIC(Pidove),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pidove),
      BACK_COORD(0x88,0),
      //PALETTES(Pidove),
      PIC_DATA_ICON_INDEX(Pidove,0),
      //ICON(Pidove, 0),
      .enemyMonElevation = 0,
    }, //Pidove,
[SPECIES_TRANQUILL] = 
    {  
      //FRONT_PIC(Tranquill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tranquill),
      BACK_COORD(0x88,0),
      //PALETTES(Tranquill),
      PIC_DATA_ICON_INDEX(Tranquill,0),
      //ICON(Tranquill, 0),
      .enemyMonElevation = 0,
    }, //Tranquill,
[SPECIES_UNFEZANT_MALE] = 
    {  
      //FRONT_PIC(UnfezantMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnfezantMale),
      BACK_COORD(0x88,0),
      //PALETTES(UnfezantMale),
      PIC_DATA_ICON_INDEX(UnfezantMale,0),
      //ICON(UnfezantMale, 0),
      .enemyMonElevation = 0,
    }, //Unfezant,
[SPECIES_BLITZLE] = 
    {  
      //FRONT_PIC(Blitzle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blitzle),
      BACK_COORD(0x88,0),
      //PALETTES(Blitzle),
      PIC_DATA_ICON_INDEX(Blitzle,0),
      //ICON(Blitzle, 0),
      .enemyMonElevation = 0,
    }, //Blitzle,
[SPECIES_ZEBSTRIKA] = 
    {  
      //FRONT_PIC(Zebstrika),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zebstrika),
      BACK_COORD(0x88,0),
      //PALETTES(Zebstrika),
      PIC_DATA_ICON_INDEX(Zebstrika,0),
      //ICON(Zebstrika, 0),
      .enemyMonElevation = 0,
    }, //Zebstrika,
[SPECIES_ROGGENROLA] = 
    {  
      //FRONT_PIC(Roggenrola),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Roggenrola),
      BACK_COORD(0x88,0),
      //PALETTES(Roggenrola),
      PIC_DATA_ICON_INDEX(Roggenrola,0),
      //ICON(Roggenrola, 0),
      .enemyMonElevation = 0,
    }, //Roggenrola,
[SPECIES_BOLDORE] = 
    {  
      //FRONT_PIC(Boldore),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Boldore),
      BACK_COORD(0x88,0),
      //PALETTES(Boldore),
      PIC_DATA_ICON_INDEX(Boldore,0),
      //ICON(Boldore, 0),
      .enemyMonElevation = 0,
    }, //Boldore,
[SPECIES_GIGALITH] = 
    {  
      //FRONT_PIC(Gigalith),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gigalith),
      BACK_COORD(0x88,0),
      //PALETTES(Gigalith),
      PIC_DATA_ICON_INDEX(Gigalith,0),
      //ICON(Gigalith, 0),
      .enemyMonElevation = 0,
    }, //Gigalith,
[SPECIES_WOOBAT] = 
    {  
      //FRONT_PIC(Woobat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Woobat),
      BACK_COORD(0x88,0),
      //PALETTES(Woobat),
      PIC_DATA_ICON_INDEX(Woobat,0),
      //ICON(Woobat, 0),
      .enemyMonElevation = 0,
    }, //Woobat,
[SPECIES_SWOOBAT] = 
    {  
      //FRONT_PIC(Swoobat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swoobat),
      BACK_COORD(0x88,0),
      //PALETTES(Swoobat),
      PIC_DATA_ICON_INDEX(Swoobat,0),
      //ICON(Swoobat, 0),
      .enemyMonElevation = 0,
    }, //Swoobat,
[SPECIES_DRILBUR] = 
    {  
      //FRONT_PIC(Drilbur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drilbur),
      BACK_COORD(0x88,0),
      //PALETTES(Drilbur),
      PIC_DATA_ICON_INDEX(Drilbur,0),
      //ICON(Drilbur, 0),
      .enemyMonElevation = 0,
    }, //Drilbur,
[SPECIES_EXCADRILL] = 
    {  
      //FRONT_PIC(Excadrill),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Excadrill),
      BACK_COORD(0x88,0),
      //PALETTES(Excadrill),
      PIC_DATA_ICON_INDEX(Excadrill,0),
      //ICON(Excadrill, 0),
      .enemyMonElevation = 0,
    }, //Excadrill,
[SPECIES_AUDINO] = 
    {  
      //FRONT_PIC(Audino),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Audino),
      BACK_COORD(0x88,0),
      //PALETTES(Audino),
      PIC_DATA_ICON_INDEX(Audino,0),
      //ICON(Audino, 0),
      .enemyMonElevation = 0,
    }, //Audino,
[SPECIES_TIMBURR] = 
    {  
      //FRONT_PIC(Timburr),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Timburr),
      BACK_COORD(0x88,0),
      //PALETTES(Timburr),
      PIC_DATA_ICON_INDEX(Timburr,0),
      //ICON(Timburr, 0),
      .enemyMonElevation = 0,
    }, //Timburr,
[SPECIES_GURDURR] = 
    {  
      //FRONT_PIC(Gurdurr),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gurdurr),
      BACK_COORD(0x88,0),
      //PALETTES(Gurdurr),
      PIC_DATA_ICON_INDEX(Gurdurr,0),
      //ICON(Gurdurr, 0),
      .enemyMonElevation = 0,
    }, //Gurdurr,
[SPECIES_CONKELDURR] = 
    {  
      //FRONT_PIC(Conkeldurr),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Conkeldurr),
      BACK_COORD(0x88,0),
      //PALETTES(Conkeldurr),
      PIC_DATA_ICON_INDEX(Conkeldurr,0),
      //ICON(Conkeldurr, 0),
      .enemyMonElevation = 0,
    }, //Conkeldurr,
[SPECIES_TYMPOLE] = 
    {  
      //FRONT_PIC(Tympole),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tympole),
      BACK_COORD(0x88,0),
      //PALETTES(Tympole),
      PIC_DATA_ICON_INDEX(Tympole,0),
      //ICON(Tympole, 0),
      .enemyMonElevation = 0,
    }, //Tympole,
[SPECIES_PALPITOAD] = 
    {  
      //FRONT_PIC(Palpitoad),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Palpitoad),
      BACK_COORD(0x88,0),
      //PALETTES(Palpitoad),
      PIC_DATA_ICON_INDEX(Palpitoad,0),
      //ICON(Palpitoad, 0),
      .enemyMonElevation = 0,
    }, //Palpitoad,
[SPECIES_SEISMITOAD] = 
    {  
      //FRONT_PIC(Seismitoad),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Seismitoad),
      BACK_COORD(0x88,0),
      //PALETTES(Seismitoad),
      PIC_DATA_ICON_INDEX(Seismitoad,0),
      //ICON(Seismitoad, 0),
      .enemyMonElevation = 0,
    }, //Seismitoad,
[SPECIES_THROH] = 
    {  
      //FRONT_PIC(Throh),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Throh),
      BACK_COORD(0x88,0),
      //PALETTES(Throh),
      PIC_DATA_ICON_INDEX(Throh,0),
      //ICON(Throh, 0),
      .enemyMonElevation = 0,
    }, //Throh,
[SPECIES_SAWK] = 
    {  
      //FRONT_PIC(Sawk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sawk),
      BACK_COORD(0x88,0),
      //PALETTES(Sawk),
      PIC_DATA_ICON_INDEX(Sawk,0),
      //ICON(Sawk, 0),
      .enemyMonElevation = 0,
    }, //Sawk,
[SPECIES_SEWADDLE] = 
    {  
      //FRONT_PIC(Sewaddle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sewaddle),
      BACK_COORD(0x88,0),
      //PALETTES(Sewaddle),
      PIC_DATA_ICON_INDEX(Sewaddle,0),
      //ICON(Sewaddle, 0),
      .enemyMonElevation = 0,
    }, //Sewaddle,
[SPECIES_SWADLOON] = 
    {  
      //FRONT_PIC(Swadloon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swadloon),
      BACK_COORD(0x88,0),
      //PALETTES(Swadloon),
      PIC_DATA_ICON_INDEX(Swadloon,0),
      //ICON(Swadloon, 0),
      .enemyMonElevation = 0,
    }, //Swadloon,
[SPECIES_LEAVANNY] = 
    {  
      //FRONT_PIC(Leavanny),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Leavanny),
      BACK_COORD(0x88,0),
      //PALETTES(Leavanny),
      PIC_DATA_ICON_INDEX(Leavanny,0),
      //ICON(Leavanny, 0),
      .enemyMonElevation = 0,
    }, //Leavanny,
[SPECIES_VENIPEDE] = 
    {  
      //FRONT_PIC(Venipede),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Venipede),
      BACK_COORD(0x88,0),
      //PALETTES(Venipede),
      PIC_DATA_ICON_INDEX(Venipede,0),
      //ICON(Venipede, 0),
      .enemyMonElevation = 0,
    }, //Venipede,
[SPECIES_WHIRLIPEDE] = 
    {  
      //FRONT_PIC(Whirlipede),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Whirlipede),
      BACK_COORD(0x88,0),
      //PALETTES(Whirlipede),
      PIC_DATA_ICON_INDEX(Whirlipede,0),
      //ICON(Whirlipede, 0),
      .enemyMonElevation = 0,
    }, //Whirlipede,
[SPECIES_SCOLIPEDE] = 
    {  
      //FRONT_PIC(Scolipede),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scolipede),
      BACK_COORD(0x88,0),
      //PALETTES(Scolipede),
      PIC_DATA_ICON_INDEX(Scolipede,0),
      //ICON(Scolipede, 0),
      .enemyMonElevation = 0,
    }, //Scolipede,
[SPECIES_COTTONEE] = 
    {  
      //FRONT_PIC(Cottonee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cottonee),
      BACK_COORD(0x88,0),
      //PALETTES(Cottonee),
      PIC_DATA_ICON_INDEX(Cottonee,0),
      //ICON(Cottonee, 0),
      .enemyMonElevation = 0,
    }, //Cottonee,
[SPECIES_WHIMSICOTT] = 
    {  
      //FRONT_PIC(Whimsicott),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Whimsicott),
      BACK_COORD(0x88,0),
      //PALETTES(Whimsicott),
      PIC_DATA_ICON_INDEX(Whimsicott,0),
      //ICON(Whimsicott, 0),
      .enemyMonElevation = 0,
    }, //Whimsicott,
[SPECIES_PETILIL] = 
    {  
      //FRONT_PIC(Petilil),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Petilil),
      BACK_COORD(0x88,0),
      //PALETTES(Petilil),
      PIC_DATA_ICON_INDEX(Petilil,0),
      //ICON(Petilil, 0),
      .enemyMonElevation = 0,
    }, //Petilil,
[SPECIES_LILLIGANT] = 
    {  
      //FRONT_PIC(Lilligant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lilligant),
      BACK_COORD(0x88,0),
      //PALETTES(Lilligant),
      PIC_DATA_ICON_INDEX(Lilligant,0),
      //ICON(Lilligant, 0),
      .enemyMonElevation = 0,
    }, //Lilligant,
[SPECIES_BASCULIN] = 
    {  
      //FRONT_PIC(Basculin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculin),
      BACK_COORD(0x88,0),
      //PALETTES(Basculin),
      PIC_DATA_ICON_INDEX(Basculin,0),
      //ICON(Basculin, 0),
      .enemyMonElevation = 0,
    }, //Basculin,
[SPECIES_SANDILE] = 
    {  
      //FRONT_PIC(Sandile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sandile),
      BACK_COORD(0x88,0),
      //PALETTES(Sandile),
      PIC_DATA_ICON_INDEX(Sandile,0),
      //ICON(Sandile, 0),
      .enemyMonElevation = 0,
    }, //Sandile,
[SPECIES_KROKOROK] = 
    {  
      //FRONT_PIC(Krokorok),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Krokorok),
      BACK_COORD(0x88,0),
      //PALETTES(Krokorok),
      PIC_DATA_ICON_INDEX(Krokorok,0),
      //ICON(Krokorok, 0),
      .enemyMonElevation = 0,
    }, //Krokorok,
[SPECIES_KROOKODILE] = 
    {  
      //FRONT_PIC(Krookodile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Krookodile),
      BACK_COORD(0x88,0),
      //PALETTES(Krookodile),
      PIC_DATA_ICON_INDEX(Krookodile,0),
      //ICON(Krookodile, 0),
      .enemyMonElevation = 0,
    }, //Krookodile,
[SPECIES_DARUMAKA] = 
    {  
      //FRONT_PIC(Darumaka),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Darumaka),
      BACK_COORD(0x88,0),
      //PALETTES(Darumaka),
      PIC_DATA_ICON_INDEX(Darumaka,0),
      //ICON(Darumaka, 0),
      .enemyMonElevation = 0,
    }, //Darumaka,
[SPECIES_DARMANITAN] = 
    {  
      //FRONT_PIC(Darmanitan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Darmanitan),
      BACK_COORD(0x88,0),
      //PALETTES(Darmanitan),
      PIC_DATA_ICON_INDEX(Darmanitan,0),
      //ICON(Darmanitan, 0),
      .enemyMonElevation = 0,
    }, //Darmanitan,
[SPECIES_MARACTUS] = 
    {  
      //FRONT_PIC(Maractus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Maractus),
      BACK_COORD(0x88,0),
      //PALETTES(Maractus),
      PIC_DATA_ICON_INDEX(Maractus,0),
      //ICON(Maractus, 0),
      .enemyMonElevation = 0,
    }, //Maractus,
[SPECIES_DWEBBLE] = 
    {  
      //FRONT_PIC(Dwebble),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dwebble),
      BACK_COORD(0x88,0),
      //PALETTES(Dwebble),
      PIC_DATA_ICON_INDEX(Dwebble,0),
      //ICON(Dwebble, 0),
      .enemyMonElevation = 0,
    }, //Dwebble,
[SPECIES_CRUSTLE] = 
    {  
      //FRONT_PIC(Crustle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Crustle),
      BACK_COORD(0x88,0),
      //PALETTES(Crustle),
      PIC_DATA_ICON_INDEX(Crustle,0),
      //ICON(Crustle, 0),
      .enemyMonElevation = 0,
    }, //Crustle,
[SPECIES_SCRAGGY] = 
    {  
      //FRONT_PIC(Scraggy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scraggy),
      BACK_COORD(0x88,0),
      //PALETTES(Scraggy),
      PIC_DATA_ICON_INDEX(Scraggy,0),
      //ICON(Scraggy, 0),
      .enemyMonElevation = 0,
    }, //Scraggy,
[SPECIES_SCRAFTY] = 
    {  
      //FRONT_PIC(Scrafty),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scrafty),
      BACK_COORD(0x88,0),
      //PALETTES(Scrafty),
      PIC_DATA_ICON_INDEX(Scrafty,0),
      //ICON(Scrafty, 0),
      .enemyMonElevation = 0,
    }, //Scrafty,
[SPECIES_SIGILYPH] = 
    {  
      //FRONT_PIC(Sigilyph),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sigilyph),
      BACK_COORD(0x88,0),
      //PALETTES(Sigilyph),
      PIC_DATA_ICON_INDEX(Sigilyph,0),
      //ICON(Sigilyph, 0),
      .enemyMonElevation = 0,
    }, //Sigilyph,
[SPECIES_YAMASK] = 
    {  
      //FRONT_PIC(Yamask),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Yamask),
      BACK_COORD(0x88,0),
      //PALETTES(Yamask),
      PIC_DATA_ICON_INDEX(Yamask,0),
      //ICON(Yamask, 0),
      .enemyMonElevation = 0,
    }, //Yamask,
[SPECIES_COFAGRIGUS] = 
    {  
      //FRONT_PIC(Cofagrigus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cofagrigus),
      BACK_COORD(0x88,0),
      //PALETTES(Cofagrigus),
      PIC_DATA_ICON_INDEX(Cofagrigus,0),
      //ICON(Cofagrigus, 0),
      .enemyMonElevation = 0,
    }, //Cofagrigus,
[SPECIES_TIRTOUGA] = 
    {  
      //FRONT_PIC(Tirtouga),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tirtouga),
      BACK_COORD(0x88,0),
      //PALETTES(Tirtouga),
      PIC_DATA_ICON_INDEX(Tirtouga,0),
      //ICON(Tirtouga, 0),
      .enemyMonElevation = 0,
    }, //Tirtouga,
[SPECIES_CARRACOSTA] = 
    {  
      //FRONT_PIC(Carracosta),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Carracosta),
      BACK_COORD(0x88,0),
      //PALETTES(Carracosta),
      PIC_DATA_ICON_INDEX(Carracosta,0),
      //ICON(Carracosta, 0),
      .enemyMonElevation = 0,
    }, //Carracosta,
[SPECIES_ARCHEN] = 
    {  
      //FRONT_PIC(Archen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Archen),
      BACK_COORD(0x88,0),
      //PALETTES(Archen),
      PIC_DATA_ICON_INDEX(Archen,0),
      //ICON(Archen, 0),
      .enemyMonElevation = 0,
    }, //Archen,
[SPECIES_ARCHEOPS] = 
    {  
      //FRONT_PIC(Archeops),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Archeops),
      BACK_COORD(0x88,0),
      //PALETTES(Archeops),
      PIC_DATA_ICON_INDEX(Archeops,0),
      //ICON(Archeops, 0),
      .enemyMonElevation = 0,
    }, //Archeops,
[SPECIES_TRUBBISH] = 
    {  
      //FRONT_PIC(Trubbish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Trubbish),
      BACK_COORD(0x88,0),
      //PALETTES(Trubbish),
      PIC_DATA_ICON_INDEX(Trubbish,0),
      //ICON(Trubbish, 0),
      .enemyMonElevation = 0,
    }, //Trubbish,
[SPECIES_GARBODOR] = 
    {  
      //FRONT_PIC(Garbodor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Garbodor),
      BACK_COORD(0x88,0),
      //PALETTES(Garbodor),
      PIC_DATA_ICON_INDEX(Garbodor,0),
      //ICON(Garbodor, 0),
      .enemyMonElevation = 0,
    }, //Garbodor,
[SPECIES_ZORUA] = 
    {  
      //FRONT_PIC(Zorua),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zorua),
      BACK_COORD(0x88,0),
      //PALETTES(Zorua),
      PIC_DATA_ICON_INDEX(Zorua,0),
      //ICON(Zorua, 0),
      .enemyMonElevation = 0,
    }, //Zorua,
[SPECIES_ZOROARK] = 
    {  
      //FRONT_PIC(Zoroark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zoroark),
      BACK_COORD(0x88,0),
      //PALETTES(Zoroark),
      PIC_DATA_ICON_INDEX(Zoroark,0),
      //ICON(Zoroark, 0),
      .enemyMonElevation = 0,
    }, //Zoroark,
[SPECIES_MINCCINO] = 
    {  
      //FRONT_PIC(Minccino),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Minccino),
      BACK_COORD(0x88,0),
      //PALETTES(Minccino),
      PIC_DATA_ICON_INDEX(Minccino,0),
      //ICON(Minccino, 0),
      .enemyMonElevation = 0,
    }, //Minccino,
[SPECIES_CINCCINO] = 
    {  
      //FRONT_PIC(Cinccino),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cinccino),
      BACK_COORD(0x88,0),
      //PALETTES(Cinccino),
      PIC_DATA_ICON_INDEX(Cinccino,0),
      //ICON(Cinccino, 0),
      .enemyMonElevation = 0,
    }, //Cinccino,
[SPECIES_GOTHITA] = 
    {  
      //FRONT_PIC(Gothita),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gothita),
      BACK_COORD(0x88,0),
      //PALETTES(Gothita),
      PIC_DATA_ICON_INDEX(Gothita,0),
      //ICON(Gothita, 0),
      .enemyMonElevation = 0,
    }, //Gothita,
[SPECIES_GOTHORITA] = 
    {  
      //FRONT_PIC(Gothorita),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gothorita),
      BACK_COORD(0x88,0),
      //PALETTES(Gothorita),
      PIC_DATA_ICON_INDEX(Gothorita,0),
      //ICON(Gothorita, 0),
      .enemyMonElevation = 0,
    }, //Gothorita,
[SPECIES_GOTHITELLE] = 
    {  
      //FRONT_PIC(Gothitelle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gothitelle),
      BACK_COORD(0x88,0),
      //PALETTES(Gothitelle),
      PIC_DATA_ICON_INDEX(Gothitelle,0),
      //ICON(Gothitelle, 0),
      .enemyMonElevation = 0,
    }, //Gothitelle,
[SPECIES_SOLOSIS] = 
    {  
      //FRONT_PIC(Solosis),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Solosis),
      BACK_COORD(0x88,0),
      //PALETTES(Solosis),
      PIC_DATA_ICON_INDEX(Solosis,0),
      //ICON(Solosis, 0),
      .enemyMonElevation = 0,
    }, //Solosis,
[SPECIES_DUOSION] = 
    {  
      //FRONT_PIC(Duosion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Duosion),
      BACK_COORD(0x88,0),
      //PALETTES(Duosion),
      PIC_DATA_ICON_INDEX(Duosion,0),
      //ICON(Duosion, 0),
      .enemyMonElevation = 0,
    }, //Duosion,
[SPECIES_REUNICLUS] = 
    {  
      //FRONT_PIC(Reuniclus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Reuniclus),
      BACK_COORD(0x88,0),
      //PALETTES(Reuniclus),
      PIC_DATA_ICON_INDEX(Reuniclus,0),
      //ICON(Reuniclus, 0),
      .enemyMonElevation = 0,
    }, //Reuniclus,
[SPECIES_DUCKLETT] = 
    {  
      //FRONT_PIC(Ducklett),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ducklett),
      BACK_COORD(0x88,0),
      //PALETTES(Ducklett),
      PIC_DATA_ICON_INDEX(Ducklett,0),
      //ICON(Ducklett, 0),
      .enemyMonElevation = 0,
    }, //Ducklett,
[SPECIES_SWANNA] = 
    {  
      //FRONT_PIC(Swanna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swanna),
      BACK_COORD(0x88,0),
      //PALETTES(Swanna),
      PIC_DATA_ICON_INDEX(Swanna,0),
      //ICON(Swanna, 0),
      .enemyMonElevation = 0,
    }, //Swanna,
[SPECIES_VANILLITE] = 
    {  
      //FRONT_PIC(Vanillite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vanillite),
      BACK_COORD(0x88,0),
      //PALETTES(Vanillite),
      PIC_DATA_ICON_INDEX(Vanillite,0),
      //ICON(Vanillite, 0),
      .enemyMonElevation = 0,
    }, //Vanillite,
[SPECIES_VANILLISH] = 
    {  
      //FRONT_PIC(Vanillish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vanillish),
      BACK_COORD(0x88,0),
      //PALETTES(Vanillish),
      PIC_DATA_ICON_INDEX(Vanillish,0),
      //ICON(Vanillish, 0),
      .enemyMonElevation = 0,
    }, //Vanillish,
[SPECIES_VANILLUXE] = 
    {  
      //FRONT_PIC(Vanilluxe),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vanilluxe),
      BACK_COORD(0x88,0),
      //PALETTES(Vanilluxe),
      PIC_DATA_ICON_INDEX(Vanilluxe,0),
      //ICON(Vanilluxe, 0),
      .enemyMonElevation = 0,
    }, //Vanilluxe,
[SPECIES_DEERLING] = 
    {  
      //FRONT_PIC(Deerling),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Deerling),
      BACK_COORD(0x88,0),
      //PALETTES(Deerling),
      PIC_DATA_ICON_INDEX(Deerling,0),
      //ICON(Deerling, 0),
      .enemyMonElevation = 0,
    }, //Deerling,
[SPECIES_SAWSBUCK] = 
    {  
      //FRONT_PIC(Sawsbuck),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sawsbuck),
      BACK_COORD(0x88,0),
      //PALETTES(Sawsbuck),
      PIC_DATA_ICON_INDEX(Sawsbuck,0),
      //ICON(Sawsbuck, 0),
      .enemyMonElevation = 0,
    }, //Sawsbuck,
[SPECIES_EMOLGA] = 
    {  
      //FRONT_PIC(Emolga),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Emolga),
      BACK_COORD(0x88,0),
      //PALETTES(Emolga),
      PIC_DATA_ICON_INDEX(Emolga,0),
      //ICON(Emolga, 0),
      .enemyMonElevation = 0,
    }, //Emolga,
[SPECIES_KARRABLAST] = 
    {  
      //FRONT_PIC(Karrablast),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Karrablast),
      BACK_COORD(0x88,0),
      //PALETTES(Karrablast),
      PIC_DATA_ICON_INDEX(Karrablast,0),
      //ICON(Karrablast, 0),
      .enemyMonElevation = 0,
    }, //Karrablast,
[SPECIES_ESCAVALIER] = 
    {  
      //FRONT_PIC(Escavalier),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Escavalier),
      BACK_COORD(0x88,0),
      //PALETTES(Escavalier),
      PIC_DATA_ICON_INDEX(Escavalier,0),
      //ICON(Escavalier, 0),
      .enemyMonElevation = 0,
    }, //Escavalier,
[SPECIES_FOONGUS] = 
    {  
      //FRONT_PIC(Foongus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Foongus),
      BACK_COORD(0x88,0),
      //PALETTES(Foongus),
      PIC_DATA_ICON_INDEX(Foongus,0),
      //ICON(Foongus, 0),
      .enemyMonElevation = 0,
    }, //Foongus,
[SPECIES_AMOONGUSS] = 
    {  
      //FRONT_PIC(Amoonguss),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Amoonguss),
      BACK_COORD(0x88,0),
      //PALETTES(Amoonguss),
      PIC_DATA_ICON_INDEX(Amoonguss,0),
      //ICON(Amoonguss, 0),
      .enemyMonElevation = 0,
    }, //Amoonguss,
[SPECIES_FRILLISH_MALE] = 
    {  
      //FRONT_PIC(FrillishMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FrillishMale),
      BACK_COORD(0x88,0),
      //PALETTES(FrillishMale),
      PIC_DATA_ICON_INDEX(FrillishMale,0),
      //ICON(FrillishMale, 0),
      .enemyMonElevation = 0,
    }, //Frillish,
[SPECIES_JELLICENT_MALE] = 
    {  
      //FRONT_PIC(JellicentMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(JellicentMale),
      BACK_COORD(0x88,0),
      //PALETTES(JellicentMale),
      PIC_DATA_ICON_INDEX(JellicentMale,0),
      //ICON(JellicentMale, 0),
      .enemyMonElevation = 0,
    }, //Jellicent,
[SPECIES_ALOMOMOLA] = 
    {  
      //FRONT_PIC(Alomomola),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Alomomola),
      BACK_COORD(0x88,0),
      //PALETTES(Alomomola),
      PIC_DATA_ICON_INDEX(Alomomola,0),
      //ICON(Alomomola, 0),
      .enemyMonElevation = 0,
    }, //Alomomola,
[SPECIES_JOLTIK] = 
    {  
      //FRONT_PIC(Joltik),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Joltik),
      BACK_COORD(0x88,0),
      //PALETTES(Joltik),
      PIC_DATA_ICON_INDEX(Joltik,0),
      //ICON(Joltik, 0),
      .enemyMonElevation = 0,
    }, //Joltik,
[SPECIES_GALVANTULA] = 
    {  
      //FRONT_PIC(Galvantula),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Galvantula),
      BACK_COORD(0x88,0),
      //PALETTES(Galvantula),
      PIC_DATA_ICON_INDEX(Galvantula,0),
      //ICON(Galvantula, 0),
      .enemyMonElevation = 0,
    }, //Galvantula,
[SPECIES_FERROSEED] = 
    {  
      //FRONT_PIC(Ferroseed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ferroseed),
      BACK_COORD(0x88,0),
      //PALETTES(Ferroseed),
      PIC_DATA_ICON_INDEX(Ferroseed,0),
      //ICON(Ferroseed, 0),
      .enemyMonElevation = 0,
    }, //Ferroseed,
[SPECIES_FERROTHORN] = 
    {  
      //FRONT_PIC(Ferrothorn),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ferrothorn),
      BACK_COORD(0x88,0),
      //PALETTES(Ferrothorn),
      PIC_DATA_ICON_INDEX(Ferrothorn,0),
      //ICON(Ferrothorn, 0),
      .enemyMonElevation = 0,
    }, //Ferrothorn,
[SPECIES_KLINK] = 
    {  
      //FRONT_PIC(Klink),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Klink),
      BACK_COORD(0x88,0),
      //PALETTES(Klink),
      PIC_DATA_ICON_INDEX(Klink,0),
      //ICON(Klink, 0),
      .enemyMonElevation = 0,
    }, //Klink,
[SPECIES_KLANG] = 
    {  
      //FRONT_PIC(Klang),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Klang),
      BACK_COORD(0x88,0),
      //PALETTES(Klang),
      PIC_DATA_ICON_INDEX(Klang,0),
      //ICON(Klang, 0),
      .enemyMonElevation = 0,
    }, //Klang,
[SPECIES_KLINKLANG] = 
    {  
      //FRONT_PIC(Klinklang),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Klinklang),
      BACK_COORD(0x88,0),
      //PALETTES(Klinklang),
      PIC_DATA_ICON_INDEX(Klinklang,0),
      //ICON(Klinklang, 0),
      .enemyMonElevation = 0,
    }, //Klinklang,
[SPECIES_TYNAMO] = 
    {  
      //FRONT_PIC(Tynamo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tynamo),
      BACK_COORD(0x88,0),
      //PALETTES(Tynamo),
      PIC_DATA_ICON_INDEX(Tynamo,0),
      //ICON(Tynamo, 0),
      .enemyMonElevation = 0,
    }, //Tynamo,
[SPECIES_EELEKTRIK] = 
    {  
      //FRONT_PIC(Eelektrik),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Eelektrik),
      BACK_COORD(0x88,0),
      //PALETTES(Eelektrik),
      PIC_DATA_ICON_INDEX(Eelektrik,0),
      //ICON(Eelektrik, 0),
      .enemyMonElevation = 0,
    }, //Eelektrik,
[SPECIES_EELEKTROSS] = 
    {  
      //FRONT_PIC(Eelektross),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Eelektross),
      BACK_COORD(0x88,0),
      //PALETTES(Eelektross),
      PIC_DATA_ICON_INDEX(Eelektross,0),
      //ICON(Eelektross, 0),
      .enemyMonElevation = 0,
    }, //Eelektross,
[SPECIES_ELGYEM] = 
    {  
      //FRONT_PIC(Elgyem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Elgyem),
      BACK_COORD(0x88,0),
      //PALETTES(Elgyem),
      PIC_DATA_ICON_INDEX(Elgyem,0),
      //ICON(Elgyem, 0),
      .enemyMonElevation = 0,
    }, //Elgyem,
[SPECIES_BEHEEYEM] = 
    {  
      //FRONT_PIC(Beheeyem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Beheeyem),
      BACK_COORD(0x88,0),
      //PALETTES(Beheeyem),
      PIC_DATA_ICON_INDEX(Beheeyem,0),
      //ICON(Beheeyem, 0),
      .enemyMonElevation = 0,
    }, //Beheeyem,
[SPECIES_LITWICK] = 
    {  
      //FRONT_PIC(Litwick),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Litwick),
      BACK_COORD(0x88,0),
      //PALETTES(Litwick),
      PIC_DATA_ICON_INDEX(Litwick,0),
      //ICON(Litwick, 0),
      .enemyMonElevation = 0,
    }, //Litwick,
[SPECIES_LAMPENT] = 
    {  
      //FRONT_PIC(Lampent),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lampent),
      BACK_COORD(0x88,0),
      //PALETTES(Lampent),
      PIC_DATA_ICON_INDEX(Lampent,0),
      //ICON(Lampent, 0),
      .enemyMonElevation = 0,
    }, //Lampent,
[SPECIES_CHANDELURE] = 
    {  
      //FRONT_PIC(Chandelure),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chandelure),
      BACK_COORD(0x88,0),
      //PALETTES(Chandelure),
      PIC_DATA_ICON_INDEX(Chandelure,0),
      //ICON(Chandelure, 0),
      .enemyMonElevation = 0,
    }, //Chandelure,
[SPECIES_AXEW] = 
    {  
      //FRONT_PIC(Axew),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Axew),
      BACK_COORD(0x88,0),
      //PALETTES(Axew),
      PIC_DATA_ICON_INDEX(Axew,0),
      //ICON(Axew, 0),
      .enemyMonElevation = 0,
    }, //Axew,
[SPECIES_FRAXURE] = 
    {  
      //FRONT_PIC(Fraxure),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fraxure),
      BACK_COORD(0x88,0),
      //PALETTES(Fraxure),
      PIC_DATA_ICON_INDEX(Fraxure,0),
      //ICON(Fraxure, 0),
      .enemyMonElevation = 0,
    }, //Fraxure,
[SPECIES_HAXORUS] = 
    {  
      //FRONT_PIC(Haxorus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Haxorus),
      BACK_COORD(0x88,0),
      //PALETTES(Haxorus),
      PIC_DATA_ICON_INDEX(Haxorus,0),
      //ICON(Haxorus, 0),
      .enemyMonElevation = 0,
    }, //Haxorus,
[SPECIES_CUBCHOO] = 
    {  
      //FRONT_PIC(Cubchoo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cubchoo),
      BACK_COORD(0x88,0),
      //PALETTES(Cubchoo),
      PIC_DATA_ICON_INDEX(Cubchoo,0),
      //ICON(Cubchoo, 0),
      .enemyMonElevation = 0,
    }, //Cubchoo,
[SPECIES_BEARTIC] = 
    {  
      //FRONT_PIC(Beartic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Beartic),
      BACK_COORD(0x88,0),
      //PALETTES(Beartic),
      PIC_DATA_ICON_INDEX(Beartic,0),
      //ICON(Beartic, 0),
      .enemyMonElevation = 0,
    }, //Beartic,
[SPECIES_CRYOGONAL] = 
    {  
      //FRONT_PIC(Cryogonal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cryogonal),
      BACK_COORD(0x88,0),
      //PALETTES(Cryogonal),
      PIC_DATA_ICON_INDEX(Cryogonal,0),
      //ICON(Cryogonal, 0),
      .enemyMonElevation = 0,
    }, //Cryogonal,
[SPECIES_SHELMET] = 
    {  
      //FRONT_PIC(Shelmet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shelmet),
      BACK_COORD(0x88,0),
      //PALETTES(Shelmet),
      PIC_DATA_ICON_INDEX(Shelmet,0),
      //ICON(Shelmet, 0),
      .enemyMonElevation = 0,
    }, //Shelmet,
[SPECIES_ACCELGOR] = 
    {  
      //FRONT_PIC(Accelgor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Accelgor),
      BACK_COORD(0x88,0),
      //PALETTES(Accelgor),
      PIC_DATA_ICON_INDEX(Accelgor,0),
      //ICON(Accelgor, 0),
      .enemyMonElevation = 0,
    }, //Accelgor,
[SPECIES_STUNFISK] = 
    {  
      //FRONT_PIC(Stunfisk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stunfisk),
      BACK_COORD(0x88,0),
      //PALETTES(Stunfisk),
      PIC_DATA_ICON_INDEX(Stunfisk,0),
      //ICON(Stunfisk, 0),
      .enemyMonElevation = 0,
    }, //Stunfisk,
[SPECIES_MIENFOO] = 
    {  
      //FRONT_PIC(Mienfoo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mienfoo),
      BACK_COORD(0x88,0),
      //PALETTES(Mienfoo),
      PIC_DATA_ICON_INDEX(Mienfoo,0),
      //ICON(Mienfoo, 0),
      .enemyMonElevation = 0,
    }, //Mienfoo,
[SPECIES_MIENSHAO] = 
    {  
      //FRONT_PIC(Mienshao),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mienshao),
      BACK_COORD(0x88,0),
      //PALETTES(Mienshao),
      PIC_DATA_ICON_INDEX(Mienshao,0),
      //ICON(Mienshao, 0),
      .enemyMonElevation = 0,
    }, //Mienshao,
[SPECIES_DRUDDIGON] = 
    {  
      //FRONT_PIC(Druddigon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Druddigon),
      BACK_COORD(0x88,0),
      //PALETTES(Druddigon),
      PIC_DATA_ICON_INDEX(Druddigon,0),
      //ICON(Druddigon, 0),
      .enemyMonElevation = 0,
    }, //Druddigon,
[SPECIES_GOLETT] = 
    {  
      //FRONT_PIC(Golett),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Golett),
      BACK_COORD(0x88,0),
      //PALETTES(Golett),
      PIC_DATA_ICON_INDEX(Golett,0),
      //ICON(Golett, 0),
      .enemyMonElevation = 0,
    }, //Golett,
[SPECIES_GOLURK] = 
    {  
      //FRONT_PIC(Golurk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Golurk),
      BACK_COORD(0x88,0),
      //PALETTES(Golurk),
      PIC_DATA_ICON_INDEX(Golurk,0),
      //ICON(Golurk, 0),
      .enemyMonElevation = 0,
    }, //Golurk,
[SPECIES_PAWNIARD] = 
    {  
      //FRONT_PIC(Pawniard),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pawniard),
      BACK_COORD(0x88,0),
      //PALETTES(Pawniard),
      PIC_DATA_ICON_INDEX(Pawniard,0),
      //ICON(Pawniard, 0),
      .enemyMonElevation = 0,
    }, //Pawniard,
[SPECIES_BISHARP] = 
    {  
      //FRONT_PIC(Bisharp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bisharp),
      BACK_COORD(0x88,0),
      //PALETTES(Bisharp),
      PIC_DATA_ICON_INDEX(Bisharp,0),
      //ICON(Bisharp, 0),
      .enemyMonElevation = 0,
    }, //Bisharp,
[SPECIES_BOUFFALANT] = 
    {  
      //FRONT_PIC(Bouffalant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bouffalant),
      BACK_COORD(0x88,0),
      //PALETTES(Bouffalant),
      PIC_DATA_ICON_INDEX(Bouffalant,0),
      //ICON(Bouffalant, 0),
      .enemyMonElevation = 0,
    }, //Bouffalant,
[SPECIES_RUFFLET] = 
    {  
      //FRONT_PIC(Rufflet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rufflet),
      BACK_COORD(0x88,0),
      //PALETTES(Rufflet),
      PIC_DATA_ICON_INDEX(Rufflet,0),
      //ICON(Rufflet, 0),
      .enemyMonElevation = 0,
    }, //Rufflet,
[SPECIES_BRAVIARY] = 
    {  
      //FRONT_PIC(Braviary),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Braviary),
      BACK_COORD(0x88,0),
      //PALETTES(Braviary),
      PIC_DATA_ICON_INDEX(Braviary,0),
      //ICON(Braviary, 0),
      .enemyMonElevation = 0,
    }, //Braviary,
[SPECIES_VULLABY] = 
    {  
      //FRONT_PIC(Vullaby),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vullaby),
      BACK_COORD(0x88,0),
      //PALETTES(Vullaby),
      PIC_DATA_ICON_INDEX(Vullaby,0),
      //ICON(Vullaby, 0),
      .enemyMonElevation = 0,
    }, //Vullaby,
[SPECIES_MANDIBUZZ] = 
    {  
      //FRONT_PIC(Mandibuzz),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mandibuzz),
      BACK_COORD(0x88,0),
      //PALETTES(Mandibuzz),
      PIC_DATA_ICON_INDEX(Mandibuzz,0),
      //ICON(Mandibuzz, 0),
      .enemyMonElevation = 0,
    }, //Mandibuzz,
[SPECIES_HEATMOR] = 
    {  
      //FRONT_PIC(Heatmor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Heatmor),
      BACK_COORD(0x88,0),
      //PALETTES(Heatmor),
      PIC_DATA_ICON_INDEX(Heatmor,0),
      //ICON(Heatmor, 0),
      .enemyMonElevation = 0,
    }, //Heatmor,
[SPECIES_DURANT] = 
    {  
      //FRONT_PIC(Durant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Durant),
      BACK_COORD(0x88,0),
      //PALETTES(Durant),
      PIC_DATA_ICON_INDEX(Durant,0),
      //ICON(Durant, 0),
      .enemyMonElevation = 0,
    }, //Durant,
[SPECIES_DEINO] = 
    {  
      //FRONT_PIC(Deino),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Deino),
      BACK_COORD(0x88,0),
      //PALETTES(Deino),
      PIC_DATA_ICON_INDEX(Deino,0),
      //ICON(Deino, 0),
      .enemyMonElevation = 0,
    }, //Deino,
[SPECIES_ZWEILOUS] = 
    {  
      //FRONT_PIC(Zweilous),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zweilous),
      BACK_COORD(0x88,0),
      //PALETTES(Zweilous),
      PIC_DATA_ICON_INDEX(Zweilous,0),
      //ICON(Zweilous, 0),
      .enemyMonElevation = 0,
    }, //Zweilous,
[SPECIES_HYDREIGON] = 
    {  
      //FRONT_PIC(Hydreigon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hydreigon),
      BACK_COORD(0x88,0),
      //PALETTES(Hydreigon),
      PIC_DATA_ICON_INDEX(Hydreigon,0),
      //ICON(Hydreigon, 0),
      .enemyMonElevation = 0,
    }, //Hydreigon,
[SPECIES_LARVESTA] = 
    {  
      //FRONT_PIC(Larvesta),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Larvesta),
      BACK_COORD(0x88,0),
      //PALETTES(Larvesta),
      PIC_DATA_ICON_INDEX(Larvesta,0),
      //ICON(Larvesta, 0),
      .enemyMonElevation = 0,
    }, //Larvesta,
[SPECIES_VOLCARONA] = 
    {  
      //FRONT_PIC(Volcarona),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Volcarona),
      BACK_COORD(0x88,0),
      //PALETTES(Volcarona),
      PIC_DATA_ICON_INDEX(Volcarona,0),
      //ICON(Volcarona, 0),
      .enemyMonElevation = 0,
    }, //Volcarona,
[SPECIES_COBALION] = 
    {  
      //FRONT_PIC(Cobalion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cobalion),
      BACK_COORD(0x88,0),
      //PALETTES(Cobalion),
      PIC_DATA_ICON_INDEX(Cobalion,0),
      //ICON(Cobalion, 0),
      .enemyMonElevation = 0,
    }, //Cobalion,
[SPECIES_TERRAKION] = 
    {  
      //FRONT_PIC(Terrakion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Terrakion),
      BACK_COORD(0x88,0),
      //PALETTES(Terrakion),
      PIC_DATA_ICON_INDEX(Terrakion,0),
      //ICON(Terrakion, 0),
      .enemyMonElevation = 0,
    }, //Terrakion,
[SPECIES_VIRIZION] = 
    {  
      //FRONT_PIC(Virizion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Virizion),
      BACK_COORD(0x88,0),
      //PALETTES(Virizion),
      PIC_DATA_ICON_INDEX(Virizion,0),
      //ICON(Virizion, 0),
      .enemyMonElevation = 0,
    }, //Virizion,
[SPECIES_TORNADUS] = 
    {  
      //FRONT_PIC(Tornadus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tornadus),
      BACK_COORD(0x88,0),
      //PALETTES(Tornadus),
      PIC_DATA_ICON_INDEX(Tornadus,0),
      //ICON(Tornadus, 0),
      .enemyMonElevation = 0,
    }, //Tornadus,
[SPECIES_THUNDURUS] = 
    {  
      //FRONT_PIC(Thundurus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Thundurus),
      BACK_COORD(0x88,0),
      //PALETTES(Thundurus),
      PIC_DATA_ICON_INDEX(Thundurus,0),
      //ICON(Thundurus, 0),
      .enemyMonElevation = 0,
    }, //Thundurus,
[SPECIES_RESHIRAM] = 
    {  
      //FRONT_PIC(Reshiram),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Reshiram),
      BACK_COORD(0x88,0),
      //PALETTES(Reshiram),
      PIC_DATA_ICON_INDEX(Reshiram,0),
      //ICON(Reshiram, 0),
      .enemyMonElevation = 0,
    }, //Reshiram,
[SPECIES_ZEKROM] = 
    {  
      //FRONT_PIC(Zekrom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zekrom),
      BACK_COORD(0x88,0),
      //PALETTES(Zekrom),
      PIC_DATA_ICON_INDEX(Zekrom,0),
      //ICON(Zekrom, 0),
      .enemyMonElevation = 0,
    }, //Zekrom,
[SPECIES_LANDORUS] = 
    {  
      //FRONT_PIC(Landorus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Landorus),
      BACK_COORD(0x88,0),
      //PALETTES(Landorus),
      PIC_DATA_ICON_INDEX(Landorus,0),
      //ICON(Landorus, 0),
      .enemyMonElevation = 0,
    }, //Landorus,
[SPECIES_KYUREM] = 
    {  
      //FRONT_PIC(Kyurem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kyurem),
      BACK_COORD(0x88,0),
      //PALETTES(Kyurem),
      PIC_DATA_ICON_INDEX(Kyurem,0),
      //ICON(Kyurem, 0),
      .enemyMonElevation = 0,
    }, //Kyurem,
[SPECIES_KELDEO] = 
    {  
      //FRONT_PIC(Keldeo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Keldeo),
      BACK_COORD(0x88,0),
      //PALETTES(Keldeo),
      PIC_DATA_ICON_INDEX(Keldeo,0),
      //ICON(Keldeo, 0),
      .enemyMonElevation = 0,
    }, //Keldeo,
[SPECIES_MELOETTA] = 
    {  
      //FRONT_PIC(Meloetta),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Meloetta),
      BACK_COORD(0x88,0),
      //PALETTES(Meloetta),
      PIC_DATA_ICON_INDEX(Meloetta,0),
      //ICON(Meloetta, 0),
      .enemyMonElevation = 0,
    }, //Meloetta,
[SPECIES_GENESECT] = 
    {  
      //FRONT_PIC(Genesect),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Genesect),
      BACK_COORD(0x88,0),
      //PALETTES(Genesect),
      PIC_DATA_ICON_INDEX(Genesect,0),
      //ICON(Genesect, 0),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_CHESPIN] = 
    {  
      //FRONT_PIC(Chespin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chespin),
      BACK_COORD(0x88,0),
      //PALETTES(Chespin),
      PIC_DATA_ICON_INDEX(Chespin,0),
      //ICON(Chespin, 0),
      .enemyMonElevation = 0,
    }, //Chespin,
[SPECIES_QUILLADIN] = 
    {  
      //FRONT_PIC(Quilladin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Quilladin),
      BACK_COORD(0x88,0),
      //PALETTES(Quilladin),
      PIC_DATA_ICON_INDEX(Quilladin,0),
      //ICON(Quilladin, 0),
      .enemyMonElevation = 0,
    }, //Quilladin,
[SPECIES_CHESNAUGHT] = 
    {  
      //FRONT_PIC(Chesnaught),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chesnaught),
      BACK_COORD(0x88,0),
      //PALETTES(Chesnaught),
      PIC_DATA_ICON_INDEX(Chesnaught,0),
      //ICON(Chesnaught, 0),
      .enemyMonElevation = 0,
    }, //Chesnaught,
[SPECIES_FENNEKIN] = 
    {  
      //FRONT_PIC(Fennekin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fennekin),
      BACK_COORD(0x88,0),
      //PALETTES(Fennekin),
      PIC_DATA_ICON_INDEX(Fennekin,0),
      //ICON(Fennekin, 0),
      .enemyMonElevation = 0,
    }, //Fennekin,
[SPECIES_BRAIXEN] = 
    {  
      //FRONT_PIC(Braixen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Braixen),
      BACK_COORD(0x88,0),
      //PALETTES(Braixen),
      PIC_DATA_ICON_INDEX(Braixen,0),
      //ICON(Braixen, 0),
      .enemyMonElevation = 0,
    }, //Braixen,
[SPECIES_DELPHOX] = 
    {  
      //FRONT_PIC(Delphox),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Delphox),
      BACK_COORD(0x88,0),
      //PALETTES(Delphox),
      PIC_DATA_ICON_INDEX(Delphox,0),
      //ICON(Delphox, 0),
      .enemyMonElevation = 0,
    }, //Delphox,
[SPECIES_FROAKIE] = 
    {  
      //FRONT_PIC(Froakie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Froakie),
      BACK_COORD(0x88,0),
      //PALETTES(Froakie),
      PIC_DATA_ICON_INDEX(Froakie,0),
      //ICON(Froakie, 0),
      .enemyMonElevation = 0,
    }, //Froakie,
[SPECIES_FROGADIER] = 
    {  
      //FRONT_PIC(Frogadier),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Frogadier),
      BACK_COORD(0x88,0),
      //PALETTES(Frogadier),
      PIC_DATA_ICON_INDEX(Frogadier,0),
      //ICON(Frogadier, 0),
      .enemyMonElevation = 0,
    }, //Frogadier,
[SPECIES_GRENINJA] = 
    {  
      //FRONT_PIC(Greninja),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Greninja),
      BACK_COORD(0x88,0),
      //PALETTES(Greninja),
      PIC_DATA_ICON_INDEX(Greninja,0),
      //ICON(Greninja, 0),
      .enemyMonElevation = 0,
    }, //Greninja,
[SPECIES_BUNNELBY] = 
    {  
      //FRONT_PIC(Bunnelby),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bunnelby),
      BACK_COORD(0x88,0),
      //PALETTES(Bunnelby),
      PIC_DATA_ICON_INDEX(Bunnelby,0),
      //ICON(Bunnelby, 0),
      .enemyMonElevation = 0,
    }, //Bunnelby,
[SPECIES_DIGGERSBY] = 
    {  
      //FRONT_PIC(Diggersby),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Diggersby),
      BACK_COORD(0x88,0),
      //PALETTES(Diggersby),
      PIC_DATA_ICON_INDEX(Diggersby,0),
      //ICON(Diggersby, 0),
      .enemyMonElevation = 0,
    }, //Diggersby,
[SPECIES_FLETCHLING] = 
    {  
      //FRONT_PIC(Fletchling),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fletchling),
      BACK_COORD(0x88,0),
      //PALETTES(Fletchling),
      PIC_DATA_ICON_INDEX(Fletchling,0),
      //ICON(Fletchling, 0),
      .enemyMonElevation = 0,
    }, //Fletchling,
[SPECIES_FLETCHINDER] = 
    {  
      //FRONT_PIC(Fletchinder),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fletchinder),
      BACK_COORD(0x88,0),
      //PALETTES(Fletchinder),
      PIC_DATA_ICON_INDEX(Fletchinder,0),
      //ICON(Fletchinder, 0),
      .enemyMonElevation = 0,
    }, //Fletchinder,
[SPECIES_TALONFLAME] = 
    {  
      //FRONT_PIC(Talonflame),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Talonflame),
      BACK_COORD(0x88,0),
      //PALETTES(Talonflame),
      PIC_DATA_ICON_INDEX(Talonflame,0),
      //ICON(Talonflame, 0),
      .enemyMonElevation = 0,
    }, //Talonflame,
[SPECIES_SCATTERBUG] = 
    {  
      //FRONT_PIC(Scatterbug),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scatterbug),
      BACK_COORD(0x88,0),
      //PALETTES(Scatterbug),
      PIC_DATA_ICON_INDEX(Scatterbug,0),
      //ICON(Scatterbug, 0),
      .enemyMonElevation = 0,
    }, //Scatterbug,
[SPECIES_SPEWPA] = 
    {  
      //FRONT_PIC(Spewpa),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spewpa),
      BACK_COORD(0x88,0),
      //PALETTES(Spewpa),
      PIC_DATA_ICON_INDEX(Spewpa,0),
      //ICON(Spewpa, 0),
      .enemyMonElevation = 0,
    }, //Spewpa,
[SPECIES_VIVILLON_SNOW] = 
    {  
      //FRONT_PIC(VivillonSnow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonSnow),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonSnow),
      PIC_DATA_ICON_INDEX(VivillonSnow,0),
      //ICON(VivillonSnow, 0),
      .enemyMonElevation = 0,
    }, //Vivillon,
[SPECIES_LITLEO] = 
    {  
      //FRONT_PIC(Litleo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Litleo),
      BACK_COORD(0x88,0),
      //PALETTES(Litleo),
      PIC_DATA_ICON_INDEX(Litleo,0),
      //ICON(Litleo, 0),
      .enemyMonElevation = 0,
    }, //Litleo,
[SPECIES_PYROAR_MALE] = 
    {  
      //FRONT_PIC(PyroarMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PyroarMale),
      BACK_COORD(0x88,0),
      //PALETTES(PyroarMale),
      PIC_DATA_ICON_INDEX(PyroarMale,0),
      //ICON(PyroarMale, 0),
      .enemyMonElevation = 0,
    }, //Pyroar,
[SPECIES_FLABEBE] = 
    {  
      //FRONT_PIC(Flabebe),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flabebe),
      BACK_COORD(0x88,0),
      //PALETTES(Flabebe),
      PIC_DATA_ICON_INDEX(Flabebe,0),
      //ICON(Flabebe, 0),
      .enemyMonElevation = 0,
    }, //Flabebe,
[SPECIES_FLOETTE] = 
    {  
      //FRONT_PIC(Floette),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Floette),
      BACK_COORD(0x88,0),
      //PALETTES(Floette),
      PIC_DATA_ICON_INDEX(Floette,0),
      //ICON(Floette, 0),
      .enemyMonElevation = 0,
    }, //Floette,
[SPECIES_FLORGES] = 
    {  
      //FRONT_PIC(Florges),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Florges),
      BACK_COORD(0x88,0),
      //PALETTES(Florges),
      PIC_DATA_ICON_INDEX(Florges,0),
      //ICON(Florges, 0),
      .enemyMonElevation = 0,
    }, //Florges,
[SPECIES_SKIDDO] = 
    {  
      //FRONT_PIC(Skiddo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skiddo),
      BACK_COORD(0x88,0),
      //PALETTES(Skiddo),
      PIC_DATA_ICON_INDEX(Skiddo,0),
      //ICON(Skiddo, 0),
      .enemyMonElevation = 0,
    }, //Skiddo,
[SPECIES_GOGOAT] = 
    {  
      //FRONT_PIC(Gogoat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gogoat),
      BACK_COORD(0x88,0),
      //PALETTES(Gogoat),
      PIC_DATA_ICON_INDEX(Gogoat,0),
      //ICON(Gogoat, 0),
      .enemyMonElevation = 0,
    }, //Gogoat,
[SPECIES_PANCHAM] = 
    {  
      //FRONT_PIC(Pancham),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pancham),
      BACK_COORD(0x88,0),
      //PALETTES(Pancham),
      PIC_DATA_ICON_INDEX(Pancham,0),
      //ICON(Pancham, 0),
      .enemyMonElevation = 0,
    }, //Pancham,
[SPECIES_PANGORO] = 
    {  
      //FRONT_PIC(Pangoro),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pangoro),
      BACK_COORD(0x88,0),
      //PALETTES(Pangoro),
      PIC_DATA_ICON_INDEX(Pangoro,0),
      //ICON(Pangoro, 0),
      .enemyMonElevation = 0,
    }, //Pangoro,
[SPECIES_FURFROU] = 
    {  
      //FRONT_PIC(Furfrou),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Furfrou),
      BACK_COORD(0x88,0),
      //PALETTES(Furfrou),
      PIC_DATA_ICON_INDEX(Furfrou,0),
      //ICON(Furfrou, 0),
      .enemyMonElevation = 0,
    }, //Furfrou,
[SPECIES_ESPURR] = 
    {  
      //FRONT_PIC(Espurr),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Espurr),
      BACK_COORD(0x88,0),
      //PALETTES(Espurr),
      PIC_DATA_ICON_INDEX(Espurr,0),
      //ICON(Espurr, 0),
      .enemyMonElevation = 0,
    }, //Espurr,
[SPECIES_MEOWSTIC_MALE] = 
    {  
      //FRONT_PIC(MeowsticMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MeowsticMale),
      BACK_COORD(0x88,0),
      //PALETTES(MeowsticMale),
      PIC_DATA_ICON_INDEX(MeowsticMale,0),
      //ICON(MeowsticMale, 0),
      .enemyMonElevation = 0,
    }, //Meowstic,
[SPECIES_HONEDGE] = 
    {  
      //FRONT_PIC(Honedge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Honedge),
      BACK_COORD(0x88,0),
      //PALETTES(Honedge),
      PIC_DATA_ICON_INDEX(Honedge,0),
      //ICON(Honedge, 0),
      .enemyMonElevation = 0,
    }, //Honedge,
[SPECIES_DOUBLADE] = 
    {  
      //FRONT_PIC(Doublade),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Doublade),
      BACK_COORD(0x88,0),
      //PALETTES(Doublade),
      PIC_DATA_ICON_INDEX(Doublade,0),
      //ICON(Doublade, 0),
      .enemyMonElevation = 0,
    }, //Doublade,
[SPECIES_AEGISLASH] = 
    {  
      //FRONT_PIC(Aegislash),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aegislash),
      BACK_COORD(0x88,0),
      //PALETTES(Aegislash),
      PIC_DATA_ICON_INDEX(Aegislash,0),
      //ICON(Aegislash, 0),
      .enemyMonElevation = 0,
    }, //Aegislash,
[SPECIES_SPRITZEE] = 
    {  
      //FRONT_PIC(Spritzee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spritzee),
      BACK_COORD(0x88,0),
      //PALETTES(Spritzee),
      PIC_DATA_ICON_INDEX(Spritzee,0),
      //ICON(Spritzee, 0),
      .enemyMonElevation = 0,
    }, //Spritzee,
[SPECIES_AROMATISSE] = 
    {  
      //FRONT_PIC(Aromatisse),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aromatisse),
      BACK_COORD(0x88,0),
      //PALETTES(Aromatisse),
      PIC_DATA_ICON_INDEX(Aromatisse,0),
      //ICON(Aromatisse, 0),
      .enemyMonElevation = 0,
    }, //Aromatisse,
[SPECIES_SWIRLIX] = 
    {  
      //FRONT_PIC(Swirlix),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Swirlix),
      BACK_COORD(0x88,0),
      //PALETTES(Swirlix),
      PIC_DATA_ICON_INDEX(Swirlix,0),
      //ICON(Swirlix, 0),
      .enemyMonElevation = 0,
    }, //Swirlix,
[SPECIES_SLURPUFF] = 
    {  
      //FRONT_PIC(Slurpuff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Slurpuff),
      BACK_COORD(0x88,0),
      //PALETTES(Slurpuff),
      PIC_DATA_ICON_INDEX(Slurpuff,0),
      //ICON(Slurpuff, 0),
      .enemyMonElevation = 0,
    }, //Slurpuff,
[SPECIES_INKAY] = 
    {  
      //FRONT_PIC(Inkay),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Inkay),
      BACK_COORD(0x88,0),
      //PALETTES(Inkay),
      PIC_DATA_ICON_INDEX(Inkay,0),
      //ICON(Inkay, 0),
      .enemyMonElevation = 0,
    }, //Inkay,
[SPECIES_MALAMAR] = 
    {  
      //FRONT_PIC(Malamar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Malamar),
      BACK_COORD(0x88,0),
      //PALETTES(Malamar),
      PIC_DATA_ICON_INDEX(Malamar,0),
      //ICON(Malamar, 0),
      .enemyMonElevation = 0,
    }, //Malamar,
[SPECIES_BINACLE] = 
    {  
      //FRONT_PIC(Binacle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Binacle),
      BACK_COORD(0x88,0),
      //PALETTES(Binacle),
      PIC_DATA_ICON_INDEX(Binacle,0),
      //ICON(Binacle, 0),
      .enemyMonElevation = 0,
    }, //Binacle,
[SPECIES_BARBARACLE] = 
    {  
      //FRONT_PIC(Barbaracle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Barbaracle),
      BACK_COORD(0x88,0),
      //PALETTES(Barbaracle),
      PIC_DATA_ICON_INDEX(Barbaracle,0),
      //ICON(Barbaracle, 0),
      .enemyMonElevation = 0,
    }, //Barbaracle,
[SPECIES_SKRELP] = 
    {  
      //FRONT_PIC(Skrelp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skrelp),
      BACK_COORD(0x88,0),
      //PALETTES(Skrelp),
      PIC_DATA_ICON_INDEX(Skrelp,0),
      //ICON(Skrelp, 0),
      .enemyMonElevation = 0,
    }, //Skrelp,
[SPECIES_DRAGALGE] = 
    {  
      //FRONT_PIC(Dragalge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dragalge),
      BACK_COORD(0x88,0),
      //PALETTES(Dragalge),
      PIC_DATA_ICON_INDEX(Dragalge,0),
      //ICON(Dragalge, 0),
      .enemyMonElevation = 0,
    }, //Dragalge,
[SPECIES_CLAUNCHER] = 
    {  
      //FRONT_PIC(Clauncher),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clauncher),
      BACK_COORD(0x88,0),
      //PALETTES(Clauncher),
      PIC_DATA_ICON_INDEX(Clauncher,0),
      //ICON(Clauncher, 0),
      .enemyMonElevation = 0,
    }, //Clauncher,
[SPECIES_CLAWITZER] = 
    {  
      //FRONT_PIC(Clawitzer),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clawitzer),
      BACK_COORD(0x88,0),
      //PALETTES(Clawitzer),
      PIC_DATA_ICON_INDEX(Clawitzer,0),
      //ICON(Clawitzer, 0),
      .enemyMonElevation = 0,
    }, //Clawitzer,
[SPECIES_HELIOPTILE] = 
    {  
      //FRONT_PIC(Helioptile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Helioptile),
      BACK_COORD(0x88,0),
      //PALETTES(Helioptile),
      PIC_DATA_ICON_INDEX(Helioptile,0),
      //ICON(Helioptile, 0),
      .enemyMonElevation = 0,
    }, //Helioptile,
[SPECIES_HELIOLISK] = 
    {  
      //FRONT_PIC(Heliolisk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Heliolisk),
      BACK_COORD(0x88,0),
      //PALETTES(Heliolisk),
      PIC_DATA_ICON_INDEX(Heliolisk,0),
      //ICON(Heliolisk, 0),
      .enemyMonElevation = 0,
    }, //Heliolisk,
[SPECIES_TYRUNT] = 
    {  
      //FRONT_PIC(Tyrunt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tyrunt),
      BACK_COORD(0x88,0),
      //PALETTES(Tyrunt),
      PIC_DATA_ICON_INDEX(Tyrunt,0),
      //ICON(Tyrunt, 0),
      .enemyMonElevation = 0,
    }, //Tyrunt,
[SPECIES_TYRANTRUM] = 
    {  
      //FRONT_PIC(Tyrantrum),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tyrantrum),
      BACK_COORD(0x88,0),
      //PALETTES(Tyrantrum),
      PIC_DATA_ICON_INDEX(Tyrantrum,0),
      //ICON(Tyrantrum, 0),
      .enemyMonElevation = 0,
    }, //Tyrantrum,
[SPECIES_AMAURA] = 
    {  
      //FRONT_PIC(Amaura),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Amaura),
      BACK_COORD(0x88,0),
      //PALETTES(Amaura),
      PIC_DATA_ICON_INDEX(Amaura,0),
      //ICON(Amaura, 0),
      .enemyMonElevation = 0,
    }, //Amaura,
[SPECIES_AURORUS] = 
    {  
      //FRONT_PIC(Aurorus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Aurorus),
      BACK_COORD(0x88,0),
      //PALETTES(Aurorus),
      PIC_DATA_ICON_INDEX(Aurorus,0),
      //ICON(Aurorus, 0),
      .enemyMonElevation = 0,
    }, //Aurorus,
[SPECIES_SYLVEON] = 
    {  
      //FRONT_PIC(Sylveon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sylveon),
      BACK_COORD(0x88,0),
      //PALETTES(Sylveon),
      PIC_DATA_ICON_INDEX(Sylveon,0),
      //ICON(Sylveon, 0),
      .enemyMonElevation = 0,
    }, //Sylveon,
[SPECIES_HAWLUCHA] = 
    {  
      //FRONT_PIC(Hawlucha),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hawlucha),
      BACK_COORD(0x88,0),
      //PALETTES(Hawlucha),
      PIC_DATA_ICON_INDEX(Hawlucha,0),
      //ICON(Hawlucha, 0),
      .enemyMonElevation = 0,
    }, //Hawlucha,
[SPECIES_DEDENNE] = 
    {  
      //FRONT_PIC(Dedenne),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dedenne),
      BACK_COORD(0x88,0),
      //PALETTES(Dedenne),
      PIC_DATA_ICON_INDEX(Dedenne,0),
      //ICON(Dedenne, 0),
      .enemyMonElevation = 0,
    }, //Dedenne,
[SPECIES_CARBINK] = 
    {  
      //FRONT_PIC(Carbink),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Carbink),
      BACK_COORD(0x88,0),
      //PALETTES(Carbink),
      PIC_DATA_ICON_INDEX(Carbink,0),
      //ICON(Carbink, 0),
      .enemyMonElevation = 0,
    }, //Carbink,
[SPECIES_GOOMY] = 
    {  
      //FRONT_PIC(Goomy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Goomy),
      BACK_COORD(0x88,0),
      //PALETTES(Goomy),
      PIC_DATA_ICON_INDEX(Goomy,0),
      //ICON(Goomy, 0),
      .enemyMonElevation = 0,
    }, //Goomy,
[SPECIES_SLIGGOO] = 
    {  
      //FRONT_PIC(Sliggoo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sliggoo),
      BACK_COORD(0x88,0),
      //PALETTES(Sliggoo),
      PIC_DATA_ICON_INDEX(Sliggoo,0),
      //ICON(Sliggoo, 0),
      .enemyMonElevation = 0,
    }, //Sliggoo,
[SPECIES_GOODRA] = 
    {  
      //FRONT_PIC(Goodra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Goodra),
      BACK_COORD(0x88,0),
      //PALETTES(Goodra),
      PIC_DATA_ICON_INDEX(Goodra,0),
      //ICON(Goodra, 0),
      .enemyMonElevation = 0,
    }, //Goodra,
[SPECIES_KLEFKI] = 
    {  
      //FRONT_PIC(Klefki),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Klefki),
      BACK_COORD(0x88,0),
      //PALETTES(Klefki),
      PIC_DATA_ICON_INDEX(Klefki,0),
      //ICON(Klefki, 0),
      .enemyMonElevation = 0,
    }, //Klefki,
[SPECIES_PHANTUMP] = 
    {  
      //FRONT_PIC(Phantump),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Phantump),
      BACK_COORD(0x88,0),
      //PALETTES(Phantump),
      PIC_DATA_ICON_INDEX(Phantump,0),
      //ICON(Phantump, 0),
      .enemyMonElevation = 0,
    }, //Phantump,
[SPECIES_TREVENANT] = 
    {  
      //FRONT_PIC(Trevenant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Trevenant),
      BACK_COORD(0x88,0),
      //PALETTES(Trevenant),
      PIC_DATA_ICON_INDEX(Trevenant,0),
      //ICON(Trevenant, 0),
      .enemyMonElevation = 0,
    }, //Trevenant,
[SPECIES_PUMPKABOO_AVERAGE_SIZE] = 
    {  
      //FRONT_PIC(PumpkabooAverageSize),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PumpkabooAverageSize),
      BACK_COORD(0x88,0),
      //PALETTES(PumpkabooAverageSize),
      PIC_DATA_ICON_INDEX(PumpkabooAverageSize,0),
      //ICON(PumpkabooAverageSize, 0),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_GOURGEIST_AVERAGE_SIZE] = 
    {  
      //FRONT_PIC(GourgeistAverageSize),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GourgeistAverageSize),
      BACK_COORD(0x88,0),
      //PALETTES(GourgeistAverageSize),
      PIC_DATA_ICON_INDEX(GourgeistAverageSize,0),
      //ICON(GourgeistAverageSize, 0),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_BERGMITE] = 
    {  
      //FRONT_PIC(Bergmite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bergmite),
      BACK_COORD(0x88,0),
      //PALETTES(Bergmite),
      PIC_DATA_ICON_INDEX(Bergmite,0),
      //ICON(Bergmite, 0),
      .enemyMonElevation = 0,
    }, //Bergmite,
[SPECIES_AVALUGG] = 
    {  
      //FRONT_PIC(Avalugg),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Avalugg),
      BACK_COORD(0x88,0),
      //PALETTES(Avalugg),
      PIC_DATA_ICON_INDEX(Avalugg,0),
      //ICON(Avalugg, 0),
      .enemyMonElevation = 0,
    }, //Avalugg,
[SPECIES_NOIBAT] = 
    {  
      //FRONT_PIC(Noibat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Noibat),
      BACK_COORD(0x88,0),
      //PALETTES(Noibat),
      PIC_DATA_ICON_INDEX(Noibat,0),
      //ICON(Noibat, 0),
      .enemyMonElevation = 0,
    }, //Noibat,
[SPECIES_NOIVERN] = 
    {  
      //FRONT_PIC(Noivern),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Noivern),
      BACK_COORD(0x88,0),
      //PALETTES(Noivern),
      PIC_DATA_ICON_INDEX(Noivern,0),
      //ICON(Noivern, 0),
      .enemyMonElevation = 0,
    }, //Noivern,
[SPECIES_XERNEAS] = 
    {  
      //FRONT_PIC(Xerneas),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Xerneas),
      BACK_COORD(0x88,0),
      //PALETTES(Xerneas),
      PIC_DATA_ICON_INDEX(Xerneas,0),
      //ICON(Xerneas, 0),
      .enemyMonElevation = 0,
    }, //Xerneas,
[SPECIES_YVELTAL] = 
    {  
      //FRONT_PIC(Yveltal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Yveltal),
      BACK_COORD(0x88,0),
      //PALETTES(Yveltal),
      PIC_DATA_ICON_INDEX(Yveltal,0),
      //ICON(Yveltal, 0),
      .enemyMonElevation = 0,
    }, //Yveltal,
[SPECIES_ZYGARDE] = 
    {  
      //FRONT_PIC(Zygarde),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zygarde),
      BACK_COORD(0x88,0),
      //PALETTES(Zygarde),
      PIC_DATA_ICON_INDEX(Zygarde,0),
      //ICON(Zygarde, 0),
      .enemyMonElevation = 0,
    }, //Zygarde,
[SPECIES_DIANCIE] = 
    {  
      //FRONT_PIC(Diancie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Diancie),
      BACK_COORD(0x88,0),
      //PALETTES(Diancie),
      PIC_DATA_ICON_INDEX(Diancie,0),
      //ICON(Diancie, 0),
      .enemyMonElevation = 0,
    }, //Diancie,
[SPECIES_HOOPA] = 
    {  
      //FRONT_PIC(Hoopa),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hoopa),
      BACK_COORD(0x88,0),
      //PALETTES(Hoopa),
      PIC_DATA_ICON_INDEX(Hoopa,0),
      //ICON(Hoopa, 0),
      .enemyMonElevation = 0,
    }, //Hoopa,
[SPECIES_VOLCANION] = 
    {  
      //FRONT_PIC(Volcanion),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Volcanion),
      BACK_COORD(0x88,0),
      //PALETTES(Volcanion),
      PIC_DATA_ICON_INDEX(Volcanion,0),
      //ICON(Volcanion, 0),
      .enemyMonElevation = 0,
    }, //Volcanion,
[SPECIES_ROWLET] = 
    {  
      //FRONT_PIC(Rowlet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rowlet),
      BACK_COORD(0x88,0),
      //PALETTES(Rowlet),
      PIC_DATA_ICON_INDEX(Rowlet,0),
      //ICON(Rowlet, 0),
      .enemyMonElevation = 0,
    }, //Rowlet,
[SPECIES_DARTRIX] = 
    {  
      //FRONT_PIC(Dartrix),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dartrix),
      BACK_COORD(0x88,0),
      //PALETTES(Dartrix),
      PIC_DATA_ICON_INDEX(Dartrix,0),
      //ICON(Dartrix, 0),
      .enemyMonElevation = 0,
    }, //Dartrix,
[SPECIES_DECIDUEYE] = 
    {  
      //FRONT_PIC(Decidueye),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Decidueye),
      BACK_COORD(0x88,0),
      //PALETTES(Decidueye),
      PIC_DATA_ICON_INDEX(Decidueye,0),
      //ICON(Decidueye, 0),
      .enemyMonElevation = 0,
    }, //Decidueye,
[SPECIES_LITTEN] = 
    {  
      //FRONT_PIC(Litten),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Litten),
      BACK_COORD(0x88,0),
      //PALETTES(Litten),
      PIC_DATA_ICON_INDEX(Litten,0),
      //ICON(Litten, 0),
      .enemyMonElevation = 0,
    }, //Litten,
[SPECIES_TORRACAT] = 
    {  
      //FRONT_PIC(Torracat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Torracat),
      BACK_COORD(0x88,0),
      //PALETTES(Torracat),
      PIC_DATA_ICON_INDEX(Torracat,0),
      //ICON(Torracat, 0),
      .enemyMonElevation = 0,
    }, //Torracat,
[SPECIES_INCINEROAR] = 
    {  
      //FRONT_PIC(Incineroar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Incineroar),
      BACK_COORD(0x88,0),
      //PALETTES(Incineroar),
      PIC_DATA_ICON_INDEX(Incineroar,0),
      //ICON(Incineroar, 0),
      .enemyMonElevation = 0,
    }, //Incineroar,
[SPECIES_POPPLIO] = 
    {  
      //FRONT_PIC(Popplio),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Popplio),
      BACK_COORD(0x88,0),
      //PALETTES(Popplio),
      PIC_DATA_ICON_INDEX(Popplio,0),
      //ICON(Popplio, 0),
      .enemyMonElevation = 0,
    }, //Popplio,
[SPECIES_BRIONNE] = 
    {  
      //FRONT_PIC(Brionne),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Brionne),
      BACK_COORD(0x88,0),
      //PALETTES(Brionne),
      PIC_DATA_ICON_INDEX(Brionne,0),
      //ICON(Brionne, 0),
      .enemyMonElevation = 0,
    }, //Brionne,
[SPECIES_PRIMARINA] = 
    {  
      //FRONT_PIC(Primarina),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Primarina),
      BACK_COORD(0x88,0),
      //PALETTES(Primarina),
      PIC_DATA_ICON_INDEX(Primarina,0),
      //ICON(Primarina, 0),
      .enemyMonElevation = 0,
    }, //Primarina,
[SPECIES_PIKIPEK] = 
    {  
      //FRONT_PIC(Pikipek),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pikipek),
      BACK_COORD(0x88,0),
      //PALETTES(Pikipek),
      PIC_DATA_ICON_INDEX(Pikipek,0),
      //ICON(Pikipek, 0),
      .enemyMonElevation = 0,
    }, //Pikipek,
[SPECIES_TRUMBEAK] = 
    {  
      //FRONT_PIC(Trumbeak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Trumbeak),
      BACK_COORD(0x88,0),
      //PALETTES(Trumbeak),
      PIC_DATA_ICON_INDEX(Trumbeak,0),
      //ICON(Trumbeak, 0),
      .enemyMonElevation = 0,
    }, //Trumbeak,
[SPECIES_TOUCANNON] = 
    {  
      //FRONT_PIC(Toucannon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toucannon),
      BACK_COORD(0x88,0),
      //PALETTES(Toucannon),
      PIC_DATA_ICON_INDEX(Toucannon,0),
      //ICON(Toucannon, 0),
      .enemyMonElevation = 0,
    }, //Toucannon,
[SPECIES_YUNGOOS] = 
    {  
      //FRONT_PIC(Yungoos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Yungoos),
      BACK_COORD(0x88,0),
      //PALETTES(Yungoos),
      PIC_DATA_ICON_INDEX(Yungoos,0),
      //ICON(Yungoos, 0),
      .enemyMonElevation = 0,
    }, //Yungoos,
[SPECIES_GUMSHOOS] = 
    {  
      //FRONT_PIC(Gumshoos),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gumshoos),
      BACK_COORD(0x88,0),
      //PALETTES(Gumshoos),
      PIC_DATA_ICON_INDEX(Gumshoos,0),
      //ICON(Gumshoos, 0),
      .enemyMonElevation = 0,
    }, //Gumshoos,
[SPECIES_GRUBBIN] = 
    {  
      //FRONT_PIC(Grubbin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grubbin),
      BACK_COORD(0x88,0),
      //PALETTES(Grubbin),
      PIC_DATA_ICON_INDEX(Grubbin,0),
      //ICON(Grubbin, 0),
      .enemyMonElevation = 0,
    }, //Grubbin,
[SPECIES_CHARJABUG] = 
    {  
      //FRONT_PIC(Charjabug),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charjabug),
      BACK_COORD(0x88,0),
      //PALETTES(Charjabug),
      PIC_DATA_ICON_INDEX(Charjabug,0),
      //ICON(Charjabug, 0),
      .enemyMonElevation = 0,
    }, //Charjabug,
[SPECIES_VIKAVOLT] = 
    {  
      //FRONT_PIC(Vikavolt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Vikavolt),
      BACK_COORD(0x88,0),
      //PALETTES(Vikavolt),
      PIC_DATA_ICON_INDEX(Vikavolt,0),
      //ICON(Vikavolt, 0),
      .enemyMonElevation = 0,
    }, //Vikavolt,
[SPECIES_CRABRAWLER] = 
    {  
      //FRONT_PIC(Crabrawler),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Crabrawler),
      BACK_COORD(0x88,0),
      //PALETTES(Crabrawler),
      PIC_DATA_ICON_INDEX(Crabrawler,0),
      //ICON(Crabrawler, 0),
      .enemyMonElevation = 0,
    }, //Crabrawler,
[SPECIES_CRABOMINABLE] = 
    {  
      //FRONT_PIC(Crabominable),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Crabominable),
      BACK_COORD(0x88,0),
      //PALETTES(Crabominable),
      PIC_DATA_ICON_INDEX(Crabominable,0),
      //ICON(Crabominable, 0),
      .enemyMonElevation = 0,
    }, //Crabominable,
[SPECIES_ORICORIO_BAILE] = 
    {  
      //FRONT_PIC(Oricorio_Baile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Oricorio_Baile),
      BACK_COORD(0x88,0),
      //PALETTES(Oricorio_Baile),
      PIC_DATA_ICON_INDEX(OricorioBaile,0),
      //ICON(OricorioBaile, 0),
      .enemyMonElevation = 0,
    }, //Oricorio_Baile,
[SPECIES_CUTIEFLY] = 
    {  
      //FRONT_PIC(Cutiefly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cutiefly),
      BACK_COORD(0x88,0),
      //PALETTES(Cutiefly),
      PIC_DATA_ICON_INDEX(Cutiefly,0),
      //ICON(Cutiefly, 0),
      .enemyMonElevation = 0,
    }, //Cutiefly,
[SPECIES_RIBOMBEE] = 
    {  
      //FRONT_PIC(Ribombee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ribombee),
      BACK_COORD(0x88,0),
      //PALETTES(Ribombee),
      PIC_DATA_ICON_INDEX(Ribombee,0),
      //ICON(Ribombee, 0),
      .enemyMonElevation = 0,
    }, //Ribombee,
[SPECIES_ROCKRUFF] = 
    {  
      //FRONT_PIC(Rockruff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rockruff),
      BACK_COORD(0x88,0),
      //PALETTES(Rockruff),
      PIC_DATA_ICON_INDEX(Rockruff,0),
      //ICON(Rockruff, 0),
      .enemyMonElevation = 0,
    }, //Rockruff,
[SPECIES_LYCANROC_MIDDAY] = 
    {  
      //FRONT_PIC(LycanrocMidday),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LycanrocMidday),
      BACK_COORD(0x88,0),
      //PALETTES(LycanrocMidday),
      PIC_DATA_ICON_INDEX(LycanrocMidday,0),
      //ICON(LycanrocMidday, 0),
      .enemyMonElevation = 0,
    }, //Lycanroc,
[SPECIES_WISHIWASHI] = 
    {  
      //FRONT_PIC(Wishiwashi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wishiwashi),
      BACK_COORD(0x88,0),
      //PALETTES(Wishiwashi),
      PIC_DATA_ICON_INDEX(Wishiwashi,0),
      //ICON(Wishiwashi, 0),
      .enemyMonElevation = 0,
    }, //Wishiwashi,
[SPECIES_MAREANIE] = 
    {  
      //FRONT_PIC(Mareanie),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mareanie),
      BACK_COORD(0x88,0),
      //PALETTES(Mareanie),
      PIC_DATA_ICON_INDEX(Mareanie,0),
      //ICON(Mareanie, 0),
      .enemyMonElevation = 0,
    }, //Mareanie,
[SPECIES_TOXAPEX] = 
    {  
      //FRONT_PIC(Toxapex),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toxapex),
      BACK_COORD(0x88,0),
      //PALETTES(Toxapex),
      PIC_DATA_ICON_INDEX(Toxapex,0),
      //ICON(Toxapex, 0),
      .enemyMonElevation = 0,
    }, //Toxapex,
[SPECIES_MUDBRAY] = 
    {  
      //FRONT_PIC(Mudbray),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mudbray),
      BACK_COORD(0x88,0),
      //PALETTES(Mudbray),
      PIC_DATA_ICON_INDEX(Mudbray,0),
      //ICON(Mudbray, 0),
      .enemyMonElevation = 0,
    }, //Mudbray,
[SPECIES_MUDSDALE] = 
    {  
      //FRONT_PIC(Mudsdale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mudsdale),
      BACK_COORD(0x88,0),
      //PALETTES(Mudsdale),
      PIC_DATA_ICON_INDEX(Mudsdale,0),
      //ICON(Mudsdale, 0),
      .enemyMonElevation = 0,
    }, //Mudsdale,
[SPECIES_DEWPIDER] = 
    {  
      //FRONT_PIC(Dewpider),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dewpider),
      BACK_COORD(0x88,0),
      //PALETTES(Dewpider),
      PIC_DATA_ICON_INDEX(Dewpider,0),
      //ICON(Dewpider, 0),
      .enemyMonElevation = 0,
    }, //Dewpider,
[SPECIES_ARAQUANID] = 
    {  
      //FRONT_PIC(Araquanid),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Araquanid),
      BACK_COORD(0x88,0),
      //PALETTES(Araquanid),
      PIC_DATA_ICON_INDEX(Araquanid,0),
      //ICON(Araquanid, 0),
      .enemyMonElevation = 0,
    }, //Araquanid,
[SPECIES_FOMANTIS] = 
    {  
      //FRONT_PIC(Fomantis),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fomantis),
      BACK_COORD(0x88,0),
      //PALETTES(Fomantis),
      PIC_DATA_ICON_INDEX(Fomantis,0),
      //ICON(Fomantis, 0),
      .enemyMonElevation = 0,
    }, //Fomantis,
[SPECIES_LURANTIS] = 
    {  
      //FRONT_PIC(Lurantis),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lurantis),
      BACK_COORD(0x88,0),
      //PALETTES(Lurantis),
      PIC_DATA_ICON_INDEX(Lurantis,0),
      //ICON(Lurantis, 0),
      .enemyMonElevation = 0,
    }, //Lurantis,
[SPECIES_MORELULL] = 
    {  
      //FRONT_PIC(Morelull),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Morelull),
      BACK_COORD(0x88,0),
      //PALETTES(Morelull),
      PIC_DATA_ICON_INDEX(Morelull,0),
      //ICON(Morelull, 0),
      .enemyMonElevation = 0,
    }, //Morelull,
[SPECIES_SHIINOTIC] = 
    {  
      //FRONT_PIC(Shiinotic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shiinotic),
      BACK_COORD(0x88,0),
      //PALETTES(Shiinotic),
      PIC_DATA_ICON_INDEX(Shiinotic,0),
      //ICON(Shiinotic, 0),
      .enemyMonElevation = 0,
    }, //Shiinotic,
[SPECIES_SALANDIT] = 
    {  
      //FRONT_PIC(Salandit),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Salandit),
      BACK_COORD(0x88,0),
      //PALETTES(Salandit),
      PIC_DATA_ICON_INDEX(Salandit,0),
      //ICON(Salandit, 0),
      .enemyMonElevation = 0,
    }, //Salandit,
[SPECIES_SALAZZLE] = 
    {  
      //FRONT_PIC(Salazzle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Salazzle),
      BACK_COORD(0x88,0),
      //PALETTES(Salazzle),
      PIC_DATA_ICON_INDEX(Salazzle,0),
      //ICON(Salazzle, 0),
      .enemyMonElevation = 0,
    }, //Salazzle,
[SPECIES_STUFFUL] = 
    {  
      //FRONT_PIC(Stufful),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stufful),
      BACK_COORD(0x88,0),
      //PALETTES(Stufful),
      PIC_DATA_ICON_INDEX(Stufful,0),
      //ICON(Stufful, 0),
      .enemyMonElevation = 0,
    }, //Stufful,
[SPECIES_BEWEAR] = 
    {  
      //FRONT_PIC(Bewear),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bewear),
      BACK_COORD(0x88,0),
      //PALETTES(Bewear),
      PIC_DATA_ICON_INDEX(Bewear,0),
      //ICON(Bewear, 0),
      .enemyMonElevation = 0,
    }, //Bewear,
[SPECIES_BOUNSWEET] = 
    {  
      //FRONT_PIC(Bounsweet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bounsweet),
      BACK_COORD(0x88,0),
      //PALETTES(Bounsweet),
      PIC_DATA_ICON_INDEX(Bounsweet,0),
      //ICON(Bounsweet, 0),
      .enemyMonElevation = 0,
    }, //Bounsweet,
[SPECIES_STEENEE] = 
    {  
      //FRONT_PIC(Steenee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Steenee),
      BACK_COORD(0x88,0),
      //PALETTES(Steenee),
      PIC_DATA_ICON_INDEX(Steenee,0),
      //ICON(Steenee, 0),
      .enemyMonElevation = 0,
    }, //Steenee,
[SPECIES_TSAREENA] = 
    {  
      //FRONT_PIC(Tsareena),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tsareena),
      BACK_COORD(0x88,0),
      //PALETTES(Tsareena),
      PIC_DATA_ICON_INDEX(Tsareena,0),
      //ICON(Tsareena, 0),
      .enemyMonElevation = 0,
    }, //Tsareena,
[SPECIES_COMFEY] = 
    {  
      //FRONT_PIC(Comfey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Comfey),
      BACK_COORD(0x88,0),
      //PALETTES(Comfey),
      PIC_DATA_ICON_INDEX(Comfey,0),
      //ICON(Comfey, 0),
      .enemyMonElevation = 0,
    }, //Comfey,
[SPECIES_ORANGURU] = 
    {  
      //FRONT_PIC(Oranguru),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Oranguru),
      BACK_COORD(0x88,0),
      //PALETTES(Oranguru),
      PIC_DATA_ICON_INDEX(Oranguru,0),
      //ICON(Oranguru, 0),
      .enemyMonElevation = 0,
    }, //Oranguru,
[SPECIES_PASSIMIAN] = 
    {  
      //FRONT_PIC(Passimian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Passimian),
      BACK_COORD(0x88,0),
      //PALETTES(Passimian),
      PIC_DATA_ICON_INDEX(Passimian,0),
      //ICON(Passimian, 0),
      .enemyMonElevation = 0,
    }, //Passimian,
[SPECIES_WIMPOD] = 
    {  
      //FRONT_PIC(Wimpod),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wimpod),
      BACK_COORD(0x88,0),
      //PALETTES(Wimpod),
      PIC_DATA_ICON_INDEX(Wimpod,0),
      //ICON(Wimpod, 0),
      .enemyMonElevation = 0,
    }, //Wimpod,
[SPECIES_GOLISOPOD] = 
    {  
      //FRONT_PIC(Golisopod),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Golisopod),
      BACK_COORD(0x88,0),
      //PALETTES(Golisopod),
      PIC_DATA_ICON_INDEX(Golisopod,0),
      //ICON(Golisopod, 0),
      .enemyMonElevation = 0,
    }, //Golisopod,
[SPECIES_SANDYGAST] = 
    {  
      //FRONT_PIC(Sandygast),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sandygast),
      BACK_COORD(0x88,0),
      //PALETTES(Sandygast),
      PIC_DATA_ICON_INDEX(Sandygast,0),
      //ICON(Sandygast, 0),
      .enemyMonElevation = 0,
    }, //Sandygast,
[SPECIES_PALOSSAND] = 
    {  
      //FRONT_PIC(Palossand),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Palossand),
      BACK_COORD(0x88,0),
      //PALETTES(Palossand),
      PIC_DATA_ICON_INDEX(Palossand,0),
      //ICON(Palossand, 0),
      .enemyMonElevation = 0,
    }, //Palossand,
[SPECIES_PYUKUMUKU] = 
    {  
      //FRONT_PIC(Pyukumuku),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pyukumuku),
      BACK_COORD(0x88,0),
      //PALETTES(Pyukumuku),
      PIC_DATA_ICON_INDEX(Pyukumuku,0),
      //ICON(Pyukumuku, 0),
      .enemyMonElevation = 0,
    }, //Pyukumuku,
[SPECIES_TYPE_NULL] = 
    {  
      //FRONT_PIC(TypeNull),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TypeNull),
      BACK_COORD(0x88,0),
      //PALETTES(TypeNull),
      PIC_DATA_ICON_INDEX(TypeNull,0),
      //ICON(TypeNull, 0),
      .enemyMonElevation = 0,
    }, //TypeNull,
[SPECIES_SILVALLY] = 
    {  
      //FRONT_PIC(Silvally),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Silvally),
      BACK_COORD(0x88,0),
      //PALETTES(Silvally),
      PIC_DATA_ICON_INDEX(Silvally,0),
      //ICON(Silvally, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_MINIOR] = 
    {  
      //FRONT_PIC(Minior),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Minior),
      BACK_COORD(0x88,0),
      //PALETTES(Minior),
      PIC_DATA_ICON_INDEX(Minior,0),
      //ICON(Minior, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_KOMALA] = 
    {  
      //FRONT_PIC(Komala),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Komala),
      BACK_COORD(0x88,0),
      //PALETTES(Komala),
      PIC_DATA_ICON_INDEX(Komala,0),
      //ICON(Komala, 0),
      .enemyMonElevation = 0,
    }, //Komala,
[SPECIES_TURTONATOR] = 
    {  
      //FRONT_PIC(Turtonator),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Turtonator),
      BACK_COORD(0x88,0),
      //PALETTES(Turtonator),
      PIC_DATA_ICON_INDEX(Turtonator,0),
      //ICON(Turtonator, 0),
      .enemyMonElevation = 0,
    }, //Turtonator,
[SPECIES_TOGEDEMARU] = 
    {  
      //FRONT_PIC(Togedemaru),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Togedemaru),
      BACK_COORD(0x88,0),
      //PALETTES(Togedemaru),
      PIC_DATA_ICON_INDEX(Togedemaru,0),
      //ICON(Togedemaru, 0),
      .enemyMonElevation = 0,
    }, //Togedemaru,
[SPECIES_MIMIKYU] = 
    {  
      //FRONT_PIC(Mimikyu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mimikyu),
      BACK_COORD(0x88,0),
      //PALETTES(Mimikyu),
      PIC_DATA_ICON_INDEX(Mimikyu,0),
      //ICON(Mimikyu, 0),
      .enemyMonElevation = 0,
    }, //Mimikyu,
[SPECIES_BRUXISH] = 
    {  
      //FRONT_PIC(Bruxish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bruxish),
      BACK_COORD(0x88,0),
      //PALETTES(Bruxish),
      PIC_DATA_ICON_INDEX(Bruxish,0),
      //ICON(Bruxish, 0),
      .enemyMonElevation = 0,
    }, //Bruxish,
[SPECIES_DRAMPA] = 
    {  
      //FRONT_PIC(Drampa),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drampa),
      BACK_COORD(0x88,0),
      //PALETTES(Drampa),
      PIC_DATA_ICON_INDEX(Drampa,0),
      //ICON(Drampa, 0),
      .enemyMonElevation = 0,
    }, //Drampa,
[SPECIES_DHELMISE] = 
    {  
      //FRONT_PIC(Dhelmise),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dhelmise),
      BACK_COORD(0x88,0),
      //PALETTES(Dhelmise),
      PIC_DATA_ICON_INDEX(Dhelmise,0),
      //ICON(Dhelmise, 0),
      .enemyMonElevation = 0,
    }, //Dhelmise,
[SPECIES_JANGMO_O] = 
    {  
      //FRONT_PIC(JangmoO),
      FRONT_COORD(0x88,0),
      //BACK_PIC(JangmoO),
      BACK_COORD(0x88,0),
      //PALETTES(JangmoO),
      PIC_DATA_ICON_INDEX(JangmoO,0),
      //ICON(JangmoO, 0),
      .enemyMonElevation = 0,
    }, //Jangmoo,
[SPECIES_HAKAMO_O] = 
    {  
      //FRONT_PIC(HakamoO),
      FRONT_COORD(0x88,0),
      //BACK_PIC(HakamoO),
      BACK_COORD(0x88,0),
      //PALETTES(HakamoO),
      PIC_DATA_ICON_INDEX(HakamoO,0),
      //ICON(HakamoO, 0),
      .enemyMonElevation = 0,
    }, //Hakamoo,
[SPECIES_KOMMO_O] = 
    {  
      //FRONT_PIC(KommoO),
      FRONT_COORD(0x88,0),
      //BACK_PIC(KommoO),
      BACK_COORD(0x88,0),
      //PALETTES(KommoO),
      PIC_DATA_ICON_INDEX(KommoO,0),
      //ICON(KommoO, 0),
      .enemyMonElevation = 0,
    }, //Kommoo,
[SPECIES_TAPU_KOKO] = 
    {  
      //FRONT_PIC(TapuKoko),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TapuKoko),
      BACK_COORD(0x88,0),
      //PALETTES(TapuKoko),
      PIC_DATA_ICON_INDEX(TapuKoko,0),
      //ICON(TapuKoko, 0),
      .enemyMonElevation = 0,
    }, //TapuKoko,
[SPECIES_TAPU_LELE] = 
    {  
      //FRONT_PIC(TapuLele),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TapuLele),
      BACK_COORD(0x88,0),
      //PALETTES(TapuLele),
      PIC_DATA_ICON_INDEX(TapuLele,0),
      //ICON(TapuLele, 0),
      .enemyMonElevation = 0,
    }, //TapuLele,
[SPECIES_TAPU_BULU] = 
    {  
      //FRONT_PIC(TapuBulu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TapuBulu),
      BACK_COORD(0x88,0),
      //PALETTES(TapuBulu),
      PIC_DATA_ICON_INDEX(TapuBulu,0),
      //ICON(TapuBulu, 0),
      .enemyMonElevation = 0,
    }, //TapuBulu,
[SPECIES_TAPU_FINI] = 
    {  
      //FRONT_PIC(TapuFini),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TapuFini),
      BACK_COORD(0x88,0),
      //PALETTES(TapuFini),
      PIC_DATA_ICON_INDEX(TapuFini,0),
      //ICON(TapuFini, 0),
      .enemyMonElevation = 0,
    }, //TapuFini,
[SPECIES_COSMOG] = 
    {  
      //FRONT_PIC(Cosmog),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cosmog),
      BACK_COORD(0x88,0),
      //PALETTES(Cosmog),
      PIC_DATA_ICON_INDEX(Cosmog,0),
      //ICON(Cosmog, 0),
      .enemyMonElevation = 0,
    }, //Cosmog,
[SPECIES_COSMOEM] = 
    {  
      //FRONT_PIC(Cosmoem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cosmoem),
      BACK_COORD(0x88,0),
      //PALETTES(Cosmoem),
      PIC_DATA_ICON_INDEX(Cosmoem,0),
      //ICON(Cosmoem, 0),
      .enemyMonElevation = 0,
    }, //Cosmoem,
[SPECIES_SOLGALEO] = 
    {  
      //FRONT_PIC(Solgaleo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Solgaleo),
      BACK_COORD(0x88,0),
      //PALETTES(Solgaleo),
      PIC_DATA_ICON_INDEX(Solgaleo,0),
      //ICON(Solgaleo, 0),
      .enemyMonElevation = 0,
    }, //Solgaleo,
[SPECIES_LUNALA] = 
    {  
      //FRONT_PIC(Lunala),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lunala),
      BACK_COORD(0x88,0),
      //PALETTES(Lunala),
      PIC_DATA_ICON_INDEX(Lunala,0),
      //ICON(Lunala, 0),
      .enemyMonElevation = 0,
    }, //Lunala,
[SPECIES_NIHILEGO] = 
    {  
      //FRONT_PIC(Nihilego),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nihilego),
      BACK_COORD(0x88,0),
      //PALETTES(Nihilego),
      PIC_DATA_ICON_INDEX(Nihilego,0),
      //ICON(Nihilego, 0),
      .enemyMonElevation = 0,
    }, //Nihilego,
[SPECIES_BUZZWOLE] = 
    {  
      //FRONT_PIC(Buzzwole),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Buzzwole),
      BACK_COORD(0x88,0),
      //PALETTES(Buzzwole),
      PIC_DATA_ICON_INDEX(Buzzwole,0),
      //ICON(Buzzwole, 0),
      .enemyMonElevation = 0,
    }, //Buzzwole,
[SPECIES_PHEROMOSA] = 
    {  
      //FRONT_PIC(Pheromosa),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pheromosa),
      BACK_COORD(0x88,0),
      //PALETTES(Pheromosa),
      PIC_DATA_ICON_INDEX(Pheromosa,0),
      //ICON(Pheromosa, 0),
      .enemyMonElevation = 0,
    }, //Pheromosa,
[SPECIES_XURKITREE] = 
    {  
      //FRONT_PIC(Xurkitree),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Xurkitree),
      BACK_COORD(0x88,0),
      //PALETTES(Xurkitree),
      PIC_DATA_ICON_INDEX(Xurkitree,0),
      //ICON(Xurkitree, 0),
      .enemyMonElevation = 0,
    }, //Xurkitree,
[SPECIES_CELESTEELA] = 
    {  
      //FRONT_PIC(Celesteela),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Celesteela),
      BACK_COORD(0x88,0),
      //PALETTES(Celesteela),
      PIC_DATA_ICON_INDEX(Celesteela,0),
      //ICON(Celesteela, 0),
      .enemyMonElevation = 0,
    }, //Celesteela,
[SPECIES_KARTANA] = 
    {  
      //FRONT_PIC(Kartana),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kartana),
      BACK_COORD(0x88,0),
      //PALETTES(Kartana),
      PIC_DATA_ICON_INDEX(Kartana,0),
      //ICON(Kartana, 0),
      .enemyMonElevation = 0,
    }, //Kartana,
[SPECIES_GUZZLORD] = 
    {  
      //FRONT_PIC(Guzzlord),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Guzzlord),
      BACK_COORD(0x88,0),
      //PALETTES(Guzzlord),
      PIC_DATA_ICON_INDEX(Guzzlord,0),
      //ICON(Guzzlord, 0),
      .enemyMonElevation = 0,
    }, //Guzzlord,
[SPECIES_NECROZMA] = 
    {  
      //FRONT_PIC(Necrozma),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Necrozma),
      BACK_COORD(0x88,0),
      //PALETTES(Necrozma),
      PIC_DATA_ICON_INDEX(Necrozma,0),
      //ICON(Necrozma, 0),
      .enemyMonElevation = 0,
    }, //Necrozma,
[SPECIES_MAGEARNA] = 
    {  
      //FRONT_PIC(Magearna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Magearna),
      BACK_COORD(0x88,0),
      //PALETTES(Magearna),
      PIC_DATA_ICON_INDEX(Magearna,0),
      //ICON(Magearna, 0),
      .enemyMonElevation = 0,
    }, //Magearna,
[SPECIES_MARSHADOW] = 
    {  
      //FRONT_PIC(Marshadow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Marshadow),
      BACK_COORD(0x88,0),
      //PALETTES(Marshadow),
      PIC_DATA_ICON_INDEX(Marshadow,0),
      //ICON(Marshadow, 0),
      .enemyMonElevation = 0,
    }, //Marshadow,
[SPECIES_POIPOLE] = 
    {  
      //FRONT_PIC(Poipole),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Poipole),
      BACK_COORD(0x88,0),
      //PALETTES(Poipole),
      PIC_DATA_ICON_INDEX(Poipole,0),
      //ICON(Poipole, 0),
      .enemyMonElevation = 0,
    }, //Poipole,
[SPECIES_NAGANADEL] = 
    {  
      //FRONT_PIC(Naganadel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Naganadel),
      BACK_COORD(0x88,0),
      //PALETTES(Naganadel),
      PIC_DATA_ICON_INDEX(Naganadel,0),
      //ICON(Naganadel, 0),
      .enemyMonElevation = 0,
    }, //Naganadel,
[SPECIES_STAKATAKA] = 
    {  
      //FRONT_PIC(Stakataka),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stakataka),
      BACK_COORD(0x88,0),
      //PALETTES(Stakataka),
      PIC_DATA_ICON_INDEX(Stakataka,0),
      //ICON(Stakataka, 0),
      .enemyMonElevation = 0,
    }, //Stakataka,
[SPECIES_BLACEPHALON] = 
    {  
      //FRONT_PIC(Blacephalon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blacephalon),
      BACK_COORD(0x88,0),
      //PALETTES(Blacephalon),
      PIC_DATA_ICON_INDEX(Blacephalon,0),
      //ICON(Blacephalon, 0),
      .enemyMonElevation = 0,
    }, //Blacephalon,
[SPECIES_ZERAORA] = 
    {  
      //FRONT_PIC(Zeraora),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zeraora),
      BACK_COORD(0x88,0),
      //PALETTES(Zeraora),
      PIC_DATA_ICON_INDEX(Zeraora,0),
      //ICON(Zeraora, 0),
      .enemyMonElevation = 0,
    }, //Zeraora,
[SPECIES_MELTAN] = 
    {  
      //FRONT_PIC(Meltan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Meltan),
      BACK_COORD(0x88,0),
      //PALETTES(Meltan),
      PIC_DATA_ICON_INDEX(Meltan,0),
      //ICON(Meltan, 0),
      .enemyMonElevation = 0,
    }, //Meltan,
[SPECIES_MELMETAL] = 
    {  
      //FRONT_PIC(Melmetal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Melmetal),
      BACK_COORD(0x88,0),
      //PALETTES(Melmetal),
      PIC_DATA_ICON_INDEX(Melmetal,0),
      //ICON(Melmetal, 0),
      .enemyMonElevation = 0,
    }, //Melmetal,
[SPECIES_GROOKEY] = 
    {  
      //FRONT_PIC(Grookey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grookey),
      BACK_COORD(0x88,0),
      //PALETTES(Grookey),
      PIC_DATA_ICON_INDEX(Grookey,0),
      //ICON(Grookey, 0),
      .enemyMonElevation = 0,
    }, //Grookey,
[SPECIES_THWACKEY] = 
    {  
      //FRONT_PIC(Thwackey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Thwackey),
      BACK_COORD(0x88,0),
      //PALETTES(Thwackey),
      PIC_DATA_ICON_INDEX(Thwackey,0),
      //ICON(Thwackey, 0),
      .enemyMonElevation = 0,
    }, //Thwackey,
[SPECIES_RILLABOOM] = 
    {  
      //FRONT_PIC(Rillaboom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rillaboom),
      BACK_COORD(0x88,0),
      //PALETTES(Rillaboom),
      PIC_DATA_ICON_INDEX(Rillaboom,0),
      //ICON(Rillaboom, 0),
      .enemyMonElevation = 0,
    }, //Rillaboom,
[SPECIES_SCORBUNNY] = 
    {  
      //FRONT_PIC(Scorbunny),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scorbunny),
      BACK_COORD(0x88,0),
      //PALETTES(Scorbunny),
      PIC_DATA_ICON_INDEX(Scorbunny,0),
      //ICON(Scorbunny, 0),
      .enemyMonElevation = 0,
    }, //Scorbunny,
[SPECIES_RABOOT] = 
    {  
      //FRONT_PIC(Raboot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Raboot),
      BACK_COORD(0x88,0),
      //PALETTES(Raboot),
      PIC_DATA_ICON_INDEX(Raboot,0),
      //ICON(Raboot, 0),
      .enemyMonElevation = 0,
    }, //Raboot,
[SPECIES_CINDERACE] = 
    {  
      //FRONT_PIC(Cinderace),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cinderace),
      BACK_COORD(0x88,0),
      //PALETTES(Cinderace),
      PIC_DATA_ICON_INDEX(Cinderace,0),
      //ICON(Cinderace, 0),
      .enemyMonElevation = 0,
    }, //Cinderace,
[SPECIES_SOBBLE] = 
    {  
      //FRONT_PIC(Sobble),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sobble),
      BACK_COORD(0x88,0),
      //PALETTES(Sobble),
      PIC_DATA_ICON_INDEX(Sobble,0),
      //ICON(Sobble, 0),
      .enemyMonElevation = 0,
    }, //Sobble,
[SPECIES_DRIZZILE] = 
    {  
      //FRONT_PIC(Drizzile),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drizzile),
      BACK_COORD(0x88,0),
      //PALETTES(Drizzile),
      PIC_DATA_ICON_INDEX(Drizzile,0),
      //ICON(Drizzile, 0),
      .enemyMonElevation = 0,
    }, //Drizzile,
[SPECIES_INTELEON] = 
    {  
      //FRONT_PIC(Inteleon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Inteleon),
      BACK_COORD(0x88,0),
      //PALETTES(Inteleon),
      PIC_DATA_ICON_INDEX(Inteleon,0),
      //ICON(Inteleon, 0),
      .enemyMonElevation = 0,
    }, //Inteleon,
[SPECIES_SKWOVET] = 
    {  
      //FRONT_PIC(Skwovet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skwovet),
      BACK_COORD(0x88,0),
      //PALETTES(Skwovet),
      PIC_DATA_ICON_INDEX(Skwovet,0),
      //ICON(Skwovet, 0),
      .enemyMonElevation = 0,
    }, //Skwovet,
[SPECIES_GREEDENT] = 
    {  
      //FRONT_PIC(Greedent),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Greedent),
      BACK_COORD(0x88,0),
      //PALETTES(Greedent),
      PIC_DATA_ICON_INDEX(Greedent,0),
      //ICON(Greedent, 0),
      .enemyMonElevation = 0,
    }, //Greedent,
[SPECIES_ROOKIDEE] = 
    {  
      //FRONT_PIC(Rookidee),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rookidee),
      BACK_COORD(0x88,0),
      //PALETTES(Rookidee),
      PIC_DATA_ICON_INDEX(Rookidee,0),
      //ICON(Rookidee, 0),
      .enemyMonElevation = 0,
    }, //Rookidee,
[SPECIES_CORVISQUIRE] = 
    {  
      //FRONT_PIC(Corvisquire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Corvisquire),
      BACK_COORD(0x88,0),
      //PALETTES(Corvisquire),
      PIC_DATA_ICON_INDEX(Corvisquire,0),
      //ICON(Corvisquire, 0),
      .enemyMonElevation = 0,
    }, //Corvisquire,
[SPECIES_CORVIKNIGHT] = 
    {  
      //FRONT_PIC(Corviknight),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Corviknight),
      BACK_COORD(0x88,0),
      //PALETTES(Corviknight),
      PIC_DATA_ICON_INDEX(Corviknight,0),
      //ICON(Corviknight, 0),
      .enemyMonElevation = 0,
    }, //Corviknight,
[SPECIES_BLIPBUG] = 
    {  
      //FRONT_PIC(Blipbug),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Blipbug),
      BACK_COORD(0x88,0),
      //PALETTES(Blipbug),
      PIC_DATA_ICON_INDEX(Blipbug,0),
      //ICON(Blipbug, 0),
      .enemyMonElevation = 0,
    }, //Blipbug,
[SPECIES_DOTTLER] = 
    {  
      //FRONT_PIC(Dottler),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dottler),
      BACK_COORD(0x88,0),
      //PALETTES(Dottler),
      PIC_DATA_ICON_INDEX(Dottler,0),
      //ICON(Dottler, 0),
      .enemyMonElevation = 0,
    }, //Dottler,
[SPECIES_ORBEETLE] = 
    {  
      //FRONT_PIC(Orbeetle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Orbeetle),
      BACK_COORD(0x88,0),
      //PALETTES(Orbeetle),
      PIC_DATA_ICON_INDEX(Orbeetle,0),
      //ICON(Orbeetle, 0),
      .enemyMonElevation = 0,
    }, //Orbeetle,
[SPECIES_NICKIT] = 
    {  
      //FRONT_PIC(Nickit),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nickit),
      BACK_COORD(0x88,0),
      //PALETTES(Nickit),
      PIC_DATA_ICON_INDEX(Nickit,0),
      //ICON(Nickit, 0),
      .enemyMonElevation = 0,
    }, //Nickit,
[SPECIES_THIEVUL] = 
    {  
      //FRONT_PIC(Thievul),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Thievul),
      BACK_COORD(0x88,0),
      //PALETTES(Thievul),
      PIC_DATA_ICON_INDEX(Thievul,0),
      //ICON(Thievul, 0),
      .enemyMonElevation = 0,
    }, //Thievul,
[SPECIES_GOSSIFLEUR] = 
    {  
      //FRONT_PIC(Gossifleur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gossifleur),
      BACK_COORD(0x88,0),
      //PALETTES(Gossifleur),
      PIC_DATA_ICON_INDEX(Gossifleur,0),
      //ICON(Gossifleur, 0),
      .enemyMonElevation = 0,
    }, //Gossifleur,
[SPECIES_ELDEGOSS] = 
    {  
      //FRONT_PIC(Eldegoss),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Eldegoss),
      BACK_COORD(0x88,0),
      //PALETTES(Eldegoss),
      PIC_DATA_ICON_INDEX(Eldegoss,0),
      //ICON(Eldegoss, 0),
      .enemyMonElevation = 0,
    }, //Eldegoss,
[SPECIES_WOOLOO] = 
    {  
      //FRONT_PIC(Wooloo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wooloo),
      BACK_COORD(0x88,0),
      //PALETTES(Wooloo),
      PIC_DATA_ICON_INDEX(Wooloo,0),
      //ICON(Wooloo, 0),
      .enemyMonElevation = 0,
    }, //Wooloo,
[SPECIES_DUBWOOL] = 
    {  
      //FRONT_PIC(Dubwool),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dubwool),
      BACK_COORD(0x88,0),
      //PALETTES(Dubwool),
      PIC_DATA_ICON_INDEX(Dubwool,0),
      //ICON(Dubwool, 0),
      .enemyMonElevation = 0,
    }, //Dubwool,
[SPECIES_CHEWTLE] = 
    {  
      //FRONT_PIC(Chewtle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Chewtle),
      BACK_COORD(0x88,0),
      //PALETTES(Chewtle),
      PIC_DATA_ICON_INDEX(Chewtle,0),
      //ICON(Chewtle, 0),
      .enemyMonElevation = 0,
    }, //Chewtle,
[SPECIES_DREDNAW] = 
    {  
      //FRONT_PIC(Drednaw),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drednaw),
      BACK_COORD(0x88,0),
      //PALETTES(Drednaw),
      PIC_DATA_ICON_INDEX(Drednaw,0),
      //ICON(Drednaw, 0),
      .enemyMonElevation = 0,
    }, //Drednaw,
[SPECIES_YAMPER] = 
    {  
      //FRONT_PIC(Yamper),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Yamper),
      BACK_COORD(0x88,0),
      //PALETTES(Yamper),
      PIC_DATA_ICON_INDEX(Yamper,0),
      //ICON(Yamper, 0),
      .enemyMonElevation = 0,
    }, //Yamper,
[SPECIES_BOLTUND] = 
    {  
      //FRONT_PIC(Boltund),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Boltund),
      BACK_COORD(0x88,0),
      //PALETTES(Boltund),
      PIC_DATA_ICON_INDEX(Boltund,0),
      //ICON(Boltund, 0),
      .enemyMonElevation = 0,
    }, //Boltund,
[SPECIES_ROLYCOLY] = 
    {  
      //FRONT_PIC(Rolycoly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rolycoly),
      BACK_COORD(0x88,0),
      //PALETTES(Rolycoly),
      PIC_DATA_ICON_INDEX(Rolycoly,0),
      //ICON(Rolycoly, 0),
      .enemyMonElevation = 0,
    }, //Rolycoly,
[SPECIES_CARKOL] = 
    {  
      //FRONT_PIC(Carkol),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Carkol),
      BACK_COORD(0x88,0),
      //PALETTES(Carkol),
      PIC_DATA_ICON_INDEX(Carkol,0),
      //ICON(Carkol, 0),
      .enemyMonElevation = 0,
    }, //Carkol,
[SPECIES_COALOSSAL] = 
    {  
      //FRONT_PIC(Coalossal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Coalossal),
      BACK_COORD(0x88,0),
      //PALETTES(Coalossal),
      PIC_DATA_ICON_INDEX(Coalossal,0),
      //ICON(Coalossal, 0),
      .enemyMonElevation = 0,
    }, //Coalossal,
[SPECIES_APPLIN] = 
    {  
      //FRONT_PIC(Applin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Applin),
      BACK_COORD(0x88,0),
      //PALETTES(Applin),
      PIC_DATA_ICON_INDEX(Applin,0),
      //ICON(Applin, 0),
      .enemyMonElevation = 0,
    }, //Applin,
[SPECIES_FLAPPLE] = 
    {  
      //FRONT_PIC(Flapple),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flapple),
      BACK_COORD(0x88,0),
      //PALETTES(Flapple),
      PIC_DATA_ICON_INDEX(Flapple,0),
      //ICON(Flapple, 0),
      .enemyMonElevation = 0,
    }, //Flapple,
[SPECIES_APPLETUN] = 
    {  
      //FRONT_PIC(Appletun),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Appletun),
      BACK_COORD(0x88,0),
      //PALETTES(Appletun),
      PIC_DATA_ICON_INDEX(Appletun,0),
      //ICON(Appletun, 0),
      .enemyMonElevation = 0,
    }, //Appletun,
[SPECIES_SILICOBRA] = 
    {  
      //FRONT_PIC(Silicobra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Silicobra),
      BACK_COORD(0x88,0),
      //PALETTES(Silicobra),
      PIC_DATA_ICON_INDEX(Silicobra,0),
      //ICON(Silicobra, 0),
      .enemyMonElevation = 0,
    }, //Silicobra,
[SPECIES_SANDACONDA] = 
    {  
      //FRONT_PIC(Sandaconda),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sandaconda),
      BACK_COORD(0x88,0),
      //PALETTES(Sandaconda),
      PIC_DATA_ICON_INDEX(Sandaconda,0),
      //ICON(Sandaconda, 0),
      .enemyMonElevation = 0,
    }, //Sandaconda,
[SPECIES_CRAMORANT] = 
    {  
      //FRONT_PIC(Cramorant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cramorant),
      BACK_COORD(0x88,0),
      //PALETTES(Cramorant),
      PIC_DATA_ICON_INDEX(Cramorant,0),
      //ICON(Cramorant, 0),
      .enemyMonElevation = 0,
    }, //Cramorant,
[SPECIES_ARROKUDA] = 
    {  
      //FRONT_PIC(Arrokuda),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arrokuda),
      BACK_COORD(0x88,0),
      //PALETTES(Arrokuda),
      PIC_DATA_ICON_INDEX(Arrokuda,0),
      //ICON(Arrokuda, 0),
      .enemyMonElevation = 0,
    }, //Arrokuda,
[SPECIES_BARRASKEWDA] = 
    {  
      //FRONT_PIC(Barraskewda),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Barraskewda),
      BACK_COORD(0x88,0),
      //PALETTES(Barraskewda),
      PIC_DATA_ICON_INDEX(Barraskewda,0),
      //ICON(Barraskewda, 0),
      .enemyMonElevation = 0,
    }, //Barraskewda,
[SPECIES_TOXEL] = 
    {  
      //FRONT_PIC(Toxel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toxel),
      BACK_COORD(0x88,0),
      //PALETTES(Toxel),
      PIC_DATA_ICON_INDEX(Toxel,0),
      //ICON(Toxel, 0),
      .enemyMonElevation = 0,
    }, //Toxel,
[SPECIES_TOXTRICITY] = 
    {  
      //FRONT_PIC(Toxtricity),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toxtricity),
      BACK_COORD(0x88,0),
      //PALETTES(Toxtricity),
      PIC_DATA_ICON_INDEX(Toxtricity,0),
      //ICON(Toxtricity, 0),
      .enemyMonElevation = 0,
    }, //Toxtricity,
[SPECIES_SIZZLIPEDE] = 
    {  
      //FRONT_PIC(Sizzlipede),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sizzlipede),
      BACK_COORD(0x88,0),
      //PALETTES(Sizzlipede),
      PIC_DATA_ICON_INDEX(Sizzlipede,0),
      //ICON(Sizzlipede, 0),
      .enemyMonElevation = 0,
    }, //Sizzlipede,
[SPECIES_CENTISKORCH] = 
    {  
      //FRONT_PIC(Centiskorch),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Centiskorch),
      BACK_COORD(0x88,0),
      //PALETTES(Centiskorch),
      PIC_DATA_ICON_INDEX(Centiskorch,0),
      //ICON(Centiskorch, 0),
      .enemyMonElevation = 0,
    }, //Centiskorch,
[SPECIES_CLOBBOPUS] = 
    {  
      //FRONT_PIC(Clobbopus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clobbopus),
      BACK_COORD(0x88,0),
      //PALETTES(Clobbopus),
      PIC_DATA_ICON_INDEX(Clobbopus,0),
      //ICON(Clobbopus, 0),
      .enemyMonElevation = 0,
    }, //Clobbopus,
[SPECIES_GRAPPLOCT] = 
    {  
      //FRONT_PIC(Grapploct),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grapploct),
      BACK_COORD(0x88,0),
      //PALETTES(Grapploct),
      PIC_DATA_ICON_INDEX(Grapploct,0),
      //ICON(Grapploct, 0),
      .enemyMonElevation = 0,
    }, //Grapploct,
[SPECIES_SINISTEA] = 
    {  
      //FRONT_PIC(Sinistea),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sinistea),
      BACK_COORD(0x88,0),
      //PALETTES(Sinistea),
      PIC_DATA_ICON_INDEX(Sinistea,0),
      //ICON(Sinistea, 0),
      .enemyMonElevation = 0,
    }, //Sinistea,
[SPECIES_POLTEAGEIST] = 
    {  
      //FRONT_PIC(Polteageist),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Polteageist),
      BACK_COORD(0x88,0),
      //PALETTES(Polteageist),
      PIC_DATA_ICON_INDEX(Polteageist,0),
      //ICON(Polteageist, 0),
      .enemyMonElevation = 0,
    }, //Polteageist,
[SPECIES_HATENNA] = 
    {  
      //FRONT_PIC(Hatenna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hatenna),
      BACK_COORD(0x88,0),
      //PALETTES(Hatenna),
      PIC_DATA_ICON_INDEX(Hatenna,0),
      //ICON(Hatenna, 0),
      .enemyMonElevation = 0,
    }, //Hatenna,
[SPECIES_HATTREM] = 
    {  
      //FRONT_PIC(Hattrem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hattrem),
      BACK_COORD(0x88,0),
      //PALETTES(Hattrem),
      PIC_DATA_ICON_INDEX(Hattrem,0),
      //ICON(Hattrem, 0),
      .enemyMonElevation = 0,
    }, //Hattrem,
[SPECIES_HATTERENE] = 
    {  
      //FRONT_PIC(Hatterene),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hatterene),
      BACK_COORD(0x88,0),
      //PALETTES(Hatterene),
      PIC_DATA_ICON_INDEX(Hatterene,0),
      //ICON(Hatterene, 0),
      .enemyMonElevation = 0,
    }, //Hatterene,
[SPECIES_IMPIDIMP] = 
    {  
      //FRONT_PIC(Impidimp),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Impidimp),
      BACK_COORD(0x88,0),
      //PALETTES(Impidimp),
      PIC_DATA_ICON_INDEX(Impidimp,0),
      //ICON(Impidimp, 0),
      .enemyMonElevation = 0,
    }, //Impidimp,
[SPECIES_MORGREM] = 
    {  
      //FRONT_PIC(Morgrem),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Morgrem),
      BACK_COORD(0x88,0),
      //PALETTES(Morgrem),
      PIC_DATA_ICON_INDEX(Morgrem,0),
      //ICON(Morgrem, 0),
      .enemyMonElevation = 0,
    }, //Morgrem,
[SPECIES_GRIMMSNARL] = 
    {  
      //FRONT_PIC(Grimmsnarl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grimmsnarl),
      BACK_COORD(0x88,0),
      //PALETTES(Grimmsnarl),
      PIC_DATA_ICON_INDEX(Grimmsnarl,0),
      //ICON(Grimmsnarl, 0),
      .enemyMonElevation = 0,
    }, //Grimmsnarl,
[SPECIES_OBSTAGOON] = 
    {  
      //FRONT_PIC(Obstagoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Obstagoon),
      BACK_COORD(0x88,0),
      //PALETTES(Obstagoon),
      PIC_DATA_ICON_INDEX(Obstagoon,0),
      //ICON(Obstagoon, 0),
      .enemyMonElevation = 0,
    }, //Obstagoon,
[SPECIES_PERRSERKER] = 
    {  
      //FRONT_PIC(Perrserker),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Perrserker),
      BACK_COORD(0x88,0),
      //PALETTES(Perrserker),
      PIC_DATA_ICON_INDEX(Perrserker,0),
      //ICON(Perrserker, 0),
      .enemyMonElevation = 0,
    }, //Perrserker,
[SPECIES_CURSOLA] = 
    {  
      //FRONT_PIC(Cursola),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cursola),
      BACK_COORD(0x88,0),
      //PALETTES(Cursola),
      PIC_DATA_ICON_INDEX(Cursola,0),
      //ICON(Cursola, 0),
      .enemyMonElevation = 0,
    }, //Cursola,
[SPECIES_SIRFETCHD] = 
    {  
      //FRONT_PIC(Sirfetchd),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sirfetchd),
      BACK_COORD(0x88,0),
      //PALETTES(Sirfetchd),
      PIC_DATA_ICON_INDEX(Sirfetchd,0),
      //ICON(Sirfetchd, 0),
      .enemyMonElevation = 0,
    }, //Sirfetchd,
[SPECIES_MR_RIME] = 
    {  
      //FRONT_PIC(MrRime),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MrRime),
      BACK_COORD(0x88,0),
      //PALETTES(MrRime),
      PIC_DATA_ICON_INDEX(MrRime,0),
      //ICON(MrRime, 0),
      .enemyMonElevation = 0,
    }, //MrRime,
[SPECIES_RUNERIGUS] = 
    {  
      //FRONT_PIC(Runerigus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Runerigus),
      BACK_COORD(0x88,0),
      //PALETTES(Runerigus),
      PIC_DATA_ICON_INDEX(Runerigus,0),
      //ICON(Runerigus, 0),
      .enemyMonElevation = 0,
    }, //Runerigus,
[SPECIES_MILCERY] = 
    {  
      //FRONT_PIC(Milcery),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Milcery),
      BACK_COORD(0x88,0),
      //PALETTES(Milcery),
      PIC_DATA_ICON_INDEX(Milcery,0),
      //ICON(Milcery, 0),
      .enemyMonElevation = 0,
    }, //Milcery,
[SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStrawberryVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,
[SPECIES_FALINKS] = 
    {  
      //FRONT_PIC(Falinks),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Falinks),
      BACK_COORD(0x88,0),
      //PALETTES(Falinks),
      PIC_DATA_ICON_INDEX(Falinks,0),
      //ICON(Falinks, 0),
      .enemyMonElevation = 0,
    }, //Falinks,
[SPECIES_PINCURCHIN] = 
    {  
      //FRONT_PIC(Pincurchin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pincurchin),
      BACK_COORD(0x88,0),
      //PALETTES(Pincurchin),
      PIC_DATA_ICON_INDEX(Pincurchin,0),
      //ICON(Pincurchin, 0),
      .enemyMonElevation = 0,
    }, //Pincurchin,
[SPECIES_SNOM] = 
    {  
      //FRONT_PIC(Snom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Snom),
      BACK_COORD(0x88,0),
      //PALETTES(Snom),
      PIC_DATA_ICON_INDEX(Snom,0),
      //ICON(Snom, 0),
      .enemyMonElevation = 0,
    }, //Snom,
[SPECIES_FROSMOTH] = 
    {  
      //FRONT_PIC(Frosmoth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Frosmoth),
      BACK_COORD(0x88,0),
      //PALETTES(Frosmoth),
      PIC_DATA_ICON_INDEX(Frosmoth,0),
      //ICON(Frosmoth, 0),
      .enemyMonElevation = 0,
    }, //Frosmoth,
[SPECIES_STONJOURNER] = 
    {  
      //FRONT_PIC(Stonjourner),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Stonjourner),
      BACK_COORD(0x88,0),
      //PALETTES(Stonjourner),
      PIC_DATA_ICON_INDEX(Stonjourner,0),
      //ICON(Stonjourner, 0),
      .enemyMonElevation = 0,
    }, //Stonjourner,
[SPECIES_EISCUE] = 
    {  
      //FRONT_PIC(Eiscue),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Eiscue),
      BACK_COORD(0x88,0),
      //PALETTES(Eiscue),
      PIC_DATA_ICON_INDEX(Eiscue,0),
      //ICON(Eiscue, 0),
      .enemyMonElevation = 0,
    }, //Eiscue,
[SPECIES_INDEEDEE_MALE] = 
    {  
      //FRONT_PIC(IndeedeeMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IndeedeeMale),
      BACK_COORD(0x88,0),
      //PALETTES(IndeedeeMale),
      PIC_DATA_ICON_INDEX(IndeedeeMale,0),
      //ICON(IndeedeeMale, 0),
      .enemyMonElevation = 0,
    }, //Indeedee,
[SPECIES_MORPEKO] = 
    {  
      //FRONT_PIC(Morpeko),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Morpeko),
      BACK_COORD(0x88,0),
      //PALETTES(Morpeko),
      PIC_DATA_ICON_INDEX(Morpeko,0),
      //ICON(Morpeko, 0),
      .enemyMonElevation = 0,
    }, //Morpeko,
[SPECIES_CUFANT] = 
    {  
      //FRONT_PIC(Cufant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cufant),
      BACK_COORD(0x88,0),
      //PALETTES(Cufant),
      PIC_DATA_ICON_INDEX(Cufant,0),
      //ICON(Cufant, 0),
      .enemyMonElevation = 0,
    }, //Cufant,
[SPECIES_COPPERAJAH] = 
    {  
      //FRONT_PIC(Copperajah),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Copperajah),
      BACK_COORD(0x88,0),
      //PALETTES(Copperajah),
      PIC_DATA_ICON_INDEX(Copperajah,0),
      //ICON(Copperajah, 0),
      .enemyMonElevation = 0,
    }, //Copperajah,
[SPECIES_DRACOZOLT] = 
    {  
      //FRONT_PIC(Dracozolt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dracozolt),
      BACK_COORD(0x88,0),
      //PALETTES(Dracozolt),
      PIC_DATA_ICON_INDEX(Dracozolt,0),
      //ICON(Dracozolt, 0),
      .enemyMonElevation = 0,
    }, //Dracozolt,
[SPECIES_ARCTOZOLT] = 
    {  
      //FRONT_PIC(Arctozolt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arctozolt),
      BACK_COORD(0x88,0),
      //PALETTES(Arctozolt),
      PIC_DATA_ICON_INDEX(Arctozolt,0),
      //ICON(Arctozolt, 0),
      .enemyMonElevation = 0,
    }, //Arctozolt,
[SPECIES_DRACOVISH] = 
    {  
      //FRONT_PIC(Dracovish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dracovish),
      BACK_COORD(0x88,0),
      //PALETTES(Dracovish),
      PIC_DATA_ICON_INDEX(Dracovish,0),
      //ICON(Dracovish, 0),
      .enemyMonElevation = 0,
    }, //Dracovish,
[SPECIES_ARCTOVISH] = 
    {  
      //FRONT_PIC(Arctovish),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arctovish),
      BACK_COORD(0x88,0),
      //PALETTES(Arctovish),
      PIC_DATA_ICON_INDEX(Arctovish,0),
      //ICON(Arctovish, 0),
      .enemyMonElevation = 0,
    }, //Arctovish,
[SPECIES_DURALUDON] = 
    {  
      //FRONT_PIC(Duraludon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Duraludon),
      BACK_COORD(0x88,0),
      //PALETTES(Duraludon),
      PIC_DATA_ICON_INDEX(Duraludon,0),
      //ICON(Duraludon, 0),
      .enemyMonElevation = 0,
    }, //Duraludon,
[SPECIES_DREEPY] = 
    {  
      //FRONT_PIC(Dreepy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dreepy),
      BACK_COORD(0x88,0),
      //PALETTES(Dreepy),
      PIC_DATA_ICON_INDEX(Dreepy,0),
      //ICON(Dreepy, 0),
      .enemyMonElevation = 0,
    }, //Dreepy,
[SPECIES_DRAKLOAK] = 
    {  
      //FRONT_PIC(Drakloak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Drakloak),
      BACK_COORD(0x88,0),
      //PALETTES(Drakloak),
      PIC_DATA_ICON_INDEX(Drakloak,0),
      //ICON(Drakloak, 0),
      .enemyMonElevation = 0,
    }, //Drakloak,
[SPECIES_DRAGAPULT] = 
    {  
      //FRONT_PIC(Dragapult),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dragapult),
      BACK_COORD(0x88,0),
      //PALETTES(Dragapult),
      PIC_DATA_ICON_INDEX(Dragapult,0),
      //ICON(Dragapult, 0),
      .enemyMonElevation = 0,
    }, //Dragapult,
[SPECIES_ZACIAN] = 
    {  
      //FRONT_PIC(Zacian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zacian),
      BACK_COORD(0x88,0),
      //PALETTES(Zacian),
      PIC_DATA_ICON_INDEX(Zacian,0),
      //ICON(Zacian, 0),
      .enemyMonElevation = 0,
    }, //Zacian,
[SPECIES_ZAMAZENTA] = 
    {  
      //FRONT_PIC(Zamazenta),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zamazenta),
      BACK_COORD(0x88,0),
      //PALETTES(Zamazenta),
      PIC_DATA_ICON_INDEX(Zamazenta,0),
      //ICON(Zamazenta, 0),
      .enemyMonElevation = 0,
    }, //Zamazenta,
[SPECIES_ETERNATUS] = 
    {  
      //FRONT_PIC(Eternatus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Eternatus),
      BACK_COORD(0x88,0),
      //PALETTES(Eternatus),
      PIC_DATA_ICON_INDEX(Eternatus,0),
      //ICON(Eternatus, 0),
      .enemyMonElevation = 0,
    }, //Eternatus,
[SPECIES_KUBFU] = 
    {  
      //FRONT_PIC(Kubfu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kubfu),
      BACK_COORD(0x88,0),
      //PALETTES(Kubfu),
      PIC_DATA_ICON_INDEX(Kubfu,0),
      //ICON(Kubfu, 0),
      .enemyMonElevation = 0,
    }, //Kubfu,
[SPECIES_URSHIFU_SINGLE_STRIKE_STYLE] = 
    {  
      FRONT_PIC(UrshifuSingleStrikeStyle),
      FRONT_COORD(0x88,0),
      BACK_PIC(UrshifuSingleStrikeStyle),
      BACK_COORD(0x88,0),
      PALETTES(UrshifuSingleStrikeStyle),
      //PIC_DATA_ICON_INDEX(UrshifuSingleStrikeStyle,0),
      ICON(Urshifu, 0),
      .enemyMonElevation = 0,
    }, //Urshifu,
[SPECIES_ZARUDE] = 
    {  
      //FRONT_PIC(Zarude),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zarude),
      BACK_COORD(0x88,0),
      //PALETTES(Zarude),
      PIC_DATA_ICON_INDEX(Zarude,0),
      //ICON(Zarude, 0),
      .enemyMonElevation = 0,
    }, //Zarude,
[SPECIES_REGIELEKI] = 
    {  
      //FRONT_PIC(Regieleki),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Regieleki),
      BACK_COORD(0x88,0),
      //PALETTES(Regieleki),
      PIC_DATA_ICON_INDEX(Regieleki,0),
      //ICON(Regieleki, 0),
      .enemyMonElevation = 0,
    }, //Regieleki,
[SPECIES_REGIDRAGO] = 
    {  
      //FRONT_PIC(Regidrago),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Regidrago),
      BACK_COORD(0x88,0),
      //PALETTES(Regidrago),
      PIC_DATA_ICON_INDEX(Regidrago,0),
      //ICON(Regidrago, 0),
      .enemyMonElevation = 0,
    }, //Regidrago,
[SPECIES_GLASTRIER] = 
    {  
      //FRONT_PIC(Glastrier),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Glastrier),
      BACK_COORD(0x88,0),
      //PALETTES(Glastrier),
      PIC_DATA_ICON_INDEX(Glastrier,0),
      //ICON(Glastrier, 0),
      .enemyMonElevation = 0,
    }, //Glastrier,
[SPECIES_SPECTRIER] = 
    {  
      //FRONT_PIC(Spectrier),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spectrier),
      BACK_COORD(0x88,0),
      //PALETTES(Spectrier),
      PIC_DATA_ICON_INDEX(Spectrier,0),
      //ICON(Spectrier, 0),
      .enemyMonElevation = 0,
    }, //Spectrier,
[SPECIES_CALYREX] = 
    {  
      //FRONT_PIC(Calyrex),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Calyrex),
      BACK_COORD(0x88,0),
      //PALETTES(Calyrex),
      PIC_DATA_ICON_INDEX(Calyrex,0),
      //ICON(Calyrex, 0),
      .enemyMonElevation = 0,
    }, //Calyrex,
[SPECIES_WYRDEER] = 
    {  
      //FRONT_PIC(Wyrdeer),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wyrdeer),
      BACK_COORD(0x88,0),
      //PALETTES(Wyrdeer),
      PIC_DATA_ICON_INDEX(Wyrdeer,0),
      //ICON(Wyrdeer, 0),
      .enemyMonElevation = 0,
    }, //Wyrdeer,
[SPECIES_KLEAVOR] = 
    {  
      //FRONT_PIC(Kleavor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kleavor),
      BACK_COORD(0x88,0),
      //PALETTES(Kleavor),
      PIC_DATA_ICON_INDEX(Kleavor,0),
      //ICON(Kleavor, 0),
      .enemyMonElevation = 0,
    }, //Kleavor,
[SPECIES_URSALUNA] = 
    {  
      //FRONT_PIC(Ursaluna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ursaluna),
      BACK_COORD(0x88,0),
      //PALETTES(Ursaluna),
      PIC_DATA_ICON_INDEX(Ursaluna,0),
      //ICON(Ursaluna, 0),
      .enemyMonElevation = 0,
    }, //Ursaluna,
[SPECIES_BASCULEGION_MALE] = 
    {  
      //FRONT_PIC(BasculegionMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BasculegionMale),
      BACK_COORD(0x88,0),
      //PALETTES(BasculegionMale),
      PIC_DATA_ICON_INDEX(BasculegionMale,0),
      //ICON(BasculegionMale, 0),
      .enemyMonElevation = 0,
    }, //Basculegion,
[SPECIES_SNEASLER] = 
    {  
      //FRONT_PIC(Sneasler),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Sneasler),
      BACK_COORD(0x88,0),
      //PALETTES(Sneasler),
      PIC_DATA_ICON_INDEX(Sneasler,0),
      //ICON(Sneasler, 0),
      .enemyMonElevation = 0,
    }, //Sneasler,
[SPECIES_OVERQWIL] = 
    {  
      //FRONT_PIC(Overqwil),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Overqwil),
      BACK_COORD(0x88,0),
      //PALETTES(Overqwil),
      PIC_DATA_ICON_INDEX(Overqwil,0),
      //ICON(Overqwil, 0),
      .enemyMonElevation = 0,
    }, //Overqwil,
[SPECIES_ENAMORUS] = 
    {  
      //FRONT_PIC(Enamorus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Enamorus),
      BACK_COORD(0x88,0),
      //PALETTES(Enamorus),
      PIC_DATA_ICON_INDEX(Enamorus,0),
      //ICON(Enamorus, 0),
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
      //FRONT_PIC(Floragato),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Floragato),
      BACK_COORD(0x88,0),
      //PALETTES(Floragato),
      PIC_DATA_ICON_INDEX(Floragato,0),
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
      //FRONT_PIC(Meowscarada),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Meowscarada),
      BACK_COORD(0x88,0),
      //PALETTES(Meowscarada),
      PIC_DATA_ICON_INDEX(Meowscarada,0),
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
      //FRONT_PIC(Fuecoco),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fuecoco),
      BACK_COORD(0x88,0),
      //PALETTES(Fuecoco),
      PIC_DATA_ICON_INDEX(Fuecoco,0),
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
      //FRONT_PIC(Crocalor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Crocalor),
      BACK_COORD(0x88,0),
      //PALETTES(Crocalor),
      PIC_DATA_ICON_INDEX(Crocalor,0),
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
      //FRONT_PIC(Skeledirge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Skeledirge),
      BACK_COORD(0x88,0),
      //PALETTES(Skeledirge),
      PIC_DATA_ICON_INDEX(Skeledirge,0),
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
      //FRONT_PIC(Quaxly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Quaxly),
      BACK_COORD(0x88,0),
      //PALETTES(Quaxly),
      PIC_DATA_ICON_INDEX(Quaxly,0),
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
      //FRONT_PIC(Quaxwell),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Quaxwell),
      BACK_COORD(0x88,0),
      //PALETTES(Quaxwell),
      PIC_DATA_ICON_INDEX(Quaxwell,0),
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
      //FRONT_PIC(Quaquaval),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Quaquaval),
      BACK_COORD(0x88,0),
      //PALETTES(Quaquaval),
      PIC_DATA_ICON_INDEX(Quaquaval,0),
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
      //FRONT_PIC(Lechonk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lechonk),
      BACK_COORD(0x88,0),
      //PALETTES(Lechonk),
      PIC_DATA_ICON_INDEX(Lechonk,0),
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
      //FRONT_PIC(OinkologneMale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OinkologneMale),
      BACK_COORD(0x88,0),
      //PALETTES(OinkologneMale),
      PIC_DATA_ICON_INDEX(OinkologneMale,0),
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
      //FRONT_PIC(OinkologneFemale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OinkologneFemale),
      BACK_COORD(0x88,0),
      //PALETTES(OinkologneFemale),
      PIC_DATA_ICON_INDEX(OinkologneFemale,0),
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
      //FRONT_PIC(Tarountula),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tarountula),
      BACK_COORD(0x88,0),
      //PALETTES(Tarountula),
      PIC_DATA_ICON_INDEX(Tarountula,0),
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
      //FRONT_PIC(Spidops),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Spidops),
      BACK_COORD(0x88,0),
      //PALETTES(Spidops),
      PIC_DATA_ICON_INDEX(Spidops,0),
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
      //FRONT_PIC(Nymble),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nymble),
      BACK_COORD(0x88,0),
      //PALETTES(Nymble),
      PIC_DATA_ICON_INDEX(Nymble,0),
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
      //FRONT_PIC(Lokix),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Lokix),
      BACK_COORD(0x88,0),
      //PALETTES(Lokix),
      PIC_DATA_ICON_INDEX(Lokix,0),
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
      //FRONT_PIC(Pawmi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pawmi),
      BACK_COORD(0x88,0),
      //PALETTES(Pawmi),
      PIC_DATA_ICON_INDEX(Pawmi,0),
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
      //FRONT_PIC(Pawmo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pawmo),
      BACK_COORD(0x88,0),
      //PALETTES(Pawmo),
      PIC_DATA_ICON_INDEX(Pawmo,0),
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
      //FRONT_PIC(Pawmot),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pawmot),
      BACK_COORD(0x88,0),
      //PALETTES(Pawmot),
      PIC_DATA_ICON_INDEX(Pawmot,0),
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
      //FRONT_PIC(Tandemaus),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tandemaus),
      BACK_COORD(0x88,0),
      //PALETTES(Tandemaus),
      PIC_DATA_ICON_INDEX(Tandemaus,0),
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
      //FRONT_PIC(MausholdFamilyOfThree),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MausholdFamilyOfThree),
      BACK_COORD(0x88,0),
      //PALETTES(MausholdFamilyOfThree),
      PIC_DATA_ICON_INDEX(MausholdFamilyOfThree,0),
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
      //FRONT_PIC(MausholdFamilyOfFour),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MausholdFamilyOfFour),
      BACK_COORD(0x88,0),
      //PALETTES(MausholdFamilyOfFour),
      PIC_DATA_ICON_INDEX(MausholdFamilyOfFour,0),
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
      //FRONT_PIC(Fidough),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fidough),
      BACK_COORD(0x88,0),
      //PALETTES(Fidough),
      PIC_DATA_ICON_INDEX(Fidough,0),
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
      //FRONT_PIC(Dachsbun),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dachsbun),
      BACK_COORD(0x88,0),
      //PALETTES(Dachsbun),
      PIC_DATA_ICON_INDEX(Dachsbun,0),
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
      //FRONT_PIC(Smoliv),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Smoliv),
      BACK_COORD(0x88,0),
      //PALETTES(Smoliv),
      PIC_DATA_ICON_INDEX(Smoliv,0),
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
      //FRONT_PIC(Dolliv),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dolliv),
      BACK_COORD(0x88,0),
      //PALETTES(Dolliv),
      PIC_DATA_ICON_INDEX(Dolliv,0),
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
      //FRONT_PIC(Arboliva),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arboliva),
      BACK_COORD(0x88,0),
      //PALETTES(Arboliva),
      PIC_DATA_ICON_INDEX(Arboliva,0),
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
      //FRONT_PIC(SquawkabillyGreenPlumage),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SquawkabillyGreenPlumage),
      BACK_COORD(0x88,0),
      //PALETTES(SquawkabillyGreenPlumage),
      PIC_DATA_ICON_INDEX(SquawkabillyGreenPlumage,0),
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
      //FRONT_PIC(SquawkabillyBluePlumage),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SquawkabillyBluePlumage),
      BACK_COORD(0x88,0),
      //PALETTES(SquawkabillyBluePlumage),
      PIC_DATA_ICON_INDEX(SquawkabillyBluePlumage,0),
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
      //FRONT_PIC(SquawkabillyYellowPlumage),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SquawkabillyYellowPlumage),
      BACK_COORD(0x88,0),
      //PALETTES(SquawkabillyYellowPlumage),
      PIC_DATA_ICON_INDEX(SquawkabillyYellowPlumage,0),
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
      //FRONT_PIC(SquawkabillyWhitePlumage),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SquawkabillyWhitePlumage),
      BACK_COORD(0x88,0),
      //PALETTES(SquawkabillyWhitePlumage),
      PIC_DATA_ICON_INDEX(SquawkabillyWhitePlumage,0),
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
      //FRONT_PIC(Nacli),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Nacli),
      BACK_COORD(0x88,0),
      //PALETTES(Nacli),
      PIC_DATA_ICON_INDEX(Nacli,0),
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
      //FRONT_PIC(Naclstack),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Naclstack),
      BACK_COORD(0x88,0),
      //PALETTES(Naclstack),
      PIC_DATA_ICON_INDEX(Naclstack,0),
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
      //FRONT_PIC(Garganacl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Garganacl),
      BACK_COORD(0x88,0),
      //PALETTES(Garganacl),
      PIC_DATA_ICON_INDEX(Garganacl,0),
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
      //FRONT_PIC(Charcadet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Charcadet),
      BACK_COORD(0x88,0),
      //PALETTES(Charcadet),
      PIC_DATA_ICON_INDEX(Charcadet,0),
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
      //FRONT_PIC(Armarouge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Armarouge),
      BACK_COORD(0x88,0),
      //PALETTES(Armarouge),
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
      //FRONT_PIC(Ceruledge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Ceruledge),
      BACK_COORD(0x88,0),
      //PALETTES(Ceruledge),
      PIC_DATA_ICON_INDEX(Ceruledge,0),
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
      //FRONT_PIC(Tadbulb),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tadbulb),
      BACK_COORD(0x88,0),
      //PALETTES(Tadbulb),
      PIC_DATA_ICON_INDEX(Tadbulb,0),
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
      //FRONT_PIC(Bellibolt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bellibolt),
      BACK_COORD(0x88,0),
      //PALETTES(Bellibolt),
      PIC_DATA_ICON_INDEX(Bellibolt,0),
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
      //FRONT_PIC(Wattrel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wattrel),
      BACK_COORD(0x88,0),
      //PALETTES(Wattrel),
      PIC_DATA_ICON_INDEX(Wattrel,0),
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
      //FRONT_PIC(Kilowattrel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kilowattrel),
      BACK_COORD(0x88,0),
      //PALETTES(Kilowattrel),
      PIC_DATA_ICON_INDEX(Kilowattrel,0),
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
      //FRONT_PIC(Maschiff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Maschiff),
      BACK_COORD(0x88,0),
      //PALETTES(Maschiff),
      PIC_DATA_ICON_INDEX(Maschiff,0),
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
      //FRONT_PIC(Mabosstiff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Mabosstiff),
      BACK_COORD(0x88,0),
      //PALETTES(Mabosstiff),
      PIC_DATA_ICON_INDEX(Mabosstiff,0),
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
      //FRONT_PIC(Shroodle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Shroodle),
      BACK_COORD(0x88,0),
      //PALETTES(Shroodle),
      PIC_DATA_ICON_INDEX(Shroodle,0),
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
      //FRONT_PIC(Grafaiai),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Grafaiai),
      BACK_COORD(0x88,0),
      //PALETTES(Grafaiai),
      PIC_DATA_ICON_INDEX(Grafaiai,0),
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
      //FRONT_PIC(Bramblin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bramblin),
      BACK_COORD(0x88,0),
      //PALETTES(Bramblin),
      PIC_DATA_ICON_INDEX(Bramblin,0),
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
      //FRONT_PIC(Brambleghast),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Brambleghast),
      BACK_COORD(0x88,0),
      //PALETTES(Brambleghast),
      PIC_DATA_ICON_INDEX(Brambleghast,0),
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
      //FRONT_PIC(Toedscool),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toedscool),
      BACK_COORD(0x88,0),
      //PALETTES(Toedscool),
      PIC_DATA_ICON_INDEX(Toedscool,0),
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
      //FRONT_PIC(Toedscruel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Toedscruel),
      BACK_COORD(0x88,0),
      //PALETTES(Toedscruel),
      PIC_DATA_ICON_INDEX(Toedscruel,0),
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
      //FRONT_PIC(Klawf),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Klawf),
      BACK_COORD(0x88,0),
      //PALETTES(Klawf),
      PIC_DATA_ICON_INDEX(Klawf,0),
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
      //FRONT_PIC(Capsakid),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Capsakid),
      BACK_COORD(0x88,0),
      //PALETTES(Capsakid),
      PIC_DATA_ICON_INDEX(Capsakid,0),
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
      //FRONT_PIC(Scovillain),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Scovillain),
      BACK_COORD(0x88,0),
      //PALETTES(Scovillain),
      PIC_DATA_ICON_INDEX(Scovillain,0),
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
      //FRONT_PIC(Rellor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rellor),
      BACK_COORD(0x88,0),
      //PALETTES(Rellor),
      PIC_DATA_ICON_INDEX(Rellor,0),
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
      //FRONT_PIC(Rabsca),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Rabsca),
      BACK_COORD(0x88,0),
      //PALETTES(Rabsca),
      PIC_DATA_ICON_INDEX(Rabsca,0),
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
      //FRONT_PIC(Flittle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flittle),
      BACK_COORD(0x88,0),
      //PALETTES(Flittle),
      PIC_DATA_ICON_INDEX(Flittle,0),
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
      //FRONT_PIC(Espathra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Espathra),
      BACK_COORD(0x88,0),
      //PALETTES(Espathra),
      PIC_DATA_ICON_INDEX(Espathra,0),
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
      //FRONT_PIC(Tinkatink),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tinkatink),
      BACK_COORD(0x88,0),
      //PALETTES(Tinkatink),
      PIC_DATA_ICON_INDEX(Tinkatink,0),
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
      //FRONT_PIC(Tinkatuff),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tinkatuff),
      BACK_COORD(0x88,0),
      //PALETTES(Tinkatuff),
      PIC_DATA_ICON_INDEX(Tinkatuff,0),
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
      //FRONT_PIC(Tinkaton),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Tinkaton),
      BACK_COORD(0x88,0),
      //PALETTES(Tinkaton),
      PIC_DATA_ICON_INDEX(Tinkaton,0),
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
      //FRONT_PIC(Wiglett),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wiglett),
      BACK_COORD(0x88,0),
      //PALETTES(Wiglett),
      PIC_DATA_ICON_INDEX(Wiglett,0),
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
      //FRONT_PIC(Wugtrio),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Wugtrio),
      BACK_COORD(0x88,0),
      //PALETTES(Wugtrio),
      PIC_DATA_ICON_INDEX(Wugtrio,0),
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
      //FRONT_PIC(Bombirdier),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Bombirdier),
      BACK_COORD(0x88,0),
      //PALETTES(Bombirdier),
      PIC_DATA_ICON_INDEX(Bombirdier,0),
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
      //FRONT_PIC(Finizen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Finizen),
      BACK_COORD(0x88,0),
      //PALETTES(Finizen),
      PIC_DATA_ICON_INDEX(Finizen,0),
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
      //FRONT_PIC(PalafinZero),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PalafinZero),
      BACK_COORD(0x88,0),
      //PALETTES(PalafinZero),
      PIC_DATA_ICON_INDEX(PalafinZero,0),
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
      //FRONT_PIC(PalafinHero),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PalafinHero),
      BACK_COORD(0x88,0),
      //PALETTES(PalafinHero),
      PIC_DATA_ICON_INDEX(PalafinHero,0),
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
      //FRONT_PIC(Varoom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Varoom),
      BACK_COORD(0x88,0),
      //PALETTES(Varoom),
      PIC_DATA_ICON_INDEX(Varoom,0),
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
      //FRONT_PIC(Revavroom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Revavroom),
      BACK_COORD(0x88,0),
      //PALETTES(Revavroom),
      PIC_DATA_ICON_INDEX(Revavroom,0),
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
      //FRONT_PIC(Cyclizar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cyclizar),
      BACK_COORD(0x88,0),
      //PALETTES(Cyclizar),
      PIC_DATA_ICON_INDEX(Cyclizar,0),
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
      //FRONT_PIC(Orthworm),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Orthworm),
      BACK_COORD(0x88,0),
      //PALETTES(Orthworm),
      PIC_DATA_ICON_INDEX(Orthworm,0),
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
      //FRONT_PIC(Glimmet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Glimmet),
      BACK_COORD(0x88,0),
      //PALETTES(Glimmet),
      PIC_DATA_ICON_INDEX(Glimmet,0),
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
      //FRONT_PIC(Glimmora),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Glimmora),
      BACK_COORD(0x88,0),
      //PALETTES(Glimmora),
      PIC_DATA_ICON_INDEX(Glimmora,0),
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
      //FRONT_PIC(Greavard),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Greavard),
      BACK_COORD(0x88,0),
      //PALETTES(Greavard),
      PIC_DATA_ICON_INDEX(Greavard,0),
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
      //FRONT_PIC(Houndstone),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Houndstone),
      BACK_COORD(0x88,0),
      //PALETTES(Houndstone),
      PIC_DATA_ICON_INDEX(Houndstone,0),
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
      //FRONT_PIC(Flamigo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Flamigo),
      BACK_COORD(0x88,0),
      //PALETTES(Flamigo),
      PIC_DATA_ICON_INDEX(Flamigo,0),
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
      //FRONT_PIC(Cetoddle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cetoddle),
      BACK_COORD(0x88,0),
      //PALETTES(Cetoddle),
      PIC_DATA_ICON_INDEX(Cetoddle,0),
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
      //FRONT_PIC(Cetitan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Cetitan),
      BACK_COORD(0x88,0),
      //PALETTES(Cetitan),
      PIC_DATA_ICON_INDEX(Cetitan,0),
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
      //FRONT_PIC(Veluza),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Veluza),
      BACK_COORD(0x88,0),
      //PALETTES(Veluza),
      PIC_DATA_ICON_INDEX(Veluza,0),
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
      //FRONT_PIC(Dondozo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dondozo),
      BACK_COORD(0x88,0),
      //PALETTES(Dondozo),
      PIC_DATA_ICON_INDEX(Dondozo,0),
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
      //FRONT_PIC(TatsugiriCurly),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TatsugiriCurly),
      BACK_COORD(0x88,0),
      //PALETTES(TatsugiriCurly),
      PIC_DATA_ICON_INDEX(TatsugiriCurly,0),
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
      //FRONT_PIC(TatsugiriDroopy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TatsugiriDroopy),
      BACK_COORD(0x88,0),
      //PALETTES(TatsugiriDroopy),
      PIC_DATA_ICON_INDEX(TatsugiriDroopy,0),
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
      //FRONT_PIC(TatsugiriStretchy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TatsugiriStretchy),
      BACK_COORD(0x88,0),
      //PALETTES(TatsugiriStretchy),
      PIC_DATA_ICON_INDEX(TatsugiriStretchy,0),
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
      //FRONT_PIC(Annihilape),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Annihilape),
      BACK_COORD(0x88,0),
      //PALETTES(Annihilape),
      PIC_DATA_ICON_INDEX(Annihilape,0),
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
      //FRONT_PIC(Clodsire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Clodsire),
      BACK_COORD(0x88,0),
      //PALETTES(Clodsire),
      PIC_DATA_ICON_INDEX(Clodsire,0),
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
      //FRONT_PIC(Farigiraf),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Farigiraf),
      BACK_COORD(0x88,0),
      //PALETTES(Farigiraf),
      PIC_DATA_ICON_INDEX(Farigiraf,0),
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
      //FRONT_PIC(DudunsparceTwoSegment),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DudunsparceTwoSegment),
      BACK_COORD(0x88,0),
      //PALETTES(DudunsparceTwoSegment),
      PIC_DATA_ICON_INDEX(DudunsparceTwoSegment,0),
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
      //FRONT_PIC(DudunsparceThreeSegment),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DudunsparceThreeSegment),
      BACK_COORD(0x88,0),
      //PALETTES(DudunsparceThreeSegment),
      PIC_DATA_ICON_INDEX(DudunsparceThreeSegment,0),
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
      //FRONT_PIC(Kingambit),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Kingambit),
      BACK_COORD(0x88,0),
      //PALETTES(Kingambit),
      PIC_DATA_ICON_INDEX(Kingambit,0),
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
      //FRONT_PIC(GreatTusk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GreatTusk),
      BACK_COORD(0x88,0),
      //PALETTES(GreatTusk),
      PIC_DATA_ICON_INDEX(GreatTusk,0),
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
      //FRONT_PIC(ScreamTail),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ScreamTail),
      BACK_COORD(0x88,0),
      //PALETTES(ScreamTail),
      PIC_DATA_ICON_INDEX(ScreamTail,0),
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
      //FRONT_PIC(BruteBonnet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BruteBonnet),
      BACK_COORD(0x88,0),
      //PALETTES(BruteBonnet),
      PIC_DATA_ICON_INDEX(BruteBonnet,0),
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
      //FRONT_PIC(FlutterMane),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlutterMane),
      BACK_COORD(0x88,0),
      //PALETTES(FlutterMane),
      PIC_DATA_ICON_INDEX(FlutterMane,0),
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
      //FRONT_PIC(SlitherWing),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SlitherWing),
      BACK_COORD(0x88,0),
      //PALETTES(SlitherWing),
      PIC_DATA_ICON_INDEX(SlitherWing,0),
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
      //FRONT_PIC(SandyShocks),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SandyShocks),
      BACK_COORD(0x88,0),
      //PALETTES(SandyShocks),
      PIC_DATA_ICON_INDEX(SandyShocks,0),
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
      //FRONT_PIC(IronTreads),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronTreads),
      BACK_COORD(0x88,0),
      //PALETTES(IronTreads),
      PIC_DATA_ICON_INDEX(IronTreads,0),
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
      //FRONT_PIC(IronBundle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronBundle),
      BACK_COORD(0x88,0),
      //PALETTES(IronBundle),
      PIC_DATA_ICON_INDEX(IronBundle,0),
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
      //FRONT_PIC(IronHands),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronHands),
      BACK_COORD(0x88,0),
      //PALETTES(IronHands),
      PIC_DATA_ICON_INDEX(IronHands,0),
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
      //FRONT_PIC(IronJugulis),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronJugulis),
      BACK_COORD(0x88,0),
      //PALETTES(IronJugulis),
      PIC_DATA_ICON_INDEX(IronJugulis,0),
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
      //FRONT_PIC(IronMoth),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronMoth),
      BACK_COORD(0x88,0),
      //PALETTES(IronMoth),
      PIC_DATA_ICON_INDEX(IronMoth,0),
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
      //FRONT_PIC(IronThorns),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronThorns),
      BACK_COORD(0x88,0),
      //PALETTES(IronThorns),
      PIC_DATA_ICON_INDEX(IronThorns,0),
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
      //FRONT_PIC(Frigibax),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Frigibax),
      BACK_COORD(0x88,0),
      //PALETTES(Frigibax),
      PIC_DATA_ICON_INDEX(Frigibax,0),
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
      //FRONT_PIC(Arctibax),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Arctibax),
      BACK_COORD(0x88,0),
      //PALETTES(Arctibax),
      PIC_DATA_ICON_INDEX(Arctibax,0),
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
      //FRONT_PIC(Baxcalibur),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Baxcalibur),
      BACK_COORD(0x88,0),
      //PALETTES(Baxcalibur),
      PIC_DATA_ICON_INDEX(Baxcalibur,0),
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
      //FRONT_PIC(GimmighoulChest),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GimmighoulChest),
      BACK_COORD(0x88,0),
      //PALETTES(GimmighoulChest),
      PIC_DATA_ICON_INDEX(GimmighoulChest,0),
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
      //FRONT_PIC(GimmighoulRoaming),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GimmighoulRoaming),
      BACK_COORD(0x88,0),
      //PALETTES(GimmighoulRoaming),
      PIC_DATA_ICON_INDEX(GimmighoulRoaming,0),
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
      //FRONT_PIC(Gholdengo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Gholdengo),
      BACK_COORD(0x88,0),
      //PALETTES(Gholdengo),
      PIC_DATA_ICON_INDEX(Gholdengo,0),
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
      //FRONT_PIC(WoChien),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WoChien),
      BACK_COORD(0x88,0),
      //PALETTES(WoChien),
      PIC_DATA_ICON_INDEX(WoChien,0),
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
      //FRONT_PIC(ChienPao),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ChienPao),
      BACK_COORD(0x88,0),
      //PALETTES(ChienPao),
      PIC_DATA_ICON_INDEX(ChienPao,0),
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
      //FRONT_PIC(TingLu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TingLu),
      BACK_COORD(0x88,0),
      //PALETTES(TingLu),
      PIC_DATA_ICON_INDEX(TingLu,0),
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
      //FRONT_PIC(ChiYu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ChiYu),
      BACK_COORD(0x88,0),
      //PALETTES(ChiYu),
      PIC_DATA_ICON_INDEX(ChiYu,0),
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
      //FRONT_PIC(RoaringMoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RoaringMoon),
      BACK_COORD(0x88,0),
      //PALETTES(RoaringMoon),
      PIC_DATA_ICON_INDEX(RoaringMoon,0),
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
      //FRONT_PIC(IronValiant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronValiant),
      BACK_COORD(0x88,0),
      //PALETTES(IronValiant),
      PIC_DATA_ICON_INDEX(IronValiant,0),
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
      //FRONT_PIC(Koraidon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Koraidon),
      BACK_COORD(0x88,0),
      //PALETTES(Koraidon),
      PIC_DATA_ICON_INDEX(Koraidon,0),
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
      //FRONT_PIC(Miraidon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Miraidon),
      BACK_COORD(0x88,0),
      //PALETTES(Miraidon),
      PIC_DATA_ICON_INDEX(Miraidon,0),
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
      //FRONT_PIC(TaurosPaldeanCombatBreed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TaurosPaldeanCombatBreed),
      BACK_COORD(0x88,0),
      //PALETTES(TaurosPaldeanCombatBreed),
      PIC_DATA_ICON_INDEX(TaurosPaldeanCombatBreed,0),
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
      //FRONT_PIC(TaurosPaldeanBlazeBreed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TaurosPaldeanBlazeBreed),
      BACK_COORD(0x88,0),
      //PALETTES(TaurosPaldeanBlazeBreed),
      PIC_DATA_ICON_INDEX(TaurosPaldeanBlazeBreed,0),
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
      //FRONT_PIC(TaurosPaldeanAquaBreed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TaurosPaldeanAquaBreed),
      BACK_COORD(0x88,0),
      //PALETTES(TaurosPaldeanAquaBreed),
      PIC_DATA_ICON_INDEX(TaurosPaldeanAquaBreed,0),
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
      //FRONT_PIC(WooperPaldean),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WooperPaldean),
      BACK_COORD(0x88,0),
      //PALETTES(WooperPaldean),
      PIC_DATA_ICON_INDEX(WooperPaldean,0),
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
      //FRONT_PIC(WalkingWake),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WalkingWake),
      BACK_COORD(0x88,0),
      //PALETTES(WalkingWake),
      PIC_DATA_ICON_INDEX(WalkingWake,0),
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
      //FRONT_PIC(IronLeaves),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronLeaves),
      BACK_COORD(0x88,0),
      //PALETTES(IronLeaves),
      PIC_DATA_ICON_INDEX(IronLeaves,0),
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
      //FRONT_PIC(Dipplin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Dipplin),
      BACK_COORD(0x88,0),
      //PALETTES(Dipplin),
      PIC_DATA_ICON_INDEX(Dipplin,0),
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
      //FRONT_PIC(PoltchageistCounterfeit),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PoltchageistCounterfeit),
      BACK_COORD(0x88,0),
      //PALETTES(PoltchageistCounterfeit),
      PIC_DATA_ICON_INDEX(PoltchageistCounterfeit,0),
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
      //FRONT_PIC(PoltchageistArtisan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PoltchageistArtisan),
      BACK_COORD(0x88,0),
      //PALETTES(PoltchageistArtisan),
      PIC_DATA_ICON_INDEX(PoltchageistArtisan,0),
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
      //FRONT_PIC(SinistchaUnremarkable),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SinistchaUnremarkable),
      BACK_COORD(0x88,0),
      //PALETTES(SinistchaUnremarkable),
      PIC_DATA_ICON_INDEX(SinistchaUnremarkable,0),
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
      //FRONT_PIC(SinistchaMasterpiece),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SinistchaMasterpiece),
      BACK_COORD(0x88,0),
      //PALETTES(SinistchaMasterpiece),
      PIC_DATA_ICON_INDEX(SinistchaMasterpiece,0),
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
      //FRONT_PIC(Okidogi),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Okidogi),
      BACK_COORD(0x88,0),
      //PALETTES(Okidogi),
      PIC_DATA_ICON_INDEX(Okidogi,0),
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
      //FRONT_PIC(Munkidori),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Munkidori),
      BACK_COORD(0x88,0),
      //PALETTES(Munkidori),
      PIC_DATA_ICON_INDEX(Munkidori,0),
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
      //FRONT_PIC(Fezandipiti),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Fezandipiti),
      BACK_COORD(0x88,0),
      //PALETTES(Fezandipiti),
      PIC_DATA_ICON_INDEX(Fezandipiti,0),
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
      //FRONT_PIC(OgerponTealMask),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OgerponTealMask),
      BACK_COORD(0x88,0),
      //PALETTES(OgerponTealMask),
      PIC_DATA_ICON_INDEX(OgerponTealMask,0),
      //ICON(OgerponTealMask, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_OGERPON_WELLSPRING_MASK] = 
    {  
      //FRONT_PIC(OgerponWellspringMask),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OgerponWellspringMask),
      BACK_COORD(0x88,0),
      //PALETTES(OgerponWellspringMask),
      PIC_DATA_ICON_INDEX(OgerponWellspringMask,0),
      //ICON(OgerponWellspringMask, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_OGERPON_HEARTHFLAME_MASK] = 
    {  
      //FRONT_PIC(OgerponHearthflameMask),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OgerponHearthflameMask),
      BACK_COORD(0x88,0),
      //PALETTES(OgerponHearthflameMask),
      PIC_DATA_ICON_INDEX(OgerponHearthflameMask,0),
      //ICON(OgerponHearthflameMask, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_OGERPON_CORNERSTONE_MASK] = 
    {  
      //FRONT_PIC(OgerponCornerstoneMask),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OgerponCornerstoneMask),
      BACK_COORD(0x88,0),
      //PALETTES(OgerponCornerstoneMask),
      PIC_DATA_ICON_INDEX(OgerponCornerstoneMask,0),
      //ICON(OgerponCornerstoneMask, 0),
      .enemyMonElevation = 0,
    },
[SPECIES_URSALUNA_BLOODMOON] =
    {
      //FRONT_PIC(UrsalunaBloodmoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UrsalunaBloodmoon),
      BACK_COORD(0x88,0),
      //PALETTES(UrsalunaBloodmoon),
      PIC_DATA_ICON_INDEX(UrsalunaBloodmoon,0),
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
      //FRONT_PIC(Archaludon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Archaludon),
      BACK_COORD(0x88,0),
      //PALETTES(Archaludon),
      PIC_DATA_ICON_INDEX(Archaludon,0),
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
      //FRONT_PIC(Hydrapple),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Hydrapple),
      BACK_COORD(0x88,0),
      //PALETTES(Hydrapple),
      PIC_DATA_ICON_INDEX(Hydrapple,0),
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
      //FRONT_PIC(GougingFire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GougingFire),
      BACK_COORD(0x88,0),
      //PALETTES(GougingFire),
      PIC_DATA_ICON_INDEX(GougingFire,0),
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
      //FRONT_PIC(RagingBolt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RagingBolt),
      BACK_COORD(0x88,0),
      //PALETTES(RagingBolt),
      PIC_DATA_ICON_INDEX(RagingBolt,0),
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
      //FRONT_PIC(IronBoulder),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronBoulder),
      BACK_COORD(0x88,0),
      //PALETTES(IronBoulder),
      PIC_DATA_ICON_INDEX(IronBoulder,0),
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
      //FRONT_PIC(IronCrown),
      FRONT_COORD(0x88,0),
      //BACK_PIC(IronCrown),
      BACK_COORD(0x88,0),
      //PALETTES(IronCrown),
      PIC_DATA_ICON_INDEX(IronCrown,0),
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
      //FRONT_PIC(TerapagosNormal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TerapagosNormal),
      BACK_COORD(0x88,0),
      //PALETTES(TerapagosNormal),
      PIC_DATA_ICON_INDEX(TerapagosNormal,0),
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
      //FRONT_PIC(TerapagosTerastal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TerapagosTerastal),
      BACK_COORD(0x88,0),
      //PALETTES(TerapagosTerastal),
      PIC_DATA_ICON_INDEX(TerapagosTerastal,0),
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
      //FRONT_PIC(TerapagosStellar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TerapagosStellar),
      BACK_COORD(0x88,0),
      //PALETTES(TerapagosStellar),
      PIC_DATA_ICON_INDEX(TerapagosStellar,0),
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
      //FRONT_PIC(Pecharunt),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Pecharunt),
      BACK_COORD(0x88,0),
      //PALETTES(Pecharunt),
      PIC_DATA_ICON_INDEX(Pecharunt,0),
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
      //FRONT_PIC(VenusaurMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VenusaurMega),
      BACK_COORD(0x88,0),
      //PALETTES(VenusaurMega),
      PIC_DATA_ICON_INDEX(VenusaurMega,0),
      //ICON(VenusaurMega, 0),
      .enemyMonElevation = 0,
    }, //VenusaurMega,
[SPECIES_CHARIZARD_MEGA_X] = 
    {  
      //FRONT_PIC(CharizardMegaX),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CharizardMegaX),
      BACK_COORD(0x88,0),
      //PALETTES(CharizardMegaX),
      PIC_DATA_ICON_INDEX(CharizardMegaX,0),
      //ICON(CharizardMegaX, 0),
      .enemyMonElevation = 0,
    }, //CharizardMegaX,
[SPECIES_CHARIZARD_MEGA_Y] = 
    {  
      //FRONT_PIC(CharizardMegaY),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CharizardMegaY),
      BACK_COORD(0x88,0),
      //PALETTES(CharizardMegaY),
      PIC_DATA_ICON_INDEX(CharizardMegaY,0),
      //ICON(CharizardMegaY, 0),
      .enemyMonElevation = 0,
    }, //CharizardMegaY,
[SPECIES_BLASTOISE_MEGA] = 
    {  
      //FRONT_PIC(BlastoiseMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BlastoiseMega),
      BACK_COORD(0x88,0),
      //PALETTES(BlastoiseMega),
      PIC_DATA_ICON_INDEX(BlastoiseMega,0),
      //ICON(BlastoiseMega, 0),
      .enemyMonElevation = 0,
    }, //BlastoiseMega,
[SPECIES_BEEDRILL_MEGA] = 
    {  
      //FRONT_PIC(BeedrillMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BeedrillMega),
      BACK_COORD(0x88,0),
      //PALETTES(BeedrillMega),
      PIC_DATA_ICON_INDEX(BeedrillMega,0),
      //ICON(BeedrillMega, 0),
      .enemyMonElevation = 0,
    }, //BeedrillMega,
[SPECIES_PIDGEOT_MEGA] = 
    {  
      //FRONT_PIC(PidgeotMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PidgeotMega),
      BACK_COORD(0x88,0),
      //PALETTES(PidgeotMega),
      PIC_DATA_ICON_INDEX(PidgeotMega,0),
      //ICON(PidgeotMega, 0),
      .enemyMonElevation = 0,
    }, //PidgeotMega,
[SPECIES_ALAKAZAM_MEGA] = 
    {  
      //FRONT_PIC(AlakazamMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlakazamMega),
      BACK_COORD(0x88,0),
      //PALETTES(AlakazamMega),
      PIC_DATA_ICON_INDEX(AlakazamMega,0),
      //ICON(AlakazamMega, 0),
      .enemyMonElevation = 0,
    }, //AlakazamMega,
[SPECIES_SLOWBRO_MEGA] = 
    {  
      //FRONT_PIC(SlowbroMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SlowbroMega),
      BACK_COORD(0x88,0),
      //PALETTES(SlowbroMega),
      PIC_DATA_ICON_INDEX(SlowbroMega,0),
      //ICON(SlowbroMega, 0),
      .enemyMonElevation = 0,
    }, //SlowbroMega,
[SPECIES_GENGAR_MEGA] = 
    {  
      //FRONT_PIC(GengarMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GengarMega),
      BACK_COORD(0x88,0),
      //PALETTES(GengarMega),
      PIC_DATA_ICON_INDEX(GengarMega,0),
      //ICON(GengarMega, 0),
      .enemyMonElevation = 0,
    }, //GengarMega,
[SPECIES_KANGASKHAN_MEGA] = 
    {  
      //FRONT_PIC(KangaskhanMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(KangaskhanMega),
      BACK_COORD(0x88,0),
      //PALETTES(KangaskhanMega),
      PIC_DATA_ICON_INDEX(KangaskhanMega,0),
      //ICON(KangaskhanMega, 0),
      .enemyMonElevation = 0,
    }, //KangaskhanMega,
[SPECIES_PINSIR_MEGA] = 
    {  
      //FRONT_PIC(PinsirMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PinsirMega),
      BACK_COORD(0x88,0),
      //PALETTES(PinsirMega),
      PIC_DATA_ICON_INDEX(PinsirMega,0),
      //ICON(PinsirMega, 0),
      .enemyMonElevation = 0,
    }, //PinsirMega,
[SPECIES_GYARADOS_MEGA] = 
    {  
      //FRONT_PIC(GyaradosMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GyaradosMega),
      BACK_COORD(0x88,0),
      //PALETTES(GyaradosMega),
      PIC_DATA_ICON_INDEX(GyaradosMega,0),
      //ICON(GyaradosMega, 0),
      .enemyMonElevation = 0,
    }, //GyaradosMega,
[SPECIES_AERODACTYL_MEGA] = 
    {  
      //FRONT_PIC(AerodactylMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AerodactylMega),
      BACK_COORD(0x88,0),
      //PALETTES(AerodactylMega),
      PIC_DATA_ICON_INDEX(AerodactylMega,0),
      //ICON(AerodactylMega, 0),
      .enemyMonElevation = 0,
    }, //AerodactylMega,
[SPECIES_MEWTWO_MEGA_X] = 
    {  
      //FRONT_PIC(MewtwoMegaX),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MewtwoMegaX),
      BACK_COORD(0x88,0),
      //PALETTES(MewtwoMegaX),
      PIC_DATA_ICON_INDEX(MewtwoMegaX,0),
      //ICON(MewtwoMegaX, 0),
      .enemyMonElevation = 0,
    }, //MewtwoMegaX,
[SPECIES_MEWTWO_MEGA_Y] = 
    {  
      //FRONT_PIC(MewtwoMegaY),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MewtwoMegaY),
      BACK_COORD(0x88,0),
      //PALETTES(MewtwoMegaY),
      PIC_DATA_ICON_INDEX(MewtwoMegaY,0),
      //ICON(MewtwoMegaY, 0),
      .enemyMonElevation = 0,
    }, //MewtwoMegaY,
[SPECIES_AMPHAROS_MEGA] = 
    {  
      //FRONT_PIC(AmpharosMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AmpharosMega),
      BACK_COORD(0x88,0),
      //PALETTES(AmpharosMega),
      PIC_DATA_ICON_INDEX(AmpharosMega,0),
      //ICON(AmpharosMega, 0),
      .enemyMonElevation = 0,
    }, //AmpharosMega,
[SPECIES_STEELIX_MEGA] = 
    {  
      //FRONT_PIC(SteelixMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SteelixMega),
      BACK_COORD(0x88,0),
      //PALETTES(SteelixMega),
      PIC_DATA_ICON_INDEX(SteelixMega,0),
      //ICON(SteelixMega, 0),
      .enemyMonElevation = 0,
    }, //SteelixMega,
[SPECIES_SCIZOR_MEGA] = 
    {  
      //FRONT_PIC(ScizorMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ScizorMega),
      BACK_COORD(0x88,0),
      //PALETTES(ScizorMega),
      PIC_DATA_ICON_INDEX(ScizorMega,0),
      //ICON(ScizorMega, 0),
      .enemyMonElevation = 0,
    }, //ScizorMega,
[SPECIES_HERACROSS_MEGA] = 
    {  
      //FRONT_PIC(HeracrossMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(HeracrossMega),
      BACK_COORD(0x88,0),
      //PALETTES(HeracrossMega),
      PIC_DATA_ICON_INDEX(HeracrossMega,0),
      //ICON(HeracrossMega, 0),
      .enemyMonElevation = 0,
    }, //HeracrossMega,
[SPECIES_HOUNDOOM_MEGA] = 
    {  
      //FRONT_PIC(HoundoomMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(HoundoomMega),
      BACK_COORD(0x88,0),
      //PALETTES(HoundoomMega),
      PIC_DATA_ICON_INDEX(HoundoomMega,0),
      //ICON(HoundoomMega, 0),
      .enemyMonElevation = 0,
    }, //HoundoomMega,
[SPECIES_TYRANITAR_MEGA] = 
    {  
      //FRONT_PIC(TyranitarMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TyranitarMega),
      BACK_COORD(0x88,0),
      //PALETTES(TyranitarMega),
      PIC_DATA_ICON_INDEX(TyranitarMega,0),
      //ICON(TyranitarMega, 0),
      .enemyMonElevation = 0,
    }, //TyranitarMega,
[SPECIES_SCEPTILE_MEGA] = 
    {  
      //FRONT_PIC(SceptileMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SceptileMega),
      BACK_COORD(0x88,0),
      //PALETTES(SceptileMega),
      PIC_DATA_ICON_INDEX(SceptileMega,0),
      //ICON(SceptileMega, 0),
      .enemyMonElevation = 0,
    }, //SceptileMega,
[SPECIES_BLAZIKEN_MEGA] = 
    {  
      //FRONT_PIC(BlazikenMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BlazikenMega),
      BACK_COORD(0x88,0),
      //PALETTES(BlazikenMega),
      PIC_DATA_ICON_INDEX(BlazikenMega,0),
      //ICON(BlazikenMega, 0),
      .enemyMonElevation = 0,
    }, //BlazikenMega,
[SPECIES_SWAMPERT_MEGA] = 
    {  
      //FRONT_PIC(SwampertMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SwampertMega),
      BACK_COORD(0x88,0),
      //PALETTES(SwampertMega),
      PIC_DATA_ICON_INDEX(SwampertMega,0),
      //ICON(SwampertMega, 0),
      .enemyMonElevation = 0,
    }, //SwampertMega,
[SPECIES_GARDEVOIR_MEGA] = 
    {  
      //FRONT_PIC(GardevoirMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GardevoirMega),
      BACK_COORD(0x88,0),
      //PALETTES(GardevoirMega),
      PIC_DATA_ICON_INDEX(GardevoirMega,0),
      //ICON(GardevoirMega, 0),
      .enemyMonElevation = 0,
    }, //GardevoirMega,
[SPECIES_SABLEYE_MEGA] = 
    {  
      //FRONT_PIC(SableyeMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SableyeMega),
      BACK_COORD(0x88,0),
      //PALETTES(SableyeMega),
      PIC_DATA_ICON_INDEX(SableyeMega,0),
      //ICON(SableyeMega, 0),
      .enemyMonElevation = 0,
    }, //SableyeMega,
[SPECIES_MAWILE_MEGA] = 
    {  
      //FRONT_PIC(MawileMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MawileMega),
      BACK_COORD(0x88,0),
      //PALETTES(MawileMega),
      PIC_DATA_ICON_INDEX(MawileMega,0),
      //ICON(MawileMega, 0),
      .enemyMonElevation = 0,
    }, //MawileMega,
[SPECIES_AGGRON_MEGA] = 
    {  
      //FRONT_PIC(AggronMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AggronMega),
      BACK_COORD(0x88,0),
      //PALETTES(AggronMega),
      PIC_DATA_ICON_INDEX(AggronMega,0),
      //ICON(AggronMega, 0),
      .enemyMonElevation = 0,
    }, //AggronMega,
[SPECIES_MEDICHAM_MEGA] = 
    {  
      //FRONT_PIC(MedichamMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MedichamMega),
      BACK_COORD(0x88,0),
      //PALETTES(MedichamMega),
      PIC_DATA_ICON_INDEX(MedichamMega,0),
      //ICON(MedichamMega, 0),
      .enemyMonElevation = 0,
    }, //MedichamMega,
[SPECIES_MANECTRIC_MEGA] = 
    {  
      //FRONT_PIC(ManectricMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ManectricMega),
      BACK_COORD(0x88,0),
      //PALETTES(ManectricMega),
      PIC_DATA_ICON_INDEX(ManectricMega,0),
      //ICON(ManectricMega, 0),
      .enemyMonElevation = 0,
    }, //ManectricMega,
[SPECIES_SHARPEDO_MEGA] = 
    {  
      //FRONT_PIC(SharpedoMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SharpedoMega),
      BACK_COORD(0x88,0),
      //PALETTES(SharpedoMega),
      PIC_DATA_ICON_INDEX(SharpedoMega,0),
      //ICON(SharpedoMega, 0),
      .enemyMonElevation = 0,
    }, //SharpedoMega,
[SPECIES_CAMERUPT_MEGA] = 
    {  
      //FRONT_PIC(CameruptMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CameruptMega),
      BACK_COORD(0x88,0),
      //PALETTES(CameruptMega),
      PIC_DATA_ICON_INDEX(CameruptMega,0),
      //ICON(CameruptMega, 0),
      .enemyMonElevation = 0,
    }, //CameruptMega,
[SPECIES_ALTARIA_MEGA] = 
    {  
      //FRONT_PIC(AltariaMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AltariaMega),
      BACK_COORD(0x88,0),
      //PALETTES(AltariaMega),
      PIC_DATA_ICON_INDEX(AltariaMega,0),
      //ICON(AltariaMega, 0),
      .enemyMonElevation = 0,
    }, //AltariaMega,
[SPECIES_BANETTE_MEGA] = 
    {  
      //FRONT_PIC(BanetteMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BanetteMega),
      BACK_COORD(0x88,0),
      //PALETTES(BanetteMega),
      PIC_DATA_ICON_INDEX(BanetteMega,0),
      //ICON(BanetteMega, 0),
      .enemyMonElevation = 0,
    }, //BanetteMega,
[SPECIES_ABSOL_MEGA] = 
    {  
      //FRONT_PIC(AbsolMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AbsolMega),
      BACK_COORD(0x88,0),
      //PALETTES(AbsolMega),
      PIC_DATA_ICON_INDEX(AbsolMega,0),
      //ICON(AbsolMega, 0),
      .enemyMonElevation = 0,
    }, //AbsolMega,
[SPECIES_GLALIE_MEGA] = 
    {  
      //FRONT_PIC(GlalieMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GlalieMega),
      BACK_COORD(0x88,0),
      //PALETTES(GlalieMega),
      PIC_DATA_ICON_INDEX(GlalieMega,0),
      //ICON(GlalieMega, 0),
      .enemyMonElevation = 0,
    }, //GlalieMega,
[SPECIES_SALAMENCE_MEGA] = 
    {  
      //FRONT_PIC(SalamenceMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SalamenceMega),
      BACK_COORD(0x88,0),
      //PALETTES(SalamenceMega),
      PIC_DATA_ICON_INDEX(SalamenceMega,0),
      //ICON(SalamenceMega, 0),
      .enemyMonElevation = 0,
    }, //SalamenceMega,
[SPECIES_METAGROSS_MEGA] = 
    {  
      //FRONT_PIC(MetagrossMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MetagrossMega),
      BACK_COORD(0x88,0),
      //PALETTES(MetagrossMega),
      PIC_DATA_ICON_INDEX(MetagrossMega,0),
      //ICON(MetagrossMega, 0),
      .enemyMonElevation = 0,
    }, //MetagrossMega,
[SPECIES_LATIAS_MEGA] = 
    {  
      //FRONT_PIC(LatiasMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LatiasMega),
      BACK_COORD(0x88,0),
      //PALETTES(LatiasMega),
      PIC_DATA_ICON_INDEX(LatiasMega,0),
      //ICON(LatiasMega, 0),
      .enemyMonElevation = 0,
    }, //LatiasMega,
[SPECIES_LATIOS_MEGA] = 
    {  
      //FRONT_PIC(LatiosMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LatiosMega),
      BACK_COORD(0x88,0),
      //PALETTES(LatiosMega),
      PIC_DATA_ICON_INDEX(LatiosMega,0),
      //ICON(LatiosMega, 0),
      .enemyMonElevation = 0,
    }, //LatiosMega,
[SPECIES_LOPUNNY_MEGA] = 
    {  
      //FRONT_PIC(LopunnyMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LopunnyMega),
      BACK_COORD(0x88,0),
      //PALETTES(LopunnyMega),
      PIC_DATA_ICON_INDEX(LopunnyMega,0),
      //ICON(LopunnyMega, 0),
      .enemyMonElevation = 0,
    }, //LopunnyMega,
[SPECIES_GARCHOMP_MEGA] = 
    {  
      //FRONT_PIC(GarchompMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GarchompMega),
      BACK_COORD(0x88,0),
      //PALETTES(GarchompMega),
      PIC_DATA_ICON_INDEX(GarchompMega,0),
      //ICON(GarchompMega, 0),
      .enemyMonElevation = 0,
    }, //GarchompMega,
[SPECIES_LUCARIO_MEGA] = 
    {  
      //FRONT_PIC(LucarioMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LucarioMega),
      BACK_COORD(0x88,0),
      //PALETTES(LucarioMega),
      PIC_DATA_ICON_INDEX(LucarioMega,0),
      //ICON(LucarioMega, 0),
      .enemyMonElevation = 0,
    }, //LucarioMega,
[SPECIES_ABOMASNOW_MEGA] = 
    {  
      //FRONT_PIC(AbomasnowMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AbomasnowMega),
      BACK_COORD(0x88,0),
      //PALETTES(AbomasnowMega),
      PIC_DATA_ICON_INDEX(AbomasnowMega,0),
      //ICON(AbomasnowMega, 0),
      .enemyMonElevation = 0,
    }, //AbomasnowMega,
[SPECIES_GALLADE_MEGA] = 
    {  
      //FRONT_PIC(GalladeMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GalladeMega),
      BACK_COORD(0x88,0),
      //PALETTES(GalladeMega),
      PIC_DATA_ICON_INDEX(GalladeMega,0),
      //ICON(GalladeMega, 0),
      .enemyMonElevation = 0,
    }, //GalladeMega,
[SPECIES_AUDINO_MEGA] = 
    {  
      //FRONT_PIC(AudinoMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AudinoMega),
      BACK_COORD(0x88,0),
      //PALETTES(AudinoMega),
      PIC_DATA_ICON_INDEX(AudinoMega,0),
      //ICON(AudinoMega, 0),
      .enemyMonElevation = 0,
    }, //AudinoMega,
[SPECIES_DIANCIE_MEGA] = 
    {  
      //FRONT_PIC(DiancieMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DiancieMega),
      BACK_COORD(0x88,0),
      //PALETTES(DiancieMega),
      PIC_DATA_ICON_INDEX(DiancieMega,0),
      //ICON(DiancieMega, 0),
      .enemyMonElevation = 0,
    }, //DiancieMega,
[SPECIES_RAYQUAZA_MEGA] = 
    {  
      //FRONT_PIC(RayquazaMega),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RayquazaMega),
      BACK_COORD(0x88,0),
      //PALETTES(RayquazaMega),
      PIC_DATA_ICON_INDEX(RayquazaMega,0),
      //ICON(RayquazaMega, 0),
      .enemyMonElevation = 0,
    }, //RayquazaMega,
[SPECIES_KYOGRE_PRIMAL] = 
    {  
      //FRONT_PIC(KyogrePrimal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(KyogrePrimal),
      BACK_COORD(0x88,0),
      //PALETTES(KyogrePrimal),
      PIC_DATA_ICON_INDEX(KyogrePrimal,0),
      //ICON(KyogrePrimal, 0),
      .enemyMonElevation = 0,
    }, //KyogrePrimal,
[SPECIES_GROUDON_PRIMAL] = 
    {  
      //FRONT_PIC(GroudonPrimal),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GroudonPrimal),
      BACK_COORD(0x88,0),
      //PALETTES(GroudonPrimal),
      PIC_DATA_ICON_INDEX(GroudonPrimal,0),
      //ICON(GroudonPrimal, 0),
      .enemyMonElevation = 0,
    }, //GroudonPrimal,
[SPECIES_RATTATA_ALOLAN] = 
    {  
      //FRONT_PIC(RattataAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RattataAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(RattataAlolan),
      PIC_DATA_ICON_INDEX(RattataAlolan,0),
      //ICON(RattataAlolan, 0),
      .enemyMonElevation = 0,
    }, //RattataAlolan,
[SPECIES_RATICATE_ALOLAN] = 
    {  
      //FRONT_PIC(RaticateAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RaticateAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(RaticateAlolan),
      PIC_DATA_ICON_INDEX(RaticateAlolan,0),
      //ICON(RaticateAlolan, 0),
      .enemyMonElevation = 0,
    }, //RaticateAlolan,
[SPECIES_RAICHU_ALOLAN] = 
    {  
      //FRONT_PIC(RaichuAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RaichuAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(RaichuAlolan),
      PIC_DATA_ICON_INDEX(RaichuAlolan,0),
      //ICON(RaichuAlolan, 0),
      .enemyMonElevation = 0,
    }, //RaichuAlolan,
[SPECIES_SANDSHREW_ALOLAN] = 
    {  
      //FRONT_PIC(SandshrewAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SandshrewAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(SandshrewAlolan),
      PIC_DATA_ICON_INDEX(SandshrewAlolan,0),
      //ICON(SandshrewAlolan, 0),
      .enemyMonElevation = 0,
    }, //SandshrewAlolan,
[SPECIES_SANDSLASH_ALOLAN] = 
    {  
      //FRONT_PIC(SandslashAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SandslashAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(SandslashAlolan),
      PIC_DATA_ICON_INDEX(SandslashAlolan,0),
      //ICON(SandslashAlolan, 0),
      .enemyMonElevation = 0,
    }, //SandslashAlolan,
[SPECIES_VULPIX_ALOLAN] = 
    {  
      //FRONT_PIC(VulpixAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VulpixAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(VulpixAlolan),
      PIC_DATA_ICON_INDEX(VulpixAlolan,0),
      //ICON(VulpixAlolan, 0),
      .enemyMonElevation = 0,
    }, //VulpixAlolan,
[SPECIES_NINETALES_ALOLAN] = 
    {  
      //FRONT_PIC(NinetalesAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(NinetalesAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(NinetalesAlolan),
      PIC_DATA_ICON_INDEX(NinetalesAlolan,0),
      //ICON(NinetalesAlolan, 0),
      .enemyMonElevation = 0,
    }, //NinetalesAlolan,
[SPECIES_DIGLETT_ALOLAN] = 
    {  
      //FRONT_PIC(DiglettAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DiglettAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(DiglettAlolan),
      PIC_DATA_ICON_INDEX(DiglettAlolan,0),
      //ICON(DiglettAlolan, 0),
      .enemyMonElevation = 0,
    }, //DiglettAlolan,
[SPECIES_DUGTRIO_ALOLAN] = 
    {  
      //FRONT_PIC(DugtrioAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DugtrioAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(DugtrioAlolan),
      PIC_DATA_ICON_INDEX(DugtrioAlolan,0),
      //ICON(DugtrioAlolan, 0),
      .enemyMonElevation = 0,
    }, //DugtrioAlolan,
[SPECIES_MEOWTH_ALOLAN] = 
    {  
      //FRONT_PIC(MeowthAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MeowthAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(MeowthAlolan),
      PIC_DATA_ICON_INDEX(MeowthAlolan,0),
      //ICON(MeowthAlolan, 0),
      .enemyMonElevation = 0,
    }, //MeowthAlolan,
[SPECIES_PERSIAN_ALOLAN] = 
    {  
      //FRONT_PIC(PersianAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PersianAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(PersianAlolan),
      PIC_DATA_ICON_INDEX(PersianAlolan,0),
      //ICON(PersianAlolan, 0),
      .enemyMonElevation = 0,
    }, //PersianAlolan,
[SPECIES_GEODUDE_ALOLAN] = 
    {  
      //FRONT_PIC(GeodudeAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GeodudeAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(GeodudeAlolan),
      PIC_DATA_ICON_INDEX(GeodudeAlolan,0),
      //ICON(GeodudeAlolan, 0),
      .enemyMonElevation = 0,
    }, //GeodudeAlolan,
[SPECIES_GRAVELER_ALOLAN] = 
    {  
      //FRONT_PIC(GravelerAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GravelerAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(GravelerAlolan),
      PIC_DATA_ICON_INDEX(GravelerAlolan,0),
      //ICON(GravelerAlolan, 0),
      .enemyMonElevation = 0,
    }, //GravelerAlolan,
[SPECIES_GOLEM_ALOLAN] = 
    {  
      //FRONT_PIC(GolemAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GolemAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(GolemAlolan),
      PIC_DATA_ICON_INDEX(GolemAlolan,0),
      //ICON(GolemAlolan, 0),
      .enemyMonElevation = 0,
    }, //GolemAlolan,
[SPECIES_GRIMER_ALOLAN] = 
    {  
      //FRONT_PIC(GrimerAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GrimerAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(GrimerAlolan),
      PIC_DATA_ICON_INDEX(GrimerAlolan,0),
      //ICON(GrimerAlolan, 0),
      .enemyMonElevation = 0,
    }, //GrimerAlolan,
[SPECIES_MUK_ALOLAN] = 
    {  
      //FRONT_PIC(MukAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MukAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(MukAlolan),
      PIC_DATA_ICON_INDEX(MukAlolan,0),
      //ICON(MukAlolan, 0),
      .enemyMonElevation = 0,
    }, //MukAlolan,
[SPECIES_EXEGGUTOR_ALOLAN] = 
    {  
      //FRONT_PIC(ExeggutorAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ExeggutorAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(ExeggutorAlolan),
      PIC_DATA_ICON_INDEX(ExeggutorAlolan,0),
      //ICON(ExeggutorAlolan, 0),
      .enemyMonElevation = 0,
    }, //ExeggutorAlolan,
[SPECIES_MAROWAK_ALOLAN] = 
    {  
      //FRONT_PIC(MarowakAlolan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MarowakAlolan),
      BACK_COORD(0x88,0),
      //PALETTES(MarowakAlolan),
      PIC_DATA_ICON_INDEX(MarowakAlolan,0),
      //ICON(MarowakAlolan, 0),
      .enemyMonElevation = 0,
    }, //MarowakAlolan,
[SPECIES_MEOWTH_GALARIAN] = 
    {  
      //FRONT_PIC(MeowthGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MeowthGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(MeowthGalarian),
      PIC_DATA_ICON_INDEX(MeowthGalarian,0),
      //ICON(MeowthGalarian, 0),
      .enemyMonElevation = 0,
    }, //MeowthGalarian,
[SPECIES_PONYTA_GALARIAN] = 
    {  
      //FRONT_PIC(PonytaGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PonytaGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(PonytaGalarian),
      PIC_DATA_ICON_INDEX(PonytaGalarian,0),
      //ICON(PonytaGalarian, 0),
      .enemyMonElevation = 0,
    }, //PonytaGalarian,
[SPECIES_RAPIDASH_GALARIAN] = 
    {  
      //FRONT_PIC(RapidashGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RapidashGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(RapidashGalarian),
      PIC_DATA_ICON_INDEX(RapidashGalarian,0),
      //ICON(RapidashGalarian, 0),
      .enemyMonElevation = 0,
    }, //RapidashGalarian,
[SPECIES_SLOWPOKE_GALARIAN] = 
    {  
      //FRONT_PIC(SlowpokeGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SlowpokeGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(SlowpokeGalarian),
      PIC_DATA_ICON_INDEX(SlowpokeGalarian,0),
      //ICON(SlowpokeGalarian, 0),
      .enemyMonElevation = 0,
    }, //SlowpokeGalarian,
[SPECIES_SLOWBRO_GALARIAN] = 
    {  
      //FRONT_PIC(SlowbroGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SlowbroGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(SlowbroGalarian),
      PIC_DATA_ICON_INDEX(SlowbroGalarian,0),
      //ICON(SlowbroGalarian, 0),
      .enemyMonElevation = 0,
    }, //SlowbroGalarian,
[SPECIES_FARFETCHD_GALARIAN] = 
    {  
      //FRONT_PIC(FarfetchdGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FarfetchdGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(FarfetchdGalarian),
      PIC_DATA_ICON_INDEX(FarfetchdGalarian,0),
      //ICON(FarfetchdGalarian, 0),
      .enemyMonElevation = 0,
    }, //FarfetchdGalarian,
[SPECIES_WEEZING_GALARIAN] = 
    {  
      //FRONT_PIC(WeezingGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WeezingGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(WeezingGalarian),
      PIC_DATA_ICON_INDEX(WeezingGalarian,0),
      //ICON(WeezingGalarian, 0),
      .enemyMonElevation = 0,
    }, //WeezingGalarian,
[SPECIES_MR_MIME_GALARIAN] = 
    {  
      //FRONT_PIC(MrMimeGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MrMimeGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(MrMimeGalarian),
      PIC_DATA_ICON_INDEX(MrMimeGalarian,0),
      //ICON(MrMimeGalarian, 0),
      .enemyMonElevation = 0,
    }, //MrMimeGalarian,
[SPECIES_ARTICUNO_GALARIAN] = 
    {  
      //FRONT_PIC(ArticunoGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArticunoGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(ArticunoGalarian),
      PIC_DATA_ICON_INDEX(ArticunoGalarian,0),
      //ICON(ArticunoGalarian, 0),
      .enemyMonElevation = 0,
    }, //ArticunoGalarian,
[SPECIES_ZAPDOS_GALARIAN] = 
    {  
      //FRONT_PIC(ZapdosGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZapdosGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(ZapdosGalarian),
      PIC_DATA_ICON_INDEX(ZapdosGalarian,0),
      //ICON(ZapdosGalarian, 0),
      .enemyMonElevation = 0,
    }, //ZapdosGalarian,
[SPECIES_MOLTRES_GALARIAN] = 
    {  
      //FRONT_PIC(MoltresGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MoltresGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(MoltresGalarian),
      PIC_DATA_ICON_INDEX(MoltresGalarian,0),
      //ICON(MoltresGalarian, 0),
      .enemyMonElevation = 0,
    }, //MoltresGalarian,
[SPECIES_SLOWKING_GALARIAN] = 
    {  
      //FRONT_PIC(SlowkingGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SlowkingGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(SlowkingGalarian),
      PIC_DATA_ICON_INDEX(SlowkingGalarian,0),
      //ICON(SlowkingGalarian, 0),
      .enemyMonElevation = 0,
    }, //SlowkingGalarian,
[SPECIES_CORSOLA_GALARIAN] = 
    {  
      //FRONT_PIC(CorsolaGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CorsolaGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(CorsolaGalarian),
      PIC_DATA_ICON_INDEX(CorsolaGalarian,0),
      //ICON(CorsolaGalarian, 0),
      .enemyMonElevation = 0,
    }, //CorsolaGalarian,
[SPECIES_ZIGZAGOON_GALARIAN] = 
    {  
      //FRONT_PIC(ZigzagoonGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZigzagoonGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(ZigzagoonGalarian),
      PIC_DATA_ICON_INDEX(ZigzagoonGalarian,0),
      //ICON(ZigzagoonGalarian, 0),
      .enemyMonElevation = 0,
    }, //ZigzagoonGalarian,
[SPECIES_LINOONE_GALARIAN] = 
    {  
      //FRONT_PIC(LinooneGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LinooneGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(LinooneGalarian),
      PIC_DATA_ICON_INDEX(LinooneGalarian,0),
      //ICON(LinooneGalarian, 0),
      .enemyMonElevation = 0,
    }, //LinooneGalarian,
[SPECIES_DARUMAKA_GALARIAN] = 
    {  
      //FRONT_PIC(DarumakaGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DarumakaGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(DarumakaGalarian),
      PIC_DATA_ICON_INDEX(DarumakaGalarian,0),
      //ICON(DarumakaGalarian, 0),
      .enemyMonElevation = 0,
    }, //DarumakaGalarian,
[SPECIES_DARMANITAN_GALARIAN] = 
    {  
      //FRONT_PIC(DarmanitanGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DarmanitanGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(DarmanitanGalarian),
      PIC_DATA_ICON_INDEX(DarmanitanGalarian,0),
      //ICON(DarmanitanGalarian, 0),
      .enemyMonElevation = 0,
    }, //DarmanitanGalarian,
[SPECIES_YAMASK_GALARIAN] = 
    {  
      //FRONT_PIC(YamaskGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(YamaskGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(YamaskGalarian),
      PIC_DATA_ICON_INDEX(YamaskGalarian,0),
      //ICON(YamaskGalarian, 0),
      .enemyMonElevation = 0,
    }, //YamaskGalarian,
[SPECIES_STUNFISK_GALARIAN] = 
    {  
      //FRONT_PIC(StunfiskGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(StunfiskGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(StunfiskGalarian),
      PIC_DATA_ICON_INDEX(StunfiskGalarian,0),
      //ICON(StunfiskGalarian, 0),
      .enemyMonElevation = 0,
    }, //StunfiskGalarian,
[SPECIES_GROWLITHE_HISUIAN] = 
    {  
      //FRONT_PIC(GrowlitheHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GrowlitheHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(GrowlitheHisuian),
      PIC_DATA_ICON_INDEX(GrowlitheHisuian,0),
      //ICON(GrowlitheHisuian, 0),
      .enemyMonElevation = 0,
    }, //GrowlitheHisuian,
[SPECIES_ARCANINE_HISUIAN] = 
    {  
      //FRONT_PIC(ArcanineHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArcanineHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(ArcanineHisuian),
      PIC_DATA_ICON_INDEX(ArcanineHisuian,0),
      //ICON(ArcanineHisuian, 0),
      .enemyMonElevation = 0,
    }, //ArcanineHisuian,
[SPECIES_VOLTORB_HISUIAN] = 
    {  
      //FRONT_PIC(VoltorbHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VoltorbHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(VoltorbHisuian),
      PIC_DATA_ICON_INDEX(VoltorbHisuian,0),
      //ICON(VoltorbHisuian, 0),
      .enemyMonElevation = 0,
    }, //VoltorbHisuian,
[SPECIES_ELECTRODE_HISUIAN] = 
    {  
      //FRONT_PIC(ElectrodeHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ElectrodeHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(ElectrodeHisuian),
      PIC_DATA_ICON_INDEX(ElectrodeHisuian,0),
      //ICON(ElectrodeHisuian, 0),
      .enemyMonElevation = 0,
    }, //ElectrodeHisuian,
[SPECIES_TYPHLOSION_HISUIAN] = 
    {  
      //FRONT_PIC(TyphlosionHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TyphlosionHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(TyphlosionHisuian),
      PIC_DATA_ICON_INDEX(TyphlosionHisuian,0),
      //ICON(TyphlosionHisuian, 0),
      .enemyMonElevation = 0,
    }, //TyphlosionHisuian,
[SPECIES_QWILFISH_HISUIAN] = 
    {  
      //FRONT_PIC(QwilfishHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(QwilfishHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(QwilfishHisuian),
      PIC_DATA_ICON_INDEX(QwilfishHisuian,0),
      //ICON(QwilfishHisuian, 0),
      .enemyMonElevation = 0,
    }, //QwilfishHisuian,
[SPECIES_SNEASEL_HISUIAN] = 
    {  
      //FRONT_PIC(SneaselHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SneaselHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(SneaselHisuian),
      PIC_DATA_ICON_INDEX(SneaselHisuian,0),
      //ICON(SneaselHisuian, 0),
      .enemyMonElevation = 0,
    }, //SneaselHisuian,
[SPECIES_SAMUROTT_HISUIAN] = 
    {  
      //FRONT_PIC(SamurottHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SamurottHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(SamurottHisuian),
      PIC_DATA_ICON_INDEX(SamurottHisuian,0),
      //ICON(SamurottHisuian, 0),
      .enemyMonElevation = 0,
    }, //SamurottHisuian,
[SPECIES_LILLIGANT_HISUIAN] = 
    {  
      //FRONT_PIC(LilligantHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LilligantHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(LilligantHisuian),
      PIC_DATA_ICON_INDEX(LilligantHisuian,0),
      //ICON(LilligantHisuian, 0),
      .enemyMonElevation = 0,
    }, //LilligantHisuian,
[SPECIES_ZORUA_HISUIAN] = 
    {  
      //FRONT_PIC(ZoruaHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZoruaHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(ZoruaHisuian),
      PIC_DATA_ICON_INDEX(ZoruaHisuian,0),
      //ICON(ZoruaHisuian, 0),
      .enemyMonElevation = 0,
    }, //ZoruaHisuian,
[SPECIES_ZOROARK_HISUIAN] = 
    {  
      //FRONT_PIC(ZoroarkHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZoroarkHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(ZoroarkHisuian),
      PIC_DATA_ICON_INDEX(ZoroarkHisuian,0),
      //ICON(ZoroarkHisuian, 0),
      .enemyMonElevation = 0,
    }, //ZoroarkHisuian,
[SPECIES_BRAVIARY_HISUIAN] = 
    {  
      //FRONT_PIC(BraviaryHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BraviaryHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(BraviaryHisuian),
      PIC_DATA_ICON_INDEX(BraviaryHisuian,0),
      //ICON(BraviaryHisuian, 0),
      .enemyMonElevation = 0,
    }, //BraviaryHisuian,
[SPECIES_SLIGGOO_HISUIAN] = 
    {  
      //FRONT_PIC(SliggooHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SliggooHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(SliggooHisuian),
      PIC_DATA_ICON_INDEX(SliggooHisuian,0),
      //ICON(SliggooHisuian, 0),
      .enemyMonElevation = 0,
    }, //SliggooHisuian,
[SPECIES_GOODRA_HISUIAN] = 
    {  
      //FRONT_PIC(GoodraHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GoodraHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(GoodraHisuian),
      PIC_DATA_ICON_INDEX(GoodraHisuian,0),
      //ICON(GoodraHisuian, 0),
      .enemyMonElevation = 0,
    }, //GoodraHisuian,
[SPECIES_AVALUGG_HISUIAN] = 
    {  
      //FRONT_PIC(AvaluggHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AvaluggHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(AvaluggHisuian),
      PIC_DATA_ICON_INDEX(AvaluggHisuian,0),
      //ICON(AvaluggHisuian, 0),
      .enemyMonElevation = 0,
    }, //AvaluggHisuian,
[SPECIES_DECIDUEYE_HISUIAN] = 
    {  
      //FRONT_PIC(DecidueyeHisuian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DecidueyeHisuian),
      BACK_COORD(0x88,0),
      //PALETTES(DecidueyeHisuian),
      PIC_DATA_ICON_INDEX(DecidueyeHisuian,0),
      //ICON(DecidueyeHisuian, 0),
      .enemyMonElevation = 0,
    }, //DecidueyeHisuian,
[SPECIES_PIKACHU_COSPLAY] = 
    {  
      //FRONT_PIC(PikachuCosplay),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuCosplay),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuCosplay),
      PIC_DATA_ICON_INDEX(PikachuCosplay,0),
      //ICON(PikachuCosplay, 0),
      .enemyMonElevation = 0,
    }, //PikachuCosplay,
[SPECIES_PIKACHU_ROCK_STAR] = 
    {  
      //FRONT_PIC(PikachuRockStar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuRockStar),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuRockStar),
      PIC_DATA_ICON_INDEX(PikachuRockStar,0),
      //ICON(PikachuRockStar, 0),
      .enemyMonElevation = 0,
    }, //PikachuRockStar,
[SPECIES_PIKACHU_BELLE] = 
    {  
      //FRONT_PIC(PikachuBelle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuBelle),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuBelle),
      PIC_DATA_ICON_INDEX(PikachuBelle,0),
      //ICON(PikachuBelle, 0),
      .enemyMonElevation = 0,
    }, //PikachuBelle,
[SPECIES_PIKACHU_POP_STAR] = 
    {  
      //FRONT_PIC(PikachuPopStar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuPopStar),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuPopStar),
      PIC_DATA_ICON_INDEX(PikachuPopStar,0),
      //ICON(PikachuPopStar, 0),
      .enemyMonElevation = 0,
    }, //PikachuPopStar,
[SPECIES_PIKACHU_PH_D] = 
    {  
      //FRONT_PIC(PikachuPhD),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuPhD),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuPhD),
      PIC_DATA_ICON_INDEX(PikachuPhD,0),
      //ICON(PikachuPhD, 0),
      .enemyMonElevation = 0,
    }, //PikachuPhD,
[SPECIES_PIKACHU_LIBRE] = 
    {  
      //FRONT_PIC(PikachuLibre),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuLibre),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuLibre),
      PIC_DATA_ICON_INDEX(PikachuLibre,0),
      //ICON(PikachuLibre, 0),
      .enemyMonElevation = 0,
    }, //PikachuLibre,
[SPECIES_PIKACHU_ORIGINAL_CAP] = 
    {  
      //FRONT_PIC(PikachuOriginalCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuOriginalCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuOriginalCap),
      PIC_DATA_ICON_INDEX(PikachuOriginalCap,0),
      //ICON(PikachuOriginalCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuOriginalCap,
[SPECIES_PIKACHU_HOENN_CAP] = 
    {  
      //FRONT_PIC(PikachuHoennCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuHoennCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuHoennCap),
      PIC_DATA_ICON_INDEX(PikachuHoennCap,0),
      //ICON(PikachuHoennCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuHoennCap,
[SPECIES_PIKACHU_SINNOH_CAP] = 
    {  
      //FRONT_PIC(PikachuSinnohCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuSinnohCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuSinnohCap),
      PIC_DATA_ICON_INDEX(PikachuSinnohCap,0),
      //ICON(PikachuSinnohCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuSinnohCap,
[SPECIES_PIKACHU_UNOVA_CAP] = 
    {  
      //FRONT_PIC(PikachuUnovaCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuUnovaCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuUnovaCap),
      PIC_DATA_ICON_INDEX(PikachuUnovaCap,0),
      //ICON(PikachuUnovaCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuUnovaCap,
[SPECIES_PIKACHU_KALOS_CAP] = 
    {  
      //FRONT_PIC(PikachuKalosCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuKalosCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuKalosCap),
      PIC_DATA_ICON_INDEX(PikachuKalosCap,0),
      //ICON(PikachuKalosCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuKalosCap,
[SPECIES_PIKACHU_ALOLA_CAP] = 
    {  
      //FRONT_PIC(PikachuAlolaCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuAlolaCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuAlolaCap),
      PIC_DATA_ICON_INDEX(PikachuAlolaCap,0),
      //ICON(PikachuAlolaCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuAlolaCap,
[SPECIES_PIKACHU_PARTNER_CAP] = 
    {  
      //FRONT_PIC(PikachuPartnerCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuPartnerCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuPartnerCap),
      PIC_DATA_ICON_INDEX(PikachuPartnerCap,0),
      //ICON(PikachuPartnerCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuPartnerCap,
[SPECIES_PIKACHU_WORLD_CAP] = 
    {  
      //FRONT_PIC(PikachuWorldCap),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PikachuWorldCap),
      BACK_COORD(0x88,0),
      //PALETTES(PikachuWorldCap),
      PIC_DATA_ICON_INDEX(PikachuWorldCap,0),
      //ICON(PikachuWorldCap, 0),
      .enemyMonElevation = 0,
    }, //PikachuWorldCap,
[SPECIES_PICHU_SPIKY_EARED] = 
    {  
      //FRONT_PIC(PichuSpikyEared),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PichuSpikyEared),
      BACK_COORD(0x88,0),
      //PALETTES(PichuSpikyEared),
      PIC_DATA_ICON_INDEX(PichuSpikyEared,0),
      //ICON(PichuSpikyEared, 0),
      .enemyMonElevation = 0,
    }, //PichuSpikyEared,
[SPECIES_CASTFORM_SUNNY] = 
    {  
      //FRONT_PIC(CastformSunny),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CastformSunny),
      BACK_COORD(0x88,0),
      //PALETTES(CastformSunny),
      PIC_DATA_ICON_INDEX(CastformSunny,0),
      //ICON(CastformSunny, 0),
      .enemyMonElevation = 0,
    }, //CastformSunny,
[SPECIES_CASTFORM_RAINY] = 
    {  
      //FRONT_PIC(CastformRainy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CastformRainy),
      BACK_COORD(0x88,0),
      //PALETTES(CastformRainy),
      PIC_DATA_ICON_INDEX(CastformRainy,0),
      //ICON(CastformRainy, 0),
      .enemyMonElevation = 0,
    }, //CastformRainy,
[SPECIES_CASTFORM_SNOWY] = 
    {  
      //FRONT_PIC(CastformSnowy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CastformSnowy),
      BACK_COORD(0x88,0),
      //PALETTES(CastformSnowy),
      PIC_DATA_ICON_INDEX(CastformSnowy,0),
      //ICON(CastformSnowy, 0),
      .enemyMonElevation = 0,
    }, //CastformSnowy,
[SPECIES_DEOXYS_ATTACK] = 
    {  
      //FRONT_PIC(DeoxysAttack),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DeoxysAttack),
      BACK_COORD(0x88,0),
      //PALETTES(DeoxysAttack),
      PIC_DATA_ICON_INDEX(DeoxysAttack,0),
      //ICON(DeoxysAttack, 0),
      .enemyMonElevation = 0,
    }, //DeoxysAttack,
[SPECIES_DEOXYS_DEFENSE] = 
    {  
      //FRONT_PIC(DeoxysDefense),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DeoxysDefense),
      BACK_COORD(0x88,0),
      //PALETTES(DeoxysDefense),
      PIC_DATA_ICON_INDEX(DeoxysDefense,0),
      //ICON(DeoxysDefense, 0),
      .enemyMonElevation = 0,
    }, //DeoxysDefense,
[SPECIES_DEOXYS_SPEED] = 
    {  
      //FRONT_PIC(DeoxysSpeed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DeoxysSpeed),
      BACK_COORD(0x88,0),
      //PALETTES(DeoxysSpeed),
      PIC_DATA_ICON_INDEX(DeoxysSpeed,0),
      //ICON(DeoxysSpeed, 0),
      .enemyMonElevation = 0,
    }, //DeoxysSpeed,
[SPECIES_BURMY_SANDY_CLOAK] = 
    {  
      //FRONT_PIC(BurmySandyCloak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BurmySandyCloak),
      BACK_COORD(0x88,0),
      //PALETTES(BurmySandyCloak),
      PIC_DATA_ICON_INDEX(BurmySandyCloak,0),
      //ICON(BurmySandyCloak, 0),
      .enemyMonElevation = 0,
    }, //BurmySandyCloak,
[SPECIES_BURMY_TRASH_CLOAK] = 
    {  
      //FRONT_PIC(BurmyTrashCloak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BurmyTrashCloak),
      BACK_COORD(0x88,0),
      //PALETTES(BurmyTrashCloak),
      PIC_DATA_ICON_INDEX(BurmyTrashCloak,0),
      //ICON(BurmyTrashCloak, 0),
      .enemyMonElevation = 0,
    }, //BurmyTrashCloak,
[SPECIES_WORMADAM_SANDY_CLOAK] = 
    {  
      //FRONT_PIC(WormadamSandyCloak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WormadamSandyCloak),
      BACK_COORD(0x88,0),
      //PALETTES(WormadamSandyCloak),
      PIC_DATA_ICON_INDEX(WormadamSandyCloak,0),
      //ICON(WormadamSandyCloak, 0),
      .enemyMonElevation = 0,
    }, //WormadamSandyCloak,
[SPECIES_WORMADAM_TRASH_CLOAK] = 
    {  
      //FRONT_PIC(WormadamTrashCloak),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WormadamTrashCloak),
      BACK_COORD(0x88,0),
      //PALETTES(WormadamTrashCloak),
      PIC_DATA_ICON_INDEX(WormadamTrashCloak,0),
      //ICON(WormadamTrashCloak, 0),
      .enemyMonElevation = 0,
    }, //WormadamTrashCloak,
[SPECIES_CHERRIM_SUNSHINE] = 
    {  
      //FRONT_PIC(CherrimSunshine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CherrimSunshine),
      BACK_COORD(0x88,0),
      //PALETTES(CherrimSunshine),
      PIC_DATA_ICON_INDEX(CherrimSunshine,0),
      //ICON(CherrimSunshine, 0),
      .enemyMonElevation = 0,
    }, //CherrimSunshine,
[SPECIES_SHELLOS_EAST_SEA] = 
    {  
      //FRONT_PIC(ShellosEastSea),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ShellosEastSea),
      BACK_COORD(0x88,0),
      //PALETTES(ShellosEastSea),
      PIC_DATA_ICON_INDEX(ShellosEastSea,0),
      //ICON(ShellosEastSea, 0),
      .enemyMonElevation = 0,
    }, //ShellosEastSea,
[SPECIES_GASTRODON_EAST_SEA] = 
    {  
      //FRONT_PIC(GastrodonEastSea),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GastrodonEastSea),
      BACK_COORD(0x88,0),
      //PALETTES(GastrodonEastSea),
      PIC_DATA_ICON_INDEX(GastrodonEastSea,0),
      //ICON(GastrodonEastSea, 0),
      .enemyMonElevation = 0,
    }, //GastrodonEastSea,
[SPECIES_ROTOM_HEAT] = 
    {  
      //FRONT_PIC(RotomHeat),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RotomHeat),
      BACK_COORD(0x88,0),
      //PALETTES(RotomHeat),
      PIC_DATA_ICON_INDEX(RotomHeat,0),
      //ICON(RotomHeat, 0),
      .enemyMonElevation = 0,
    }, //RotomHeat,
[SPECIES_ROTOM_WASH] = 
    {  
      //FRONT_PIC(RotomWash),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RotomWash),
      BACK_COORD(0x88,0),
      //PALETTES(RotomWash),
      PIC_DATA_ICON_INDEX(RotomWash,0),
      //ICON(RotomWash, 0),
      .enemyMonElevation = 0,
    }, //RotomWash,
[SPECIES_ROTOM_FROST] = 
    {  
      //FRONT_PIC(RotomFrost),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RotomFrost),
      BACK_COORD(0x88,0),
      //PALETTES(RotomFrost),
      PIC_DATA_ICON_INDEX(RotomFrost,0),
      //ICON(RotomFrost, 0),
      .enemyMonElevation = 0,
    }, //RotomFrost,
[SPECIES_ROTOM_FAN] = 
    {  
      //FRONT_PIC(RotomFan),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RotomFan),
      BACK_COORD(0x88,0),
      //PALETTES(RotomFan),
      PIC_DATA_ICON_INDEX(RotomFan,0),
      //ICON(RotomFan, 0),
      .enemyMonElevation = 0,
    }, //RotomFan,
[SPECIES_ROTOM_MOW] = 
    {  
      //FRONT_PIC(RotomMow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(RotomMow),
      BACK_COORD(0x88,0),
      //PALETTES(RotomMow),
      PIC_DATA_ICON_INDEX(RotomMow,0),
      //ICON(RotomMow, 0),
      .enemyMonElevation = 0,
    }, //RotomMow,
[SPECIES_GIRATINA_ORIGIN] = 
    {  
      //FRONT_PIC(GiratinaOrigin),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GiratinaOrigin),
      BACK_COORD(0x88,0),
      //PALETTES(GiratinaOrigin),
      PIC_DATA_ICON_INDEX(GiratinaOrigin,0),
      //ICON(GiratinaOrigin, 0),
      .enemyMonElevation = 0,
    }, //GiratinaOrigin,
[SPECIES_SHAYMIN_SKY] = 
    {  
      //FRONT_PIC(ShayminSky),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ShayminSky),
      BACK_COORD(0x88,0),
      //PALETTES(ShayminSky),
      PIC_DATA_ICON_INDEX(ShayminSky,0),
      //ICON(ShayminSky, 0),
      .enemyMonElevation = 0,
    }, //ShayminSky,
[SPECIES_ARCEUS_FIGHTING] = 
    {  
      //FRONT_PIC(ArceusFighting),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusFighting),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusFighting),
      PIC_DATA_ICON_INDEX(ArceusFighting,0),
      //ICON(ArceusFighting, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_FLYING] = 
    {  
      //FRONT_PIC(ArceusFlying),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusFlying),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusFlying),
      PIC_DATA_ICON_INDEX(ArceusFlying,0),
      //ICON(ArceusFlying, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_POISON] = 
    {  
      //FRONT_PIC(ArceusPoison),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusPoison),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusPoison),
      PIC_DATA_ICON_INDEX(ArceusPoison,0),
      //ICON(ArceusPoison, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_GROUND] = 
    {  
      //FRONT_PIC(ArceusGround),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusGround),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusGround),
      PIC_DATA_ICON_INDEX(ArceusGround,0),
      //ICON(ArceusGround, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_ROCK] = 
    {  
      //FRONT_PIC(ArceusRock),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusRock),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusRock),
      PIC_DATA_ICON_INDEX(ArceusRock,0),
      //ICON(ArceusRock, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_BUG] = 
    {  
      //FRONT_PIC(ArceusBug),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusBug),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusBug),
      PIC_DATA_ICON_INDEX(ArceusBug,0),
      //ICON(ArceusBug, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_GHOST] = 
    {  
      //FRONT_PIC(ArceusGhost),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusGhost),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusGhost),
      PIC_DATA_ICON_INDEX(ArceusGhost,0),
      //ICON(ArceusGhost, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_STEEL] = 
    {  
      //FRONT_PIC(ArceusSteel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusSteel),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusSteel),
      PIC_DATA_ICON_INDEX(ArceusSteel,0),
      //ICON(ArceusSteel, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_FIRE] = 
    {  
      //FRONT_PIC(ArceusFire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusFire),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusFire),
      PIC_DATA_ICON_INDEX(ArceusFire,0),
      //ICON(ArceusFire, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_WATER] = 
    {  
      //FRONT_PIC(ArceusWater),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusWater),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusWater),
      PIC_DATA_ICON_INDEX(ArceusWater,0),
      //ICON(ArceusWater, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_GRASS] = 
    {  
      //FRONT_PIC(ArceusGrass),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusGrass),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusGrass),
      PIC_DATA_ICON_INDEX(ArceusGrass,0),
      //ICON(ArceusGrass, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_ELECTRIC] = 
    {  
      //FRONT_PIC(ArceusElectric),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusElectric),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusElectric),
      PIC_DATA_ICON_INDEX(ArceusElectric,0),
      //ICON(ArceusElectric, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_PSYCHIC] = 
    {  
      //FRONT_PIC(ArceusPsychic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusPsychic),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusPsychic),
      PIC_DATA_ICON_INDEX(ArceusPsychic,0),
      //ICON(ArceusPsychic, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_ICE] = 
    {  
      //FRONT_PIC(ArceusIce),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusIce),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusIce),
      PIC_DATA_ICON_INDEX(ArceusIce,0),
      //ICON(ArceusIce, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_DRAGON] = 
    {  
      //FRONT_PIC(ArceusDragon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusDragon),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusDragon),
      PIC_DATA_ICON_INDEX(ArceusDragon,0),
      //ICON(ArceusDragon, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_DARK] = 
    {  
      //FRONT_PIC(ArceusDark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusDark),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusDark),
      PIC_DATA_ICON_INDEX(ArceusDark,0),
      //ICON(ArceusDark, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_ARCEUS_FAIRY] = 
    {  
      //FRONT_PIC(ArceusFairy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ArceusFairy),
      BACK_COORD(0x88,0),
      //PALETTES(ArceusFairy),
      PIC_DATA_ICON_INDEX(ArceusFairy,0),
      //ICON(ArceusFairy, 0),
      .enemyMonElevation = 0,
    }, //Arceus,
[SPECIES_BASCULIN_BLUE_STRIPED] = 
    {  
      //FRONT_PIC(BasculinBlueStriped),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BasculinBlueStriped),
      BACK_COORD(0x88,0),
      //PALETTES(BasculinBlueStriped),
      PIC_DATA_ICON_INDEX(BasculinBlueStriped,0),
      //ICON(BasculinBlueStriped, 0),
      .enemyMonElevation = 0,
    }, //BasculinBlueStriped,
[SPECIES_BASCULIN_WHITE_STRIPED] = 
    {  
      //FRONT_PIC(BasculinWhiteStriped),
      FRONT_COORD(0x88,0),
      //BACK_PIC(BasculinWhiteStriped),
      BACK_COORD(0x88,0),
      //PALETTES(BasculinWhiteStriped),
      PIC_DATA_ICON_INDEX(BasculinWhiteStriped,0),
      //ICON(BasculinWhiteStriped, 0),
      .enemyMonElevation = 0,
    }, //BasculinWhiteStriped,
[SPECIES_DARMANITAN_ZEN_MODE] = 
    {  
      //FRONT_PIC(DarmanitanZenMode),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DarmanitanZenMode),
      BACK_COORD(0x88,0),
      //PALETTES(DarmanitanZenMode),
      PIC_DATA_ICON_INDEX(DarmanitanZenMode,0),
      //ICON(DarmanitanZenMode, 0),
      .enemyMonElevation = 0,
    }, //DarmanitanZenMode,
[SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] = 
    {  
      //FRONT_PIC(DarmanitanZenModeGalarian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DarmanitanZenModeGalarian),
      BACK_COORD(0x88,0),
      //PALETTES(DarmanitanZenModeGalarian),
      PIC_DATA_ICON_INDEX(DarmanitanZenModeGalarian,0),
      //ICON(DarmanitanZenModeGalarian, 0),
      .enemyMonElevation = 0,
    }, //DarmanitanZenModeGalarian,
[SPECIES_DEERLING_SUMMER] = 
    {  
      //FRONT_PIC(DeerlingSummer),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DeerlingSummer),
      BACK_COORD(0x88,0),
      //PALETTES(DeerlingSummer),
      PIC_DATA_ICON_INDEX(DeerlingSummer,0),
      //ICON(DeerlingSummer, 0),
      .enemyMonElevation = 0,
    }, //DeerlingSummer,
[SPECIES_DEERLING_AUTUMN] = 
    {  
      //FRONT_PIC(DeerlingAutumn),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DeerlingAutumn),
      BACK_COORD(0x88,0),
      //PALETTES(DeerlingAutumn),
      PIC_DATA_ICON_INDEX(DeerlingAutumn,0),
      //ICON(DeerlingAutumn, 0),
      .enemyMonElevation = 0,
    }, //DeerlingAutumn,
[SPECIES_DEERLING_WINTER] = 
    {  
      //FRONT_PIC(DeerlingWinter),
      FRONT_COORD(0x88,0),
      //BACK_PIC(DeerlingWinter),
      BACK_COORD(0x88,0),
      //PALETTES(DeerlingWinter),
      PIC_DATA_ICON_INDEX(DeerlingWinter,0),
      //ICON(DeerlingWinter, 0),
      .enemyMonElevation = 0,
    }, //DeerlingWinter,
[SPECIES_SAWSBUCK_SUMMER] = 
    {  
      //FRONT_PIC(SawsbuckSummer),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SawsbuckSummer),
      BACK_COORD(0x88,0),
      //PALETTES(SawsbuckSummer),
      PIC_DATA_ICON_INDEX(SawsbuckSummer,0),
      //ICON(SawsbuckSummer, 0),
      .enemyMonElevation = 0,
    }, //SawsbuckSummer,
[SPECIES_SAWSBUCK_AUTUMN] = 
    {  
      //FRONT_PIC(SawsbuckAutumn),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SawsbuckAutumn),
      BACK_COORD(0x88,0),
      //PALETTES(SawsbuckAutumn),
      PIC_DATA_ICON_INDEX(SawsbuckAutumn,0),
      //ICON(SawsbuckAutumn, 0),
      .enemyMonElevation = 0,
    }, //SawsbuckAutumn,
[SPECIES_SAWSBUCK_WINTER] = 
    {  
      //FRONT_PIC(SawsbuckWinter),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SawsbuckWinter),
      BACK_COORD(0x88,0),
      //PALETTES(SawsbuckWinter),
      PIC_DATA_ICON_INDEX(SawsbuckWinter,0),
      //ICON(SawsbuckWinter, 0),
      .enemyMonElevation = 0,
    }, //SawsbuckWinter,
[SPECIES_TORNADUS_THERIAN] = 
    {  
      //FRONT_PIC(TornadusTherian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(TornadusTherian),
      BACK_COORD(0x88,0),
      //PALETTES(TornadusTherian),
      PIC_DATA_ICON_INDEX(TornadusTherian,0),
      //ICON(TornadusTherian, 0),
      .enemyMonElevation = 0,
    }, //TornadusTherian,
[SPECIES_THUNDURUS_THERIAN] = 
    {  
      //FRONT_PIC(ThundurusTherian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ThundurusTherian),
      BACK_COORD(0x88,0),
      //PALETTES(ThundurusTherian),
      PIC_DATA_ICON_INDEX(ThundurusTherian,0),
      //ICON(ThundurusTherian, 0),
      .enemyMonElevation = 0,
    }, //ThundurusTherian,
[SPECIES_LANDORUS_THERIAN] = 
    {  
      //FRONT_PIC(LandorusTherian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LandorusTherian),
      BACK_COORD(0x88,0),
      //PALETTES(LandorusTherian),
      PIC_DATA_ICON_INDEX(LandorusTherian,0),
      //ICON(LandorusTherian, 0),
      .enemyMonElevation = 0,
    }, //LandorusTherian,
[SPECIES_ENAMORUS_THERIAN] = 
    {  
      //FRONT_PIC(EnamorusTherian),
      FRONT_COORD(0x88,0),
      //BACK_PIC(EnamorusTherian),
      BACK_COORD(0x88,0),
      //PALETTES(EnamorusTherian),
      PIC_DATA_ICON_INDEX(EnamorusTherian,0),
      //ICON(EnamorusTherian, 0),
      .enemyMonElevation = 0,
    }, //EnamorusTherian,
[SPECIES_KYUREM_WHITE] = 
    {  
      //FRONT_PIC(KyuremWhite),
      FRONT_COORD(0x88,0),
      //BACK_PIC(KyuremWhite),
      BACK_COORD(0x88,0),
      //PALETTES(KyuremWhite),
      PIC_DATA_ICON_INDEX(KyuremWhite,0),
      //ICON(KyuremWhite, 0),
      .enemyMonElevation = 0,
    }, //KyuremWhite,
[SPECIES_KYUREM_BLACK] = 
    {  
      //FRONT_PIC(KyuremBlack),
      FRONT_COORD(0x88,0),
      //BACK_PIC(KyuremBlack),
      BACK_COORD(0x88,0),
      //PALETTES(KyuremBlack),
      PIC_DATA_ICON_INDEX(KyuremBlack,0),
      //ICON(KyuremBlack, 0),
      .enemyMonElevation = 0,
    }, //KyuremBlack,
[SPECIES_KELDEO_RESOLUTE] = 
    {  
      //FRONT_PIC(KeldeoResolute),
      FRONT_COORD(0x88,0),
      //BACK_PIC(KeldeoResolute),
      BACK_COORD(0x88,0),
      //PALETTES(KeldeoResolute),
      PIC_DATA_ICON_INDEX(KeldeoResolute,0),
      //ICON(KeldeoResolute, 0),
      .enemyMonElevation = 0,
    }, //KeldeoResolute,
[SPECIES_MELOETTA_PIROUETTE] = 
    {  
      //FRONT_PIC(MeloettaPirouette),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MeloettaPirouette),
      BACK_COORD(0x88,0),
      //PALETTES(MeloettaPirouette),
      PIC_DATA_ICON_INDEX(MeloettaPirouette,0),
      //ICON(MeloettaPirouette, 0),
      .enemyMonElevation = 0,
    }, //MeloettaPirouette,
[SPECIES_GENESECT_DOUSE_DRIVE] = 
    {  
      //FRONT_PIC(GenesectDouseDrive),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GenesectDouseDrive),
      BACK_COORD(0x88,0),
      //PALETTES(GenesectDouseDrive),
      PIC_DATA_ICON_INDEX(GenesectDouseDrive,0),
      //ICON(GenesectDouseDrive, 0),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GENESECT_SHOCK_DRIVE] = 
    {  
      //FRONT_PIC(GenesectShockDrive),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GenesectShockDrive),
      BACK_COORD(0x88,0),
      //PALETTES(GenesectShockDrive),
      PIC_DATA_ICON_INDEX(GenesectShockDrive,0),
      //ICON(GenesectShockDrive, 0),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GENESECT_BURN_DRIVE] = 
    {  
      //FRONT_PIC(GenesectBurnDrive),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GenesectBurnDrive),
      BACK_COORD(0x88,0),
      //PALETTES(GenesectBurnDrive),
      PIC_DATA_ICON_INDEX(GenesectBurnDrive,0),
      //ICON(GenesectBurnDrive, 0),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GENESECT_CHILL_DRIVE] = 
    {  
      //FRONT_PIC(GenesectChillDrive),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GenesectChillDrive),
      BACK_COORD(0x88,0),
      //PALETTES(GenesectChillDrive),
      PIC_DATA_ICON_INDEX(GenesectChillDrive,0),
      //ICON(GenesectChillDrive, 0),
      .enemyMonElevation = 0,
    }, //Genesect,
[SPECIES_GRENINJA_ASH] = 
    {  
      //FRONT_PIC(GreninjaAsh),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GreninjaAsh),
      BACK_COORD(0x88,0),
      //PALETTES(GreninjaAsh),
      PIC_DATA_ICON_INDEX(GreninjaAsh,0),
      //ICON(GreninjaAsh, 0),
      .enemyMonElevation = 0,
    }, //GreninjaAsh,
[SPECIES_VIVILLON_POLAR] = 
    {  
      //FRONT_PIC(VivillonPolar),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonPolar),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonPolar),
      PIC_DATA_ICON_INDEX(VivillonPolar,0),
      //ICON(VivillonPolar, 0),
      .enemyMonElevation = 0,
    }, //VivillonPolar,
[SPECIES_VIVILLON_TUNDRA] = 
    {  
      //FRONT_PIC(VivillonTundra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonTundra),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonTundra),
      PIC_DATA_ICON_INDEX(VivillonTundra,0),
      //ICON(VivillonTundra, 0),
      .enemyMonElevation = 0,
    }, //VivillonTundra,
[SPECIES_VIVILLON_CONTINENTAL] = 
    {  
      //FRONT_PIC(VivillonContinental),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonContinental),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonContinental),
      PIC_DATA_ICON_INDEX(VivillonContinental,0),
      //ICON(VivillonContinental, 0),
      .enemyMonElevation = 0,
    }, //VivillonContinental,
[SPECIES_VIVILLON_GARDEN] = 
    {  
      //FRONT_PIC(VivillonGarden),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonGarden),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonGarden),
      PIC_DATA_ICON_INDEX(VivillonGarden,0),
      //ICON(VivillonGarden, 0),
      .enemyMonElevation = 0,
    }, //VivillonGarden,
[SPECIES_VIVILLON_ELEGANT] = 
    {  
      //FRONT_PIC(VivillonElegant),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonElegant),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonElegant),
      PIC_DATA_ICON_INDEX(VivillonElegant,0),
      //ICON(VivillonElegant, 0),
      .enemyMonElevation = 0,
    }, //VivillonElegant,
[SPECIES_VIVILLON_MEADOW] = 
    {  
      //FRONT_PIC(VivillonMeadow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonMeadow),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonMeadow),
      PIC_DATA_ICON_INDEX(VivillonMeadow,0),
      //ICON(VivillonMeadow, 0),
      .enemyMonElevation = 0,
    }, //VivillonMeadow,
[SPECIES_VIVILLON_MODERN] = 
    {  
      //FRONT_PIC(VivillonModern),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonModern),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonModern),
      PIC_DATA_ICON_INDEX(VivillonModern,0),
      //ICON(VivillonModern, 0),
      .enemyMonElevation = 0,
    }, //VivillonModern,
[SPECIES_VIVILLON_MARINE] = 
    {  
      //FRONT_PIC(VivillonMarine),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonMarine),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonMarine),
      PIC_DATA_ICON_INDEX(VivillonMarine,0),
      //ICON(VivillonMarine, 0),
      .enemyMonElevation = 0,
    }, //VivillonMarine,
[SPECIES_VIVILLON_ARCHIPELAGO] = 
    {  
      //FRONT_PIC(VivillonArchipelago),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonArchipelago),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonArchipelago),
      PIC_DATA_ICON_INDEX(VivillonArchipelago,0),
      //ICON(VivillonArchipelago, 0),
      .enemyMonElevation = 0,
    }, //VivillonArchipelago,
[SPECIES_VIVILLON_HIGH_PLAINS] = 
    {  
      //FRONT_PIC(VivillonHighPlains),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonHighPlains),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonHighPlains),
      PIC_DATA_ICON_INDEX(VivillonHighPlains,0),
      //ICON(VivillonHighPlains, 0),
      .enemyMonElevation = 0,
    }, //VivillonHighPlains,
[SPECIES_VIVILLON_SANDSTORM] = 
    {  
      //FRONT_PIC(VivillonSandstorm),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonSandstorm),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonSandstorm),
      PIC_DATA_ICON_INDEX(VivillonSandstorm,0),
      //ICON(VivillonSandstorm, 0),
      .enemyMonElevation = 0,
    }, //VivillonSandstorm,
[SPECIES_VIVILLON_RIVER] = 
    {  
      //FRONT_PIC(VivillonRiver),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonRiver),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonRiver),
      PIC_DATA_ICON_INDEX(VivillonRiver,0),
      //ICON(VivillonRiver, 0),
      .enemyMonElevation = 0,
    }, //VivillonRiver,
[SPECIES_VIVILLON_MONSOON] = 
    {  
      //FRONT_PIC(VivillonMonsoon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonMonsoon),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonMonsoon),
      PIC_DATA_ICON_INDEX(VivillonMonsoon,0),
      //ICON(VivillonMonsoon, 0),
      .enemyMonElevation = 0,
    }, //VivillonMonsoon,
[SPECIES_VIVILLON_SAVANNA] = 
    {  
      //FRONT_PIC(VivillonSavanna),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonSavanna),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonSavanna),
      PIC_DATA_ICON_INDEX(VivillonSavanna,0),
      //ICON(VivillonSavanna, 0),
      .enemyMonElevation = 0,
    }, //VivillonSavanna,
[SPECIES_VIVILLON_SUN] = 
    {  
      //FRONT_PIC(VivillonSun),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonSun),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonSun),
      PIC_DATA_ICON_INDEX(VivillonSun,0),
      //ICON(VivillonSun, 0),
      .enemyMonElevation = 0,
    }, //VivillonSun,
[SPECIES_VIVILLON_OCEAN] = 
    {  
      //FRONT_PIC(VivillonOcean),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonOcean),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonOcean),
      PIC_DATA_ICON_INDEX(VivillonOcean,0),
      //ICON(VivillonOcean, 0),
      .enemyMonElevation = 0,
    }, //VivillonOcean,
[SPECIES_VIVILLON_JUNGLE] = 
    {  
      //FRONT_PIC(VivillonJungle),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonJungle),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonJungle),
      PIC_DATA_ICON_INDEX(VivillonJungle,0),
      //ICON(VivillonJungle, 0),
      .enemyMonElevation = 0,
    }, //VivillonJungle,
[SPECIES_VIVILLON_FANCY] = 
    {  
      //FRONT_PIC(VivillonFancy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonFancy),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonFancy),
      PIC_DATA_ICON_INDEX(VivillonFancy,0),
      //ICON(VivillonFancy, 0),
      .enemyMonElevation = 0,
    }, //VivillonFancy,
[SPECIES_VIVILLON_POKE_BALL] = 
    {  
      //FRONT_PIC(VivillonPokeBall),
      FRONT_COORD(0x88,0),
      //BACK_PIC(VivillonPokeBall),
      BACK_COORD(0x88,0),
      //PALETTES(VivillonPokeBall),
      PIC_DATA_ICON_INDEX(VivillonPokeBall,0),
      //ICON(VivillonPokeBall, 0),
      .enemyMonElevation = 0,
    }, //VivillonPokeBall,
[SPECIES_UNFEZANT_FEMALE] = 
    {  
      //FRONT_PIC(UnfezantFemale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(UnfezantFemale),
      BACK_COORD(0x88,0),
      //PALETTES(UnfezantFemale),
      PIC_DATA_ICON_INDEX(UnfezantFemale,0),
      //ICON(UnfezantFemale, 0),
      .enemyMonElevation = 0,
    }, //Unfezant_Female
[SPECIES_PYROAR_FEMALE] = 
    {  
      //FRONT_PIC(PyroarFemale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PyroarFemale),
      BACK_COORD(0x88,0),
      //PALETTES(PyroarFemale),
      PIC_DATA_ICON_INDEX(PyroarFemale,0),
      //ICON(PyroarFemale, 0),
      .enemyMonElevation = 0,
    }, //Pyroar_Female,
[SPECIES_FLABEBE_YELLOW_FLOWER] = 
    {  
      //FRONT_PIC(FlabebeYellowFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlabebeYellowFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlabebeYellowFlower),
      PIC_DATA_ICON_INDEX(FlabebeYellowFlower,0),
      //ICON(FlabebeYellowFlower, 0),
      .enemyMonElevation = 0,
    }, //FlabebeYellowFlower,
[SPECIES_FLABEBE_ORANGE_FLOWER] = 
    {  
      //FRONT_PIC(FlabebeOrangeFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlabebeOrangeFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlabebeOrangeFlower),
      PIC_DATA_ICON_INDEX(FlabebeOrangeFlower,0),
      //ICON(FlabebeOrangeFlower, 0),
      .enemyMonElevation = 0,
    }, //FlabebeOrangeFlower,
[SPECIES_FLABEBE_BLUE_FLOWER] = 
    {  
      //FRONT_PIC(FlabebeBlueFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlabebeBlueFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlabebeBlueFlower),
      PIC_DATA_ICON_INDEX(FlabebeBlueFlower,0),
      //ICON(FlabebeBlueFlower, 0),
      .enemyMonElevation = 0,
    }, //FlabebeBlueFlower,
[SPECIES_FLABEBE_WHITE_FLOWER] = 
    {  
      //FRONT_PIC(FlabebeWhiteFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlabebeWhiteFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlabebeWhiteFlower),
      PIC_DATA_ICON_INDEX(FlabebeWhiteFlower,0),
      //ICON(FlabebeWhiteFlower, 0),
      .enemyMonElevation = 0,
    }, //FlabebeWhiteFlower,
[SPECIES_FLOETTE_YELLOW_FLOWER] = 
    {  
      //FRONT_PIC(FloetteYellowFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FloetteYellowFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FloetteYellowFlower),
      PIC_DATA_ICON_INDEX(FloetteYellowFlower,0),
      //ICON(FloetteYellowFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteYellowFlower,
[SPECIES_FLOETTE_ORANGE_FLOWER] = 
    {  
      //FRONT_PIC(FloetteOrangeFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FloetteOrangeFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FloetteOrangeFlower),
      PIC_DATA_ICON_INDEX(FloetteOrangeFlower,0),
      //ICON(FloetteOrangeFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteOrangeFlower,
[SPECIES_FLOETTE_BLUE_FLOWER] = 
    {  
      //FRONT_PIC(FloetteBlueFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FloetteBlueFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FloetteBlueFlower),
      PIC_DATA_ICON_INDEX(FloetteBlueFlower,0),
      //ICON(FloetteBlueFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteBlueFlower,
[SPECIES_FLOETTE_WHITE_FLOWER] = 
    {  
      //FRONT_PIC(FloetteWhiteFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FloetteWhiteFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FloetteWhiteFlower),
      PIC_DATA_ICON_INDEX(FloetteWhiteFlower,0),
      //ICON(FloetteWhiteFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteWhiteFlower,
[SPECIES_FLOETTE_ETERNAL_FLOWER] = 
    {  
      //FRONT_PIC(FloetteEternalFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FloetteEternalFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FloetteEternalFlower),
      PIC_DATA_ICON_INDEX(FloetteEternalFlower,0),
      //ICON(FloetteEternalFlower, 0),
      .enemyMonElevation = 0,
    }, //FloetteEternalFlower,
[SPECIES_FLORGES_YELLOW_FLOWER] = 
    {  
      //FRONT_PIC(FlorgesYellowFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlorgesYellowFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlorgesYellowFlower),
      PIC_DATA_ICON_INDEX(FlorgesYellowFlower,0),
      //ICON(FlorgesYellowFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesYellowFlower,
[SPECIES_FLORGES_ORANGE_FLOWER] = 
    {  
      //FRONT_PIC(FlorgesOrangeFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlorgesOrangeFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlorgesOrangeFlower),
      PIC_DATA_ICON_INDEX(FlorgesOrangeFlower,0),
      //ICON(FlorgesOrangeFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesOrangeFlower,
[SPECIES_FLORGES_BLUE_FLOWER] = 
    {  
      //FRONT_PIC(FlorgesBlueFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlorgesBlueFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlorgesBlueFlower),
      PIC_DATA_ICON_INDEX(FlorgesBlueFlower,0),
      //ICON(FlorgesBlueFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesBlueFlower,
[SPECIES_FLORGES_WHITE_FLOWER] = 
    {  
      //FRONT_PIC(FlorgesWhiteFlower),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FlorgesWhiteFlower),
      BACK_COORD(0x88,0),
      //PALETTES(FlorgesWhiteFlower),
      PIC_DATA_ICON_INDEX(FlorgesWhiteFlower,0),
      //ICON(FlorgesWhiteFlower, 0),
      .enemyMonElevation = 0,
    }, //FlorgesWhiteFlower,
[SPECIES_FURFROU_HEART_TRIM] = 
    {  
      //FRONT_PIC(FurfrouHeartTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouHeartTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouHeartTrim),
      PIC_DATA_ICON_INDEX(FurfrouHeartTrim,0),
      //ICON(FurfrouHeartTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouHeartTrim,
[SPECIES_FURFROU_STAR_TRIM] = 
    {  
      //FRONT_PIC(FurfrouStarTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouStarTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouStarTrim),
      PIC_DATA_ICON_INDEX(FurfrouStarTrim,0),
      //ICON(FurfrouStarTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouStarTrim,
[SPECIES_FURFROU_DIAMOND_TRIM] = 
    {  
      //FRONT_PIC(FurfrouDiamondTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouDiamondTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouDiamondTrim),
      PIC_DATA_ICON_INDEX(FurfrouDiamondTrim,0),
      //ICON(FurfrouDiamondTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouDiamondTrim,
[SPECIES_FURFROU_DEBUTANTE_TRIM] = 
    {  
      //FRONT_PIC(FurfrouDebutanteTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouDebutanteTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouDebutanteTrim),
      PIC_DATA_ICON_INDEX(FurfrouDebutanteTrim,0),
      //ICON(FurfrouDebutanteTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouDebutanteTrim,
[SPECIES_FURFROU_MATRON_TRIM] = 
    {  
      //FRONT_PIC(FurfrouMatronTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouMatronTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouMatronTrim),
      PIC_DATA_ICON_INDEX(FurfrouMatronTrim,0),
      //ICON(FurfrouMatronTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouMatronTrim,
[SPECIES_FURFROU_DANDY_TRIM] = 
    {  
      //FRONT_PIC(FurfrouDandyTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouDandyTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouDandyTrim),
      PIC_DATA_ICON_INDEX(FurfrouDandyTrim,0),
      //ICON(FurfrouDandyTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouDandyTrim,
[SPECIES_FURFROU_LA_REINE_TRIM] = 
    {  
      //FRONT_PIC(FurfrouLaReineTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouLaReineTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouLaReineTrim),
      PIC_DATA_ICON_INDEX(FurfrouLaReineTrim,0),
      //ICON(FurfrouLaReineTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouLaReineTrim,
[SPECIES_FURFROU_KABUKI_TRIM] = 
    {  
      //FRONT_PIC(FurfrouKabukiTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouKabukiTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouKabukiTrim),
      PIC_DATA_ICON_INDEX(FurfrouKabukiTrim,0),
      //ICON(FurfrouKabukiTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouKabukiTrim,
[SPECIES_FURFROU_PHARAOH_TRIM] = 
    {  
      //FRONT_PIC(FurfrouPharaohTrim),
      FRONT_COORD(0x88,0),
      //BACK_PIC(FurfrouPharaohTrim),
      BACK_COORD(0x88,0),
      //PALETTES(FurfrouPharaohTrim),
      PIC_DATA_ICON_INDEX(FurfrouPharaohTrim,0),
      //ICON(FurfrouPharaohTrim, 0),
      .enemyMonElevation = 0,
    }, //FurfrouPharaohTrim,
[SPECIES_MEOWSTIC_FEMALE] = 
    {  
      //FRONT_PIC(MeowsticFemale),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MeowsticFemale),
      BACK_COORD(0x88,0),
      //PALETTES(MeowsticFemale),
      PIC_DATA_ICON_INDEX(MeowsticFemale,0),
      //ICON(MeowsticFemale, 0),
      .enemyMonElevation = 0,
    }, //Meowstic_Female,
[SPECIES_AEGISLASH_BLADE] = 
    {  
      //FRONT_PIC(AegislashBlade),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AegislashBlade),
      BACK_COORD(0x88,0),
      //PALETTES(AegislashBlade),
      PIC_DATA_ICON_INDEX(AegislashBlade,0),
      //ICON(AegislashBlade, 0),
      .enemyMonElevation = 0,
    }, //AegislashBlade,
[SPECIES_PUMPKABOO_SMALL] = 
    {  
      //FRONT_PIC(PumpkabooSmall),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PumpkabooSmall),
      BACK_COORD(0x88,0),
      //PALETTES(PumpkabooSmall),
      PIC_DATA_ICON_INDEX(PumpkabooSmall,0),
      //ICON(PumpkabooSmall, 0),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_PUMPKABOO_LARGE] = 
    {  
      //FRONT_PIC(PumpkabooLarge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PumpkabooLarge),
      BACK_COORD(0x88,0),
      //PALETTES(PumpkabooLarge),
      PIC_DATA_ICON_INDEX(PumpkabooLarge,0),
      //ICON(PumpkabooLarge, 0),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_PUMPKABOO_SUPER] = 
    {  
      //FRONT_PIC(PumpkabooSuper),
      FRONT_COORD(0x88,0),
      //BACK_PIC(PumpkabooSuper),
      BACK_COORD(0x88,0),
      //PALETTES(PumpkabooSuper),
      PIC_DATA_ICON_INDEX(PumpkabooSuper,0),
      //ICON(PumpkabooSuper, 0),
      .enemyMonElevation = 0,
    }, //Pumpkaboo,
[SPECIES_GOURGEIST_SMALL] = 
    {  
      //FRONT_PIC(GourgeistSmall),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GourgeistSmall),
      BACK_COORD(0x88,0),
      //PALETTES(GourgeistSmall),
      PIC_DATA_ICON_INDEX(GourgeistSmall,0),
      //ICON(GourgeistSmall, 0),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_GOURGEIST_LARGE] = 
    {  
      //FRONT_PIC(GourgeistLarge),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GourgeistLarge),
      BACK_COORD(0x88,0),
      //PALETTES(GourgeistLarge),
      PIC_DATA_ICON_INDEX(GourgeistLarge,0),
      //ICON(GourgeistLarge, 0),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_GOURGEIST_SUPER] = 
    {  
      //FRONT_PIC(GourgeistSuper),
      FRONT_COORD(0x88,0),
      //BACK_PIC(GourgeistSuper),
      BACK_COORD(0x88,0),
      //PALETTES(GourgeistSuper),
      PIC_DATA_ICON_INDEX(GourgeistSuper,0),
      //ICON(GourgeistSuper, 0),
      .enemyMonElevation = 0,
    }, //Gourgeist,
[SPECIES_XERNEAS_ACTIVE] = 
    {  
      //FRONT_PIC(XerneasActive),
      FRONT_COORD(0x88,0),
      //BACK_PIC(XerneasActive),
      BACK_COORD(0x88,0),
      //PALETTES(XerneasActive),
      PIC_DATA_ICON_INDEX(XerneasActive,0),
      //ICON(XerneasActive, 0),
      .enemyMonElevation = 0,
    }, //XerneasActive,
[SPECIES_ZYGARDE_10] = 
    {  
      //FRONT_PIC(Zygarde10),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zygarde10),
      BACK_COORD(0x88,0),
      //PALETTES(Zygarde10),
      PIC_DATA_ICON_INDEX(Zygarde10,0),
      //ICON(Zygarde10, 0),
      .enemyMonElevation = 0,
    }, //Zygarde10,
[SPECIES_ZYGARDE_10_POWER_CONSTRUCT] = 
    {  
      //FRONT_PIC(Zygarde10PowerConstruct),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zygarde10PowerConstruct),
      BACK_COORD(0x88,0),
      //PALETTES(Zygarde10PowerConstruct),
      PIC_DATA_ICON_INDEX(Zygarde10PowerConstruct,0),
      //ICON(Zygarde10PowerConstruct, 0),
      .enemyMonElevation = 0,
    }, //Zygarde10,
[SPECIES_ZYGARDE_50_POWER_CONSTRUCT] = 
    {  
      //FRONT_PIC(Zygarde50PowerConstruct),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Zygarde50PowerConstruct),
      BACK_COORD(0x88,0),
      //PALETTES(Zygarde50PowerConstruct),
      PIC_DATA_ICON_INDEX(Zygarde50PowerConstruct,0),
      //ICON(Zygarde50PowerConstruct, 0),
      .enemyMonElevation = 0,
    }, //Zygarde,
[SPECIES_ZYGARDE_COMPLETE] = 
    {  
      //FRONT_PIC(ZygardeComplete),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZygardeComplete),
      BACK_COORD(0x88,0),
      //PALETTES(ZygardeComplete),
      PIC_DATA_ICON_INDEX(ZygardeComplete,0),
      //ICON(ZygardeComplete, 0),
      .enemyMonElevation = 0,
    }, //ZygardeComplete,
[SPECIES_HOOPA_UNBOUND] = 
    {  
      //FRONT_PIC(HoopaUnbound),
      FRONT_COORD(0x88,0),
      //BACK_PIC(HoopaUnbound),
      BACK_COORD(0x88,0),
      //PALETTES(HoopaUnbound),
      PIC_DATA_ICON_INDEX(HoopaUnbound,0),
      //ICON(HoopaUnbound, 0),
      .enemyMonElevation = 0,
    }, //HoopaUnbound,
[SPECIES_ORICORIO_POM_POM] = 
    {  
      //FRONT_PIC(OricorioPomPom),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OricorioPomPom),
      BACK_COORD(0x88,0),
      //PALETTES(OricorioPomPom),
      PIC_DATA_ICON_INDEX(OricorioPomPom,0),
      //ICON(OricorioPomPom, 0),
      .enemyMonElevation = 0,
    }, //OricorioPomPom,
[SPECIES_ORICORIO_PAU] = 
    {  
      //FRONT_PIC(OricorioPau),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OricorioPau),
      BACK_COORD(0x88,0),
      //PALETTES(OricorioPau),
      PIC_DATA_ICON_INDEX(OricorioPau,0),
      //ICON(OricorioPau, 0),
      .enemyMonElevation = 0,
    }, //OricorioPau,
[SPECIES_ORICORIO_SENSU] = 
    {  
      //FRONT_PIC(OricorioSensu),
      FRONT_COORD(0x88,0),
      //BACK_PIC(OricorioSensu),
      BACK_COORD(0x88,0),
      //PALETTES(OricorioSensu),
      PIC_DATA_ICON_INDEX(OricorioSensu,0),
      //ICON(OricorioSensu, 0),
      .enemyMonElevation = 0,
    }, //OricorioSensu,
[SPECIES_LYCANROC_MIDNIGHT] = 
    {  
      //FRONT_PIC(LycanrocMidnight),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LycanrocMidnight),
      BACK_COORD(0x88,0),
      //PALETTES(LycanrocMidnight),
      PIC_DATA_ICON_INDEX(LycanrocMidnight,0),
      //ICON(LycanrocMidnight, 0),
      .enemyMonElevation = 0,
    }, //LycanrocMidnight,
[SPECIES_LYCANROC_DUSK] = 
    {  
      //FRONT_PIC(LycanrocDusk),
      FRONT_COORD(0x88,0),
      //BACK_PIC(LycanrocDusk),
      BACK_COORD(0x88,0),
      //PALETTES(LycanrocDusk),
      PIC_DATA_ICON_INDEX(LycanrocDusk,0),
      //ICON(LycanrocDusk, 0),
      .enemyMonElevation = 0,
    }, //LycanrocDusk,
[SPECIES_WISHIWASHI_SCHOOL] = 
    {  
      //FRONT_PIC(WishiwashiSchool),
      FRONT_COORD(0x88,0),
      //BACK_PIC(WishiwashiSchool),
      BACK_COORD(0x88,0),
      //PALETTES(WishiwashiSchool),
      PIC_DATA_ICON_INDEX(WishiwashiSchool,0),
      //ICON(WishiwashiSchool, 0),
      .enemyMonElevation = 0,
    }, //WishiwashiSchool,
[SPECIES_SILVALLY_FIGHTING] = 
    {  
      //FRONT_PIC(SilvallyFighting),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyFighting),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyFighting),
      PIC_DATA_ICON_INDEX(SilvallyFighting,0),
      //ICON(SilvallyFighting, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_FLYING] = 
    {  
      //FRONT_PIC(SilvallyFlying),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyFlying),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyFlying),
      PIC_DATA_ICON_INDEX(SilvallyFlying,0),
      //ICON(SilvallyFlying, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_POISON] = 
    {  
      //FRONT_PIC(SilvallyPoison),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyPoison),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyPoison),
      PIC_DATA_ICON_INDEX(SilvallyPoison,0),
      //ICON(SilvallyPoison, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_GROUND] = 
    {  
      //FRONT_PIC(SilvallyGround),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyGround),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyGround),
      PIC_DATA_ICON_INDEX(SilvallyGround,0),
      //ICON(SilvallyGround, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_ROCK] = 
    {  
      //FRONT_PIC(SilvallyRock),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyRock),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyRock),
      PIC_DATA_ICON_INDEX(SilvallyRock,0),
      //ICON(SilvallyRock, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_BUG] = 
    {  
      //FRONT_PIC(SilvallyBug),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyBug),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyBug),
      PIC_DATA_ICON_INDEX(SilvallyBug,0),
      //ICON(SilvallyBug, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_GHOST] = 
    {  
      //FRONT_PIC(SilvallyGhost),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyGhost),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyGhost),
      PIC_DATA_ICON_INDEX(SilvallyGhost,0),
      //ICON(SilvallyGhost, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_STEEL] = 
    {  
      //FRONT_PIC(SilvallySteel),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallySteel),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallySteel),
      PIC_DATA_ICON_INDEX(SilvallySteel,0),
      //ICON(SilvallySteel, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_FIRE] = 
    {  
      //FRONT_PIC(SilvallyFire),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyFire),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyFire),
      PIC_DATA_ICON_INDEX(SilvallyFire,0),
      //ICON(SilvallyFire, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_WATER] = 
    {  
      //FRONT_PIC(SilvallyWater),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyWater),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyWater),
      PIC_DATA_ICON_INDEX(SilvallyWater,0),
      //ICON(SilvallyWater, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_GRASS] = 
    {  
      //FRONT_PIC(SilvallyGrass),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyGrass),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyGrass),
      PIC_DATA_ICON_INDEX(SilvallyGrass,0),
      //ICON(SilvallyGrass, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_ELECTRIC] = 
    {  
      //FRONT_PIC(SilvallyElectric),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyElectric),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyElectric),
      PIC_DATA_ICON_INDEX(SilvallyElectric,0),
      //ICON(SilvallyElectric, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_PSYCHIC] = 
    {  
      //FRONT_PIC(SilvallyPsychic),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyPsychic),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyPsychic),
      PIC_DATA_ICON_INDEX(SilvallyPsychic,0),
      //ICON(SilvallyPsychic, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_ICE] = 
    {  
      //FRONT_PIC(SilvallyIce),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyIce),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyIce),
      PIC_DATA_ICON_INDEX(SilvallyIce,0),
      //ICON(SilvallyIce, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_DRAGON] = 
    {  
      //FRONT_PIC(SilvallyDragon),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyDragon),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyDragon),
      PIC_DATA_ICON_INDEX(SilvallyDragon,0),
      //ICON(SilvallyDragon, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_DARK] = 
    {  
      //FRONT_PIC(SilvallyDark),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyDark),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyDark),
      PIC_DATA_ICON_INDEX(SilvallyDark,0),
      //ICON(SilvallyDark, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_SILVALLY_FAIRY] = 
    {  
      //FRONT_PIC(SilvallyFairy),
      FRONT_COORD(0x88,0),
      //BACK_PIC(SilvallyFairy),
      BACK_COORD(0x88,0),
      //PALETTES(SilvallyFairy),
      PIC_DATA_ICON_INDEX(SilvallyFairy,0),
      //ICON(SilvallyFairy, 0),
      .enemyMonElevation = 0,
    }, //Silvally,
[SPECIES_MINIOR_METEOR_ORANGE] = 
    {  
      //FRONT_PIC(MiniorMeteorOrange),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorMeteorOrange),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorMeteorOrange),
      PIC_DATA_ICON_INDEX(MiniorMeteorOrange,0),
      //ICON(MiniorMeteorOrange, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_YELLOW] = 
    {  
      //FRONT_PIC(MiniorMeteorYellow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorMeteorYellow),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorMeteorYellow),
      PIC_DATA_ICON_INDEX(MiniorMeteorYellow,0),
      //ICON(MiniorMeteorYellow, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_GREEN] = 
    {  
      //FRONT_PIC(MiniorMeteorGreen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorMeteorGreen),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorMeteorGreen),
      PIC_DATA_ICON_INDEX(MiniorMeteorGreen,0),
      //ICON(MiniorMeteorGreen, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_BLUE] = 
    {  
      //FRONT_PIC(MiniorMeteorBlue),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorMeteorBlue),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorMeteorBlue),
      PIC_DATA_ICON_INDEX(MiniorMeteorBlue,0),
      //ICON(MiniorMeteorBlue, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_INDIGO] = 
    {  
      //FRONT_PIC(MiniorMeteorIndigo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorMeteorIndigo),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorMeteorIndigo),
      PIC_DATA_ICON_INDEX(MiniorMeteorIndigo,0),
      //ICON(MiniorMeteorIndigo, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_METEOR_VIOLET] = 
    {  
      //FRONT_PIC(MiniorMeteorViolet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorMeteorViolet),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorMeteorViolet),
      PIC_DATA_ICON_INDEX(MiniorMeteorViolet,0),
      //ICON(MiniorMeteorViolet, 0),
      .enemyMonElevation = 0,
    }, //Minior,
[SPECIES_MINIOR_CORE_RED] = 
    {  
      //FRONT_PIC(MiniorCoreRed),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreRed),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreRed),
      PIC_DATA_ICON_INDEX(MiniorCoreRed,0),
      //ICON(MiniorCoreRed, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreRed,
[SPECIES_MINIOR_CORE_ORANGE] = 
    {  
      //FRONT_PIC(MiniorCoreOrange),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreOrange),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreOrange),
      PIC_DATA_ICON_INDEX(MiniorCoreOrange,0),
      //ICON(MiniorCoreOrange, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreOrange,
[SPECIES_MINIOR_CORE_YELLOW] = 
    {  
      //FRONT_PIC(MiniorCoreYellow),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreYellow),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreYellow),
      PIC_DATA_ICON_INDEX(MiniorCoreYellow,0),
      //ICON(MiniorCoreYellow, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreYellow,
[SPECIES_MINIOR_CORE_GREEN] = 
    {  
      //FRONT_PIC(MiniorCoreGreen),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreGreen),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreGreen),
      PIC_DATA_ICON_INDEX(MiniorCoreGreen,0),
      //ICON(MiniorCoreGreen, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreGreen,
[SPECIES_MINIOR_CORE_BLUE] = 
    {  
      //FRONT_PIC(MiniorCoreBlue),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreBlue),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreBlue),
      PIC_DATA_ICON_INDEX(MiniorCoreBlue,0),
      //ICON(MiniorCoreBlue, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreBlue,
[SPECIES_MINIOR_CORE_INDIGO] = 
    {  
      //FRONT_PIC(MiniorCoreIndigo),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreIndigo),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreIndigo),
      PIC_DATA_ICON_INDEX(MiniorCoreIndigo,0),
      //ICON(MiniorCoreIndigo, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreIndigo,
[SPECIES_MINIOR_CORE_VIOLET] = 
    {  
      //FRONT_PIC(MiniorCoreViolet),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MiniorCoreViolet),
      BACK_COORD(0x88,0),
      //PALETTES(MiniorCoreViolet),
      PIC_DATA_ICON_INDEX(MiniorCoreViolet,0),
      //ICON(MiniorCoreViolet, 0),
      .enemyMonElevation = 0,
    }, //MiniorCoreViolet,
[SPECIES_MIMIKYU_BUSTED] = 
    {  
      //FRONT_PIC(MimikyuBusted),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MimikyuBusted),
      BACK_COORD(0x88,0),
      //PALETTES(MimikyuBusted),
      PIC_DATA_ICON_INDEX(MimikyuBusted,0),
      //ICON(MimikyuBusted, 0),
      .enemyMonElevation = 0,
    }, //MimikyuBusted,
[SPECIES_NECROZMA_DUSK_MANE] = 
    {  
      //FRONT_PIC(NecrozmaDuskMane),
      FRONT_COORD(0x88,0),
      //BACK_PIC(NecrozmaDuskMane),
      BACK_COORD(0x88,0),
      //PALETTES(NecrozmaDuskMane),
      PIC_DATA_ICON_INDEX(NecrozmaDuskMane,0),
      //ICON(NecrozmaDuskMane, 0),
      .enemyMonElevation = 0,
    }, //NecrozmaDuskMane,
[SPECIES_NECROZMA_DAWN_WINGS] = 
    {  
      //FRONT_PIC(NecrozmaDawnWings),
      FRONT_COORD(0x88,0),
      //BACK_PIC(NecrozmaDawnWings),
      BACK_COORD(0x88,0),
      //PALETTES(NecrozmaDawnWings),
      PIC_DATA_ICON_INDEX(NecrozmaDawnWings,0),
      //ICON(NecrozmaDawnWings, 0),
      .enemyMonElevation = 0,
    }, //NecrozmaDawnWings,
[SPECIES_NECROZMA_ULTRA] = 
    {  
      //FRONT_PIC(NecrozmaUltra),
      FRONT_COORD(0x88,0),
      //BACK_PIC(NecrozmaUltra),
      BACK_COORD(0x88,0),
      //PALETTES(NecrozmaUltra),
      PIC_DATA_ICON_INDEX(NecrozmaUltra,0),
      //ICON(NecrozmaUltra, 0),
      .enemyMonElevation = 0,
    }, //NecrozmaUltra,
[SPECIES_MAGEARNA_ORIGINAL_COLOR] = 
    {  
      //FRONT_PIC(MagearnaOriginalColor),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MagearnaOriginalColor),
      BACK_COORD(0x88,0),
      //PALETTES(MagearnaOriginalColor),
      PIC_DATA_ICON_INDEX(MagearnaOriginalColor,0),
      //ICON(MagearnaOriginalColor, 0),
      .enemyMonElevation = 0,
    }, //MagearnaOriginalColor,
[SPECIES_CRAMORANT_GULPING] = 
    {  
      //FRONT_PIC(CramorantGulping),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CramorantGulping),
      BACK_COORD(0x88,0),
      //PALETTES(CramorantGulping),
      PIC_DATA_ICON_INDEX(CramorantGulping,0),
      //ICON(CramorantGulping, 0),
      .enemyMonElevation = 0,
    }, //Cramorant_Gulping,
[SPECIES_CRAMORANT_GORGING] = 
    {  
      //FRONT_PIC(CramorantGorging),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CramorantGorging),
      BACK_COORD(0x88,0),
      //PALETTES(CramorantGorging),
      PIC_DATA_ICON_INDEX(CramorantGorging,0),
      //ICON(CramorantGorging, 0),
      .enemyMonElevation = 0,
    }, //Cramorant_Gorging,
[SPECIES_TOXTRICITY_LOW_KEY] = 
    {  
      //FRONT_PIC(ToxtricityLowKey),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ToxtricityLowKey),
      BACK_COORD(0x88,0),
      //PALETTES(ToxtricityLowKey),
      PIC_DATA_ICON_INDEX(ToxtricityLowKey,0),
      //ICON(ToxtricityLowKey, 0),
      .enemyMonElevation = 0,
    }, //Toxtricity_Low_key,
      //[SPECIES_SINISTEA_ANTIQUE]                = gMonIcon_Sinistea_Antique,
      //[SPECIES_POLTEAGEIST_ANTIQUE]             = gMonIcon_PolteaGeist_Antique,
      
    //Alcremie forms
[SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStrawberryRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStrawberryMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStrawberryMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStrawberryLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStrawberrySaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberrySaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberrySaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberrySaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberrySaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieStrawberryRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieStrawberryCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieStrawberryRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStrawberryRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStrawberryRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStrawberryRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieStrawberryRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieBlueberryVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieBlueberryRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieBlueberryMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieBlueberryMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieBlueberryLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieBlueberrySaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberrySaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberrySaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberrySaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberrySaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieBlueberryRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieBlueberryCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_BLUEBERRY_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieBlueberryRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieBlueberryRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieBlueberryRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieBlueberryRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieBlueberryRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieLoveVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieLoveRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieLoveMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieLoveMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieLoveLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieLoveSaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveSaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveSaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveSaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveSaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieLoveRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieLoveCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieLoveRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieLoveRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieLoveRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieLoveRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieLoveRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStarVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStarRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStarMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStarMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStarLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieStarSaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarSaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarSaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarSaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarSaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieStarRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieStarCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieStarRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieStarRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieStarRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieStarRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieStarRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieCloverVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieCloverRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieCloverMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieCloverMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieCloverLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieCloverSaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverSaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverSaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverSaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverSaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieCloverRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieCloverCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieCloverRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieCloverRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieCloverRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieCloverRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieCloverRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieFlowerVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieFlowerRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieFlowerMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieFlowerMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieFlowerLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieFlowerSaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerSaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerSaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerSaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerSaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieFlowerRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieFlowerCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieFlowerRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieFlowerRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieFlowerRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieFlowerRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieFlowerRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieRibbonVanillaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonVanillaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonVanillaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonVanillaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonVanillaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_RUBY_CREAM] = 
    {  
      //FRONT_PIC(AlcremieRibbonRubyCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonRubyCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonRubyCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonRubyCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonRubyCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM] = 
    {  
      //FRONT_PIC(AlcremieRibbonMatchaCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonMatchaCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonMatchaCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonMatchaCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonMatchaCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_MINT_CREAM] = 
    {  
      //FRONT_PIC(AlcremieRibbonMintCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonMintCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonMintCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonMintCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonMintCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_LEMON_CREAM] = 
    {  
      //FRONT_PIC(AlcremieRibbonLemonCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonLemonCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonLemonCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonLemonCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonLemonCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_SALTED_CREAM] = 
    {  
      //FRONT_PIC(AlcremieRibbonSaltedCream),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonSaltedCream),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonSaltedCream), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonSaltedCream,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonSaltedCream, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieRibbonRubySwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonRubySwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonRubySwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonRubySwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonRubySwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieRibbonCaramelSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonCaramelSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonCaramelSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonCaramelSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonCaramelSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

[SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL] = 
    {  
      //FRONT_PIC(AlcremieRibbonRainbowSwirl),
      FRONT_COORD(0x88,0),
      //BACK_PIC(AlcremieRibbonRainbowSwirl),
      BACK_COORD(0x88,0),
      //PALETTES(AlcremieRibbonRainbowSwirl), //gMonPalette_AlcremieStrawberryVanillaCream
      PIC_DATA_ICON_INDEX(AlcremieRibbonRainbowSwirl,0), //gMonIcon_Alcremie
      //ICON(AlcremieRibbonRainbowSwirl, 0),
      .enemyMonElevation = 0,
    }, //AlcremieStrawberry,

    

[SPECIES_EISCUE_NOICE_FACE] = 
    {  
      //FRONT_PIC(EiscueNoiceFace),
      FRONT_COORD(0x88,0),
      //BACK_PIC(EiscueNoiceFace),
      BACK_COORD(0x88,0),
      //PALETTES(EiscueNoiceFace),
      PIC_DATA_ICON_INDEX(EiscueNoiceFace,0),
      //ICON(EiscueNoiceFace, 0),
      .enemyMonElevation = 0,
    }, //Eiscue_noice_face,
[SPECIES_INDEEDEE_FEMALE] = 
    {  
      //FRONT_PIC(Indeedee_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Indeedee_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Indeedee_Female),
      PIC_DATA_ICON_INDEX(Indeedee_Female,0),
      //ICON(IndeedeeFemale, 0),
      .enemyMonElevation = 0,
    }, //Indeedee_Female,
[SPECIES_MORPEKO_HANGRY] = 
    {  
      //FRONT_PIC(MorpekoHangry),
      FRONT_COORD(0x88,0),
      //BACK_PIC(MorpekoHangry),
      BACK_COORD(0x88,0),
      //PALETTES(MorpekoHangry),
      PIC_DATA_ICON_INDEX(MorpekoHangry,0),
      //ICON(MorpekoHangry, 0),
      .enemyMonElevation = 0,
    }, //Morpeko_Hangry,
[SPECIES_ZACIAN_CROWNED_SWORD] = 
    {  
      //FRONT_PIC(ZacianCrownedSword),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZacianCrownedSword),
      BACK_COORD(0x88,0),
      //PALETTES(ZacianCrownedSword),
      PIC_DATA_ICON_INDEX(ZacianCrownedSword,0),
      //ICON(ZacianCrownedSword, 0),
      .enemyMonElevation = 0,
    }, //Zacian_Crowned_Sword,
[SPECIES_ZAMAZENTA_CROWNED_SHIELD] = 
    {  
      //FRONT_PIC(ZamazentaCrownedShield),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZamazentaCrownedShield),
      BACK_COORD(0x88,0),
      //PALETTES(ZamazentaCrownedShield),
      PIC_DATA_ICON_INDEX(ZamazentaCrownedShield,0),
      //ICON(ZamazentaCrownedShield, 0),
      .enemyMonElevation = 0,
    }, //Zamazenta_Crowned_Shield,
[SPECIES_ETERNATUS_ETERNAMAX] = 
    {  
      //FRONT_PIC(EternatusEternamax),
      FRONT_COORD(0x88,0),
      //BACK_PIC(EternatusEternamax),
      BACK_COORD(0x88,0),
      //PALETTES(EternatusEternamax),
      PIC_DATA_ICON_INDEX(EternatusEternamax,0),
      //ICON(EternatusEternamax, 0),
      .enemyMonElevation = 0,
    }, //Eternatus_Eternamax,
[SPECIES_URSHIFU_RAPID_STRIKE_STYLE] = 
    {  
      FRONT_PIC(UrshifuRapidStrikeStyle),
      FRONT_COORD(0x88,0),
      BACK_PIC(UrshifuRapidStrikeStyle),
      BACK_COORD(0x88,0),
      PALETTES(UrshifuRapidStrikeStyle),
      //PIC_DATA_ICON_INDEX(UrshifuRapidStrikeStyle,0),
      ICON(Urshifu, 0),
      .enemyMonElevation = 0,
    }, //Urshifu_Rapid, //think last value needs no comma, nope doesn't matter but using comma is better in case you plan to add more
[SPECIES_ZARUDE_DADA] = 
    {  
      //FRONT_PIC(ZarudeDada),
      FRONT_COORD(0x88,0),
      //BACK_PIC(ZarudeDada),
      BACK_COORD(0x88,0),
      //PALETTES(ZarudeDada),
      PIC_DATA_ICON_INDEX(ZarudeDada,0),
      //ICON(ZarudeDada, 0),
      .enemyMonElevation = 0,
    }, //Zarude_Dada,
[SPECIES_CALYREX_ICE_RIDER] = 
    {  
      //FRONT_PIC(CalyrexIceRider),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CalyrexIceRider),
      BACK_COORD(0x88,0),
      //PALETTES(CalyrexIceRider),
      PIC_DATA_ICON_INDEX(CalyrexIceRider,0),
      //ICON(CalyrexIceRider, 0),
      .enemyMonElevation = 0,
    }, //Calyrex_Ice_Rider,
[SPECIES_CALYREX_SHADOW_RIDER] = 
    {  
      //FRONT_PIC(CalyrexShadowRider),
      FRONT_COORD(0x88,0),
      //BACK_PIC(CalyrexShadowRider),
      BACK_COORD(0x88,0),
      //PALETTES(CalyrexShadowRider),
      PIC_DATA_ICON_INDEX(CalyrexShadowRider,0), //names w dashes are in icons only, can be pushsed to pallete and front/back pics
      .enemyMonElevation = 0,
    }, //Calyrex_Shadow_Rider,
[SPECIES_BASCULEGION_FEMALE] = 
    {  
      //FRONT_PIC(Basculegion_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculegion_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Basculegion_Female),
      PIC_DATA_ICON_INDEX(BasculegionFemale,0),
      //ICON(BasculegionFemale, 0),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
[SPECIES_FRILLISH_FEMALE] = 
    {  
      //FRONT_PIC(Basculegion_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculegion_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Basculegion_Female),
      PIC_DATA_ICON_INDEX(FrillishFemale,0),
      //ICON(FrillishFemale, 0),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
[SPECIES_JELLICENT_FEMALE] = 
    {  
      //FRONT_PIC(Basculegion_Female),
      FRONT_COORD(0x88,0),
      //BACK_PIC(Basculegion_Female),
      BACK_COORD(0x88,0),
      //PALETTES(Basculegion_Female),
      PIC_DATA_ICON_INDEX(JellicentFemale,0),
      //ICON(JellicentFemale, 0),
      .enemyMonElevation = 0,
    }, //Basculegion_Female,
};