#pragma once

#include <memory>
#include <string>
#include <windows.h>
#include <vector>
#include "player.hpp"

using std::string;

class Settings
{
public:

	struct
	{
		int horizontal{ 100 };
		int vertical{ 100 };
	}velocity;

	struct
	{
		int fov{ 80 };
		int speed{ 50 };
		int dist{ 6 };
	}aimassist;

	struct
	{
		std::vector<PlayerPtr> legit;
	}antibot;

	struct
	{
		std::string version{ "" };
	}misc;
};

inline std::unique_ptr<Settings> settings;

void Settings_Initialize();