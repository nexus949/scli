#pragma once
#include <utility>
#include <string>

bool hasDoubleQuote(char character);
bool outOfBounds(int sizeOfString, int index, int offset);
std::pair<std::string, bool> separateKey(const std::string& _read, int pairNumber);
std::pair<std::string, bool> separateValue(const std::string& _read, int pairNumber);
std::pair<std::string, std::string> parseShortcut(std::string& _read, bool& valid, int pairNumber);
std::pair<std::string, bool> checkInputKey(std::string& key);
