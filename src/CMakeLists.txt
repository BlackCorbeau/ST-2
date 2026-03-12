set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(circle_header ${header_path}/circle.h)
set(tasks_header ${header_path}/tasks.h)
set(circle_src circle.cpp)
set(tasks_src tasks.cpp)

add_library(${PROJECT_NAME} SHARED
  ${circle_header}
  ${circle_src}
  ${tasks_header}
  ${tasks_src})
  
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
  pthread)

add_executable(${PROJECT_NAME}.info main.cpp)
target_include_directories(${PROJECT_NAME}.info
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}.info
  ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "${lib_dest}"
    ARCHIVE DESTINATION "${lib_dest}"
    COMPONENT library)
install(TARGETS ${PROJECT_NAME}.info
        RUNTIME DESTINATION "${tool_dest}"
    COMPONENT library)
install(FILES ${circle_header} ${tasks_header} DESTINATION "${include_dest}")
