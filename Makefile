all:
	gcc *.c *.h -o programaTrab
run:
	./programaTrab
wall:
	gcc *.c *.h -o programaTrab -Wall
debug:
	bash ./.tools/criaheaderdeTodasAsFiles.sh
	gcc *.c *.h -o programaTrab -g -Wall;
	valgrind ./programaTrab

exec:
	bash ./.tools/criaheaderdeTodasAsFiles.sh
	gcc *.c *.h -o programaTrab -g -Wall;
	./programaTrab < 1.in;
	