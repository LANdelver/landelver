find_package(Python3 REQUIRED COMPONENTS Development)
find_package(Lua REQUIRED)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.c)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES} ${LUA_LIBRARIES})

