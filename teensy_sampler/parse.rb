#!/usr/bin/ruby

#ARGV[0] = File to parse
#ARGV[1] = Output file

parsed = File.new(ARGV[1], "w"); #Parsed output file
f = File.open(ARGV[0], "r"); 

bytesRead = 0;

while bytesRead < File.size?(ARGV[0]) do
val = f.read(2).unpack("v"); #Read 2 bytes at a time and convert to unsigned, 16-bit integer, little-endian 
parsed.write(val[0]);  #Write the result to file
parsed.write("\n");
#puts val;
bytesRead += 2;
end


parsed.close();
