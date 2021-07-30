CC = gcc
CFLAGS=-I$(INCPATH) -c
INCPATH=./inc/
SRCPATH=./src/
FUNCPATH=./func/
UNITTESTSPATH=./unit/
OUTPATH=./out/
.PHONY: clean
app.exe: $(OUTPATH) $(OUTPATH)main.o $(OUTPATH)matr_gener.o $(OUTPATH)matr_io.o $(OUTPATH)multiply.o
	mkdir -p $(OUTPATH)
	$(CC) -o app.exe $(OUTPATH)main.o $(OUTPATH)matr_gener.o $(OUTPATH)matr_io.o $(OUTPATH)multiply.o
$(OUTPATH)main.o: $(SRCPATH)main.c $(INCPATH)matr_gener.h $(INCPATH)matr_io.h $(INCPATH)multiply.h $(INCPATH)types.h
	$(CC) $(CFLAGS) -o$(OUTPATH)main.o $(SRCPATH)main.c
$(OUTPATH)matr_io.o: $(SRCPATH)matr_io.c $(INCPATH)matr_io.h $(INCPATH)types.h
	$(CC) $(CFLAGS) -o$(OUTPATH)matr_io.o $(SRCPATH)matr_io.c
$(OUTPATH)matr_gener.o: $(SRCPATH)matr_gener.c $(INCPATH)matr_gener.h $(INCPATH)types.h
	$(CC) $(CFLAGS) -o$(OUTPATH)matr_gener.o $(SRCPATH)matr_gener.c
$(OUTPATH)multiply.o: $(SRCPATH)multiply.c $(INCPATH)multiply.h $(INCPATH)types.h
	$(CC) $(CFLAGS) -o$(OUTPATH)multiply.o $(SRCPATH)multiply.c
clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
