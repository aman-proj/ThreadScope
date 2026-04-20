#include <iostream>
#include <fstream>
#include "parser/parser.h"
#include "core/warp_simulator.h"
#include "core/memory_model.h"
#include "analyzer/performance_analyzer.h"
#include "analyzer/suggestion_engine.h"

using namespace GpuSim;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <kernel_file.txt>\n";
        return 1;
    }

    std::string kernelFile = argv[1];
    std::cout << "Loading Kernel: " << kernelFile << "...\n";

    auto instructions = Parser::parseFile(kernelFile);
    if (instructions.empty()) {
        std::cerr << "No instructions to execute.\n";
        return 1;
    }

    // Initialize Simulator
    int numWarps = 4; // Mocking a 128-thread block (4 warps)
    MemoryModel memory(1024 * 1024); // 1 MB mock memory

    int totalCycles = 0;
    int totalDivergencePenalties = 0;

    for (int i = 0; i < numWarps; ++i) {
        WarpSimulator warp(i);
        warp.execute(instructions, memory);
        totalCycles += warp.totalCycles;
        totalDivergencePenalties += warp.divergencePenalties;
    }

    // Creating average dummy metrics over the warps
    WarpSimulator combinedWarpData(0);
    combinedWarpData.totalCycles = totalCycles / numWarps;
    combinedWarpData.divergencePenalties = totalDivergencePenalties; 

    // Analyzer & Suggestions
    auto metrics = PerformanceAnalyzer::analyze(combinedWarpData, memory, numWarps);
    PerformanceAnalyzer::printMetrics(metrics);
    
    auto suggestions = SuggestionEngine::generateSuggestions(metrics);
    SuggestionEngine::printSuggestions(suggestions);

    // Export to JSON for AI visualization script
    std::ofstream jsonFile("output/metrics.json");
    if (jsonFile.is_open()) {
        jsonFile << "{\n";
        jsonFile << "  \"latency\": " << metrics.totalCycles << ",\n";
        jsonFile << "  \"divergence\": " << metrics.divergenceCycles << ",\n";
        jsonFile << "  \"coalescing_efficiency\": " << metrics.coalescingEfficiency << ",\n";
        jsonFile << "  \"occupancy\": " << metrics.theoreticalOccupancy << "\n";
        jsonFile << "}\n";
        jsonFile.close();
        std::cout << "[Info] Exported metrics to output/metrics.json for Python AI analyzer.\n";
    }

    return 0;
}
