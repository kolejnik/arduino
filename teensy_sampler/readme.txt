Using teensy-adc
===============

*** This is currently for Linux only... 

1. Set up your environment. 
- Get Arduino libraries and IDE from arduino.cc. 
- Get Teensy code and drivers from pjrc.com/teensy/td_download.html

2. Upload the code to your teensy. 

3. Plug in your teensy. Use dmesg to see where it is in the filesystem. For my system it was /dev/ttyACM0. 

4. Unplug it. Run runSerial.sh youroutputfile.txt. It will complain until you plug in the teensy again. 

5. By default it will sample for a minute, or however long you modified it to run for. 

6. Now you can parse it. parse.rb youroutputfile.txt 

7. Success!
