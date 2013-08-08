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
     
	 values_read = 0;
    sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
    f = File.new(ARGV[0], "w");
    sp.read_timeout = 8; 
	 
    #just read forever
	
	start = Time.now();
	while(Time.now() - start < 60)
		
			stuff = sp.read(2)       # see note 2
			while(stuff == nil)
			stuff = sp.read(2)
			end
			
			values_read += 1;
			stuff = stuff.bytes.to_a
			result = stuff[0] | (stuff[1] << 8)
			f.write(result);
			f.write("\n");
			#puts stuff;
			
			#puts stuff.class #String
			
		
     
	 end
    sp.close                       #see note 1
	f.close();
	
	puts (values_read/60.0);
