configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${XCB_INCLUDE_DIRS}
        ${LIBXCB_INCLUDE_DIRS}
        ${DBUS_INCLUDE_DIRS}
)

link_directories (${PC_LIBELEMENTARY_LIBRARY_DIRS})

add_executable(${PROJECT_NAME_LOWER}
        gemian-lock.cpp
        randr.cpp
        unlock_indicator.cpp
        xcb.cpp
        power_button_event_sink.cpp
        power_button_event_sink.h
        dbus_message_handle.cpp dbus_connection_handle.cpp)

target_link_libraries(${PROJECT_NAME_LOWER}
        ${LIBEV_LIBRARIES}
        ${XCB_LIBRARIES}
        ${PAM_LIBRARIES}
        ${DBUS_LIBRARIES}
        xkbcommon
        xkbcommon-x11
        cairo
        )

install(TARGETS ${PROJECT_NAME_LOWER} RUNTIME DESTINATION bin)
