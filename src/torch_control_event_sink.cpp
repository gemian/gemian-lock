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

#include "torch_control_event_sink.h"
#include "dbus_message_handle.h"

char const *const dbus_gemian_leds_name = "org.thinkglobally.Gemian.LEDs";
char const *const dbus_gemian_leds_path = "/org/thinkglobally/Gemian/LEDs";
char const *const dbus_gemian_leds_interface = "org.thinkglobally.Gemian.LEDs";
char const *const dbus_gemian_leds_message = "SetTorch";

TorchControlEventSink::TorchControlEventSink(std::string const &dbus_address) : dbus_connection{dbus_address}, on(false) {
}

void TorchControlEventSink::toggle_torch() {
    on = !on;
    dbus_uint32_t v = 0;
    DBusMessage *msg = dbus_message_new_method_call(
            dbus_gemian_leds_name,
            dbus_gemian_leds_path,
            dbus_gemian_leds_interface,
            dbus_gemian_leds_message);
    dbus_message_append_args(msg,
            DBUS_TYPE_BOOLEAN, &on,
            DBUS_TYPE_UINT32, &v,
            DBUS_TYPE_INVALID);
    usc::DBusMessageHandle signal{ msg };

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}
