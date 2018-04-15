//
// Created by adam on 15/04/18.
//

#include "lock_active_event_sink.h"
#include "dbus_message_handle.h"

char const* const gemian_lock_active_name = "org.thinkglobally.Gemian.Lock";
char const* const gemian_lock_active_path = "/org/thinkglobally/Gemian/Lock";
char const* const gemian_lock_active_iface = "org.thinkglobally.Gemian.Lock";

LockActiveEventSink::LockActiveEventSink(std::string const &dbus_address)
        : dbus_connection{dbus_address} {
    dbus_connection.request_name(gemian_lock_active_name);
}

void LockActiveEventSink::notify_lock_active() {
    usc::DBusMessageHandle signal{
            dbus_message_new_signal(
                    gemian_lock_active_path,
                    gemian_lock_active_iface,
                    "Active")};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void LockActiveEventSink::notify_lock_inactive() {
    usc::DBusMessageHandle signal{
            dbus_message_new_signal(
                    gemian_lock_active_path,
                    gemian_lock_active_iface,
                    "Inactive")};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}
