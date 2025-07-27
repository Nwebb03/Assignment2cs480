#include <string>
#include <iostream>
#include <vector>
class Parser {
public:
    std::vector<Command> parseInput(const std::string& input);
private:
    // Splits the input string by the '|' character into a list of command segments.
    std::vector<std::string> splitByPipe(const std::string& input);

};

struct Command {
    std::string executable;
    std::string arg;
    bool hasArg;

};