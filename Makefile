all:
	gcc *.c *.h -o programaTrab
run:
	./programaTrab

debug:
	bash ./.tools/criaheaderdeTodasAsFiles.sh
	gcc *.c *.h -o programaTrab -g -Wall;
	valgrind ./programaTrab < 1.in

exec:
	bash ./.tools/criaheaderdeTodasAsFiles.sh
	gcc *.c *.h -o programaTrab -g -Wall;
	./programaTrab < 1.in;
	