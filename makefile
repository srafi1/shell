compile: tokenizer.c tokenizer.h shell.c shell.h exec.c exec.h
	gcc -c shell.c tokenizer.c exec.c
	gcc shell.o tokenizer.o exec.o -o shell
run: shell
	./shell
clean: shell
	rm shell
	rm *.o
