#include <iostream>
#include "../headers/parser.hpp"
#include "../headers/commands.hpp"

int main(int argc, char* argv[]){

    if (argc < 2){
        std::cout << "No command given. Use 'scli help'." << "\n";
        return 1;
    }

    std::string command = argv[1];

    //help command
    if (command == "help" && argc == 2){
        helpCmd();
    }
    //list command
    else if(command == "list" && argc == 2){
        listShortcuts();
    }
    //open command
    else if(command == "open" && argc == 3){
        std::string key = argv[2];
        openShortcut(key);
    }
    //add command
    else if(command == "add" && argc == 4){
        std::string key = argv[2];
        std::string value = argv[3];

        addShortcut(key, value);
    }
    //remove command
    else if(command == "remove" && argc == 3){
        std::string key = argv[2];
        removeShortcut(key);
    }
    else{
        std::cout << "Invalid or Insufficient arguments." << "\n";
        std::cout << "Use 'scli help' to view all available commands";
    }

    return 0;
}
