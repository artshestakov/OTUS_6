cmake_minimum_required(VERSION 3.12)

project(homework_6)

set (CMAKE_CXX_STANDARD 17)

add_executable(homework_6
    src/main.cpp
	src/matrix.h
)

target_include_directories(homework_6
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS homework_6 RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME "homework_6")
set(CPACK_PACKAGE_CONTACT art.shestakov@icloud.com)
include(CPack)
