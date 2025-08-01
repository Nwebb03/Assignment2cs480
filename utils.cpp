//## Names
//- Nate Webb cssc1467
//- Noah Bakayou cssc1409

//## Class Information
//- CS480-02-Sum202

//## Assignment Information
//- Assignment #2 - basic shell

//Filename: utils.cpp

#include "utils.h"
#include <iostream>
#include <unistd.h>

void printPrompt() {
    std::cout << getUsername() << "% " << std::flush;
}

std::string getUsername() {
    char *username = getlogin();
    if (username) {
        return std::string(username);
    } else {
        // Fallback to environment variable
        const char *envUsername = getenv("USER");
        if (envUsername) {
            return std::string(envUsername);
        } else {
            return "unknown_user"; // Fallback if both methods fail
        }
    }
}

void printError(const std::string &msg) {
    std::cerr << "Error: " << msg << std::endl;
}

std::string getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

