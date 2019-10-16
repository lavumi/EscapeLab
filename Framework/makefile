CC = g++


SRCDIR1 = ./Character
SRCDIR2 = ./Input
SRCDIR3 = ./Map
SRCDIR4 = ./Render
SRCDIR5 = ./UserInterface

VPATH = $(SRCDIR1) $(SRCDIR2) $(SRCDIR3) $(SRCDIR4) $(SRCDIR5) 

TARGET = frameworks

SRCS = $(foreach dir, .. $(SRCDIR1) $(SRCDIR2) $(SRCDIR3) $(SRCDIR4) $(SRCDIR5) , $(wildcard $(dir)/*.cpp))
SRCS := $(notdir $(SRCS))

OBJS = $(SRCS:.c = .o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET)
	mv $(TARGET) ../

%o:%c
	$(CC) -c $< -o $@

clean:
	-rm -rf $(OBJS)
	-rm -f ../$(TARGET)

depend: $(SRCS)
	$(CC) -M $(CFLAGS) $^ > $@