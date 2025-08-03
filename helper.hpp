#pragma once
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> loadAllShortcutsFromFile(bool& NEW_FILE_CREATION_FLAG);
bool isFileEmpty();
