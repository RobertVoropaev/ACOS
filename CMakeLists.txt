cmake_minimum_required(VERSION 3.9)
project(Acos C)

set(CMAKE_C_STANDARD 99)

add_executable(Acos ls.c nc.c pipe.c sed.c sieve_aratosthenes.c tail.c thread_wc.c wc.c)