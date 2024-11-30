# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML package
find_package(SFML 2.6 COMPONENTS graphics window system network REQUIRED)
link_libraries(sfml-graphics sfml-window sfml-system sfml-network pthread)

# Create the visualizer library
add_library(visualizer STATIC visualizer.cpp)
target_link_libraries(visualizer PRIVATE resources)


add_library(abstract OBJECT abstract_visualizer.cpp)
target_link_libraries(abstract PRIVATE resources)

add_library(algorithm OBJECT algorithm.cpp)

# Main executable for visualizer
add_executable(main_visualizer main_visualizer.cpp)
target_link_libraries(main_visualizer PRIVATE visualizer resources algorithm)

# Main executable for abstract visualizer
add_executable(main_abstract main_abstract.cpp)
target_link_libraries(main_abstract PRIVATE abstract resources algorithm)
