#! /bin/bash

cd
mkdir A
mkdir B
mkdir C
cp -r linux-5.19.9 A
cp -r linux-5.19.9 B
cp -r linux-5.19.9 C
cd A
cd linux-5.19.9
cp config-rev-9-gold .config
cd
cd B
cd linux-5.19.9
cp config-rev-9-gold .config
cd
cd C
cd linux-5.19.9
cp config-rev-9-gold .config
cd