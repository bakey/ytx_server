#./main_exe -d"../data/" -s"pps" -c"../conf/parser.conf" -n$1 -i20000 2>err.log  1>debug.log &
./main_exe -d"./data/" -s"forum" -c../conf/parser.conf -n20 -i20 -b10 -t0 2>err.log 1>debug.log &
