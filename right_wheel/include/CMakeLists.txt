add_subdirectory(right_wheel)

MAP_ADD_STR(hdrs "${PROJECT_NAME}/" headers)
set(headers ${headers} PARENT_SCOPE)
