# Kosy Wayfire Integration
Simple plugin to integrate the Kosy enviroment with Wayfire. Plugin provides necessary features for Jupiter (and later also Kerberos).

Depends on Wayfire obviously.

### Build and install
meson build

ninja -C build

sudo ninja -C build install

### Enable
Add full path of this plugin into the list of plugins in wayfire.ini, e.g. ``/usr/local/lib/x86_64-linux-gnu/wayfire/libkwi.so``
