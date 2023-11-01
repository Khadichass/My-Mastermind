CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
TARGET = my_mastermind
OBJ = my_mastermind.o 
SRC = my_mastermind.c 

all : $(TARGET)

$(TARGET) : $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ) 

$(OBJ) : $(SRC)
	gcc $(CFLAGS) -c $(SRC)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)