// Add to your project's common header:
#include "tracy/Tracy.hpp"

// Add zones to your functions:
void SomeFunction() {
    ZoneScoped;  // Automatically profiles this scope
    
    // Your function code here
    
    {
        ZoneNamedN(innerZone, "Inner Operation", true);  // Named zone with color
        // Code to profile separately
    }
}

### Memory Profiling

// Track memory allocations
void* operator new(std::size_t count) {
    auto ptr = malloc(count);
    TracyAlloc(ptr, count);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    TracyFree(ptr);
    free(ptr);
}

// In your main source file:
void main() {
    // Initialize Tracy
    TracyAppInfo("My Application", sizeof("My Application"));
    
    // Your code here
}
