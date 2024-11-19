# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML package
find_package(SFML 2.6 COMPONENTS graphics window system network REQUIRED)
link_libraries(sfml-graphics sfml-window sfml-system sfml-network pthread)

# Create the visualizer library
add_library(visualizer STATIC visualizer.cpp visualizer2.cpp)
target_link_libraries(visualizer PRIVATE resources)


# add_library(visualizer2 OBJECT visualizer2.cpp)
# target_link_libraries(visualizer2 PRIVATE resources)

add_library(algorithm OBJECT algorithm.cpp)

# Main executable for visualizer
add_executable(main_visualizer main_visualizer.cpp)
target_link_libraries(main_visualizer PRIVATE visualizer resources algorithm)


# Main executable for visualizer 2
add_executable(main_visualizer2 main_visualizer2.cpp)
target_link_libraries(main_visualizer2 PRIVATE visualizer resources algorithm)



add_executable(test_algos test_algos.cpp)
target_link_libraries(test_algos PRIVATE algorithm)
