cmake_minimum_required(VERSION 3.20)
project(WorkerManager)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp workerManager.cpp
        worker.h
        employee.h
        employee.cpp
        manager.h
        manager.cpp
        boss.h
        boss.cpp)