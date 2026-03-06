#include "global.h"
#include "main.h"
#include "palette.h"
#include "string_util.h"
#include "window.h"
#include "text.h"
#include "blit.h"

static EWRAM_DATA struct TextPrinter sTempTextPrinter = {0};
static EWRAM_DATA struct TextPrinter sTextPrinters[NUM_TEXT_PRINTERS] = {0};

static u16 sFontHalfRowLookupTable[0x51];
static u16 sLastTextBgColor;
static u16 sLastTextFgColor;
static u16 sLastTextShadowColor;

COMMON_DATA const struct FontInfo *gFonts = NULL;
COMMON_DATA struct GlyphInfo gGlyphInfo = {0};

static const u8 sFontHalfRowOffsets[] =
{
    0x00, 0x01, 0x02, 0x00, 0x03, 0x04, 0x05, 0x03, 0x06, 0x07, 0x08, 0x06, 0x00, 0x01, 0x02, 0x00,
    0x09, 0x0A, 0x0B, 0x09, 0x0C, 0x0D, 0x0E, 0x0C, 0x0F, 0x10, 0x11, 0x0F, 0x09, 0x0A, 0x0B, 0x09,
    0x12, 0x13, 0x14, 0x12, 0x15, 0x16, 0x17, 0x15, 0x18, 0x19, 0x1A, 0x18, 0x12, 0x13, 0x14, 0x12,
    0x00, 0x01, 0x02, 0x00, 0x03, 0x04, 0x05, 0x03, 0x06, 0x07, 0x08, 0x06, 0x00, 0x01, 0x02, 0x00,
    0x1B, 0x1C, 0x1D, 0x1B, 0x1E, 0x1F, 0x20, 0x1E, 0x21, 0x22, 0x23, 0x21, 0x1B, 0x1C, 0x1D, 0x1B,
    0x24, 0x25, 0x26, 0x24, 0x27, 0x28, 0x29, 0x27, 0x2A, 0x2B, 0x2C, 0x2A, 0x24, 0x25, 0x26, 0x24,
    0x2D, 0x2E, 0x2F, 0x2D, 0x30, 0x31, 0x32, 0x30, 0x33, 0x34, 0x35, 0x33, 0x2D, 0x2E, 0x2F, 0x2D,
    0x1B, 0x1C, 0x1D, 0x1B, 0x1E, 0x1F, 0x20, 0x1E, 0x21, 0x22, 0x23, 0x21, 0x1B, 0x1C, 0x1D, 0x1B,
    0x36, 0x37, 0x38, 0x36, 0x39, 0x3A, 0x3B, 0x39, 0x3C, 0x3D, 0x3E, 0x3C, 0x36, 0x37, 0x38, 0x36,
    0x3F, 0x40, 0x41, 0x3F, 0x42, 0x43, 0x44, 0x42, 0x45, 0x46, 0x47, 0x45, 0x3F, 0x40, 0x41, 0x3F,
    0x48, 0x49, 0x4A, 0x48, 0x4B, 0x4C, 0x4D, 0x4B, 0x4E, 0x4F, 0x50, 0x4E, 0x48, 0x49, 0x4A, 0x48,
    0x36, 0x37, 0x38, 0x36, 0x39, 0x3A, 0x3B, 0x39, 0x3C, 0x3D, 0x3E, 0x3C, 0x36, 0x37, 0x38, 0x36,
    0x00, 0x01, 0x02, 0x00, 0x03, 0x04, 0x05, 0x03, 0x06, 0x07, 0x08, 0x06, 0x00, 0x01, 0x02, 0x00,
    0x09, 0x0A, 0x0B, 0x09, 0x0C, 0x0D, 0x0E, 0x0C, 0x0F, 0x10, 0x11, 0x0F, 0x09, 0x0A, 0x0B, 0x09,
    0x12, 0x13, 0x14, 0x12, 0x15, 0x16, 0x17, 0x15, 0x18, 0x19, 0x1A, 0x18, 0x12, 0x13, 0x14, 0x12,
    0x00, 0x01, 0x02, 0x00, 0x03, 0x04, 0x05, 0x03, 0x06, 0x07, 0x08, 0x06, 0x00, 0x01, 0x02, 0x00
};

void SetFontsPointer(const struct FontInfo *fonts)
{
    gFonts = fonts;
}

void DeactivateAllTextPrinters (void)
{
    int printer;
    for (printer = 0; printer < NUM_TEXT_PRINTERS; ++printer)
        sTextPrinters[printer].active = 0;
}

u16 AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.currentChar = str;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = fontId;
    printerTemplate.x = x;
    printerTemplate.y = y;
    printerTemplate.currentX = x;
    printerTemplate.currentY = y;
    printerTemplate.letterSpacing = gFonts[fontId].letterSpacing;
    printerTemplate.lineSpacing = gFonts[fontId].lineSpacing;
    printerTemplate.color.accent = gFonts[fontId].color.accent;
    printerTemplate.color.foreground = gFonts[fontId].color.foreground;
    printerTemplate.color.background = gFonts[fontId].color.background;
    printerTemplate.color.shadow = gFonts[fontId].color.shadow;
    return AddTextPrinter(&printerTemplate, speed, callback);
}

bool16 AddTextPrinter(struct TextPrinterTemplate *textSubPrinter, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    int i;
    u16 j;

    if (!gFonts)
        return FALSE;

    sTempTextPrinter.active = TRUE;
    sTempTextPrinter.state = RENDER_STATE_HANDLE_CHAR;
    sTempTextPrinter.textSpeed = speed;
    sTempTextPrinter.delayCounter = 0;
    sTempTextPrinter.scrollDistance = 0;

    for (i = 0; i < (int)ARRAY_COUNT(sTempTextPrinter.subStructFields); ++i)
    {
        sTempTextPrinter.subStructFields[i] = 0;
    }

    sTempTextPrinter.printerTemplate = *textSubPrinter;
    sTempTextPrinter.callback = callback;
    sTempTextPrinter.minLetterSpacing = sTempTextPrinter.printerTemplate.letterSpacing;
    sTempTextPrinter.japanese = 0;

    GenerateFontHalfRowLookupTable(textSubPrinter->color.foreground, textSubPrinter->color.background, textSubPrinter->color.shadow);
    if (speed != TEXT_SKIP_DRAW && speed != 0x0)
    {
        --sTempTextPrinter.textSpeed;
        sTextPrinters[textSubPrinter->windowId] = sTempTextPrinter;
    }
    else
    {
        sTempTextPrinter.textSpeed = 0;

        // Render all text (up to limit) at once
        for (j = 0; j < 0x400; ++j)
        {
            if ((u32)RenderFont(&sTempTextPrinter) == RENDER_FINISH)
                break;
        }

        // All the text is rendered to the window but don't draw it yet.
        if (speed != TEXT_SKIP_DRAW)
          CopyWindowToVram(sTempTextPrinter.printerTemplate.windowId, COPYWIN_GFX);
        sTextPrinters[textSubPrinter->windowId].active = FALSE;
    }
    return TRUE;
}

void RunTextPrinters(void)
{
    int i;


    for (i = 0; i < WINDOWS_MAX; ++i) //DON'T NKOW how this constant is relevant?
    {
        if (sTextPrinters[i].active != 0)
        {
            u16 renderCmd = RenderFont(&sTextPrinters[i]);
            CopyWindowToVram(sTextPrinters[i].printerTemplate.windowId, COPYWIN_GFX); //change ellabrella faster text
            switch (renderCmd) { 
                case RENDER_PRINT:
                case RENDER_UPDATE:
                    if (sTextPrinters[i].callback != 0)
                        sTextPrinters[i].callback(&sTextPrinters[i].printerTemplate, renderCmd);
                    break;
                case RENDER_FINISH:
                    sTextPrinters[i].active = 0;
                    break;
            }
        }
    }
}

bool16 IsTextPrinterActive(u8 id)
{
    return sTextPrinters[id].active;
}

u32 RenderFont(struct TextPrinter *textPrinter)
{
    u32 ret;
    while (TRUE)
    {
        ret = gFonts[textPrinter->printerTemplate.fontId].fontFunction(textPrinter);
        if (ret != RENDER_REPEAT)
            return ret;
    }
}

void GenerateFontHalfRowLookupTable(u8 fgColor, u8 bgColor, u8 shadowColor)
{
    int lutIndex;
    int i, j, k, l;
    const u32 colors[] = {bgColor, fgColor, shadowColor};

    sLastTextBgColor = bgColor;
    sLastTextFgColor = fgColor;
    sLastTextShadowColor = shadowColor;

    lutIndex = 0;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                for (l = 0; l < 3; l++)
                    sFontHalfRowLookupTable[lutIndex++] = (colors[l] << 12) | (colors[k] << 8) | (colors[j] << 4) | colors[i];
}

void SaveTextColors(u8 *fgColor, u8 *bgColor, u8 *shadowColor)
{
    *bgColor = sLastTextBgColor;
    *fgColor = sLastTextFgColor;
    *shadowColor = sLastTextShadowColor;
}

void RestoreTextColors(u8 *fgColor, u8 *bgColor, u8 *shadowColor)
{
    GenerateFontHalfRowLookupTable(*fgColor, *bgColor, *shadowColor);
}

void DecompressGlyphTile(const void *src_, void *dest_)
{
    u32 temp;
    const u16 *src = src_;
    u32 *dest = dest_;

    temp = *(src++);
    *(dest)++ = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);

    temp = *(src++);
    *(dest++) = ((sFontHalfRowLookupTable[sFontHalfRowOffsets[temp & 0xFF]]) << 16) | (sFontHalfRowLookupTable[sFontHalfRowOffsets[temp >> 8]]);
}


u8 GetLastTextColor(u8 colorType)
{
    switch (colorType)
    {
        case 0:
            return sLastTextFgColor;
        case 2:
            return sLastTextBgColor;
        case 1:
            return sLastTextShadowColor;
        default:
            return 0;
    }
}

inline static void GLYPH_COPY(u8 *windowTiles, u32 widthOffset, u32 j, u32 i, u32 *glyphPixels, s32 width, s32 height)
{
    u32 xAdd, yAdd, pixelData, bits, toOrr, dummyX;
    u8 *dst;

    xAdd = j + width;
    yAdd = i + height;
    dummyX = j;
    for (; i < yAdd; i++)
    {
        pixelData = *glyphPixels++;
        for (j = dummyX; j < xAdd; j++)
        {
            if ((toOrr = pixelData & 0xF))
            {
                dst = windowTiles + ((j / 8) * 32) + ((j % 8) / 2) + ((i / 8) * widthOffset) + ((i % 8) * 4);
                bits = ((j & 1) * 4);
                *dst = (toOrr << bits) | (*dst & (0xF0 >> bits));
            }
            pixelData >>= 4;
        }
    }
}

void CopyGlyphToWindow(struct TextPrinter *textPrinter)
{
    struct Window *window;
    struct WindowTemplate *template;
    u32 *glyphPixels;
    u32 currX, currY, widthOffset;
    s32 glyphWidth, glyphHeight;
    u8 *windowTiles;

    window = &gWindows[textPrinter->printerTemplate.windowId];
    template = &window->window;

    if ((glyphWidth = (template->width * 8) - textPrinter->printerTemplate.currentX) > gGlyphInfo.width)
        glyphWidth = gGlyphInfo.width;

    if ((glyphHeight = (template->height * 8) - textPrinter->printerTemplate.currentY) > gGlyphInfo.height)
        glyphHeight = gGlyphInfo.height;

    currX = textPrinter->printerTemplate.currentX;
    currY = textPrinter->printerTemplate.currentY;
    glyphPixels = gGlyphInfo.gfxBufferTop;
    windowTiles = window->tileData;
    widthOffset = template->width * 32;

    if (glyphWidth < 9)
    {
        if (glyphHeight < 9)
        {
            GLYPH_COPY(windowTiles, widthOffset, currX, currY, glyphPixels, glyphWidth, glyphHeight);
        }
        else
        {
            GLYPH_COPY(windowTiles, widthOffset, currX, currY, glyphPixels, glyphWidth, 8);
            GLYPH_COPY(windowTiles, widthOffset, currX, currY + 8, glyphPixels + 16, glyphWidth, glyphHeight - 8);
        }
    }
    else
    {
        if (glyphHeight < 9)
        {
            GLYPH_COPY(windowTiles, widthOffset, currX, currY, glyphPixels, 8, glyphHeight);
            GLYPH_COPY(windowTiles, widthOffset, currX + 8, currY, glyphPixels + 8, glyphWidth - 8, glyphHeight);
        }
        else
        {
            GLYPH_COPY(windowTiles, widthOffset, currX, currY, glyphPixels, 8, 8);
            GLYPH_COPY(windowTiles, widthOffset, currX + 8, currY, glyphPixels + 8, glyphWidth - 8, 8);
            GLYPH_COPY(windowTiles, widthOffset, currX, currY + 8, glyphPixels + 16, 8, glyphHeight - 8);
            GLYPH_COPY(windowTiles, widthOffset, currX + 8, currY + 8, glyphPixels + 24, glyphWidth - 8, glyphHeight - 8);
        }
    }
}

//does'nt appear to be called? //yeah unusued
void CopyGlyphToWindow_Parameterized(void * tileData, u16 currentX, u16 currentY, u16 width, u16 height)
{
    int r0, r1;
    u8 r2;
    u16 r3;
    
    if (width - currentX < gGlyphInfo.width)
        r0 = width - currentX;
    else
        r0 = gGlyphInfo.width;
    if (height - currentY < gGlyphInfo.height)
        r1 = height - currentY;
    else
        r1 = gGlyphInfo.height;
    
    r2 = 0;
    r3  = (width + (width & 7)) >> 3;
    if (r0 > 8)
        r2 |= 1;
    if (r1 > 8)
        r2 |= 2;
    
    /*switch (r2)
    {
        case 0:
            GLYPH_COPY(0, 0, r0, r1, tileData, currentX, currentY, r3);
            return;
        case 1:
            GLYPH_COPY(0, 0, 8, r1, tileData, currentX, currentY, r3);
            GLYPH_COPY(8, 0, r0 - 8, r1, tileData, currentX, currentY, r3);
            return;
        case 2:
            GLYPH_COPY(0, 0, r0, 8, tileData, currentX, currentY, r3);
            GLYPH_COPY(0, 8, r0, r1 - 8, tileData, currentX, currentY, r3);
            return;
        case 3:
            GLYPH_COPY(0, 0, 8, 8, tileData, currentX, currentY, r3);
            GLYPH_COPY(8, 0, r0 - 8, 8, tileData, currentX, currentY, r3);
            GLYPH_COPY(0, 8, 8, r1 - 8, tileData, currentX, currentY, r3);
            GLYPH_COPY(8, 8, r0 - 8, r1 - 8, tileData, currentX, currentY, r3);
            return;
    }*/
}

void ClearTextSpan(struct TextPrinter *textPrinter, u32 width)
{
}

// this is an implementation of text clearing that RSE uses
void ClearTextSpanDebug(struct TextPrinter *textPrinter, u32 width)
{
    struct Window *window;
    struct Bitmap pixels_data;
    struct GlyphInfo *glyph;
    u8 *glyphHeight;

    if (sLastTextBgColor != TEXT_COLOR_TRANSPARENT)
    {
        window = &gWindows[textPrinter->printerTemplate.windowId];
        pixels_data.pixels = window->tileData;
        pixels_data.width = window->window.width << 3;
        pixels_data.height = window->window.height << 3;

        glyph = &gGlyphInfo;
        glyphHeight = &glyph->height;

        FillBitmapRect4Bit(
            &pixels_data,
            textPrinter->printerTemplate.currentX,
            textPrinter->printerTemplate.currentY,
            width,
            *glyphHeight,
            sLastTextBgColor);
    }
}
