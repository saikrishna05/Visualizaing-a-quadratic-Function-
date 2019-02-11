
cmake_minimum_required(VERSION 3.8.0-rc1)

PROJECT(Project2)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(project2 MACOSX_BUNDLE project2)

if(VTK_LIBRARIES)
  target_link_libraries(project2 ${VTK_LIBRARIES})
else()
  target_link_libraries(project2 vtkHybrid vtkWidgets)
endif()
