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

    if ((gSaveBlock1Ptr->weather == OVERWORLD_WEATHER_DARKFOG_HORIZONTAL)
    && (gMapHeader.regionMapSectionId == MAPSEC_POKEMON_TOWER)
    && !FlagGet(FLAG_RESCUED_MR_FUJI))
        gSaveBlock1Ptr->weather = OVERWORLD_WEATHER_FOG_HORIZONTAL;
    
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

//NOT USED in FR
//but could use to calc weather patterns
//based on location i.e climate based on region
static const u8 sWeatherCycleRoute119[] = {
    OVERWORLD_WEATHER_SUNNY,
    OVERWORLD_WEATHER_RAIN,
    OVERWORLD_WEATHER_RAIN_THUNDERSTORM,
    OVERWORLD_WEATHER_RAIN,
};

static const u8 sWeatherCycleRoute123[] = {
    OVERWORLD_WEATHER_SUNNY,
    OVERWORLD_WEATHER_SUNNY,
    OVERWORLD_WEATHER_RAIN,
    OVERWORLD_WEATHER_SUNNY,
};

//NEED ADd other weathers
static u8 TranslateWeatherNum(u8 weather)
{
    switch (weather)
    {
    case OVERWORLD_WEATHER_NONE:               return OVERWORLD_WEATHER_NONE;
    case OVERWORLD_WEATHER_SUNNY_CLOUDS:       return OVERWORLD_WEATHER_SUNNY_CLOUDS;
    case OVERWORLD_WEATHER_SUNNY:              return OVERWORLD_WEATHER_SUNNY;
    case OVERWORLD_WEATHER_RAIN:            return OVERWORLD_WEATHER_RAIN;
    case OVERWORLD_WEATHER_SNOW:             return OVERWORLD_WEATHER_SNOW;
    case OVERWORLD_WEATHER_RAIN_THUNDERSTORM:  return OVERWORLD_WEATHER_RAIN_THUNDERSTORM;
    case OVERWORLD_WEATHER_FOG_HORIZONTAL:     return OVERWORLD_WEATHER_FOG_HORIZONTAL;
    case OVERWORLD_WEATHER_DARKFOG_HORIZONTAL: return OVERWORLD_WEATHER_DARKFOG_HORIZONTAL;
    case OVERWORLD_WEATHER_VOLCANIC_ASH:       return OVERWORLD_WEATHER_VOLCANIC_ASH;
    case OVERWORLD_WEATHER_SANDSTORM:        return OVERWORLD_WEATHER_SANDSTORM;
    case OVERWORLD_WEATHER_FOG_DIAGONAL:       return OVERWORLD_WEATHER_FOG_DIAGONAL;
    case OVERWORLD_WEATHER_UNDERWATER:         return OVERWORLD_WEATHER_UNDERWATER;
    case OVERWORLD_WEATHER_SHADE:              return OVERWORLD_WEATHER_SHADE;
    case OVERWORLD_WEATHER_DROUGHT:            return OVERWORLD_WEATHER_DROUGHT;
    case OVERWORLD_WEATHER_DOWNPOUR:           return OVERWORLD_WEATHER_DOWNPOUR;
    case OVERWORLD_WEATHER_UNDERWATER_BUBBLES: return OVERWORLD_WEATHER_UNDERWATER_BUBBLES;
    case OVERWORLD_WEATHER_ROUTE119_CYCLE:     return sWeatherCycleRoute119[gSaveBlock1Ptr->weatherCycleStage];
    case OVERWORLD_WEATHER_ROUTE123_CYCLE:     return sWeatherCycleRoute123[gSaveBlock1Ptr->weatherCycleStage];
    default:                         return OVERWORLD_WEATHER_NONE;
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
        && (newWeather == OVERWORLD_WEATHER_RAIN || newWeather == OVERWORLD_WEATHER_RAIN_THUNDERSTORM
        || newWeather == OVERWORLD_WEATHER_ACID_RAIN))
        IncrementGameStat(GAME_STAT_GOT_RAINED_ON);
}
