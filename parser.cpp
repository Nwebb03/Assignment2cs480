#include "parser.h"
#include <sstream>   // for std::istringstream and std::getline
#include <vector>    // for std::vector

std::vector<Command> parseInput(const std::string& input) {
        std::vector<Command> commands;
        std::vector<std::string> segments = splitByPipe(input); // Store each command between the pipe into a different string

        for (const std::string& segment : segments) {
            Command cmd; // create a new command structure
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
    std::vector<std::string> splitByPipe(const std::string& input) {
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
            }
        }

        return segments; // return the list of clean, trimmed command segments
    }
