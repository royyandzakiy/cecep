from conan import ConanFile
from conan.tools.cmake import cmake_layout

class MyProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("fmt/12.1.0")
        self.requires("gtest/1.17.0")
        self.requires("ftxui/6.1.9")
        self.requires("tomlplusplus/3.4.0")
        self.requires("cli11/2.6.2")
        self.requires("nextsilicon-cpp-subprocess/2.0.2")

    def layout(self):
        cmake_layout(self)
