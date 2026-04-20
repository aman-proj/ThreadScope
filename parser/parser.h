#pragma once
#include <string>
#include <vector>
#include "../core/ir.h"

namespace GpuSim {

class Parser {
public:
    // Parses a simple file and returns intermediate representation.
    // Format supported:
    // LOAD <reg> <array> <index>
    // STORE <array> <index> <reg>
    // COMPUTE <reg> <arg1> <op> <arg2>
    // BRANCH <condition>
    static std::vector<Instruction> parseFile(const std::string& filename);
};

} // namespace GpuSim
