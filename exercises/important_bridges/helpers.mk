# include this script in your Makefile with "include helpers.mk"

# File locations
BASENAME?=important_bridges # set BASENAME only if it was not set before
EXE_LOC?=./$(BASENAME) # set EXE_LOC only if it was not set before

TEST_DIR=./test

# The number of lines to show (for 'run' and 'test')
N_LINES=10

# run gdb
gdb: all
	gdb $(EXE_LOC)

# run valgrind on all .in files
valgrind: all
	for input in $(TEST_DIR)/*.in ; do \
		valgrind $(EXE_LOC) < $$input ; \
	done

# run the program on all .in files
run: all
	for input in $(TEST_DIR)/*.in ; do \
		echo "Running on $$input"; \
		myout=$${input%.in}.myout; \
		$(EXE_LOC) < $$input > $$myout ; \
		echo "Showing the first $(N_LINES) lines. Run 'cat $$myout' to see the full output."; \
		head -n $(N_LINES) $$myout; \
	done

# run the program on all .in files, comparing it with the expected output
test: all
	for input in $(TEST_DIR)/*.in ; do \
		echo "Running on $$input"; \
		referene=$${input%.in}.out; \
		myout=$${input%.in}.myout; \
		differences=$${input%.in}.diff; \
		time $(EXE_LOC) < $$input > $$myout ; \
		diff --side-by-side $$referene $$myout >$$differences; \
		if [ $$? -eq 0 ]; \
		then \
			echo "Output correct for file $$input"; \
		else \
			echo "Showing the first $(N_LINES) lines of the difference for file $$input. Run 'cat $$differences' to see the full report."; \
			head -n $(N_LINES) $$differences; \
		fi; \
	done
