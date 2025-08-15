#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <cstdlib>
#include "../headers/parser.hpp"
#include "../headers/helper.hpp"
#include "../headers/commands.hpp"
#include "../headers/commandTypes.hpp"

//this flag is used in the addShortcut() function to determine wheather the shortcut file needs to created or not.
bool NEW_FILE_CREATION_FLAG = false;

void helpCmd(){
    std::cout << "[scli Command List]" << "\n" << "\n";
    std::cout << "scli help - Displays list of all commands." << "\n";
    std::cout << "scli list - Displays list of all available shortcuts." << "\n";
    std::cout << "scli open <key> - Opens the particular folder or file corresponding to that specific key." << "\n";
    std::cout << "scli add <key> <value> - Adds a shortcut. Key is the term used to refer to it (must be unique) and value is the path to the folder or file." << "\n";
    std::cout << "scli remove <key> - Removes the shortcut corresponding to that key." << "\n" << "\n";
    std::cout << "Remember to replace <key> and <value> with your desired term and path." << "\n";
    return;
}

void listShortcuts(){
    if(isFileEmpty()) return;

    auto shortcuts = loadAllShortcutsFromFile(NEW_FILE_CREATION_FLAG, Commands::LIST);
    int pairNumber = 1;

    if(shortcuts.empty()) return;

    for(auto& pair : shortcuts){
        std::cout << pairNumber << ". " << pair.first << '=' << '"' << pair.second << '"' << "\n";
        pairNumber += 1;
    }
}

void openShortcut(std::string& key){
    //just in case duplicate keys are present it opens the first occurance of the key (can only be done if the shortcurts file is edited manually).
    auto shortcuts = loadAllShortcutsFromFile(NEW_FILE_CREATION_FLAG, Commands::OPEN);

    //if key is not present
    if(!shortcuts.count(key)){
        std::cout << "No valid Key Found ! Use 'add' to add shortcuts..." << std::endl;
        return;
    }

    //check if the path is valid
    if(!std::filesystem::exists(shortcuts[key])){
        std::cout << "Path associated with key: " << key << " is not a valid path..." << std::endl;
        return;
    }

    // a \" denotes a double quote inside a string literal so we do start "" (result of \"\") then a starting " using another \" and we close the string with ";
    // we then add the path and concat another string literal which contains another "(result of \") inside "";
    std::string command = "start \"\" \"" + shortcuts[key] + "\"";
    std::system(command.c_str()); //c_str returns a pointer to the command string's first element !

}

void addShortcut(std::string& key, std::string& value){
    //key validation check. If the input key is invalid return then and theres
    auto keyValidation = checkInputKey(key); //returns a std::pair<std::string, bool>
    if(keyValidation.second == 0){
        std::cout << keyValidation.first << std::endl;
        return;
    }

    auto shortcuts = loadAllShortcutsFromFile(NEW_FILE_CREATION_FLAG, Commands::ADD); //returns a std::unordered_map<std::string, std::string>

    //check if the incoming key is present in the loaded map.
    if(shortcuts.count(key)){
        std::cout << "[ERROR] This key already exists. Try another key..." << std::endl;
        return;
    }

    //only return if the shortcut file is not empty but shortcut map is empty. This shows that there already is a key present.
    if(shortcuts.empty() && !isFileEmpty()) {
        return;
    }

    std::ofstream fileOut;
    if(NEW_FILE_CREATION_FLAG){
        fileOut.open("scli_shortcuts.txt");
    }
    else{
        fileOut.open("scli_shortcuts.txt", std::ios::app);
    }

    //open file in append mode and get cursor position using tellp(), If file not empty insert a newline.
    if(fileOut.tellp() != 0){
        fileOut << "\n";
    }

    fileOut << key << '=' << '"' << value << '"' << "\n";
    fileOut.close();
    std::cout << "Shortcut added successfully !" << std::endl;
}

void removeShortcut(std::string& key){
    if(isFileEmpty()) return;

    auto shortcuts = loadAllShortcutsFromFile(NEW_FILE_CREATION_FLAG, Commands::REMOVE);
    int pairNumber = 1;

    if(shortcuts.empty()) return;

    std::ofstream fileOut("scli_shortcuts.txt");
    for(auto& pair : shortcuts){
        if(pair.first == key) continue;
        fileOut << pair.first << '=' << '"' << pair.second << '"' << "\n";
    }

    fileOut.close();
}
