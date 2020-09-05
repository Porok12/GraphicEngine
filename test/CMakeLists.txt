set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(UnitTests test.cpp)

target_link_libraries(UnitTests
        ${Boost_LIBRARIES}
        GraphicEngine)