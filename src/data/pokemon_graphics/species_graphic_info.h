
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


#define PALETTES(pal)                                       \
        .palette = gMonPalette_## pal,                      \
        .shinyPalette = gMonShinyPalette_## pal


#define ICON(sprite, palId)                                 \
        .iconSprite = gMonIcon_## sprite,                   \
        .iconPalIndex = palId

//tag equals species constant
//can put that in functinon rather than needing to put in table
//use get tag and have it just set to species
const struct SpeciesGraphicInfo gSpeciesGraphics[] =
{
[SPECIES_NONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //QuestionMark, 
[SPECIES_BULBASAUR] = 
    {  
      FRONT_PIC(Bulbasaur),
      FRONT_COORD(0x88,0),
      BACK_PIC(Bulbasaur),
      BACK_COORD(0x88,0),
      PALETTES(Bulbasaur),
      ICON(Bulbasaur,0),
      TAG(SPECIES_NONE),
    }, //Bulbasaur,
[SPECIES_IVYSAUR] = 
    {  
      FRONT_PIC(Ivysaur),
      FRONT_COORD(0x88,0),
      BACK_PIC(Ivysaur),
      BACK_COORD(0x88,0),
      PALETTES(Ivysaur),
      ICON(Ivysaur,0),
      TAG(SPECIES_NONE),
    }, //Ivysaur,
[SPECIES_VENUSAUR] = 
    {  
      FRONT_PIC(Venusaur),
      FRONT_COORD(0x88,0),
      BACK_PIC(Venusaur),
      BACK_COORD(0x88,0),
      PALETTES(Venusaur),
      ICON(Venusaur,0),
      TAG(SPECIES_NONE),
    }, //Venusaur,
[SPECIES_CHARMANDER] = 
    {  
      FRONT_PIC(Charmander),
      FRONT_COORD(0x88,0),
      BACK_PIC(Charmander),
      BACK_COORD(0x88,0),
      PALETTES(Charmander),
      ICON(Charmander,0),
      TAG(SPECIES_NONE),
    }, //Charmander,
[SPECIES_CHARMELEON] = 
    {  
      FRONT_PIC(Charmeleon),
      FRONT_COORD(0x88,0),
      BACK_PIC(Charmeleon),
      BACK_COORD(0x88,0),
      PALETTES(Charmeleon),
      ICON(Charmeleon,0),
      TAG(SPECIES_NONE),
    }, //Charmeleon,
[SPECIES_CHARIZARD] = 
    {  
      FRONT_PIC(Charizard),
      FRONT_COORD(0x88,0),
      BACK_PIC(Charizard),
      BACK_COORD(0x88,0),
      PALETTES(Charizard),
      ICON(Charizard,0),
      TAG(SPECIES_NONE),
    }, //Charizard,
[SPECIES_SQUIRTLE] = 
    {  
      FRONT_PIC(Squirtle),
      FRONT_COORD(0x88,0),
      BACK_PIC(Squirtle),
      BACK_COORD(0x88,0),
      PALETTES(Squirtle),
      ICON(Squirtle,0),
      TAG(SPECIES_NONE),
    }, //Squirtle,
[SPECIES_WARTORTLE] = 
    {  
      FRONT_PIC(Wartortle),
      FRONT_COORD(0x88,0),
      BACK_PIC(Wartortle),
      BACK_COORD(0x88,0),
      PALETTES(Wartortle),
      ICON(Wartortle,0),
      TAG(SPECIES_NONE),
    }, //Wartortle,
[SPECIES_BLASTOISE] = 
    {  
      FRONT_PIC(Blastoise),
      FRONT_COORD(0x88,0),
      BACK_PIC(Blastoise),
      BACK_COORD(0x88,0),
      PALETTES(Blastoise),
      ICON(Blastoise,0),
      TAG(SPECIES_NONE),
    }, //Blastoise,
[SPECIES_CATERPIE] = 
    {  
      FRONT_PIC(Caterpie),
      FRONT_COORD(0x88,0),
      BACK_PIC(Caterpie),
      BACK_COORD(0x88,0),
      PALETTES(Caterpie),
      ICON(Caterpie,0),
      TAG(SPECIES_NONE),
    }, //Caterpie,
[SPECIES_METAPOD] = 
    {  
      FRONT_PIC(Metapod),
      FRONT_COORD(0x88,0),
      BACK_PIC(Metapod),
      BACK_COORD(0x88,0),
      PALETTES(Metapod),
      ICON(Metapod,0),
      TAG(SPECIES_NONE),
    }, //Metapod,
[SPECIES_BUTTERFREE] = 
    {  
      FRONT_PIC(Butterfree),
      FRONT_COORD(0x88,0),
      BACK_PIC(Butterfree),
      BACK_COORD(0x88,0),
      PALETTES(Butterfree),
      ICON(Butterfree,0),
      TAG(SPECIES_NONE),
    }, //Butterfree,
[SPECIES_WEEDLE] = 
    {  
      FRONT_PIC(Weedle),
      FRONT_COORD(0x88,0),
      BACK_PIC(Weedle),
      BACK_COORD(0x88,0),
      PALETTES(Weedle),
      ICON(Weedle,0),
      TAG(SPECIES_NONE),
    }, //Weedle,
[SPECIES_KAKUNA] = 
    {  
      FRONT_PIC(Kakuna),
      FRONT_COORD(0x88,0),
      BACK_PIC(Kakuna),
      BACK_COORD(0x88,0),
      PALETTES(Kakuna),
      ICON(Kakuna,0),
      TAG(SPECIES_NONE),
    }, //Kakuna,
[SPECIES_BEEDRILL] = 
    {  
      FRONT_PIC(Beedrill),
      FRONT_COORD(0x88,0),
      BACK_PIC(Beedrill),
      BACK_COORD(0x88,0),
      PALETTES(Beedrill),
      ICON(Beedrill,0),
      TAG(SPECIES_NONE),
    }, //Beedrill,
[SPECIES_PIDGEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pidgey,
[SPECIES_PIDGEOTTO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pidgeotto,
[SPECIES_PIDGEOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pidgeot,
[SPECIES_RATTATA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rattata,
[SPECIES_RATICATE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Raticate,
[SPECIES_SPEAROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spearow,
[SPECIES_FEAROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Fearow,
[SPECIES_EKANS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ekans,
[SPECIES_ARBOK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arbok,
[SPECIES_PIKACHU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pikachu,
[SPECIES_RAICHU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Raichu,
[SPECIES_SANDSHREW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sandshrew,
[SPECIES_SANDSLASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sandslash,
[SPECIES_NIDORAN_F] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //NidoranF,
[SPECIES_NIDORINA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nidorina,
[SPECIES_NIDOQUEEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nidoqueen,
[SPECIES_NIDORAN_M] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //NidoranM,
[SPECIES_NIDORINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nidorino,
[SPECIES_NIDOKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nidoking,
[SPECIES_CLEFAIRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Clefairy,
[SPECIES_CLEFABLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Clefable,
[SPECIES_VULPIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vulpix,
[SPECIES_NINETALES] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ninetales,
[SPECIES_JIGGLYPUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jigglypuff,
[SPECIES_WIGGLYTUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wigglytuff,
[SPECIES_ZUBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zubat,
[SPECIES_GOLBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Golbat,
[SPECIES_ODDISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Oddish,
[SPECIES_GLOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gloom,
[SPECIES_VILEPLUME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vileplume,
[SPECIES_PARAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Paras,
[SPECIES_PARASECT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Parasect,
[SPECIES_VENONAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Venonat,
[SPECIES_VENOMOTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Venomoth,
[SPECIES_DIGLETT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Diglett,
[SPECIES_DUGTRIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dugtrio,
[SPECIES_MEOWTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Meowth,
[SPECIES_PERSIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Persian,
[SPECIES_PSYDUCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Psyduck,
[SPECIES_GOLDUCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Golduck,
[SPECIES_MANKEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mankey,
[SPECIES_PRIMEAPE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Primeape,
[SPECIES_GROWLITHE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Growlithe,
[SPECIES_ARCANINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arcanine,
[SPECIES_POLIWAG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Poliwag,
[SPECIES_POLIWHIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Poliwhirl,
[SPECIES_POLIWRATH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Poliwrath,
[SPECIES_ABRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Abra,
[SPECIES_KADABRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kadabra,
[SPECIES_ALAKAZAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alakazam,
[SPECIES_MACHOP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Machop,
[SPECIES_MACHOKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Machoke,
[SPECIES_MACHAMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Machamp,
[SPECIES_BELLSPROUT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bellsprout,
[SPECIES_WEEPINBELL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Weepinbell,
[SPECIES_VICTREEBEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Victreebel,
[SPECIES_TENTACOOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tentacool,
[SPECIES_TENTACRUEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tentacruel,
[SPECIES_GEODUDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Geodude,
[SPECIES_GRAVELER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Graveler,
[SPECIES_GOLEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Golem,
[SPECIES_PONYTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ponyta,
[SPECIES_RAPIDASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rapidash,
[SPECIES_SLOWPOKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slowpoke,
[SPECIES_SLOWBRO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slowbro,
[SPECIES_MAGNEMITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magnemite,
[SPECIES_MAGNETON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magneton,
[SPECIES_FARFETCHD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Farfetchd,
[SPECIES_DODUO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Doduo,
[SPECIES_DODRIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dodrio,
[SPECIES_SEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Seel,
[SPECIES_DEWGONG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dewgong,
[SPECIES_GRIMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grimer,
[SPECIES_MUK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Muk,
[SPECIES_SHELLDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shellder,
[SPECIES_CLOYSTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cloyster,
[SPECIES_GASTLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gastly,
[SPECIES_HAUNTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Haunter,
[SPECIES_GENGAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gengar,
[SPECIES_ONIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Onix,
[SPECIES_DROWZEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drowzee,
[SPECIES_HYPNO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hypno,
[SPECIES_KRABBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Krabby,
[SPECIES_KINGLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kingler,
[SPECIES_VOLTORB] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Voltorb,
[SPECIES_ELECTRODE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Electrode,
[SPECIES_EXEGGCUTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Exeggcute,
[SPECIES_EXEGGUTOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Exeggutor,
[SPECIES_CUBONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cubone,
[SPECIES_MAROWAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Marowak,
[SPECIES_HITMONLEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hitmonlee,
[SPECIES_HITMONCHAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hitmonchan,
[SPECIES_LICKITUNG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lickitung,
[SPECIES_KOFFING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Koffing,
[SPECIES_WEEZING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Weezing,
[SPECIES_RHYHORN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rhyhorn,
[SPECIES_RHYDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rhydon,
[SPECIES_CHANSEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chansey,
[SPECIES_TANGELA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tangela,
[SPECIES_KANGASKHAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kangaskhan,
[SPECIES_HORSEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Horsea,
[SPECIES_SEADRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Seadra,
[SPECIES_GOLDEEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Goldeen,
[SPECIES_SEAKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Seaking,
[SPECIES_STARYU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Staryu,
[SPECIES_STARMIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Starmie,
[SPECIES_MR_MIME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MrMime,
[SPECIES_SCYTHER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scyther,
[SPECIES_JYNX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jynx,
[SPECIES_ELECTABUZZ] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Electabuzz,
[SPECIES_MAGMAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magmar,
[SPECIES_PINSIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pinsir,
[SPECIES_TAUROS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tauros,
[SPECIES_MAGIKARP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magikarp,
[SPECIES_GYARADOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gyarados,
[SPECIES_LAPRAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lapras,
[SPECIES_DITTO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ditto,
[SPECIES_EEVEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eevee,
[SPECIES_VAPOREON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vaporeon,
[SPECIES_JOLTEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jolteon,
[SPECIES_FLAREON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Flareon,
[SPECIES_PORYGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Porygon,
[SPECIES_OMANYTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Omanyte,
[SPECIES_OMASTAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Omastar,
[SPECIES_KABUTO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kabuto,
[SPECIES_KABUTOPS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kabutops,
[SPECIES_AERODACTYL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aerodactyl,
[SPECIES_SNORLAX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Snorlax,
[SPECIES_ARTICUNO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Articuno,
[SPECIES_ZAPDOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zapdos,
[SPECIES_MOLTRES] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Moltres,
[SPECIES_DRATINI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dratini,
[SPECIES_DRAGONAIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dragonair,
[SPECIES_DRAGONITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dragonite,
[SPECIES_MEWTWO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mewtwo,
[SPECIES_MEW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mew,
[SPECIES_CHIKORITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chikorita,
[SPECIES_BAYLEEF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bayleef,
[SPECIES_MEGANIUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Meganium,
[SPECIES_CYNDAQUIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cyndaquil,
[SPECIES_QUILAVA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Quilava,
[SPECIES_TYPHLOSION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Typhlosion,
[SPECIES_TOTODILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Totodile,
[SPECIES_CROCONAW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Croconaw,
[SPECIES_FERALIGATOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Feraligatr,
[SPECIES_SENTRET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sentret,
[SPECIES_FURRET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Furret,
[SPECIES_HOOTHOOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hoothoot,
[SPECIES_NOCTOWL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Noctowl,
[SPECIES_LEDYBA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ledyba,
[SPECIES_LEDIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ledian,
[SPECIES_SPINARAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spinarak,
[SPECIES_ARIADOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ariados,
[SPECIES_CROBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Crobat,
[SPECIES_CHINCHOU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chinchou,
[SPECIES_LANTURN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lanturn,
[SPECIES_PICHU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pichu,
[SPECIES_CLEFFA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cleffa,
[SPECIES_IGGLYBUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Igglybuff,
[SPECIES_TOGEPI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Togepi,
[SPECIES_TOGETIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Togetic,
[SPECIES_NATU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Natu,
[SPECIES_XATU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Xatu,
[SPECIES_MAREEP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mareep,
[SPECIES_FLAAFFY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Flaaffy,
[SPECIES_AMPHAROS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ampharos,
[SPECIES_BELLOSSOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bellossom,
[SPECIES_MARILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Marill,
[SPECIES_AZUMARILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Azumarill,
[SPECIES_SUDOWOODO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sudowoodo,
[SPECIES_POLITOED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Politoed,
[SPECIES_HOPPIP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hoppip,
[SPECIES_SKIPLOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skiploom,
[SPECIES_JUMPLUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jumpluff,
[SPECIES_AIPOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aipom,
[SPECIES_SUNKERN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sunkern,
[SPECIES_SUNFLORA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sunflora,
[SPECIES_YANMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Yanma,
[SPECIES_WOOPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wooper,
[SPECIES_QUAGSIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Quagsire,
[SPECIES_ESPEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Espeon,
[SPECIES_UMBREON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Umbreon,
[SPECIES_MURKROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Murkrow,
[SPECIES_SLOWKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slowking,
[SPECIES_MISDREAVUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Misdreavus,
[SPECIES_UNOWN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Unown,
[SPECIES_WOBBUFFET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wobbuffet,
[SPECIES_GIRAFARIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Girafarig,
[SPECIES_PINECO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pineco,
[SPECIES_FORRETRESS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Forretress,
[SPECIES_DUNSPARCE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dunsparce,
[SPECIES_GLIGAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gligar,
[SPECIES_STEELIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Steelix,
[SPECIES_SNUBBULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Snubbull,
[SPECIES_GRANBULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Granbull,
[SPECIES_QWILFISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Qwilfish,
[SPECIES_SCIZOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scizor,
[SPECIES_SHUCKLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shuckle,
[SPECIES_HERACROSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Heracross,
[SPECIES_SNEASEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sneasel,
[SPECIES_TEDDIURSA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Teddiursa,
[SPECIES_URSARING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ursaring,
[SPECIES_SLUGMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slugma,
[SPECIES_MAGCARGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magcargo,
[SPECIES_SWINUB] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swinub,
[SPECIES_PILOSWINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Piloswine,
[SPECIES_CORSOLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Corsola,
[SPECIES_REMORAID] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Remoraid,
[SPECIES_OCTILLERY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Octillery,
[SPECIES_DELIBIRD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Delibird,
[SPECIES_MANTINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mantine,
[SPECIES_SKARMORY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skarmory,
[SPECIES_HOUNDOUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Houndour,
[SPECIES_HOUNDOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Houndoom,
[SPECIES_KINGDRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kingdra,
[SPECIES_PHANPY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Phanpy,
[SPECIES_DONPHAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Donphan,
[SPECIES_PORYGON2] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Porygon2,
[SPECIES_STANTLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stantler,
[SPECIES_SMEARGLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Smeargle,
[SPECIES_TYROGUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tyrogue,
[SPECIES_HITMONTOP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hitmontop,
[SPECIES_SMOOCHUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Smoochum,
[SPECIES_ELEKID] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Elekid,
[SPECIES_MAGBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magby,
[SPECIES_MILTANK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Miltank,
[SPECIES_BLISSEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Blissey,
[SPECIES_RAIKOU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Raikou,
[SPECIES_ENTEI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Entei,
[SPECIES_SUICUNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Suicune,
[SPECIES_LARVITAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Larvitar,
[SPECIES_PUPITAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pupitar,
[SPECIES_TYRANITAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tyranitar,
[SPECIES_LUGIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lugia,
[SPECIES_HO_OH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //HoOh,
[SPECIES_CELEBI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Celebi,
    
[SPECIES_TREECKO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Treecko,
[SPECIES_GROVYLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grovyle,
[SPECIES_SCEPTILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sceptile,
[SPECIES_TORCHIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Torchic,
[SPECIES_COMBUSKEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Combusken,
[SPECIES_BLAZIKEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Blaziken,
[SPECIES_MUDKIP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mudkip,
[SPECIES_MARSHTOMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Marshtomp,
[SPECIES_SWAMPERT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swampert,
[SPECIES_POOCHYENA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Poochyena,
[SPECIES_MIGHTYENA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mightyena,
[SPECIES_ZIGZAGOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zigzagoon,
[SPECIES_LINOONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Linoone,
[SPECIES_WURMPLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wurmple,
[SPECIES_SILCOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silcoon,
[SPECIES_BEAUTIFLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Beautifly,
[SPECIES_CASCOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cascoon,
[SPECIES_DUSTOX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dustox,
[SPECIES_LOTAD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lotad,
[SPECIES_LOMBRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lombre,
[SPECIES_LUDICOLO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ludicolo,
[SPECIES_SEEDOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Seedot,
[SPECIES_NUZLEAF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nuzleaf,
[SPECIES_SHIFTRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shiftry,
[SPECIES_NINCADA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nincada,
[SPECIES_NINJASK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ninjask,
[SPECIES_SHEDINJA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shedinja,
[SPECIES_TAILLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Taillow,
[SPECIES_SWELLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swellow,
[SPECIES_SHROOMISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shroomish,
[SPECIES_BRELOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Breloom,
[SPECIES_SPINDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spinda,
[SPECIES_WINGULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wingull,
[SPECIES_PELIPPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pelipper,
[SPECIES_SURSKIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Surskit,
[SPECIES_MASQUERAIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Masquerain,
[SPECIES_WAILMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wailmer,
[SPECIES_WAILORD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wailord,
[SPECIES_SKITTY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skitty,
[SPECIES_DELCATTY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Delcatty,
[SPECIES_KECLEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kecleon,
[SPECIES_BALTOY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Baltoy,
[SPECIES_CLAYDOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Claydol,
[SPECIES_NOSEPASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nosepass,
[SPECIES_TORKOAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Torkoal,
[SPECIES_SABLEYE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sableye,
[SPECIES_BARBOACH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Barboach,
[SPECIES_WHISCASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Whiscash,
[SPECIES_LUVDISC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Luvdisc,
[SPECIES_CORPHISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Corphish,
[SPECIES_CRAWDAUNT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Crawdaunt,
[SPECIES_FEEBAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Feebas,
[SPECIES_MILOTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Milotic,
[SPECIES_CARVANHA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Carvanha,
[SPECIES_SHARPEDO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sharpedo,
[SPECIES_TRAPINCH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Trapinch,
[SPECIES_VIBRAVA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vibrava,
[SPECIES_FLYGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Flygon,
[SPECIES_MAKUHITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Makuhita,
[SPECIES_HARIYAMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hariyama,
[SPECIES_ELECTRIKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Electrike,
[SPECIES_MANECTRIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Manectric,
[SPECIES_NUMEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Numel,
[SPECIES_CAMERUPT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Camerupt,
[SPECIES_SPHEAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spheal,
[SPECIES_SEALEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sealeo,
[SPECIES_WALREIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Walrein,
[SPECIES_CACNEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cacnea,
[SPECIES_CACTURNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cacturne,
[SPECIES_SNORUNT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Snorunt,
[SPECIES_GLALIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Glalie,
[SPECIES_LUNATONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lunatone,
[SPECIES_SOLROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Solrock,
[SPECIES_AZURILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Azurill,
[SPECIES_SPOINK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spoink,
[SPECIES_GRUMPIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grumpig,
[SPECIES_PLUSLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Plusle,
[SPECIES_MINUN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minun,
[SPECIES_MAWILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mawile,
[SPECIES_MEDITITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Meditite,
[SPECIES_MEDICHAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Medicham,
[SPECIES_SWABLU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swablu,
[SPECIES_ALTARIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Altaria,
[SPECIES_WYNAUT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wynaut,
[SPECIES_DUSKULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Duskull,
[SPECIES_DUSCLOPS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dusclops,
[SPECIES_ROSELIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Roselia,
[SPECIES_SLAKOTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slakoth,
[SPECIES_VIGOROTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vigoroth,
[SPECIES_SLAKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slaking,
[SPECIES_GULPIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gulpin,
[SPECIES_SWALOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swalot,
[SPECIES_TROPIUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tropius,
[SPECIES_WHISMUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Whismur,
[SPECIES_LOUDRED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Loudred,
[SPECIES_EXPLOUD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Exploud,
[SPECIES_CLAMPERL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Clamperl,
[SPECIES_HUNTAIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Huntail,
[SPECIES_GOREBYSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gorebyss,
[SPECIES_ABSOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Absol,
[SPECIES_SHUPPET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shuppet,
[SPECIES_BANETTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Banette,
[SPECIES_SEVIPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Seviper,
[SPECIES_ZANGOOSE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zangoose,
[SPECIES_RELICANTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Relicanth,
[SPECIES_ARON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aron,
[SPECIES_LAIRON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lairon,
[SPECIES_AGGRON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aggron,
[SPECIES_CASTFORM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Castform,
[SPECIES_VOLBEAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Volbeat,
[SPECIES_ILLUMISE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Illumise,
[SPECIES_LILEEP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lileep,
[SPECIES_CRADILY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cradily,
[SPECIES_ANORITH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Anorith,
[SPECIES_ARMALDO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Armaldo,
[SPECIES_RALTS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ralts,
[SPECIES_KIRLIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kirlia,
[SPECIES_GARDEVOIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gardevoir,
[SPECIES_BAGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bagon,
[SPECIES_SHELGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shelgon,
[SPECIES_SALAMENCE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Salamence,
[SPECIES_BELDUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Beldum,
[SPECIES_METANG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Metang,
[SPECIES_METAGROSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Metagross,
[SPECIES_REGIROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Regirock,
[SPECIES_REGICE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Regice,
[SPECIES_REGISTEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Registeel,
[SPECIES_KYOGRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kyogre,
[SPECIES_GROUDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Groudon,
[SPECIES_RAYQUAZA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rayquaza,
[SPECIES_LATIAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Latias,
[SPECIES_LATIOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Latios,
[SPECIES_JIRACHI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jirachi,
[SPECIES_DEOXYS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Deoxys,
[SPECIES_CHIMECHO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chimecho,
[SPECIES_EGG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Egg,
[SPECIES_UNOWN_B] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownB,
[SPECIES_UNOWN_C] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownC,
[SPECIES_UNOWN_D] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownD,
[SPECIES_UNOWN_E] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownE,
[SPECIES_UNOWN_F] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownF,
[SPECIES_UNOWN_G] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownG,
[SPECIES_UNOWN_H] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownH,
[SPECIES_UNOWN_I] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownI,
[SPECIES_UNOWN_J] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownJ,
[SPECIES_UNOWN_K] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownK,
[SPECIES_UNOWN_L] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownL,
[SPECIES_UNOWN_M] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownM,
[SPECIES_UNOWN_N] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownN,
[SPECIES_UNOWN_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownO,
[SPECIES_UNOWN_P] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownP,
[SPECIES_UNOWN_Q] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownQ,
[SPECIES_UNOWN_R] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownR,
[SPECIES_UNOWN_S] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownS,
[SPECIES_UNOWN_T] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownT,
[SPECIES_UNOWN_U] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownU,
[SPECIES_UNOWN_V] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownV,
[SPECIES_UNOWN_W] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownW,
[SPECIES_UNOWN_X] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownX,
[SPECIES_UNOWN_Y] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownY,
[SPECIES_UNOWN_Z] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownZ,
[SPECIES_UNOWN_EMARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownExclamationMark,
[SPECIES_UNOWN_QMARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //UnownQuestionMark, //ok I see now part of problem, this doeesn't have a comma and others are misaligned.
[SPECIES_TURTWIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Turtwig,
[SPECIES_GROTLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grotle,
[SPECIES_TORTERRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Torterra,
[SPECIES_CHIMCHAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chimchar,
[SPECIES_MONFERNO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Monferno,
[SPECIES_INFERNAPE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Infernape,
[SPECIES_PIPLUP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Piplup,
[SPECIES_PRINPLUP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Prinplup,
[SPECIES_EMPOLEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Empoleon,
[SPECIES_STARLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Starly,
[SPECIES_STARAVIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Staravia,
[SPECIES_STARAPTOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Staraptor,
[SPECIES_BIDOOF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bidoof,
[SPECIES_BIBAREL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bibarel,
[SPECIES_KRICKETOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kricketot,
[SPECIES_KRICKETUNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kricketune,
[SPECIES_SHINX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shinx,
[SPECIES_LUXIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Luxio,
[SPECIES_LUXRAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Luxray,
[SPECIES_BUDEW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Budew,
[SPECIES_ROSERADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Roserade,
[SPECIES_CRANIDOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cranidos,
[SPECIES_RAMPARDOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rampardos,
[SPECIES_SHIELDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shieldon,
[SPECIES_BASTIODON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bastiodon,
[SPECIES_BURMY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Burmy,
[SPECIES_WORMADAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wormadam,
[SPECIES_MOTHIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mothim,
[SPECIES_COMBEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Combee,
[SPECIES_VESPIQUEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vespiquen,
[SPECIES_PACHIRISU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pachirisu,
[SPECIES_BUIZEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Buizel,
[SPECIES_FLOATZEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Floatzel,
[SPECIES_CHERUBI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cherubi,
[SPECIES_CHERRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cherrim,
[SPECIES_SHELLOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shellos,
[SPECIES_GASTRODON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gastrodon,
[SPECIES_AMBIPOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ambipom,
[SPECIES_DRIFLOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drifloon,
[SPECIES_DRIFBLIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drifblim,
[SPECIES_BUNEARY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Buneary,
[SPECIES_LOPUNNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lopunny,
[SPECIES_MISMAGIUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mismagius,
[SPECIES_HONCHKROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Honchkrow,
[SPECIES_GLAMEOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Glameow,
[SPECIES_PURUGLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Purugly,
[SPECIES_CHINGLING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chingling,
[SPECIES_STUNKY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stunky,
[SPECIES_SKUNTANK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skuntank,
[SPECIES_BRONZOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bronzor,
[SPECIES_BRONZONG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bronzong,
[SPECIES_BONSLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bonsly,
[SPECIES_MIME_JR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MimeJr,
[SPECIES_HAPPINY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Happiny,
[SPECIES_CHATOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chatot,
[SPECIES_SPIRITOMB] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spiritomb,
[SPECIES_GIBLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gible,
[SPECIES_GABITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gabite,
[SPECIES_GARCHOMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Garchomp,
[SPECIES_MUNCHLAX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Munchlax,
[SPECIES_RIOLU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Riolu,
[SPECIES_LUCARIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lucario,
[SPECIES_HIPPOPOTAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hippopotas,
[SPECIES_HIPPOWDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hippowdon,
[SPECIES_SKORUPI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skorupi,
[SPECIES_DRAPION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drapion,
[SPECIES_CROAGUNK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Croagunk,
[SPECIES_TOXICROAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Toxicroak,
[SPECIES_CARNIVINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Carnivine,
[SPECIES_FINNEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Finneon,
[SPECIES_LUMINEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lumineon,
[SPECIES_MANTYKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mantyke,
[SPECIES_SNOVER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Snover,
[SPECIES_ABOMASNOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Abomasnow,
[SPECIES_WEAVILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Weavile,
[SPECIES_MAGNEZONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magnezone,
[SPECIES_LICKILICKY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lickilicky,
[SPECIES_RHYPERIOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rhyperior,
[SPECIES_TANGROWTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tangrowth,
[SPECIES_ELECTIVIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Electivire,
[SPECIES_MAGMORTAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magmortar,
[SPECIES_TOGEKISS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Togekiss,
[SPECIES_YANMEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Yanmega,
[SPECIES_LEAFEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Leafeon,
[SPECIES_GLACEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Glaceon,
[SPECIES_GLISCOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gliscor,
[SPECIES_MAMOSWINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mamoswine,
[SPECIES_PORYGON_Z] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Porygon_Z,
[SPECIES_GALLADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gallade,
[SPECIES_PROBOPASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Probopass,
[SPECIES_DUSKNOIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dusknoir,
[SPECIES_FROSLASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Froslass,
[SPECIES_ROTOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rotom,
[SPECIES_UXIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Uxie,
[SPECIES_MESPRIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mesprit,
[SPECIES_AZELF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Azelf,
[SPECIES_DIALGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dialga,
[SPECIES_PALKIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Palkia,
[SPECIES_HEATRAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Heatran,
[SPECIES_REGIGIGAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Regigigas,
[SPECIES_GIRATINA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Giratina,
[SPECIES_CRESSELIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cresselia,
[SPECIES_PHIONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Phione,
[SPECIES_MANAPHY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Manaphy,
[SPECIES_DARKRAI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Darkrai,
[SPECIES_SHAYMIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shaymin,
[SPECIES_ARCEUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
[SPECIES_VICTINI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Victini,
[SPECIES_SNIVY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Snivy,
[SPECIES_SERVINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Servine,
[SPECIES_SERPERIOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Serperior,
[SPECIES_TEPIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tepig,
[SPECIES_PIGNITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pignite,
[SPECIES_EMBOAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Emboar,
[SPECIES_OSHAWOTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Oshawott,
[SPECIES_DEWOTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dewott,
[SPECIES_SAMUROTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Samurott,
[SPECIES_PATRAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Patrat,
[SPECIES_WATCHOG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Watchog,
[SPECIES_LILLIPUP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lillipup,
[SPECIES_HERDIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Herdier,
[SPECIES_STOUTLAND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stoutland,
[SPECIES_PURRLOIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Purrloin,
[SPECIES_LIEPARD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Liepard,
[SPECIES_PANSAGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pansage,
[SPECIES_SIMISAGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Simisage,
[SPECIES_PANSEAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pansear,
[SPECIES_SIMISEAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Simisear,
[SPECIES_PANPOUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Panpour,
[SPECIES_SIMIPOUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Simipour,
[SPECIES_MUNNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Munna,
[SPECIES_MUSHARNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Musharna,
[SPECIES_PIDOVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pidove,
[SPECIES_TRANQUILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tranquill,
[SPECIES_UNFEZANT_MALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Unfezant,
[SPECIES_BLITZLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Blitzle,
[SPECIES_ZEBSTRIKA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zebstrika,
[SPECIES_ROGGENROLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Roggenrola,
[SPECIES_BOLDORE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Boldore,
[SPECIES_GIGALITH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gigalith,
[SPECIES_WOOBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Woobat,
[SPECIES_SWOOBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swoobat,
[SPECIES_DRILBUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drilbur,
[SPECIES_EXCADRILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Excadrill,
[SPECIES_AUDINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Audino,
[SPECIES_TIMBURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Timburr,
[SPECIES_GURDURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gurdurr,
[SPECIES_CONKELDURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Conkeldurr,
[SPECIES_TYMPOLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tympole,
[SPECIES_PALPITOAD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Palpitoad,
[SPECIES_SEISMITOAD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Seismitoad,
[SPECIES_THROH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Throh,
[SPECIES_SAWK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sawk,
[SPECIES_SEWADDLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sewaddle,
[SPECIES_SWADLOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swadloon,
[SPECIES_LEAVANNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Leavanny,
[SPECIES_VENIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Venipede,
[SPECIES_WHIRLIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Whirlipede,
[SPECIES_SCOLIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scolipede,
[SPECIES_COTTONEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cottonee,
[SPECIES_WHIMSICOTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Whimsicott,
[SPECIES_PETILIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Petilil,
[SPECIES_LILLIGANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lilligant,
[SPECIES_BASCULIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Basculin,
[SPECIES_SANDILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sandile,
[SPECIES_KROKOROK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Krokorok,
[SPECIES_KROOKODILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Krookodile,
[SPECIES_DARUMAKA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Darumaka,
[SPECIES_DARMANITAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Darmanitan,
[SPECIES_MARACTUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Maractus,
[SPECIES_DWEBBLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dwebble,
[SPECIES_CRUSTLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Crustle,
[SPECIES_SCRAGGY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scraggy,
[SPECIES_SCRAFTY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scrafty,
[SPECIES_SIGILYPH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sigilyph,
[SPECIES_YAMASK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Yamask,
[SPECIES_COFAGRIGUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cofagrigus,
[SPECIES_TIRTOUGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tirtouga,
[SPECIES_CARRACOSTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Carracosta,
[SPECIES_ARCHEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Archen,
[SPECIES_ARCHEOPS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Archeops,
[SPECIES_TRUBBISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Trubbish,
[SPECIES_GARBODOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Garbodor,
[SPECIES_ZORUA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zorua,
[SPECIES_ZOROARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zoroark,
[SPECIES_MINCCINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minccino,
[SPECIES_CINCCINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cinccino,
[SPECIES_GOTHITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gothita,
[SPECIES_GOTHORITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gothorita,
[SPECIES_GOTHITELLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gothitelle,
[SPECIES_SOLOSIS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Solosis,
[SPECIES_DUOSION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Duosion,
[SPECIES_REUNICLUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Reuniclus,
[SPECIES_DUCKLETT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ducklett,
[SPECIES_SWANNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swanna,
[SPECIES_VANILLITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vanillite,
[SPECIES_VANILLISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vanillish,
[SPECIES_VANILLUXE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vanilluxe,
[SPECIES_DEERLING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Deerling,
[SPECIES_SAWSBUCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sawsbuck,
[SPECIES_EMOLGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Emolga,
[SPECIES_KARRABLAST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Karrablast,
[SPECIES_ESCAVALIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Escavalier,
[SPECIES_FOONGUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Foongus,
[SPECIES_AMOONGUSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Amoonguss,
[SPECIES_FRILLISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Frillish,
[SPECIES_JELLICENT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jellicent,
[SPECIES_ALOMOMOLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alomomola,
[SPECIES_JOLTIK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Joltik,
[SPECIES_GALVANTULA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Galvantula,
[SPECIES_FERROSEED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ferroseed,
[SPECIES_FERROTHORN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ferrothorn,
[SPECIES_KLINK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Klink,
[SPECIES_KLANG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Klang,
[SPECIES_KLINKLANG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Klinklang,
[SPECIES_TYNAMO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tynamo,
[SPECIES_EELEKTRIK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eelektrik,
[SPECIES_EELEKTROSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eelektross,
[SPECIES_ELGYEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Elgyem,
[SPECIES_BEHEEYEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Beheeyem,
[SPECIES_LITWICK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Litwick,
[SPECIES_LAMPENT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lampent,
[SPECIES_CHANDELURE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chandelure,
[SPECIES_AXEW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Axew,
[SPECIES_FRAXURE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Fraxure,
[SPECIES_HAXORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Haxorus,
[SPECIES_CUBCHOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cubchoo,
[SPECIES_BEARTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Beartic,
[SPECIES_CRYOGONAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cryogonal,
[SPECIES_SHELMET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shelmet,
[SPECIES_ACCELGOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Accelgor,
[SPECIES_STUNFISK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stunfisk,
[SPECIES_MIENFOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mienfoo,
[SPECIES_MIENSHAO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mienshao,
[SPECIES_DRUDDIGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Druddigon,
[SPECIES_GOLETT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Golett,
[SPECIES_GOLURK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Golurk,
[SPECIES_PAWNIARD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pawniard,
[SPECIES_BISHARP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bisharp,
[SPECIES_BOUFFALANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bouffalant,
[SPECIES_RUFFLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rufflet,
[SPECIES_BRAVIARY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Braviary,
[SPECIES_VULLABY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vullaby,
[SPECIES_MANDIBUZZ] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mandibuzz,
[SPECIES_HEATMOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Heatmor,
[SPECIES_DURANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Durant,
[SPECIES_DEINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Deino,
[SPECIES_ZWEILOUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zweilous,
[SPECIES_HYDREIGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hydreigon,
[SPECIES_LARVESTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Larvesta,
[SPECIES_VOLCARONA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Volcarona,
[SPECIES_COBALION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cobalion,
[SPECIES_TERRAKION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Terrakion,
[SPECIES_VIRIZION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Virizion,
[SPECIES_TORNADUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tornadus,
[SPECIES_THUNDURUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Thundurus,
[SPECIES_RESHIRAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Reshiram,
[SPECIES_ZEKROM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zekrom,
[SPECIES_LANDORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Landorus,
[SPECIES_KYUREM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kyurem,
[SPECIES_KELDEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Keldeo,
[SPECIES_MELOETTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Meloetta,
[SPECIES_GENESECT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Genesect,
[SPECIES_CHESPIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chespin,
[SPECIES_QUILLADIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Quilladin,
[SPECIES_CHESNAUGHT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chesnaught,
[SPECIES_FENNEKIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Fennekin,
[SPECIES_BRAIXEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Braixen,
[SPECIES_DELPHOX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Delphox,
[SPECIES_FROAKIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Froakie,
[SPECIES_FROGADIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Frogadier,
[SPECIES_GRENINJA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Greninja,
[SPECIES_BUNNELBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bunnelby,
[SPECIES_DIGGERSBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Diggersby,
[SPECIES_FLETCHLING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Fletchling,
[SPECIES_FLETCHINDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Fletchinder,
[SPECIES_TALONFLAME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Talonflame,
[SPECIES_SCATTERBUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scatterbug,
[SPECIES_SPEWPA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spewpa,
[SPECIES_VIVILLON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vivillon,
[SPECIES_LITLEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Litleo,
[SPECIES_PYROAR_MALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pyroar,
[SPECIES_FLABEBE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Flabebe,
[SPECIES_FLOETTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Floette,
[SPECIES_FLORGES] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Florges,
[SPECIES_SKIDDO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skiddo,
[SPECIES_GOGOAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gogoat,
[SPECIES_PANCHAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pancham,
[SPECIES_PANGORO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pangoro,
[SPECIES_FURFROU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Furfrou,
[SPECIES_ESPURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Espurr,
[SPECIES_MEOWSTIC_MALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Meowstic,
[SPECIES_HONEDGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Honedge,
[SPECIES_DOUBLADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Doublade,
[SPECIES_AEGISLASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aegislash,
[SPECIES_SPRITZEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spritzee,
[SPECIES_AROMATISSE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aromatisse,
[SPECIES_SWIRLIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Swirlix,
[SPECIES_SLURPUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Slurpuff,
[SPECIES_INKAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Inkay,
[SPECIES_MALAMAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Malamar,
[SPECIES_BINACLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Binacle,
[SPECIES_BARBARACLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Barbaracle,
[SPECIES_SKRELP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skrelp,
[SPECIES_DRAGALGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dragalge,
[SPECIES_CLAUNCHER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Clauncher,
[SPECIES_CLAWITZER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Clawitzer,
[SPECIES_HELIOPTILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Helioptile,
[SPECIES_HELIOLISK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Heliolisk,
[SPECIES_TYRUNT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tyrunt,
[SPECIES_TYRANTRUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tyrantrum,
[SPECIES_AMAURA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Amaura,
[SPECIES_AURORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Aurorus,
[SPECIES_SYLVEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sylveon,
[SPECIES_HAWLUCHA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hawlucha,
[SPECIES_DEDENNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dedenne,
[SPECIES_CARBINK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Carbink,
[SPECIES_GOOMY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Goomy,
[SPECIES_SLIGGOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sliggoo,
[SPECIES_GOODRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Goodra,
[SPECIES_KLEFKI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Klefki,
[SPECIES_PHANTUMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Phantump,
[SPECIES_TREVENANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Trevenant,
[SPECIES_PUMPKABOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pumpkaboo,
[SPECIES_GOURGEIST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gourgeist,
[SPECIES_BERGMITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bergmite,
[SPECIES_AVALUGG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Avalugg,
[SPECIES_NOIBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Noibat,
[SPECIES_NOIVERN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Noivern,
[SPECIES_XERNEAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Xerneas,
[SPECIES_YVELTAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Yveltal,
[SPECIES_ZYGARDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zygarde,
[SPECIES_DIANCIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Diancie,
[SPECIES_HOOPA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hoopa,
[SPECIES_VOLCANION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Volcanion,
[SPECIES_ROWLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rowlet,
[SPECIES_DARTRIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dartrix,
[SPECIES_DECIDUEYE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Decidueye,
[SPECIES_LITTEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Litten,
[SPECIES_TORRACAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Torracat,
[SPECIES_INCINEROAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Incineroar,
[SPECIES_POPPLIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Popplio,
[SPECIES_BRIONNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Brionne,
[SPECIES_PRIMARINA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Primarina,
[SPECIES_PIKIPEK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pikipek,
[SPECIES_TRUMBEAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Trumbeak,
[SPECIES_TOUCANNON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Toucannon,
[SPECIES_YUNGOOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Yungoos,
[SPECIES_GUMSHOOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gumshoos,
[SPECIES_GRUBBIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grubbin,
[SPECIES_CHARJABUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Charjabug,
[SPECIES_VIKAVOLT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Vikavolt,
[SPECIES_CRABRAWLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Crabrawler,
[SPECIES_CRABOMINABLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Crabominable,
[SPECIES_ORICORIO_BAILE] = 
    {  
      FRONT_PIC(Oricorio_Baile),
      FRONT_COORD(0x88,0),
      BACK_PIC(Oricorio_Baile),
      BACK_COORD(0x88,0),
      PALETTES(Oricorio_Baile),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Oricorio_Baile,
[SPECIES_CUTIEFLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cutiefly,
[SPECIES_RIBOMBEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ribombee,
[SPECIES_ROCKRUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rockruff,
[SPECIES_LYCANROC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lycanroc,
[SPECIES_WISHIWASHI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wishiwashi,
[SPECIES_MAREANIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mareanie,
[SPECIES_TOXAPEX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Toxapex,
[SPECIES_MUDBRAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mudbray,
[SPECIES_MUDSDALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mudsdale,
[SPECIES_DEWPIDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dewpider,
[SPECIES_ARAQUANID] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Araquanid,
[SPECIES_FOMANTIS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Fomantis,
[SPECIES_LURANTIS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lurantis,
[SPECIES_MORELULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Morelull,
[SPECIES_SHIINOTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Shiinotic,
[SPECIES_SALANDIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Salandit,
[SPECIES_SALAZZLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Salazzle,
[SPECIES_STUFFUL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stufful,
[SPECIES_BEWEAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bewear,
[SPECIES_BOUNSWEET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bounsweet,
[SPECIES_STEENEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Steenee,
[SPECIES_TSAREENA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Tsareena,
[SPECIES_COMFEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Comfey,
[SPECIES_ORANGURU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Oranguru,
[SPECIES_PASSIMIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Passimian,
[SPECIES_WIMPOD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wimpod,
[SPECIES_GOLISOPOD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Golisopod,
[SPECIES_SANDYGAST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sandygast,
[SPECIES_PALOSSAND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Palossand,
[SPECIES_PYUKUMUKU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pyukumuku,
[SPECIES_TYPE_NULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TypeNull,
[SPECIES_SILVALLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
[SPECIES_MINIOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
[SPECIES_KOMALA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Komala,
[SPECIES_TURTONATOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Turtonator,
[SPECIES_TOGEDEMARU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Togedemaru,
[SPECIES_MIMIKYU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Mimikyu,
[SPECIES_BRUXISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Bruxish,
[SPECIES_DRAMPA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drampa,
[SPECIES_DHELMISE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dhelmise,
[SPECIES_JANGMO_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Jangmoo,
[SPECIES_HAKAMO_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hakamoo,
[SPECIES_KOMMO_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kommoo,
[SPECIES_TAPU_KOKO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TapuKoko,
[SPECIES_TAPU_LELE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TapuLele,
[SPECIES_TAPU_BULU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TapuBulu,
[SPECIES_TAPU_FINI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TapuFini,
[SPECIES_COSMOG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cosmog,
[SPECIES_COSMOEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cosmoem,
[SPECIES_SOLGALEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Solgaleo,
[SPECIES_LUNALA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Lunala,
[SPECIES_NIHILEGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nihilego,
[SPECIES_BUZZWOLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Buzzwole,
[SPECIES_PHEROMOSA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pheromosa,
[SPECIES_XURKITREE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Xurkitree,
[SPECIES_CELESTEELA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Celesteela,
[SPECIES_KARTANA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kartana,
[SPECIES_GUZZLORD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Guzzlord,
[SPECIES_NECROZMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Necrozma,
[SPECIES_MAGEARNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Magearna,
[SPECIES_MARSHADOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Marshadow,
[SPECIES_POIPOLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Poipole,
[SPECIES_NAGANADEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Naganadel,
[SPECIES_STAKATAKA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stakataka,
[SPECIES_BLACEPHALON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Blacephalon,
[SPECIES_ZERAORA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zeraora,
[SPECIES_MELTAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Meltan,
[SPECIES_MELMETAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Melmetal,
[SPECIES_GROOKEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grookey,
[SPECIES_THWACKEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Thwackey,
[SPECIES_RILLABOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rillaboom,
[SPECIES_SCORBUNNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Scorbunny,
[SPECIES_RABOOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Raboot,
[SPECIES_CINDERACE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cinderace,
[SPECIES_SOBBLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sobble,
[SPECIES_DRIZZILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drizzile,
[SPECIES_INTELEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Inteleon,
[SPECIES_SKWOVET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Skwovet,
[SPECIES_GREEDENT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Greedent,
[SPECIES_ROOKIDEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rookidee,
[SPECIES_CORVISQUIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Corvisquire,
[SPECIES_CORVIKNIGHT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Corviknight,
[SPECIES_BLIPBUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Blipbug,
[SPECIES_DOTTLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dottler,
[SPECIES_ORBEETLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Orbeetle,
[SPECIES_NICKIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Nickit,
[SPECIES_THIEVUL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Thievul,
[SPECIES_GOSSIFLEUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gossifleur,
[SPECIES_ELDEGOSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eldegoss,
[SPECIES_WOOLOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wooloo,
[SPECIES_DUBWOOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dubwool,
[SPECIES_CHEWTLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Chewtle,
[SPECIES_DREDNAW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drednaw,
[SPECIES_YAMPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Yamper,
[SPECIES_BOLTUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Boltund,
[SPECIES_ROLYCOLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Rolycoly,
[SPECIES_CARKOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Carkol,
[SPECIES_COALOSSAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Coalossal,
[SPECIES_APPLIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Applin,
[SPECIES_FLAPPLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Flapple,
[SPECIES_APPLETUN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Appletun,
[SPECIES_SILICOBRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silicobra,
[SPECIES_SANDACONDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sandaconda,
[SPECIES_CRAMORANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cramorant,
[SPECIES_ARROKUDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arrokuda,
[SPECIES_BARRASKEWDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Barraskewda,
[SPECIES_TOXEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Toxel,
[SPECIES_TOXTRICITY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Toxtricity,
[SPECIES_SIZZLIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sizzlipede,
[SPECIES_CENTISKORCH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Centiskorch,
[SPECIES_CLOBBOPUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Clobbopus,
[SPECIES_GRAPPLOCT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grapploct,
[SPECIES_SINISTEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sinistea,
[SPECIES_POLTEAGEIST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Polteageist,
[SPECIES_HATENNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hatenna,
[SPECIES_HATTREM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hattrem,
[SPECIES_HATTERENE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Hatterene,
[SPECIES_IMPIDIMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Impidimp,
[SPECIES_MORGREM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Morgrem,
[SPECIES_GRIMMSNARL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Grimmsnarl,
[SPECIES_OBSTAGOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Obstagoon,
[SPECIES_PERRSERKER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Perrserker,
[SPECIES_CURSOLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cursola,
[SPECIES_SIRFETCHD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sirfetchd,
[SPECIES_MR_RIME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MrRime,
[SPECIES_RUNERIGUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Runerigus,
[SPECIES_MILCERY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Milcery,
[SPECIES_ALCREMIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie,
[SPECIES_FALINKS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Falinks,
[SPECIES_PINCURCHIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pincurchin,
[SPECIES_SNOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Snom,
[SPECIES_FROSMOTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Frosmoth,
[SPECIES_STONJOURNER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Stonjourner,
[SPECIES_EISCUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eiscue,
[SPECIES_INDEEDEE_MALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Indeedee,
[SPECIES_MORPEKO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Morpeko,
[SPECIES_CUFANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cufant,
[SPECIES_COPPERAJAH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Copperajah,
[SPECIES_DRACOZOLT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dracozolt,
[SPECIES_ARCTOZOLT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arctozolt,
[SPECIES_DRACOVISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dracovish,
[SPECIES_ARCTOVISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arctovish,
[SPECIES_DURALUDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Duraludon,
[SPECIES_DREEPY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dreepy,
[SPECIES_DRAKLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Drakloak,
[SPECIES_DRAGAPULT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Dragapult,
[SPECIES_ZACIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zacian,
[SPECIES_ZAMAZENTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zamazenta,
[SPECIES_ETERNATUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eternatus,
[SPECIES_KUBFU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kubfu,
[SPECIES_URSHIFU_SINGLE_STRIKE_STYLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Urshifu,
[SPECIES_ZARUDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zarude,
[SPECIES_REGIELEKI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Regieleki,
[SPECIES_REGIDRAGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Regidrago,
[SPECIES_GLASTRIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Glastrier,
[SPECIES_SPECTRIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Spectrier,
[SPECIES_CALYREX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Calyrex,
[SPECIES_WYRDEER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Wyrdeer,
[SPECIES_KLEAVOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Kleavor,
[SPECIES_URSALUNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Ursaluna,
[SPECIES_BASCULEGION_MALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Basculegion,
[SPECIES_SNEASLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Sneasler,
[SPECIES_OVERQWIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Overqwil,
[SPECIES_ENAMORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Enamorus,
  [SPECIES_VENUSAUR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VenusaurMega,
  [SPECIES_CHARIZARD_MEGA_X] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CharizardMegaX,
  [SPECIES_CHARIZARD_MEGA_Y] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CharizardMegaY,
  [SPECIES_BLASTOISE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BlastoiseMega,
  [SPECIES_BEEDRILL_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BeedrillMega,
  [SPECIES_PIDGEOT_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PidgeotMega,
  [SPECIES_ALAKAZAM_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AlakazamMega,
  [SPECIES_SLOWBRO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SlowbroMega,
  [SPECIES_GENGAR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GengarMega,
  [SPECIES_KANGASKHAN_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //KangaskhanMega,
  [SPECIES_PINSIR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PinsirMega,
  [SPECIES_GYARADOS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GyaradosMega,
  [SPECIES_AERODACTYL_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AerodactylMega,
  [SPECIES_MEWTWO_MEGA_X] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MewtwoMegaX,
  [SPECIES_MEWTWO_MEGA_Y] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MewtwoMegaY,
  [SPECIES_AMPHAROS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AmpharosMega,
  [SPECIES_STEELIX_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SteelixMega,
  [SPECIES_SCIZOR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ScizorMega,
  [SPECIES_HERACROSS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //HeracrossMega,
  [SPECIES_HOUNDOOM_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //HoundoomMega,
  [SPECIES_TYRANITAR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TyranitarMega,
  [SPECIES_SCEPTILE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SceptileMega,
  [SPECIES_BLAZIKEN_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BlazikenMega,
  [SPECIES_SWAMPERT_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SwampertMega,
  [SPECIES_GARDEVOIR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GardevoirMega,
  [SPECIES_SABLEYE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SableyeMega,
  [SPECIES_MAWILE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MawileMega,
  [SPECIES_AGGRON_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AggronMega,
  [SPECIES_MEDICHAM_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MedichamMega,
  [SPECIES_MANECTRIC_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ManectricMega,
  [SPECIES_SHARPEDO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SharpedoMega,
  [SPECIES_CAMERUPT_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CameruptMega,
  [SPECIES_ALTARIA_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AltariaMega,
  [SPECIES_BANETTE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BanetteMega,
  [SPECIES_ABSOL_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AbsolMega,
  [SPECIES_GLALIE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GlalieMega,
  [SPECIES_SALAMENCE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SalamenceMega,
  [SPECIES_METAGROSS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MetagrossMega,
  [SPECIES_LATIAS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LatiasMega,
  [SPECIES_LATIOS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LatiosMega,
  [SPECIES_LOPUNNY_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LopunnyMega,
  [SPECIES_GARCHOMP_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GarchompMega,
  [SPECIES_LUCARIO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LucarioMega,
  [SPECIES_ABOMASNOW_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AbomasnowMega,
  [SPECIES_GALLADE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GalladeMega,
  [SPECIES_AUDINO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AudinoMega,
  [SPECIES_DIANCIE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DiancieMega,
  [SPECIES_RAYQUAZA_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RayquazaMega,
  [SPECIES_KYOGRE_PRIMAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //KyogrePrimal,
  [SPECIES_GROUDON_PRIMAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GroudonPrimal,
  [SPECIES_RATTATA_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RattataAlolan,
  [SPECIES_RATICATE_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RaticateAlolan,
  [SPECIES_RAICHU_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RaichuAlolan,
  [SPECIES_SANDSHREW_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SandshrewAlolan,
  [SPECIES_SANDSLASH_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SandslashAlolan,
  [SPECIES_VULPIX_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VulpixAlolan,
  [SPECIES_NINETALES_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //NinetalesAlolan,
  [SPECIES_DIGLETT_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DiglettAlolan,
  [SPECIES_DUGTRIO_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DugtrioAlolan,
  [SPECIES_MEOWTH_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MeowthAlolan,
  [SPECIES_PERSIAN_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PersianAlolan,
  [SPECIES_GEODUDE_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GeodudeAlolan,
  [SPECIES_GRAVELER_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GravelerAlolan,
  [SPECIES_GOLEM_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GolemAlolan,
  [SPECIES_GRIMER_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GrimerAlolan,
  [SPECIES_MUK_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MukAlolan,
  [SPECIES_EXEGGUTOR_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ExeggutorAlolan,
  [SPECIES_MAROWAK_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MarowakAlolan,
  [SPECIES_MEOWTH_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MeowthGalarian,
  [SPECIES_PONYTA_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PonytaGalarian,
  [SPECIES_RAPIDASH_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RapidashGalarian,
  [SPECIES_SLOWPOKE_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SlowpokeGalarian,
  [SPECIES_SLOWBRO_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SlowbroGalarian,
  [SPECIES_FARFETCHD_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FarfetchdGalarian,
  [SPECIES_WEEZING_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //WeezingGalarian,
  [SPECIES_MR_MIME_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MrMimeGalarian,
  [SPECIES_ARTICUNO_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ArticunoGalarian,
  [SPECIES_ZAPDOS_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ZapdosGalarian,
  [SPECIES_MOLTRES_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MoltresGalarian,
  [SPECIES_SLOWKING_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SlowkingGalarian,
  [SPECIES_CORSOLA_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CorsolaGalarian,
  [SPECIES_ZIGZAGOON_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ZigzagoonGalarian,
  [SPECIES_LINOONE_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LinooneGalarian,
  [SPECIES_DARUMAKA_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DarumakaGalarian,
  [SPECIES_DARMANITAN_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DarmanitanGalarian,
  [SPECIES_YAMASK_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //YamaskGalarian,
  [SPECIES_STUNFISK_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //StunfiskGalarian,
  [SPECIES_GROWLITHE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GrowlitheHisuian,
  [SPECIES_ARCANINE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ArcanineHisuian,
  [SPECIES_VOLTORB_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VoltorbHisuian,
  [SPECIES_ELECTRODE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ElectrodeHisuian,
  [SPECIES_TYPHLOSION_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TyphlosionHisuian,
  [SPECIES_QWILFISH_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //QwilfishHisuian,
  [SPECIES_SNEASEL_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SneaselHisuian,
  [SPECIES_SAMUROTT_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SamurottHisuian,
  [SPECIES_LILLIGANT_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LilligantHisuian,
  [SPECIES_ZORUA_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ZoruaHisuian,
  [SPECIES_ZOROARK_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ZoroarkHisuian,
  [SPECIES_BRAVIARY_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BraviaryHisuian,
  [SPECIES_SLIGGOO_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SliggooHisuian,
  [SPECIES_GOODRA_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GoodraHisuian,
  [SPECIES_AVALUGG_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AvaluggHisuian,
  [SPECIES_DECIDUEYE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DecidueyeHisuian,
  [SPECIES_PIKACHU_COSPLAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuCosplay,
  [SPECIES_PIKACHU_ROCK_STAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuRockStar,
  [SPECIES_PIKACHU_BELLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuBelle,
  [SPECIES_PIKACHU_POP_STAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuPopStar,
  [SPECIES_PIKACHU_PH_D] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuPhD,
  [SPECIES_PIKACHU_LIBRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuLibre,
  [SPECIES_PIKACHU_ORIGINAL_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuOriginalCap,
  [SPECIES_PIKACHU_HOENN_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuHoennCap,
  [SPECIES_PIKACHU_SINNOH_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuSinnohCap,
  [SPECIES_PIKACHU_UNOVA_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuUnovaCap,
  [SPECIES_PIKACHU_KALOS_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuKalosCap,
  [SPECIES_PIKACHU_ALOLA_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuAlolaCap,
  [SPECIES_PIKACHU_PARTNER_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuPartnerCap,
  [SPECIES_PIKACHU_WORLD_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PikachuWorldCap,
  [SPECIES_PICHU_SPIKY_EARED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //PichuSpikyEared,
  [SPECIES_CASTFORM_SUNNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CastformSunny,
  [SPECIES_CASTFORM_RAINY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CastformRainy,
  [SPECIES_CASTFORM_SNOWY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CastformSnowy,
  [SPECIES_DEOXYS_ATTACK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DeoxysAttack,
  [SPECIES_DEOXYS_DEFENSE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DeoxysDefense,
  [SPECIES_DEOXYS_SPEED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DeoxysSpeed,
  [SPECIES_BURMY_SANDY_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BurmySandyCloak,
  [SPECIES_BURMY_TRASH_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BurmyTrashCloak,
  [SPECIES_WORMADAM_SANDY_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //WormadamSandyCloak,
  [SPECIES_WORMADAM_TRASH_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //WormadamTrashCloak,
  [SPECIES_CHERRIM_SUNSHINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //CherrimSunshine,
  [SPECIES_SHELLOS_EAST_SEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ShellosEastSea,
  [SPECIES_GASTRODON_EAST_SEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GastrodonEastSea,
  [SPECIES_ROTOM_HEAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RotomHeat,
  [SPECIES_ROTOM_WASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RotomWash,
  [SPECIES_ROTOM_FROST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RotomFrost,
  [SPECIES_ROTOM_FAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RotomFan,
  [SPECIES_ROTOM_MOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //RotomMow,
  [SPECIES_GIRATINA_ORIGIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GiratinaOrigin,
  [SPECIES_SHAYMIN_SKY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ShayminSky,
  [SPECIES_ARCEUS_FIGHTING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_FLYING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_POISON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_GROUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_ROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_BUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_GHOST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_STEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_FIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_WATER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_GRASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_ELECTRIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_PSYCHIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_ICE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_DRAGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_DARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_ARCEUS_FAIRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Arceus,
  [SPECIES_BASCULIN_BLUE_STRIPED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BasculinBlueStriped,
  [SPECIES_BASCULIN_WHITE_STRIPED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //BasculinHisuian,
  [SPECIES_DARMANITAN_ZEN_MODE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DarmanitanZenMode,
  [SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DarmanitanZenModeGalarian,
  [SPECIES_DEERLING_SUMMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DeerlingSummer,
  [SPECIES_DEERLING_AUTUMN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DeerlingAutumn,
  [SPECIES_DEERLING_WINTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //DeerlingWinter,
  [SPECIES_SAWSBUCK_SUMMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SawsbuckSummer,
  [SPECIES_SAWSBUCK_AUTUMN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SawsbuckAutumn,
  [SPECIES_SAWSBUCK_WINTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //SawsbuckWinter,
  [SPECIES_TORNADUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //TornadusTherian,
  [SPECIES_THUNDURUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ThundurusTherian,
  [SPECIES_LANDORUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LandorusTherian,
  [SPECIES_ENAMORUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //EnamorusTherian,
  [SPECIES_KYUREM_WHITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //KyuremWhite,
  [SPECIES_KYUREM_BLACK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //KyuremBlack,
  [SPECIES_KELDEO_RESOLUTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //KeldeoResolute,
  [SPECIES_MELOETTA_PIROUETTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MeloettaPirouette,
  [SPECIES_GENESECT_DOUSE_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Genesect,
  [SPECIES_GENESECT_SHOCK_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Genesect,
  [SPECIES_GENESECT_BURN_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Genesect,
  [SPECIES_GENESECT_CHILL_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Genesect,
  [SPECIES_GRENINJA_ASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //GreninjaAsh,
  [SPECIES_VIVILLON_POLAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonPolar,
  [SPECIES_VIVILLON_TUNDRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonTundra,
  [SPECIES_VIVILLON_CONTINENTAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonContinental,
  [SPECIES_VIVILLON_GARDEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonGarden,
  [SPECIES_VIVILLON_ELEGANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonElegant,
  [SPECIES_VIVILLON_MEADOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonMeadow,
  [SPECIES_VIVILLON_MODERN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonModern,
  [SPECIES_VIVILLON_MARINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonMarine,
  [SPECIES_VIVILLON_ARCHIPELAGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonArchipelago,
  [SPECIES_VIVILLON_HIGH_PLAINS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonHighPlains,
  [SPECIES_VIVILLON_SANDSTORM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonSandstorm,
  [SPECIES_VIVILLON_RIVER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonRiver,
  [SPECIES_VIVILLON_MONSOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonMonsoon,
  [SPECIES_VIVILLON_SAVANNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonSavanna,
  [SPECIES_VIVILLON_SUN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonSun,
  [SPECIES_VIVILLON_OCEAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonOcean,
  [SPECIES_VIVILLON_JUNGLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonJungle,
  [SPECIES_VIVILLON_FANCY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonFancy,
  [SPECIES_VIVILLON_POKE_BALL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //VivillonPokeBall,
  [SPECIES_UNFEZANT_FEMALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Unfezant_Female
  [SPECIES_PYROAR_FEMALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pyroar_Female,
  [SPECIES_FLABEBE_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlabebeYellowFlower,
  [SPECIES_FLABEBE_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlabebeOrangeFlower,
  [SPECIES_FLABEBE_BLUE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlabebeBlueFlower,
  [SPECIES_FLABEBE_WHITE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlabebeWhiteFlower,
  [SPECIES_FLOETTE_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FloetteYellowFlower,
  [SPECIES_FLOETTE_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FloetteOrangeFlower,
  [SPECIES_FLOETTE_BLUE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FloetteBlueFlower,
  [SPECIES_FLOETTE_WHITE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FloetteWhiteFlower,
  [SPECIES_FLOETTE_ETERNAL_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FloetteEternalFlower,
  [SPECIES_FLORGES_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlorgesYellowFlower,
  [SPECIES_FLORGES_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlorgesOrangeFlower,
  [SPECIES_FLORGES_BLUE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlorgesBlueFlower,
  [SPECIES_FLORGES_WHITE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FlorgesWhiteFlower,
  [SPECIES_FURFROU_HEART_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouHeartTrim,
  [SPECIES_FURFROU_STAR_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouStarTrim,
  [SPECIES_FURFROU_DIAMOND_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouDiamondTrim,
  [SPECIES_FURFROU_DEBUTANTE_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouDebutanteTrim,
  [SPECIES_FURFROU_MATRON_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouMatronTrim,
  [SPECIES_FURFROU_DANDY_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouDandyTrim,
  [SPECIES_FURFROU_LA_REINE_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouLaReineTrim,
  [SPECIES_FURFROU_KABUKI_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouKabukiTrim,
  [SPECIES_FURFROU_PHARAOH_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //FurfrouPharaohTrim,
  [SPECIES_MEOWSTIC_FEMALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MeowsticFemale,
  [SPECIES_AEGISLASH_BLADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //AegislashBlade,
  [SPECIES_PUMPKABOO_SMALL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pumpkaboo,
  [SPECIES_PUMPKABOO_LARGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pumpkaboo,
  [SPECIES_PUMPKABOO_SUPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Pumpkaboo,
  [SPECIES_GOURGEIST_SMALL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gourgeist,
  [SPECIES_GOURGEIST_LARGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gourgeist,
  [SPECIES_GOURGEIST_SUPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Gourgeist,
  [SPECIES_XERNEAS_ACTIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //XerneasActive,
  [SPECIES_ZYGARDE_10] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zygarde10,
  [SPECIES_ZYGARDE_10_POWER_CONSTRUCT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zygarde10,
  [SPECIES_ZYGARDE_50_POWER_CONSTRUCT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zygarde,
  [SPECIES_ZYGARDE_COMPLETE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //ZygardeComplete,
  [SPECIES_HOOPA_UNBOUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //HoopaUnbound,
  [SPECIES_ORICORIO_POM_POM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //OricorioPomPom,
  [SPECIES_ORICORIO_PAU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //OricorioPau,
  [SPECIES_ORICORIO_SENSU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //OricorioSensu,
  [SPECIES_LYCANROC_MIDNIGHT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LycanrocMidnight,
  [SPECIES_LYCANROC_DUSK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //LycanrocDusk,
  [SPECIES_WISHIWASHI_SCHOOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //WishiwashiSchool,
  [SPECIES_SILVALLY_FIGHTING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_FLYING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_POISON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_GROUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_ROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_BUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_GHOST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_STEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_FIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_WATER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_GRASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_ELECTRIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_PSYCHIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_ICE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_DRAGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_DARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_SILVALLY_FAIRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Silvally,
  [SPECIES_MINIOR_METEOR_ORANGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_YELLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_GREEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_BLUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_INDIGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_VIOLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Minior,
  [SPECIES_MINIOR_CORE_RED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreRed,
  [SPECIES_MINIOR_CORE_ORANGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreOrange,
  [SPECIES_MINIOR_CORE_YELLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreYellow,
  [SPECIES_MINIOR_CORE_GREEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreGreen,
  [SPECIES_MINIOR_CORE_BLUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreBlue,
  [SPECIES_MINIOR_CORE_INDIGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreIndigo,
  [SPECIES_MINIOR_CORE_VIOLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MiniorCoreViolet,
  [SPECIES_MIMIKYU_BUSTED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MimikyuBusted,
  [SPECIES_NECROZMA_DUSK_MANE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //NecrozmaDuskMane,
  [SPECIES_NECROZMA_DAWN_WINGS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //NecrozmaDawnWings,
  [SPECIES_NECROZMA_ULTRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //NecrozmaUltra,
  [SPECIES_MAGEARNA_ORIGINAL_COLOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //MagearnaOriginalColor,
  [SPECIES_CRAMORANT_GULPING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cramorant_Gulping,
  [SPECIES_CRAMORANT_GORGING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Cramorant_Gorging,
  [SPECIES_TOXTRICITY_LOW_KEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Toxtricity_Low_key,
      //[SPECIES_SINISTEA_ANTIQUE]                = gMonIcon_Sinistea_Antique,
      //[SPECIES_POLTEAGEIST_ANTIQUE]             = gMonIcon_PolteaGeist_Antique,
    [SPECIES_ALCREMIE_RUBY_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_ruby,
    [SPECIES_ALCREMIE_MATCHA_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_matcha,
    [SPECIES_ALCREMIE_MINT_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_mint,
    [SPECIES_ALCREMIE_LEMON_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_lemon,
    [SPECIES_ALCREMIE_SALTED_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_salt,
    [SPECIES_ALCREMIE_RUBY_SWIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_ruby_swirl,
    [SPECIES_ALCREMIE_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_caramel_swirl,
    [SPECIES_ALCREMIE_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Alcremie_rainbow_swirl,
    [SPECIES_EISCUE_NOICE_FACE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eiscue_noice_face,
    [SPECIES_INDEEDEE_FEMALE] = 
    {  
      FRONT_PIC(Indeedee_Female),
      FRONT_COORD(0x88,0),
      BACK_PIC(Indeedee_Female),
      BACK_COORD(0x88,0),
      PALETTES(Indeedee_Female),
      ICON(Indeedee_Female,0),
      TAG(SPECIES_NONE),
    }, //Indeedee_Female,
    [SPECIES_MORPEKO_HANGRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Morpeko_Hangry,
    [SPECIES_ZACIAN_CROWNED_SWORD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zacian_Crowned_Sword,
    [SPECIES_ZAMAZENTA_CROWNED_SHIELD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zamazenta_Crowned_Shield,
    [SPECIES_ETERNATUS_ETERNAMAX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Eternatus_Eternamax,
    [SPECIES_URSHIFU_RAPID_STRIKE_STYLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Urshifu_Rapid, //think last value needs no comma, nope doesn't matter but using comma is better in case you plan to add more
    [SPECIES_ZARUDE_DADA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
      TAG(SPECIES_NONE),
    }, //Zarude_Dada,
    [SPECIES_CALYREX_ICE_RIDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(Calyrex_Ice_Rider,0),
      TAG(SPECIES_NONE),
    }, //Calyrex_Ice_Rider,
    [SPECIES_CALYREX_SHADOW_RIDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CalyrexShadowRider),
      ICON(Calyrex_Shadow_Rider,0), //names w dashes are in icons only, can be pushsed to pallete and front/back pics
    }, //Calyrex_Shadow_Rider,
    [SPECIES_BASCULEGION_FEMALE] = 
    {  
      FRONT_PIC(BasculegionFemale),
      FRONT_COORD(0x88,0),
      BACK_PIC(BasculegionFemale),
      BACK_COORD(0x88,0),
      PALETTES(BasculegionFemale),
      ICON(BasculegionFemale,0),
      TAG(SPECIES_NONE),
    }, //BasculegionFemale,
    [SPECIES_FRILLISH_FEMALE] = 
    {  
      FRONT_PIC(BasculegionFemale),
      FRONT_COORD(0x88,0),
      BACK_PIC(BasculegionFemale),
      BACK_COORD(0x88,0),
      PALETTES(BasculegionFemale),
      ICON(BasculegionFemale,0),
      TAG(SPECIES_NONE),
    }, //BasculegionFemale,
    [SPECIES_JELLICENT_FEMALE] = 
    {  
      FRONT_PIC(BasculegionFemale),
      FRONT_COORD(0x88,0),
      BACK_PIC(BasculegionFemale),
      BACK_COORD(0x88,0),
      PALETTES(BasculegionFemale),
      ICON(BasculegionFemale,0),
      TAG(SPECIES_NONE),
    }, //BasculegionFemale,
};
