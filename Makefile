NAME = pipex
NAME_BONUS = pipex_bonus
SRC = main.c utils_pipex.c
SRC_BONUS = main_bonus.c utils_pipex_bonus.c comand_setup_bonus.c here_doc_bonus.c
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

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	@rm -f $(OBJDIR)/*.o
	@rmdir $(OBJDIR) 2>/dev/null || true

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
