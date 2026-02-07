#ifndef GUARD_CONSTANTS_WEATHER_H
#define GUARD_CONSTANTS_WEATHER_H

//interacting w battle weather constants
//need rename these
//OW_WEATHER
//OVERWORLD_WEATHER

//sigh with freeze change
//snow defaults to snow
//so would need make hail ow weather

//RAIN snow and sandstorm are the ones
//that interfere w battle weather constants

#define WEATHER_NONE               0
#define WEATHER_SUNNY_CLOUDS       1   // unused
#define WEATHER_SUNNY              2
#define OVERWORLD_WEATHER_RAIN     3   // unused
#define WEATHER_SNOW               4   // unused
#define WEATHER_RAIN_THUNDERSTORM  5   // unused
#define WEATHER_FOG_HORIZONTAL     6
#define WEATHER_DARKFOG_HORIZONTAL 7
#define WEATHER_VOLCANIC_ASH       8   // unused
#define WEATHER_SANDSTORM          9   // unused
#define WEATHER_FOG_DIAGONAL       10   // unused
#define WEATHER_UNDERWATER         11  // unused
#define WEATHER_SHADE              12
#define WEATHER_DROUGHT            13  // unused and broken in overworld
#define WEATHER_DOWNPOUR           14  // unused
#define WEATHER_UNDERWATER_BUBBLES 15  // unused //this and below is for sWeatherFuncs
#define WEATHER_ROUTE119_CYCLE     20  // unused
#define WEATHER_ROUTE123_CYCLE     21  // unused
#define OVERWORLD_WEATHER_ACID_RAIN          22
#define OVERWORLD_WEATHER_ACID_THUNDERSTORM    23

#endif  // GUARD_CONSTANTS_WEATHER_H
