from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout


class bu(ConanFile):
    name = "bu"
    version = "0.1"

    description = "bu-test source"
    topics = "interview"
    author = "akhil"
    # license = "Proprietary"

    # Binary configuration
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "fPIC": [True, False]}
    # default_options = {"shared": False, "fPIC": True}
    default_options = {"shared": False, "fPIC": False}

    def requirements(self):
        # Core dependencies with version ranges for better compatibility
        self.requires("cereal/[~1.3.2]")  # Serialization
        self.requires("cryptopp/[>=8.9.0 <9.0]")  # Cryptography
        self.requires("eastl/[>=3.17.03 <3.21.13]")  # Cryptography
        self.requires("fmt/[~12.0]", override=True, force=True)
        self.requires(
            "abseil/20250814.0", override=True, force=True
        )  # was causing some issue with cpp abi being of older version
        self.requires("folly/2024.08.12.00")  # used by events
        self.requires("nlohmann_json/[>=3.12.0]")  # used by infra::events
        self.requires("rapidjson/[~1.1]")  # used by core
        self.requires("boost/[~1.88.0]", override=True, force=True)
        self.requires("zlib/[>=1.3.0 <1.5]")
        self.requires("re2/[>=20251105]")
        self.requires("libpcap/[~1.10.5]")
        self.requires("benchmark/[>=1.8.5]")
        self.requires("gtest/[>=1.16.0 <2.0]")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.30 <4.0]")

    def config_options(self):
        if self.settings.os == "Linux":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)
        #
        # check if this is needed?

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_CXX_STANDARD"] = "23"
        tc.variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        # Add more customization here
        tc.generate()
