CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
SRCS = main.c core/core.c scheduler/scheduler.c memory/memory.c fs/fs.c device/device.c shell/shell.c
OBJS = $(SRCS:.c=.o)
TARGET = kernelsim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)
