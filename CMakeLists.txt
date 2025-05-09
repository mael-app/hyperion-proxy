cmake_minimum_required(VERSION 3.20)
project(HyperionProxy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/yaml-cpp)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

function(get_sources_recursive return_var dir)
    file(GLOB_RECURSE tmp_list CONFIGURE_DEPENDS
        "${dir}/*.cpp"
        "${dir}/*.cxx"
        "${dir}/*.cc"
    )
    set(${return_var} ${tmp_list} PARENT_SCOPE)
endfunction()

# ───── Common interface target ─────
add_library(common INTERFACE)
target_include_directories(common INTERFACE common/include)

# ───── Client ─────
get_sources_recursive(CLIENT_SOURCES client/src)
add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client PRIVATE common yaml-cpp)
target_include_directories(client PRIVATE client/src)
target_include_directories(client PRIVATE client/include)

# ───── Server ─────
get_sources_recursive(SERVER_SOURCES server/src)
add_executable(server ${SERVER_SOURCES})
target_link_libraries(server PRIVATE common yaml-cpp)
target_include_directories(server PRIVATE server/src)
target_include_directories(server PRIVATE server/include)