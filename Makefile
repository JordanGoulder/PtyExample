TARGET	= mypty

SRCS	= mypty.c hexdump.c pty.c timed_read.c

OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
