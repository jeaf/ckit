TCC      = $(USERPROFILE)\app\tcc\tcc.exe
TCC_OPTS = -Wall
PYTHON   = C:\Python27\python.exe

test.exe: ckit.o test.o test_struct.o
	$(TCC) -o $@ $+

ckit.o: ckit.c ckit.h
	$(TCC) $(TCC_OPTS) -c $<

ckit.c: array.c array.h heap.c heap.h create_amalgamation.py
	$(PYTHON) create_amalgamation.py

test_struct.o: test_struct.c test_struct.h
	$(TCC) $(TCC_OPTS) -c $<

test.o: test.c ckit.h test_struct.h
	$(TCC) $(TCC_OPTS) -c $<

