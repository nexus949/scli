#pragma once
#include <utility>
#include <string>

bool hasDoubleQuote(char character);
bool outOfBounds(int sizeOfString, int index, int offset);
std::pair<std::string, bool> separateKey(std::string& _read);
std::pair<std::string, bool> separateValue(std::string& _read);
std::pair<std::string, std::string> parseShortcut(std::string& _read, bool& valid);
std::pair<std::string, bool> checkInputParams(std::string& key, std::string& value);
