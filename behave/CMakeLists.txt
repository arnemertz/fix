add_test(NAME behave_stable_tests COMMAND behave -t ~skip -t ~wip -k
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_test(NAME behave_wip_tests COMMAND behave -t wip -k --no-capture --no-logcapture
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
