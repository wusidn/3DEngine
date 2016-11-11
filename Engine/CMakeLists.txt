CMAKE_MINIMUM_REQUIRED (VERSION 3.4)

PROJECT (Engine VERSION 0.0.0)

#读取Src目录
AUX_SOURCE_DIRECTORY(Src DIR_SRCS)
AUX_SOURCE_DIRECTORY(Src/Tools DIR_SRCS)

#指定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/Include)
include_directories(${PROJECT_SOURCE_DIR}/Include/Tools)
include_directories(${PROJECT_SOURCE_DIR}/Library/Include)

find_package(OpenGL REQUIRED)  
include_directories(${OPENGL_INCLUDE_DIR})  
  
find_package(GLUT REQUIRED)  
include_directories(${GLUT_INCLUDE_DIR}) 

find_package(GLEW REQUIRED)  
include_directories(${GLEW_INCLUDE_DIR}) 

#生成库
ADD_LIBRARY(${PROJECT_NAME} ${DIR_SRCS})

#输出路径
SET(LIBRARY_OUTPUT_PATH ${ROOT}/build/bin)

#链接库
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} GL GLEW glut uuid pthread)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLUT_LIBRARY} GLEW ${OPENGL_LIBRARY} ${UUID_LIBRARY} pthread)

#拷贝资源
FILE(COPY ${PROJECT_SOURCE_DIR}/Shader DESTINATION ${ROOT}/build/bin)
# FILE(COPY ${PROJECT_SOURCE_DIR}/Source DESTINATION ${ROOT}/build/bin)

#设置编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")
