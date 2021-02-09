# DIR='tests/gnl_main';
# FILENAME='christmas_tree.txt';
# FILE="$DIR/$FILENAME";

# mkdir 'outBUF';
# mkdir 'diffBUF';

for i in {1..100}
	do 
		echo "BUFFER SIZE is $i\n\n";
		gcc -g get*.c main.c -D BUFFER_SIZE=$i;
		./a.out $FILE > outBUF/outBUF$i.txt;
		diff -w out.txt $FILE > diffBUF/diffBUF$i.txt;
		echo "\n";
	done