TARGET=mypty

SRCS=mypty.c

OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
