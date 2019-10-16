CPP = g++


SRCDIR1 = ./Framework/Render
SRCDIR2 = ./Framework/Character
SRCDIR3 = ./Framework/Input
SRCDIR4 = ./Framework/Map
SRCDIR5 = ./Framework/UserInterface
SRCDIR6 = ./Framework
SRCDIR7 = ./Source
SRCDIR8 = ./Source/Character



LDFLAGS = -lncurses


SRCS = $(foreach dir, . .. $(SRCDIR8) $(SRCDIR1) $(SRCDIR2) $(SRCDIR3) $(SRCDIR4) $(SRCDIR5) $(SRCDIR6) $(SRCDIR7), $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

TARGET = EscapeLab

all : $(TARGET)
	$(CPP) -Wall -o $(TARGET) $(notdir $(OBJS)) $(LDFLAGS)

$(TARGET) :
	$(CPP) -std=c++11 -c  $(SRCS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
 