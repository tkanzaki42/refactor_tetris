TARGET		= tetris
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I./includes
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/tetris.c \
				$(SRC_DIR)/has_to_update.c \
				$(SRC_DIR)/set_timeout.c \
				$(SRC_DIR)/create_random_shape.c \
				$(SRC_DIR)/check_puttable.c \
				$(SRC_DIR)/delete_shape.c \
				$(SRC_DIR)/print_table.c \
				$(SRC_DIR)/rotate_shape.c
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
