set(SOURCE_EXE 
    main.cpp
)	

add_executable(app ${SOURCE_EXE})

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(app PRIVATE saber)