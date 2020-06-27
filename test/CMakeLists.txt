set(Boost_USE_STATIC_LIBS OFF) #enable dynamic linking

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(UnitTests test.cpp)

# Note: a target should be already defined using 'add_executable' or 'add_library' 
target_link_libraries(UnitTests ${Boost_LIBRARIES})

#target_link_libraries(UnitTests test_library)