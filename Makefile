# Standard
NAME				= pipex

# Directories
LIBFT				= ./libft/libft.a
INC					= inc/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
RM					= rm -f

# Source Files
SRCS_DIR		=	Mandatory/pipex.c \
					Mandatory/exec.c \
					Mandatory/utils.c \
					libft/libft.a

SRCS_BONUS		=	Bonus/pipex_bonus.c \
					Bonus/exec_bonus.c \
					Bonus/utils_bonus.c \
					libft/libft.a

# Build rules

$(NAME): 			
					@make all -C ./libft
					gcc $(CFLAGS) $(SRCS_DIR) -o $(NAME)

all: 				$(NAME)

fclean: 			clean
					@$(RM) $(NAME)
					@make clean -C ./libft

clean:
					@$(RM) $(NAME)
					@make clean -C ./libft

re: 				fclean all