chat_server: *.c
	gcc *.c *.h  -o chat_server -std=c99 `mysql_config --cflags --libs`