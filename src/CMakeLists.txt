# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML package
find_package(SFML 2.6 COMPONENTS graphics window system network REQUIRED)
link_libraries(sfml-graphics sfml-window sfml-system sfml-network pthread)

# Create the visualizer library
add_library(visualizer STATIC visualizer.cpp)
target_link_libraries(visualizer PRIVATE resources)


add_library(generic OBJECT generic_visualizer.cpp)
target_link_libraries(generic PRIVATE resources)

add_library(algorithm OBJECT algorithm.cpp)

# Main executable for visualizer
add_executable(main_visualizer main_visualizer.cpp)
target_link_libraries(main_visualizer PRIVATE visualizer resources algorithm)

# Main executable for generic visualizer
add_executable(main_generic main_generic.cpp)
target_link_libraries(main_generic PRIVATE generic visualizer resources algorithm)
