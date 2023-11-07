OBJS = main.cpp

CC = g++

OBJ_NAME = specter

FLAGS = -lncurses

all : $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(OBJ_NAME)
