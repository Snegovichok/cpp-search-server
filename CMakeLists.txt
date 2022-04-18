cmake_minimum_required(VERSION 3.17)
project(cpp-search-server)

set(CMAKE_CXX_STANDARD 17)
set(-DCMAKE_CXX_COMPILER=g++-10)

add_executable(cpp-search-server main.cpp document.cpp document.h paginator.h read_input_functions.cpp read_input_functions.h request_queue.cpp request_queue.h search_server.cpp search_server.h string_processing.cpp string_processing.h log_duration.h test_example_functions.cpp test_example_functions.h process_queries.cpp process_queries.h concurrent_map.h)