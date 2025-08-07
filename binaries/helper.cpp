#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "../headers/helper.hpp"
#include "../headers/parser.hpp"
#include "../headers/commandTypes.hpp"

bool isFileEmpty(){
    std::ifstream fileIn("scli_shortcuts.txt", std::ios::ate);

    //check for non existent shortcut file
    if (!fileIn.is_open()) {
        return true; // Treat missing file as empty
    }

    return fileIn.tellg() == 0;
}

std::unordered_map<std::string, std::string> loadAllShortcutsFromFile(bool& NEW_FILE_CREATION_FLAG, Commands cmd){
    std::unordered_map<std::string, std::string> shortcuts;

    std::ifstream fileIn("scli_shortcuts.txt");
    if(!fileIn){
        if(cmd == Commands::ADD){
            //this ensures that the error message is not printed when user is entering their first shortcut and the shortcut file does not exists.
            NEW_FILE_CREATION_FLAG = true;
            return shortcuts;
        }

        std::cerr << "Error opening shortcuts file, No file present, add shortcuts to create a file." << std::endl;
        return shortcuts;
    }

    std::string _read;
    int pairNumber = 1;
    bool valid;

    while(std::getline(fileIn, _read)){
        auto [s_key, s_value] = parseShortcut(_read, valid, pairNumber);

        if(!valid){
            std::cout << s_key << std::endl;
            fileIn.close();
            shortcuts.clear();
            return shortcuts;
        }

        //check for duplicates
        if(shortcuts.find(s_key) != shortcuts.end()){
            std::cout << "Duplicate found at pair Number: " << pairNumber << ", " << shortcuts[s_key] << std::endl;
            fileIn.close();
            shortcuts.clear();
            return shortcuts;
        }
        else{
            //store the value in the map
            shortcuts[s_key] = s_value;
            pairNumber += 1;
        }

    }

    return shortcuts;
}

