#!/bin/bash

# This script is supposed to be used via $WINETEST_WRAPPER when running "make test" out of the guest
# Wine tree. Use like this:
#
# cd build/wine-guest32
# WINETEST_WRAPPER=/path/to/hangover/hangover-test.sh make test

# We receive arguments like ../../../wine ddraw_test.exe d3d. Throw away Wine and replace it with
# invoking qemu inside Wine instead.

my_dir="$(dirname "$0")" # Nicked from stackoverflow. Not sure if it is really reliable

shift
$my_dir/../build/wine-host/wine64 $my_dir/../build/qemu/x86_64-windows-user/qemu-x86_64.exe.so $@
