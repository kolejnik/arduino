#Optional, write ADC values to a file on host
#From Arduino website: http://playground.arduino.cc/Interfacing/Ruby
#
#simplest ruby program to read from arduino serial,
    #using the SerialPort gem
    #(http://rubygems.org/gems/serialport)
     
    require "serialport"
     
    #params for serial port
    port_str = "COM18"  #may be different for you
    baud_rate = 9600
    data_bits = 8
    stop_bits = 1
    parity = SerialPort::NONE
     
    sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
    f = File.new(ARGV[0], "w");
	 
	 
    #just read forever
	
	start = Time.now();
	while(Time.now() - start < 60)
		
			i = sp.gets.chomp       # see note 2
			#puts i
			f.write(i);
			f.write("\n");
			#puts i.class #String
			
		
     
	 end
    sp.close                       #see note 1
	f.close();
