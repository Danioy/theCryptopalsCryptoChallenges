TGT = single_xor

ALL: $(TGT)

single_xor: single_xor.o common.o
	gcc -o $@ $^

common.o: ../common.c ../common.h
	gcc -Wall -c -I.. $^

%.o: %.c ../common.h
	gcc -Wall -c -I.. $^

clean:
	rm -f *.o $(TGT)
