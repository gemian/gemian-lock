/*
 * Copyright © 2019 Adam Boardman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "silver_button_event_sink.h"
#include "dbus_message_handle.h"

char const* const silver_button_name = "org.thinkglobally.Gemian.SilverButton";
char const* const silver_button_path = "/org/thinkglobally/Gemian/SilverButton";
char const* const silver_button_iface = "org.thinkglobally.Gemian.SilverButton";
static const char *const on_press = "OnPress";
static const char *const on_release = "OnRelease";

SilverButtonEventSink::SilverButtonEventSink(std::string const &dbus_address)
        : dbus_connection{dbus_address} {
    dbus_connection.request_name(silver_button_name);
}

void SilverButtonEventSink::notify_on_press() {
    usc::DBusMessageHandle signal{
            dbus_message_new_signal(
                    silver_button_path,
                    silver_button_iface,
                    on_press)};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void SilverButtonEventSink::notify_on_release() {
    usc::DBusMessageHandle signal{
            dbus_message_new_signal(
                    silver_button_path,
                    silver_button_iface,
                    on_release)};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}
