#!/usr/bin/ruby

#Ruby client which receives and unpacks data from arduino. 
#Expects IP arduino = 192.168.7.2, IP host = 192.168.7.1
#Port 59000 must be open

#Arguments: [optional] tofile filename parse
#tofile - write to file?
#filename - name of file to output results. If not provided and tofile is given,will generate an output file with timestamp in current directory.
#parse - print unpacked values to screen. Should only be used for debugging as printing will skew measurements of sampling rate.
#benchmark - will not unpack. For calculating sampling rate
#Usage examples:
#ruby arduinoclient.rb tofile
#ruby arduinoclient.rb 
#ruby arduinoclient.rb tofile output.txt



require 'socket'
socket = UDPSocket.new
socket.bind("192.168.7.1", 59000);
socket.connect("192.168.7.2", 59000);

puts "Made a socket..." 
i = 0;
packets = 0;
socket.puts("Hello Arduino!"); #Required for connection setup...

time = Time.now();


if(ARGV[0] == "tofile" || ARGV[0] == "benchmark") #Write to file?
	if(ARGV[1] == nil)
	f = File.open("arduino_#{time.hour}-#{time.min}-#{time.sec}.txt", "w");
	else
	f = File.open("#{ARGV[1]}", "w");
	end
end

puts "Receiving data..."
while (Time.now() - time < 60) #Collect for 1 minute

	begin
	data = socket.recvfrom_nonblock(65536); #Receive max udp packet size 
	mesg = data[0] #Remove header
	packets +=1;

	rescue IO::WaitReadable
	IO.select([socket])
	retry
	
	end

	i+=(mesg.length/2); #Two 8-bit values to make one 16-bit value


	if (ARGV[0] != "benchmark")
j = 1;

		while (j < mesg.length)
	
		val2 = mesg[j-1].ord | (mesg[j].ord << 8);
	
		#puts "Packet#: #{packets}  #{val2}"
		j+=2;
			if (ARGV[0] == "parse" || ARGV[1] == "parse" || ARGV[2] == "parse")
			puts val2
			end

			if (f != nil)
			f.write(val2);
			f.write("\n");
			end

		end


	else
	f.write(mesg);
	end
	
end

if (f != nil)
f.close();
end

puts "Packets: #{packets}"
puts "Values: #{i}"
puts "Sampling rate: #{(i/60.0)}";
