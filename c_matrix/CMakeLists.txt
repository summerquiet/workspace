cmake_minimum_required(VERSION 2.8.12)

project(c_matrix)

#指定编译器
set(CMAKE_CXX_FLAGS "-std=c++14 -fPIC -fpermissive -pthread")

#指定编译版本
SET(CMAKE_BUILD_TYPE DEBUG)
#SET(CMAKE_BUILD_TYPE RELEASE)

#定义宏
add_definitions(-DNDEBUG)
add_definitions(-DKOTEI_LINUX)
add_definitions(-DLINUX)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

#设置头文件目录
#set(SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#指定包含头文件
file(GLOB PROJECT_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/matrix"
    "/usr/local/include/eigen3"
    )

include_directories(${PROJECT_HEADERS})

#指定源文件
file(GLOB PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/inl_matrix_common.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/inl_matrix_eigen.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/test_matrix.c"
    )

#指定链接库目录
file(GLOB PROJECT_LIBRARIES
    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    )

link_directories(${PROJECT_LIBRARIES})

#设置执行程序目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#生成可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_LIBRARIES})
	
#附加依赖项
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
    stdc++
    pthread
    )
