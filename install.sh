#!/bin/bash

# Exit if something fails
set -e

if [ -e /etc/os-release ]; then
   . /etc/os-release
else
   . /usr/lib/os-release
fi

if [ "$ID_LIKE" = "arch" ];then
    package_manager="pacman -S"
elif [ "$ID_LIKE" = "debain" ];then
    package_manager="apt-get install"
elif [ "$ID" = "fedora" ];then
    package_manager="dnf install"
elif [ "$ID_LIKE" = "opensuse suse" ];then
    package_manager="zypper install"
fi

sudo $package_manager cmake extra-cmake-modules

mkdir -p ~/.config/krunnercrypto
cp config/config.json ~/.config/krunnercrypto

mkdir -p build
cd build

cmake -DKDE_INSTALL_PLUGINDIR=`kf5-config --qt-plugins` -DCMAKE_BUILD_TYPE=Release  ..
make -j$(nproc)
sudo make install

# KRunner needs to be restarted for the changes to be applied
# we can just kill it and it will be started when the shortcut is invoked
kquitapp5 krunner
