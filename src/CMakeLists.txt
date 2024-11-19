project("qjsh" VERSION 0.0.1
             DESCRIPTION "A header-only c++ library that helps parse and serialize QJson"
             HOMEPAGE_URL "https://github.com/SirotinDE/qjsh")

add_library(qjsh INTERFACE)
target_include_directories(qjsh INTERFACE ./qjsh.h)

