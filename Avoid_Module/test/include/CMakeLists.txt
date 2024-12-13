add_subdirectory(Avoid_ModuleTest)

MAP_ADD_STR(hdrs "${PROJECT_NAME}Test/" headers)
set(headers ${headers} PARENT_SCOPE)
