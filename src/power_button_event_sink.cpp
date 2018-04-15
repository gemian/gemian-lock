/*
 * Copyright © 2016 Canonical Ltd.
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

#include "power_button_event_sink.h"
#include "dbus_message_handle.h"

namespace
{
    char const* const power_button_name = "org.thinkglobally.Gemian.PowerButton";
    char const* const power_button_path = "/org/thinkglobally/Gemian/PowerButton";
    char const* const power_button_iface = "org.thinkglobally.Gemian.PowerButton";
}

usc::PowerButtonEventSink::PowerButtonEventSink(
        std::string const& dbus_address)
        : dbus_connection{dbus_address}
{
    dbus_connection.request_name(power_button_name);
}

void usc::PowerButtonEventSink::notify_press()
{
    DBusMessageHandle signal{
            dbus_message_new_signal(
                    power_button_path,
                    power_button_iface,
                    "Press")};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void usc::PowerButtonEventSink::notify_release()
{
    DBusMessageHandle signal{
            dbus_message_new_signal(
                    power_button_path,
                    power_button_iface,
                    "Release")};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}