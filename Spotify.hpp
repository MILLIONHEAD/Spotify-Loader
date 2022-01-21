#pragma once
#include "cammon.hpp"

class folder
{
public:
	void setup();
	void removeall();
	std::string set_folder(std::string title);
public:
	std::string save_path_folder{ "saveFolder.txt" };
	std::string spotify_path;
};

inline std::unique_ptr<folder> g_folder;