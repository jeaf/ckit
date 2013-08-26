TCC          = $(USERPROFILE)\app\tcc\tcc.exe

test.exe: heap.o
	$(TCC) -o $@ $+

heap.o: heap.c
	$(TCC) -c $<

