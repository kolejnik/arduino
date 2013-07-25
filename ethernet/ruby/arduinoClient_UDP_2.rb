#!/usr/bin/ruby

require 'socket'


socket = UDPSocket.new
socket.bind("192.168.7.1", 59000);
socket.connect("192.168.7.2", 59000);

puts "Made a socket..." 
i = 0;
packets = 0;
socket.puts("Hello Arduino!");

time = Time.now();

#f = File.open("arduino_#{time.hour}-#{time.min}-#{time.sec}.txt", "w");

while (Time.now() - time < 60)

	begin
	data = socket.recvfrom_nonblock(65536);
	mesg = data[0]
	#puts mesg
	packets +=1;

	rescue IO::WaitReadable
	IO.select([socket])
	retry
	
	end

i+=(mesg.length/2);
#f.write(mesg);
=begin
j = 1;

	while (j < mesg.length)
	
	val2 = mesg[j-1].ord | (mesg[j].ord << 8);
	
	#puts "Packet#: #{packets}  #{val2}"
	j+=2;
	#puts val2

	end

=end
end

#f.close();
puts "Packets: #{packets}"
puts "Values: #{i}"
puts "Sampling rate: #{(i/60.0)}";
