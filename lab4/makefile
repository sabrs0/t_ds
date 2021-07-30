app.exe: main.o funcs_list.o funcs_arr.o
	gcc -o app.exe main.o funcs_list.o funcs_arr.o
main.o: main.c funcs_list.c funcs_arr.c funcs.h
	gcc -c main.c funcs_list.c funcs_arr.c
funcs_list.o: funcs_list.c funcs.h
	gcc -c funcs_list.c
funcs_arr.o: funcs_arr.c funcs.h
	gcc -c funcs_arr.c
clean:
	rm -fv *exe
	rm -fv *o
