pathlib=LRU-cache/lib
pathmain=LRU-cache/main
$(pathlib)/models/node.o: $(pathlib)/models/node.c
	gcc -c $(pathlib)/models/node.c -I$(pathlib) -o $(pathlib)/models/node.o
$(pathlib)/models/message.o: $(pathlib)/models/message.c
	gcc -c $(pathlib)/models/message.c -I$(pathlib) -o $(pathlib)/models/message.o
$(pathlib)/filehandler/filehandler.o: $(pathlib)/filehandler/filehandler.c
	gcc -c $(pathlib)/filehandler/filehandler.c -I$(pathlib) -o $(pathlib)/filehandler/filehandler.o
$(pathlib)/doublylinkedlist/doublylinkedlist.o: $(pathlib)/doublylinkedlist/doublylinkedlist.c
	gcc -c $(pathlib)/doublylinkedlist/doublylinkedlist.c -I$(pathlib) -o $(pathlib)/doublylinkedlist/doublylinkedlist.o	
$(pathlib)/hashmap/hashmap.o: $(pathlib)/hashmap/hashmap.c
	gcc -c $(pathlib)/hashmap/hashmap.c -I$(pathlib) -o $(pathlib)/hashmap/hashmap.o
main.exe: $(pathlib)/models/node.o $(pathlib)/models/message.o $(pathlib)/filehandler/filehandler.o $(pathlib)/doublylinkedlist/doublylinkedlist.o $(pathlib)/hashmap/hashmap.o  $(pathmain)/main.c 
	gcc $(pathlib)/models/node.o $(pathlib)/models/message.o $(pathlib)/filehandler/filehandler.o $(pathlib)/doublylinkedlist/doublylinkedlist.o $(pathlib)/hashmap/hashmap.o $(pathmain)/main.c -I$(pathlib) -o $(pathmain)/main.exe
