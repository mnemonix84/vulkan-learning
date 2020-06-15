
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/externals/VulkanMemoryAllocator/src)

if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "Vulkan SDK required but not found.")
endif()

include(files.cmake)

add_executable(${CMAKE_PROJECT_NAME}
    ${SRC_FILES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE
        VMA_STATIC_VULKAN_FUNCTIONS=0
        VMA_DYNAMIC_VULKAN_FUNCTIONS=0
        VULKAN_NO_PROTOTYPES)

if(MSVC)
    target_link_libraries(${CMAKE_PROJECT_NAME} $ENV{VULKAN_SDK}/Lib/shaderc_shared.lib)
    target_compile_definitions(${CMAKE_PROJECT_NAME}
        PRIVATE
            _CRT_SECURE_NO_WARNINGS)
endif()
