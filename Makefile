run: compile
	./main

compile:
	gcc main.c atlacan.c -o main

clean:
	rm -f main

tar:
	tar -zcvf MOLINATTI_XAVIER.tar *.c *.h Makefile README.md
