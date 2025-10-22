from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.scm import Version


class PhyllanthusEmblicaRecepie(ConanFile):
    name = "phyllanthus-emblica"
    version = "0.1"
    user = "akhiltiwari13"

    # Package metadata
    description = "HFT Engineer/ Quant Real-World Interview problems collections"
    topics = ("boost", "conan", "cmake", "cpp20")
    license = "MIT"

    # Binary configuration
    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        self.requires("boost/[~1.88]")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.30 <4.0]")

    def configure(self):
        check_min_cppstd(self, 23)

    def validate(self):
        # Validate compiler support for C++20
        if (
            self.settings.compiler == "gcc"
            and Version(self.settings.compiler.version) < "10"
        ):
            raise ConanInvalidConfiguration(
                "GCC 10 or higher is required for C++23 support"
            )
        if (
            self.settings.compiler == "clang"
            and Version(self.settings.compiler.version) < "12"
        ):
            raise ConanInvalidConfiguration(
                "Clang 12 or higher is required for C++23 support"
            )

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

    def package_info(self):
        # Set package information for consumers
        self.cpp_info.libs = ["boost-applications"]
        self.cpp_info.cppstd = "23"
