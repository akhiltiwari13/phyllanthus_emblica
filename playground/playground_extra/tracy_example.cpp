// #include <thread>
// #include <vector>
// #include <cmath>
// #include <memory>
// #include "tracy/Tracy.hpp"
//
// void worker_function(int iterations) {
//     ZoneScopedN("Worker Function");
//
//     volatile double result = 0;
//     for(int i = 0; i < iterations; i++) {
//         ZoneScopedN("Calculation");
//         result += std::sin(i * 0.1) * std::cos(i * 0.1);
//
//         // Updated plot syntax
//         TracyPlot("Intermediate Result", result);
//
//         std::this_thread::sleep_for(std::chrono::microseconds(100));
//     }
// }
//
// void memory_intensive_operation() {
//     ZoneScoped;
//
//     // Allocate with proper Tracy tracking
//     const size_t size = 1024 * 1024;
//     auto ptr = std::make_unique<int[]>(size);
//     TracyAllocS(ptr.get(), size * sizeof(int), 10);  // Now 3 arguments
//
//     // Initialize memory
//     for(size_t i = 0; i < size; i++) {
//         ptr[i] = rand() % 100;
//     }
//
//     TracyFreeS(ptr.get(), 10);  // Match allocation tracking
//     ptr.reset();
// }
//
// int main() {
//     // tracy::SetThreadName("Main Thread");
//             ZoneScopedN("Main");
//
//     while(true) {
//         FrameMarkStart("Main Loop");
//
//         {
//             ZoneScopedN("Main Loop");
//
//             worker_function(100);
//             memory_intensive_operation();
//
//             TracyMessageL("Completed frame work");
//
//             std::this_thread::sleep_for(std::chrono::milliseconds(16));
//         }
//
//         FrameMarkEnd("Main Loop");
//
//         // Updated plot configuration (if needed)
//         // Tracy v0.10+ uses automatic format detection
//         // Remove TracyPlotConfig if not needed
//     }
//
//     return 0;
// }
#include "tracy/Tracy.hpp"
#include <thread>

int main() {
    // tracy::SetThreadName("Main Thread");
    while(true) {
        FrameMark;
        {
            ZoneScopedN("Work");
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }
}
