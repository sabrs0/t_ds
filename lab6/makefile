INC = ./inc/
OUT = ./out/
SRC = ./src/
.PHONY: clean
app.exe: $(OUT) $(OUT)main.o $(OUT)tree_funcs.o $(OUT)hash_funcs.o
	mkdir -p $(OUT)
	gcc -o app.exe $(OUT)main.o $(OUT)tree_funcs.o $(OUT)hash_funcs.o
stat.exe: $(OUT) $(OUT)stat.o $(OUT)tree_funcs.o $(OUT)hash_funcs.o
	mkdir -p $(OUT)
	gcc -o stat.exe $(OUT)stat.o $(OUT)tree_funcs.o $(OUT)hash_funcs.o
$(OUT)stat.o: $(SRC)stat.c $(INC)tree_funcs.h $(INC)hash_funcs.h
	gcc -I$(INC) -c -o $(OUT)stat.o $(SRC)stat.c
$(OUT)main.o: $(SRC)main.c $(INC)tree_funcs.h $(INC)hash_funcs.h
	gcc -I$(INC) -c -o $(OUT)main.o $(SRC)main.c 
$(OUT)tree_funcs.o: $(SRC)tree_funcs.c $(INC)tree_funcs.h
	gcc -I$(INC) -c -o $(OUT)tree_funcs.o $(SRC)tree_funcs.c
$(OUT)hash_funcs.o: $(SRC)hash_funcs.c $(INC)hash_funcs.h
	gcc -I$(INC) -c -o $(OUT)hash_funcs.o $(SRC)hash_funcs.c
clean:
	rm -fv *.exe
	rm -fv *.o
	rm -fv *.gcno
