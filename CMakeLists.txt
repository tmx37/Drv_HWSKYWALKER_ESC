# Library main CMakeLists, add here dependencies for compilation

add_library(Stm32_HwSkyWalker_Module STATIC
    src/Stm32_HwSkyWalker_Module.c
)

target_include_directories(Stm32_HwSkyWalker_Module
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)