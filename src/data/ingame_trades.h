static const struct InGameTrade sInGameTrades[] = {
    [INGAME_TRADE_MR_MIME] = 
    {
        .nickname = _("MIMIEN"),
        .species = SPECIES_MR_MIME,
        .ivs = {20, 15, 17, 24, 23, 22}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,    //would like to have a way to randomize these  //redistribute all Ivs for best options, and change ability from base, 
        .otId = 1985,
        .contestStats = {5, 5, 5, 30, 5}, //conditions are the contest stats
        .personality = 0x00009cae,
        .heldItem = ITEM_NONE,
        //.mailNum = 255,
        .otName = _("REYLEY"),
        .otGender = MALE, //replaced mailNum set removed mail items on jynx, may use trades as a way to get rare items
        //.sheen = 10,
        .requestedSpecies = SPECIES_ABRA
    }, 
    [INGAME_TRADE_JYNX] = 
    {
        .nickname = _("ZYNX"),
        .species = SPECIES_JYNX,
        .ivs = {18, 17, 18, 22, 25, 21}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 36728,
        .contestStats = {5, 30, 5, 5, 5},
        .personality = 0x498a2e1d,
        .heldItem = ITEM_NONE,
        //.mailNum = 0,
        .otName = _("DONTAE"),
        .otGender = MALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_POLIWHIRL
    }, 
    [INGAME_TRADE_ZIGZAGOON] = 
    {
#if defined(FIRERED)
        .nickname = _("WILD CAT"),
        .species = SPECIES_ZIGZAGOON_GALARIAN,
        .ivs = {22, 18, 25, 19, 15, 22}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 2,
        .otId = 63184,
        .contestStats = {5, 5, 5, 5, 30},
        .personality = 0x4c970b89,
        .heldItem = ITEM_BLACK_GLASSES,
        //.mailNum = 255,
        .otName = _("SAIGE"),
        .otGender = FEMALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_RATTATA
#elif defined(LEAFGREEN)
        .nickname = _("TOM CAT"),
        .species = SPECIES_ZIGZAGOON_GALARIAN,
        .ivs = {19, 25, 18, 22, 22, 15}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 2,
        .otId = 63184,
        .contestStats = {30, 5, 5, 5, 5},
        .personality = 0x4c970b9e,
        .heldItem = ITEM_BLACK_GLASSES,
        //.mailNum = 255,
        .otName = _("SAIGE"),
        .otGender = FEMALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_RATTATA
#endif
    }, 
    [INGAME_TRADE_FARFETCHD] = 
    {
        .nickname = _("CH'DING"),
        .species = SPECIES_FARFETCHD,
        .ivs = {20, 25, 21, 24, 15, 20}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 8810,
        .contestStats = {30, 5, 5, 5, 5},
        .personality = 0x151943d7,
        .heldItem = ITEM_LEEK,
        //.mailNum = 255,
        .otName = _("ELYSSA"),
        .otGender = MALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_SPEAROW
    }, 
    [INGAME_TRADE_NIDORINOA] = 
    {
#if defined(FIRERED)
        .nickname = _("NINA"),
        .species = SPECIES_NIDORINA,
        .ivs = {22, 25, 18, 19, 22, 15}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 13637,
        .contestStats = {5, 5, 30, 5, 5},
        .personality = 0x00eeca15,
        .heldItem = ITEM_NONE,
        //.mailNum = 255,
        .otName = _("TURNER"),
        .otGender = MALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_NIDORINO
#elif defined(LEAFGREEN)
        .nickname = _("NINO"),
        .species = SPECIES_NIDORINO,
        .ivs = {19, 18, 25, 22, 15, 22}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 13637,
        .contestStats = {5, 5, 5, 5, 30},
        .personality = 0x00eeca19,
        .heldItem = ITEM_NONE,
        //.mailNum = 255,
        .otName = _("TURNER"),
        .otGender = MALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_NIDORINA
#endif
    }, 
    [INGAME_TRADE_LICKITUNG] = 
    {
        .nickname = _("MARC"),
        .species = SPECIES_LICKITUNG,
        .ivs = {24, 19, 21, 15, 23, 21}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 1239,
        .contestStats = {5, 5, 5, 5, 30},
        .personality = 0x451308ab,
        .heldItem = ITEM_NONE,
        //.mailNum = 255,
        .otName = _("HADEN"),
        .otGender = MALE,
        //.sheen = 10,
#if defined(FIRERED)
        .requestedSpecies = SPECIES_GOLDUCK
#elif defined(LEAFGREEN)
        .requestedSpecies = SPECIES_SLOWBRO
#endif
    }, 
    [INGAME_TRADE_ELECTRODE] = 
    {
        .nickname = _("ESPHERE"),
        .species = SPECIES_ELECTRODE,
        .ivs = {19, 16, 18, 25, 25, 19}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 1,
        .otId = 50298,
        .contestStats = {30, 5, 5, 5, 5},
        .personality = 0x06341016,
        .heldItem = ITEM_NONE,
        //.mailNum = 255,
        .otName = _("CLIFTON"),
        .otGender = MALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_RAICHU
    }, 
    [INGAME_TRADE_TANGELA] = 
    {
        .nickname = _("TANGENY"),
        .species = SPECIES_TANGELA,
        .ivs = {22, 17, 25, 16, 23, 20}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 60042,
        .contestStats = {5, 5, 30, 5, 5},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_STARDUST,
        //.mailNum = 255,
        .otName = _("NORMA"),
        .otGender = FEMALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_VENONAT
    },
    [INGAME_TRADE_SEEL] = 
    {
        .nickname = _("SEELOR"),
        .species = SPECIES_SEEL,
        .ivs = {24, 15, 22, 16, 23, 22}, //hp, atk, def, speed, spatk, spdef
        .abilityNum = 0,
        .otId = 9853,
        .contestStats = {5, 5, 5, 5, 30},
        .personality = 0x482cac89,
        .heldItem = ITEM_NONE,
        //.mailNum = 255,
        .otName = _("GARETT"),
        .otGender = MALE,
        //.sheen = 10,
        .requestedSpecies = SPECIES_PONYTA
    }
};

/*static const u16 sInGameTradeMailMessages[][10] = {
    {
        EC_WORD_THAT_S,
        EC_WORD_A,
        EC_WORD_HEALTHY,
        EC_POKEMON(JYNX),
        EC_WORD_EXCL,
        EC_WORD_BE,
        EC_WORD_KIND,
        EC_WORD_TO,
        EC_WORD_IT
    }
};*/
