# CMakeLists file
cmake_minimum_required(VERSION 2.6)

project (bombbaby_server)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "-g -O2")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--hash-style=sysv")

include_directories ("${PROJECT_SOURCE_DIR}/logapi/include" "/usr/local/gd2/inclue" "/usr/local/services/include/mysql++" "/usr/include" "/usr/local/services/mysql/include" "/usr/local/services/include" "${PROJECT_SOURCE_DIR}/event" )
link_directories ("${PROJECT_SOURCE_DIR}/logapi/lib" "/usr/local/gd2/lib" "/usr/local/services/lib" "/usr/local/services/lib" "/usr/local/services/mysql/lib")

add_subdirectory (common)
add_subdirectory (event)
add_subdirectory (logic)
add_subdirectory (net)
add_subdirectory (worldd)
add_subdirectory (gamed)
add_subdirectory (star)
add_subdirectory (transfer)

add_executable (gamed gamed/Daemon.cpp)
add_executable (worldd worldd/worldd.cpp)
add_executable (stard star/stard.cpp)
add_executable (transferd transfer/transfer.cpp)
target_link_libraries (gamed game event logic common net protobuf log4cxx config++ tokyotyrant msglog gd)
target_link_libraries (worldd world event logic common net protobuf log4cxx config++)
target_link_libraries (stard star event logic common net protobuf log4cxx config++ tokyotyrant msglog gd)
target_link_libraries (transferd transfer event logic common net protobuf log4cxx config++ tokyotyrant mysqlpp msglog gd)
