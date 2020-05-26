all:
	gcc *.c *.h -o programaTrab
run:
	./programaTrab
wall:
	gcc *.c *.h -o programaTrab -Wall -g
debug:
	bash ./.Tools/criaHeaderTodas.sh
	gcc *.c *.h -o programaTrab -g -Wall;
	valgrind ./programaTrab

exec:
	bash ./.tools/criaheaderdeTodasAsFiles.sh
	gcc *.c *.h -o programaTrab -g -Wall;
	./programaTrab < 1.in;

test:
	gcc test.c command.c command.h -o out -g