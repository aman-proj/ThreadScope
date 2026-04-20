#pragma once
#include <string>
#include <vector>

namespace GpuSim {

enum class Opcode {
    LOAD,
    STORE,
    COMPUTE,
    BRANCH,
    SYNC,
    UNKNOWN
};

struct Instruction {
    Opcode op;
    std::string arg1;
    std::string arg2;
    std::string arg3;
    std::string arg4;
    int id;

    Instruction(Opcode o, const std::string& a1, const std::string& a2, const std::string& a3, const std::string& a4, int i)
        : op(o), arg1(a1), arg2(a2), arg3(a3), arg4(a4), id(i) {}
};

} // namespace GpuSim
