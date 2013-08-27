TCC      = $(USERPROFILE)\app\tcc\tcc.exe
TCC_OPTS = -Wall

test.exe: array.o heap.o test.o
	$(TCC) -o $@ $+

array.o: array.c array.h
	$(TCC) $(TCC_OPTS) -c $<

heap.o: heap.c heap.h
	$(TCC) $(TCC_OPTS) -c $<

test.o: test.c array.h heap.h
	$(TCC) $(TCC_OPTS) -c $<

