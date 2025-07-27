#include "exec.h"
#include "parser.h"
#include "utils.h"
#include <iostream>
#include <cstring> // for strdup and free
#include <vector>
#include <unistd.h> // for execvp



std::vector<Command> commands; // List of commands to execute

void executePipeline(const std::vector<Command> &commands) {
    for (const Command &cmd : commands) {
        if (cmd.executable.empty()) {
            printError("Empty command found, skipping.");
            continue; // Skip empty commands
        }
        executeCommand(cmd); // Execute each command in the pipeline
    }
}

char ** buildArgv(const Command &cmd) {
    char **argv = new char*[3]; // Allocate memory for argv (2 args + null terminator) 1st one is the executable, 2nd is the argument, and 3rd is the null terminator
    argv[0] = strdup(cmd.executable.c_str()); // Copy the executable name

    if (cmd.hasArg) {
        argv[1] = strdup(cmd.arg.c_str()); // Copy argument if present
    } else {
        argv[1] = nullptr; // No argument
    }
    argv[2] = nullptr; // Null terminator for execvp
    return argv;
}

void freeArgv(char **argv) {
    if (argv) {
        for (int i = 0; argv[i] != nullptr; ++i) {
            free(argv[i]); // Free each argument
        }
        delete[] argv; // Free the array itself
    }
}

void executeCommand(const Command &cmd) {
    char **argv = buildArgv(cmd); // Build the argument array
    if (execvp(argv[0], argv) == -1) { // Execute the command
        perror("execvp failed"); // Print error if execvp fails
    }
    freeArgv(argv); // Free the allocated memory for argv
}