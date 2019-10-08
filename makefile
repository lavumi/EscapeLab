CC = g++
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = EscapeLab

all : $(TARGET)
	$(CC) -o $(TARGET) $(OBJS)

$(TARGET) :
	$(CC) -c $(SRCS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
