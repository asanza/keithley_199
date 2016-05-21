# Keithley 199 Digital Board Replacement

This is an upgrade replacement for the digital control board on Keithley 199 multimeters.

The [Keithley 199](http://exodus.poly.edu/~kurt/manuals/manuals/Keithley/KEI%20199%20Operation,%20Programming%20&%20Maintenance.pdf) is a digital multimeter built in the 90. It is capable of current, voltage and resistance measurements and also provides a gpib interface for remote control.

This multimeters contains three electronic circuit boards, one which contains the analog circuitry, including analog signal conditioning and analog digital converter, a display board which contains the user interface, and a digital control board, with a processor who controls display, gpib interface and analog digital converter.

This repository contains hardware and software files needed to build a replacement of this board.

# Building the hardware 

The hardware files are in [Kicad](http://kicad-pcb.org/) format. Gerber files are available.

# Building the software

The software was built with the microchip toolchain (http://www.microchip.com/mplab/compilers). 

We use [Ceedling](http://www.throwtheswitch.org/ceedling/) for building and testing (but for comfort, [MPLABX](http://www.microchip.com/mplab/mplab-x-ide)files are available). 

In order to build the software, go to the root directory and do:

```
$rake release

```
Or to perform the unit tests:
```
$rake test:all
```


## Hardware

The hardware is pretty basic. It contains a pic32mx controller which do the heavy lifting. An ftdi chip provides an usb interface, while two open drain drivers controll the led displays. The external trigger input and output are connected to the microcontroller through the necessary input/output protection.

## Software 