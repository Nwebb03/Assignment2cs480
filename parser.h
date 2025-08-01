//## Names
//- Nate Webb cssc1467
//- Noah Bakayou cssc1409

//## Class Information
//- CS480-02-Sum202

//## Assignment Information
//- Assignment #2 - basic shell

//Filename: parser.h
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>

struct Command {
    std::string executable;
    std::string arg;
    bool hasArg;
    std::string original; // Store the original segment for validation
};

class Parser {
public:
    std::vector<Command> parseInput(const std::string& input);
    // Returns true if the command vector is valid according to assignment rules
    bool validateCommands(const std::vector<Command>& commands) const;
private:
    // Splits the input string by the '|' character into a list of command segments.
    std::vector<std::string> splitByPipe(const std::string& input);
};

#endif