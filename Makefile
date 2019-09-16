CC := gcc
CFLAGS := -g -Wall
SRCDIR := src
OBJDIR := obj
TSTDIR := tests
INCDIR := include
FLAGS := -lcheck -pthread -lcheck_pic -pthread -lrt -lm -lsubunit

TEST_SOURCE = $(shell find $(TSTDIR) $(SRCDIR) -type f ! -name main.c -name *.c)
SOURCE := $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS_TEST := $(patsubst $(SRCDIR)/%.cpp $(TSTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SOURCE:.c=.o))
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCE:.c=.o))

main: main_make clean_src
tests: tests_make clean_src clean_tst


tests_make: $(OBJECTS_TEST)
	@mkdir -p $(@D)
	@$(CC) -o test $(OBJECTS_TEST) $(FLAGS)
	./test

main_make: $(OBJECTS)
	@mkdir -p $(@D)
	@$(CC) -o tp1 $(OBJECTS) $(FLAGS)

clean_src:
	@rm $(SRCDIR)/*.o

clean_tst:
	@rm $(TSTDIR)/*.o


# tests: check_check_main.o check_list.o check_team.o list.o team.o
# 	$(CC) check_check_main.o check_list.o check_team.o list.o team.o -o test $(FLAGS)
# 	rm *.o
# 	./test

# check_team.o: $(TSTDIR)/check_team.c
# 	$(CC) -c $(TSTDIR)/check_team.c

# check_check_main.o: $(TSTDIR)/check_check_main.c
# 	$(CC) -c $(TSTDIR)/check_check_main.c

# check_list.o: $(TSTDIR)/check_list.c
# 	$(CC) -c $(TSTDIR)/check_list.c

# list.o: $(SRCDIR)/list.c
# 	$(CC) -c $(SRCDIR)/list.c

# team.o: $(SRCDIR)/team.c
# 	$(CC) -c $(SRCDIR)/team.c