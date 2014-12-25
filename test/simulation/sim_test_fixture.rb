OUT_FILE = "test/simulation/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE 
IO.popen("mdb.sh test/simulation/sim_instructions.txt > test/simulation/simlog.txt")
sleep 15
if File.exists? OUT_FILE 
    file_contents = File.read OUT_FILE
    file_contents.gsub!("\r\n","\n")
    print file_contents
    #puts file_contents.gsub("\n"){""}
end
