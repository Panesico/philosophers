cmake_minimum_required(VERSION 3.24)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

include_directories(../minishell_parser/libft)
file(GLOB SOURCES_LIBFT "../minishell_parser/libft/*.c")
add_library(../minishell_parser/libft STATIC ${SOURCES_LIBFT})
include_directories(includes)
file(GLOB SOURCES_PHILO "srcs/*.c")
add_library(PHILO STATIC ${SOURCES_PHILO})
file(GLOB SOURCES "srcs/*.c" "../minishell_parser/libft/*.c")
add_executable(philosophers ${SOURCES})
