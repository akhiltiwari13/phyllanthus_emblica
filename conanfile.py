from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.scm import Version

from conan import ConanFile


class PhyllanthusEmblicaRecepie(ConanFile):
    name = "phyllanthus-emblica"
    version = "0.1"
    author = "akhiltiwari13"

    # Package metadata
    description = "HFT Engineer/ Quant Real-World Interview problems collections"
    topics = ("boost", "conan", "cmake", "cpp20", "cpp23")
    license = "MIT"

    # Binary configuration
    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        self.requires("boost/[~1.88]")
        self.requires("yaml-cpp/[>=0.8.0]")
        self.requires("fmt/[~12.0]", override=True, force=True)
        self.requires("nlohmann_json/[>=3.12.0]")  # used by infra::events
        self.requires("benchmark/[>=1.8.5]")
        self.requires("gtest/[>=1.16.0 <2.0]")
        self.requires("tracy/[~0.13]")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.30 <4.4]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        # Generate CMake dependencies
        deps = CMakeDeps(self)
        deps.generate()

        # Configure CMake toolchain with modern practices
        tc = CMakeToolchain(self)

        # C++23 standard
        tc.variables["CMAKE_CXX_STANDARD"] = "23"
        tc.variables["CMAKE_CXX_STANDARD_REQUIRED"] = "ON"
        tc.variables["CMAKE_CXX_EXTENSIONS"] = "OFF"

        tc.generate()
