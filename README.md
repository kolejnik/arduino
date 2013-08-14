arduino
=======

Arduino code for fast voltage sampling and Ethernet data transfer. 


How to use?
==========

1. Get Arduino IDE and drivers. 
2. Replace the following library files with the ones in the lib directory. Where they are located on your system depends on where you installed the Arduino IDE:

	w5100.h
	w5100.cpp
	EthernetUDP.h

3. Plug in your Arduino and Ethernet cable. To use the default configuration, set the following IP address for your host's Ethernet interface: 192.168.7.1
4. Make sure port 59000 is open on the host. 
5. Upload the code to your Arduino. If you want to first test that everything works, upload the ethernet-test code. 
6. Run the arduinoclient.rb on your host with your parameters of choice. 

Teensy
=====

Similar process, except you will be running the serial ruby client instead. No ports need to be open.  
