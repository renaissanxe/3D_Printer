# 3D Printer

Introduction
------------
This project is intended for use with the Stony Brook University's 3D printer in the Light Engineering building. It is designed to work with the hardware in Dr. Shanshan Yao's research lab. The purpose of this project is to integrate a dispenser with a 3D printing stage to expand its material compatibilities.  

Environment
-----------
* Sonoplot Microplotter II
* Musashi ML808GX
* Raspberry Pi 4b

Build
-----
``` 
$ git clone https://github.com/renaissanxe/3D_Printer.git
$ cd 3D_Printer
$ git submodule init
$ git submodule update
$ cd src
$ make
```

Usage
---
Update serial port config, PWM input pin at config.ini
```
To connect to Raspberry Pi use the following commands

# ssh ubuntu@ubuntu
# cd 3D_Printer/src
# sudo ./dispenserController
```
Wiring
---
Voltage divider is done as follows

![IMG_20220407_162607](https://user-images.githubusercontent.com/7773827/165858407-a8bdd549-67e1-43e4-bc6c-3f7ed73ce354.jpg)


RJ11 cable wiring
Green - Signal
Red - Ground
![IMG_20220428_153535](https://user-images.githubusercontent.com/7773827/165858136-3ac2e8d4-4aa8-401d-b2c3-33e37ceac59c.jpg)


Control Latency
---------------
|       | 19200 | 38400 |
|-------|-------|-------|
| Start | 18ms  | 13ms  |
| Stop  | 14ms  | 8ms   |



