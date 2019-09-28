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
tests: tests_make clean_src clean_tst tests_run


tests_make: $(OBJECTS_TEST)
	@mkdir -p $(@D)
	@$(CC) -o test $(OBJECTS_TEST) $(FLAGS)
	

main_make: $(OBJECTS)
	@mkdir -p $(@D)
	@$(CC) -o tp1 $(OBJECTS)

tests_run:
	./test

clean_src:
	@rm $(SRCDIR)/*.o

clean_tst:
	@rm $(TSTDIR)/*.o