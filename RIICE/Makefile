CC = cc
DO = python
FLAGS = -fPIC -shared -o
SRC = *.c
EXEC = *.py

file : 
	$(CC) $(FLAGS) rice.so $(SRC)
	$(DO) $(EXEC)
	rm rice.so
