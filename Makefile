TCC      = $(USERPROFILE)\app\tcc\tcc.exe
TCC_OPTS = -Wall
PYTHON   = C:\Python27\python.exe

test.exe: ckit.o test.o
	$(TCC) -o $@ $+

ckit.o: ckit.c ckit.h
	$(TCC) $(TCC_OPTS) -c $<

ckit.c: array.c array.h heap.c heap.h create_amalgamation.py
	$(PYTHON) create_amalgamation.py

test.o: test.c ckit.h
	$(TCC) $(TCC_OPTS) -c $<

