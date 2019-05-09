CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR}/header)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src rshell_src)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/unit_tests rshell_test)

ADD_EXECUTABLE(rshell
    	${rshell_src}
)

ADD_EXECUTABLE(test
    	${rshell_test}
        ${CMAKE_CURRENT_LIST_DIR}/src/command.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/connector.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/exeargu.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/rshellbase.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
