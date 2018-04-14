gemian-lock - improved screen locker
===============================
gemian-lock is a simple screen locker like slock. After starting it, you will
see a white screen (you can configure the color/an image). You can return
to your screen by entering your password.

Many little improvements have been made to gemian-lock over time:

- gemian-lock forks, so you can combine it with an alias to suspend to RAM
  (run "gemian-lock && echo mem > /sys/power/state" to get a locked screen
   after waking up your computer from suspend to RAM)

- You can specify either a background color or a PNG image which will be
  displayed while your screen is locked.

- You can specify whether gemian-lock should bell upon a wrong password.

- gemian-lock uses PAM and therefore is compatible with LDAP etc.
  On OpenBSD gemian-lock uses the bsd_auth(3) framework.

Requirements
------------
- pkg-config
- libxcb
- libxcb-util
- libpam-dev
- libcairo-dev
- libxcb-xinerama
- libxcb-randr
- libev
- libx11-dev
- libx11-xcb-dev
- libxkbcommon >= 0.5.0
- libxkbcommon-x11 >= 0.5.0

Running gemian-lock
-------------
Simply invoke the 'gemian-lock' command. To get out of it, enter your password and
press enter.

On OpenBSD the `gemian-lock` binary needs to be setgid `auth` to call the
authentication helpers, e.g. `/usr/libexec/auth/login_passwd`.

Upstream
--------
Please submit pull requests to https://github.com/i3/i3lock
