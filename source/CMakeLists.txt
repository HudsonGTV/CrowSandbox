cmake_minimum_required(VERSION 3.14)
project(crow_sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Provide Asio path manually
set(ASIO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/asio/asio/include")

# Add Crow (will use ASIO_INCLUDE_DIR)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/crow)

# Create executable from source files
add_executable(crow_sandbox 
    main.cpp
    webpage.cpp
)

# Include directories
target_include_directories(crow_sandbox PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/external/crow/include
    ${ASIO_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}  # Add this to find webpage.hpp
)

# Add required definitions
target_compile_definitions(crow_sandbox PRIVATE
    ASIO_STANDALONE
    _WIN32_WINNT=0x0601  # Windows 7 or later
    _CRT_SECURE_NO_WARNINGS
)

# Link Crow
target_link_libraries(crow_sandbox PRIVATE Crow::Crow)

# Windows networking libs
if(WIN32)
    target_link_libraries(crow_sandbox PRIVATE ws2_32 mswsock)
endif()