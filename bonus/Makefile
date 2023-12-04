CC = cc
FLAGS = -Werror -Wextra -Wall #-fsanitize=address -g 
SRCS =  casting_rays.c casting_rays_helper.c free.c cub3d.c draw.c errors.c get_pixel.c info_player.c key_mlx.c map.c parsing.c rendering_walls.c utils.c utils_helper.c
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
	$(CC) $(FLAGS) $< -c

clean :
	rm -f $(OBJS)
	make -C ./lib/libft clean

fclean : clean
	rm -f $(NAME)
	rm -f $(MLX42)
	make -C ./lib/libft fclean
re : fclean all

MLX :
	git clone https://github.com/codam-coding-college/MLX42.git ./lib/MLX42