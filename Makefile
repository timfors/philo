NAME		= philo

HEADER_DIR	= includes/
HEADERS		= philo.h

SRC_DIR		= source/
SRC			= philosopher.c logger.c list.c main.c utils.c

OBJ_DIR		= objects/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FLAGS		= -Werror -Wall -Wextra

all	: $(OBJ_DIR) $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ_DIR) $(OBJ)
	gcc $(FLAGS) -o $@ $^ -I ./includes/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)$(HEADERS)
	gcc $(FLAGS) -c $< -o $@ -I ./includes/

clean	:
	rm -rf $(OBJ_DIR)

fclean	: clean
	rm $(NAME)

re	: fclean all

.PHONY	: all clean fclean re
