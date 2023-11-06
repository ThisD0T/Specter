OBJS = main.cpp ymd.cpp

CC = g++

OBJ_NAME = specter

all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME)
