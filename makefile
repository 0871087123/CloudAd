#Serial : main.c
#	gcc -g -o $@ $^
Serial : main.cpp
	g++ -g -o $@ $^ -lserial 
clean:
	rm -rf Serial
