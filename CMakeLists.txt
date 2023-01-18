cmake_minimum_required(VERSION 3.23)
project(speech)

set(CMAKE_CXX_STANDARD 14)

add_executable(speech main.cpp SpeechManager.cpp SpeechManager.h Speaker.cpp Speaker.h)
