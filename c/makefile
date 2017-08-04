
exc: machexec.o functionsc.o
	gcc machexec.o functionsc.o -o exc

machexec.o: machexec.c
	gcc -c machexec.c

functionsc.o: functionsc.c functionsc.h
	gcc -c functionsc.c

run: exc
	./exc
clean:
	rm *.o exc
