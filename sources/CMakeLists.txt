include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(system)
add_subdirectory(render)
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(application)

add_dependencies(render system)
add_dependencies(engine render)
add_dependencies(editor engine)
add_dependencies(application editor)