/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:27:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/10 18:16:46 by mbousbaa         ###   ########.fr       */
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
}	t_map;

//parsing.c
int	process_type_ids(t_map *map);
#endif
