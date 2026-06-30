from conan import ConanFile

class MyProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("fmt/12.1.0")
        self.requires("gtest/1.17.0")
        self.requires("ftxui/6.1.9")
        self.requires("tomlplusplus/3.4.0")
