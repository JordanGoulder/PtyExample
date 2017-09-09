TARGET=mypty

SRCS=mypty.c hexdump.c

OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
