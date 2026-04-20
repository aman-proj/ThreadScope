#include "performance_analyzer.h"
#include <iostream>

namespace GpuSim {

PerformanceMetrics PerformanceAnalyzer::analyze(const WarpSimulator& warp, const MemoryModel& memory, int numWarps) {
    PerformanceMetrics metrics;
    metrics.totalCycles = warp.totalCycles;
    metrics.divergenceCycles = warp.divergencePenalties;

    int totalMemoryAccesses = memory.coalescedAccesses + memory.uncoalescedAccesses;
    if (totalMemoryAccesses == 0) {
        metrics.coalescingEfficiency = 1.0f;
    } else {
        metrics.coalescingEfficiency = static_cast<float>(memory.coalescedAccesses) / totalMemoryAccesses;
    }

    // Mock occupancy calculation: say hardware max is 32 warps per SM
    int maxWarps = 32;
    metrics.theoreticalOccupancy = static_cast<float>(numWarps) / maxWarps;
    if (metrics.theoreticalOccupancy > 1.0f) metrics.theoreticalOccupancy = 1.0f;

    return metrics;
}

void PerformanceAnalyzer::printMetrics(const PerformanceMetrics& metrics) {
    std::cout << "--- PERFORMANCE METRICS ---\n";
    std::cout << "Latency (Cycles):     " << metrics.totalCycles << "\n";
    std::cout << "Divergence Penalty:   " << metrics.divergenceCycles << " cycles\n";
    std::cout << "Coalescing Efficiency:" << metrics.coalescingEfficiency * 100 << "%\n";
    std::cout << "Occupancy:            " << metrics.theoreticalOccupancy * 100 << "%\n";
    std::cout << "---------------------------\n";
}

} // namespace GpuSim
