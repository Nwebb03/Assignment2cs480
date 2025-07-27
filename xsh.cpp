#include "utils.h"
#include "exec.h"
#include "parser.h"
#include <string>
#include <vector>
#include <iostream> // for std::cout

using std::string;
using std::vector;

int main() {
    string input;
    Parser parser; // Create a Parser instance
    Executor executor; // Create an Executor instance
    vector<Command> commands; // To hold parsed commands

    while (true) {
        printPrompt();
        input = getUserInput();
        if (input == "exit") break; // exit conditon
        if (input.empty()) continue; // skip empty input
        commands = parser.parseInput(input); // Parse the input into commands
        executor.executePipeline(commands);   // Execute the parsed commands
    }

    return 0;
}
