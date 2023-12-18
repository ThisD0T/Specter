OBJS = main.cpp

CC = g++

OBJ_NAME = specter

FLAGS = -lncurses -lboost_serialization

all : $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(OBJ_NAME)
