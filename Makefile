NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address -static-libasan 
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
INC_FLAGS = -I $(INC_DIR)

SRC_FILES = main.c \
			parse.c \
			init.c \
			dinner.c \
			forks.c \
			cleanup.c \
			time.c \
			utils.c \
			safe_functions.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(NAME) : $(OBJS)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(INC_FLAGS)
	$(MSG1)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Reset
Color_Off='\033[0m'       # Text Reset
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
ICyan='\033[0;96m'        # Cyan

MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG4 = @echo ${IGreen}"Libft Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	$(MSG2)

fclean: clean
	@rm -f $(NAME)
	$(MSG3)

re: fclean all
	

.PHONY: all clean fclean re