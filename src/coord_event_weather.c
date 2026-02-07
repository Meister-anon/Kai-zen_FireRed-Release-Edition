#include "global.h"
#include "constants/weather.h"

// These were all dummied out because it's always sunny in Viridian
void WeatherCoordEvent_SunnyClouds(void) {}
void WeatherCoordEvent_Sunny(void) {}
void WeatherCoordEvent_Rain(void) {}
void WeatherCoordEvent_Snow(void) {}
void WeatherCoordEvent_RainThunderstorm(void) {}
void WeatherCoordEvent_FogHorizontal(void) {}
void WeatherCoordEvent_VolcanicAsh(void) {}
void WeatherCoordEvent_Sandstorm(void) {}
void WeatherCoordEvent_FogDiagonal(void) {}
void WeatherCoordEvent_Underwater(void) {}
void WeatherCoordEvent_Shade(void) {}
void WeatherCoordEvent_Route119Cycle(void) {}
void WeatherCoordEvent_Route123Cycle(void) {}

static struct {
    u8 weatherId;
    void (*callback)(void);
} const sWeatherCoordEventFuncs[] = {
    {OVERWORLD_WEATHER_SUNNY_CLOUDS,          WeatherCoordEvent_SunnyClouds     },
    {OVERWORLD_WEATHER_SUNNY,                 WeatherCoordEvent_Sunny           },
    {OVERWORLD_WEATHER_RAIN,        WeatherCoordEvent_Rain            },
    {OVERWORLD_WEATHER_SNOW,        WeatherCoordEvent_Snow            },
    {OVERWORLD_WEATHER_RAIN_THUNDERSTORM,     WeatherCoordEvent_RainThunderstorm},
    {OVERWORLD_WEATHER_FOG_HORIZONTAL,        WeatherCoordEvent_FogHorizontal   },
    {OVERWORLD_WEATHER_VOLCANIC_ASH,          WeatherCoordEvent_VolcanicAsh     },
    {OVERWORLD_WEATHER_SANDSTORM,   WeatherCoordEvent_Sandstorm       },
    {OVERWORLD_WEATHER_FOG_DIAGONAL,          WeatherCoordEvent_FogDiagonal     },
    {OVERWORLD_WEATHER_UNDERWATER,            WeatherCoordEvent_Underwater      },
    {OVERWORLD_WEATHER_SHADE,                 WeatherCoordEvent_Shade           },
    {OVERWORLD_WEATHER_ROUTE119_CYCLE,        WeatherCoordEvent_Route119Cycle   },
    {OVERWORLD_WEATHER_ROUTE123_CYCLE,        WeatherCoordEvent_Route123Cycle   },
    {OVERWORLD_WEATHER_DARKFOG_HORIZONTAL,    WeatherCoordEvent_FogHorizontal   }
};//seems this isn't relevant to anything the sweatherfuncs is the important one

void DoCoordEventWeather(u8 weatherId)
{
    u8 i;
    for (i = 0; i < NELEMS(sWeatherCoordEventFuncs); i++)
    {
        if (sWeatherCoordEventFuncs[i].weatherId == weatherId)
        {
            sWeatherCoordEventFuncs[i].callback();
            return;
        }
    }
}
