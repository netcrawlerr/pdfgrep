cmake_minimum_required(VERSION 3.20)

project(pdfgrep
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

pkg_check_modules(
    POPPLER_CPP
    REQUIRED
    IMPORTED_TARGET
    poppler-cpp
)

add_executable(pdfgrep
    src/main.cpp
    src/cli.cpp
    src/pdf.cpp
    src/scanner.cpp
    src/search.cpp
)

target_include_directories(pdfgrep
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(pdfgrep
    PRIVATE
        PkgConfig::POPPLER_CPP
)

target_compile_options(pdfgrep
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# ---------------------------------------------------------------------------
# Installation
# ---------------------------------------------------------------------------

include(GNUInstallDirs)

install(
    TARGETS pdfgrep
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
