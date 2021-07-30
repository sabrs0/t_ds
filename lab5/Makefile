CC=gcc
INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
CFLAGS= -c
.PHONY: clean
app.exe: $(OUTPATH) $(OUTPATH)main.o $(OUTPATH)funcs.o
	mkdir -p $(OUTPATH)
	$(CC) -o app.exe $(OUTPATH)main.o $(OUTPATH)funcs.o

$(OUTPATH)main.o: $(OUTPATH) $(SRCPATH)main.c $(INCPATH)funcs.h
	mkdir -p $(OUTPATH)
	$(CC) $(CFLAGS) -o$(OUTPATH)main.o $(SRCPATH)main.c

$(OUTPATH)funcs.o: $(OUTPATH) $(SRCPATH)funcs.c $(INCPATH)funcs.h
	mkdir -p $(OUTPATH)
	$(CC) $(CFLAGS) -o$(OUTPATH)funcs.o $(SRCPATH)funcs.c

clean:
	rm -fv *.exe
	rm -fv *.png
	rm -fv *.gv	
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
