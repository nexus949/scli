#include <iostream>
#include <cctype>
#include <sstream>
#include "../headers/parser.hpp"

bool hasDoubleQuote(char character){
    return character == '"';
}

//check for out of bounds error. If the index is greater than the size of string then its trying to access out of bounds.
bool outOfBounds(int sizeOfString, int index, int offset){
    return (index + offset) >= sizeOfString;
}

//read focused separation logic
std::pair<std::string, bool> separateKey(const std::string& _read, int pairNumber){
    std::string key;
    std::stringstream ss;
   //to check if returned string is a valid key or error message we use integer, 1 = valid, 0 = error
    for(char c : _read){
        if(c == '='){
            return { key, 1 };
        }

        if(!std::isalnum(c) && c != '_'){
            ss << "[READ][ERROR] Key containing Whitespaces or Symbols Found ! at pair Number: " << pairNumber;
            return { ss.str(), 0 };
        }
        key += c;
    }

    ss << "[READ][ERROR] Delimeter '=' not found ! at pair Number: " << pairNumber;
    return { ss.str(), 0 };
}

//read focused separation logic
std::pair<std::string, bool> separateValue(const std::string& _read, int pairNumber){
    std::string value;
    std::stringstream ss;
    bool reachedDelimeter = false;

    std::size_t index = 0;

    for(index; index < _read.size(); ++index){
        if(_read[index] == '='){
            reachedDelimeter = true;

            //check for out of bounds as after this we will be accessing those indexes
            if(outOfBounds(_read.size(), index, 2)){
                ss << "[READ][ERROR] No Value present after '=', Expected Missing Path Value ! at pair Number: " << pairNumber;
                return { ss.str(), 0 };
            }
            //check the immediate next character of the delimeter (should be a ")
            if(!hasDoubleQuote(_read[index + 1])){
                ss << "[READ][ERROR] Value must start with double quotes after '=' ! at pair Number: " << pairNumber;
                return { ss.str(), 0 };
            }
            //check if the next character is alphanumeric or not
            else if(!std::isalnum(_read[index + 2])){
                ss << "[READ][ERROR] Path Value must start with Alphabets or Numbers after the first double quotes ! at pair Number: " << pairNumber;
                return { ss.str(), 0 };
            }
            //this is needed as we already check for the next 2 indexes, so increment the index by 2
            //Because the next term after '=' is a double quote and that terminates the reading and returns an error
            index += 2;
        }

        //check for inline trailing double quote
        if(hasDoubleQuote(_read[index])){
            //a trailing double quote inside path value indicates end of value.
            return { value, 1 };
        }

        //not reached '=' yet ? continue to loop
        if(!reachedDelimeter) continue;

        value += _read[index];
    }

    //check for closing a.k.a. trailing double quote
    if(_read.empty() || !hasDoubleQuote(_read.back())) {
        ss << "[READ][ERROR] No Closing double quotes found ! at pair Number: " << pairNumber;
        return { ss.str(), 0 };
    }

    return { value, 1 };
}

std::pair<std::string, std::string> parseShortcut(std::string& _read, bool& valid, int pairNumber){
    auto key = separateKey(_read, pairNumber);
    if(key.second == 0){
        valid = false;
        return { key.first, "invalid key !" };
    }

    auto value = separateValue(_read, pairNumber);
    if(value.second == 0){
        valid = false;
        return { value.first, "invalid value !" };
    }

    valid = true;
    return { key.first, value.first };
}

std::pair<std::string, bool> checkInputKey(std::string& key){
    //key check
    for(char k : key){
        if(!std::isalnum(k) && k != '_'){
            return { "[WRITE][ERROR] Invalid Key format. Key cannot contain spaces, symbols or special characters except for _(underscore)", 0 };
        }
    }

    return { key, 1 };
}
