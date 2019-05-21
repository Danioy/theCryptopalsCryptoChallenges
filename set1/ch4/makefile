TGT = single_char_xor


ALL: $(TGT)

single_char_xor: single_char_xor.o common.o
	gcc -o $@ $^

common.o: ../common.c ../common.h
	gcc -Wall -I.. -c $^

single_char_xor.o: single_char_xor.c ../common.h
	gcc -Wall -I.. -c $^

clean:
	rm -f $(TGT) *.o
