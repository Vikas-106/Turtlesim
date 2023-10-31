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
add_executable(gotoxy src/move_to_XY.cpp)
target_link_libraries(gotoxy ${catkin_LIBRARIES})
add_executable(square src/move_square.cpp)
target_link_libraries(square ${catkin_LIBRARIES})