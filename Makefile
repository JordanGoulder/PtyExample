TARGET	= pty-example

SRCS	= main.c hexdump.c pty.c timed_read.c

OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
