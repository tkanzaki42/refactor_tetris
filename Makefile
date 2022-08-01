TARGET		= tetris
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I./includes
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/tetris.c \
				$(SRC_DIR)/hastoupdate.c \
				$(SRC_DIR)/settimeout.c \
				$(SRC_DIR)/cs.c \
				$(SRC_DIR)/cp.c \
				$(SRC_DIR)/ds.c \
				$(SRC_DIR)/pt.c \
				$(SRC_DIR)/rs.c
OBJS		= $(SRCS:.c=.o)
DBGFLAG		= -g -fsanitize=address

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -lncurses -o $@

.c.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: debug
debug:
	rm -f $(TARGET)
	$(CC) $(CFLAGS) $(DBGFLAG) $(SRCS) $(INCLUDE) -lncurses -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(TARGET)

.PHONY: re
re: fclean all
