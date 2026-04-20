#pragma once
#include <map>
#include <string>

namespace GpuSim {

class Thread {
public:
    int id;
    int pc; // Program Counter
    bool active;
    std::map<std::string, float> registers;

    Thread(int threadId) : id(threadId), pc(0), active(true) {}

    float getRegister(const std::string& reg) {
        return registers[reg];
    }

    void setRegister(const std::string& reg, float value) {
        registers[reg] = value;
    }
};

} // namespace GpuSim
