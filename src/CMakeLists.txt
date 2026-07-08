# =============================================================================
# ${PROJECT_NAME} — Standalone Hello-World Binary
# =============================================================================
# Intentionally independent of MyLib so BUILD_APP and BUILD_LIB can be toggled
# separately in multi-config workflows (e.g. CI matrix, feature toggles).
# =============================================================================

# ---- Executable -------------------------------------------------------------
add_executable(${PROJECT_NAME})

# ---- Sources ----------------------------------------------------------------
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# ---- Include Paths ----------------------------------------------------------
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# ---- Properties -------------------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF           # Matches root setting (good practice)
    # OUTPUT_NAME ${PROJECT_NAME}          # Optional: lower-case output name
    # VERSION ${PROJECT_VERSION} # Optional: version info
)

# ---- Compile Features -------------------------------------------------------
# Even though root sets it globally, this makes it explicit
target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_23
)

# ---- Compile Options --------------------------------------------------------
# target_compile_options(${PROJECT_NAME}
#     PRIVATE
#         $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
#         $<$<CXX_COMPILER_ID:GCC>:-Wno-sign-compare>
# )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXCEPTIONS ON  # This handles the flags correctly for each compiler
)

# ---- Dependencies -----------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        fmt::fmt
        CLI11::CLI11
        ftxui::component
        nextsilicon-cpp-subprocess::nextsilicon-cpp-subprocess
        tomlplusplus::tomlplusplus)

# ---- Cross-Cutting Configuration --------------------------------------------
# Applies PCH, unity build, profiler links (Tracy/Perfetto), clang-tidy,
# Windows ASan DLL deployment — all via configure_target().
# See cmake/configure_target.cmake for implementation details.
configure_target(${PROJECT_NAME})

if (ENABLE_SANITIZERS)
  target_enable_sanitizers(${PROJECT_NAME})
endif()

message(STATUS "${PROJECT_NAME} configured (standalone executable)")
