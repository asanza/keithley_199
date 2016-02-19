require 'rbconfig'
is_windows = (RbConfig::CONFIG['host_os'] =~ /mswin|mingw|cygwin/)
OUT_FILE = "./test/simulation/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE
if is_windows
	var = IO.popen("mdb.bat ./test/simulation/sim_instructions.txt > ./test/simulation/simlog.txt")
else
	var = IO.popen("mdb.sh ./test/simulation/sim_instructions.txt > ./test/simulation/simlog.txt")
end
Process.wait
if File.exists? OUT_FILE
    file_contents = File.read OUT_FILE
    file_contents.gsub!("\r\n","\n")
    print file_contents
    #puts file_contents.gsub("\n"){""}
end
