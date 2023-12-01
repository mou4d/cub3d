/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:27:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/01 22:19:14 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "./lib/libft/libft.h"
# include "./lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_angle
{
	bool 	r_anglefacingdown;
	bool	r_anglefacingup;
	bool	r_anglefacingleft;
	bool	r_anglefacingright;
}	t_angle_facing;

typedef struct  s_wall3d
{
	double	*rays_angle;
	double	*small_distance;
	bool *x_vertical;
	uint32_t color;
}	t_wall3d;


typedef struct s_player
{
	double x;
	double y;
	double radius;
	int direction;// turndirection if = 0 >> stable if -1 >> left if +1 to right
	int move_up_down;// walk if = 0 >> not walking if +1 >> to up if >> -1 to back
	int	move_right_or_left;
	double retactionangle;
	double speedmv;//move speed
	double retactionsSpeed;//retaction speed
	double	fovue_angle;
	double num_arys;
} t_plr;

typedef struct s_textue
{
	mlx_texture_t	*North;
	mlx_texture_t	*South;
	mlx_texture_t	*East;
	mlx_texture_t	*West;
}t_png;


typedef struct s_map
{
	t_plr		*plr;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_wall3d	*wall3d;
	t_png		*txt;
	int			Xwindows_width;
	int			Ywindows_height;
	int			size_wall_y_x;
	int			*width_map;
	int			height_map;
	char		*map_path;
	int			map_fd;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*F;
	char		*C;
	char		**map_s;
	int			init_player_x;
	int			init_player_y;
	int			map_idx;
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
void	draw_line_direction(t_map *map, double ray_angle, double line_px);

// errors.c
void	error_(char *custom_error, char *file_name);
void	free_2d_array(char **var);
int		check_texture_file(char **type_id); //to be moved to another file later
int		check_color_formula(char **color_line); // to be moved to another file later
void	trim_type_ids(t_map *map); // to be moved to another file later

#endif
