cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

project(vulkan-learning)

option(${CMAKE_PROJECT_NAME}_Superbuild "Build ${CMAKE_PROJECT_NAME}_Superbuild and all of its dependencies." ON)

if(${CMAKE_PROJECT_NAME}_Superbuild)
    include(Superbuild.cmake)
    return()
endif()

add_subdirectory(src)