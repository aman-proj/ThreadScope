#include "warp_simulator.h"
#include <iostream>

namespace GpuSim {

WarpSimulator::WarpSimulator(int id) : warpId(id), totalCycles(0), divergencePenalties(0) {
    for (int i = 0; i < 32; ++i) {
        threads.emplace_back(id * 32 + i);
    }
}

void WarpSimulator::execute(const std::vector<Instruction>& instructions, MemoryModel& memory) {
    int maxPc = static_cast<int>(instructions.size());
    bool allDone = false;

    while (!allDone) {
        allDone = true;
        
        int currentPc = -1;
        for (const auto& t : threads) {
            if (t.active && t.pc < maxPc) {
                currentPc = t.pc;
                allDone = false;
                break;
            }
        }
        
        if (allDone) break;

        const Instruction& inst = instructions[currentPc];
        std::vector<MemoryAccess> memAccesses;

        for (auto& t : threads) {
            if (!t.active || t.pc != currentPc) continue;

            if (inst.op == Opcode::LOAD) {
                int address = memory.getBaseAddress(inst.arg2) + (t.id * 4); 
                memAccesses.push_back({t.id, address, false});
                t.setRegister(inst.arg1, 1.0f);
            } else if (inst.op == Opcode::STORE) {
                int address = memory.getBaseAddress(inst.arg1) + (t.id * 4);
                memAccesses.push_back({t.id, address, true});
            } else if (inst.op == Opcode::COMPUTE) {
                t.setRegister(inst.arg1, 2.0f); 
            } else if (inst.op == Opcode::BRANCH) {
                // Hardcoded mock divergence check
            }
            t.pc++;
        }

        memory.simulateWarpAccess(memAccesses);

        if (inst.op == Opcode::BRANCH && inst.arg1.find("divergence") != std::string::npos) {
            divergencePenalties += 10; 
            totalCycles += 10;
        }

        totalCycles++;
    }
}

} // namespace GpuSim
