set(SOURCE_LIB 
    binary.cpp
    list.cpp
)	

add_library(saber SHARED ${SOURCE_LIB})

target_include_directories(saber PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})