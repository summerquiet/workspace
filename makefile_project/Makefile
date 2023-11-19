# 指令编译器和选项
CC = g++
CFLAGS = -Wall lcm
LDLIBS = -llcm

# 目标文件
TARGET = lcm_test
SRCS = lcm_test.cpp

INC = -I./exlcm 

OBJS = $(SRCS:.c=.o)

$(TARGET):$(OBJS)
#	@echo TARGET:$@
#	@echo OBJECTS:$^
	$(CC) -o $@ $^ $(LDLIBS)

clean:
	rm -rf $(TARGET) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
