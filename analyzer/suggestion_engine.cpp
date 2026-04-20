#include "suggestion_engine.h"
#include <iostream>

namespace GpuSim {

std::vector<std::string> SuggestionEngine::generateSuggestions(const PerformanceMetrics& metrics) {
    std::vector<std::string> suggestions;

    if (metrics.divergenceCycles > 0) {
        suggestions.push_back("High Warp Divergence detected. Suggestion: Minimize branches within warps, or refactor conditionals to avoid thread execution serialization.");
    }

    if (metrics.coalescingEfficiency < 0.8f) {
        suggestions.push_back("Poor Memory Coalescing. Suggestion: Ensure threads in a warp access memory in a contiguous pattern (e.g., array[tid]).");
    }

    if (metrics.theoreticalOccupancy < 0.5f) {
        suggestions.push_back("Low Occupancy. Suggestion: Increase the number of threads per block, or reduce register/shared memory usage to allow more active warps.");
    }

    if (suggestions.empty()) {
        suggestions.push_back("Great job! Kernel performance looks healthy within simulated boundaries.");
    }

    return suggestions;
}

void SuggestionEngine::printSuggestions(const std::vector<std::string>& suggestions) {
    std::cout << "--- OPTIMIZATION SUGGESTIONS ---\n";
    for (const auto& sig : suggestions) {
        std::cout << "[*] " << sig << "\n";
    }
}

} // namespace GpuSim
