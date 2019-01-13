configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(default.png ${CMAKE_BINARY_DIR}/images/${f} COPYONLY)

add_definitions(-DPACKAGE_DATA_DIR="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}")

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
        dbus_message_handle.cpp
        dbus_connection_handle.cpp
        clock.cpp
        power_button_event_sink.cpp
        user_activity_event_sink.cpp
        lock_active_event_sink.cpp
        silver_button_event_sink.cpp)

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

# Install data files
install(FILES
        org.thinkglobally.Gemian.conf
        DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/dbus-1/system.d
        )
install(FILES
        org.thinkglobally.Gemian.PowerButton.xml
        org.thinkglobally.Gemian.UserActivity.xml
        org.thinkglobally.Gemian.Lock.xml
        org.thinkglobally.Gemian.SilverButton.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/dbus-1/interfaces
        )
install(FILES default.png DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}/images)
