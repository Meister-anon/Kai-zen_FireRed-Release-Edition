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

//note from GriffinR on porymap compatibility
/*
You can change them, Porymap just reads the names from
your file to populate the dropdown. 
It looks for names that start with WEATHER_,
if your new names don't start with that 
you can update your regex_weather setting
under Project Settings to tell Porymap how to find them
*/

//change mine to read overworld_weather_,

#define OVERWORLD_WEATHER_NONE               0
#define OVERWORLD_WEATHER_SUNNY_CLOUDS       1   // unused
#define OVERWORLD_WEATHER_SUNNY              2
#define OVERWORLD_WEATHER_RAIN               3   // unused
#define OVERWORLD_WEATHER_SNOW               4   // unused
#define OVERWORLD_WEATHER_RAIN_THUNDERSTORM  5   // unused
#define OVERWORLD_WEATHER_FOG_HORIZONTAL     6
#define OVERWORLD_WEATHER_DARKFOG_HORIZONTAL 7
#define OVERWORLD_WEATHER_VOLCANIC_ASH       8   // unused
#define OVERWORLD_WEATHER_SANDSTORM          9   // unused
#define OVERWORLD_WEATHER_FOG_DIAGONAL       10   // unused
#define OVERWORLD_WEATHER_UNDERWATER         11  // unused
#define OVERWORLD_WEATHER_SHADE              12
#define OVERWORLD_WEATHER_DROUGHT            13  // unused and broken in overworld
#define OVERWORLD_WEATHER_DOWNPOUR           14  // unused
#define OVERWORLD_WEATHER_UNDERWATER_BUBBLES 15  // unused //this and below is for sWeatherFuncs
#define OVERWORLD_WEATHER_ROUTE119_CYCLE     20  // unused
#define OVERWORLD_WEATHER_ROUTE123_CYCLE     21  // unused
#define OVERWORLD_WEATHER_ACID_RAIN          22
#define OVERWORLD_WEATHER_ACID_THUNDERSTORM  23
#define NUM_OVERWORLD_WEATHER

#endif  // GUARD_CONSTANTS_WEATHER_H
