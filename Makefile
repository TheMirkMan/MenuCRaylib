Menu: src/Menu.c
	gcc -Wall -o Menu.exe src/Menu.c -Wl,-rpath /usr/local/lib -L/usr/local/lib -lraylib 
