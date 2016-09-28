
CC=g++-4.9
COMPILE_FLAGS=-Wall -O3
DEBUG_FLAGS=-Wall -O0 -g

NAME=moving_books

all:
	if [ ! -d bin ] ; then mkdir bin ; fi;
	$(CC) $(COMPILE_FLAGS) -o bin/$(NAME) $(NAME).cpp

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
