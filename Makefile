TARGET = bf
SRC    = main.c
FLAGS  = -I. -Wall

default: bf

$(TARGET): $(SRC)
	gcc $(FLAGS) $^ -o $@

clean:
	$(RM) $(TARGET)

.PHONY: default clean
