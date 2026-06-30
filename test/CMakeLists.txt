# test/CMakeLists.txt
# =============================================================================
# GTest Setup (shared by unit_tests and the sanitizer trip-wires)
# =============================================================================
find_package(GTest CONFIG REQUIRED) # need to add `gtest` in vcpkg.json


include(GoogleTest)

add_executable(app_tests test_simple.cpp)
target_include_directories(app_tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(app_tests PRIVATE GTest::gmock GTest::gmock GTest::gtest_main fmt::fmt)
gtest_discover_tests(app_tests)
