#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>

#define MAKE_ENUM(name, ...) enum class name { __VA_ARGS__}; \
static std::vector<std::string> Enum_##name##_init()\
{\
    const std::string content = #__VA_ARGS__; \
    std::vector<std::string> str;\
    size_t len = content.length();\
    std::ostringstream temp;\
    for(size_t i = 0; i < len; i ++) {\
    if(isspace(content[i])) continue;\
    else if(content[i] == ',') {\
    str.push_back(temp.str());\
    temp.str(std::string());}\
    else temp<< content[i];}\
    str.push_back(temp.str());\
    return str;\
}\
static const std::vector<std::string> Enum_##name##_str_vec = Enum_##name##_init();\
static std::string to_string(name val)\
{\
    return Enum_##name##_str_vec[static_cast<size_t>(val)];\
}\

enum class eActorType
{
	User,
	Monster
};


enum eAnimState
{
	Idle = 0,
	Attack1 = 2,
	Attack2 = 3,
	Move = 4,
	Dead = 5
};

enum eMonsterType
{
	Beholder,
	BlackKnight,
	Chest,
	Crab,
	Demon,
	Lizard
};

//MAKE_ENUM(Define,
//	LevelPoint);
enum Define
{
	LevelPoint
};






