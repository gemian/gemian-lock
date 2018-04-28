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
    static const char *const on_press = "OnPress";
    static const char *const on_release = "OnRelease";
    static const char *const sleep_press = "SleepPress";
    static const char *const sleep_release = "SleepRelease";
    static const char *const off_press = "OffPress";
    static const char *const off_release = "OffRelease";
}

usc::PowerButtonEventSink::PowerButtonEventSink(
        std::string const& dbus_address)
        : dbus_connection{dbus_address}
{
    dbus_connection.request_name(power_button_name);
}

void usc::PowerButtonEventSink::send_signal_name(const char *name) const {
    usc::DBusMessageHandle signal{
            dbus_message_new_signal(
                    power_button_path,
                    power_button_iface,
                    name)};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void usc::PowerButtonEventSink::notify_on_press()
{
    send_signal_name(on_press);
}

void usc::PowerButtonEventSink::notify_on_release()
{
    send_signal_name(on_release);
}

void usc::PowerButtonEventSink::notify_sleep_press()
{
    send_signal_name(sleep_press);
}

void usc::PowerButtonEventSink::notify_sleep_release()
{
    send_signal_name(sleep_release);
}

void usc::PowerButtonEventSink::notify_off_press()
{
    send_signal_name(off_press);
}

void usc::PowerButtonEventSink::notify_off_release()
{
    send_signal_name(off_release);
}