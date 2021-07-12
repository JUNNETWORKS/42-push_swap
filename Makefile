NAME := push_swap
CC := gcc
CFLAGS := -Werror -Wall -Wextra -g

LIBFT_PATH := libft
LIBFT_MAKE := $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB := -L./libft -lft

HEADER_FILES := push_swap.h
SRCS := main.c \
		dlist.c dlist2.c dlist3.c \
		operations.c \
		sort_stacks.c sort_le_3_elements.c sort_le_6_elements.c \
		sort_arr.c
OBJS := ${SRCS:.c=.o}
DEPS := ${SRCS:.c=.d}

all: ${NAME}

%.o: %.c
	# -MMD -MP -MF で依存ファイルリスト生成
	$(CC) $(CFLAGS)  -MMD -MP -MF $(<:.c=.d) -c $< -o $@

-include $(DEPS)
$(NAME): ${OBJS}
	$(LIBFT_MAKE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBFT_LIB)

clean:
	$(LIBFT_MAKE) clean
	${RM} ${OBJS}
	${RM} ${DEPS}

fclean: clean
	$(LIBFT_MAKE) fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
