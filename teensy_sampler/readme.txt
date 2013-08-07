About
=========

This is code for a teensyduino DAQ (pjrc.com/teensy/teensyduino.html). The sampling rate is approximately 71kHz. 

Data is sent over the serial port and must be collected and parsed on the other end. 


Usage
=========

1. Set up your environment. 
- Get Arduino libraries and IDE from arduino.cc. 
- Get Teensy code and drivers from pjrc.com/teensy/td_download.html

2. Upload the code to your teensy. You can do this from within the Arduino IDE. 

3. Plug in your teensy. Use dmesg to see where it is in the filesystem. For my system it was /dev/ttyACM0. 

4. Unplug it. Run readSerial.sh youroutputfile.txt if you are on Linux. It will complain until you plug in the teensy again. You can also use readSerial.rb -- but you'll have to install the serialport gem. 

5. By default it will sample for a minute, or however long you modified it to run for. 

6. Now you can parse it. parse.rb youroutputfile.txt parsedfile.txt

7. Success!
