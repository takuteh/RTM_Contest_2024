add_test(NAME ${PROJECT_NAME}_test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Test.py -o "manager.components.precreate:${PROJECT_NAME}" -o "manager.components.preconnect:${PROJECT_NAME}0.mpu_data?port=${PROJECT_NAME}Test0.mpu_data,${PROJECT_NAME}0.env?port=${PROJECT_NAME}Test0.env" -o "manager.components.preactivation:${PROJECT_NAME}0,${PROJECT_NAME}Test0" WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
string(REPLACE ";" "\\;" PYTHONPATH "$ENV{PYTHONPATH}")
if(UNIX)
  set_tests_properties(${PROJECT_NAME}_test PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_SOURCE_DIR}:${PYTHONPATH}")
else()
  set_tests_properties(${PROJECT_NAME}_test PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_SOURCE_DIR}\;${PYTHONPATH}")
endif()
