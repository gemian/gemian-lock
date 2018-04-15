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

#include "user_activity_event_sink.h"
#include "user_activity_type.h"
#include "dbus_message_handle.h"

namespace
{
    char const* const unity_user_activity_name = "com.canonical.Unity.UserActivity";
    char const* const unity_user_activity_path = "/com/canonical/Unity/UserActivity";
    char const* const unity_user_activity_iface = "com.canonical.Unity.UserActivity";
}

usc::UserActivityEventSink::UserActivityEventSink(
        std::string const& dbus_address)
        : dbus_connection{dbus_address},
          u_clock{std::make_shared<usc::Clock>()},
          event_period{500}
{
    dbus_connection.request_name(unity_user_activity_name);
}

void usc::UserActivityEventSink::do_notify_activity_changing_power_state()
{
    auto const changing_power_state =
            static_cast<int>(UserActivityType::changing_power_state);

    DBusMessageHandle signal{
            dbus_message_new_signal(
                    unity_user_activity_path,
                    unity_user_activity_iface,
                    "Activity"),
            DBUS_TYPE_INT32, &changing_power_state,
            DBUS_TYPE_INVALID};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void usc::UserActivityEventSink::do_notify_activity_extending_power_state()
{
    auto const extending_power_state =
            static_cast<int>(UserActivityType::extending_power_state);

    DBusMessageHandle signal{
            dbus_message_new_signal(
                    unity_user_activity_path,
                    unity_user_activity_iface,
                    "Activity"),
            DBUS_TYPE_INT32, &extending_power_state,
            DBUS_TYPE_INVALID};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void usc::UserActivityEventSink::notify_activity_changing_power_state()
{
    std::lock_guard<std::mutex> lock{event_mutex};

    if (u_clock->now() >= last_activity_changing_power_state_event_time + event_period)
    {
        do_notify_activity_changing_power_state();
        last_activity_changing_power_state_event_time = u_clock->now();
    }
}

void usc::UserActivityEventSink::notify_activity_extending_power_state()
{
    std::lock_guard<std::mutex> lock{event_mutex};

    if (u_clock->now() >= last_activity_extending_power_state_event_time + event_period)
    {
        do_notify_activity_extending_power_state();
        last_activity_extending_power_state_event_time = u_clock->now();
    }
}