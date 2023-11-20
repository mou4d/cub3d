/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:27:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/17 22:47:55 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "./lib/libft/libft.h"
# include "./lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_player
{
	double x;
	double y;
	double radius;
	int direction;// turndirection if = 0 >> stable if -1 >> left if +1 to right
	int move;// walk if = 0 >> not walking if +1 >> to up if >> -1 to back
	double retactionangle;
	double speedmv;//move speed
	double retactionsSpeed;//retaction speed
} t_plr;


typedef struct s_map
{
	t_plr	*plr;
	mlx_t	*mlx;
	mlx_image_t *img;
	int		Xwindows_width;
	int		Ywindows_height;
	int		width_map;
	int		height_map;
	char	*map_path;
	int		map_fd;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	char	**map_s;
	int		init_player_x;
	int		init_player_y;
}	t_map;

//parsing.c
t_map	*read_map(char *file);
int		process_type_ids(t_map *map);
void	init_type_ids(t_map *map, char *type);
int		process_map(t_map *map);

// map.c
int		check_top_border(t_map *map);
int		check_bottom_border(t_map *map);
int		check_side_borders (t_map *map);
int		check_map_elements(t_map *map, char **str, char *valid_elements);

// // utils.c
void	error_mlx(void);
void	init_mlx(t_map *map);
void	draw_player(t_map *map, mlx_image_t *img);
#endif
