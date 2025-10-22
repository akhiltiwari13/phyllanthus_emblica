#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>

namespace fs = ::boost::filesystem;

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
    void use() { std::cout << "Resource in use\n"; }
};

int main() {

    ::boost::shared_ptr<Resource> ptr = ::boost::make_shared<Resource>();
    ptr->use();
    
    // Create another reference
    ::boost::shared_ptr<Resource> ptr2 = ptr;
    
    std::cout << "Reference count: " << ptr.use_count() << std::endl;
    try {
        ::boost::asio::io_context io_context;
        
        // Resolve the hostname
        ::boost::asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("www.example.com", "http");
        
        // Create and connect the socket
        ::boost::asio::ip::tcp::socket socket(io_context);
        ::boost::asio::connect(socket, endpoints);
        
        // Send an HTTP request
        std::string request =
            "GET / HTTP/1.1\r\n"
            "Host: www.example.com\r\n"
            "Connection: close\r\n\r\n";
        ::boost::asio::write(socket, ::boost::asio::buffer(request));
        
        // Read the response
        ::boost::asio::streambuf response;
        ::boost::system::error_code ec;
        while (::boost::asio::read(socket, response, 
                                ::boost::asio::transfer_at_least(1), ec)) {
            if (ec != ::boost::asio::error::eof) throw ::boost::system::system_error(ec);
        }
        
        // Output the response
        std::cout << std::istream(&response).rdbuf() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    fs::path p = fs::current_path();
    
    std::cout << "Current path: " << p << std::endl;
    
    // Iterate over directory contents
    for (fs::directory_iterator it(p); it != fs::directory_iterator(); ++it) {
        std::cout << (fs::is_directory(it->status()) ? "Dir:  " : "File: ")
                  << it->path().filename() << std::endl;
    }
    
    // Create directories
    fs::create_directories("./boost_test/nested");
    
    // Check if a file exists
    if (fs::exists("./boost_test")) {
        std::cout << "Directory created successfully" << std::endl;
        
        // Calculate directory size
        uintmax_t size = 0;
        for (fs::recursive_directory_iterator it("./boost_test"); 
             it != fs::recursive_directory_iterator(); ++it) {
            if (fs::is_regular_file(it->status())) {
                size += fs::file_size(it->path());
            }
        }
        std::cout << "Directory size: " << size << " bytes" << std::endl;
    }

    // Resource will be automatically released when both pointers go out of scope.
    return 0;
}

