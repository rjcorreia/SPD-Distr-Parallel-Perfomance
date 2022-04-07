read -p "Insert type of programming: " file
read -p "Insert input file: " input
read -p "Insert number of times: " n
read -p "Insert name of output: " output
for ((i=0; i<$n; i++))
do
   ./$file ../inputs/$input >> outputs/$output
   done
   exit 0
