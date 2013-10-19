#Serial : main.c
#	gcc -g -o $@ $^
Serial : main.cpp 
# also can use static library
#../libs/libserial.a
	$(CXX) -g -L./../libs/ -I./../include/ -o $@ $^ -lserial --static 
clean:
	rm -rf Serial
