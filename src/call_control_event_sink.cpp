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

#include "call_control_event_sink.h"
#include "dbus_message_handle.h"

char const *const dbus_telephony_approver_name = "com.canonical.Approver";
char const *const dbus_telephony_approver_path = "/com/canonical/Approver";
char const *const dbus_telephony_approver_interface = "com.canonical.TelephonyServiceApprover";
char const *const dbus_telephony_approver_message = "HangUpAndAcceptCall";

CallControlEventSink::CallControlEventSink(std::string const &dbus_address)
        : dbus_connection{dbus_address} {
}

void CallControlEventSink::hang_up_and_accept_call() {
    usc::DBusMessageHandle signal{
            dbus_message_new_method_call(
                    dbus_telephony_approver_name,
                    dbus_telephony_approver_path,
                    dbus_telephony_approver_interface,
                    dbus_telephony_approver_message)};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}
