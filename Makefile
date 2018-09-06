all:
	gcc  client.c  -o client  -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient
	gcc  server.c  -o server 	-I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient
	gcc  register.c  -o register -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient	
	gcc  login.c -o login    -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient
	gcc  chat.c -o chat -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient
clean:
	rm client server register 