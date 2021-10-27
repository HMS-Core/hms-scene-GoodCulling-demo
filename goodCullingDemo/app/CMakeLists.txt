# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/main/cpp/include)
link_directories(src/main/jniLibs/arm64-v8a)

add_library(native-lib # Sets the name of the library.
        SHARED    # Sets the library as a shared library.
        src/main/cpp/goodculling-demo.cpp
        )

find_library( # Sets the name of the path variable.
        log-lib
        log
        )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries( # Specifies the target library.
        native-lib
        android
        ${log-lib}
        # Links the target library to the log library
        libc++_shared.so
        libCoreCulling.so
        )

