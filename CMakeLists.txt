cmake_minimum_required(VERSION 2.8)

project(stanal)

set(CMAKE_BUILD_TYPE debug)

set(S_JSON_SRC_LIST
    "jparsers.cpp"
    "jvalue.cpp"
    "jnull.cpp"
    "jboolean.cpp"
    "jnumber.cpp"
    "jstring.cpp"
    "jobject.cpp"
    "jarray.cpp"
)

add_executable(${PROJECT_NAME} ${S_JSON_SRC_LIST} "main.cpp")
