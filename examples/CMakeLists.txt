macro(_tampl_add_example name)
    add_executable(tampl_example_${name} ${name}.cpp)
    target_link_libraries(tampl_example_${name} PRIVATE tampl)
endmacro()

_tampl_add_example(test_task_planning)