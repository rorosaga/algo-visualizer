# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML package
find_package(SFML 2.6 COMPONENTS graphics window system network REQUIRED)
link_libraries(sfml-graphics sfml-window sfml-system sfml-network pthread)

# Create the visualizer library
add_library(visualizer OBJECT visualizer.cpp)
target_link_libraries(visualizer PRIVATE resources)

# Main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE visualizer resources)
