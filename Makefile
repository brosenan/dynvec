dynvec.o: dynvec.c dynvec.h
	${CC} -c $<

test: dynvec.o test_dynvec.c
	${CC} -o dynvec_test $^
	./dynvec_test
	echo Tests Pass
