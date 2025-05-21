

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



//#define CRY_INFO(cry) (const struct ToneData[]) \
.type        = 0x20, \
.key    = 60, \
.length   = 0, \
.pan_sweep = 0,\
.wav     = (cry), \
.attack  = 0xff, \
.decay = 0, \
.sustain  = 0xff, \
.release = 0, 

//make 4 of these as mostly same just change first arguemnt
//cryinfo reverse
//cryinfo uncomp
//crinfo uncomp_reverse etcs
//talk w josh type first value stores compression and reverse together
/*
  .equiv TONEDATA_TYPE_CGB, 0x07
    .equiv TONEDATA_TYPE_FIX, 0x08
    .equiv TONEDATA_TYPE_REV, 0x10
    .equiv TONEDATA_TYPE_CMP, 0x20
    .equiv TONEDATA_TYPE_SPL, 0x40 @ key split
    .equiv TONEDATA_TYPE_RHY, 0x80 @ rhythm
add value to .type if true
*/

#define CRY_INFO(...) (struct ToneData[]) { 0x20, 60, 0, 0, (struct WaveData *) __VA_ARGS__, 0xff, 0, 0xff, 0}
#define CRY_INFO_REVERSE(...) (struct ToneData[]) { 0x30, 60, 0, 0, (struct WaveData *) __VA_ARGS__, 0xff, 0, 0xff, 0}
#define CRY_INFO_UNCOMP(...) (struct ToneData[]) { 0x0, 60, 0, 0, (struct WaveData *) __VA_ARGS__, 0xff, 0, 0xff, 0}
#define CRY_INFO_REVERSE_UNCOMP(...) (struct ToneData[]) { 0x10, 60, 0, 0, (struct WaveData *) __VA_ARGS__, 0xff, 0, 0xff, 0}

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

//Vsonic IMPORTANT
//note still need set enemyMonElevation from EE for all mon post gen 3
//do with python make dictionary of species with non 0 elevations in their files
//as key with elevation as entry
//other idea, can take the line rather than just the value,
//as EE also uses .enemyMonElevation = value,

//whichever I need make global table to hold values  as I loop over all the base stat files
//in EE because they decided to separate them into separte files smh
//so in order I'd have to get the data of Gen_4_families - Gen_9_families
//then match species of this file with those found w non 0 elevations there
//and replace elevation 0 here


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
      .cryData = CRY_NONE,
      .cryData_Reverse = CRY_NONE,
}, //QuestionMark, 
[SPECIES_BULBASAUR] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x64, 0x10),
      PIC_DATA_ICON_INDEX(Bulbasaur, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bulbasaur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bulbasaur),
}, //Bulbasaur,
[SPECIES_IVYSAUR] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Ivysaur, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ivysaur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ivysaur),
}, //Ivysaur,
[SPECIES_VENUSAUR] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Venusaur, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Venusaur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Venusaur),
}, //Venusaur,
[SPECIES_CHARMANDER] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Charmander, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Charmander),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Charmander),
}, //Charmander,
[SPECIES_CHARMELEON] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Charmeleon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Charmeleon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Charmeleon),
}, //Charmeleon,
[SPECIES_CHARIZARD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Charizard, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Charizard),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Charizard),
}, //Charizard,
[SPECIES_SQUIRTLE] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x75, 0x0f),
      PIC_DATA_ICON_INDEX(Squirtle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Squirtle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Squirtle),
}, //Squirtle,
[SPECIES_WARTORTLE] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Wartortle, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wartortle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wartortle),
}, //Wartortle,
[SPECIES_BLASTOISE] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Blastoise, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Blastoise),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Blastoise),
}, //Blastoise,
[SPECIES_CATERPIE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x55, 0x0f),
      PIC_DATA_ICON_INDEX(Caterpie, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Caterpie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Caterpie),
}, //Caterpie,
[SPECIES_METAPOD] = 
    {  
      FRONT_COORD(0x54, 14),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Metapod, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Metapod),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Metapod),
}, //Metapod,
[SPECIES_BUTTERFREE] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Butterfree, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Butterfree),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Butterfree),
}, //Butterfree,
[SPECIES_WEEDLE] = 
    {  
      FRONT_COORD(0x54, 13),
      BACK_COORD(0x56, 0x0b),
      PIC_DATA_ICON_INDEX(Weedle, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Weedle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Weedle),
}, //Weedle,
[SPECIES_KAKUNA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x46, 0x0a),
      PIC_DATA_ICON_INDEX(Kakuna, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kakuna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kakuna),
}, //Kakuna,
[SPECIES_BEEDRILL] = 
    {  
      FRONT_COORD(0x86, 5),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Beedrill, 2),
      .enemyMonElevation = 9,
      .cryData = CRY_INFO(Cry_Beedrill),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Beedrill),
}, //Beedrill,
[SPECIES_PIDGEY] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Pidgey, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pidgey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pidgey),
}, //Pidgey,
[SPECIES_PIDGEOTTO] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Pidgeotto, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pidgeotto),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pidgeotto),
}, //Pidgeotto,
[SPECIES_PIDGEOT] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Pidgeot, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Pidgeot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pidgeot),
}, //Pidgeot,
[SPECIES_RATTATA] = 
    {  
      FRONT_COORD(0x44, 13),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Rattata, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rattata),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rattata),
}, //Rattata,
[SPECIES_RATICATE] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Raticate, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Raticate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Raticate),
}, //Raticate,
[SPECIES_SPEAROW] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Spearow, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spearow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spearow),
}, //Spearow,
[SPECIES_FEAROW] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Fearow, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Fearow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fearow),
}, //Fearow,
[SPECIES_EKANS] = 
    {  
      FRONT_COORD(0x65, 10),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Ekans, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ekans),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ekans),
}, //Ekans,
[SPECIES_ARBOK] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Arbok, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arbok),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arbok),
}, //Arbok,
[SPECIES_PIKACHU] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Pikachu, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //Pikachu,
[SPECIES_RAICHU] = 
    {  
      FRONT_COORD(0x67, 3),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Raichu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Raichu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Raichu),
}, //Raichu,
[SPECIES_SANDSHREW] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Sandshrew, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandshrew),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandshrew),
}, //Sandshrew,
[SPECIES_SANDSLASH] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Sandslash, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandslash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandslash),
}, //Sandslash,
[SPECIES_NIDORAN_F] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x55, 0x0c),
      PIC_DATA_ICON_INDEX(NidoranF, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_NidoranF),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_NidoranF),
}, //NidoranF,
[SPECIES_NIDORINA] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Nidorina, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nidorina),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nidorina),
}, //Nidorina,
[SPECIES_NIDOQUEEN] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Nidoqueen, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nidoqueen),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nidoqueen),
}, //Nidoqueen,
[SPECIES_NIDORAN_M] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x56, 0x08),
      PIC_DATA_ICON_INDEX(NidoranM, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_NidoranM),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_NidoranM),
}, //NidoranM,
[SPECIES_NIDORINO] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Nidorino, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nidorino),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nidorino),
}, //Nidorino,
[SPECIES_NIDOKING] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Nidoking, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nidoking),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nidoking),
}, //Nidoking,
[SPECIES_CLEFAIRY] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Clefairy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clefairy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clefairy),
}, //Clefairy,
[SPECIES_CLEFABLE] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Clefable, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clefable),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clefable),
}, //Clefable,
[SPECIES_VULPIX] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Vulpix, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vulpix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vulpix),
}, //Vulpix,
[SPECIES_NINETALES] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Ninetales, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ninetales),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ninetales),
}, //Ninetales,
[SPECIES_JIGGLYPUFF] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Jigglypuff, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Jigglypuff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jigglypuff),
}, //Jigglypuff,
[SPECIES_WIGGLYTUFF] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Wigglytuff, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wigglytuff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wigglytuff),
}, //Wigglytuff,
[SPECIES_ZUBAT] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Zubat, 2),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Zubat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zubat),
}, //Zubat,
[SPECIES_GOLBAT] = 
    {  
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Golbat, 2),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Golbat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golbat),
}, //Golbat,
[SPECIES_ODDISH] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Oddish, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Oddish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Oddish),
}, //Oddish,
[SPECIES_GLOOM] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Gloom, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gloom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gloom),
}, //Gloom,
[SPECIES_VILEPLUME] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Vileplume, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vileplume),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vileplume),
}, //Vileplume,
[SPECIES_PARAS] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x63, 0x14),
      PIC_DATA_ICON_INDEX(Paras, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Paras),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Paras),
}, //Paras,
[SPECIES_PARASECT] = 
    {  
      FRONT_COORD(0x86, 7),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Parasect, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Parasect),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Parasect),
}, //Parasect,
[SPECIES_VENONAT] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Venonat, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Venonat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Venonat),
}, //Venonat,
[SPECIES_VENOMOTH] = 
    {  
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Venomoth, 2),
      .enemyMonElevation = 11,
      .cryData = CRY_INFO(Cry_Venomoth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Venomoth),
}, //Venomoth,
[SPECIES_DIGLETT] = 
    {  
      FRONT_COORD(0x54, 17),
      BACK_COORD(0x54, 0x10),
      PIC_DATA_ICON_INDEX(Diglett, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Diglett),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Diglett),
}, //Diglett,
[SPECIES_DUGTRIO] = 
    {  
      FRONT_COORD(0x75, 11),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Dugtrio, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dugtrio),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dugtrio),
}, //Dugtrio,
[SPECIES_MEOWTH] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Meowth, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meowth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meowth),
}, //Meowth,
[SPECIES_PERSIAN] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Persian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Persian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Persian),
}, //Persian,
[SPECIES_PSYDUCK] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x67, 0x07),
      PIC_DATA_ICON_INDEX(Psyduck, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Psyduck),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Psyduck),
}, //Psyduck,
[SPECIES_GOLDUCK] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Golduck, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Golduck),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golduck),
}, //Golduck,
[SPECIES_MANKEY] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Mankey, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mankey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mankey),
}, //Mankey,
[SPECIES_PRIMEAPE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Primeape, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Primeape),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Primeape),
}, //Primeape,
[SPECIES_GROWLITHE] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Growlithe, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Growlithe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Growlithe),
}, //Growlithe,
[SPECIES_ARCANINE] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Arcanine, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arcanine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arcanine),
}, //Arcanine,
[SPECIES_POLIWAG] = 
    {  
      FRONT_COORD(0x74, 13),
      BACK_COORD(0x74, 0x10),
      PIC_DATA_ICON_INDEX(Poliwag, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Poliwag),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poliwag),
}, //Poliwag,
[SPECIES_POLIWHIRL] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Poliwhirl, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Poliwhirl),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poliwhirl),
}, //Poliwhirl,
[SPECIES_POLIWRATH] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Poliwrath, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Poliwrath),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poliwrath),
}, //Poliwrath,
[SPECIES_ABRA] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x55, 0x0c),
      PIC_DATA_ICON_INDEX(Abra, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Abra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Abra),
}, //Abra,
[SPECIES_KADABRA] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Kadabra, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kadabra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kadabra),
}, //Kadabra,
[SPECIES_ALAKAZAM] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Alakazam, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alakazam),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alakazam),
}, //Alakazam,
[SPECIES_MACHOP] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Machop, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Machop),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Machop),
}, //Machop,
[SPECIES_MACHOKE] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Machoke, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Machoke),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Machoke),
}, //Machoke,
[SPECIES_MACHAMP] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x67, 0x04),
      PIC_DATA_ICON_INDEX(Machamp, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Machamp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Machamp),
}, //Machamp,
[SPECIES_BELLSPROUT] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Bellsprout, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bellsprout),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bellsprout),
}, //Bellsprout,
[SPECIES_WEEPINBELL] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Weepinbell, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Weepinbell),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Weepinbell),
}, //Weepinbell,
[SPECIES_VICTREEBEL] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Victreebel, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Victreebel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Victreebel),
}, //Victreebel,
[SPECIES_TENTACOOL] = 
    {  
      FRONT_COORD(0x46, 7),
      BACK_COORD(0x56, 0x0a),
      PIC_DATA_ICON_INDEX(Tentacool, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tentacool),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tentacool),
}, //Tentacool,
[SPECIES_TENTACRUEL] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Tentacruel, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tentacruel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tentacruel),
}, //Tentacruel,
[SPECIES_GEODUDE] = 
    {  
      FRONT_COORD(0x54, 10),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Geodude, 1),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Geodude),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Geodude),
}, //Geodude,
[SPECIES_GRAVELER] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x75, 0x0c),
      PIC_DATA_ICON_INDEX(Graveler, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Graveler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Graveler),
}, //Graveler,
[SPECIES_GOLEM] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Golem, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Golem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golem),
}, //Golem,
[SPECIES_PONYTA] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Ponyta, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ponyta),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ponyta),
}, //Ponyta,
[SPECIES_RAPIDASH] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Rapidash, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rapidash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rapidash),
}, //Rapidash,
[SPECIES_SLOWPOKE] = 
    {  
      FRONT_COORD(0x66, 16),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Slowpoke, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slowpoke),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slowpoke),
}, //Slowpoke,
[SPECIES_SLOWBRO] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Slowbro, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slowbro),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slowbro),
}, //Slowbro,
[SPECIES_MAGNEMITE] = 
    {  
      FRONT_COORD(0x43, 20),
      BACK_COORD(0x43, 0x14),
      PIC_DATA_ICON_INDEX(Magnemite, 0),
      .enemyMonElevation = 16,
      .cryData = CRY_INFO(Cry_Magnemite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magnemite),
}, //Magnemite,
[SPECIES_MAGNETON] = 
    {  
      FRONT_COORD(0x76, 7),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Magneton, 0),
      .enemyMonElevation = 11,
      .cryData = CRY_INFO(Cry_Magneton),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magneton),
}, //Magneton,
[SPECIES_FARFETCHD] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Farfetchd, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Farfetchd),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Farfetchd),
}, //Farfetchd,
[SPECIES_DODUO] = 
    {  
      FRONT_COORD(0x57, 7),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Doduo, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Doduo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Doduo),
}, //Doduo,
[SPECIES_DODRIO] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Dodrio, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dodrio),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dodrio),
}, //Dodrio,
[SPECIES_SEEL] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Seel, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Seel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Seel),
}, //Seel,
[SPECIES_DEWGONG] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Dewgong, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dewgong),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dewgong),
}, //Dewgong,
[SPECIES_GRIMER] = 
    {  
      FRONT_COORD(0x65, 9),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Grimer, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grimer),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grimer),
}, //Grimer,
[SPECIES_MUK] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Muk, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Muk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Muk),
}, //Muk,
[SPECIES_SHELLDER] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Shellder, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shellder),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shellder),
}, //Shellder,
[SPECIES_CLOYSTER] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Cloyster, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cloyster),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cloyster),
}, //Cloyster,
[SPECIES_GASTLY] = 
    {  
      FRONT_COORD(0x77, 13),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Gastly, 2),
      .enemyMonElevation = 5,
      .cryData = CRY_INFO(Cry_Gastly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gastly),
}, //Gastly,
[SPECIES_HAUNTER] = 
    {  
      FRONT_COORD(0x77, 13),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Haunter, 2),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Haunter),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Haunter),
}, //Haunter,
[SPECIES_GENGAR] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Gengar, 2),
      .enemyMonElevation = 1,
      .cryData = CRY_INFO(Cry_Gengar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gengar),
}, //Gengar,
[SPECIES_ONIX] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Onix, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Onix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Onix),
}, //Onix,
[SPECIES_DROWZEE] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Drowzee, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drowzee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drowzee),
}, //Drowzee,
[SPECIES_HYPNO] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Hypno, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hypno),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hypno),
}, //Hypno,
[SPECIES_KRABBY] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Krabby, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Krabby),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Krabby),
}, //Krabby,
[SPECIES_KINGLER] = 
    {  
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Kingler, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kingler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kingler),
}, //Kingler,
[SPECIES_VOLTORB] = 
    {  
      FRONT_COORD(0x44, 10),
      BACK_COORD(0x55, 0x0e),
      PIC_DATA_ICON_INDEX(Voltorb, 0),
      .enemyMonElevation = 1,
      .cryData = CRY_INFO(Cry_Voltorb),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Voltorb),
}, //Voltorb,
[SPECIES_ELECTRODE] = 
    {  
      FRONT_COORD(0x55, 6),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Electrode, 0),
      .enemyMonElevation = 1,
      .cryData = CRY_INFO(Cry_Electrode),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Electrode),
}, //Electrode,
[SPECIES_EXEGGCUTE] = 
    {  
      FRONT_COORD(0x87, 12),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Exeggcute, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Exeggcute),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Exeggcute),
}, //Exeggcute,
[SPECIES_EXEGGUTOR] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Exeggutor, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Exeggutor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Exeggutor),
}, //Exeggutor,
[SPECIES_CUBONE] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Cubone, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cubone),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cubone),
}, //Cubone,
[SPECIES_MAROWAK] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Marowak, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Marowak),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Marowak),
}, //Marowak,
[SPECIES_HITMONLEE] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Hitmonlee, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hitmonlee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hitmonlee),
}, //Hitmonlee,
[SPECIES_HITMONCHAN] = 
    {  
      FRONT_COORD(0x67, 3),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Hitmonchan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hitmonchan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hitmonchan),
}, //Hitmonchan,
[SPECIES_LICKITUNG] = 
    {  
      FRONT_COORD(0x86, 7),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Lickitung, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lickitung),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lickitung),
}, //Lickitung,
[SPECIES_KOFFING] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Koffing, 2),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Koffing),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Koffing),
}, //Koffing,
[SPECIES_WEEZING] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Weezing, 2),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Weezing),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Weezing),
}, //Weezing,
[SPECIES_RHYHORN] = 
    {  
      FRONT_COORD(0x76, 12),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Rhyhorn, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rhyhorn),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rhyhorn),
}, //Rhyhorn,
[SPECIES_RHYDON] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Rhydon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rhydon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rhydon),
}, //Rhydon,
[SPECIES_CHANSEY] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Chansey, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chansey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chansey),
}, //Chansey,
[SPECIES_TANGELA] = 
    {  
      FRONT_COORD(0x67, 12),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Tangela, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tangela),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tangela),
}, //Tangela,
[SPECIES_KANGASKHAN] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Kangaskhan, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kangaskhan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kangaskhan),
}, //Kangaskhan,
[SPECIES_HORSEA] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Horsea, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Horsea),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Horsea),
}, //Horsea,
[SPECIES_SEADRA] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Seadra, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Seadra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Seadra),
}, //Seadra,
[SPECIES_GOLDEEN] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Goldeen, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Goldeen),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Goldeen),
}, //Goldeen,
[SPECIES_SEAKING] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Seaking, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Seaking),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Seaking),
}, //Seaking,
[SPECIES_STARYU] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Staryu, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Staryu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Staryu),
}, //Staryu,
[SPECIES_STARMIE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Starmie, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Starmie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Starmie),
}, //Starmie,
[SPECIES_MR_MIME] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(MrMime, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MrMime),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MrMime),
}, //MrMime,
[SPECIES_SCYTHER] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Scyther, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scyther),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scyther),
}, //Scyther,
[SPECIES_JYNX] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Jynx, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Jynx),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jynx),
}, //Jynx,
[SPECIES_ELECTABUZZ] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Electabuzz, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Electabuzz),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Electabuzz),
}, //Electabuzz,
[SPECIES_MAGMAR] = 
    {  
      FRONT_COORD(0x77, 4),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Magmar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magmar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magmar),
}, //Magmar,
[SPECIES_PINSIR] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Pinsir, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pinsir),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pinsir),
}, //Pinsir,
[SPECIES_TAUROS] = 
    {  
      FRONT_COORD(0x78, 5),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Tauros, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tauros),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tauros),
}, //Tauros,
[SPECIES_MAGIKARP] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Magikarp, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magikarp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magikarp),
}, //Magikarp,
[SPECIES_GYARADOS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Gyarados, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gyarados),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gyarados),
}, //Gyarados,
[SPECIES_LAPRAS] = 
    {  
      FRONT_COORD(0x85, 2),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Lapras, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lapras),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lapras),
}, //Lapras,
[SPECIES_DITTO] = 
    {  
      FRONT_COORD(0x54, 15),
      BACK_COORD(0x54, 0x11),
      PIC_DATA_ICON_INDEX(Ditto, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ditto),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ditto),
}, //Ditto,
[SPECIES_EEVEE] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Eevee, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Eevee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Eevee),
}, //Eevee,
[SPECIES_VAPOREON] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Vaporeon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vaporeon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vaporeon),
}, //Vaporeon,
[SPECIES_JOLTEON] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Jolteon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Jolteon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jolteon),
}, //Jolteon,
[SPECIES_FLAREON] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Flareon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Flareon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flareon),
}, //Flareon,
[SPECIES_PORYGON] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Porygon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Porygon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Porygon),
}, //Porygon,
[SPECIES_OMANYTE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Omanyte, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Omanyte),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Omanyte),
}, //Omanyte,
[SPECIES_OMASTAR] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Omastar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Omastar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Omastar),
}, //Omastar,
[SPECIES_KABUTO] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Kabuto, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kabuto),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kabuto),
}, //Kabuto,
[SPECIES_KABUTOPS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Kabutops, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kabutops),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kabutops),
}, //Kabutops,
[SPECIES_AERODACTYL] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Aerodactyl, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Aerodactyl),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aerodactyl),
}, //Aerodactyl,
[SPECIES_SNORLAX] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Snorlax, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Snorlax),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Snorlax),
}, //Snorlax,
[SPECIES_ARTICUNO] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Articuno, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Articuno),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Articuno),
}, //Articuno,
[SPECIES_ZAPDOS] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Zapdos, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Zapdos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zapdos),
}, //Zapdos,
[SPECIES_MOLTRES] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Moltres, 0),
      .enemyMonElevation = 5,
      .cryData = CRY_INFO(Cry_Moltres),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Moltres),
}, //Moltres,
[SPECIES_DRATINI] = 
    {  
      FRONT_COORD(0x75, 9),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Dratini, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dratini),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dratini),
}, //Dratini,
[SPECIES_DRAGONAIR] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Dragonair, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dragonair),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dragonair),
}, //Dragonair,
[SPECIES_DRAGONITE] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Dragonite, 2),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Dragonite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dragonite),
}, //Dragonite,
[SPECIES_MEWTWO] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x01),
      PIC_DATA_ICON_INDEX(Mewtwo, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mewtwo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mewtwo),
}, //Mewtwo,
[SPECIES_MEW] = 
    {  
      FRONT_COORD(0x55, 9),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Mew, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Mew),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mew),
}, //Mew,
[SPECIES_CHIKORITA] = 
    {  
      FRONT_COORD(0x75, 10),
      BACK_COORD(0x56, 0x0a),
      PIC_DATA_ICON_INDEX(Chikorita, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chikorita),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chikorita),
}, //Chikorita,
[SPECIES_BAYLEEF] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Bayleef, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bayleef),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bayleef),
}, //Bayleef,
[SPECIES_MEGANIUM] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Meganium, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meganium),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meganium),
}, //Meganium,
[SPECIES_CYNDAQUIL] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Cyndaquil, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cyndaquil),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cyndaquil),
}, //Cyndaquil,
[SPECIES_QUILAVA] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Quilava, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Quilava),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Quilava),
}, //Quilava,
[SPECIES_TYPHLOSION] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Typhlosion, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Typhlosion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Typhlosion),
}, //Typhlosion,
[SPECIES_TOTODILE] = 
    {  
      FRONT_COORD(0x55, 14),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Totodile, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Totodile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Totodile),
}, //Totodile,
[SPECIES_CROCONAW] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x67, 0x07),
      PIC_DATA_ICON_INDEX(Croconaw, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Croconaw),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Croconaw),
}, //Croconaw,
[SPECIES_FERALIGATOR] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Feraligator, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Feraligator),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Feraligator),
}, //Feraligator,
[SPECIES_SENTRET] = 
    {  
      FRONT_COORD(0x47, 2),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Sentret, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sentret),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sentret),
}, //Sentret,
[SPECIES_FURRET] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Furret, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furret),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furret),
}, //Furret,
[SPECIES_HOOTHOOT] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Hoothoot, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hoothoot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hoothoot),
}, //Hoothoot,
[SPECIES_NOCTOWL] = 
    {  
      FRONT_COORD(0x58, 2),
      BACK_COORD(0x68, 0x03),
      PIC_DATA_ICON_INDEX(Noctowl, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Noctowl),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Noctowl),
}, //Noctowl,
[SPECIES_LEDYBA] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Ledyba, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Ledyba),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ledyba),
}, //Ledyba,
[SPECIES_LEDIAN] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Ledian, 0),
      .enemyMonElevation = 11,
      .cryData = CRY_INFO(Cry_Ledian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ledian),
}, //Ledian,
[SPECIES_SPINARAK] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x73, 0x15),
      PIC_DATA_ICON_INDEX(Spinarak, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spinarak),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spinarak),
}, //Spinarak,
[SPECIES_ARIADOS] = 
    {  
      FRONT_COORD(0x87, 6),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Ariados, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ariados),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ariados),
}, //Ariados,
[SPECIES_CROBAT] = 
    {  
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Crobat, 2),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Crobat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Crobat),
}, //Crobat,
[SPECIES_CHINCHOU] = 
    {  
      FRONT_COORD(0x75, 12),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Chinchou, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chinchou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chinchou),
}, //Chinchou,
[SPECIES_LANTURN] = 
    {  
      FRONT_COORD(0x87, 11),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Lanturn, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lanturn),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lanturn),
}, //Lanturn,
[SPECIES_PICHU] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Pichu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pichu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pichu),
}, //Pichu,
[SPECIES_CLEFFA] = 
    {  
      FRONT_COORD(0x44, 18),
      BACK_COORD(0x65, 0x0f),
      PIC_DATA_ICON_INDEX(Cleffa, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cleffa),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cleffa),
}, //Cleffa,
[SPECIES_IGGLYBUFF] = 
    {  
      FRONT_COORD(0x44, 17),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Igglybuff, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Igglybuff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Igglybuff),
}, //Igglybuff,
[SPECIES_TOGEPI] = 
    {  
      FRONT_COORD(0x34, 16),
      BACK_COORD(0x54, 0x10),
      PIC_DATA_ICON_INDEX(Togepi, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Togepi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Togepi),
}, //Togepi,
[SPECIES_TOGETIC] = 
    {  
      FRONT_COORD(0x46, 8),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Togetic, 2),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Togetic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Togetic),
}, //Togetic,
[SPECIES_NATU] = 
    {  
      FRONT_COORD(0x44, 17),
      BACK_COORD(0x54, 0x11),
      PIC_DATA_ICON_INDEX(Natu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Natu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Natu),
}, //Natu,
[SPECIES_XATU] = 
    {  
      FRONT_COORD(0x47, 5),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Xatu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Xatu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Xatu),
}, //Xatu,
[SPECIES_MAREEP] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Mareep, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mareep),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mareep),
}, //Mareep,
[SPECIES_FLAAFFY] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Flaaffy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Flaaffy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flaaffy),
}, //Flaaffy,
[SPECIES_AMPHAROS] = 
    {  
      FRONT_COORD(0x77, 2),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Ampharos, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ampharos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ampharos),
}, //Ampharos,
[SPECIES_BELLOSSOM] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Bellossom, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bellossom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bellossom),
}, //Bellossom,
[SPECIES_MARILL] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x75, 0x0c),
      PIC_DATA_ICON_INDEX(Marill, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Marill),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Marill),
}, //Marill,
[SPECIES_AZUMARILL] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Azumarill, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Azumarill),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Azumarill),
}, //Azumarill,
[SPECIES_SUDOWOODO] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Sudowoodo, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sudowoodo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sudowoodo),
}, //Sudowoodo,
[SPECIES_POLITOED] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Politoed, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Politoed),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Politoed),
}, //Politoed,
[SPECIES_HOPPIP] = 
    {  
      FRONT_COORD(0x66, 14),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Hoppip, 1),
      .enemyMonElevation = 13,
      .cryData = CRY_INFO(Cry_Hoppip),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hoppip),
}, //Hoppip,
[SPECIES_SKIPLOOM] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x65, 0x0d),
      PIC_DATA_ICON_INDEX(Skiploom, 1),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Skiploom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skiploom),
}, //Skiploom,
[SPECIES_JUMPLUFF] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Jumpluff, 2),
      .enemyMonElevation = 18,
      .cryData = CRY_INFO(Cry_Jumpluff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jumpluff),
}, //Jumpluff,
[SPECIES_AIPOM] = 
    {  
      FRONT_COORD(0x58, 1),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Aipom, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aipom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aipom),
}, //Aipom,
[SPECIES_SUNKERN] = 
    {  
      FRONT_COORD(0x44, 17),
      BACK_COORD(0x56, 0x0a),
      PIC_DATA_ICON_INDEX(Sunkern, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sunkern),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sunkern),
}, //Sunkern,
[SPECIES_SUNFLORA] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Sunflora, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sunflora),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sunflora),
}, //Sunflora,
[SPECIES_YANMA] = 
    {  
      FRONT_COORD(0x86, 14),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Yanma, 1),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Yanma),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yanma),
}, //Yanma,
[SPECIES_WOOPER] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Wooper, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wooper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wooper),
}, //Wooper,
[SPECIES_QUAGSIRE] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Quagsire, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Quagsire),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Quagsire),
}, //Quagsire,
[SPECIES_ESPEON] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Espeon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Espeon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Espeon),
}, //Espeon,
[SPECIES_UMBREON] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Umbreon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Umbreon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Umbreon),
}, //Umbreon,
[SPECIES_MURKROW] = 
    {  
      FRONT_COORD(0x66, 15),
      BACK_COORD(0x66, 0x09),
      PIC_DATA_ICON_INDEX(Murkrow, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Murkrow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Murkrow),
}, //Murkrow,
[SPECIES_SLOWKING] = 
    {  
      FRONT_COORD(0x58, 1),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Slowking, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slowking),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slowking),
}, //Slowking,
[SPECIES_MISDREAVUS] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Misdreavus, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Misdreavus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Misdreavus),
}, //Misdreavus,
[SPECIES_UNOWN] = 
    {  
      FRONT_COORD(0x35, 15),
      BACK_COORD(0x36, 0x08),
      PIC_DATA_ICON_INDEX(Unown, 0),
      .enemyMonElevation = 14,
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
}, //Unown,
[SPECIES_WOBBUFFET] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x75, 0x0c),
      PIC_DATA_ICON_INDEX(Wobbuffet, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wobbuffet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wobbuffet),
}, //Wobbuffet,
[SPECIES_GIRAFARIG] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Girafarig, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Girafarig),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Girafarig),
}, //Girafarig,
[SPECIES_PINECO] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x65, 0x0f),
      PIC_DATA_ICON_INDEX(Pineco, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pineco),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pineco),
}, //Pineco,
[SPECIES_FORRETRESS] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Forretress, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Forretress),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Forretress),
}, //Forretress,
[SPECIES_DUNSPARCE] = 
    {  
      FRONT_COORD(0x74, 9),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Dunsparce, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dunsparce),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dunsparce),
}, //Dunsparce,
[SPECIES_GLIGAR] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Gligar, 2),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Gligar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gligar),
}, //Gligar,
[SPECIES_STEELIX] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Steelix, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Steelix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Steelix),
}, //Steelix,
[SPECIES_SNUBBULL] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Snubbull, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Snubbull),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Snubbull),
}, //Snubbull,
[SPECIES_GRANBULL] = 
    {  
      FRONT_COORD(0x57, 4),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Granbull, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Granbull),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Granbull),
}, //Granbull,
[SPECIES_QWILFISH] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Qwilfish, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Qwilfish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Qwilfish),
}, //Qwilfish,
[SPECIES_SCIZOR] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Scizor, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Scizor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scizor),
}, //Scizor,
[SPECIES_SHUCKLE] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x56, 0x0b),
      PIC_DATA_ICON_INDEX(Shuckle, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shuckle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shuckle),
}, //Shuckle,
[SPECIES_HERACROSS] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Heracross, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Heracross),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Heracross),
}, //Heracross,
[SPECIES_SNEASEL] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Sneasel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sneasel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sneasel),
}, //Sneasel,
[SPECIES_TEDDIURSA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Teddiursa, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Teddiursa),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Teddiursa),
}, //Teddiursa,
[SPECIES_URSARING] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Ursaring, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ursaring),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ursaring),
}, //Ursaring,
[SPECIES_SLUGMA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Slugma, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slugma),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slugma),
}, //Slugma,
[SPECIES_MAGCARGO] = 
    {  
      FRONT_COORD(0x57, 6),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Magcargo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magcargo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magcargo),
}, //Magcargo,
[SPECIES_SWINUB] = 
    {  
      FRONT_COORD(0x43, 18),
      BACK_COORD(0x63, 0x15),
      PIC_DATA_ICON_INDEX(Swinub, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swinub),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swinub),
}, //Swinub,
[SPECIES_PILOSWINE] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Piloswine, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Piloswine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Piloswine),
}, //Piloswine,
[SPECIES_CORSOLA] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Corsola, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Corsola),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Corsola),
}, //Corsola,
[SPECIES_REMORAID] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x75, 0x0d),
      PIC_DATA_ICON_INDEX(Remoraid, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Remoraid),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Remoraid),
}, //Remoraid,
[SPECIES_OCTILLERY] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Octillery, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Octillery),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Octillery),
}, //Octillery,
[SPECIES_DELIBIRD] = 
    {  
      FRONT_COORD(0x56, 7),
      BACK_COORD(0x67, 0x06),
      PIC_DATA_ICON_INDEX(Delibird, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Delibird),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Delibird),
}, //Delibird,
[SPECIES_MANTINE] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Mantine, 2),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Mantine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mantine),
}, //Mantine,
[SPECIES_SKARMORY] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Skarmory, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skarmory),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skarmory),
}, //Skarmory,
[SPECIES_HOUNDOUR] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x55, 0x0c),
      PIC_DATA_ICON_INDEX(Houndour, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Houndour),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Houndour),
}, //Houndour,
[SPECIES_HOUNDOOM] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Houndoom, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Houndoom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Houndoom),
}, //Houndoom,
[SPECIES_KINGDRA] = 
    {  
      FRONT_COORD(0x78, 1),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Kingdra, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kingdra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kingdra),
}, //Kingdra,
[SPECIES_PHANPY] = 
    {  
      FRONT_COORD(0x54, 16),
      BACK_COORD(0x65, 0x0e),
      PIC_DATA_ICON_INDEX(Phanpy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Phanpy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Phanpy),
}, //Phanpy,
[SPECIES_DONPHAN] = 
    {  
      FRONT_COORD(0x86, 9),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Donphan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Donphan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Donphan),
}, //Donphan,
[SPECIES_PORYGON2] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Porygon2, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Porygon2),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Porygon2),
}, //Porygon2,
[SPECIES_STANTLER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x03),
      PIC_DATA_ICON_INDEX(Stantler, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stantler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stantler),
}, //Stantler,
[SPECIES_SMEARGLE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Smeargle, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Smeargle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Smeargle),
}, //Smeargle,
[SPECIES_TYROGUE] = 
    {  
      FRONT_COORD(0x46, 9),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Tyrogue, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tyrogue),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tyrogue),
}, //Tyrogue,
[SPECIES_HITMONTOP] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Hitmontop, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hitmontop),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hitmontop),
}, //Hitmontop,
[SPECIES_SMOOCHUM] = 
    {  
      FRONT_COORD(0x35, 13),
      BACK_COORD(0x56, 0x09),
      PIC_DATA_ICON_INDEX(Smoochum, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Smoochum),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Smoochum),
}, //Smoochum,
[SPECIES_ELEKID] = 
    {  
      FRONT_COORD(0x76, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Elekid, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Elekid),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Elekid),
}, //Elekid,
[SPECIES_MAGBY] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Magby, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magby),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magby),
}, //Magby,
[SPECIES_MILTANK] = 
    {  
      FRONT_COORD(0x77, 8),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Miltank, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Miltank),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Miltank),
}, //Miltank,
[SPECIES_BLISSEY] = 
    {  
      FRONT_COORD(0x77, 5),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Blissey, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Blissey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Blissey),
}, //Blissey,
[SPECIES_RAIKOU] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Raikou, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Raikou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Raikou),
}, //Raikou,
[SPECIES_ENTEI] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Entei, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Entei),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Entei),
}, //Entei,
[SPECIES_SUICUNE] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Suicune, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Suicune),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Suicune),
}, //Suicune,
[SPECIES_LARVITAR] = 
    {  
      FRONT_COORD(0x46, 10),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Larvitar, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Larvitar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Larvitar),
}, //Larvitar,
[SPECIES_PUPITAR] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Pupitar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pupitar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pupitar),
}, //Pupitar,
[SPECIES_TYRANITAR] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Tyranitar, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tyranitar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tyranitar),
}, //Tyranitar,
[SPECIES_LUGIA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Lugia, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Lugia),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lugia),
}, //Lugia,
[SPECIES_HO_OH] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(HoOh, 1),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_HoOh),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_HoOh),
}, //HoOh,
[SPECIES_CELEBI] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Celebi, 1),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Celebi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Celebi),
}, //Celebi,
    
[SPECIES_TREECKO] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Treecko, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Treecko),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Treecko),
}, //Treecko,
[SPECIES_GROVYLE] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Grovyle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grovyle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grovyle),
}, //Grovyle,
[SPECIES_SCEPTILE] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Sceptile, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sceptile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sceptile),
}, //Sceptile,
[SPECIES_TORCHIC] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x67, 0x05),
      PIC_DATA_ICON_INDEX(Torchic, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Torchic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Torchic),
}, //Torchic,
[SPECIES_COMBUSKEN] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Combusken, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Combusken),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Combusken),
}, //Combusken,
[SPECIES_BLAZIKEN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Blaziken, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Blaziken),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Blaziken),
}, //Blaziken,
[SPECIES_MUDKIP] = 
    {  
      FRONT_COORD(0x56, 13),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Mudkip, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mudkip),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mudkip),
}, //Mudkip,
[SPECIES_MARSHTOMP] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Marshtomp, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Marshtomp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Marshtomp),
}, //Marshtomp,
[SPECIES_SWAMPERT] = 
    {  
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Swampert, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swampert),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swampert),
}, //Swampert,
[SPECIES_POOCHYENA] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x76, 0x09),
      PIC_DATA_ICON_INDEX(Poochyena, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Poochyena),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poochyena),
}, //Poochyena,
[SPECIES_MIGHTYENA] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Mightyena, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mightyena),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mightyena),
}, //Mightyena,
[SPECIES_ZIGZAGOON] = 
    {  
      FRONT_COORD(0x85, 12),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Zigzagoon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zigzagoon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zigzagoon),
}, //Zigzagoon,
[SPECIES_LINOONE] = 
    {  
      FRONT_COORD(0x78, 13),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Linoone, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Linoone),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Linoone),
}, //Linoone,
[SPECIES_WURMPLE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Wurmple, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wurmple),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wurmple),
}, //Wurmple,
[SPECIES_SILCOON] = 
    {  
      FRONT_COORD(0x75, 10),
      BACK_COORD(0x83, 0x15),
      PIC_DATA_ICON_INDEX(Silcoon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Silcoon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silcoon),
}, //Silcoon,
[SPECIES_BEAUTIFLY] = 
    {  
      FRONT_COORD(0x86, 9),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Beautifly, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Beautifly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Beautifly),
}, //Beautifly,
[SPECIES_CASCOON] = 
    {  
      FRONT_COORD(0x74, 10),
      BACK_COORD(0x73, 0x14),
      PIC_DATA_ICON_INDEX(Cascoon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cascoon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cascoon),
}, //Cascoon,
[SPECIES_DUSTOX] = 
    {  
      FRONT_COORD(0x86, 12),
      BACK_COORD(0x83, 0x14),
      PIC_DATA_ICON_INDEX(Dustox, 1),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Dustox),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dustox),
}, //Dustox,
[SPECIES_LOTAD] = 
    {  
      FRONT_COORD(0x65, 13),
      BACK_COORD(0x75, 0x0f),
      PIC_DATA_ICON_INDEX(Lotad, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lotad),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lotad),
}, //Lotad,
[SPECIES_LOMBRE] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Lombre, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lombre),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lombre),
}, //Lombre,
[SPECIES_LUDICOLO] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Ludicolo, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ludicolo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ludicolo),
}, //Ludicolo,
[SPECIES_SEEDOT] = 
    {  
      FRONT_COORD(0x46, 12),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Seedot, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Seedot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Seedot),
}, //Seedot,
[SPECIES_NUZLEAF] = 
    {  
      FRONT_COORD(0x56, 7),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Nuzleaf, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nuzleaf),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nuzleaf),
}, //Nuzleaf,
[SPECIES_SHIFTRY] = 
    {  
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Shiftry, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shiftry),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shiftry),
}, //Shiftry,
[SPECIES_NINCADA] = 
    {  
      FRONT_COORD(0x74, 16),
      BACK_COORD(0x83, 0x14),
      PIC_DATA_ICON_INDEX(Nincada, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nincada),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nincada),
}, //Nincada,
[SPECIES_NINJASK] = 
    {  
      FRONT_COORD(0x86, 11),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Ninjask, 1),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Ninjask),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ninjask),
}, //Ninjask,
[SPECIES_SHEDINJA] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Shedinja, 1),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Shedinja),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shedinja),
}, //Shedinja,
[SPECIES_TAILLOW] = 
    {  
      FRONT_COORD(0x64, 11),
      BACK_COORD(0x64, 0x11),
      PIC_DATA_ICON_INDEX(Taillow, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Taillow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Taillow),
}, //Taillow,
[SPECIES_SWELLOW] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Swellow, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swellow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swellow),
}, //Swellow,
[SPECIES_SHROOMISH] = 
    {  
      FRONT_COORD(0x54, 14),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Shroomish, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shroomish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shroomish),
}, //Shroomish,
[SPECIES_BRELOOM] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Breloom, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Breloom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Breloom),
}, //Breloom,
[SPECIES_SPINDA] = 
    {  
      FRONT_COORD(0x68, 8),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Spinda, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spinda),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spinda),
}, //Spinda,
[SPECIES_WINGULL] = 
    {  
      FRONT_COORD(0x84, 11),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Wingull, 0),
      .enemyMonElevation = 16,
      .cryData = CRY_INFO(Cry_Wingull),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wingull),
}, //Wingull,
[SPECIES_PELIPPER] = 
    {  
      FRONT_COORD(0x77, 2),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Pelipper, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Pelipper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pelipper),
}, //Pelipper,
[SPECIES_SURSKIT] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Surskit, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Surskit),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Surskit),
}, //Surskit,
[SPECIES_MASQUERAIN] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 0x00),
      PIC_DATA_ICON_INDEX(Masquerain, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Masquerain),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Masquerain),
}, //Masquerain,
[SPECIES_WAILMER] = 
    {  
      FRONT_COORD(0x75, 10),
      BACK_COORD(0x83, 0x15),
      PIC_DATA_ICON_INDEX(Wailmer, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wailmer),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wailmer),
}, //Wailmer,
[SPECIES_WAILORD] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x83, 0x16),
      PIC_DATA_ICON_INDEX(Wailord, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wailord),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wailord),
}, //Wailord,
[SPECIES_SKITTY] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Skitty, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skitty),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skitty),
}, //Skitty,
[SPECIES_DELCATTY] = 
    {  
      FRONT_COORD(0x66, 4),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Delcatty, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Delcatty),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Delcatty),
}, //Delcatty,
[SPECIES_KECLEON] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Kecleon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kecleon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kecleon),
}, //Kecleon,
[SPECIES_BALTOY] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Baltoy, 1),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Baltoy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Baltoy),
}, //Baltoy,
[SPECIES_CLAYDOL] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Claydol, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Claydol),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Claydol),
}, //Claydol,
[SPECIES_NOSEPASS] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Nosepass, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nosepass),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nosepass),
}, //Nosepass,
[SPECIES_TORKOAL] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Torkoal, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Torkoal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Torkoal),
}, //Torkoal,
[SPECIES_SABLEYE] = 
    {  
      FRONT_COORD(0x66, 10),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Sableye, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sableye),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sableye),
}, //Sableye,
[SPECIES_BARBOACH] = 
    {  
      FRONT_COORD(0x46, 12),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Barboach, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Barboach),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Barboach),
}, //Barboach,
[SPECIES_WHISCASH] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Whiscash, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Whiscash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Whiscash),
}, //Whiscash,
[SPECIES_LUVDISC] = 
    {  
      FRONT_COORD(0x46, 14),
      BACK_COORD(0x46, 0x0a),
      PIC_DATA_ICON_INDEX(Luvdisc, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Luvdisc),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Luvdisc),
}, //Luvdisc,
[SPECIES_CORPHISH] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Corphish, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Corphish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Corphish),
}, //Corphish,
[SPECIES_CRAWDAUNT] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Crawdaunt, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Crawdaunt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Crawdaunt),
}, //Crawdaunt,
[SPECIES_FEEBAS] = 
    {  
      FRONT_COORD(0x46, 10),
      BACK_COORD(0x67, 0x07),
      PIC_DATA_ICON_INDEX(Feebas, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Feebas),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Feebas),
}, //Feebas,
[SPECIES_MILOTIC] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x68, 0x02),
      PIC_DATA_ICON_INDEX(Milotic, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Milotic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Milotic),
}, //Milotic,
[SPECIES_CARVANHA] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Carvanha, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Carvanha),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Carvanha),
}, //Carvanha,
[SPECIES_SHARPEDO] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 0x02),
      PIC_DATA_ICON_INDEX(Sharpedo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sharpedo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sharpedo),
}, //Sharpedo,
[SPECIES_TRAPINCH] = 
    {  
      FRONT_COORD(0x54, 12),
      BACK_COORD(0x75, 0x0e),
      PIC_DATA_ICON_INDEX(Trapinch, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Trapinch),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Trapinch),
}, //Trapinch,
[SPECIES_VIBRAVA] = 
    {  
      FRONT_COORD(0x86, 10),
      BACK_COORD(0x74, 0x11),
      PIC_DATA_ICON_INDEX(Vibrava, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vibrava),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vibrava),
}, //Vibrava,
[SPECIES_FLYGON] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0x02),
      PIC_DATA_ICON_INDEX(Flygon, 1),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Flygon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flygon),
}, //Flygon,
[SPECIES_MAKUHITA] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Makuhita, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Makuhita),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Makuhita),
}, //Makuhita,
[SPECIES_HARIYAMA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Hariyama, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hariyama),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hariyama),
}, //Hariyama,
[SPECIES_ELECTRIKE] = 
    {  
      FRONT_COORD(0x64, 14),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Electrike, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Electrike),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Electrike),
}, //Electrike,
[SPECIES_MANECTRIC] = 
    {  
      FRONT_COORD(0x67, 2),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Manectric, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Manectric),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Manectric),
}, //Manectric,
[SPECIES_NUMEL] = 
    {  
      FRONT_COORD(0x65, 9),
      BACK_COORD(0x86, 0x0b),
      PIC_DATA_ICON_INDEX(Numel, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Numel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Numel),
}, //Numel,
[SPECIES_CAMERUPT] = 
    {  
      FRONT_COORD(0x87, 6),
      BACK_COORD(0x84, 0x13),
      PIC_DATA_ICON_INDEX(Camerupt, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Camerupt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Camerupt),
}, //Camerupt,
[SPECIES_SPHEAL] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x64, 0x12),
      PIC_DATA_ICON_INDEX(Spheal, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spheal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spheal),
}, //Spheal,
[SPECIES_SEALEO] = 
    {  
      FRONT_COORD(0x86, 10),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Sealeo, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sealeo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sealeo),
}, //Sealeo,
[SPECIES_WALREIN] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Walrein, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Walrein),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Walrein),
}, //Walrein,
[SPECIES_CACNEA] = 
    {  
      FRONT_COORD(0x74, 13),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Cacnea, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cacnea),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cacnea),
}, //Cacnea,
[SPECIES_CACTURNE] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Cacturne, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cacturne),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cacturne),
}, //Cacturne,
[SPECIES_SNORUNT] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x76, 0x0a),
      PIC_DATA_ICON_INDEX(Snorunt, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Snorunt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Snorunt),
}, //Snorunt,
[SPECIES_GLALIE] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x85, 0x0c),
      PIC_DATA_ICON_INDEX(Glalie, 0),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Glalie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Glalie),
}, //Glalie,
[SPECIES_LUNATONE] = 
    {  
      FRONT_COORD(0x66, 9),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Lunatone, 1),
      .enemyMonElevation = 13,
      .cryData = CRY_INFO(Cry_Lunatone),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lunatone),
}, //Lunatone,
[SPECIES_SOLROCK] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Solrock, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Solrock),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Solrock),
}, //Solrock,
[SPECIES_AZURILL] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Azurill, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Azurill),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Azurill),
}, //Azurill,
[SPECIES_SPOINK] = 
    {  
      FRONT_COORD(0x46, 9),
      BACK_COORD(0x56, 0x0b),
      PIC_DATA_ICON_INDEX(Spoink, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spoink),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spoink),
}, //Spoink,
[SPECIES_GRUMPIG] = 
    {  
      FRONT_COORD(0x77, 2),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Grumpig, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grumpig),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grumpig),
}, //Grumpig,
[SPECIES_PLUSLE] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Plusle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Plusle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Plusle),
}, //Plusle,
[SPECIES_MINUN] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Minun, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minun),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minun),
}, //Minun,
[SPECIES_MAWILE] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x87, 0x04),
      PIC_DATA_ICON_INDEX(Mawile, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mawile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mawile),
}, //Mawile,
[SPECIES_MEDITITE] = 
    {  
      FRONT_COORD(0x65, 10),
      BACK_COORD(0x76, 0x0b),
      PIC_DATA_ICON_INDEX(Meditite, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meditite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meditite),
}, //Meditite,
[SPECIES_MEDICHAM] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x68, 0x03),
      PIC_DATA_ICON_INDEX(Medicham, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Medicham),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Medicham),
}, //Medicham,
[SPECIES_SWABLU] = 
    {  
      FRONT_COORD(0x76, 14),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Swablu, 0),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Swablu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swablu),
}, //Swablu,
[SPECIES_ALTARIA] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 0x06),
      PIC_DATA_ICON_INDEX(Altaria, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Altaria),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Altaria),
}, //Altaria,
[SPECIES_WYNAUT] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x77, 0x07),
      PIC_DATA_ICON_INDEX(Wynaut, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wynaut),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wynaut),
}, //Wynaut,
[SPECIES_DUSKULL] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Duskull, 0),
      .enemyMonElevation = 9,
      .cryData = CRY_INFO(Cry_Duskull),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Duskull),
}, //Duskull,
[SPECIES_DUSCLOPS] = 
    {  
      FRONT_COORD(0x77, 3),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Dusclops, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dusclops),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dusclops),
}, //Dusclops,
[SPECIES_ROSELIA] = 
    {  
      FRONT_COORD(0x76, 11),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Roselia, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Roselia),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Roselia),
}, //Roselia,
[SPECIES_SLAKOTH] = 
    {  
      FRONT_COORD(0x74, 15),
      BACK_COORD(0x85, 0x0f),
      PIC_DATA_ICON_INDEX(Slakoth, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slakoth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slakoth),
}, //Slakoth,
[SPECIES_VIGOROTH] = 
    {  
      FRONT_COORD(0x78, 7),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Vigoroth, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vigoroth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vigoroth),
}, //Vigoroth,
[SPECIES_SLAKING] = 
    {  
      FRONT_COORD(0x86, 7),
      BACK_COORD(0x86, 0x08),
      PIC_DATA_ICON_INDEX(Slaking, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slaking),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slaking),
}, //Slaking,
[SPECIES_GULPIN] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x66, 0x0b),
      PIC_DATA_ICON_INDEX(Gulpin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gulpin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gulpin),
}, //Gulpin,
[SPECIES_SWALOT] = 
    {  
      FRONT_COORD(0x66, 5),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Swalot, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swalot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swalot),
}, //Swalot,
[SPECIES_TROPIUS] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Tropius, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tropius),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tropius),
}, //Tropius,
[SPECIES_WHISMUR] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Whismur, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Whismur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Whismur),
}, //Whismur,
[SPECIES_LOUDRED] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Loudred, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Loudred),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Loudred),
}, //Loudred,
[SPECIES_EXPLOUD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Exploud, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Exploud),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Exploud),
}, //Exploud,
[SPECIES_CLAMPERL] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Clamperl, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clamperl),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clamperl),
}, //Clamperl,
[SPECIES_HUNTAIL] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x68, 0x02),
      PIC_DATA_ICON_INDEX(Huntail, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Huntail),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Huntail),
}, //Huntail,
[SPECIES_GOREBYSS] = 
    {  
      FRONT_COORD(0x86, 6),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Gorebyss, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gorebyss),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gorebyss),
}, //Gorebyss,
[SPECIES_ABSOL] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x78, 0x03),
      PIC_DATA_ICON_INDEX(Absol, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Absol),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Absol),
}, //Absol,
[SPECIES_SHUPPET] = 
    {  
      FRONT_COORD(0x56, 13),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Shuppet, 0),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Shuppet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shuppet),
}, //Shuppet,
[SPECIES_BANETTE] = 
    {  
      FRONT_COORD(0x55, 7),
      BACK_COORD(0x65, 0x0c),
      PIC_DATA_ICON_INDEX(Banette, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Banette),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Banette),
}, //Banette,
[SPECIES_SEVIPER] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Seviper, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Seviper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Seviper),
}, //Seviper,
[SPECIES_ZANGOOSE] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x88, 0x01),
      PIC_DATA_ICON_INDEX(Zangoose, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zangoose),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zangoose),
}, //Zangoose,
[SPECIES_RELICANTH] = 
    {  
      FRONT_COORD(0x77, 10),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Relicanth, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Relicanth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Relicanth),
}, //Relicanth,
[SPECIES_ARON] = 
    {  
      FRONT_COORD(0x43, 14),
      BACK_COORD(0x54, 0x11),
      PIC_DATA_ICON_INDEX(Aron, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aron),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aron),
}, //Aron,
[SPECIES_LAIRON] = 
    {  
      FRONT_COORD(0x75, 8),
      BACK_COORD(0x84, 0x11),
      PIC_DATA_ICON_INDEX(Lairon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lairon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lairon),
}, //Lairon,
[SPECIES_AGGRON] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Aggron, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aggron),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aggron),
}, //Aggron,
[SPECIES_CASTFORM] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x45, 0x0d),
      PIC_DATA_ICON_INDEX(Castform, 0),
      .enemyMonElevation = 16,
      .cryData = CRY_INFO(Cry_Castform),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Castform),
}, //Castform,
[SPECIES_VOLBEAT] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x76, 0x08),
      PIC_DATA_ICON_INDEX(Volbeat, 0),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Volbeat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Volbeat),
}, //Volbeat,
[SPECIES_ILLUMISE] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x67, 0x06),
      PIC_DATA_ICON_INDEX(Illumise, 2),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Illumise),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Illumise),
}, //Illumise,
[SPECIES_LILEEP] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x86, 0x09),
      PIC_DATA_ICON_INDEX(Lileep, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lileep),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lileep),
}, //Lileep,
[SPECIES_CRADILY] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Cradily, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cradily),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cradily),
}, //Cradily,
[SPECIES_ANORITH] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x83, 0x17),
      PIC_DATA_ICON_INDEX(Anorith, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Anorith),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Anorith),
}, //Anorith,
[SPECIES_ARMALDO] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x77, 0x05),
      PIC_DATA_ICON_INDEX(Armaldo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Armaldo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Armaldo),
}, //Armaldo,
[SPECIES_RALTS] = 
    {  
      FRONT_COORD(0x35, 12),
      BACK_COORD(0x45, 0x0d),
      PIC_DATA_ICON_INDEX(Ralts, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ralts),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ralts),
}, //Ralts,
[SPECIES_KIRLIA] = 
    {  
      FRONT_COORD(0x47, 6),
      BACK_COORD(0x57, 0x06),
      PIC_DATA_ICON_INDEX(Kirlia, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kirlia),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kirlia),
}, //Kirlia,
[SPECIES_GARDEVOIR] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x77, 0x04),
      PIC_DATA_ICON_INDEX(Gardevoir, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gardevoir),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gardevoir),
}, //Gardevoir,
[SPECIES_BAGON] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x66, 0x08),
      PIC_DATA_ICON_INDEX(Bagon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bagon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bagon),
}, //Bagon,
[SPECIES_SHELGON] = 
    {  
      FRONT_COORD(0x66, 9),
      BACK_COORD(0x85, 0x0d),
      PIC_DATA_ICON_INDEX(Shelgon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shelgon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shelgon),
}, //Shelgon,
[SPECIES_SALAMENCE] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x77, 0x06),
      PIC_DATA_ICON_INDEX(Salamence, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Salamence),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Salamence),
}, //Salamence,
[SPECIES_BELDUM] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x66, 0x0a),
      PIC_DATA_ICON_INDEX(Beldum, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Beldum),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Beldum),
}, //Beldum,
[SPECIES_METANG] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x84, 0x10),
      PIC_DATA_ICON_INDEX(Metang, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Metang),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Metang),
}, //Metang,
[SPECIES_METAGROSS] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x83, 0x14),
      PIC_DATA_ICON_INDEX(Metagross, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Metagross),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Metagross),
}, //Metagross,
[SPECIES_REGIROCK] = 
    {  
      FRONT_COORD(0x78, 3),
      BACK_COORD(0x86, 0x0a),
      PIC_DATA_ICON_INDEX(Regirock, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Regirock),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Regirock),
}, //Regirock,
[SPECIES_REGICE] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Regice, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Regice),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Regice),
}, //Regice,
[SPECIES_REGISTEEL] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x85, 0x0e),
      PIC_DATA_ICON_INDEX(Registeel, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Registeel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Registeel),
}, //Registeel,
[SPECIES_KYOGRE] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x84, 0x13),
      PIC_DATA_ICON_INDEX(Kyogre, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kyogre),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kyogre),
}, //Kyogre,
[SPECIES_GROUDON] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Groudon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Groudon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Groudon),
}, //Groudon,
[SPECIES_RAYQUAZA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 0x00),
      PIC_DATA_ICON_INDEX(Rayquaza, 1),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Rayquaza),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rayquaza),
}, //Rayquaza,
[SPECIES_LATIAS] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0x02),
      PIC_DATA_ICON_INDEX(Latias, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Latias),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Latias),
}, //Latias,
[SPECIES_LATIOS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0x03),
      PIC_DATA_ICON_INDEX(Latios, 2),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Latios),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Latios),
}, //Latios,
[SPECIES_JIRACHI] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x87, 0x05),
      PIC_DATA_ICON_INDEX(Jirachi, 0),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Jirachi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jirachi),
}, //Jirachi,
[SPECIES_DEOXYS] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 0x07),
      PIC_DATA_ICON_INDEX(Deoxys, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Deoxys),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deoxys),
}, //Deoxys,
[SPECIES_CHIMECHO] = 
    {  
      FRONT_COORD(0x37, 6),
      BACK_COORD(0x47, 0x07),
      PIC_DATA_ICON_INDEX(Chimecho, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Chimecho),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chimecho),
}, //Chimecho,
[SPECIES_EGG] = 
    {  
      FRONT_PIC(Egg),
      FRONT_COORD(0x33, 20),
      BACK_COORD(0x36, 10),
      .palette = gMonPalette_Egg,
      ICON(Egg, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_NONE,
      .cryData_Reverse = CRY_NONE,
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
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
      .cryData = CRY_INFO(Cry_Unown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unown),
}, //UnownQuestionMark, //ok I see now part of problem, this doeesn't have a comma and others are misaligned.
[SPECIES_TURTWIG] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 6),
      PIC_DATA_ICON_INDEX(Turtwig, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Turtwig),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Turtwig),
}, //Turtwig,
[SPECIES_GROTLE] = 
    {  
      FRONT_COORD(0x56, 7),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Grotle, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grotle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grotle),
}, //Grotle,
[SPECIES_TORTERRA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Torterra, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Torterra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Torterra),
}, //Torterra,
[SPECIES_CHIMCHAR] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Chimchar, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chimchar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chimchar),
}, //Chimchar,
[SPECIES_MONFERNO] = 
    {  
      FRONT_COORD(0x66, 8),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Monferno, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Monferno),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Monferno),
}, //Monferno,
[SPECIES_INFERNAPE] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Infernape, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Infernape),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Infernape),
}, //Infernape,
[SPECIES_PIPLUP] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x56, 10),
      PIC_DATA_ICON_INDEX(Piplup, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Piplup),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Piplup),
}, //Piplup,
[SPECIES_PRINPLUP] = 
    {  
      FRONT_COORD(0x66, 7),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Prinplup, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Prinplup),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Prinplup),
}, //Prinplup,
[SPECIES_EMPOLEON] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Empoleon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Empoleon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Empoleon),
}, //Empoleon,
[SPECIES_STARLY] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Starly, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Starly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Starly),
}, //Starly,
[SPECIES_STARAVIA] = 
    {  
      FRONT_COORD(0x54, 8),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Staravia, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Staravia),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Staravia),
}, //Staravia,
[SPECIES_STARAPTOR] = 
    {  
      FRONT_COORD(0x76, 3),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Staraptor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Staraptor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Staraptor),
}, //Staraptor,
[SPECIES_BIDOOF] = 
    {  
      FRONT_COORD(0x54, 12),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Bidoof, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bidoof),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bidoof),
}, //Bidoof,
[SPECIES_BIBAREL] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Bibarel, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bibarel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bibarel),
}, //Bibarel,
[SPECIES_KRICKETOT] = 
    {  
      FRONT_COORD(0x86, 11),
      BACK_COORD(0x67, 6),
      PIC_DATA_ICON_INDEX(Kricketot, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kricketot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kricketot),
}, //Kricketot,
[SPECIES_KRICKETUNE] = 
    {  
      FRONT_COORD(0x65, 7),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Kricketune, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kricketune),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kricketune),
}, //Kricketune,
[SPECIES_SHINX] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Shinx, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shinx),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shinx),
}, //Shinx,
[SPECIES_LUXIO] = 
    {  
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Luxio, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Luxio),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Luxio),
}, //Luxio,
[SPECIES_LUXRAY] = 
    {  
      FRONT_COORD(0x44, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Luxray, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Luxray),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Luxray),
}, //Luxray,
[SPECIES_BUDEW] = 
    {  
      FRONT_COORD(0x66, 14),
      BACK_COORD(0x57, 11),
      PIC_DATA_ICON_INDEX(Budew, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Budew),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Budew),
}, //Budew,
[SPECIES_ROSERADE] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Roserade, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Roserade),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Roserade),
}, //Roserade,
[SPECIES_CRANIDOS] = 
    {  
      FRONT_COORD(0x78, 10),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Cranidos, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cranidos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cranidos),
}, //Cranidos,
[SPECIES_RAMPARDOS] = 
    {  
      FRONT_COORD(0x65, 3),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Rampardos, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rampardos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rampardos),
}, //Rampardos,
[SPECIES_SHIELDON] = 
    {  
      FRONT_COORD(0x88, 15),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Shieldon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shieldon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shieldon),
}, //Shieldon,
[SPECIES_BASTIODON] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Bastiodon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bastiodon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bastiodon),
}, //Bastiodon,
[SPECIES_BURMY] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x57, 6),
      PIC_DATA_ICON_INDEX(Burmy, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Burmy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Burmy),
}, //Burmy,
[SPECIES_WORMADAM] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Wormadam, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wormadam),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wormadam),
}, //Wormadam,
[SPECIES_MOTHIM] = 
    {  
      FRONT_COORD(0x76, 12),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Mothim, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Mothim),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mothim),
}, //Mothim,
[SPECIES_COMBEE] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x86, 22),
      PIC_DATA_ICON_INDEX(Combee, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Combee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Combee),
}, //Combee,
[SPECIES_VESPIQUEN] = 
    {  
      FRONT_COORD(0x66, 4),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Vespiquen, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Vespiquen),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vespiquen),
}, //Vespiquen,
[SPECIES_PACHIRISU] = 
    {  
      FRONT_COORD(0x78, 12),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Pachirisu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pachirisu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pachirisu),
}, //Pachirisu,
[SPECIES_BUIZEL] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Buizel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Buizel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Buizel),
}, //Buizel,
[SPECIES_FLOATZEL] = 
    {  
      FRONT_COORD(0x66, 3),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Floatzel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Floatzel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floatzel),
}, //Floatzel,
[SPECIES_CHERUBI] = 
    {  
      FRONT_COORD(0x78, 16),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Cherubi, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cherubi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cherubi),
}, //Cherubi,
[SPECIES_CHERRIM] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x57, 9),
      PIC_DATA_ICON_INDEX(Cherrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cherrim),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cherrim),
}, //Cherrim,
[SPECIES_SHELLOS] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x57, 8),
      PIC_DATA_ICON_INDEX(Shellos, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shellos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shellos),
}, //Shellos,
[SPECIES_GASTRODON] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Gastrodon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gastrodon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gastrodon),
}, //Gastrodon,
[SPECIES_AMBIPOM] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Ambipom, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ambipom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ambipom),
}, //Ambipom,
[SPECIES_DRIFLOON] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x58, 0),
      PIC_DATA_ICON_INDEX(Drifloon, 2),
      .enemyMonElevation = 5,
      .cryData = CRY_INFO(Cry_Drifloon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drifloon),
}, //Drifloon,
[SPECIES_DRIFBLIM] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Drifblim, 2),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Drifblim),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drifblim),
}, //Drifblim,
[SPECIES_BUNEARY] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Buneary, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Buneary),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Buneary),
}, //Buneary,
[SPECIES_LOPUNNY] = 
    {  
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Lopunny, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lopunny),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lopunny),
}, //Lopunny,
[SPECIES_MISMAGIUS] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Mismagius, 2),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Mismagius),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mismagius),
}, //Mismagius,
[SPECIES_HONCHKROW] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Honchkrow, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Honchkrow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Honchkrow),
}, //Honchkrow,
[SPECIES_GLAMEOW] = 
    {  
      FRONT_COORD(0x77, 8),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Glameow, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Glameow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Glameow),
}, //Glameow,
[SPECIES_PURUGLY] = 
    {  
      FRONT_COORD(0x55, 5),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Purugly, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Purugly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Purugly),
}, //Purugly,
[SPECIES_CHINGLING] = 
    {  
      FRONT_COORD(0x86, 15),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(Chingling, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chingling),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chingling),
}, //Chingling,
[SPECIES_STUNKY] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Stunky, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stunky),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stunky),
}, //Stunky,
[SPECIES_SKUNTANK] = 
    {  
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Skuntank, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skuntank),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skuntank),
}, //Skuntank,
[SPECIES_BRONZOR] = 
    {  
      FRONT_COORD(0x54, 14),
      BACK_COORD(0x56, 9),
      PIC_DATA_ICON_INDEX(Bronzor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bronzor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bronzor),
}, //Bronzor,
[SPECIES_BRONZONG] = 
    {  
      FRONT_COORD(0x75, 6),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Bronzong, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Bronzong),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bronzong),
}, //Bronzong,
[SPECIES_BONSLY] = 
    {  
      FRONT_COORD(0x55, 9),
      BACK_COORD(0x58, 6),
      PIC_DATA_ICON_INDEX(Bonsly, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bonsly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bonsly),
}, //Bonsly,
[SPECIES_MIME_JR] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(MimeJr, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MimeJr),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MimeJr),
}, //MimeJr,
[SPECIES_HAPPINY] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Happiny, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Happiny),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Happiny),
}, //Happiny,
[SPECIES_CHATOT] = 
    {  
      FRONT_COORD(0x78, 11),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(Chatot, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chatot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chatot),
}, //Chatot,
[SPECIES_SPIRITOMB] = 
    {  
      FRONT_COORD(0x65, 6),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Spiritomb, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spiritomb),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spiritomb),
}, //Spiritomb,
[SPECIES_GIBLE] = 
    {  
      FRONT_COORD(0x77, 9),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Gible, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gible),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gible),
}, //Gible,
[SPECIES_GABITE] = 
    {  
      FRONT_COORD(0x66, 2),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Gabite, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gabite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gabite),
}, //Gabite,
[SPECIES_GARCHOMP] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Garchomp, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Garchomp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Garchomp),
}, //Garchomp,
[SPECIES_MUNCHLAX] = 
    {  
      FRONT_COORD(0x74, 10),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Munchlax, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Munchlax),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Munchlax),
}, //Munchlax,
[SPECIES_RIOLU] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Riolu, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Riolu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Riolu),
}, //Riolu,
[SPECIES_LUCARIO] = 
    {  
      FRONT_COORD(0x76, 7),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Lucario, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lucario),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lucario),
}, //Lucario,
[SPECIES_HIPPOPOTAS] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Hippopotas, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hippopotas),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hippopotas),
}, //Hippopotas,
[SPECIES_HIPPOWDON] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Hippowdon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hippowdon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hippowdon),
}, //Hippowdon,
[SPECIES_SKORUPI] = 
    {  
      FRONT_COORD(0x87, 11),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Skorupi, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skorupi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skorupi),
}, //Skorupi,
[SPECIES_DRAPION] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Drapion, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drapion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drapion),
}, //Drapion,
[SPECIES_CROAGUNK] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Croagunk, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Croagunk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Croagunk),
}, //Croagunk,
[SPECIES_TOXICROAK] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Toxicroak, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Toxicroak),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Toxicroak),
}, //Toxicroak,
[SPECIES_CARNIVINE] = 
    {  
      FRONT_COORD(0x65, 10),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Carnivine, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Carnivine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Carnivine),
}, //Carnivine,
[SPECIES_FINNEON] = 
    {  
      FRONT_COORD(0x66, 14),
      BACK_COORD(0x75, 13),
      PIC_DATA_ICON_INDEX(Finneon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Finneon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Finneon),
}, //Finneon,
[SPECIES_LUMINEON] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Lumineon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lumineon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lumineon),
}, //Lumineon,
[SPECIES_MANTYKE] = 
    {  
      FRONT_COORD(0x46, 12),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Mantyke, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mantyke),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mantyke),
}, //Mantyke,
[SPECIES_SNOVER] = 
    {  
      FRONT_COORD(0x87, 10),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Snover, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Snover),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Snover),
}, //Snover,
[SPECIES_ABOMASNOW] = 
    {  
      FRONT_COORD(0x54, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Abomasnow, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Abomasnow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Abomasnow),
}, //Abomasnow,
[SPECIES_WEAVILE] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Weavile, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Weavile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Weavile),
}, //Weavile,
[SPECIES_MAGNEZONE] = 
    {  
      FRONT_COORD(0x77, 4),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Magnezone, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Magnezone),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magnezone),
}, //Magnezone,
[SPECIES_LICKILICKY] = 
    {  
      FRONT_COORD(0x66, 2),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Lickilicky, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lickilicky),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lickilicky),
}, //Lickilicky,
[SPECIES_RHYPERIOR] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Rhyperior, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rhyperior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rhyperior),
}, //Rhyperior,
[SPECIES_TANGROWTH] = 
    {  
      FRONT_COORD(0x66, 2),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Tangrowth, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tangrowth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tangrowth),
}, //Tangrowth,
[SPECIES_ELECTIVIRE] = 
    {  
      FRONT_COORD(0x86, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Electivire, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Electivire),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Electivire),
}, //Electivire,
[SPECIES_MAGMORTAR] = 
    {  
      FRONT_COORD(0x43, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Magmortar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magmortar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magmortar),
}, //Magmortar,
[SPECIES_TOGEKISS] = 
    {  
      FRONT_COORD(0x76, 10),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Togekiss, 2),
      .enemyMonElevation = 14,
      .cryData = CRY_INFO(Cry_Togekiss),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Togekiss),
}, //Togekiss,
[SPECIES_YANMEGA] = 
    {  
      FRONT_COORD(0x66, 5),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Yanmega, 1),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Yanmega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yanmega),
}, //Yanmega,
[SPECIES_LEAFEON] = 
    {  
      FRONT_COORD(0x57, 9),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Leafeon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Leafeon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Leafeon),
}, //Leafeon,
[SPECIES_GLACEON] = 
    {  
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x78, 6),
      PIC_DATA_ICON_INDEX(Glaceon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Glaceon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Glaceon),
}, //Glaceon,
[SPECIES_GLISCOR] = 
    {  
      FRONT_COORD(0x76, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Gliscor, 2),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Gliscor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gliscor),
}, //Gliscor,
[SPECIES_MAMOSWINE] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Mamoswine, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mamoswine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mamoswine),
}, //Mamoswine,
[SPECIES_PORYGON_Z] = 
    {  
      FRONT_COORD(0x65, 6),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(PorygonZ, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_PorygonZ),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_PorygonZ),
}, //Porygon_Z,
[SPECIES_GALLADE] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Gallade, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gallade),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gallade),
}, //Gallade,
[SPECIES_PROBOPASS] = 
    {  
      FRONT_COORD(0x55, 4),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Probopass, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Probopass),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Probopass),
}, //Probopass,
[SPECIES_DUSKNOIR] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Dusknoir, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dusknoir),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dusknoir),
}, //Dusknoir,
[SPECIES_FROSLASS] = 
    {  
      FRONT_COORD(0x77, 8),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Froslass, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Froslass),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Froslass),
}, //Froslass,
[SPECIES_ROTOM] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Rotom, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Rotom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rotom),
}, //Rotom,
[SPECIES_UXIE] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Uxie, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Uxie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Uxie),
}, //Uxie,
[SPECIES_MESPRIT] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Mesprit, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Mesprit),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mesprit),
}, //Mesprit,
[SPECIES_AZELF] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Azelf, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Azelf),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Azelf),
}, //Azelf,
[SPECIES_DIALGA] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Dialga, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dialga),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dialga),
}, //Dialga,
[SPECIES_PALKIA] = 
    {  
      FRONT_COORD(0x65, 0),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Palkia, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Palkia),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Palkia),
}, //Palkia,
[SPECIES_HEATRAN] = 
    {  
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Heatran, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Heatran),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Heatran),
}, //Heatran,
[SPECIES_REGIGIGAS] = 
    {  
      FRONT_COORD(0x44, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Regigigas, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Regigigas),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Regigigas),
}, //Regigigas,
[SPECIES_GIRATINA] = 
    {  
      FRONT_COORD(0x55, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Giratina, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Giratina),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Giratina),
}, //Giratina,
[SPECIES_CRESSELIA] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Cresselia, 0),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Cresselia),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cresselia),
}, //Cresselia,
[SPECIES_PHIONE] = 
    {  
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Phione, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Phione),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Phione),
}, //Phione,
[SPECIES_MANAPHY] = 
    {  
      FRONT_COORD(0x55, 13),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Manaphy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Manaphy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Manaphy),
}, //Manaphy,
[SPECIES_DARKRAI] = 
    {  
      FRONT_COORD(0x76, 3),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Darkrai, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Darkrai),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darkrai),
}, //Darkrai,
[SPECIES_SHAYMIN_LAND] = 
    {  
      FRONT_COORD(0x87, 16),
      BACK_COORD(0x75, 15),
      PIC_DATA_ICON_INDEX(Shaymin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ShayminLand),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ShayminLand),
}, //Shaymin,
[SPECIES_ARCEUS] = 
    {  
      FRONT_COORD(0x67, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Arceus, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
}, //Arceus,
[SPECIES_VICTINI] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x58, 7),
      PIC_DATA_ICON_INDEX(Victini, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Victini),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Victini),
}, //Victini,
[SPECIES_SNIVY] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Snivy, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Snivy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Snivy),
}, //Snivy,
[SPECIES_SERVINE] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(Servine, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Servine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Servine),
}, //Servine,
[SPECIES_SERPERIOR] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Serperior, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Serperior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Serperior),
}, //Serperior,
[SPECIES_TEPIG] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Tepig, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tepig),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tepig),
}, //Tepig,
[SPECIES_PIGNITE] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Pignite, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pignite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pignite),
}, //Pignite,
[SPECIES_EMBOAR] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Emboar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Emboar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Emboar),
}, //Emboar,
[SPECIES_OSHAWOTT] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 14),
      PIC_DATA_ICON_INDEX(Oshawott, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Oshawott),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Oshawott),
}, //Oshawott,
[SPECIES_DEWOTT] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Dewott, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dewott),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dewott),
}, //Dewott,
[SPECIES_SAMUROTT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Samurott, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Samurott),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Samurott),
}, //Samurott,
[SPECIES_PATRAT] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Patrat, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Patrat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Patrat),
}, //Patrat,
[SPECIES_WATCHOG] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Watchog, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Watchog),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Watchog),
}, //Watchog,
[SPECIES_LILLIPUP] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 12),
      PIC_DATA_ICON_INDEX(Lillipup, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lillipup),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lillipup),
}, //Lillipup,
[SPECIES_HERDIER] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x67, 10),
      PIC_DATA_ICON_INDEX(Herdier, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Herdier),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Herdier),
}, //Herdier,
[SPECIES_STOUTLAND] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Stoutland, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stoutland),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stoutland),
}, //Stoutland,
[SPECIES_PURRLOIN] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Purrloin, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Purrloin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Purrloin),
}, //Purrloin,
[SPECIES_LIEPARD] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Liepard, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Liepard),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Liepard),
}, //Liepard,
[SPECIES_PANSAGE] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(Pansage, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pansage),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pansage),
}, //Pansage,
[SPECIES_SIMISAGE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x78, 6),
      PIC_DATA_ICON_INDEX(Simisage, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Simisage),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Simisage),
}, //Simisage,
[SPECIES_PANSEAR] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 10),
      PIC_DATA_ICON_INDEX(Pansear, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pansear),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pansear),
}, //Pansear,
[SPECIES_SIMISEAR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Simisear, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Simisear),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Simisear),
}, //Simisear,
[SPECIES_PANPOUR] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(Panpour, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Panpour),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Panpour),
}, //Panpour,
[SPECIES_SIMIPOUR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Simipour, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Simipour),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Simipour),
}, //Simipour,
[SPECIES_MUNNA] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x64, 16),
      PIC_DATA_ICON_INDEX(Munna, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Munna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Munna),
}, //Munna,
[SPECIES_MUSHARNA] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Musharna, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Musharna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Musharna),
}, //Musharna,
[SPECIES_PIDOVE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Pidove, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pidove),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pidove),
}, //Pidove,
[SPECIES_TRANQUILL] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Tranquill, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tranquill),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tranquill),
}, //Tranquill,
[SPECIES_UNFEZANT_MALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(UnfezantMale, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Unfezant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unfezant),
}, //Unfezant,
[SPECIES_BLITZLE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Blitzle, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Blitzle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Blitzle),
}, //Blitzle,
[SPECIES_ZEBSTRIKA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Zebstrika, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zebstrika),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zebstrika),
}, //Zebstrika,
[SPECIES_ROGGENROLA] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 13),
      PIC_DATA_ICON_INDEX(Roggenrola, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Roggenrola),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Roggenrola),
}, //Roggenrola,
[SPECIES_BOLDORE] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x85, 16),
      PIC_DATA_ICON_INDEX(Boldore, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Boldore),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Boldore),
}, //Boldore,
[SPECIES_GIGALITH] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Gigalith, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gigalith),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gigalith),
}, //Gigalith,
[SPECIES_WOOBAT] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Woobat, 0),
      .enemyMonElevation = 19,
      .cryData = CRY_INFO(Cry_Woobat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Woobat),
}, //Woobat,
[SPECIES_SWOOBAT] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Swoobat, 0),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Swoobat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swoobat),
}, //Swoobat,
[SPECIES_DRILBUR] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Drilbur, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drilbur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drilbur),
}, //Drilbur,
[SPECIES_EXCADRILL] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Excadrill, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Excadrill),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Excadrill),
}, //Excadrill,
[SPECIES_AUDINO] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x77, 9),
      PIC_DATA_ICON_INDEX(Audino, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Audino),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Audino),
}, //Audino,
[SPECIES_TIMBURR] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Timburr, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Timburr),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Timburr),
}, //Timburr,
[SPECIES_GURDURR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Gurdurr, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gurdurr),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gurdurr),
}, //Gurdurr,
[SPECIES_CONKELDURR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 13),
      PIC_DATA_ICON_INDEX(Conkeldurr, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Conkeldurr),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Conkeldurr),
}, //Conkeldurr,
[SPECIES_TYMPOLE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x54, 17),
      PIC_DATA_ICON_INDEX(Tympole, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tympole),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tympole),
}, //Tympole,
[SPECIES_PALPITOAD] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Palpitoad, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Palpitoad),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Palpitoad),
}, //Palpitoad,
[SPECIES_SEISMITOAD] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Seismitoad, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Seismitoad),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Seismitoad),
}, //Seismitoad,
[SPECIES_THROH] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Throh, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Throh),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Throh),
}, //Throh,
[SPECIES_SAWK] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Sawk, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sawk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sawk),
}, //Sawk,
[SPECIES_SEWADDLE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 13),
      PIC_DATA_ICON_INDEX(Sewaddle, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sewaddle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sewaddle),
}, //Sewaddle,
[SPECIES_SWADLOON] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 10),
      PIC_DATA_ICON_INDEX(Swadloon, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swadloon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swadloon),
}, //Swadloon,
[SPECIES_LEAVANNY] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Leavanny, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Leavanny),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Leavanny),
}, //Leavanny,
[SPECIES_VENIPEDE] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Venipede, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Venipede),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Venipede),
}, //Venipede,
[SPECIES_WHIRLIPEDE] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Whirlipede, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Whirlipede),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Whirlipede),
}, //Whirlipede,
[SPECIES_SCOLIPEDE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Scolipede, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scolipede),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scolipede),
}, //Scolipede,
[SPECIES_COTTONEE] = 
    {  
      FRONT_COORD(0x45, 18),
      BACK_COORD(0x84, 18),
      PIC_DATA_ICON_INDEX(Cottonee, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cottonee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cottonee),
}, //Cottonee,
[SPECIES_WHIMSICOTT] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Whimsicott, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Whimsicott),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Whimsicott),
}, //Whimsicott,
[SPECIES_PETILIL] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x57, 9),
      PIC_DATA_ICON_INDEX(Petilil, 1),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Petilil),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Petilil),
}, //Petilil,
[SPECIES_LILLIGANT] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Lilligant, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lilligant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lilligant),
}, //Lilligant,
[SPECIES_BASCULIN_RED_STRIPED] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 16),
      PIC_DATA_ICON_INDEX(Basculin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Basculin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Basculin),
}, //Basculin,
[SPECIES_SANDILE] = 
    {  
      FRONT_COORD(0x45, 18),
      BACK_COORD(0x84, 18),
      PIC_DATA_ICON_INDEX(Sandile, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandile),
}, //Sandile,
[SPECIES_KROKOROK] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Krokorok, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Krokorok),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Krokorok),
}, //Krokorok,
[SPECIES_KROOKODILE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Krookodile, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Krookodile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Krookodile),
}, //Krookodile,
[SPECIES_DARUMAKA] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x76, 12),
      PIC_DATA_ICON_INDEX(Darumaka, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Darumaka),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darumaka),
}, //Darumaka,
[SPECIES_DARMANITAN] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Darmanitan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Darmanitan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darmanitan),
}, //Darmanitan,
[SPECIES_MARACTUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Maractus, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Maractus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Maractus),
}, //Maractus,
[SPECIES_DWEBBLE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x74, 17),
      PIC_DATA_ICON_INDEX(Dwebble, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dwebble),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dwebble),
}, //Dwebble,
[SPECIES_CRUSTLE] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Crustle, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Crustle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Crustle),
}, //Crustle,
[SPECIES_SCRAGGY] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Scraggy, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scraggy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scraggy),
}, //Scraggy,
[SPECIES_SCRAFTY] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(Scrafty, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scrafty),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scrafty),
}, //Scrafty,
[SPECIES_SIGILYPH] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Sigilyph, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Sigilyph),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sigilyph),
}, //Sigilyph,
[SPECIES_YAMASK] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x55, 14),
      PIC_DATA_ICON_INDEX(Yamask, 0),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Yamask),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yamask),
}, //Yamask,
[SPECIES_COFAGRIGUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Cofagrigus, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cofagrigus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cofagrigus),
}, //Cofagrigus,
[SPECIES_TIRTOUGA] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Tirtouga, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tirtouga),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tirtouga),
}, //Tirtouga,
[SPECIES_CARRACOSTA] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Carracosta, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Carracosta),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Carracosta),
}, //Carracosta,
[SPECIES_ARCHEN] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Archen, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Archen),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Archen),
}, //Archen,
[SPECIES_ARCHEOPS] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Archeops, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Archeops),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Archeops),
}, //Archeops,
[SPECIES_TRUBBISH] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(Trubbish, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Trubbish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Trubbish),
}, //Trubbish,
[SPECIES_GARBODOR] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Garbodor, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Garbodor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Garbodor),
}, //Garbodor,
[SPECIES_ZORUA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Zorua, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zorua),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zorua),
}, //Zorua,
[SPECIES_ZOROARK] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Zoroark, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zoroark),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zoroark),
}, //Zoroark,
[SPECIES_MINCCINO] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Minccino, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minccino),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minccino),
}, //Minccino,
[SPECIES_CINCCINO] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Cinccino, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cinccino),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cinccino),
}, //Cinccino,
[SPECIES_GOTHITA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 10),
      PIC_DATA_ICON_INDEX(Gothita, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gothita),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gothita),
}, //Gothita,
[SPECIES_GOTHORITA] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Gothorita, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gothorita),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gothorita),
}, //Gothorita,
[SPECIES_GOTHITELLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Gothitelle, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gothitelle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gothitelle),
}, //Gothitelle,
[SPECIES_SOLOSIS] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x64, 19),
      PIC_DATA_ICON_INDEX(Solosis, 1),
      .enemyMonElevation = 14,
      .cryData = CRY_INFO(Cry_Solosis),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Solosis),
}, //Solosis,
[SPECIES_DUOSION] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 13),
      PIC_DATA_ICON_INDEX(Duosion, 1),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Duosion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Duosion),
}, //Duosion,
[SPECIES_REUNICLUS] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x86, 13),
      PIC_DATA_ICON_INDEX(Reuniclus, 1),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Reuniclus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Reuniclus),
}, //Reuniclus,
[SPECIES_DUCKLETT] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x66, 10),
      PIC_DATA_ICON_INDEX(Ducklett, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ducklett),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ducklett),
}, //Ducklett,
[SPECIES_SWANNA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Swanna, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swanna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swanna),
}, //Swanna,
[SPECIES_VANILLITE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x56, 9),
      PIC_DATA_ICON_INDEX(Vanillite, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vanillite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vanillite),
}, //Vanillite,
[SPECIES_VANILLISH] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Vanillish, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vanillish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vanillish),
}, //Vanillish,
[SPECIES_VANILLUXE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Vanilluxe, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vanilluxe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vanilluxe),
}, //Vanilluxe,
[SPECIES_DEERLING] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Deerling, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Deerling),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deerling),
}, //Deerling,
[SPECIES_SAWSBUCK] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(Sawsbuck, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sawsbuck),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sawsbuck),
}, //Sawsbuck,
[SPECIES_EMOLGA] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x75, 16),
      PIC_DATA_ICON_INDEX(Emolga, 2),
      .enemyMonElevation = 19,
      .cryData = CRY_INFO(Cry_Emolga),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Emolga),
}, //Emolga,
[SPECIES_KARRABLAST] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x66, 14),
      PIC_DATA_ICON_INDEX(Karrablast, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Karrablast),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Karrablast),
}, //Karrablast,
[SPECIES_ESCAVALIER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Escavalier, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Escavalier),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Escavalier),
}, //Escavalier,
[SPECIES_FOONGUS] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Foongus, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Foongus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Foongus),
}, //Foongus,
[SPECIES_AMOONGUSS] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Amoonguss, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Amoonguss),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Amoonguss),
}, //Amoonguss,
[SPECIES_FRILLISH_MALE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x57, 7),
      PIC_DATA_ICON_INDEX(FrillishMale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Frillish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Frillish),
}, //Frillish,
[SPECIES_JELLICENT_MALE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(JellicentMale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Jellicent),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jellicent),
}, //Jellicent,
[SPECIES_ALOMOMOLA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Alomomola, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alomomola),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alomomola),
}, //Alomomola,
[SPECIES_JOLTIK] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x64, 19),
      PIC_DATA_ICON_INDEX(Joltik, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Joltik),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Joltik),
}, //Joltik,
[SPECIES_GALVANTULA] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x85, 18),
      PIC_DATA_ICON_INDEX(Galvantula, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Galvantula),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Galvantula),
}, //Galvantula,
[SPECIES_FERROSEED] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 15),
      PIC_DATA_ICON_INDEX(Ferroseed, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ferroseed),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ferroseed),
}, //Ferroseed,
[SPECIES_FERROTHORN] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Ferrothorn, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ferrothorn),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ferrothorn),
}, //Ferrothorn,
[SPECIES_KLINK] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(Klink, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Klink),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Klink),
}, //Klink,
[SPECIES_KLANG] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Klang, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Klang),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Klang),
}, //Klang,
[SPECIES_KLINKLANG] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Klinklang, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Klinklang),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Klinklang),
}, //Klinklang,
[SPECIES_TYNAMO] = 
    {  
      FRONT_COORD(0x45, 22),
      BACK_COORD(0x83, 21),
      PIC_DATA_ICON_INDEX(Tynamo, 0),
      .enemyMonElevation = 16,
      .cryData = CRY_INFO(Cry_Tynamo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tynamo),
}, //Tynamo,
[SPECIES_EELEKTRIK] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(Eelektrik, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Eelektrik),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Eelektrik),
}, //Eelektrik,
[SPECIES_EELEKTROSS] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Eelektross, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Eelektross),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Eelektross),
}, //Eelektross,
[SPECIES_ELGYEM] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x67, 10),
      PIC_DATA_ICON_INDEX(Elgyem, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Elgyem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Elgyem),
}, //Elgyem,
[SPECIES_BEHEEYEM] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Beheeyem, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Beheeyem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Beheeyem),
}, //Beheeyem,
[SPECIES_LITWICK] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x55, 14),
      PIC_DATA_ICON_INDEX(Litwick, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Litwick),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Litwick),
}, //Litwick,
[SPECIES_LAMPENT] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x76, 12),
      PIC_DATA_ICON_INDEX(Lampent, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lampent),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lampent),
}, //Lampent,
[SPECIES_CHANDELURE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Chandelure, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chandelure),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chandelure),
}, //Chandelure,
[SPECIES_AXEW] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Axew, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Axew),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Axew),
}, //Axew,
[SPECIES_FRAXURE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x86, 13),
      PIC_DATA_ICON_INDEX(Fraxure, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fraxure),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fraxure),
}, //Fraxure,
[SPECIES_HAXORUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Haxorus, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Haxorus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Haxorus),
}, //Haxorus,
[SPECIES_CUBCHOO] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x55, 12),
      PIC_DATA_ICON_INDEX(Cubchoo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cubchoo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cubchoo),
}, //Cubchoo,
[SPECIES_BEARTIC] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Beartic, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Beartic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Beartic),
}, //Beartic,
[SPECIES_CRYOGONAL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(Cryogonal, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cryogonal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cryogonal),
}, //Cryogonal,
[SPECIES_SHELMET] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x84, 19),
      PIC_DATA_ICON_INDEX(Shelmet, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shelmet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shelmet),
}, //Shelmet,
[SPECIES_ACCELGOR] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Accelgor, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Accelgor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Accelgor),
}, //Accelgor,
[SPECIES_STUNFISK] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x83, 22),
      PIC_DATA_ICON_INDEX(Stunfisk, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stunfisk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stunfisk),
}, //Stunfisk,
[SPECIES_MIENFOO] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(Mienfoo, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mienfoo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mienfoo),
}, //Mienfoo,
[SPECIES_MIENSHAO] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Mienshao, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mienshao),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mienshao),
}, //Mienshao,
[SPECIES_DRUDDIGON] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Druddigon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Druddigon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Druddigon),
}, //Druddigon,
[SPECIES_GOLETT] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Golett, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Golett),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golett),
}, //Golett,
[SPECIES_GOLURK] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Golurk, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Golurk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golurk),
}, //Golurk,
[SPECIES_PAWNIARD] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Pawniard, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pawniard),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pawniard),
}, //Pawniard,
[SPECIES_BISHARP] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Bisharp, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bisharp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bisharp),
}, //Bisharp,
[SPECIES_BOUFFALANT] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Bouffalant, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bouffalant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bouffalant),
}, //Bouffalant,
[SPECIES_RUFFLET] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Rufflet, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rufflet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rufflet),
}, //Rufflet,
[SPECIES_BRAVIARY] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Braviary, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Braviary),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Braviary),
}, //Braviary,
[SPECIES_VULLABY] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x86, 14),
      PIC_DATA_ICON_INDEX(Vullaby, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vullaby),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vullaby),
}, //Vullaby,
[SPECIES_MANDIBUZZ] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Mandibuzz, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mandibuzz),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mandibuzz),
}, //Mandibuzz,
[SPECIES_HEATMOR] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x83, 21),
      PIC_DATA_ICON_INDEX(Heatmor, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Heatmor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Heatmor),
}, //Heatmor,
[SPECIES_DURANT] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x84, 17),
      PIC_DATA_ICON_INDEX(Durant, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Durant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Durant),
}, //Durant,
[SPECIES_DEINO] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x66, 14),
      PIC_DATA_ICON_INDEX(Deino, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Deino),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deino),
}, //Deino,
[SPECIES_ZWEILOUS] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Zweilous, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zweilous),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zweilous),
}, //Zweilous,
[SPECIES_HYDREIGON] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Hydreigon, 2),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Hydreigon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hydreigon),
}, //Hydreigon,
[SPECIES_LARVESTA] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Larvesta, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Larvesta),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Larvesta),
}, //Larvesta,
[SPECIES_VOLCARONA] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Volcarona, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Volcarona),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Volcarona),
}, //Volcarona,
[SPECIES_COBALION] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 6),
      PIC_DATA_ICON_INDEX(Cobalion, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cobalion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cobalion),
}, //Cobalion,
[SPECIES_TERRAKION] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Terrakion, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Terrakion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Terrakion),
}, //Terrakion,
[SPECIES_VIRIZION] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Virizion, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Virizion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Virizion),
}, //Virizion,
[SPECIES_TORNADUS_INCARNATE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Tornadus, 1),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_TornadusIncarnate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TornadusIncarnate),
}, //Tornadus,
[SPECIES_THUNDURUS_INCARNATE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Thundurus, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_ThundurusIncarnate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ThundurusIncarnate),
}, //Thundurus,
[SPECIES_RESHIRAM] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Reshiram, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Reshiram),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Reshiram),
}, //Reshiram,
[SPECIES_ZEKROM] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Zekrom, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zekrom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zekrom),
}, //Zekrom,
[SPECIES_LANDORUS_INCARNATE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Landorus, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_LandorusIncarnate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LandorusIncarnate),
}, //Landorus,
[SPECIES_KYUREM] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Kyurem, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kyurem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kyurem),
}, //Kyurem,
[SPECIES_KELDEO] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(Keldeo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Keldeo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Keldeo),
}, //Keldeo,
[SPECIES_MELOETTA] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Meloetta, 4),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meloetta),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meloetta),
}, //Meloetta,
[SPECIES_GENESECT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Genesect, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Genesect),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Genesect),
}, //Genesect,
[SPECIES_CHESPIN] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x78, 6),
      PIC_DATA_ICON_INDEX(Chespin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chespin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chespin),
}, //Chespin,
[SPECIES_QUILLADIN] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Quilladin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Quilladin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Quilladin),
}, //Quilladin,
[SPECIES_CHESNAUGHT] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Chesnaught, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chesnaught),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chesnaught),
}, //Chesnaught,
[SPECIES_FENNEKIN] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Fennekin, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fennekin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fennekin),
}, //Fennekin,
[SPECIES_BRAIXEN] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Braixen, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Braixen),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Braixen),
}, //Braixen,
[SPECIES_DELPHOX] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Delphox, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Delphox),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Delphox),
}, //Delphox,
[SPECIES_FROAKIE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Froakie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Froakie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Froakie),
}, //Froakie,
[SPECIES_FROGADIER] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Frogadier, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Frogadier),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Frogadier),
}, //Frogadier,
[SPECIES_GRENINJA] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Greninja, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Greninja),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Greninja),
}, //Greninja,
[SPECIES_BUNNELBY] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Bunnelby, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bunnelby),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bunnelby),
}, //Bunnelby,
[SPECIES_DIGGERSBY] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Diggersby, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Diggersby),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Diggersby),
}, //Diggersby,
[SPECIES_FLETCHLING] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Fletchling, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fletchling),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fletchling),
}, //Fletchling,
[SPECIES_FLETCHINDER] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Fletchinder, 2),
      .enemyMonElevation = 9,
      .cryData = CRY_INFO(Cry_Fletchinder),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fletchinder),
}, //Fletchinder,
[SPECIES_TALONFLAME] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Talonflame, 2),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Talonflame),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Talonflame),
}, //Talonflame,
[SPECIES_SCATTERBUG] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x57, 12),
      PIC_DATA_ICON_INDEX(Scatterbug, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scatterbug),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scatterbug),
}, //Scatterbug,
[SPECIES_SPEWPA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 12),
      PIC_DATA_ICON_INDEX(Spewpa, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spewpa),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spewpa),
}, //Spewpa,
[SPECIES_VIVILLON_SNOW] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSnow, 0),
      .enemyMonElevation = 9,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //Vivillon,
[SPECIES_LITLEO] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Litleo, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Litleo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Litleo),
}, //Litleo,
[SPECIES_PYROAR_MALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(PyroarMale, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pyroar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pyroar),
}, //Pyroar,
[SPECIES_FLABEBE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Flabebe, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Flabebe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flabebe),
}, //Flabebe,
[SPECIES_FLOETTE] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Floette, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Floette),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floette),
}, //Floette,
[SPECIES_FLORGES] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Florges, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Florges),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Florges),
}, //Florges,
[SPECIES_SKIDDO] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Skiddo, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skiddo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skiddo),
}, //Skiddo,
[SPECIES_GOGOAT] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Gogoat, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gogoat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gogoat),
}, //Gogoat,
[SPECIES_PANCHAM] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Pancham, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pancham),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pancham),
}, //Pancham,
[SPECIES_PANGORO] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Pangoro, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pangoro),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pangoro),
}, //Pangoro,
[SPECIES_FURFROU] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Furfrou, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //Furfrou,
[SPECIES_ESPURR] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Espurr, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Espurr),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Espurr),
}, //Espurr,
[SPECIES_MEOWSTIC_MALE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(MeowsticMale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meowstic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meowstic),
}, //Meowstic,
[SPECIES_HONEDGE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Honedge, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Honedge),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Honedge),
}, //Honedge,
[SPECIES_DOUBLADE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Doublade, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Doublade),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Doublade),
}, //Doublade,
[SPECIES_AEGISLASH] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Aegislash, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aegislash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aegislash),
}, //Aegislash,
[SPECIES_SPRITZEE] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Spritzee, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spritzee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spritzee),
}, //Spritzee,
[SPECIES_AROMATISSE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Aromatisse, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aromatisse),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aromatisse),
}, //Aromatisse,
[SPECIES_SWIRLIX] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Swirlix, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Swirlix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Swirlix),
}, //Swirlix,
[SPECIES_SLURPUFF] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Slurpuff, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slurpuff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slurpuff),
}, //Slurpuff,
[SPECIES_INKAY] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x78, 9),
      PIC_DATA_ICON_INDEX(Inkay, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Inkay),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Inkay),
}, //Inkay,
[SPECIES_MALAMAR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Malamar, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Malamar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Malamar),
}, //Malamar,
[SPECIES_BINACLE] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Binacle, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Binacle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Binacle),
}, //Binacle,
[SPECIES_BARBARACLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Barbaracle, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Barbaracle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Barbaracle),
}, //Barbaracle,
[SPECIES_SKRELP] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Skrelp, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skrelp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skrelp),
}, //Skrelp,
[SPECIES_DRAGALGE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Dragalge, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dragalge),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dragalge),
}, //Dragalge,
[SPECIES_CLAUNCHER] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Clauncher, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clauncher),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clauncher),
}, //Clauncher,
[SPECIES_CLAWITZER] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Clawitzer, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clawitzer),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clawitzer),
}, //Clawitzer,
[SPECIES_HELIOPTILE] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Helioptile, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Helioptile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Helioptile),
}, //Helioptile,
[SPECIES_HELIOLISK] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Heliolisk, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Heliolisk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Heliolisk),
}, //Heliolisk,
[SPECIES_TYRUNT] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Tyrunt, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tyrunt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tyrunt),
}, //Tyrunt,
[SPECIES_TYRANTRUM] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Tyrantrum, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tyrantrum),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tyrantrum),
}, //Tyrantrum,
[SPECIES_AMAURA] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x58, 3),
      PIC_DATA_ICON_INDEX(Amaura, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Amaura),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Amaura),
}, //Amaura,
[SPECIES_AURORUS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Aurorus, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aurorus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aurorus),
}, //Aurorus,
[SPECIES_SYLVEON] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Sylveon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sylveon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sylveon),
}, //Sylveon,
[SPECIES_HAWLUCHA] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Hawlucha, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hawlucha),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hawlucha),
}, //Hawlucha,
[SPECIES_DEDENNE] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Dedenne, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dedenne),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dedenne),
}, //Dedenne,
[SPECIES_CARBINK] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Carbink, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Carbink),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Carbink),
}, //Carbink,
[SPECIES_GOOMY] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Goomy, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Goomy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Goomy),
}, //Goomy,
[SPECIES_SLIGGOO] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Sliggoo, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sliggoo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sliggoo),
}, //Sliggoo,
[SPECIES_GOODRA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Goodra, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Goodra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Goodra),
}, //Goodra,
[SPECIES_KLEFKI] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x78, 8),
      PIC_DATA_ICON_INDEX(Klefki, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO_UNCOMP(Cry_Klefki),
      .cryData_Reverse = CRY_INFO_REVERSE_UNCOMP(Cry_Klefki),
}, //Klefki,
[SPECIES_PHANTUMP] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Phantump, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Phantump),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Phantump),
}, //Phantump,
[SPECIES_TREVENANT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Trevenant, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Trevenant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Trevenant),
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
      .cryData = CRY_INFO(Cry_Pumpkaboo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pumpkaboo),
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
      .cryData = CRY_INFO(Cry_Gourgeist),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gourgeist),
}, //Gourgeist,
[SPECIES_BERGMITE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x76, 13),
      PIC_DATA_ICON_INDEX(Bergmite, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bergmite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bergmite),
}, //Bergmite,
[SPECIES_AVALUGG] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x85, 12),
      PIC_DATA_ICON_INDEX(Avalugg, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Avalugg),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Avalugg),
}, //Avalugg,
[SPECIES_NOIBAT] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x78, 7),
      PIC_DATA_ICON_INDEX(Noibat, 2),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Noibat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Noibat),
}, //Noibat,
[SPECIES_NOIVERN] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Noivern, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Noivern),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Noivern),
}, //Noivern,
[SPECIES_XERNEAS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Xerneas, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Xerneas),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Xerneas),
}, //Xerneas,
[SPECIES_YVELTAL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Yveltal, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Yveltal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yveltal),
}, //Yveltal,
[SPECIES_ZYGARDE_10] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 9),
      PIC_DATA_ICON_INDEX(Zygarde10, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zygarde10),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zygarde10),
}, //Zygarde,
[SPECIES_DIANCIE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Diancie, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Diancie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Diancie),
}, //Diancie,
[SPECIES_HOOPA] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Hoopa, 0),
      .enemyMonElevation = 13,
      .cryData = CRY_INFO(Cry_HoopaConfined),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_HoopaConfined),
}, //Hoopa,
[SPECIES_VOLCANION] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Volcanion, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Volcanion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Volcanion),
}, //Volcanion,
[SPECIES_ROWLET] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 15),
      PIC_DATA_ICON_INDEX(Rowlet, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rowlet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rowlet),
}, //Rowlet,
[SPECIES_DARTRIX] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x77, 4),
      PIC_DATA_ICON_INDEX(Dartrix, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dartrix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dartrix),
}, //Dartrix,
[SPECIES_DECIDUEYE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Decidueye, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Decidueye),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Decidueye),
}, //Decidueye,
[SPECIES_LITTEN] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Litten, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Litten),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Litten),
}, //Litten,
[SPECIES_TORRACAT] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Torracat, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Torracat),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Torracat),
}, //Torracat,
[SPECIES_INCINEROAR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Incineroar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Incineroar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Incineroar),
}, //Incineroar,
[SPECIES_POPPLIO] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 11),
      PIC_DATA_ICON_INDEX(Popplio, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Popplio),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Popplio),
}, //Popplio,
[SPECIES_BRIONNE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x67, 9),
      PIC_DATA_ICON_INDEX(Brionne, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Brionne),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Brionne),
}, //Brionne,
[SPECIES_PRIMARINA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Primarina, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Primarina),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Primarina),
}, //Primarina,
[SPECIES_PIKIPEK] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(Pikipek, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikipek),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikipek),
}, //Pikipek,
[SPECIES_TRUMBEAK] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Trumbeak, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Trumbeak),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Trumbeak),
}, //Trumbeak,
[SPECIES_TOUCANNON] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Toucannon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Toucannon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Toucannon),
}, //Toucannon,
[SPECIES_YUNGOOS] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x65, 14),
      PIC_DATA_ICON_INDEX(Yungoos, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Yungoos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yungoos),
}, //Yungoos,
[SPECIES_GUMSHOOS] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(Gumshoos, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gumshoos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gumshoos),
}, //Gumshoos,
[SPECIES_GRUBBIN] = 
    {  
      FRONT_COORD(0x45, 17),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Grubbin, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grubbin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grubbin),
}, //Grubbin,
[SPECIES_CHARJABUG] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Charjabug, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Charjabug),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Charjabug),
}, //Charjabug,
[SPECIES_VIKAVOLT] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Vikavolt, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Vikavolt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vikavolt),
}, //Vikavolt,
[SPECIES_CRABRAWLER] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Crabrawler, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Crabrawler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Crabrawler),
}, //Crabrawler,
[SPECIES_CRABOMINABLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Crabominable, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Crabominable),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Crabominable),
}, //Crabominable,
[SPECIES_ORICORIO_BAILE] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioBaile, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_OricorioBaile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_OricorioBaile),
}, //Oricorio_Baile,
[SPECIES_CUTIEFLY] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x76, 15),
      PIC_DATA_ICON_INDEX(Cutiefly, 2),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Cutiefly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cutiefly),
}, //Cutiefly,
[SPECIES_RIBOMBEE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Ribombee, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ribombee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ribombee),
}, //Ribombee,
[SPECIES_ROCKRUFF] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Rockruff, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rockruff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rockruff),
}, //Rockruff,
[SPECIES_LYCANROC_MIDDAY] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(LycanrocMidday, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_LycanrocMidday),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LycanrocMidday),
}, //Lycanroc,
[SPECIES_WISHIWASHI_SOLO] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x74, 18),
      PIC_DATA_ICON_INDEX(Wishiwashi, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_WishiwashiSolo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_WishiwashiSolo),
}, //Wishiwashi,
[SPECIES_MAREANIE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x86, 15),
      PIC_DATA_ICON_INDEX(Mareanie, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mareanie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mareanie),
}, //Mareanie,
[SPECIES_TOXAPEX] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Toxapex, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Toxapex),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Toxapex),
}, //Toxapex,
[SPECIES_MUDBRAY] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Mudbray, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mudbray),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mudbray),
}, //Mudbray,
[SPECIES_MUDSDALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Mudsdale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mudsdale),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mudsdale),
}, //Mudsdale,
[SPECIES_DEWPIDER] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x56, 8),
      PIC_DATA_ICON_INDEX(Dewpider, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dewpider),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dewpider),
}, //Dewpider,
[SPECIES_ARAQUANID] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Araquanid, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Araquanid),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Araquanid),
}, //Araquanid,
[SPECIES_FOMANTIS] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x57, 5),
      PIC_DATA_ICON_INDEX(Fomantis, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fomantis),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fomantis),
}, //Fomantis,
[SPECIES_LURANTIS] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x78, 1),
      PIC_DATA_ICON_INDEX(Lurantis, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lurantis),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lurantis),
}, //Lurantis,
[SPECIES_MORELULL] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x56, 9),
      PIC_DATA_ICON_INDEX(Morelull, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Morelull),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Morelull),
}, //Morelull,
[SPECIES_SHIINOTIC] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Shiinotic, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shiinotic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shiinotic),
}, //Shiinotic,
[SPECIES_SALANDIT] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Salandit, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Salandit),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Salandit),
}, //Salandit,
[SPECIES_SALAZZLE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x68, 3),
      PIC_DATA_ICON_INDEX(Salazzle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Salazzle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Salazzle),
}, //Salazzle,
[SPECIES_STUFFUL] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x75, 12),
      PIC_DATA_ICON_INDEX(Stufful, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stufful),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stufful),
}, //Stufful,
[SPECIES_BEWEAR] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Bewear, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bewear),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bewear),
}, //Bewear,
[SPECIES_BOUNSWEET] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x65, 14),
      PIC_DATA_ICON_INDEX(Bounsweet, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bounsweet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bounsweet),
}, //Bounsweet,
[SPECIES_STEENEE] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(Steenee, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Steenee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Steenee),
}, //Steenee,
[SPECIES_TSAREENA] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Tsareena, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tsareena),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tsareena),
}, //Tsareena,
[SPECIES_COMFEY] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Comfey, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Comfey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Comfey),
}, //Comfey,
[SPECIES_ORANGURU] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Oranguru, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Oranguru),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Oranguru),
}, //Oranguru,
[SPECIES_PASSIMIAN] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Passimian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Passimian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Passimian),
}, //Passimian,
[SPECIES_WIMPOD] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Wimpod, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wimpod),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wimpod),
}, //Wimpod,
[SPECIES_GOLISOPOD] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Golisopod, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Golisopod),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golisopod),
}, //Golisopod,
[SPECIES_SANDYGAST] = 
    {  
      FRONT_COORD(0x45, 11),
      BACK_COORD(0x56, 11),
      PIC_DATA_ICON_INDEX(Sandygast, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandygast),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandygast),
}, //Sandygast,
[SPECIES_PALOSSAND] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Palossand, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Palossand),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Palossand),
}, //Palossand,
[SPECIES_PYUKUMUKU] = 
    {  
      FRONT_COORD(0x45, 15),
      BACK_COORD(0x64, 16),
      PIC_DATA_ICON_INDEX(Pyukumuku, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pyukumuku),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pyukumuku),
}, //Pyukumuku,
[SPECIES_TYPE_NULL] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x78, 1),
      PIC_DATA_ICON_INDEX(TypeNull, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TypeNull),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TypeNull),
}, //TypeNull,
[SPECIES_SILVALLY] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Silvally, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
}, //Silvally,
[SPECIES_MINIOR] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 17,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //Minior,
[SPECIES_KOMALA] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Komala, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Komala),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Komala),
}, //Komala,
[SPECIES_TURTONATOR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(Turtonator, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Turtonator),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Turtonator),
}, //Turtonator,
[SPECIES_TOGEDEMARU] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x86, 13),
      PIC_DATA_ICON_INDEX(Togedemaru, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Togedemaru),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Togedemaru),
}, //Togedemaru,
[SPECIES_MIMIKYU] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(Mimikyu, 3),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mimikyu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mimikyu),
}, //Mimikyu,
[SPECIES_BRUXISH] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 14),
      PIC_DATA_ICON_INDEX(Bruxish, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bruxish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bruxish),
}, //Bruxish,
[SPECIES_DRAMPA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Drampa, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drampa),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drampa),
}, //Drampa,
[SPECIES_DHELMISE] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Dhelmise, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dhelmise),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dhelmise),
}, //Dhelmise,
[SPECIES_JANGMO_O] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x67, 7),
      PIC_DATA_ICON_INDEX(JangmoO, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_JangmoO),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_JangmoO),
}, //Jangmoo,
[SPECIES_HAKAMO_O] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(HakamoO, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_HakamoO),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_HakamoO),
}, //Hakamoo,
[SPECIES_KOMMO_O] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(KommoO, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_KommoO),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_KommoO),
}, //Kommoo,
[SPECIES_TAPU_KOKO] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(TapuKoko, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TapuKoko),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TapuKoko),
}, //TapuKoko,
[SPECIES_TAPU_LELE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(TapuLele, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TapuLele),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TapuLele),
}, //TapuLele,
[SPECIES_TAPU_BULU] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(TapuBulu, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TapuBulu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TapuBulu),
}, //TapuBulu,
[SPECIES_TAPU_FINI] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(TapuFini, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TapuFini),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TapuFini),
}, //TapuFini,
[SPECIES_COSMOG] = 
    {  
      FRONT_COORD(0x45, 10),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Cosmog, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cosmog),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cosmog),
}, //Cosmog,
[SPECIES_COSMOEM] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x85, 17),
      PIC_DATA_ICON_INDEX(Cosmoem, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cosmoem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cosmoem),
}, //Cosmoem,
[SPECIES_SOLGALEO] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Solgaleo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Solgaleo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Solgaleo),
}, //Solgaleo,
[SPECIES_LUNALA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Lunala, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lunala),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lunala),
}, //Lunala,
[SPECIES_NIHILEGO] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Nihilego, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nihilego),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nihilego),
}, //Nihilego,
[SPECIES_BUZZWOLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 14),
      PIC_DATA_ICON_INDEX(Buzzwole, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Buzzwole),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Buzzwole),
}, //Buzzwole,
[SPECIES_PHEROMOSA] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Pheromosa, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pheromosa),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pheromosa),
}, //Pheromosa,
[SPECIES_XURKITREE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Xurkitree, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Xurkitree),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Xurkitree),
}, //Xurkitree,
[SPECIES_CELESTEELA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Celesteela, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Celesteela),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Celesteela),
}, //Celesteela,
[SPECIES_KARTANA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Kartana, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kartana),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kartana),
}, //Kartana,
[SPECIES_GUZZLORD] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x87, 10),
      PIC_DATA_ICON_INDEX(Guzzlord, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Guzzlord),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Guzzlord),
}, //Guzzlord,
[SPECIES_NECROZMA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Necrozma, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Necrozma),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Necrozma),
}, //Necrozma,
[SPECIES_MAGEARNA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Magearna, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magearna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magearna),
}, //Magearna,
[SPECIES_MARSHADOW] = 
    {  
      FRONT_COORD(0x45, 9),
      BACK_COORD(0x57, 6),
      PIC_DATA_ICON_INDEX(Marshadow, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Marshadow),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Marshadow),
}, //Marshadow,
[SPECIES_POIPOLE] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x67, 6),
      PIC_DATA_ICON_INDEX(Poipole, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Poipole),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poipole),
}, //Poipole,
[SPECIES_NAGANADEL] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Naganadel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Naganadel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Naganadel),
}, //Naganadel,
[SPECIES_STAKATAKA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x86, 12),
      PIC_DATA_ICON_INDEX(Stakataka, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stakataka),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stakataka),
}, //Stakataka,
[SPECIES_BLACEPHALON] = 
    {  
      FRONT_COORD(0x45, 1),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Blacephalon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Blacephalon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Blacephalon),
}, //Blacephalon,
[SPECIES_ZERAORA] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Zeraora, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zeraora),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zeraora),
}, //Zeraora,
[SPECIES_MELTAN] = 
    {  
      FRONT_COORD(0x45, 8),
      BACK_COORD(0x55, 12),
      PIC_DATA_ICON_INDEX(Meltan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meltan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meltan),
}, //Meltan,
[SPECIES_MELMETAL] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Melmetal, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Melmetal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Melmetal),
}, //Melmetal,
[SPECIES_GROOKEY] = 
    {  
      FRONT_COORD(0x56, 12),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Grookey, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grookey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grookey),
}, //Grookey,
[SPECIES_THWACKEY] = 
    {  
      FRONT_COORD(0x67, 7),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Thwackey, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Thwackey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Thwackey),
}, //Thwackey,
[SPECIES_RILLABOOM] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Rillaboom, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rillaboom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rillaboom),
}, //Rillaboom,
[SPECIES_SCORBUNNY] = 
    {  
      FRONT_COORD(0x57, 8),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Scorbunny, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scorbunny),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scorbunny),
}, //Scorbunny,
[SPECIES_RABOOT] = 
    {  
      FRONT_COORD(0x57, 7),
      BACK_COORD(0x77, 6),
      PIC_DATA_ICON_INDEX(Raboot, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Raboot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Raboot),
}, //Raboot,
[SPECIES_CINDERACE] = 
    {  
      FRONT_COORD(0x58, 0),
      BACK_COORD(0x67, 4),
      PIC_DATA_ICON_INDEX(Cinderace, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cinderace),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cinderace),
}, //Cinderace,
[SPECIES_SOBBLE] = 
    {  
      FRONT_COORD(0x57, 11),
      BACK_COORD(0x57, 8),
      PIC_DATA_ICON_INDEX(Sobble, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sobble),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sobble),
}, //Sobble,
[SPECIES_DRIZZILE] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Drizzile, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drizzile),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drizzile),
}, //Drizzile,
[SPECIES_INTELEON] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Inteleon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Inteleon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Inteleon),
}, //Inteleon,
[SPECIES_SKWOVET] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Skwovet, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skwovet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skwovet),
}, //Skwovet,
[SPECIES_GREEDENT] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Greedent, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Greedent),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Greedent),
}, //Greedent,
[SPECIES_ROOKIDEE] = 
    {  
      FRONT_COORD(0x55, 16),
      BACK_COORD(0x84, 17),
      PIC_DATA_ICON_INDEX(Rookidee, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rookidee),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rookidee),
}, //Rookidee,
[SPECIES_CORVISQUIRE] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Corvisquire, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_Corvisquire),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Corvisquire),
}, //Corvisquire,
[SPECIES_CORVIKNIGHT] = 
    {  
      FRONT_COORD(0x78, 2),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Corviknight, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Corviknight),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Corviknight),
}, //Corviknight,
[SPECIES_BLIPBUG] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x57, 7),
      PIC_DATA_ICON_INDEX(Blipbug, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Blipbug),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Blipbug),
}, //Blipbug,
[SPECIES_DOTTLER] = 
    {  
      FRONT_COORD(0x65, 13),
      BACK_COORD(0x74, 17),
      PIC_DATA_ICON_INDEX(Dottler, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dottler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dottler),
}, //Dottler,
[SPECIES_ORBEETLE] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Orbeetle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Orbeetle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Orbeetle),
}, //Orbeetle,
[SPECIES_NICKIT] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Nickit, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nickit),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nickit),
}, //Nickit,
[SPECIES_THIEVUL] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Thievul, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Thievul),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Thievul),
}, //Thievul,
[SPECIES_GOSSIFLEUR] = 
    {  
      FRONT_COORD(0x67, 11),
      BACK_COORD(0x76, 15),
      PIC_DATA_ICON_INDEX(Gossifleur, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gossifleur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gossifleur),
}, //Gossifleur,
[SPECIES_ELDEGOSS] = 
    {  
      FRONT_COORD(0x67, 4),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Eldegoss, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Eldegoss),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Eldegoss),
}, //Eldegoss,
[SPECIES_WOOLOO] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x74, 18),
      PIC_DATA_ICON_INDEX(Wooloo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wooloo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wooloo),
}, //Wooloo,
[SPECIES_DUBWOOL] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Dubwool, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dubwool),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dubwool),
}, //Dubwool,
[SPECIES_CHEWTLE] = 
    {  
      FRONT_COORD(0x46, 13),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(Chewtle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Chewtle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Chewtle),
}, //Chewtle,
[SPECIES_DREDNAW] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x85, 18),
      PIC_DATA_ICON_INDEX(Drednaw, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drednaw),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drednaw),
}, //Drednaw,
[SPECIES_YAMPER] = 
    {  
      FRONT_COORD(0x56, 10),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(Yamper, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Yamper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yamper),
}, //Yamper,
[SPECIES_BOLTUND] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Boltund, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Boltund),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Boltund),
}, //Boltund,
[SPECIES_ROLYCOLY] = 
    {  
      FRONT_COORD(0x55, 16),
      BACK_COORD(0x84, 17),
      PIC_DATA_ICON_INDEX(Rolycoly, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rolycoly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rolycoly),
}, //Rolycoly,
[SPECIES_CARKOL] = 
    {  
      FRONT_COORD(0x67, 8),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Carkol, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Carkol),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Carkol),
}, //Carkol,
[SPECIES_COALOSSAL] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Coalossal, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Coalossal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Coalossal),
}, //Coalossal,
[SPECIES_APPLIN] = 
    {  
      FRONT_COORD(0x45, 16),
      BACK_COORD(0x56, 15),
      PIC_DATA_ICON_INDEX(Applin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Applin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Applin),
}, //Applin,
[SPECIES_FLAPPLE] = 
    {  
      FRONT_COORD(0x76, 9),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Flapple, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Flapple),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flapple),
}, //Flapple,
[SPECIES_APPLETUN] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x87, 11),
      PIC_DATA_ICON_INDEX(Appletun, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Appletun),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Appletun),
}, //Appletun,
[SPECIES_SILICOBRA] = 
    {  
      FRONT_COORD(0x55, 12),
      BACK_COORD(0x76, 10),
      PIC_DATA_ICON_INDEX(Silicobra, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Silicobra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silicobra),
}, //Silicobra,
[SPECIES_SANDACONDA] = 
    {  
      FRONT_COORD(0x85, 12),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Sandaconda, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandaconda),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandaconda),
}, //Sandaconda,
[SPECIES_CRAMORANT] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 1),
      PIC_DATA_ICON_INDEX(Cramorant, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cramorant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cramorant),
}, //Cramorant,
[SPECIES_ARROKUDA] = 
    {  
      FRONT_COORD(0x74, 17),
      BACK_COORD(0x65, 15),
      PIC_DATA_ICON_INDEX(Arrokuda, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arrokuda),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arrokuda),
}, //Arrokuda,
[SPECIES_BARRASKEWDA] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Barraskewda, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Barraskewda),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Barraskewda),
}, //Barraskewda,
[SPECIES_TOXEL] = 
    {  
      FRONT_COORD(0x56, 11),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Toxel, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Toxel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Toxel),
}, //Toxel,
[SPECIES_TOXTRICITY_AMPED] = 
    {  
      FRONT_COORD(0x68, 1),
      BACK_COORD(0x78, 0),
      PIC_DATA_ICON_INDEX(Toxtricity, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ToxtricityAmped),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ToxtricityAmped),
}, //Toxtricity,
[SPECIES_SIZZLIPEDE] = 
    {  
      FRONT_COORD(0x64, 17),
      BACK_COORD(0x54, 16),
      PIC_DATA_ICON_INDEX(Sizzlipede, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sizzlipede),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sizzlipede),
}, //Sizzlipede,
[SPECIES_CENTISKORCH] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(Centiskorch, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Centiskorch),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Centiskorch),
}, //Centiskorch,
[SPECIES_CLOBBOPUS] = 
    {  
      FRONT_COORD(0x65, 15),
      BACK_COORD(0x85, 14),
      PIC_DATA_ICON_INDEX(Clobbopus, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clobbopus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clobbopus),
}, //Clobbopus,
[SPECIES_GRAPPLOCT] = 
    {  
      FRONT_COORD(0x67, 5),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Grapploct, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grapploct),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grapploct),
}, //Grapploct,
[SPECIES_SINISTEA] = 
    {  
      FRONT_COORD(0x54, 17),
      BACK_COORD(0x64, 16),
      PIC_DATA_ICON_INDEX(Sinistea, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sinistea),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sinistea),
}, //Sinistea,
[SPECIES_POLTEAGEIST] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(Polteageist, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Polteageist),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Polteageist),
}, //Polteageist,
[SPECIES_HATENNA] = 
    {  
      FRONT_COORD(0x66, 12),
      BACK_COORD(0x55, 12),
      PIC_DATA_ICON_INDEX(Hatenna, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hatenna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hatenna),
}, //Hatenna,
[SPECIES_HATTREM] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Hattrem, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hattrem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hattrem),
}, //Hattrem,
[SPECIES_HATTERENE] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(Hatterene, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hatterene),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hatterene),
}, //Hatterene,
[SPECIES_IMPIDIMP] = 
    {  
      FRONT_COORD(0x65, 12),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(Impidimp, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Impidimp),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Impidimp),
}, //Impidimp,
[SPECIES_MORGREM] = 
    {  
      FRONT_COORD(0x67, 6),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(Morgrem, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Morgrem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Morgrem),
}, //Morgrem,
[SPECIES_GRIMMSNARL] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(Grimmsnarl, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grimmsnarl),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grimmsnarl),
}, //Grimmsnarl,
[SPECIES_OBSTAGOON] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Obstagoon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Obstagoon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Obstagoon),
}, //Obstagoon,
[SPECIES_PERRSERKER] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Perrserker, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Perrserker),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Perrserker),
}, //Perrserker,
[SPECIES_CURSOLA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Cursola, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cursola),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cursola),
}, //Cursola,
[SPECIES_SIRFETCHD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(Sirfetchd, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sirfetchd),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sirfetchd),
}, //Sirfetchd,
[SPECIES_MR_RIME] = 
    {  
      FRONT_COORD(0x78, 4),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(MrRime, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MrRime),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MrRime),
}, //MrRime,
[SPECIES_RUNERIGUS] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(Runerigus, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Runerigus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Runerigus),
}, //Runerigus,
[SPECIES_MILCERY] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x76, 16),
      PIC_DATA_ICON_INDEX(Milcery, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Milcery),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Milcery),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,
[SPECIES_FALINKS] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x85, 15),
      PIC_DATA_ICON_INDEX(Falinks, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Falinks),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Falinks),
}, //Falinks,
[SPECIES_PINCURCHIN] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x75, 13),
      PIC_DATA_ICON_INDEX(Pincurchin, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pincurchin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pincurchin),
}, //Pincurchin,
[SPECIES_SNOM] = 
    {  
      FRONT_COORD(0x54, 20),
      BACK_COORD(0x64, 17),
      PIC_DATA_ICON_INDEX(Snom, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Snom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Snom),
}, //Snom,
[SPECIES_FROSMOTH] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Frosmoth, 0),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Frosmoth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Frosmoth),
}, //Frosmoth,
[SPECIES_STONJOURNER] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Stonjourner, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stonjourner),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stonjourner),
}, //Stonjourner,
[SPECIES_EISCUE_ICE_FACE] = 
    {  
      FRONT_COORD(0x58, 0),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(Eiscue, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_EiscueIceFace),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EiscueIceFace),
}, //Eiscue,
[SPECIES_INDEEDEE_MALE] = 
    {  
      FRONT_COORD(0x57, 9),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(IndeedeeMale, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IndeedeeMale),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IndeedeeMale),
}, //Indeedee,
[SPECIES_MORPEKO_FULL_BELLY] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(Morpeko, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MorpekoFullBelly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MorpekoFullBelly),
}, //Morpeko,
[SPECIES_CUFANT] = 
    {  
      FRONT_COORD(0x76, 11),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Cufant, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cufant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cufant),
}, //Cufant,
[SPECIES_COPPERAJAH] = 
    {  
      FRONT_COORD(0x87, 5),
      BACK_COORD(0x84, 16),
      PIC_DATA_ICON_INDEX(Copperajah, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Copperajah),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Copperajah),
}, //Copperajah,
[SPECIES_DRACOZOLT] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(Dracozolt, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dracozolt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dracozolt),
}, //Dracozolt,
[SPECIES_ARCTOZOLT] = 
    {  
      FRONT_COORD(0x78, 1),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(Arctozolt, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arctozolt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arctozolt),
}, //Arctozolt,
[SPECIES_DRACOVISH] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Dracovish, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dracovish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dracovish),
}, //Dracovish,
[SPECIES_ARCTOVISH] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Arctovish, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arctovish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arctovish),
}, //Arctovish,
[SPECIES_DURALUDON] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Duraludon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Duraludon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Duraludon),
}, //Duraludon,
[SPECIES_DREEPY] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x75, 15),
      PIC_DATA_ICON_INDEX(Dreepy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dreepy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dreepy),
}, //Dreepy,
[SPECIES_DRAKLOAK] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(Drakloak, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Drakloak),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Drakloak),
}, //Drakloak,
[SPECIES_DRAGAPULT] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(Dragapult, 0),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Dragapult),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dragapult),
}, //Dragapult,
[SPECIES_ZACIAN] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(Zacian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ZacianHeroOfManyBattles),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ZacianHeroOfManyBattles),
}, //Zacian,
[SPECIES_ZAMAZENTA] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Zamazenta, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ZamazentaHeroOfManyBattles),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ZamazentaHeroOfManyBattles),
}, //Zamazenta,
[SPECIES_ETERNATUS] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Eternatus, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Eternatus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Eternatus),
}, //Eternatus,
[SPECIES_KUBFU] = 
    {  
      FRONT_COORD(0x56, 8),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(Kubfu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kubfu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kubfu),
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
      .cryData = CRY_INFO(Cry_UrshifuSingleStrikeStyle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_UrshifuSingleStrikeStyle),
}, //Urshifu,
[SPECIES_ZARUDE] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(Zarude, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zarude),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zarude),
}, //Zarude,
[SPECIES_REGIELEKI] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 11),
      PIC_DATA_ICON_INDEX(Regieleki, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Regieleki),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Regieleki),
}, //Regieleki,
[SPECIES_REGIDRAGO] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(Regidrago, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Regidrago),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Regidrago),
}, //Regidrago,
[SPECIES_GLASTRIER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Glastrier, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Glastrier),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Glastrier),
}, //Glastrier,
[SPECIES_SPECTRIER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(Spectrier, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spectrier),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spectrier),
}, //Spectrier,
[SPECIES_CALYREX] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x76, 10),
      PIC_DATA_ICON_INDEX(Calyrex, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Calyrex),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Calyrex),
}, //Calyrex,
[SPECIES_WYRDEER] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Wyrdeer, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wyrdeer),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wyrdeer),
}, //Wyrdeer,
[SPECIES_KLEAVOR] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 5),
      PIC_DATA_ICON_INDEX(Kleavor, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kleavor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kleavor),
}, //Kleavor,
[SPECIES_URSALUNA] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 14),
      PIC_DATA_ICON_INDEX(Ursaluna, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ursaluna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ursaluna),
}, //Ursaluna,
[SPECIES_BASCULEGION_MALE] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x72, 1),
      PIC_DATA_ICON_INDEX(BasculegionMale, 4),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Basculegion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Basculegion),
}, //Basculegion,
[SPECIES_SNEASLER] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x76, 1),
      PIC_DATA_ICON_INDEX(Sneasler, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sneasler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sneasler),
}, //Sneasler,
[SPECIES_OVERQWIL] = 
    {  
      FRONT_COORD(0x62, 5),
      BACK_COORD(0x62, 12),
      PIC_DATA_ICON_INDEX(Overqwil, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Overqwil),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Overqwil),
}, //Overqwil,
[SPECIES_ENAMORUS_INCARNATE] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x68, 1),
      PIC_DATA_ICON_INDEX(Enamorus, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_EnamorusIncarnate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EnamorusIncarnate),
}, //Enamorus,
    [SPECIES_CEFIREON] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,0),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_EnamorusIncarnate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EnamorusIncarnate),
}, //Enamorus,
    [SPECIES_FRAEYJTA] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,0),
      PIC_DATA_ICON_INDEX(CircledQuestionMark,0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_EnamorusIncarnate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EnamorusIncarnate),
}, //Enamorus,
[SPECIES_SPRIGATITO] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Sprigatito, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sprigatito),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sprigatito),
},

[SPECIES_FLORAGATO] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Floragato, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Floragato),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floragato),
},

[SPECIES_MEOWSCARADA] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Meowscarada, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meowscarada),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meowscarada),
},

[SPECIES_FUECOCO] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Fuecoco, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fuecoco),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fuecoco),
},

[SPECIES_CROCALOR] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Crocalor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Crocalor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Crocalor),
},

[SPECIES_SKELEDIRGE] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Skeledirge, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Skeledirge),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Skeledirge),
},

[SPECIES_QUAXLY] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Quaxly, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Quaxly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Quaxly),
},

[SPECIES_QUAXWELL] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Quaxwell, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Quaxwell),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Quaxwell),
},

[SPECIES_QUAQUAVAL] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Quaquaval, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Quaquaval),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Quaquaval),
},

[SPECIES_LECHONK] =
    {
      FRONT_COORD(0x88, 12),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Lechonk, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lechonk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lechonk),
},

[SPECIES_OINKOLOGNE_MALE] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(OinkologneMale, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_OinkologneMale),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_OinkologneMale),
},

[SPECIES_OINKOLOGNE_FEMALE] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(OinkologneFemale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_OinkologneFemale),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_OinkologneFemale),
},

[SPECIES_TAROUNTULA] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Tarountula, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tarountula),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tarountula),
},

[SPECIES_SPIDOPS] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Spidops, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Spidops),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Spidops),
},

[SPECIES_NYMBLE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Nymble, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nymble),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nymble),
},

[SPECIES_LOKIX] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Lokix, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lokix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lokix),
},

[SPECIES_PAWMI] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Pawmi, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pawmi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pawmi),
},

[SPECIES_PAWMO] =
    {
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Pawmo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pawmo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pawmo),
},

[SPECIES_PAWMOT] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Pawmot, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pawmot),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pawmot),
},

[SPECIES_TANDEMAUS] =
    {
      FRONT_COORD(0x88, 15),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(Tandemaus, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tandemaus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tandemaus),
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
      .cryData = CRY_INFO(Cry_MausholdFamilyOfThree),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MausholdFamilyOfThree),
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
      .cryData = CRY_INFO(Cry_MausholdFamilyOfFour),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MausholdFamilyOfFour),
},

[SPECIES_FIDOUGH] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(Fidough, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fidough),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fidough),
},

[SPECIES_DACHSBUN] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Dachsbun, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dachsbun),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dachsbun),
},

[SPECIES_SMOLIV] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Smoliv, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Smoliv),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Smoliv),
},

[SPECIES_DOLLIV] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Dolliv, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dolliv),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dolliv),
},

[SPECIES_ARBOLIVA] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Arboliva, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arboliva),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arboliva),
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
      .cryData = CRY_INFO(Cry_Squawkabilly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Squawkabilly),
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
      .cryData = CRY_INFO(Cry_Squawkabilly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Squawkabilly),
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
      .cryData = CRY_INFO(Cry_Squawkabilly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Squawkabilly),
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
      .cryData = CRY_INFO(Cry_Squawkabilly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Squawkabilly),
},

[SPECIES_NACLI] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Nacli, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Nacli),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Nacli),
},

[SPECIES_NACLSTACK] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Naclstack, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Naclstack),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Naclstack),
},

[SPECIES_GARGANACL] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Garganacl, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Garganacl),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Garganacl),
},

[SPECIES_CHARCADET] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(Charcadet, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Charcadet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Charcadet),
},//vsonic

[SPECIES_ARMAROUGE] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Armarouge, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Armarouge),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Armarouge),
},

[SPECIES_CERULEDGE] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Ceruledge, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ceruledge),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ceruledge),
},

[SPECIES_TADBULB] =
    {
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Tadbulb, 0),
      .enemyMonElevation = 12,
      .cryData = CRY_INFO(Cry_Tadbulb),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tadbulb),
},

[SPECIES_BELLIBOLT] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Bellibolt, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bellibolt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bellibolt),
},

[SPECIES_WATTREL] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Wattrel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wattrel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wattrel),
},

[SPECIES_KILOWATTREL] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Kilowattrel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kilowattrel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kilowattrel),
},

[SPECIES_MASCHIFF] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Maschiff, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Maschiff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Maschiff),
},

[SPECIES_MABOSSTIFF] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Mabosstiff, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mabosstiff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mabosstiff),
},

[SPECIES_SHROODLE] =
    {
      FRONT_COORD(0x88, 17),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(Shroodle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shroodle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shroodle),
},

[SPECIES_GRAFAIAI] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(Grafaiai, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grafaiai),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grafaiai),
},

[SPECIES_BRAMBLIN] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Bramblin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Bramblin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bramblin),
},

[SPECIES_BRAMBLEGHAST] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Brambleghast, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Brambleghast),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Brambleghast),
},

[SPECIES_TOEDSCOOL] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Toedscool, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Toedscool),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Toedscool),
},

[SPECIES_TOEDSCRUEL] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Toedscruel, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Toedscruel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Toedscruel),
},

[SPECIES_KLAWF] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 20),
      PIC_DATA_ICON_INDEX(Klawf, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Klawf),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Klawf),
},

[SPECIES_CAPSAKID] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(Capsakid, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Capsakid),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Capsakid),
},

[SPECIES_SCOVILLAIN] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(Scovillain, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Scovillain),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Scovillain),
},

[SPECIES_RELLOR] =
    {
      FRONT_COORD(0x88, 17),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Rellor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rellor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rellor),
},

[SPECIES_RABSCA] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Rabsca, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rabsca),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rabsca),
},

[SPECIES_FLITTLE] =
    {
      FRONT_COORD(0x88, 12),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Flittle, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Flittle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flittle),
},

[SPECIES_ESPATHRA] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Espathra, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Espathra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Espathra),
},

[SPECIES_TINKATINK] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Tinkatink, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tinkatink),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tinkatink),
},

[SPECIES_TINKATUFF] =
    {
      FRONT_COORD(0x88, 9),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Tinkatuff, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tinkatuff),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tinkatuff),
},

[SPECIES_TINKATON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Tinkaton, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tinkaton),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tinkaton),
},

[SPECIES_WIGLETT] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Wiglett, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wiglett),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wiglett),
},

[SPECIES_WUGTRIO] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Wugtrio, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wugtrio),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wugtrio),
},

[SPECIES_BOMBIRDIER] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Bombirdier, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Bombirdier),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Bombirdier),
},

[SPECIES_FINIZEN] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(Finizen, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Finizen),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Finizen),
},

[SPECIES_PALAFIN_ZERO] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(PalafinZero, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_PalafinZero),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_PalafinZero),
},

[SPECIES_PALAFIN_HERO] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(PalafinHero, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_PalafinHero),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_PalafinHero),
},

[SPECIES_VAROOM] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Varoom, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Varoom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Varoom),
},

[SPECIES_REVAVROOM] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(Revavroom, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Revavroom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Revavroom),
},

[SPECIES_CYCLIZAR] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(Cyclizar, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cyclizar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cyclizar),
},

[SPECIES_ORTHWORM] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Orthworm, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Orthworm),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Orthworm),
},

[SPECIES_GLIMMET] =
    {
      FRONT_COORD(0x88, 16),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Glimmet, 0),
      .enemyMonElevation = 11,
      .cryData = CRY_INFO(Cry_Glimmet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Glimmet),
},

[SPECIES_GLIMMORA] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Glimmora, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_Glimmora),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Glimmora),
},

[SPECIES_GREAVARD] =
    {
      FRONT_COORD(0x88, 6),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Greavard, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Greavard),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Greavard),
},

[SPECIES_HOUNDSTONE] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Houndstone, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Houndstone),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Houndstone),
},

[SPECIES_FLAMIGO] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(Flamigo, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Flamigo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flamigo),
},

[SPECIES_CETODDLE] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(Cetoddle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cetoddle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cetoddle),
},

[SPECIES_CETITAN] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Cetitan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cetitan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cetitan),
},

[SPECIES_VELUZA] =
    {
      FRONT_COORD(0x88, 11),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(Veluza, 1),
      .enemyMonElevation = 5,
      .cryData = CRY_INFO(Cry_Veluza),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Veluza),
},

[SPECIES_DONDOZO] =
    {
      FRONT_COORD(0x88, 4),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Dondozo, 0),
      .enemyMonElevation = 1,
      .cryData = CRY_INFO(Cry_Dondozo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dondozo),
},

[SPECIES_TATSUGIRI_CURLY] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(TatsugiriCurly, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TatsugiriCurly),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TatsugiriCurly),
},

[SPECIES_TATSUGIRI_DROOPY] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(TatsugiriDroopy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TatsugiriDroopy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TatsugiriDroopy),
},

[SPECIES_TATSUGIRI_STRETCHY] =
    {
      FRONT_COORD(0x88, 14),
      BACK_COORD(0x88, 17),
      PIC_DATA_ICON_INDEX(TatsugiriStretchy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TatsugiriStretchy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TatsugiriStretchy),
},
[SPECIES_ANNIHILAPE] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Annihilape, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Annihilape),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Annihilape),
},
    

[SPECIES_CLODSIRE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 15),
      PIC_DATA_ICON_INDEX(Clodsire, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Clodsire),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Clodsire),
},

[SPECIES_FARIGIRAF] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Farigiraf, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Farigiraf),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Farigiraf),
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
      .cryData = CRY_INFO(Cry_Dudunsparce),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dudunsparce),
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
      .cryData = CRY_INFO(Cry_Dudunsparce),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dudunsparce),
},

[SPECIES_KINGAMBIT] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Kingambit, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Kingambit),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Kingambit),
},
[SPECIES_GREAT_TUSK] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(GreatTusk, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GreatTusk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GreatTusk),
},

[SPECIES_SCREAM_TAIL] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(ScreamTail, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ScreamTail),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ScreamTail),
},

[SPECIES_BRUTE_BONNET] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(BruteBonnet, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_BruteBonnet),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_BruteBonnet),
},

[SPECIES_FLUTTER_MANE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(FlutterMane, 2),
      .enemyMonElevation = 18,
      .cryData = CRY_INFO(Cry_FlutterMane),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_FlutterMane),
},

[SPECIES_SLITHER_WING] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(SlitherWing, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SlitherWing),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SlitherWing),
},

[SPECIES_SANDY_SHOCKS] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(SandyShocks, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SandyShocks),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SandyShocks),
},

[SPECIES_IRON_TREADS] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(IronTreads, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronTreads),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronTreads),
},

[SPECIES_IRON_BUNDLE] =
    {
      FRONT_COORD(0x88, 8),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(IronBundle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronBundle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronBundle),
},

[SPECIES_IRON_HANDS] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(IronHands, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronHands),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronHands),
},

[SPECIES_IRON_JUGULIS] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 11), //back sprite not great
      PIC_DATA_ICON_INDEX(IronJugulis, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_IronJugulis),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronJugulis),
},//vsonic

[SPECIES_IRON_MOTH] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(IronMoth, 3),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_IronMoth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronMoth),
},

[SPECIES_IRON_THORNS] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(IronThorns,1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronThorns),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronThorns),
},

[SPECIES_FRIGIBAX] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 11),
      PIC_DATA_ICON_INDEX(Frigibax, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Frigibax),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Frigibax),
},

[SPECIES_ARCTIBAX] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(Arctibax, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arctibax),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arctibax),
},

[SPECIES_BAXCALIBUR] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Baxcalibur, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Baxcalibur),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Baxcalibur),
},

[SPECIES_GIMMIGHOUL_CHEST] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 16),
      PIC_DATA_ICON_INDEX(GimmighoulChest, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gimmighoul),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gimmighoul),
},//will make money based evolution I guess 70k poke, kinda griny but make gimmighoul better to use pre evo
    //and counter is you can evolve it at any level - brought down because u16 param

[SPECIES_GIMMIGHOUL_ROAMING] =
    {
      FRONT_COORD(0x88, 11),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(GimmighoulRoaming, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gimmighoul),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gimmighoul),
}, //not gonna use this form

[SPECIES_GHOLDENGO] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(Gholdengo, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gholdengo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gholdengo),
},

[SPECIES_WO_CHIEN] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(WoChien, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_WoChien),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_WoChien),
},

[SPECIES_CHIEN_PAO] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(ChienPao, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ChienPao),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ChienPao),
},

[SPECIES_TING_LU] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(TingLu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TingLu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TingLu),
},

[SPECIES_CHI_YU] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 14),
      PIC_DATA_ICON_INDEX(ChiYu, 0),
      .enemyMonElevation = 15,
      .cryData = CRY_INFO(Cry_ChiYu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ChiYu),
},

[SPECIES_ROARING_MOON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 10),
      PIC_DATA_ICON_INDEX(RoaringMoon, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_RoaringMoon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_RoaringMoon),
},

[SPECIES_IRON_VALIANT] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(IronValiant, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronValiant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronValiant),
},

[SPECIES_KORAIDON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Koraidon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Koraidon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Koraidon),
},

[SPECIES_MIRAIDON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Miraidon, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Miraidon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Miraidon),
},

[SPECIES_TAUROS_PALDEAN_COMBAT_BREED] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(TaurosPaldeanCombatBreed, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tauros),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tauros),
},

[SPECIES_TAUROS_PALDEAN_BLAZE_BREED] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(TaurosPaldeanBlazeBreed, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tauros),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tauros),
},

[SPECIES_TAUROS_PALDEAN_AQUA_BREED] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(TaurosPaldeanAquaBreed, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Tauros),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Tauros),
},

[SPECIES_WOOPER_PALDEAN] =
    {
      FRONT_COORD(0x88, 16),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(WooperPaldean, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wooper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wooper),
},

[SPECIES_WALKING_WAKE] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(WalkingWake, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_WalkingWake),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_WalkingWake),
},

[SPECIES_IRON_LEAVES] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 8),
      PIC_DATA_ICON_INDEX(IronLeaves, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronLeaves),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronLeaves),
},
[SPECIES_DIPPLIN] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(Dipplin, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dipplin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dipplin),
},

[SPECIES_POLTCHAGEIST_COUNTERFEIT] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Poltchageist, 1),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Poltchageist),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poltchageist),
},//vsonic

[SPECIES_POLTCHAGEIST_ARTISAN] =
    {
      FRONT_COORD(0x88, 7),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Poltchageist, 1),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Poltchageist),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Poltchageist),
},//vsonic

[SPECIES_SINISTCHA_UNREMARKABLE] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 13), //sprites came out bad? especially back
      PIC_DATA_ICON_INDEX(Sinistcha, 1), //low res
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Sinistcha),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sinistcha),
},
[SPECIES_SINISTCHA_MASTERPIECE] =
    {
      FRONT_COORD(0x88, 10),
      BACK_COORD(0x88, 13),
      PIC_DATA_ICON_INDEX(Sinistcha, 1),
      .enemyMonElevation = 10,
      .cryData = CRY_INFO(Cry_Sinistcha),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sinistcha),
},

[SPECIES_OKIDOGI] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 13), //back looks better w/o tail, check model may remove
      PIC_DATA_ICON_INDEX(Okidogi, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Okidogi),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Okidogi),
},

[SPECIES_MUNKIDORI] =
    {
      FRONT_COORD(0x88, 5),
      BACK_COORD(0x88, 3), //maybe 2?
      PIC_DATA_ICON_INDEX(Munkidori, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Munkidori),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Munkidori),
},

[SPECIES_FEZANDIPITI] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Fezandipiti, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Fezandipiti),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Fezandipiti),
},

[SPECIES_OGERPON_TEAL_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponTealMask, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_OGERPON_WELLSPRING_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponWellspringMask, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_OGERPON_HEARTHFLAME_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponHearthflameMask, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_OGERPON_CORNERSTONE_MASK] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponCornerstoneMask, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},//need grahpics for tera forms
[SPECIES_OGERPON_TEAL_MASK_TERA] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponTealMask, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_OGERPON_WELLSPRING_MASK_TERA] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponWellspringMask, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_OGERPON_HEARTHFLAME_MASK_TERA] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponHearthflameMask, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_OGERPON_CORNERSTONE_MASK_TERA] = 
    {  
      FRONT_COORD(0x88,0),
      BACK_COORD(0x88,16),
      PIC_DATA_ICON_INDEX(OgerponCornerstoneMask, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ogerpon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ogerpon),
},
[SPECIES_URSALUNA_BLOODMOON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(UrsalunaBloodmoon, 2), //icon is off, think source is problem
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ursaluna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ursaluna),
},//vsonic

[SPECIES_ARCHALUDON] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(Archaludon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Archaludon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Archaludon),
},

//missing archaludon and hydrapple flapple evo
[SPECIES_HYDRAPPLE] =
    {
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Hydrapple, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Hydrapple),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Hydrapple),
},



[SPECIES_GOUGING_FIRE] =
    {
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x88, 6),
      PIC_DATA_ICON_INDEX(GougingFire, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GougingFire),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GougingFire),
},

[SPECIES_RAGING_BOLT] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(RagingBolt, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_RagingBolt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_RagingBolt),
},

[SPECIES_IRON_BOULDER] =
    {
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x88, 12),
      PIC_DATA_ICON_INDEX(IronBoulder, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronBoulder),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronBoulder),
},

[SPECIES_IRON_CROWN] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 2),
      PIC_DATA_ICON_INDEX(IronCrown, 3),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IronCrown),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IronCrown),
},

[SPECIES_TERAPAGOS_NORMAL] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(Terapagos, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Terapagos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Terapagos),
},

[SPECIES_TERAPAGOS_TERASTAL] =
    {
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(TerapagosTerastal, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Terapagos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Terapagos),
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
      .cryData = CRY_INFO(Cry_Terapagos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Terapagos),
},

[SPECIES_PECHARUNT] =
    {
      FRONT_COORD(0x88, 13),
      BACK_COORD(0x88, 5),
      PIC_DATA_ICON_INDEX(Pecharunt, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pecharunt),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pecharunt),
},
[SPECIES_VENUSAUR_MEGA] = 
    {  
      FRONT_COORD(0, 6),
      BACK_COORD(0, 10),
      PIC_DATA_ICON_INDEX(VenusaurMega, 4),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_VenusaurMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_VenusaurMega),
}, //VenusaurMega,
[SPECIES_CHARIZARD_MEGA_X] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 2),
      PIC_DATA_ICON_INDEX(CharizardMegaX, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_CharizardMegaX),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_CharizardMegaX),
}, //CharizardMegaX,
[SPECIES_CHARIZARD_MEGA_Y] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(CharizardMegaY, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_CharizardMegaY),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_CharizardMegaY),
}, //CharizardMegaY,
[SPECIES_BLASTOISE_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(BlastoiseMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_BlastoiseMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_BlastoiseMega),
}, //BlastoiseMega,
[SPECIES_BEEDRILL_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 5),
      PIC_DATA_ICON_INDEX(BeedrillMega, 2),
      .enemyMonElevation = 5,
      .cryData = CRY_INFO(Cry_BeedrillMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_BeedrillMega),
}, //BeedrillMega,
[SPECIES_PIDGEOT_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 7),
      PIC_DATA_ICON_INDEX(PidgeotMega, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_PidgeotMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_PidgeotMega),
}, //PidgeotMega,
[SPECIES_ALAKAZAM_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(AlakazamMega, 2),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_AlakazamMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AlakazamMega),
}, //AlakazamMega,
[SPECIES_SLOWBRO_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 9),
      PIC_DATA_ICON_INDEX(SlowbroMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slowbro),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slowbro),
}, //SlowbroMega,
[SPECIES_GENGAR_MEGA] = 
    {  
      FRONT_COORD(0, 8),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(GengarMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GengarMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GengarMega),
}, //GengarMega,
[SPECIES_KANGASKHAN_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(KangaskhanMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_KangaskhanMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_KangaskhanMega),
}, //KangaskhanMega,
[SPECIES_PINSIR_MEGA] = 
    {  
      FRONT_COORD(0, 4),
      BACK_COORD(0, 7),
      PIC_DATA_ICON_INDEX(PinsirMega, 2),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_PinsirMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_PinsirMega),
}, //PinsirMega,
[SPECIES_GYARADOS_MEGA] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(GyaradosMega, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_GyaradosMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GyaradosMega),
}, //GyaradosMega,
[SPECIES_AERODACTYL_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 8),
      PIC_DATA_ICON_INDEX(AerodactylMega, 2),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_AerodactylMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AerodactylMega),
}, //AerodactylMega,
[SPECIES_MEWTWO_MEGA_X] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(MewtwoMegaX, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MewtwoMegaX),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MewtwoMegaX),
}, //MewtwoMegaX,
[SPECIES_MEWTWO_MEGA_Y] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 2),
      PIC_DATA_ICON_INDEX(MewtwoMegaY, 2),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_MewtwoMegaY),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MewtwoMegaY),
}, //MewtwoMegaY,
[SPECIES_AMPHAROS_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(AmpharosMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_AmpharosMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AmpharosMega),
}, //AmpharosMega,
[SPECIES_STEELIX_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(SteelixMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SteelixMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SteelixMega),
}, //SteelixMega,
[SPECIES_SCIZOR_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 4),
      PIC_DATA_ICON_INDEX(ScizorMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ScizorMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ScizorMega),
}, //ScizorMega,
[SPECIES_HERACROSS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(HeracrossMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_HeracrossMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_HeracrossMega),
}, //HeracrossMega,
[SPECIES_HOUNDOOM_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(HoundoomMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_HoundoomMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_HoundoomMega),
}, //HoundoomMega,
[SPECIES_TYRANITAR_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(TyranitarMega, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TyranitarMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TyranitarMega),
}, //TyranitarMega,
[SPECIES_SCEPTILE_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(SceptileMega, 4),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SceptileMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SceptileMega),
}, //SceptileMega,
[SPECIES_BLAZIKEN_MEGA] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(BlazikenMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_BlazikenMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_BlazikenMega),
}, //BlazikenMega,
[SPECIES_SWAMPERT_MEGA] = 
    {  
      FRONT_COORD(0, 4),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(SwampertMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SwampertMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SwampertMega),
}, //SwampertMega,
[SPECIES_GARDEVOIR_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(GardevoirMega, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GardevoirMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GardevoirMega),
}, //GardevoirMega,
[SPECIES_SABLEYE_MEGA] = 
    {  
      FRONT_COORD(0, 7),
      BACK_COORD(0, 13),
      PIC_DATA_ICON_INDEX(SableyeMega, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SableyeMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SableyeMega),
}, //SableyeMega,
[SPECIES_MAWILE_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(MawileMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MawileMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MawileMega),
}, //MawileMega,
[SPECIES_AGGRON_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 7),
      PIC_DATA_ICON_INDEX(AggronMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_AggronMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AggronMega),
}, //AggronMega,
[SPECIES_MEDICHAM_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 2),
      PIC_DATA_ICON_INDEX(MedichamMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MedichamMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MedichamMega),
}, //MedichamMega,
[SPECIES_MANECTRIC_MEGA] = 
    {  
      FRONT_COORD(0, 3),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(ManectricMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ManectricMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ManectricMega),
}, //ManectricMega,
[SPECIES_SHARPEDO_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(SharpedoMega, 0),
      .enemyMonElevation = 1,
      .cryData = CRY_INFO(Cry_SharpedoMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SharpedoMega),
}, //SharpedoMega,
[SPECIES_CAMERUPT_MEGA] = 
    {  
      FRONT_COORD(0, 6),
      BACK_COORD(0, 9),
      PIC_DATA_ICON_INDEX(CameruptMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_CameruptMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_CameruptMega),
}, //CameruptMega,
[SPECIES_ALTARIA_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 10),
      PIC_DATA_ICON_INDEX(AltariaMega, 0),
      .enemyMonElevation = 6,
      .cryData = CRY_INFO(Cry_AltariaMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AltariaMega),
}, //AltariaMega,
[SPECIES_BANETTE_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(BanetteMega, 0),
      .enemyMonElevation = 5,
      .cryData = CRY_INFO(Cry_BanetteMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_BanetteMega),
}, //BanetteMega,
[SPECIES_ABSOL_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(AbsolMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_AbsolMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AbsolMega),
}, //AbsolMega,
[SPECIES_GLALIE_MEGA] = 
    {  
      FRONT_COORD(0, 4),
      BACK_COORD(0, 10),
      PIC_DATA_ICON_INDEX(GlalieMega, 0),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_GlalieMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GlalieMega),
}, //GlalieMega,
[SPECIES_SALAMENCE_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(SalamenceMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SalamenceMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SalamenceMega),
}, //SalamenceMega,
[SPECIES_METAGROSS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6), //back sprite bad check for updated versionin EE
      PIC_DATA_ICON_INDEX(MetagrossMega, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_MetagrossMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MetagrossMega),
}, //MetagrossMega, //vsonic
[SPECIES_LATIAS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(LatiasMega, 2),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_LatiasMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LatiasMega),
}, //LatiasMega,
[SPECIES_LATIOS_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(LatiosMega, 2),
      .enemyMonElevation = 8,
      .cryData = CRY_INFO(Cry_LatiosMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LatiosMega),
}, //LatiosMega,
[SPECIES_LOPUNNY_MEGA] = 
    {  
      FRONT_COORD(0, 2),
      BACK_COORD(0, 4),
      PIC_DATA_ICON_INDEX(LopunnyMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_LopunnyMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LopunnyMega),
}, //LopunnyMega,
[SPECIES_GARCHOMP_MEGA] = 
    {  
      FRONT_COORD(0, 3),
      BACK_COORD(0, 4),
      PIC_DATA_ICON_INDEX(GarchompMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GarchompMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GarchompMega),
}, //GarchompMega,
[SPECIES_LUCARIO_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(LucarioMega, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_LucarioMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LucarioMega),
}, //LucarioMega,
[SPECIES_ABOMASNOW_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(AbomasnowMega, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_AbomasnowMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AbomasnowMega),
}, //AbomasnowMega,
[SPECIES_GALLADE_MEGA] = 
    {  
      FRONT_COORD(0, 1),
      BACK_COORD(0, 3),
      PIC_DATA_ICON_INDEX(GalladeMega, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GalladeMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GalladeMega),
}, //GalladeMega,
[SPECIES_AUDINO_MEGA] = 
    {  
      FRONT_COORD(0, 5),
      BACK_COORD(0, 0),
      PIC_DATA_ICON_INDEX(AudinoMega, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_AudinoMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_AudinoMega),
}, //AudinoMega,
[SPECIES_DIANCIE_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 6),
      PIC_DATA_ICON_INDEX(DiancieMega, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_DiancieMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_DiancieMega),
}, //DiancieMega,
[SPECIES_RAYQUAZA_MEGA] = 
    {  
      FRONT_COORD(0, 0),
      BACK_COORD(0, 1),
      PIC_DATA_ICON_INDEX(RayquazaMega, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_RayquazaMega),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_RayquazaMega),
}, //RayquazaMega,
[SPECIES_KYOGRE_PRIMAL] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x84, 18),
      PIC_DATA_ICON_INDEX(KyogrePrimal, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_KyogrePrimal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_KyogrePrimal),
}, //KyogrePrimal,
[SPECIES_GROUDON_PRIMAL] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(GroudonPrimal, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_GroudonPrimal),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GroudonPrimal),
}, //GroudonPrimal,
[SPECIES_RATTATA_ALOLAN] = 
    {  
      FRONT_COORD(0x44, 13),
      BACK_COORD(0x65, 7),
      PIC_DATA_ICON_INDEX(RattataAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rattata),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rattata),
}, //RattataAlolan,
[SPECIES_RATICATE_ALOLAN] = 
    {  
      FRONT_COORD(0x66, 6),
      BACK_COORD(0x75, 10),
      PIC_DATA_ICON_INDEX(RaticateAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Raticate),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Raticate),
}, //RaticateAlolan,
[SPECIES_RAICHU_ALOLAN] = 
    {  
      FRONT_COORD(0x67, 3),
      BACK_COORD(0x66, 6),
      PIC_DATA_ICON_INDEX(RaichuAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Raichu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Raichu),
}, //RaichuAlolan,
[SPECIES_SANDSHREW_ALOLAN] = 
    {  
      FRONT_COORD(0x55, 11),
      BACK_COORD(0x65, 13),
      PIC_DATA_ICON_INDEX(SandshrewAlolan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandshrew),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandshrew),
}, //SandshrewAlolan,
[SPECIES_SANDSLASH_ALOLAN] = 
    {  
      FRONT_COORD(0x76, 6),
      BACK_COORD(0x86, 18),//11, 6, 18
      PIC_DATA_ICON_INDEX(SandslashAlolan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sandslash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sandslash),
}, //SandslashAlolan,
[SPECIES_VULPIX_ALOLAN] = 
    {  
      FRONT_COORD(0x65, 11),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(VulpixAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vulpix),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vulpix),
}, //VulpixAlolan,
[SPECIES_NINETALES_ALOLAN] = 
    {  
      FRONT_COORD(0x88, 3),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(NinetalesAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ninetales),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ninetales),
}, //NinetalesAlolan,
[SPECIES_DIGLETT_ALOLAN] = 
    {  
      FRONT_COORD(0x54, 17),
      BACK_COORD(0x54, 14),
      PIC_DATA_ICON_INDEX(DiglettAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Diglett),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Diglett),
}, //DiglettAlolan,
[SPECIES_DUGTRIO_ALOLAN] = 
    {  
      FRONT_COORD(0x75, 11),
      BACK_COORD(0x66, 17),
      PIC_DATA_ICON_INDEX(DugtrioAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Dugtrio),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Dugtrio),
}, //DugtrioAlolan,
[SPECIES_MEOWTH_ALOLAN] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x65, 7),
      PIC_DATA_ICON_INDEX(MeowthAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meowth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meowth),
}, //MeowthAlolan,
[SPECIES_PERSIAN_ALOLAN] = 
    {  
      FRONT_COORD(0x77, 4),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(PersianAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Persian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Persian),
}, //PersianAlolan,
[SPECIES_GEODUDE_ALOLAN] = 
    {  
      FRONT_COORD(0x54, 10),
      BACK_COORD(0x66, 13),
      PIC_DATA_ICON_INDEX(GeodudeAlolan, 2),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Geodude),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Geodude),
}, //GeodudeAlolan,
[SPECIES_GRAVELER_ALOLAN] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x75, 10),
      PIC_DATA_ICON_INDEX(GravelerAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Graveler),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Graveler),
}, //GravelerAlolan,
[SPECIES_GOLEM_ALOLAN] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x84, 13),
      PIC_DATA_ICON_INDEX(GolemAlolan, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Golem),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Golem),
}, //GolemAlolan,
[SPECIES_GRIMER_ALOLAN] = 
    {  
      FRONT_COORD(0x65, 9),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(GrimerAlolan, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Grimer),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Grimer),
}, //GrimerAlolan,
[SPECIES_MUK_ALOLAN] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(MukAlolan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Muk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Muk),
}, //MukAlolan,
[SPECIES_EXEGGUTOR_ALOLAN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(ExeggutorAlolan, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Exeggutor),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Exeggutor),
}, //ExeggutorAlolan,
[SPECIES_MAROWAK_ALOLAN] = 
    {  
      FRONT_COORD(0x76, 8),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(MarowakAlolan, 4),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Marowak),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Marowak),
}, //MarowakAlolan,
[SPECIES_MEOWTH_GALARIAN] = 
    {  
      FRONT_COORD(0x66, 9),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(MeowthGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meowth),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meowth),
}, //MeowthGalarian,
[SPECIES_PONYTA_GALARIAN] = 
    {  
      FRONT_COORD(0x87, 8),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PonytaGalarian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Ponyta),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Ponyta),
}, //PonytaGalarian,
[SPECIES_RAPIDASH_GALARIAN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(RapidashGalarian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rapidash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rapidash),
}, //RapidashGalarian,
[SPECIES_SLOWPOKE_GALARIAN] = 
    {  
      FRONT_COORD(0x74, 19),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(SlowpokeGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_SlowpokeGalarian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_SlowpokeGalarian),
}, //SlowpokeGalarian,
[SPECIES_SLOWBRO_GALARIAN] = 
    {  
      FRONT_COORD(0x87, 4),
      BACK_COORD(0x86, 9),
      PIC_DATA_ICON_INDEX(SlowbroGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slowbro),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slowbro),
}, //SlowbroGalarian,
[SPECIES_FARFETCHD_GALARIAN] = 
    {  
      FRONT_COORD(0x86, 9),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(FarfetchdGalarian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Farfetchd),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Farfetchd),
}, //FarfetchdGalarian,
[SPECIES_WEEZING_GALARIAN] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(WeezingGalarian, 1),
      .enemyMonElevation = 3,
      .cryData = CRY_INFO(Cry_Weezing),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Weezing),
}, //WeezingGalarian,
[SPECIES_MR_MIME_GALARIAN] = 
    {  
      FRONT_COORD(0x77, 7),
      BACK_COORD(0x86, 8),
      PIC_DATA_ICON_INDEX(MrMimeGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MrMime),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MrMime),
}, //MrMimeGalarian,
[SPECIES_ARTICUNO_GALARIAN] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(ArticunoGalarian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Articuno),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Articuno),
}, //ArticunoGalarian,
[SPECIES_ZAPDOS_GALARIAN] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x76, 9),
      PIC_DATA_ICON_INDEX(ZapdosGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zapdos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zapdos),
}, //ZapdosGalarian,
[SPECIES_MOLTRES_GALARIAN] = 
    {  
      FRONT_COORD(0x88, 1),
      BACK_COORD(0x77, 5),
      PIC_DATA_ICON_INDEX(MoltresGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Moltres),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Moltres),
}, //MoltresGalarian,
[SPECIES_SLOWKING_GALARIAN] = 
    {  
      FRONT_COORD(0x68, 0),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(SlowkingGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Slowking),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Slowking),
}, //SlowkingGalarian,
[SPECIES_CORSOLA_GALARIAN] = 
    {  
      FRONT_COORD(0x66, 11),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(CorsolaGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Corsola),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Corsola),
}, //CorsolaGalarian,
[SPECIES_ZIGZAGOON_GALARIAN] = 
    {  
      FRONT_COORD(0x75, 13),
      BACK_COORD(0x76, 12),
      PIC_DATA_ICON_INDEX(ZigzagoonGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zigzagoon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zigzagoon),
}, //ZigzagoonGalarian,
[SPECIES_LINOONE_GALARIAN] = 
    {  
      FRONT_COORD(0x85, 13),
      BACK_COORD(0x85, 13),
      PIC_DATA_ICON_INDEX(LinooneGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Linoone),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Linoone),
}, //LinooneGalarian,
[SPECIES_DARUMAKA_GALARIAN] = 
    {  
      FRONT_COORD(0x55, 15),
      BACK_COORD(0x76, 11),
      PIC_DATA_ICON_INDEX(DarumakaGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Darumaka),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darumaka),
}, //DarumakaGalarian,
[SPECIES_DARMANITAN_GALARIAN] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(DarmanitanGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Darmanitan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darmanitan),
}, //DarmanitanGalarian,
[SPECIES_YAMASK_GALARIAN] = 
    {  
      FRONT_COORD(0x65, 13),
      BACK_COORD(0x55, 13),
      PIC_DATA_ICON_INDEX(YamaskGalarian, 2),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_Yamask),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Yamask),
}, //YamaskGalarian,
[SPECIES_STUNFISK_GALARIAN] = 
    {  
      FRONT_COORD(0x65, 14),
      BACK_COORD(0x83, 23),
      PIC_DATA_ICON_INDEX(StunfiskGalarian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Stunfisk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Stunfisk),
}, //StunfiskGalarian,
[SPECIES_GROWLITHE_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 6),
      BACK_COORD(0x76, 8),
      PIC_DATA_ICON_INDEX(GrowlitheHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Growlithe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Growlithe),
}, //GrowlitheHisuian,
[SPECIES_ARCANINE_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 2),
      BACK_COORD(0x87, 3),
      PIC_DATA_ICON_INDEX(ArcanineHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Arcanine),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arcanine),
}, //ArcanineHisuian,
[SPECIES_VOLTORB_HISUIAN] = 
    {  
      FRONT_COORD(0x65, 0),
      BACK_COORD(0x76, 10),
      PIC_DATA_ICON_INDEX(VoltorbHisuian, 0),
      .enemyMonElevation = 1, //sprite is oddly high see if can adjust?
      .cryData = CRY_INFO(Cry_Voltorb),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Voltorb),
}, //VoltorbHisuian,
[SPECIES_ELECTRODE_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(ElectrodeHisuian, 3),
      .enemyMonElevation = 1, //is just better contrast w shadow
      .cryData = CRY_INFO(Cry_Electrode),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Electrode),
}, //ElectrodeHisuian,
[SPECIES_TYPHLOSION_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 2),
      PIC_DATA_ICON_INDEX(TyphlosionHisuian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Typhlosion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Typhlosion),
}, //TyphlosionHisuian,
[SPECIES_QWILFISH_HISUIAN] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x55, 6),
      PIC_DATA_ICON_INDEX(QwilfishHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Qwilfish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Qwilfish),
}, //QwilfishHisuian,
[SPECIES_SNEASEL_HISUIAN] = 
    {  
      FRONT_COORD(0x65, 7),
      BACK_COORD(0x87, 3),
      PIC_DATA_ICON_INDEX(SneaselHisuian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sneasel),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sneasel),
}, //SneaselHisuian,
[SPECIES_SAMUROTT_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 0),
      BACK_COORD(0x87, 8),
      PIC_DATA_ICON_INDEX(SamurottHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Samurott),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Samurott),
}, //SamurottHisuian,
[SPECIES_LILLIGANT_HISUIAN] = 
    {  
      FRONT_COORD(0x65, 1),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(LilligantHisuian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Lilligant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Lilligant),
}, //LilligantHisuian,
[SPECIES_ZORUA_HISUIAN] = 
    {  
      FRONT_COORD(0x55, 2),
      BACK_COORD(0x55, 1),
      PIC_DATA_ICON_INDEX(ZoruaHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zorua),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zorua),
}, //ZoruaHisuian,
[SPECIES_ZOROARK_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 1),
      BACK_COORD(0x87, 0),
      PIC_DATA_ICON_INDEX(ZoroarkHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zoroark),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zoroark),
}, //ZoroarkHisuian,
[SPECIES_BRAVIARY_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(BraviaryHisuian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Braviary),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Braviary),
}, //BraviaryHisuian,
[SPECIES_SLIGGOO_HISUIAN] = 
    {  
      FRONT_COORD(0x55, 6),
      BACK_COORD(0x55, 1),
      PIC_DATA_ICON_INDEX(SliggooHisuian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sliggoo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sliggoo),
}, //SliggooHisuian,
[SPECIES_GOODRA_HISUIAN] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x87, 0),
      PIC_DATA_ICON_INDEX(GoodraHisuian, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Goodra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Goodra),
}, //GoodraHisuian,
[SPECIES_AVALUGG_HISUIAN] = 
    {  
      FRONT_COORD(0x85, 5),
      BACK_COORD(0x87, 16),
      PIC_DATA_ICON_INDEX(AvaluggHisuian, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Avalugg),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Avalugg),
}, //AvaluggHisuian,
[SPECIES_DECIDUEYE_HISUIAN] = 
    {  
      FRONT_COORD(0x77, 0),
      BACK_COORD(0x87, 0),
      PIC_DATA_ICON_INDEX(DecidueyeHisuian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Decidueye),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Decidueye),
}, //DecidueyeHisuian,
[SPECIES_PIKACHU_COSPLAY] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuCosplay, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuCosplay,
[SPECIES_PIKACHU_ROCK_STAR] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuRockStar, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuRockStar,
[SPECIES_PIKACHU_BELLE] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuBelle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuBelle,
[SPECIES_PIKACHU_POP_STAR] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuPopStar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuPopStar,
[SPECIES_PIKACHU_PH_D] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuPhD, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuPhD,
[SPECIES_PIKACHU_LIBRE] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuLibre, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuLibre,
[SPECIES_PIKACHU_ORIGINAL_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuOriginalCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuOriginalCap,
[SPECIES_PIKACHU_HOENN_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuHoennCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuHoennCap,
[SPECIES_PIKACHU_SINNOH_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuSinnohCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuSinnohCap,
[SPECIES_PIKACHU_UNOVA_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuUnovaCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuUnovaCap,
[SPECIES_PIKACHU_KALOS_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuKalosCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuKalosCap,
[SPECIES_PIKACHU_ALOLA_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuAlolaCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuAlolaCap,
[SPECIES_PIKACHU_PARTNER_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4), //vsonic palett off for this one
      PIC_DATA_ICON_INDEX(PikachuPartnerCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuPartnerCap,
[SPECIES_PIKACHU_WORLD_CAP] = 
    {  
      FRONT_COORD(0x67, 9),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(PikachuWorldCap, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pikachu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pikachu),
}, //PikachuWorldCap,
[SPECIES_PICHU_SPIKY_EARED] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(PichuSpikyEared, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pichu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pichu),
}, //PichuSpikyEared,
[SPECIES_CASTFORM_SUNNY] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x48, 0),
      PIC_DATA_ICON_INDEX(CastformSunny, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Castform),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Castform),
}, //CastformSunny,
[SPECIES_CASTFORM_RAINY] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x48, 0),
      PIC_DATA_ICON_INDEX(CastformRainy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Castform),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Castform),
}, //CastformRainy,
[SPECIES_CASTFORM_SNOWY] = 
    {  
      FRONT_COORD(0x34, 17),
      BACK_COORD(0x48, 0),
      PIC_DATA_ICON_INDEX(CastformSnowy, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Castform),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Castform),
}, //CastformSnowy,
[SPECIES_DEOXYS_ATTACK] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 2),
      PIC_DATA_ICON_INDEX(DeoxysAttack,0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Deoxys),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deoxys),
}, //DeoxysAttack,
[SPECIES_DEOXYS_DEFENSE] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 9),
      PIC_DATA_ICON_INDEX(DeoxysDefense,0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Deoxys),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deoxys),
}, //DeoxysDefense,
[SPECIES_DEOXYS_SPEED] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 1),
      PIC_DATA_ICON_INDEX(DeoxysSpeed,0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Deoxys),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deoxys),
}, //DeoxysSpeed,
[SPECIES_BURMY_SANDY_CLOAK] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x57, 6),
      PIC_DATA_ICON_INDEX(BurmySandyCloak, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Burmy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Burmy),
}, //BurmySandyCloak,
[SPECIES_BURMY_TRASH_CLOAK] = 
    {  
      FRONT_COORD(0x67, 13),
      BACK_COORD(0x57, 1),
      PIC_DATA_ICON_INDEX(BurmyTrashCloak, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Burmy),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Burmy),
}, //BurmyTrashCloak,
[SPECIES_WORMADAM_SANDY_CLOAK] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(WormadamSandyCloak, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wormadam),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wormadam),
}, //WormadamSandyCloak,
[SPECIES_WORMADAM_TRASH_CLOAK] = 
    {  
      FRONT_COORD(0x55, 10),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(WormadamTrashCloak, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Wormadam),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Wormadam),
}, //WormadamTrashCloak,
[SPECIES_CHERRIM_SUNSHINE] = 
    {  
      FRONT_COORD(0x55, 8),
      BACK_COORD(0x57, 9),
      PIC_DATA_ICON_INDEX(CherrimSunshine, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cherrim),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cherrim),
}, //CherrimSunshine,
[SPECIES_SHELLOS_EAST_SEA] = 
    {  
      FRONT_COORD(0x66, 13),
      BACK_COORD(0x57, 8),
      PIC_DATA_ICON_INDEX(ShellosEastSea, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Shellos),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Shellos),
}, //ShellosEastSea,
[SPECIES_GASTRODON_EAST_SEA] = 
    {  
      FRONT_COORD(0x65, 8),
      BACK_COORD(0x78, 3),
      PIC_DATA_ICON_INDEX(GastrodonEastSea, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Gastrodon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gastrodon),
}, //GastrodonEastSea,
[SPECIES_ROTOM_HEAT] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 12),
      PIC_DATA_ICON_INDEX(RotomHeat, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rotom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rotom),
}, //RotomHeat,
[SPECIES_ROTOM_WASH] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 11),
      PIC_DATA_ICON_INDEX(RotomWash, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rotom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rotom),
}, //RotomWash,
[SPECIES_ROTOM_FROST] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(RotomFrost, 5),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rotom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rotom),
}, //RotomFrost,
[SPECIES_ROTOM_FAN] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 8),
      PIC_DATA_ICON_INDEX(RotomFan, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rotom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rotom),
}, //RotomFan,
[SPECIES_ROTOM_MOW] = 
    {  
      FRONT_COORD(0x77, 11),
      BACK_COORD(0x77, 11),
      PIC_DATA_ICON_INDEX(RotomMow, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Rotom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Rotom),
}, //RotomMow,
[SPECIES_GIRATINA_ORIGIN] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x65, 5),
      PIC_DATA_ICON_INDEX(GiratinaOrigin, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_Giratina),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Giratina),
}, //GiratinaOrigin,
[SPECIES_SHAYMIN_SKY] = 
    {  
      FRONT_COORD(0x87, 7),
      BACK_COORD(0x65, 2),
      PIC_DATA_ICON_INDEX(ShayminSky, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ShayminSky),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ShayminSky),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
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
      .cryData = CRY_INFO(Cry_Arceus),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Arceus),
}, //Arceus,
[SPECIES_BASCULIN_BLUE_STRIPED] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 16),
      PIC_DATA_ICON_INDEX(BasculinBlueStriped, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Basculin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Basculin),
}, //BasculinBlueStriped,
[SPECIES_BASCULIN_WHITE_STRIPED] = 
    {  
      FRONT_COORD(0x45, 13),
      BACK_COORD(0x86, 16),
      PIC_DATA_ICON_INDEX(BasculinWhiteStriped, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Basculin),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Basculin),
}, //BasculinWhiteStriped,
[SPECIES_DARMANITAN_ZEN_MODE] = 
    {  
      FRONT_COORD(0x87, 9),
      BACK_COORD(0x66, 18),
      PIC_DATA_ICON_INDEX(DarmanitanZenMode, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Darmanitan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darmanitan),
}, //DarmanitanZenMode,
[SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(DarmanitanZenModeGalarian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Darmanitan),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Darmanitan),
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
      .cryData = CRY_INFO(Cry_Deerling),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deerling),
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
      .cryData = CRY_INFO(Cry_Deerling),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deerling),
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
      .cryData = CRY_INFO(Cry_Deerling),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Deerling),
}, //DeerlingWinter,
[SPECIES_SAWSBUCK_SUMMER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(SawsbuckSummer, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sawsbuck),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sawsbuck),
}, //SawsbuckSummer,
[SPECIES_SAWSBUCK_AUTUMN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(SawsbuckAutumn, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sawsbuck),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sawsbuck),
}, //SawsbuckAutumn,
[SPECIES_SAWSBUCK_WINTER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x68, 5),
      PIC_DATA_ICON_INDEX(SawsbuckWinter, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Sawsbuck),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sawsbuck),
}, //SawsbuckWinter,
[SPECIES_TORNADUS_THERIAN] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x66, 3),
      PIC_DATA_ICON_INDEX(TornadusTherian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_TornadusTherian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_TornadusTherian),
}, //TornadusTherian,
[SPECIES_THUNDURUS_THERIAN] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x66, 7),
      PIC_DATA_ICON_INDEX(ThundurusTherian, 0),
      .enemyMonElevation = 7,
      .cryData = CRY_INFO(Cry_ThundurusTherian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ThundurusTherian),
}, //ThundurusTherian,
[SPECIES_LANDORUS_THERIAN] = 
    {  
      FRONT_COORD(0x87, 2),
      BACK_COORD(0x66, 7),
      PIC_DATA_ICON_INDEX(LandorusTherian, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_LandorusTherian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LandorusTherian),
}, //LandorusTherian,
[SPECIES_ENAMORUS_THERIAN] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x68, 7),
      PIC_DATA_ICON_INDEX(EnamorusTherian, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_EnamorusTherian),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EnamorusTherian),
}, //EnamorusTherian,
[SPECIES_KYUREM_WHITE] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x66, 3),
      PIC_DATA_ICON_INDEX(KyuremWhite, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_KyuremWhite),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_KyuremWhite),
}, //KyuremWhite,
[SPECIES_KYUREM_BLACK] = 
    {  
      FRONT_COORD(0x87, 0),
      BACK_COORD(0x66, 3),
      PIC_DATA_ICON_INDEX(KyuremBlack, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_KyuremBlack),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_KyuremBlack),
}, //KyuremBlack,
[SPECIES_KELDEO_RESOLUTE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x78, 4),
      PIC_DATA_ICON_INDEX(KeldeoResolute, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Keldeo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Keldeo),
}, //KeldeoResolute,
[SPECIES_MELOETTA_PIROUETTE] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(MeloettaPirouette, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meloetta),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meloetta),
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
      .cryData = CRY_INFO(Cry_Genesect),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Genesect),
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
      .cryData = CRY_INFO(Cry_Genesect),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Genesect),
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
      .cryData = CRY_INFO(Cry_Genesect),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Genesect),
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
      .cryData = CRY_INFO(Cry_Genesect),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Genesect),
}, //Genesect,
[SPECIES_GRENINJA_ASH] = 
    {  
      FRONT_COORD(0x45, 7),
      BACK_COORD(0x86, 11),
      PIC_DATA_ICON_INDEX(GreninjaAsh, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Greninja),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Greninja),
}, //GreninjaAsh,
[SPECIES_VIVILLON_POLAR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonPolar, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonPolar,
[SPECIES_VIVILLON_TUNDRA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonTundra, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonTundra,
[SPECIES_VIVILLON_CONTINENTAL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonContinental, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonContinental,
[SPECIES_VIVILLON_GARDEN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonGarden, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonGarden,
[SPECIES_VIVILLON_ELEGANT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonElegant, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonElegant,
[SPECIES_VIVILLON_MEADOW] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonMeadow, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonMeadow,
[SPECIES_VIVILLON_MODERN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonModern, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonModern,
[SPECIES_VIVILLON_MARINE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonMarine, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonMarine,
[SPECIES_VIVILLON_ARCHIPELAGO] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonArchipelago, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonArchipelago,
[SPECIES_VIVILLON_HIGH_PLAINS] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonHighPlains, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonHighPlains,
[SPECIES_VIVILLON_SANDSTORM] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSandstorm, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonSandstorm,
[SPECIES_VIVILLON_RIVER] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonRiver, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonRiver,
[SPECIES_VIVILLON_MONSOON] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonMonsoon, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonMonsoon,
[SPECIES_VIVILLON_SAVANNA] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSavanna, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonSavanna,
[SPECIES_VIVILLON_SUN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonSun, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonSun,
[SPECIES_VIVILLON_OCEAN] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonOcean, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonOcean,
[SPECIES_VIVILLON_JUNGLE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonJungle, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonJungle,
[SPECIES_VIVILLON_FANCY] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonFancy, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonFancy,
[SPECIES_VIVILLON_POKE_BALL] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(VivillonPokeBall, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Vivillon),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Vivillon),
}, //VivillonPokeBall,
[SPECIES_UNFEZANT_FEMALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(UnfezantFemale, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Unfezant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Unfezant),
}, //Unfezant_Female
[SPECIES_PYROAR_FEMALE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88,3),
      PIC_DATA_ICON_INDEX(PyroarFemale, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Pyroar),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pyroar),
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
      .cryData = CRY_INFO(Cry_Flabebe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flabebe),
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
      .cryData = CRY_INFO(Cry_Flabebe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flabebe),
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
      .cryData = CRY_INFO(Cry_Flabebe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flabebe),
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
      .cryData = CRY_INFO(Cry_Flabebe),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Flabebe),
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
      .cryData = CRY_INFO(Cry_Floette),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floette),
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
      .cryData = CRY_INFO(Cry_Floette),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floette),
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
      .cryData = CRY_INFO(Cry_Floette),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floette),
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
      .cryData = CRY_INFO(Cry_Floette),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Floette),
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
      .cryData = CRY_INFO(Cry_FloetteEternalFlower),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_FloetteEternalFlower),
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
      .cryData = CRY_INFO(Cry_Florges),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Florges),
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
      .cryData = CRY_INFO(Cry_Florges),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Florges),
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
      .cryData = CRY_INFO(Cry_Florges),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Florges),
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
      .cryData = CRY_INFO(Cry_Florges),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Florges),
}, //FlorgesWhiteFlower,
[SPECIES_FURFROU_HEART_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouHeartTrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouHeartTrim,
[SPECIES_FURFROU_STAR_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouStarTrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouStarTrim,
[SPECIES_FURFROU_DIAMOND_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouDiamondTrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouDiamondTrim,
[SPECIES_FURFROU_DEBUTANTE_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouDebutanteTrim, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouDebutanteTrim,
[SPECIES_FURFROU_MATRON_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouMatronTrim, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouMatronTrim,
[SPECIES_FURFROU_DANDY_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouDandyTrim, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouDandyTrim,
[SPECIES_FURFROU_LA_REINE_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouLaReineTrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouLaReineTrim,
[SPECIES_FURFROU_KABUKI_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouKabukiTrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouKabukiTrim,
[SPECIES_FURFROU_PHARAOH_TRIM] = 
    {  
      FRONT_COORD(0x45, 3),
      BACK_COORD(0x78, 2),
      PIC_DATA_ICON_INDEX(FurfrouPharaohTrim, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Furfrou),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Furfrou),
}, //FurfrouPharaohTrim,
[SPECIES_MEOWSTIC_FEMALE] = 
    {  
      FRONT_COORD(0x45, 6),
      BACK_COORD(0x88, 9),
      PIC_DATA_ICON_INDEX(MeowsticFemale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Meowstic),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Meowstic),
}, //Meowstic_Female,
[SPECIES_AEGISLASH_BLADE] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x66, 9),
      PIC_DATA_ICON_INDEX(AegislashBlade, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Aegislash),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Aegislash),
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
      .cryData = CRY_INFO(Cry_Pumpkaboo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pumpkaboo),
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
      .cryData = CRY_INFO(Cry_Pumpkaboo),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Pumpkaboo),
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
      .cryData = CRY_INFO(Cry_PumpkabooSuper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_PumpkabooSuper),
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
      .cryData = CRY_INFO(Cry_Gourgeist),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gourgeist),
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
      .cryData = CRY_INFO(Cry_Gourgeist),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Gourgeist),
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
      .cryData = CRY_INFO(Cry_GourgeistSuper),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_GourgeistSuper),
}, //Gourgeist,
[SPECIES_XERNEAS_ACTIVE] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(XerneasActive, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Xerneas),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Xerneas),
}, //XerneasActive,
[SPECIES_ZYGARDE_50] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(Zygarde50, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zygarde50),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zygarde50),
}, //Zygarde,
[SPECIES_ZYGARDE_COMPLETE] = 
    {  
      FRONT_COORD(0x55, 0),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(ZygardeComplete, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ZygardeComplete),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ZygardeComplete),
}, //ZygardeComplete,
[SPECIES_HOOPA_UNBOUND] = 
    {  
      FRONT_COORD(0x87, 1),
      BACK_COORD(0x66, 4),
      PIC_DATA_ICON_INDEX(HoopaUnbound, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_HoopaUnbound),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_HoopaUnbound),
}, //HoopaUnbound,
[SPECIES_ORICORIO_POM_POM] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioPomPom, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_OricorioPomPom),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_OricorioPomPom),
}, //OricorioPomPom,
[SPECIES_ORICORIO_PAU] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioPau, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_OricorioPau),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_OricorioPau),
}, //OricorioPau,
[SPECIES_ORICORIO_SENSU] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 0),
      PIC_DATA_ICON_INDEX(OricorioSensu, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_OricorioSensu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_OricorioSensu),
}, //OricorioSensu,
[SPECIES_LYCANROC_MIDNIGHT] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(LycanrocMidnight, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_LycanrocMidnight),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LycanrocMidnight),
}, //LycanrocMidnight,
[SPECIES_LYCANROC_DUSK] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x77, 7),
      PIC_DATA_ICON_INDEX(LycanrocDusk, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_LycanrocDusk),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_LycanrocDusk),
}, //LycanrocDusk,
[SPECIES_WISHIWASHI_SCHOOL] = 
    {  
      FRONT_COORD(0x87, 3),
      BACK_COORD(0x66, 8),
      PIC_DATA_ICON_INDEX(WishiwashiSchool, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_WishiwashiSchool),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_WishiwashiSchool),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
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
      .cryData = CRY_INFO(Cry_Silvally),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Silvally),
}, //Silvally,
[SPECIES_MINIOR_METEOR_ORANGE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //Minior,
[SPECIES_MINIOR_METEOR_YELLOW] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //Minior,
[SPECIES_MINIOR_METEOR_GREEN] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //Minior,
[SPECIES_MINIOR_METEOR_BLUE] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //Minior,
[SPECIES_MINIOR_METEOR_INDIGO] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //Minior,
[SPECIES_MINIOR_METEOR_VIOLET] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x75, 14),
      PIC_DATA_ICON_INDEX(MiniorMeteor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
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
      .cryData = CRY_INFO(Cry_Minior),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Minior),
}, //MiniorCoreViolet,
[SPECIES_MIMIKYU_BUSTED] = 
    {  
      FRONT_COORD(0x45, 12),
      BACK_COORD(0x77, 15),
      PIC_DATA_ICON_INDEX(MimikyuBusted, 3),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Mimikyu),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Mimikyu),
}, //MimikyuBusted,
[SPECIES_NECROZMA_DUSK_MANE] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(NecrozmaDuskMane, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_NecrozmaDuskMane),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_NecrozmaDuskMane),
}, //NecrozmaDuskMane,
[SPECIES_NECROZMA_DAWN_WINGS] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(NecrozmaDawnWings, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_NecrozmaDawnWings),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_NecrozmaDawnWings),
}, //NecrozmaDawnWings,
[SPECIES_NECROZMA_ULTRA] = 
    {  
      FRONT_COORD(0x45, 2),
      BACK_COORD(0x88, 4),
      PIC_DATA_ICON_INDEX(NecrozmaUltra, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_NecrozmaUltra),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_NecrozmaUltra),
}, //NecrozmaUltra,
[SPECIES_MAGEARNA_ORIGINAL_COLOR] = 
    {  
      FRONT_COORD(0x45, 0),
      BACK_COORD(0x87, 4),
      PIC_DATA_ICON_INDEX(MagearnaOriginalColor, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Magearna),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Magearna),
}, //MagearnaOriginalColor,
[SPECIES_CRAMORANT_GULPING] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(CramorantGulping, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cramorant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cramorant),
}, //Cramorant_Gulping,
[SPECIES_CRAMORANT_GORGING] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 1),
      PIC_DATA_ICON_INDEX(CramorantGorging, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Cramorant),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Cramorant),
}, //Cramorant_Gorging,
[SPECIES_TOXTRICITY_LOW_KEY] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x68, 0),
      PIC_DATA_ICON_INDEX(ToxtricityLowKey, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ToxtricityLowKey),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ToxtricityLowKey),
}, //Toxtricity_Low_key,
[SPECIES_SINISTEA_ANTIQUE]  =
{
  FRONT_COORD(0x54, 17),
  BACK_COORD(0x64, 16),
  PIC_DATA_ICON_INDEX(Sinistea, 0),
  .enemyMonElevation = 0,
  .cryData = CRY_INFO(Cry_Sinistea),
  .cryData_Reverse = CRY_INFO_REVERSE(Cry_Sinistea),
},
[SPECIES_POLTEAGEIST_ANTIQUE]  =
{
  FRONT_COORD(0x66, 11),
  BACK_COORD(0x85, 13),
  PIC_DATA_ICON_INDEX(Polteageist, 0),
  .enemyMonElevation = 0,
  .cryData = CRY_INFO(Cry_Polteageist),
  .cryData_Reverse = CRY_INFO_REVERSE(Cry_Polteageist),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverVanillaCream),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RUBY_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverRubyCream),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverMatchaCream),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_MINT_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverMintCream),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_LEMON_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverLemonCream),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_SALTED_CREAM] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverSaltedCream),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverRubySwirl),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverCaramelSwirl),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

[SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(AlcremieClover),
      FRONT_COORD(0x57, 7),
      BACK_PIC(AlcremieClover),
      BACK_COORD(0x67, 9),
      PAL(AlcremieCloverRainbowSwirl),
      SHINYPAL(AlcremieClover),
      ICON(Alcremie, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
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
      .cryData = CRY_INFO(Cry_Alcremie),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Alcremie),
}, //AlcremieStrawberry,

    

[SPECIES_EISCUE_NOICE_FACE] = 
    {  
      FRONT_COORD(0x58, 0),
      BACK_COORD(0x58, 0),
      PIC_DATA_ICON_INDEX(EiscueNoiceFace, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_EiscueNoiceFace),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EiscueNoiceFace),
}, //Eiscue_noice_face,
[SPECIES_INDEEDEE_FEMALE] = 
    {  
      FRONT_COORD(0x56, 9),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(IndeedeeFemale, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_IndeedeeFemale),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_IndeedeeFemale),
}, //Indeedee_Female,
[SPECIES_MORPEKO_HANGRY] = 
    {  
      FRONT_COORD(0x45, 14),
      BACK_COORD(0x67, 8),
      PIC_DATA_ICON_INDEX(MorpekoHangry, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_MorpekoHangry),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_MorpekoHangry),
}, //Morpeko_Hangry,
[SPECIES_ZACIAN_CROWNED_SWORD] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 6),
      PIC_DATA_ICON_INDEX(ZacianCrownedSword, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ZacianCrownedSword),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ZacianCrownedSword),
}, //Zacian_Crowned_Sword,
[SPECIES_ZAMAZENTA_CROWNED_SHIELD] = 
    {  
      FRONT_COORD(0x78, 0),
      BACK_COORD(0x88, 3),
      PIC_DATA_ICON_INDEX(ZamazentaCrownedShield, 2),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_ZamazentaCrownedShield),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_ZamazentaCrownedShield),
}, //Zamazenta_Crowned_Shield,
[SPECIES_ETERNATUS_ETERNAMAX] = 
    {  
      FRONT_COORD(0x86, 4),
      BACK_COORD(0x85, 11),
      PIC_DATA_ICON_INDEX(EternatusEternamax, 0),
      .enemyMonElevation = 4,
      .cryData = CRY_INFO(Cry_EternatusEternamax),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_EternatusEternamax),
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
      .cryData = CRY_INFO(Cry_UrshifuRapidStrikeStyle),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_UrshifuRapidStrikeStyle),
}, //Urshifu_Rapid, //think last value needs no comma, nope doesn't matter but using comma is better in case you plan to add more
[SPECIES_ZARUDE_DADA] = 
    {  
      FRONT_COORD(0x88, 2),
      BACK_COORD(0x87, 5),
      PIC_DATA_ICON_INDEX(ZarudeDada, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Zarude),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Zarude),
}, //Zarude_Dada,
[SPECIES_CALYREX_ICE_RIDER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x88, 7),
      PIC_DATA_ICON_INDEX(CalyrexIceRider, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_CalyrexIceRider),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_CalyrexIceRider),
}, //Calyrex_Ice_Rider,
[SPECIES_CALYREX_SHADOW_RIDER] = 
    {  
      FRONT_COORD(0x88, 0),
      BACK_COORD(0x87, 7),
      PIC_DATA_ICON_INDEX(CalyrexShadowRider, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_CalyrexShadowRider),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_CalyrexShadowRider),
}, //Calyrex_Shadow_Rider,
[SPECIES_BASCULEGION_FEMALE] = 
    {  
      FRONT_COORD(0x68, 2),
      BACK_COORD(0x72, 1),
      PIC_DATA_ICON_INDEX(BasculegionFemale, 0),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Basculegion),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Basculegion),
}, //Basculegion_Female,
[SPECIES_FRILLISH_FEMALE] = 
    {  
      FRONT_COORD(0x45, 5),
      BACK_COORD(0x57, 7),
      PIC_DATA_ICON_INDEX(FrillishFemale, 1),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Frillish),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Frillish),
}, //Basculegion_Female,
[SPECIES_JELLICENT_FEMALE] = 
    {  
      FRONT_COORD(0x45, 4),
      BACK_COORD(0x86, 10),
      PIC_DATA_ICON_INDEX(JellicentFemale, 4),
      .enemyMonElevation = 0,
      .cryData = CRY_INFO(Cry_Jellicent),
      .cryData_Reverse = CRY_INFO_REVERSE(Cry_Jellicent),
}, //Basculegion_Female,
};
