# DIR='tests/gnl_main';
# FILENAME='christmas_tree.txt';
WAR="war_and_peace_test.txt"

# mkdir 'outBUF';
# mkdir 'diffBUF';

for i in 1 `seq 2000 2000 10000`
	do 
		echo "BUFFER SIZE is $i\n\n";
		gcc get*.c main.c -D BUFFER_SIZE=$i;
		/usr/bin/time >> out.txt ./a.out $WAR 2>&1;
		echo "\n";
	done