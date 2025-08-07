/*

COMMANDS LIST
//
1. scli help - Displays list of all commands and what they do.
2. scli list - Lists all the available shortcuts (key value pairs).
3. scli open key - Opens the particular directory corresponding to that key.
4. scli add key value - Adds a key value shortcut pair.
5. scli remove key - Removes the particular key value pair corresponding to that key.

*/

#pragma once
#include <string>

//this helps to understand which command is using helper functions
enum command {
    HELP,
    LIST,
    OPEN,
    ADD,
    REMOVE
};

void helpCmd();
void listShortcuts();
void addShortcut(std::string& key, std::string& value);
void openShortcut(std::string& key);
void removeShortcut(std::string& key);
bool duplicateExists();
