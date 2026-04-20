#pragma once
#include "performance_analyzer.h"
#include <vector>
#include <string>

namespace GpuSim {

class SuggestionEngine {
public:
    static std::vector<std::string> generateSuggestions(const PerformanceMetrics& metrics);
    static void printSuggestions(const std::vector<std::string>& suggestions);
};

} // namespace GpuSim
