
CC=g++-4.9
COMPILE_FLAGS=-Wall -O3 -std=c++11
BGL_COMPILE_FLAGS=-O2 -std=c++11 -I /usr/local/include/boost
DEBUG_FLAGS=-Wall -O0 -g -std=c++11 -I /usr/local/include/boost

NAME=coin_tossing

all:
	if [ ! -d bin ] ; then mkdir bin ; fi;
	$(CC) $(BGL_COMPILE_FLAGS) -o bin/$(NAME) $(NAME).cpp

debug:
	if [ ! -d bin ] ; then mkdir bin ; fi;
	$(CC) $(DEBUG_FLAGS) -o bin/$(NAME) $(NAME).cpp
	gdb bin/$(NAME)

clean:
	if [ -d bin ] ; then rm -R bin ; fi;

test:
	for input in testsets/*.in ; do \
		./bin/$(NAME) < $$input > $$input.tmp ; \
	done
	for output in testsets/*.out ; do \
		diff $$output $${output%.out}.in.tmp ; \
	done
	rm testsets/*.in.tmp

time:
	for input in testsets/*.in ; do \
		time ./bin/$(NAME) < $$input > $$input.tmp ; \
	done
	rm testsets/*.in.tmp
