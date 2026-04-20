#pragma once
#include <vector>
#include "thread.h"
#include "memory_model.h"
#include "ir.h"

namespace GpuSim {

class WarpSimulator {
public:
    std::vector<Thread> threads;
    int warpId;
    int totalCycles;
    int divergencePenalties;

    WarpSimulator(int id);
    void execute(const std::vector<Instruction>& instructions, MemoryModel& memory);
};

} // namespace GpuSim
