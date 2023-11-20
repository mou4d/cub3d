CC = cc
FLAGS = -fsanitize=address -g #-Werror -Wextra -Wall 
SRCS = parsing.c map.c cub3d.c utils.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I./lib/MLX42/include/MLX42
LIBFT = ./lib/libft/libft.a
MLX42 = ./lib/MLX42/build/libmlx42.a
NAME = cub3d

GLFW = $(shell brew --prefix glfw)/lib

all : $(NAME)

$(NAME) : $(LIBFT) $(MLX42) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX42) $(INCLUDES) -L $(GLFW)  -lglfw -pthread -lm -o $(NAME)

$(LIBFT) :
	make -C ./lib/libft

$(MLX42) :
	cmake -S ./lib/MLX42 -B ./lib/MLX42/build
	cmake --build ./lib/MLX42/build -j4

%.o : %.c
	$(CC) $(FLAGS) $< -g -c

clean :
	rm -f $(OBJS)
	make -C ./lib/libft clean

fclean : clean
	rm -f $(NAME)
	make -C ./lib/libft fclean

re : fclean all
