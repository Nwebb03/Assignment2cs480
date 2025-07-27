#ifndef EXEC_H
#define EXEC_H

#include "parser.h"
#include <vector>

class Executor {
public:
    // Execute a pipeline of commands (supports 1 or many pipes)
    void executePipeline(const std::vector<Command> &commands);

private:
    // Build argv[] for exec calls
    char** buildArgv(const Command &cmd);

    // Free argv[] memory
    void freeArgv(char** argv);

    // Execute command using correct exec variant
    void executeCommand(const Command &cmd);
};

#endif
