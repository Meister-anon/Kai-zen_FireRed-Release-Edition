const struct MonCoords gTrainerBackPicCoords[] = {
    [BACK_PIC_RED] = {.size = 8, .y_offset = 5},
    [BACK_PIC_LEAF] = {.size = 8, .y_offset = 5},
    [BACK_PIC_RS_BRENDAN] = {.size = 8, .y_offset = 4},
    [BACK_PIC_RS_MAY] = {.size = 8, .y_offset = 4},
    [BACK_PIC_POKEDUDE] = {.size = 8, .y_offset = 4},
    [BACK_PIC_OLDMAN] = {.size = 8, .y_offset = 4}
};

const struct CompressedSpriteSheet gTrainerBackPicTable[] = {
    [BACK_PIC_RED] = { (const u32 *)gTrainerBackPic_Red, 0x2800, 0 },
    [BACK_PIC_LEAF] = { (const u32 *)gTrainerBackPic_Leaf, 0x2800, 1 },
    [BACK_PIC_RS_BRENDAN] = { (const u32 *)gTrainerBackPic_RSBrendan, 0x2000, 2 },
    [BACK_PIC_RS_MAY] = { (const u32 *)gTrainerBackPic_RSMay, 0x2000, 3 },
    [BACK_PIC_POKEDUDE] = { (const u32 *)gTrainerBackPic_Pokedude, 0x2000, 4 },
    [BACK_PIC_OLDMAN] = { (const u32 *)gTrainerBackPic_OldMan, 0x2000, 5 }
};

const struct SpritePalette gTrainerBackPicPaletteTable[] = {
    [BACK_PIC_RED] = { gTrainerPalette_RedBackPic, 0 },
    [BACK_PIC_LEAF] = { gTrainerPalette_LeafBackPic, 1 },
    [BACK_PIC_RS_BRENDAN] = { gTrainerPalette_RSBrendan1, 2 },
    [BACK_PIC_RS_MAY] = { gTrainerPalette_RSMay1, 3 },
    [BACK_PIC_POKEDUDE] = { gTrainerPalette_PokedudeBackPic, 4 },
    [BACK_PIC_OLDMAN] = { gTrainerPalette_OldManBackPic, 5 }
};
