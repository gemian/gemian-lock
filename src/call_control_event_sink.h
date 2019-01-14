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

#ifndef CALL_CONTROL_EVENT_SINK_H_
#define CALL_CONTROL_EVENT_SINK_H_

#include "dbus_connection_handle.h"

class CallControlEventSink {
public:
    CallControlEventSink(std::string const &dbus_address);

    void hang_up_and_accept_call();

private:
    void send_signal_name(const char *name) const;

private:
    usc::DBusConnectionHandle dbus_connection;
};


#endif //CALL_CONTROL_EVENT_SINK_H_