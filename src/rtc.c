#include "global.h"
#include "rtc.h"
#include "constants/rtc.h"
#include "string_util.h"
#include "text.h"

// iwram bss
static u16 sErrorStatus;
static struct SiiRtcInfo sRtc;
static u8 sProbeResult;
static u16 sSavedIme;

// iwram common
struct Time gLocalTime;

// const rom

static const struct SiiRtcInfo sRtcDummy = {0, MONTH_JAN, 1}; // 2000 Jan 1

static const s32 sNumDaysInMonths[NUM_MONTHS] =
{
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31,
};

#define PALTAG_ARROW 0x1000

static const struct OamData sOamData_Arrow =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
//taken from rhh need arrow for dex stuff
static const u8 sArrowDown_Gfx[] = INCBIN_U8("graphics/misc/arrow_down.4bpp");
static const u8 sArrowRight_Gfx[] = INCBIN_U8("graphics/misc/arrow_right.4bpp");
static const u16 sArrow_Pal[] = INCBIN_U16("graphics/misc/arrow.gbapal");

static const struct SpriteFrameImage sPicTable_Arrow[] =
{
    obj_frame_tiles(sArrowDown_Gfx),
    obj_frame_tiles(sArrowRight_Gfx)
};

const struct SpritePalette gSpritePalette_Arrow =
{
    sArrow_Pal, PALTAG_ARROW
};

static const union AnimCmd sAnim_Arrow_Down[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Arrow_Up[] =
{
    ANIMCMD_FRAME(0, 30, .vFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Arrow_Right[] =
{
    ANIMCMD_FRAME(1, 30),
    ANIMCMD_JUMP(0),
};

enum {
    ARROW_DOWN,
    ARROW_UP,
    ARROW_RIGHT,
};

static const union AnimCmd *const sAnims_Arrow[] =
{
    [ARROW_DOWN]  = sAnim_Arrow_Down,
    [ARROW_UP]    = sAnim_Arrow_Up,
    [ARROW_RIGHT] = sAnim_Arrow_Right,
};

const struct SpriteTemplate gSpriteTemplate_Arrow =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALTAG_ARROW,
    .oam = &sOamData_Arrow,
    .anims = sAnims_Arrow,
    .images = sPicTable_Arrow,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

void RtcDisableInterrupts(void)
{
    sSavedIme = REG_IME;
    REG_IME = 0;
}

void RtcRestoreInterrupts(void)
{
    REG_IME = sSavedIme;
}

u32 ConvertBcdToBinary(u8 bcd)
{
    if (bcd > 0x9F)
        return 0xFF;

    if ((bcd & 0xF) <= 9)
        return (10 * ((bcd >> 4) & 0xF)) + (bcd & 0xF);
    else
        return 0xFF;
}

bool8 IsLeapYear(u32 year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return TRUE;

    return FALSE;
}

u16 ConvertDateToDayCount(u8 year, u8 month, u8 day)
{
    s32 i;
    u16 dayCount = 0;

    for (i = year - 1; i >= 0; i--)
    {
        dayCount += 365;

        if (IsLeapYear(i) == TRUE)
            dayCount++;
    }

    for (i = 0; i < month - 1; i++)
        dayCount += sNumDaysInMonths[i];

    if (month > MONTH_FEB && IsLeapYear(year) == TRUE)
        dayCount++;

    dayCount += day;

    return dayCount;
}

u16 RtcGetDayCount(struct SiiRtcInfo *rtc)
{
    u8 year = ConvertBcdToBinary(rtc->year);
    u8 month = ConvertBcdToBinary(rtc->month);
    u8 day = ConvertBcdToBinary(rtc->day);
    return ConvertDateToDayCount(year, month, day);
}

void RtcInit(void)
{
    sErrorStatus = 0;

    RtcDisableInterrupts();
    SiiRtcUnprotect();
    sProbeResult = SiiRtcProbe();
    RtcRestoreInterrupts();

    if ((sProbeResult & 0xF) != 1)
    {
        sErrorStatus = RTC_INIT_ERROR;
        return;
    }

    if (sProbeResult & 0xF0)
        sErrorStatus = RTC_INIT_WARNING;
    else
        sErrorStatus = 0;

    RtcGetRawInfo(&sRtc);
    sErrorStatus = RtcCheckInfo(&sRtc);
}

u16 RtcGetErrorStatus(void)
{
    return sErrorStatus;
}

void RtcGetInfo(struct SiiRtcInfo *rtc)
{
    if (sErrorStatus & RTC_ERR_FLAG_MASK)
        *rtc = sRtcDummy;
    else
        RtcGetRawInfo(rtc);
}

void RtcGetDateTime(struct SiiRtcInfo *rtc)
{
    RtcDisableInterrupts();
    SiiRtcGetDateTime(rtc);
    RtcRestoreInterrupts();
}

void RtcGetStatus(struct SiiRtcInfo *rtc)
{
    RtcDisableInterrupts();
    SiiRtcGetStatus(rtc);
    RtcRestoreInterrupts();
}

void RtcGetRawInfo(struct SiiRtcInfo *rtc)
{
    RtcGetStatus(rtc);
    RtcGetDateTime(rtc);
}

u16 RtcCheckInfo(struct SiiRtcInfo *rtc)
{
    u16 errorFlags = 0;
    s32 year;
    s32 month;
    s32 value;

    if (rtc->status & SIIRTCINFO_POWER)
        errorFlags |= RTC_ERR_POWER_FAILURE;

    if (!(rtc->status & SIIRTCINFO_24HOUR))
        errorFlags |= RTC_ERR_12HOUR_CLOCK;

    year = ConvertBcdToBinary(rtc->year);

    if (year == 0xFF)
        errorFlags |= RTC_ERR_INVALID_YEAR;

    month = ConvertBcdToBinary(rtc->month);

    if (month == 0xFF || month == 0 || month > 12)
        errorFlags |= RTC_ERR_INVALID_MONTH;

    value = ConvertBcdToBinary(rtc->day);

    if (value == 0xFF)
        errorFlags |= RTC_ERR_INVALID_DAY;

    if (month == MONTH_FEB)
    {
        if (value > IsLeapYear(year) + sNumDaysInMonths[month - 1])
            errorFlags |= RTC_ERR_INVALID_DAY;
    }
    else
    {
        if (value > sNumDaysInMonths[month - 1])
            errorFlags |= RTC_ERR_INVALID_DAY;
    }

    value = ConvertBcdToBinary(rtc->hour);

    if (value > 24)
        errorFlags |= RTC_ERR_INVALID_HOUR;

    value = ConvertBcdToBinary(rtc->minute);

    if (value > 60)
        errorFlags |= RTC_ERR_INVALID_MINUTE;

    value = ConvertBcdToBinary(rtc->second);

    if (value > 60)
        errorFlags |= RTC_ERR_INVALID_SECOND;

    return errorFlags;
}

void RtcReset(void)
{
    RtcDisableInterrupts();
    SiiRtcReset();
    RtcRestoreInterrupts();
}

void FormatDecimalTime(u8 *dest, s32 hour, s32 minute, s32 second)
{
    dest = ConvertIntToDecimalStringN(dest, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, second, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatHexTime(u8 *dest, s32 hour, s32 minute, s32 second)
{
    dest = ConvertIntToHexStringN(dest, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToHexStringN(dest, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToHexStringN(dest, second, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatHexRtcTime(u8 *dest)
{
    FormatHexTime(dest, sRtc.hour, sRtc.minute, sRtc.second);
}

void FormatDecimalDate(u8 *dest, s32 year, s32 month, s32 day)
{
    dest = ConvertIntToDecimalStringN(dest, year, STR_CONV_MODE_LEADING_ZEROS, 4);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToDecimalStringN(dest, month, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToDecimalStringN(dest, day, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatHexDate(u8 *dest, s32 year, s32 month, s32 day)
{
    dest = ConvertIntToHexStringN(dest, year, STR_CONV_MODE_LEADING_ZEROS, 4);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToHexStringN(dest, month, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToHexStringN(dest, day, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void RtcCalcTimeDifference(struct SiiRtcInfo *rtc, struct Time *result, struct Time *t)
{
    u16 days = RtcGetDayCount(rtc);
    result->seconds = ConvertBcdToBinary(rtc->second) - t->seconds;
    result->minutes = ConvertBcdToBinary(rtc->minute) - t->minutes;
    result->hours = ConvertBcdToBinary(rtc->hour) - t->hours;
    result->days = days - t->days;

    if (result->seconds < 0)
    {
        result->seconds += 60;
        --result->minutes;
    }

    if (result->minutes < 0)
    {
        result->minutes += 60;
        --result->hours;
    }

    if (result->hours < 0)
    {
        result->hours += 24;
        --result->days;
    }
}

void RtcCalcLocalTime(void)
{
    RtcGetInfo(&sRtc);
    RtcCalcTimeDifference(&sRtc, &gLocalTime, &gSaveBlock2Ptr->localTimeOffset);
}

bool8 IsBetweenHours(s32 hours, s32 begin, s32 end)
{
    if (end < begin)
        return hours >= begin || hours < end;
    else
        return hours >= begin && hours < end;
}

u8 GetTimeOfDay(void)
{
    RtcCalcLocalTime();
    if (IsBetweenHours(gLocalTime.hours, MORNING_HOUR_BEGIN, MORNING_HOUR_END))
        return TIME_MORNING;
    else if (IsBetweenHours(gLocalTime.hours, EVENING_HOUR_BEGIN, EVENING_HOUR_END))
        return TIME_EVENING;
    else if (IsBetweenHours(gLocalTime.hours, NIGHT_HOUR_BEGIN, NIGHT_HOUR_END))
        return TIME_NIGHT;
    return TIME_DAY;
}

void RtcInitLocalTimeOffset(s32 hour, s32 minute)
{
    RtcCalcLocalTimeOffset(0, hour, minute, 0);
}

void RtcCalcLocalTimeOffset(s32 days, s32 hours, s32 minutes, s32 seconds)
{
    gLocalTime.days = days;
    gLocalTime.hours = hours;
    gLocalTime.minutes = minutes;
    gLocalTime.seconds = seconds;
    RtcGetInfo(&sRtc);
    RtcCalcTimeDifference(&sRtc, &gSaveBlock2Ptr->localTimeOffset, &gLocalTime);
}

void CalcTimeDifference(struct Time *result, struct Time *t1, struct Time *t2)
{
    result->seconds = t2->seconds - t1->seconds;
    result->minutes = t2->minutes - t1->minutes;
    result->hours = t2->hours - t1->hours;
    result->days = t2->days - t1->days;

    if (result->seconds < 0)
    {
        result->seconds += 60;
        --result->minutes;
    }

    if (result->minutes < 0)
    {
        result->minutes += 60;
        --result->hours;
    }

    if (result->hours < 0)
    {
        result->hours += 24;
        --result->days;
    }
}

u32 RtcGetMinuteCount(void)
{
    RtcGetInfo(&sRtc);
    return (24 * 60) * RtcGetDayCount(&sRtc) + 60 * sRtc.hour + sRtc.minute;
}

u32 RtcGetLocalDayCount(void)
{
    return RtcGetDayCount(&sRtc);
}
