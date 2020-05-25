version : connection.c biblio.h
	gcc -o gladewin main.c function.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic `mysql_config --cflags --libs`
