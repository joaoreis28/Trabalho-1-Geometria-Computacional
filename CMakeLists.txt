cmake_minimum_required(VERSION 3.1)
cmake_policy(VERSION 3.1)

# Set the project name and version.
project(CGL VERSION 1.0)

# Find required packages.
find_package(CGAL REQUIRED COMPONENTS Qt5)

# Build type for performance.
set(CMAKE_BUILD_TYPE Release)

# Set library directories.
set(CGL_SOURCE ${PROJECT_SOURCE_DIR}/src)
set(CGL_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(CGL_DRAW_SOURCE ${CGL_SOURCE}/Draw)
set(CGL_DRAW_INCLUDE ${CGL_INCLUDE}/Draw)

# Set examples directory.
set(CGL_EXAMPLES ${PROJECT_SOURCE_DIR}/trab1)



add_executable(trab ${CGL_EXAMPLES}/polygon_2_triangulate_good.cpp ${CGL_SOURCE}/IO.cpp ${CGL_SOURCE}/Partition.cpp ${CGL_SOURCE}/Primitives.cpp ${CGL_DRAW_SOURCE}/DrawSegments3.cpp ${CGL_SOURCE}/Wurfel.cpp)
target_include_directories(trab PRIVATE ${CGL_INCLUDE} ${CGL_DRAW_INCLUDE})
target_link_libraries(trab PUBLIC CGAL::CGAL_Basic_viewer)




