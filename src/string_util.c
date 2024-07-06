#include "global.h"
#include "gflib.h"
#include "event_data.h"  //needed to load flag check


EWRAM_DATA u8 gStringVar1[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)] = {};
EWRAM_DATA u8 gStringVar2[20] = {};
EWRAM_DATA u8 gStringVar3[20] = {};
EWRAM_DATA u8 gStringVar4[1000] = {};
EWRAM_DATA u8 gUnknownStringVar[16] = {0};

static const u8 sDigits[] = __("0123456789ABCDEF");

static const s32 sPowersOfTen[] =
{
             1,
            10,
           100,
          1000,
         10000,
        100000,
       1000000,
      10000000,
     100000000,
    1000000000,
};

//all values not defined
const u8 gCaseToggleTable[239] = {
    [CHAR_A] = CHAR_a,
    [CHAR_B] = CHAR_b,
    [CHAR_C] = CHAR_c,
    [CHAR_D] = CHAR_d,
    [CHAR_E] = CHAR_e,
    [CHAR_F] = CHAR_f,
    [CHAR_G] = CHAR_g,
    [CHAR_H] = CHAR_h,
    [CHAR_I] = CHAR_i,
    [CHAR_J] = CHAR_j,
    [CHAR_K] = CHAR_k,
    [CHAR_L] = CHAR_l,
    [CHAR_M] = CHAR_m,
    [CHAR_N] = CHAR_n,
    [CHAR_O] = CHAR_o,
    [CHAR_P] = CHAR_p,
    [CHAR_Q] = CHAR_q,
    [CHAR_R] = CHAR_r,
    [CHAR_S] = CHAR_s,
    [CHAR_T] = CHAR_t,
    [CHAR_U] = CHAR_u,
    [CHAR_V] = CHAR_v,
    [CHAR_W] = CHAR_w,
    [CHAR_X] = CHAR_x,
    [CHAR_Y] = CHAR_y,
    [CHAR_Z] = CHAR_z,
    [CHAR_a] = CHAR_A,
    [CHAR_b] = CHAR_B,
    [CHAR_c] = CHAR_C,
    [CHAR_d] = CHAR_D,
    [CHAR_e] = CHAR_E,
    [CHAR_f] = CHAR_F,
    [CHAR_g] = CHAR_G,
    [CHAR_h] = CHAR_H,
    [CHAR_i] = CHAR_I,
    [CHAR_j] = CHAR_J,
    [CHAR_k] = CHAR_K,
    [CHAR_l] = CHAR_L,
    [CHAR_m] = CHAR_M,
    [CHAR_n] = CHAR_N,
    [CHAR_o] = CHAR_O,
    [CHAR_p] = CHAR_P,
    [CHAR_q] = CHAR_Q,
    [CHAR_r] = CHAR_R,
    [CHAR_s] = CHAR_S,
    [CHAR_t] = CHAR_T,
    [CHAR_u] = CHAR_U,
    [CHAR_v] = CHAR_V,
    [CHAR_w] = CHAR_W,
    [CHAR_x] = CHAR_X,
    [CHAR_y] = CHAR_Y,
    [CHAR_z] = CHAR_Z,
    /*[CHAR_A_GRAVE] = CHAR_a_GRAVE,
    [CHAR_A_ACUTE] = CHAR_a_ACUTE,
    [CHAR_A_CIRCUMFLEX] = CHAR_a_CIRCUMFLEX,
    [CHAR_A_DIAERESIS] = CHAR_a_DIAERESIS,
    [CHAR_C_CEDILLA] = CHAR_c_CEDILLA,
    [CHAR_E_GRAVE] = CHAR_e_GRAVE,
    [CHAR_E_ACUTE] = CHAR_e_ACUTE,
    [CHAR_E_CIRCUMFLEX] = CHAR_e_CIRCUMFLEX,
    [CHAR_E_DIAERESIS] = CHAR_e_DIAERESIS,
    [CHAR_I_GRAVE] = CHAR_i_GRAVE,
    [CHAR_I_ACUTE] = CHAR_i_ACUTE,
    [CHAR_I_CIRCUMFLEX] = CHAR_i_CIRCUMFLEX,
    [CHAR_I_DIAERESIS] = CHAR_i_DIAERESIS,
    [CHAR_O_GRAVE] = CHAR_o_GRAVE,
    [CHAR_O_ACUTE] = CHAR_o_ACUTE,
    [CHAR_O_CIRCUMFLEX] = CHAR_o_CIRCUMFLEX,
    [CHAR_O_DIAERESIS] = CHAR_o_DIAERESIS,
    [CHAR_OE] = CHAR_oe,
    [CHAR_U_GRAVE] = CHAR_u_GRAVE,
    [CHAR_U_ACUTE] = CHAR_u_ACUTE,
    [CHAR_U_CIRCUMFLEX] = CHAR_u_CIRCUMFLEX,
    [CHAR_U_DIAERESIS] = CHAR_u_DIAERESIS,
    [CHAR_N_TILDE] = CHAR_n_TILDE,
    [CHAR_ESZETT] = CHAR_ESZETT,
    [CHAR_a_GRAVE] = CHAR_A_GRAVE,
    [CHAR_a_ACUTE] = CHAR_A_ACUTE,
    [CHAR_a_CIRCUMFLEX] = CHAR_A_CIRCUMFLEX,
    [CHAR_a_DIAERESIS] = CHAR_A_DIAERESIS,
    [CHAR_c_CEDILLA] = CHAR_C_CEDILLA,
    [CHAR_e_GRAVE] = CHAR_E_GRAVE,
    [CHAR_e_ACUTE] = CHAR_E_ACUTE,
    [CHAR_e_CIRCUMFLEX] = CHAR_E_CIRCUMFLEX,
    [CHAR_e_DIAERESIS] = CHAR_E_DIAERESIS,
    [CHAR_i_GRAVE] = CHAR_I_GRAVE,
    [CHAR_i_ACUTE] = CHAR_I_ACUTE,
    [CHAR_i_CIRCUMFLEX] = CHAR_I_CIRCUMFLEX,
    [CHAR_i_DIAERESIS] = CHAR_I_DIAERESIS,
    [CHAR_o_GRAVE] = CHAR_O_GRAVE,
    [CHAR_o_ACUTE] = CHAR_O_ACUTE,
    [CHAR_o_CIRCUMFLEX] = CHAR_O_CIRCUMFLEX,
    [CHAR_o_DIAERESIS] = CHAR_O_DIAERESIS,
    [CHAR_oe] = CHAR_OE,
    [CHAR_u_GRAVE] = CHAR_U_GRAVE,
    [CHAR_u_ACUTE] = CHAR_U_ACUTE,
    [CHAR_u_CIRCUMFLEX] = CHAR_U_CIRCUMFLEX,
    [CHAR_u_DIAERESIS] = CHAR_U_DIAERESIS,
    [CHAR_n_TILDE] = CHAR_N_TILDE,
    [CHAR_0] = CHAR_0,
    [CHAR_1] = CHAR_1,
    [CHAR_2] = CHAR_2,
    [CHAR_3] = CHAR_3,
    [CHAR_4] = CHAR_4,
    [CHAR_5] = CHAR_5,
    [CHAR_6] = CHAR_6,
    [CHAR_7] = CHAR_7,
    [CHAR_8] = CHAR_8,
    [CHAR_9] = CHAR_9,
    [CHAR_PK] = CHAR_PK,
    [CHAR_MN] = CHAR_MN,
    [CHAR_PO] = CHAR_PO,
    [CHAR_KE] = CHAR_KE,
    [CHAR_SUPER_E]  = CHAR_SUPER_E,
    [CHAR_SUPER_ER] = CHAR_SUPER_ER,
    [CHAR_SUPER_RE] = CHAR_SUPER_RE,
    [CHAR_PERIOD] = CHAR_PERIOD,
    [CHAR_COMMA] = CHAR_COMMA,
    [CHAR_COLON] = CHAR_COLON,
    [CHAR_SEMICOLON] = CHAR_SEMICOLON,
    [CHAR_EXCL_MARK] = CHAR_EXCL_MARK,
    [CHAR_QUESTION_MARK] = CHAR_QUESTION_MARK,
    [CHAR_HYPHEN] = CHAR_HYPHEN,
    [CHAR_SLASH] = CHAR_SLASH,
    [CHAR_ELLIPSIS] = CHAR_ELLIPSIS,
    [CHAR_LEFT_PAREN] = CHAR_LEFT_PAREN,
    [CHAR_RIGHT_PAREN] = CHAR_RIGHT_PAREN,
    [CHAR_AMPERSAND] = CHAR_AMPERSAND,
    [CHAR_DBL_QUOTE_LEFT] = CHAR_DBL_QUOTE_LEFT,
    [CHAR_DBL_QUOTE_RIGHT] = CHAR_DBL_QUOTE_RIGHT,
    [CHAR_SGL_QUOTE_LEFT] = CHAR_SGL_QUOTE_LEFT,
    [CHAR_SGL_QUOTE_RIGHT] = CHAR_SGL_QUOTE_RIGHT,
    [CHAR_MASCULINE_ORDINAL] = CHAR_MASCULINE_ORDINAL,
    [CHAR_FEMININE_ORDINAL] = CHAR_FEMININE_ORDINAL,
    [CHAR_BULLET] = CHAR_BULLET,
    [CHAR_EQUALS] = CHAR_EQUALS,
    [CHAR_MULT_SIGN] = CHAR_MULT_SIGN,
    [CHAR_PERCENT] = CHAR_PERCENT,
    [CHAR_LESS_THAN] = CHAR_LESS_THAN,
    [CHAR_GREATER_THAN] = CHAR_GREATER_THAN,
    [CHAR_MALE] = CHAR_MALE,
    [CHAR_FEMALE] = CHAR_FEMALE,
    [CHAR_CURRENCY] = CHAR_CURRENCY,
    [CHAR_BLACK_TRIANGLE] = CHAR_BLACK_TRIANGLE,*/
};


extern u8 gExpandedPlaceholder_Empty[];
extern u8 gExpandedPlaceholder_Kun[];
extern u8 gExpandedPlaceholder_Chan[];
extern u8 gExpandedPlaceholder_Sapphire[];
extern u8 gExpandedPlaceholder_Ruby[];
extern u8 gExpandedPlaceholder_Aqua[];
extern u8 gExpandedPlaceholder_Magma[];
extern u8 gExpandedPlaceholder_Archie[];
extern u8 gExpandedPlaceholder_Maxie[];
extern u8 gExpandedPlaceholder_Kyogre[];
extern u8 gExpandedPlaceholder_Groudon[];
extern u8 gExpandedPlaceholder_Red[];
extern u8 gExpandedPlaceholder_Green[];

u8 *StringCopy_Nickname(u8 *dest, const u8 *src)
{
    u8 i;
    u32 limit = POKEMON_NAME_LENGTH;

    //believe what this means is if should cap/decap
    //if curr char isn't capitalization placeholder add it,
    //if it is there but.. I guess skip copying it?
    /*if (DECAP_ENABLED && !DECAP_NICKNAMES)
    {
        */
       /*if (IsStringAddrSafe(dest, limit) && *src != CHAR_CAPITALIZE_SPECIES)
            *dest++ = CHAR_CAPITALIZE_SPECIES;
        else if (*src == CHAR_CAPITALIZE_SPECIES)
            *dest++ = *src++;*/
    //}

    for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }

    dest[i] = EOS;
    return &dest[i];
}

u8 *StringGet_Nickname(u8 *str)//found correct syntax but don't believe this is correct place for it?
{
    u8 i;
    u32 limit = POKEMON_NAME_LENGTH;

    /*if (*str == CHAR_CAPITALIZE_SPECIES)
        str++;
    */
        
    for (i = 0; i < limit; i++)
        if (str[i] == EOS)
            return &str[i];

    str[i] = EOS;
    return &str[i];
}

u8 *StringCopy_PlayerName(u8 *dest, const u8 *src)
{
    s32 i;
    s32 limit = PLAYER_NAME_LENGTH;

    for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }

    dest[i] = EOS;
    return &dest[i];
}

u8 *StringCopy(u8 *dest, const u8 *src)
{
    while (*src != EOS)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = EOS;
    return dest;
}

u8 *StringAppend(u8 *dest, const u8 *src)
{
    while (*dest != EOS)
        dest++;

    return StringCopy(dest, src);
}

u8 *StringCopyN(u8 *dest, const u8 *src, u8 n)
{
    u16 i;

    for (i = 0; i < n; i++)
        dest[i] = src[i];

    return &dest[n];
}

u8 *StringAppendN(u8 *dest, const u8 *src, u8 n)
{
    while (*dest != EOS)
        dest++;

    return StringCopyN(dest, src, n);
}

u16 StringLength(const u8 *str)
{
    u16 length = 0;

    while (str[length] != EOS)
        length++;

    return length;
}

s32 StringCompare(const u8 *str1, const u8 *str2)
{
    while (*str1 == *str2)
    {
        if (*str1 == EOS)
            return 0;
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

s32 StringCompareN(const u8 *str1, const u8 *str2, u32 n)
{
    while (*str1 == *str2)
    {
        if (*str1 == EOS)
            return 0;
        str1++;
        str2++;
        if (--n == 0)
            return 0;
    }

    return *str1 - *str2;
}

u8 *ConvertIntToDecimalStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    s32 powerOfTen;
    s32 largestPowerOfTen = sPowersOfTen[n - 1];

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfTen = largestPowerOfTen; powerOfTen > 0; powerOfTen /= 10)
    {
        u8 *out;
        u8 c;
        u16 digit = value / powerOfTen;
        s32 temp = value - (powerOfTen * digit);

        if (state == WRITING_DIGITS)
        {
            out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfTen == 1)
        {
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACE;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *ConvertIntToHexStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    u8 i;
    s32 powerOfSixteen;
    s32 largestPowerOfSixteen = 1;

    for (i = 1; i < n; i++)
        largestPowerOfSixteen *= 16;

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfSixteen = largestPowerOfSixteen; powerOfSixteen > 0; powerOfSixteen /= 16)
    {
        u8 *out;
        u8 c;
        u32 digit = value / powerOfSixteen;
        s32 temp = value % powerOfSixteen;

        if (state == WRITING_DIGITS)
        {
            out = dest++;

            if (digit <= 0xF)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfSixteen == 1)
        {
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 0xF)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACE;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *StringExpandPlaceholders(u8 *dest, const u8 *src)
{
    for (;;)
    {
        u8 c = *src++;
        u8 placeholderId;
        u8 *expandedString;

        switch (c)
        {
            case PLACEHOLDER_BEGIN:
                placeholderId = *src++;
                expandedString = GetExpandedPlaceholder(placeholderId);
                dest = StringExpandPlaceholders(dest, expandedString);
                break;
            case EXT_CTRL_CODE_BEGIN:
                *dest++ = c;
                c = *src++;
                *dest++ = c;

                switch (c)
                {
                    case EXT_CTRL_CODE_RESET_FONT:
                    case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
                    case EXT_CTRL_CODE_FILL_WINDOW:
                    case EXT_CTRL_CODE_JPN:
                    case EXT_CTRL_CODE_ENG:
                    case EXT_CTRL_CODE_PAUSE_MUSIC:
                    case EXT_CTRL_CODE_RESUME_MUSIC:
                        break;
                    case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
                        *dest++ = *src++;
                    case EXT_CTRL_CODE_PLAY_BGM:
                        *dest++ = *src++;
                    default:
                        *dest++ = *src++;
                }
                break;
            case EOS:
                *dest = EOS;
                return dest;
            /*case CHAR_CAPITALIZE_ABILITY:
            case CHAR_CAPITALIZE_SPECIES:
            case CHAR_CAPITALIZE_MOVES:
            case CHAR_CAPITALIZE_ITEMS:*/
            case CHAR_MISC_CAP:
            case CHAR_END_CAPITALIZATION:
            case CHAR_PROMPT_SCROLL:
            case CHAR_PROMPT_CLEAR:
            case CHAR_NEWLINE:
            default:
                *dest++ = c;
        }
    }
}

u8 *StringBraille(u8 *dest, const u8 *src)
{
    u8 setBrailleFont[] = { 0xFC, 0x06, 0x06, 0xFF };
    u8 gotoLine2[] = { 0xFE, 0xFC, 0x0E, 0x02, 0xFF };

    dest = StringCopy(dest, setBrailleFont);

    for (;;)
    {
        u8 c = *src++;

        switch (c)
        {
            case EOS:   //0xFF
                *dest = c;
                return dest;
            case CHAR_NEWLINE:  //0xFE
                dest = StringCopy(dest, gotoLine2);
                break;
            default:
                *dest++ = c;
                *dest++ = c + 0x40;
                break;
        }
    }
}

static u8 *ExpandPlaceholder_UnknownStringVar(void)
{
    return gUnknownStringVar;
}

//add to placeholders, and do if should cap misc cap the string that would be returned, and then do the return
//to make simple put all in one function, flag check etc. then can remove the cap stuff in text, and remove the capitlize text, don't need it,
//since I'm swapping the text before it printsnot as it prints
static u8 *ExpandPlaceholder_PlayerName(void)
{
    return gSaveBlock2Ptr->playerName;
}

static u8 *ExpandPlaceholder_StringVar1(void)
{
    return gStringVar1;
}

static u8 *ExpandPlaceholder_StringVar2(void)
{
    return gStringVar2;
}

static u8 *ExpandPlaceholder_StringVar3(void)
{
    return gStringVar3;
}

static u8 *ExpandPlaceholder_KunChan(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        return gExpandedPlaceholder_Kun;
    else
        return gExpandedPlaceholder_Chan;
}

static u8 *ExpandPlaceholder_RivalName(void)
{
    if (gSaveBlock1Ptr->rivalName[0] == EOS)
    {
        if (gSaveBlock2Ptr->playerGender == MALE)
            return gExpandedPlaceholder_Green;
        else
            return gExpandedPlaceholder_Red;
    }//not relevant in fr/lg never uses rival name buffer before name is stored
    else//will always trigger below,
    {
        return gSaveBlock1Ptr->rivalName;
    }
}//calls saved rival name, for text will need to compare stored value against all buffer values
//if name matches buffer can do, if not skip
//do same for player, and change all to lowercase

static u8 *ExpandPlaceholder_Version(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Ruby;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Sapphire;
#endif
}

static u8 *ExpandPlaceholder_Magma(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Magma;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Aqua;
#endif
}

static u8 *ExpandPlaceholder_Aqua(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Aqua;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Magma;
#endif
}

static u8 *ExpandPlaceholder_Maxie(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Maxie;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Archie;
#endif
}

static u8 *ExpandPlaceholder_Archie(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Archie;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Maxie;
#endif
}

static u8 *ExpandPlaceholder_Groudon(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Groudon;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Kyogre;
#endif
}

static u8 *ExpandPlaceholder_Kyogre(void)
{
#if defined(FIRERED)
    return gExpandedPlaceholder_Kyogre;
#elif defined(LEAFGREEN)
    return gExpandedPlaceholder_Groudon;
#endif
}

#define STRING_PLACEHOLDER_TABLE
u8 *GetExpandedPlaceholder(u32 id)
{
    typedef u8 *(*ExpandPlaceholderFunc)(void);

    //function table must line up with charmap string placeholders
    static const ExpandPlaceholderFunc funcs[] =
    {
        [PLACEHOLDER_ID_UNKNOWN]      = ExpandPlaceholder_UnknownStringVar,
        [PLACEHOLDER_ID_PLAYER]       = ExpandPlaceholder_PlayerName,
        [PLACEHOLDER_ID_STRING_VAR_1] = ExpandPlaceholder_StringVar1,
        [PLACEHOLDER_ID_STRING_VAR_2] = ExpandPlaceholder_StringVar2,
        [PLACEHOLDER_ID_STRING_VAR_3] = ExpandPlaceholder_StringVar3,
        [PLACEHOLDER_ID_KUN]          = ExpandPlaceholder_KunChan,
        [PLACEHOLDER_ID_RIVAL]        = ExpandPlaceholder_RivalName,
        [PLACEHOLDER_ID_VERSION]      = ExpandPlaceholder_Version,
        [PLACEHOLDER_ID_EVIL_TEAM]        = ExpandPlaceholder_Magma,
        [PLACEHOLDER_ID_GOOD_TEAM]         = ExpandPlaceholder_Aqua,
        [PLACEHOLDER_ID_EVIL_LEADER]        = ExpandPlaceholder_Maxie,
        [PLACEHOLDER_ID_GOOD_LEADER]       = ExpandPlaceholder_Archie,
        [PLACEHOLDER_ID_EVIL_LEGENDARY]      = ExpandPlaceholder_Groudon,
        [PLACEHOLDER_ID_GOOD_LEGENDARY]       = ExpandPlaceholder_Kyogre,
    };

    if (id >= NELEMS(funcs))
        return gExpandedPlaceholder_Empty;
    else
        return funcs[id]();
}

u8 *StringFill(u8 *dest, u8 c, u16 n)
{
    u16 i;

    for (i = 0; i < n; i++)
        *dest++ = c;

    *dest = EOS;
    return dest;
}

u8 *StringCopyPadded(u8 *dest, const u8 *src, u8 c, u16 n)
{
    while (*src != EOS)
    {
        *dest++ = *src++;

        if (n)
            n--;
    }

    n--;

    while (n != (u16)-1)
    {
        *dest++ = c;
        n--;
    }

    *dest = EOS;
    return dest;
}

u8 *StringFillWithTerminator(u8 *dest, u16 n)
{
    return StringFill(dest, EOS, n);
}

u8 *StringCopyN_Multibyte(u8 *dest, const u8 *src, u32 n)
{
    u32 i;

    for (i = n - 1; i != -1u; i--)
    {
        if (*src == EOS)
        {
            break;
        }
        else
        {
            *dest++ = *src++;
            if (*(src - 1) == 0xF9)
                *dest++ = *src++;
        }
    }

    *dest = EOS;
    return dest;
}

u32 StringLength_Multibyte(const u8 *str)
{
    u32 length = 0;

    while (*str != EOS)
    {
        if (*str == CHAR_EXTRA_SYMBOL) //0xf9
            str++;
        str++;
        length++;
    }

    return length;
}

u8 *WriteColorChangeControlCode(u8 *dest, u32 colorType, u8 color)
{
    *dest = EXT_CTRL_CODE_BEGIN; //0xfc
    dest++;

    switch (colorType)
    {
    case 0:
        *dest = 1;
        dest++;
        break;
    case 1:
        *dest = 3;
        dest++;
        break;
    case 2:
        *dest = 2;
        dest++;
        break;
    }

    *dest = color;
    dest++;
    *dest = EOS;
    return dest;
}

u8 GetExtCtrlCodeLength(u8 code)
{
    static const u8 lengths[] =
    {
        [0]                                    = 1,
        [EXT_CTRL_CODE_COLOR]                  = 2,
        [EXT_CTRL_CODE_HIGHLIGHT]              = 2,
        [EXT_CTRL_CODE_SHADOW]                 = 2,
        [EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW] = 4,
        [EXT_CTRL_CODE_PALETTE]                = 2,
        [EXT_CTRL_CODE_FONT]                   = 2,
        [EXT_CTRL_CODE_RESET_FONT]             = 1,
        [EXT_CTRL_CODE_PAUSE]                  = 2,
        [EXT_CTRL_CODE_PAUSE_UNTIL_PRESS]      = 1,
        [EXT_CTRL_CODE_WAIT_SE]                = 1,
        [EXT_CTRL_CODE_PLAY_BGM]               = 3,
        [EXT_CTRL_CODE_ESCAPE]                 = 2,
        [EXT_CTRL_CODE_SHIFT_RIGHT]             = 2,
        [EXT_CTRL_CODE_SHIFT_DOWN]             = 2,
        [EXT_CTRL_CODE_FILL_WINDOW]            = 1,
        [EXT_CTRL_CODE_PLAY_SE]                = 3,
        [EXT_CTRL_CODE_CLEAR]                  = 2,
        [EXT_CTRL_CODE_SKIP]                   = 2,
        [EXT_CTRL_CODE_CLEAR_TO]               = 2,
        [EXT_CTRL_CODE_MIN_LETTER_SPACING]     = 2,
        [EXT_CTRL_CODE_JPN]                    = 1,
        [EXT_CTRL_CODE_ENG]                    = 1,
        [EXT_CTRL_CODE_PAUSE_MUSIC]            = 1,
        [EXT_CTRL_CODE_RESUME_MUSIC]           = 1,
        [EXT_CTRL_CODE_CLEAR_TEXT_TO]          = 2,
        /*[EXT_CTRL_CODE_CAPITALIZE_ABILITY]     = 1,
        [EXT_CTRL_CODE_CAPITALIZE_SPECIES]     = 1,
        [EXT_CTRL_CODE_CAPITALIZE_MOVES]       = 1,
        [EXT_CTRL_CODE_CAPITALIZE_ITEMS]       = 1,
        [EXT_CTRL_CODE_MISC_CAP]           = 1,
        [EXT_CTRL_CODE_END_CAPITALIZATION]     = 1,
        */
    };

    u8 length = 0;
    if (code < NELEMS(lengths))
        length = lengths[code];
    return length;
}

static const u8 *SkipExtCtrlCode(const u8 *s)
{
    while (*s == EXT_CTRL_CODE_BEGIN)//0xFC
    {
        s++;
        s += GetExtCtrlCodeLength(*s);
    }

    return s;
}

s32 StringCompareWithoutExtCtrlCodes(const u8 *str1, const u8 *str2)
{
    s32 retVal = 0;

    while (1)
    {
        str1 = SkipExtCtrlCode(str1);
        str2 = SkipExtCtrlCode(str2);

        if (*str1 > *str2)
            break;

        if (*str1 < *str2)
        {
            retVal = -1;
            if (*str2 == EOS)
                retVal = 1;
        }

        if (*str1 == EOS)
            return retVal;

        str1++;
        str2++;
    }

    retVal = 1;

    if (*str1 == EOS)
        retVal = -1;

    return retVal;
}

void ConvertInternationalString(u8 *s, u8 language)
{
    if (language == LANGUAGE_JAPANESE)
    {
        u8 i;

        StripExtCtrlCodes(s);
        i = StringLength(s);
        s[i++] = EXT_CTRL_CODE_BEGIN;
        s[i++] = 22;
        s[i++] = EOS;

        i--;

        while (i != (u8)-1)
        {
            s[i + 2] = s[i];
            i--;
        }

        s[0] = EXT_CTRL_CODE_BEGIN;
        s[1] = 21;
    }
}

void StripExtCtrlCodes(u8 *str)
{
    u16 srcIndex = 0;
    u16 destIndex = 0;
    while (str[srcIndex] != EOS)
    {
        if (str[srcIndex] == EXT_CTRL_CODE_BEGIN)
        {
            srcIndex++;
            srcIndex += GetExtCtrlCodeLength(str[srcIndex]);
        }
        else
        {
            str[destIndex++] = str[srcIndex++];
        }
    }
    str[destIndex] = EOS;
}

u8 *StringCopyUppercase(u8 *dest, const u8 *src)
{
    while (*src != EOS)
    {
        if (*src >= CHAR_a && *src <= CHAR_z)
            *dest = 0;//gCaseToggleTable[*src];
        else
            *dest = *src;
        dest++;
        src++;
    }

    *dest = EOS;    //think puts null terminator at end
    return dest;
}

//ok initially to false for check so it would auto capitalize
//because the flag wasn't set anywhere just to see if it worked
//was supposed to say, if true capitalize
bool8 ShouldCapitalizeSpecies(void)
{
    return FlagGet(FLAG_CAPITALIZE_SPECIES_TEXT); //plan rename to capitalize
}

bool8 ShouldCapitalizeAbility(void)
{
    return FlagGet(FLAG_CAPITALIZE_ABILITY_TEXT);
}

bool8 ShouldCapitalizeMoves(void)
{
    return FlagGet(FLAG_CAPITALIZE_MOVE_TEXT);
}

bool8 ShouldCapitalizeItems(void)
{
    return FlagGet(FLAG_CAPITALIZE_ITEM_TEXT);
}

//since not using buff can do everything on string itself, no need to pass to expanded buffer
//can just use this function and filter with condition functions, just need put in src that populates
//other filters, i.e original call and set area, which is why getspeciesname worked for species name cap
//works for display but currently doesn't work in  string texts
void CapializeString(u8 *src) 
{

    u32 i = 0;


    while (src[i] != EOS)
    {
        if (src[i] >= CHAR_a && src[i] <= CHAR_z)
            CAPITALIZE_CHAR(src[i]);

        i++;
    }

}

//believe doesn't work but keep for later reference
/*void StringCopy_CapitalizeConst(u8 *dest, const u8 *src)
{
    //u8 i;
    //u32 limit = POKEMON_NAME_LENGTH + 1;

    //believe what this means is if should cap/decap
    //if curr char isn't capitalization placeholder add it,
    //if it is there but.. I guess skip copying it?
    /*if (DECAP_ENABLED && !DECAP_NICKNAMES)
    {
        */
       /*if (IsStringAddrSafe(dest, limit) && *src != CHAR_CAPITALIZE_SPECIES)
            *dest++ = CHAR_CAPITALIZE_SPECIES;
        else if (*src == CHAR_CAPITALIZE_SPECIES)
            *dest++ = *src++;*/
    //}

    /*for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }*/


    /*for (i = 0; i < limit; i++)
    {
        if (dest[i] >= CHAR_a && dest[i] <= CHAR_z)
            dest[i] = gCaseToggleTable[dest[i]];
        else
            dest[i] = dest[i];

        if (dest[i] == EOS)
            break;
    }*/

    /*while (*src != EOS)
    {
        if (*src >= CHAR_a && *src <= CHAR_z)
            *dest = gCaseToggleTable[*src];
        else
            *dest = *src;
        dest++;
        src++;
    }

    *dest = EOS;    //think puts null terminator at end

    //src = (const u8 *)dest; //attempt to cast to const to pass the capped pointer to const ptr

    //return dest;
    //if works no need to return, flag check is handled already

}*/
