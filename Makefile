CC  :=gcc
CFLAGS  :=-g -O0 -Wall -Wextra -std=c17 -MMD -MP
TARGET  :=shell

SRCS  :=$(wildcard *.c)
HDRS  :=$(wildcard *.h)
OBJS  :=$(SRCS:.c=.o)
DEPS  :=$(SRCS:.c=.d)

#Default rule
all:$(TARGET)

#Link object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

#compile source file into object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
    
#clean up generated files

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

#Include automatically generated header dependencies
-include $(DEPS)

.PHONY: all clean

