# https://makefiletutorial.com/

#CPP COMPILER AND FLAGS
C = gcc
CFLAGS = -g -Wall -fstack-protector -O3

#CPP COMPILER AND FLAGS
CXX = g++
CXXFLAGS = -g -Wall -fstack-protector -O3

src_ext = c
VALGRIND_MEM_FLAGS = --tool=memcheck --track-origins=yes
VALGRIND_LEAKS_FLAGS = --leak-check=full

all: help

help:
	@echo 'Makefile help:'
	@echo 'make exercises'

compile_src:
	gcc Atp1.c -o Atp1_exe


gdb: $(APP_NAME)	
	gdb ./$(APP_NAME)

clean:
	rm -f *.o

clear_terminal:
	clear

valgrind:
	valgrind ./$(APP_NAME)


mem:
	clear
	make $(APP_NAME)
	valgrind $(VALGRIND_MEM_FLAGS) ./$(APP_NAME) ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt
	make clean

leaks:
	clear
	make $(APP_NAME)
	valgrind $(VALGRIND_LEAKS_FLAGS) ./$(APP_NAME) ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt
	make clean
# valgrind leaks:
# 	$(valgrind_leaks_flags) ./$(APP_NAME) ftp://netlab1.fe.up.pt/pub.txt

$(files_list): %.o: %.$(src_ext)

Atp1: compile_src 
	./Atp1_exe