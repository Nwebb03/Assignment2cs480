#include "utils.h"
#include "exec.h"
#include "parser.h"
#include <string>
#include <vector>
#include <iostream> // for std::cout
#include <readline/readline.h>
#include <readline/history.h>

using std::string;
using std::vector;

int main() {
    string input;
    Parser parser; // Create a Parser instance
    Executor executor; // Create an Executor instance
    vector<Command> commands; // To hold parsed commands

    while (true) {
        // Added history to shell
        // Readline handles the prompt, line editing and arrow key history navigation
        std::string prompt = getUsername() + "% ";
        char* raw_input = readline(prompt.c_str());
        if (!raw_input) break; // EOF (Ctrl+D) exits the shell
        input = string(raw_input);
        free(raw_input);

        // Add non-empty input to history (enables up/down arrow recall)
        if (!input.empty()) {
            add_history(input.c_str());
        }

        // Exit shell if user types "exit"
        if (input == "exit") break;
        // Skip empty input (just pressing Enter)
        if (input.empty()) continue;

        // Parse the input into commands and execute them (handles pipes, etc.)
        commands = parser.parseInput(input);
        executor.executePipeline(commands);
    }

    return 0;
}
