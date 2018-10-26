dynvec.o: dynvec.c dynvec.h
	clang -c $<

test: dynvec.o test_dynvec.c
	clang -o dynvec_test $^
	./dynvec_test
	echo Tests Pass
