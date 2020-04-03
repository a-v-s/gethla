gethla
======

Simple tool to get the ST-Link Serial String for use with OpenOCD. When multiple ST-Links are connected, 
one must specify the serial number to connect. As the ST-Link V2 uses a serial number consisting of non-ascii characters,
it is not straight forwards to capture the serial number using for example lsusb.

	$ lsusb -d 0483: -v | grep Serial
	  iSerial                 3 HÿpexUU% !g

Therefore I have created this tool to generate the serial string for use with OpenOCD


Running
=======
	$ ./gethla 
	Scanning for connected STLink
	STLink V2   hla_serial \x48\x3F\x70\x06\x65\x78\x55\x55\x25\x20\x21\x67
  
Using
=====
	$ openocd -f "interface/stlink.cfg" -c "hla_serial \x48\x3F\x70\x06\x65\x78\x55\x55\x25\x20\x21\x67" -f "target/stm32f1x.cfg" 


Building
========

At the moment I have created a minimum Makefile to build the executable.
Dependencies: libusb-1.0


	$ make 
	cc -I/usr/include/libusb-1.0  -lusb-1.0  -ogethla gethla.c

