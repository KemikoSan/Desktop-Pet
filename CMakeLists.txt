include(FetchContent)

cmake_minimum_required(VERSION 4.2.0)
project(Desktop-Pets)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        main
)

FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(SDL3 SDL3_image)

add_executable(${PROJECT_NAME}
  src/rng.cpp
  src/animation.cpp
  src/file.cpp
  src/main.cpp
  src/pet.cpp
  src/time.cpp
  src/interval.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

if(WIN32)
  target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-fuse-ld=lld -Wall -Wextra>
    $<$<CONFIG:Release>:-O3 -fuse-ld=lld -Wall -Wextra -Wl,/SUBSYSTEM:WINDOWS -Wl,/ENTRY:mainCRTStartup>
  )
elseif(UNIX)
  target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra>
    $<$<CONFIG:Release>:-O3 -Wall -Wextra>
  )
endif()
