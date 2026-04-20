#pragma once
#include "../core/warp_simulator.h"
#include "../core/memory_model.h"

namespace GpuSim {

struct PerformanceMetrics {
    int totalCycles;
    int divergenceCycles;
    float coalescingEfficiency; // 0.0 to 1.0
    float theoreticalOccupancy; // 0.0 to 1.0
};

class PerformanceAnalyzer {
public:
    static PerformanceMetrics analyze(const WarpSimulator& warp, const MemoryModel& memory, int numWarps);
    static void printMetrics(const PerformanceMetrics& metrics);
};

} // namespace GpuSim
