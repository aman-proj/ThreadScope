#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace GpuSim {

std::vector<Instruction> Parser::parseFile(const std::string& filename) {
    std::vector<Instruction> instructions;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open kernel file: " << filename << std::endl;
        return instructions;
    }

    std::string line;
    int id = 0;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty and comments

        std::istringstream iss(line);
        std::string opStr;
        iss >> opStr;

        Opcode op = Opcode::UNKNOWN;
        std::string arg1 = "", arg2 = "", arg3 = "", arg4 = "";

        if (opStr == "LOAD") {
            op = Opcode::LOAD;
            iss >> arg1 >> arg2 >> arg3; // LOAD R1 A tid
        } else if (opStr == "STORE") {
            op = Opcode::STORE;
            iss >> arg1 >> arg2 >> arg3; // STORE C tid R3
        } else if (opStr == "COMPUTE") {
            op = Opcode::COMPUTE;
            iss >> arg1 >> arg2 >> arg3 >> arg4; // COMPUTE R3 R1 + R2
        } else if (opStr == "BRANCH") {
            op = Opcode::BRANCH;
            std::string rest;
            std::getline(iss, rest);
            arg1 = rest; // e.g. "tid % 2 == 0"
        }

        if (op != Opcode::UNKNOWN) {
            instructions.emplace_back(op, arg1, arg2, arg3, arg4, id++);
        }
    }

    return instructions;
}

} // namespace GpuSim
