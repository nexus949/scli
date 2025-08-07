#pragma once
#include <string>
#include <unordered_map>
#include "../headers/commandTypes.hpp"

std::unordered_map<std::string, std::string> loadAllShortcutsFromFile(bool& NEW_FILE_CREATION_FLAG, Commands cmd);
bool isFileEmpty();
