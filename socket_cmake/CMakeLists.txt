# CMakeList.txt : CMake project for CMakeProjTest, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

#project NAME
project(socket_cmake)

#指定编译器
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -fpermissive -pthread")

#指定编译版本
set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

#定义宏
#add_definitions(-DNDEBUG)
#add_definitions(-DKOTEI_LINUX)
#add_definitions(-DLINUX)
#add_definitions(-DUNICODE)
#add_definitions(-D_UNICODE)

#设置头文件目录
#set(SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#指定源文件
file(GLOB PROJECT_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Functions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Functions/*.c"
        )

#指定包含头文件
file(GLOB PROJECT_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Functions"
        )
include_directories(${PROJECT_HEADERS})

#指定链接库目录
file(GLOB PROJECT_LIBRARIES
        "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        )
link_directories(${PROJECT_LIBRARIES})

#设置执行程序目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/out)

#CMakeFile debug output
message(STATUS "----------CMAKE DEBUG MESSAGE----------")
message(STATUS "cur line:"  ${CMAKE_CURRENT_LIST_LINE})
message(STATUS "src path:"  ${PROJECT_SOURCES})
message(STATUS "hdr path:"  ${PROJECT_HEADERS})
message(STATUS "lib path:"  ${PROJECT_LIBRARIES})

#生成可执行文件
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_LIBRARIES})

#附加依赖项
target_link_libraries(${PROJECT_NAME}
        )
