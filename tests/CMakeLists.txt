include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


file(GLOB_RECURSE CXX_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
add_executable(unit_tests ${CXX_FILES}
    test_data/Widget.h test_data/Widget.cpp
    test_data/Numbers.h test_data/Numbers.cpp)

target_link_libraries(unit_tests
    INTERFACE
    qjsh)

target_link_libraries(unit_tests
    PRIVATE
    gtest_main
    Qt${QT_VERSION_MAJOR}::Core
)
target_include_directories(unit_tests PRIVATE ${gtest_SOURCE_DIR}/include)
target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(unit_tests)
