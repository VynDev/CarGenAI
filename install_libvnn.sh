#!/bin/sh

make dynamic -C ThirdParty/libvnn
mkdir -p Binaries/Linux
cp ThirdParty/libvnn/libvnn.so Binaries/Linux/libvnn.so