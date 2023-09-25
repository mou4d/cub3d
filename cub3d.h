/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:27:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/25 18:48:16 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include "./lib/libft/libft.h"
# include "./lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
	char	*map_path;
	int		map_fd;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	char	*map_r;
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
#endif
