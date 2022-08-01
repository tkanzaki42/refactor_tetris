tetris: srcs/tetris.c \
		srcs/hastoupdate.c \
		srcs/settimeout.c \
		srcs/cs.c \
		srcs/cp.c \
		srcs/ds.c \
		srcs/pt.c \
		srcs/rs.c
	gcc $^ -Iincludes -lncurses -o tetris
