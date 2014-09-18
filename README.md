Keithley 199 Upgrade
--------------------

Recently I bought an old Keithley 199 multimeter (datasheet can be found at 
http://exodus.poly.edu/~kurt/manuals/manuals/Keithley/KEI%20199%20Operation,%20Programming%20&%20Maintenance.pdf). 
It was cheap because it didn't work. The digital control board was damaged 
(the "Versatile Interface Adapter" was dead), so I designed a new digital 
control board (see section hw.kicad) around an pic32 which was liying around. 
The new board replaces the old and is in charge of controlling the analog 
circuitry (which contains a custom made, discrete analog digital converters, 
signal conditioning and analog switchs for mode and range selection). 
For the software, I used the mplabx environment from microchip and the xc32 
compiler. 

The software works (at least I can measure AC and DC voltages with good 
accuracy, support for resistance and current measurements is on the way). 

The new board contains also a temperature sensor (for accurate temperature 
compensation) and instead of the old gpib interface in the old board, an usb
interface.

