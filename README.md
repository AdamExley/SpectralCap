# SpectralCap (WIP)

**Hyper-spectral image capture and preprocessing.**


Focuses on photography of IR and UV light in addition to visible light.


This project center's around a high-power LED controller, which is controlled by a [Adafruit Itsy-bitsy M0 Express](https://www.adafruit.com/product/3727).

The design is capable of running up to 12 different LEDs, with the limitation that only one be fully on at a time, and an external bench constant-current power source be used. The controller is powered independantly from the LEDs, and up to ~1A of current can be run through the controller.

Lights can be controlled with a serial command interface defined in [SerialCom.cpp](./SpecLight/SerialCom.cpp). (Or simply send 'help' in the serial console for the commands to be displayed)

Project schematics and PCB are [available here](https://oshwlab.com/exley2020/speclight). The PCBs can be bought assembled from [JLCPCB](https://jlcpcb.com/), with the exception of the [Itsy-bitsy M0 Express](https://www.adafruit.com/product/3727), which must be supplied and soldered on manually.


## Disclaimer

This project is a *bit* of a reach. Hyperspectal photography is more easily done with a filter wheel, and outdoors. 

Using LEDs as a hyperspectral source *does* give you more control over levels and makes things like UV photography more feasible, but it's very involved.

What can I say, I wanted to try it and see what happened!

> This also means that my code isn't exactly commented very well, because this was mostly just an experiment for me, sorry! (Please contact me if you want more info.)










