//## Names
//- Nate Webb cssc1467
//- Noah Bakayou cssc1409

//## Class Information
//- CS480-02-Sum202

//## Assignment Information
//- Assignment #2 - basic shell

//Filename: parser.cpp
#include "parser.h"
#include <sstream>   // for std::istringstream and std::getline
#include <vector>    // for std::vector

std::vector<Command> Parser::parseInput(const std::string& input) {
        std::vector<Command> commands;
        std::vector<std::string> segments = splitByPipe(input); // Store each command between the pipe into a different string

        for (const std::string& segment : segments) {
            Command cmd; // create a new command structure
            cmd.original = segment; // Save the original segment
            std::istringstream ss(segment); // create a stream for the segment
            ss >> cmd.executable;

            // Check if there's an argument
            if (ss >> cmd.arg) {
                cmd.hasArg = true; 
            } else {
                cmd.hasArg = false;
            }

            commands.push_back(cmd); // add the command to the list
        }

        return commands;
    }

    // Splits the input string by the '|' character into a list of command segments.
    std::vector<std::string> Parser::splitByPipe(const std::string& input) {
        std::vector<std::string> segments;  // stores the split command segments
        std::string segment;                // holds each extracted substring
        std::istringstream stream(input);  // create a stream from the input string

        // Read the input line segment-by-segment, splitting on '|'
        while (std::getline(stream, segment, '|')) {
            // Trim leading whitespace
            size_t start = segment.find_first_not_of(" ");
            // Trim trailing whitespace
            size_t end = segment.find_last_not_of(" ");

            // If the segment contains non-whitespace characters, add it to the result
            if (start != std::string::npos && end != std::string::npos) {
                // Extract the trimmed substring and add to segments
                segments.push_back(segment.substr(start, end - start + 1));
            } else {
                // If the segment is empty or only whitespace, add an empty string
                segments.push_back("");
            }
        }
        // If the input ends with a pipe, add an empty segment to represent the missing command
        if (!input.empty() && input.back() == '|') {
            segments.push_back("");
        }
        return segments; // return the list of clean, trimmed command segments
    }

// Returns true if the command vector is valid according to assignment rules
bool Parser::validateCommands(const std::vector<Command>& commands) const {
    for (const Command& cmd : commands) {
        // Command must have an executable and original segment must not be empty or whitespace
        std::string trimmed = cmd.original;
        trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
        trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);
        if (trimmed.empty() || cmd.executable.empty()) return false;
        // Strictly check for more than one argument using the original segment
        std::istringstream ss(cmd.original);
        std::string word1, word2, word3;
        ss >> word1; // executable
        ss >> word2; // argument (if any)
        if (ss >> word3) return false; // more than one argument
    }
    return true;
}
