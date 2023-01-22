all:	message pipe 

message:  msg-server msg-client

msg-server:  msg-server.c
	cc msg-server.c -o msg-server

msg-client:  msg-client.c
	cc msg-client.c -o msg-client

pipe: ex-pipe 

ex-pipe: ex-pipe.c
	cc ex-pipe.c -o ex-pipe

clean: 
	rm ex-pipe msg-server msg-client
