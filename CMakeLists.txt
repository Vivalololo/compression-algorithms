cmake_minimum_required(VERSION 3.10.0)

project(Compress VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compress
    main.cpp
    src/Huffman.h
    src/Huffman.cpp
    src/Shannon-Fano.h
    src/Shannon-Fano.cpp
)

