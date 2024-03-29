/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:27:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/05 22:46:39 by mbousbaa         ###   ########.fr       */
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
# define MINI_MAP 0.09

typedef struct s_angle
{
	bool	r_anglefacingdown;
	bool	r_anglefacingup;
	bool	r_anglefacingleft;
	bool	r_anglefacingright;
}	t_angle_facing;

typedef struct s_wall3d
{
	double			*rays_angle;
	double			*small_distance;
	bool			*x_vertical;
	t_angle_facing	*a_f;
}	t_wall3d;

typedef struct s_player
{
	double	x;
	double	y;
	double	radius;
	int		direction;
	int		move_up_down;
	int		move_right_or_left;
	double	retactionangle;
	double	speedmv;
	double	retactionsspeed;
	double	fovue_angle;
	double	num_arys;
}	t_plr;

typedef struct s_textue
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_png;

typedef struct s_map
{
	t_plr		*plr;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_wall3d	*wall3d;
	t_png		*txt;
	int			xwindows_width;
	int			ywindows_height;
	int			size_wall_y_x;
	int			*width_map;
	int			height_map;
	int			map_fd;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	char		map_buff[BUFSIZ];
	char		**map_s;
	int			init_player_x;
	int			init_player_y;
	int			map_idx;
}	t_map;

//parsing.c
t_map		*read_map(char *file);
int			process_type_ids(t_map *map);
void		init_type_ids(t_map *map, char *type);
int			process_map(t_map *map);
int			check_line(char **map, char *line, int c);

// map.c
int			check_map_elements(t_map *map, char **str, char *valid_elements);
int			check_texture_file(char **type_id);

// errors.c
void		error_(char *custom_error, char *file_name);
void		free_2d_array(char **var);
int			check_color_formula(char **color_line);
void		trim_type_ids(t_map *map);

/*//============================exv=============================\\*/

//cub3d.c
void		start_cub3d(t_map *map);
void		helper_start_cub3d(t_map *map);
void		find_tab_change_it_to_sp(char **map);
char		**fix_map(char **map);

//casting_rays,c // check done //
double		hm_px_bw_pyr_and_wall(t_map *map, double rayangle, int i);
void		cast_rays(t_map *map);
//casting_rays_helper.c // done
double		find_y_horztouch(t_map *map, double rayangle, t_angle_facing *a_f);
double		find_x_verticletouch(t_map *map, double rayangle,
				t_angle_facing *a_f);
//renderinng_walls.c // done
uint32_t	get_color(t_map *map, int i, int y);
void		rendering_wall_3d(t_map *map);

// // utils.c // done
double		make_angle_postive(double angle);
double		calculate_distance(double x1, double y1, double x2, double y2);
void		angle_facing(t_angle_facing *mongol, double rayangle);
void		clear_windows(t_map *map);
void		init_mlx(t_map *map);

// utils_helper.c 
void		error_mlx(void);
int			strlen_map_big_width_and_height(char **p, char c);
void		strlen_wight_pointer(t_map *map);

//info_player.c
void		info_player_helper(t_map *m);
void		info_player(t_plr *p, t_map *m);

//free.c // done
void		free_all(t_map *map);
void		count_and_check(char *types, char l, int *ret);
void		check_map_newlines(char *map_buff);

// get_pixel.c
uint32_t	get_east_pixel_color(t_map *map, int x, int y);
uint32_t	get_west_pixel_color(t_map *map, int x, int y);
uint32_t	get_south_pixel_color(t_map *map, int x, int y);
uint32_t	get_north_pixel_color(t_map *map, int x, int y);

//draw.c // done
void		put_px(t_map *map, int x, int y, uint32_t color);
void		draw_mini_map(t_map *map);
void		draw_line_direction(t_map *map, double ray_angle, double line_px);
void		draw_player(t_map *map, mlx_image_t *img);
void		draw_wall_3d(t_map *map, int startx, int starty,
				double wall_height);

//key_mlx.c 
bool		movestp_not_into_wall(t_map *map, double movestp, double M);
void		update_key(void *tmp);
#endif
