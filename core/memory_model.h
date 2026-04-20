#pragma once
#include <vector>
#include <iostream>

namespace GpuSim {

// Assuming 128-byte cache lines, and a float is 4 bytes.
// So 32 floats per cache line. 
// If all 32 threads in a warp access contiguous addresses, they fit in 1 cache line.

struct MemoryAccess {
    int threadId;
    int address;
    bool isWrite;
};

class MemoryModel {
public:
    int sizeBytes;
    int coalescedAccesses;
    int uncoalescedAccesses;

    MemoryModel(int size) : sizeBytes(size), coalescedAccesses(0), uncoalescedAccesses(0) {}

    void simulateWarpAccess(const std::vector<MemoryAccess>& accesses) {
        if (accesses.empty()) return;

        // Count unique cache lines accessed
        std::vector<int> cacheLines;
        for (const auto& acc : accesses) {
            int line = acc.address / 128;
            bool found = false;
            for (int cl : cacheLines) {
                if (cl == line) {
                    found = true;
                    break;
                }
            }
            if (!found) cacheLines.push_back(line);
        }

        // Ideal scenario: 32 threads accessing contiguous 4-byte floats fit in one 128-byte cache line.
        // Or if addresses are same.
        if (cacheLines.size() <= 2) { 
            // 1 or 2 lines is coalesced (e.g. crossing boundary)
            coalescedAccesses++;
        } else {
            uncoalescedAccesses++;
        }
    }

    // Dummy mapping array base addr to ints
    int getBaseAddress(const std::string& arrayName) {
        if (arrayName == "A") return 0;
        if (arrayName == "B") return 4096;
        if (arrayName == "C") return 8192;
        return 16384;
    }
};

} // namespace GpuSim
