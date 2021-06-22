file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/utils.cpp src/utils.h src/InfixToPostfix.cpp src/InfixToPostfix.h src/Follow.cpp src/Follow.h src/Parent.cpp src/Parent.h src/Query.cpp src/Query.h src/Use.cpp src/Use.h src/Modifies.cpp src/Modifies.h src/Pattern.cpp src/Pattern.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


