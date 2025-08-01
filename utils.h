//## Names
//- Nate Webb cssc1467
//- Noah Bakayou cssc1409

//## Class Information
//- CS480-02-Sum202

//## Assignment Information
//- Assignment #2 - basic shell

//Filename: utils.h


#ifndef UTILS_H
#define UTILS_H

#include <string>

// Prints the shell prompt (e.g., "cssc0000% ")
void printPrompt();

// Prints a standardized error message
void printError(const std::string &msg);


// Retrieves the current username (via getlogin() or fallback)
std::string getUsername();

std::string getUserInput();

#endif