cmake_minimum_required(VERSION 3.0.2)
project(beginner_projects)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf2
  tf2_ros
  turtlesim
)
catkin_package(
)

include_directories(

  ${catkin_INCLUDE_DIRS}
)
install(FILES
    start_demo.launch
    #myfile2
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
 )
add_executable(movetox src/move_to_X.cpp)
target_link_libraries(movetox ${catkin_LIBRARIES})
add_executable(gotoxy src/move_to_XY.cpp)
target_link_libraries(gotoxy ${catkin_LIBRARIES})
add_executable(square src/move_square.cpp)
target_link_libraries(square ${catkin_LIBRARIES})
add_executable(circle src/move_circle.cpp)
target_link_libraries(circle ${catkin_LIBRARIES})
add_executable(turtle_tf2_broadcaster src/turtle_tf2_broadcaster.cpp)
target_link_libraries(turtle_tf2_broadcaster ${catkin_LIBRARIES})
add_executable(turtle_tf2_listener src/turtle_tf2_listener.cpp)
target_link_libraries(turtle_tf2_listener ${catkin_LIBRARIES})