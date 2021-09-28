NAME		= philo

HEADER_DIR	= includes/
HEADERS		= philo.h

SRC_DIR		= source/
SRC		= main.c utils_1.c list.c logger.c forks.c list_el.c log.c params.c philosopher_action.c philosopher_create.c time.c utils_2.c

OBJ_DIR		= objects/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FLAGS		= -Werror -Wall -Wextra

all	: $(OBJ_DIR) $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
	gcc -o $@ $^ -pthread

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)$(HEADERS)
	gcc $(FLAGS) -I$(HEADER_DIR) -c $< -o $@ 

clean	:
	rm -rf $(OBJ_DIR)

fclean	: clean
	rm $(NAME)

re	: fclean all

.PHONY	: all clean fclean re
