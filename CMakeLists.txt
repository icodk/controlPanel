cmake_minimum_required(VERSION 3.5)

if (NOT DEFINED PROJECT_NAME)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    project(controlPanel)
else()
    message(FATAL_ERROR "LV PORT ESP32: This must be a project's main CMakeLists.txt.")
endif()

execute_process(COMMAND cmd /C git describe --abbrev=7 --dirty --always --tags > gitversion2.c )
