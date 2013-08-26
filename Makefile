TCC          = $(USERPROFILE)\app\tcc\tcc.exe

test.exe: heap.o test.o
	$(TCC) -o $@ $+

heap.o: heap.c heap.h
	$(TCC) -c $<

test.o: test.c heap.h
	$(TCC) -c $<

