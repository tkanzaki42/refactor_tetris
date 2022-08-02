TARGET		= tetris
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I./includes
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/game_body.c \
				$(SRC_DIR)/game_init.c \
				$(SRC_DIR)/key_input.c \
				$(SRC_DIR)/screen_print.c \
				$(SRC_DIR)/screen_update.c \
				$(SRC_DIR)/shape_check.c \
				$(SRC_DIR)/shape_create_delete.c \
				$(SRC_DIR)/shape_move_copy.c \
				$(SRC_DIR)/tetris.c
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
