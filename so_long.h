/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likiffel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:12:06 by likiffel          #+#    #+#             */
/*   Updated: 2024/04/25 03:14:44 by likiffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
//renlever avant push
#include <stdio.h>
#include "mlx/mlx.h"
#include "mlx/mlx_opengl.h"
#include "gnl/get_next_line.h"
#include "gnl/get_next_line.c"
#include "gnl/get_next_line_utils.c"

struct s_data
{
    void    *img;
    char    *addresse;
    int     bit_par_pixel;
    int     line_length;
    int     endian;    
};

struct	s_var
{
	void	*mlx;
	void	*mlx_win;
  void *img;
  struct s_point *points;
  
};

struct s_tab 
{
    char **tab_bis;
};

struct s_len
{
    int line_len;
    int actual_line_len;
    int line_nb;
    char *name_map;
};

struct s_excolpos
{
    int colectbles;
    int exite;
    int starting_block; 
    int i;
    char *gnl;
    int get_collectibles;
};

 struct  s_size_bis
  {
    int           x;
    int           y;
  };
  struct  s_point
  {
    int           x;
    int           y;
    int nbr_collect_fill;
    int nbr_collect_ramaser;
    int nbr_exit_fill;
    int i;
    char *gnl;
    int xbis;
    int ybis;
    char **tab_bis_bis;
    struct s_var *vars;
    struct s_tab *tabs;
    struct s_size_bis *size;
    struct s_len *lines;
    int moves;
  };

 
  
struct s_position 
{
    int x;
    int y;
};

struct s_global {
    struct s_var *vars;
    struct s_point *points;
    
};













#endif
