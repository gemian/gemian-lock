gemian-lock - improved screen locker
====================================
gemian-lock is a simple lock screen with some Gemini PDA specific features.

Currently
---------
- Requires the user to enter their password to unlock their device.
- Whilst locked it supports the Gemini external button as a 'saytime' button. Requires saytime availability.

TODO
----
- Should plug itself into X as the screensaver
- External button should answer an incoming call if present
- Should indicate activity+power button activity to repowerd to enable efficient power saving
- Passphrase should be optional (including config widget)
- Should display notifications of messages/missed calls etc

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
-------------------
Simply invoke the 'gemian-lock' command. To get out of it, enter your password and
press enter.

Upstream
--------
We doubt the upstream project will be interested in our changes, but for reference it is:
https://github.com/i3/i3lock
