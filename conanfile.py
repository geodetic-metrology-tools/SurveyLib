from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class SurveyLibConan(ConanFile):
    name = "surveylib"
    version = "4.3.1"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    exports_sources = "source/*", "SurveryLibVersion.in", "lib/*", "licenses/*"

    requires = (
        "eigen/3.4.0",
    )

    # default_options = {
    #     "eigen/*:build_tests": False,
    # }

    def layout(self):
        self.folders.source = "source"
        self.folders.build = "build"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["surveylib"]
