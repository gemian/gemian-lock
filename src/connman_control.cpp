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

#include "connman_control.h"
#include <cstring>

#include "dbus_message_handle.h"

char const *const dbus_connman_name = "net.connman";
char const *const dbus_connman_path_cellular = "/net/connman/technology/cellular";
char const *const dbus_connman_path_wifi = "/net/connman/technology/wifi";
char const *const dbus_connman_path_bluetooth = "/net/connman/technology/bluetooth";
char const *const dbus_connman_interface = "net.connman.Technology";
char const *const dbus_connman_message_set_property = "SetProperty";
char const *const dbus_connman_message_get_properties = "GetProperties";
char const *const dbus_connman_message_powered = "Powered";

ConnmanControl::ConnmanControl(std::string const &dbus_address) :
        dbus_connection{dbus_address} {
}

dbus_bool_t ConnmanControl::getPoweredForPath(const char *path) {
    DBusMessageIter messageItr;
    DBusMessageIter contentItr;
    DBusMessageIter elementItr;
    DBusMessageIter variantItr;
    int messageType;
    int contentType;
    int elementType;
    int variantType;
    const char *replyString;
    dbus_bool_t replyValue;
    dbus_bool_t ret = false;

    DBusMessage *msg = dbus_message_new_method_call(
            dbus_connman_name,
            path,
            dbus_connman_interface,
            dbus_connman_message_get_properties);

    DBusMessage *reply = dbus_connection_send_with_reply_and_block(dbus_connection, msg, -1, nullptr);

    dbus_message_iter_init(reply, &messageItr);
    while ((messageType = dbus_message_iter_get_arg_type(&messageItr)) != DBUS_TYPE_INVALID) {
        if (messageType == DBUS_TYPE_ARRAY) {
            dbus_message_iter_recurse(&messageItr, &contentItr);
            while ((contentType = dbus_message_iter_get_arg_type(&contentItr)) != DBUS_TYPE_INVALID) {
                if (contentType == DBUS_TYPE_DICT_ENTRY) {
                    dbus_message_iter_recurse(&contentItr, &elementItr);
                    while ((elementType = dbus_message_iter_get_arg_type(&elementItr)) != DBUS_TYPE_INVALID) {
                        if (elementType == DBUS_TYPE_STRING) {
                            dbus_message_iter_get_basic(&elementItr, &replyString);
                        }
                        if (elementType == DBUS_TYPE_VARIANT) {
                            dbus_message_iter_recurse(&elementItr, &variantItr);
                            while ((variantType = dbus_message_iter_get_arg_type(&variantItr)) != DBUS_TYPE_INVALID) {
                                if (variantType == DBUS_TYPE_BOOLEAN) {
                                    dbus_message_iter_get_basic(&variantItr, &replyValue);
                                    if (strcmp(replyString, dbus_connman_message_powered) == 0) {
                                        ret = replyValue;
                                    }
                                }
                                dbus_message_iter_next(&variantItr);
                            }
                        }
                        dbus_message_iter_next(&elementItr);
                    }
                }
                dbus_message_iter_next(&contentItr);
            }
        }
        dbus_message_iter_next(&messageItr);
    }

    return ret;
}

void ConnmanControl::setPoweredForPath(const char *path) {
    DBusMessageIter iter;
    DBusMessageIter variant;
    dbus_bool_t on = !getPoweredForPath(path);

    DBusMessage *msg = dbus_message_new_method_call(
            dbus_connman_name,
            path,
            dbus_connman_interface,
            dbus_connman_message_set_property);
    dbus_message_iter_init_append(msg, &iter);
    dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &dbus_connman_message_powered);
    dbus_message_iter_open_container(&iter, DBUS_TYPE_VARIANT, "b", &variant);
    dbus_message_iter_append_basic(&variant, DBUS_TYPE_BOOLEAN, &on);
    dbus_message_iter_close_container(&iter, &variant);
    usc::DBusMessageHandle signal{msg};

    dbus_connection_send(dbus_connection, signal, nullptr);
    dbus_connection_flush(dbus_connection);
}

void ConnmanControl::toggle_celluar() {
    setPoweredForPath(dbus_connman_path_cellular);
}

void ConnmanControl::toggle_wifi() {
    setPoweredForPath(dbus_connman_path_wifi);
}

void ConnmanControl::toggle_bluetooth() {
    setPoweredForPath(dbus_connman_path_bluetooth);
}
