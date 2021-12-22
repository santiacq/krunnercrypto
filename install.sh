#!/bin/bash

# Exit if something fails
set -e

declare -A osInfo;
osInfo[/etc/debian_version]="apt-get install"
osInfo[/etc/fedora-release]="dnf install"
osInfo[/etc/arch-release]="pacman -S"

for f in ${!osInfo[@]}
do
    if [[ -f $f ]];then
        package_manager=${osInfo[$f]}
    fi
done

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
