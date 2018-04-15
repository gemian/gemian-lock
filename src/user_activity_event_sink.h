//
// Created by adam on 15/04/18.
//

#ifndef GEMIAN_LOCK_USER_ACTIVITY_EVENT_SINK_H
#define GEMIAN_LOCK_USER_ACTIVITY_EVENT_SINK_H


class user_activity_event_sink {

};


#endif //GEMIAN_LOCK_USER_ACTIVITY_EVENT_SINK_H
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

#ifndef USC_UNITY_USER_ACTIVITY_EVENT_SINK_H_
#define USC_UNITY_USER_ACTIVITY_EVENT_SINK_H_

#include <mutex>
#include <memory>
#include "dbus_connection_handle.h"
#include "clock.h"

namespace usc
{

    class UserActivityEventSink
    {
    public:
        UserActivityEventSink(std::string const& dbus_address);

        void notify_activity_changing_power_state();
        void notify_activity_extending_power_state();

    private:
        void do_notify_activity_changing_power_state();
        void do_notify_activity_extending_power_state();

    private:
        DBusConnectionHandle dbus_connection;
        std::mutex event_mutex;
        std::shared_ptr<usc::Clock> u_clock;
        std::chrono::milliseconds event_period;
        std::chrono::steady_clock::time_point last_activity_changing_power_state_event_time;
        std::chrono::steady_clock::time_point last_activity_extending_power_state_event_time;
    };

}

#endif