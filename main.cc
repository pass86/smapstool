#include "smapstool.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: smapstool command file" << std::endl;
        std::cout << "code: Print code memory" << std::endl;
        return -1;
    }
    SmapsTool tool;
    if (!tool.LoadFile(argv[2]))
        return -1;
    std::string command(argv[1]);
    if (command == "code")
        tool.PrintCodeMemory();
    return 0;
}
