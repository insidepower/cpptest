all:
	#gcc -g -o client client.c 
	#gcc -g -o server server.c 
	#gcc -g -pthread -D_GNU_SOURCE -c -o MemDebug.o MemDebug.c
	#gcc -g -pthread -D_GNU_SOURCE -o msdu.o -c msdu.c
	#gcc -g -pthread -D_GNU_SOURCE -o msdu msdu.o MemDebug.o client.c
	gcc -g -pthread -D_GNU_SOURCE -o msdu MemDebug.o client_msdu.c
	#gcc -g -o msdu2 client_msdu.c

obj:
	gcc -c MemDebug.c -o MemDebug.o

vlan:vlan.c
	gcc -g -pthread -D_GNU_SOURCE -o vlan vlan.c
