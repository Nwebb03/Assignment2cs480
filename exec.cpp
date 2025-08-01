//## Names
//- Nate Webb cssc1467
//- Noah Bakayou cssc1409

//## Class Information
//- CS480-02-Sum202

//## Assignment Information
//- Assignment #2 - basic shell

//Filename: exec.cpp


#include "exec.h"
#include "parser.h"
#include "utils.h"
#include <iostream>
#include <cstring> // for strdup and free
#include <vector>
#include <unistd.h> // for execvp
#include <sys/wait.h> // for waitpid

std::vector<Command> commands; // List of commands to execute

void Executor::executePipeline(const std::vector<Command> &commands) {
    size_t n = commands.size();
    // If no commands, do nothing
    if (n == 0) return;
    // If only one command, run it normally (no pipes needed)
    if (n == 1) {
        executeCommand(commands[0]);
        return;
    }

    // Store child process IDs for waiting later
    std::vector<pid_t> pids;
    int prev_fd = -1; // File descriptor for previous pipe's read end
    // Loop through each command in the pipeline
    for (size_t i = 0; i < n; ++i) {
        int pipefd[2];
        // If not the last command, create a pipe
        // Not necessary for the last command, because the last command’s input comes from the read end of the previous pipe (set up by the previous command).
        if (i < n - 1) {
            if (pipe(pipefd) == -1) { // creates a pipe for the command, if it returns 0, it means it is successful
                perror("pipe failed");
                return;
            }
        }

        pid_t pid = fork(); // Fork a child process
        if (pid == 0) {
            // --- Child process ---
            // This part connects the child processes together using pipes

            // If not the first command, redirect stdin to previous pipe's read end
            if (i > 0) {
                dup2(prev_fd, 0); // stdin from previous pipe
                close(prev_fd);
            }
            // If not the last command, redirect stdout to current pipe's write end
            if (i < n - 1) {
                close(pipefd[0]); // close unused read end
                dup2(pipefd[1], 1); // stdout (1) to write end of pipe
                close(pipefd[1]);
            }
            // Build argv and execute the command
            char **argv = buildArgv(commands[i]);
            execvp(argv[0], argv);
            // If execvp fails, print error and exit child
            perror("execvp failed");
            exit(1);
        } else if (pid > 0) {
            // --- Parent process ---
            pids.push_back(pid); // Save child PID
            // Close previous pipe's read end (no longer needed)
            if (i > 0) close(prev_fd);
            // If not the last command, save current pipe's read end for next command
            if (i < n - 1) {
                close(pipefd[1]); // close unused write end
                prev_fd = pipefd[0]; // save read end for next command
            }
        } else {
            // Fork failed
            perror("fork failed");
            return;
        }
    }
    // Wait for all child processes to finish
    // ex: if a sort is the last command and is taking a long time, it will wait for the sort to finish before showing cssc0000% prompt again
    for (pid_t pid : pids) {
        int status;
        waitpid(pid, &status, 0);
    }
}

char ** Executor::buildArgv(const Command &cmd) {
    char **argv = new char*[3]; // Allocate memory for argv (2 args + null terminator) 1st one is the executable, 2nd is the argument and 3rd is the null terminator
    argv[0] = strdup(cmd.executable.c_str()); // Copy the executable name

    if (cmd.hasArg) {
        argv[1] = strdup(cmd.arg.c_str()); // Copy argument if present
    } else {
        argv[1] = nullptr; // No argument
    }
    argv[2] = nullptr; // Null terminator for execvp
    return argv;
}

void Executor::freeArgv(char **argv) {
    if (argv) {
        for (int i = 0; argv[i] != nullptr; ++i) {
            free(argv[i]); // Free each argument
        }
        delete[] argv; // Free the array itself
    }
}

void Executor::executeCommand(const Command &cmd) {
    char **argv = buildArgv(cmd);

    pid_t pid = fork(); // Create a child process

    if (pid == 0) {
        // This is the child process
        execvp(argv[0], argv);
        // If execvp fails, print error and exit child
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        // This is the parent process (the shell)
        int status;
        waitpid(pid, &status, 0); // Wait for the child to finish
    } else {
        // Fork failed
        perror("fork failed");
    }

    freeArgv(argv); // Clean up memory
}