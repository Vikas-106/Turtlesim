cmake_minimum_required(VERSION 3.0.2)
project(beginner_projects)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)
catkin_package(
)

include_directories(

  ${catkin_INCLUDE_DIRS}
)
add_executable(movetox src/move_to_X.cpp)
target_link_libraries(movetox ${catkin_LIBRARIES})