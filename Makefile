TCC      = $(USERPROFILE)\app\tcc\tcc.exe
TCC_OPTS = -Wall -g
# TCC_OPTS = -Wall -g -DNDEBUG
PYTHON   = C:\Python27\python.exe

test.exe: ckit.o test.o test_struct.o
	$(TCC) -o $@ $+

ckit.o: ckit.c ckit.h
	$(TCC) $(TCC_OPTS) -c $<

ckit.c: array.c array.h hashtbl.c hashtbl.h heap.c heap.h ckit.config ckitgen.py
	$(PYTHON) ckitgen.py

test_struct.o: test_struct.c test_struct.h
	$(TCC) $(TCC_OPTS) -c $<

test.o: test.c ckit.h test_struct.h
	$(TCC) $(TCC_OPTS) -c $<

