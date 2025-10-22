#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>


int main() {
    // Default logger (stdout, colored)
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    
    // Warning with multiple arguments
    spdlog::warn("Easy padding in numbers: {:08d}", 12);
    
    // Critical with format string syntax
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    
    // Debug with named arguments
    spdlog::debug("The answer is {answer}", spdlog::arg("answer", 42));
    
    // Conditional logging
    for(int i = 0; i < 10; i++) {
        // Log only if i > 5
        SPDLOG_INFO_IF(i > 5, "i = {}", i);
    }
    
    // Basic file logger
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/basic.txt");
    file_logger->info("Basic file log message");
    
    // Rotating file logger with 5MB size max and 3 rotated files
    auto rotating_logger = spdlog::rotating_logger_mt("rotating_logger", "logs/rotating.txt", 
                                                    5 * 1024 * 1024, 3);
    rotating_logger->info("Rotating file log message");
    
    // Daily logger - creates new file at midnight
    auto daily_logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
    daily_logger->info("Daily file log message");
    
    // Initialize asynchronous logger with a queue size of 8192 and 1 backing thread
    spdlog::init_thread_pool(8192, 1);
    
    // Create the asynchronous logger
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "logs/async.txt");
    
    // Set as default logger
    spdlog::set_default_logger(async_file);
    
    // Log without blocking the main thread
    for(int i = 0; i < 10000; i++) {
        spdlog::info("Async message #{}", i);
    }
    
    // Ensure all messages are flushed before exit
    spdlog::shutdown();
    
    return 0;
}
