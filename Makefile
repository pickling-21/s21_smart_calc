CC=gcc 
CFLAGS=-std=c11 -Wall -g

TARGET ?= hof
SRC_DIRS ?= ./

SRCS := $(shell find $(SRC_DIRS) -name '*.c' )
OBJS := $(addsuffix .o,$(basename $(SRCS)))


all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)


