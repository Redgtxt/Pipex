NAME = pipex
NAME_BONUS = pipex_bonus

# Source paths adjusted for mandatory and bonus folders
SRC = mandatory/main.c mandatory/utils_pipex.c
SRC_BONUS = bonus/main_bonus.c bonus/utils_pipex_bonus.c bonus/comand_setup_bonus.c bonus/here_doc_bonus.c

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

OBJDIR = ./obj
OBJS = $(SRC:%.c=$(OBJDIR)/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=$(OBJDIR)/%.o)

CC = cc
FLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

# Adjusted compilation rule to handle files in subdirectories
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/mandatory
	mkdir -p $(OBJDIR)/bonus

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus