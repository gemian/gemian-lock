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

#ifndef USC_POWER_BUTTON_EVENT_SINK_H_
#define USC_POWER_BUTTON_EVENT_SINK_H_

#include "dbus_connection_handle.h"

namespace usc
{

    class PowerButtonEventSink
    {
    public:
        PowerButtonEventSink(std::string const& dbus_address);

        void notify_on_press();
        void notify_on_release();
        void notify_sleep_press();
        void notify_sleep_release();
        void notify_off_press();
        void notify_off_release();

    private:
        void send_signal_name(const char *name) const;

    private:
        DBusConnectionHandle dbus_connection;
    };

}

#endif