# Intro

This is the code for the RPi gaming console, which is a project for the Computer Architecture classes at ELSYS/TUES

> NOTE:
> The code for the arduino controllers (in the controllers) is under this [link](https://create.arduino.cc/editor/kristyanYochev/5887d6e6-7c70-4aab-ba35-bb7f8fca8af2/preview)

# Prerequesites
+ A Raspberry Pi 3 Model B+
+ A microSD card with some kind of Raspbian on it

# Building
```sh
cd build
make
```

# Installing on the RPi
1. Mount the SD card on your machine
2. Open the ```boot``` drive
3. Remove all ```kernel*.img```
4. Copy-paste ```build/kernel8.img``` into the root directory of the ```boot``` drive
5. Eject the SD card
6. Boot your Raspberry Pi from the SD card
