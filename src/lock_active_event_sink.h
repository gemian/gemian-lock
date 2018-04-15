//
// Created by adam on 15/04/18.
//

#ifndef GEMIAN_LOCK_ACTIVE_SINK_H
#define GEMIAN_LOCK_ACTIVE_SINK_H

#include "dbus_connection_handle.h"

class LockActiveEventSink {
public:
    LockActiveEventSink(std::string const& dbus_address);

    void notify_lock_active();
    void notify_lock_inactive();

private:
    usc::DBusConnectionHandle dbus_connection;
};


#endif //GEMIAN_LOCK_ACTIVE_SINK_H
