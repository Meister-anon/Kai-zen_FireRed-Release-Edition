#include "global.h"
#include "field_weather.h"
#include "overworld.h"
#include "constants/weather.h"
#include "event_data.h"
#include "constants/region_map_sections.h"

static u8 TranslateWeatherNum(u8 weather);
static void UpdateRainCounter(u8 newWeather, u8 oldWeather);

void SetSav1Weather(u32 weather)
{
    u8 oldWeather = gSaveBlock1Ptr->weather;
    gSaveBlock1Ptr->weather = TranslateWeatherNum(weather);
    UpdateRainCounter(gSaveBlock1Ptr->weather, oldWeather);
}

u8 GetSav1Weather(void)
{
    return gSaveBlock1Ptr->weather;
}

//tested works,
//can put the switch here, do flag check
    //for beating team rocket at pokemon tower,
    //assign curr weather to other fog,
    //think what will do is have fog be main,
    //set to dark fog after
    //hmm well want to keep top as fog,
    //so instead if weather dark fog and flag not set,
    //set to fog
    //that way will be like spirits have calmed down,
    //and fog isn't as strong
void SetSav1WeatherFromCurrMapHeader(void)
{
    u8 oldWeather = gSaveBlock1Ptr->weather;
    gSaveBlock1Ptr->weather = TranslateWeatherNum(gMapHeader.weather);

    if ((gSaveBlock1Ptr->weather == WEATHER_DARKFOG_HORIZONTAL)
    && (gMapHeader.regionMapSectionId == MAPSEC_POKEMON_TOWER)
    && !FlagGet(FLAG_RESCUED_MR_FUJI))
        gSaveBlock1Ptr->weather = WEATHER_FOG_HORIZONTAL;
    
    UpdateRainCounter(gSaveBlock1Ptr->weather, oldWeather);
}

void SetWeather(u32 weather)
{
    SetSav1Weather(weather);
    SetNextWeather(GetSav1Weather());
}

void SetWeather_Unused(u32 weather)
{
    SetSav1Weather(weather);
    SetCurrentAndNextWeather(GetSav1Weather());
}

void DoCurrentWeather(void)
{
    u8 weather = GetSav1Weather();

    SetNextWeather(weather);
}

void ResumePausedWeather(void)
{
    u8 weather = GetSav1Weather();

    SetCurrentAndNextWeather(weather);
}

static const u8 sWeatherCycleRoute119[] = {
    WEATHER_SUNNY,
    WEATHER_RAIN,
    WEATHER_RAIN_THUNDERSTORM,
    WEATHER_RAIN,
};

static const u8 sWeatherCycleRoute123[] = {
    WEATHER_SUNNY,
    WEATHER_SUNNY,
    WEATHER_RAIN,
    WEATHER_SUNNY,
};

static u8 TranslateWeatherNum(u8 weather)
{
    switch (weather)
    {
    case WEATHER_NONE:               return WEATHER_NONE;
    case WEATHER_SUNNY_CLOUDS:       return WEATHER_SUNNY_CLOUDS;
    case WEATHER_SUNNY:              return WEATHER_SUNNY;
    case WEATHER_RAIN:               return WEATHER_RAIN;
    case WEATHER_SNOW:               return WEATHER_SNOW;
    case WEATHER_RAIN_THUNDERSTORM:  return WEATHER_RAIN_THUNDERSTORM;
    case WEATHER_FOG_HORIZONTAL:     return WEATHER_FOG_HORIZONTAL;
    case WEATHER_DARKFOG_HORIZONTAL: return WEATHER_DARKFOG_HORIZONTAL;
    case WEATHER_VOLCANIC_ASH:       return WEATHER_VOLCANIC_ASH;
    case WEATHER_SANDSTORM:          return WEATHER_SANDSTORM;
    case WEATHER_FOG_DIAGONAL:       return WEATHER_FOG_DIAGONAL;
    case WEATHER_UNDERWATER:         return WEATHER_UNDERWATER;
    case WEATHER_SHADE:              return WEATHER_SHADE;
    case WEATHER_DROUGHT:            return WEATHER_DROUGHT;
    case WEATHER_DOWNPOUR:           return WEATHER_DOWNPOUR;
    case WEATHER_UNDERWATER_BUBBLES: return WEATHER_UNDERWATER_BUBBLES;
    case WEATHER_ROUTE119_CYCLE:     return sWeatherCycleRoute119[gSaveBlock1Ptr->weatherCycleStage];
    case WEATHER_ROUTE123_CYCLE:     return sWeatherCycleRoute123[gSaveBlock1Ptr->weatherCycleStage];
    default:                         return WEATHER_NONE;
    }
}

void UpdateWeatherPerDay(u16 increment)
{
    u16 weatherStage = gSaveBlock1Ptr->weatherCycleStage + increment;
    weatherStage %= 4;
    gSaveBlock1Ptr->weatherCycleStage = weatherStage;
}

static void UpdateRainCounter(u8 newWeather, u8 oldWeather)
{
    if (newWeather != oldWeather
        && (newWeather == WEATHER_RAIN || newWeather == WEATHER_RAIN_THUNDERSTORM))
        IncrementGameStat(GAME_STAT_GOT_RAINED_ON);
}
