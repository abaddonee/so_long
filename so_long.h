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

  struct  s_point
  {
    int           x;
    int           y;
    int nbr_collect_fill;
    int nbr_exit_fill;
    int i;
    char *gnl;
    int xbis;
    int ybis;
    char **tab_bis_bis;
  };

 
   struct  s_size_bis
  {
    int           x;
    int           y;
  };
struct s_position 
{
    int x;
    int y;
};

struct s_move_data {
    struct s_var *vars;
    struct s_point *player_position;
    struct s_size_bis size;
    char **map;
};



void	*ft_memset(void *b, int c, size_t len);
int	ft_close(int keycode, struct s_var *vars);
int cross_close(struct s_var *vars);
int    ft_opening();
struct s_len ft_reading(int fd);
struct s_len ft_rectangular(int fd);
size_t	ft_nb_of_c(const char *s, int c);
void  ft_same_len(int fd, struct s_len length);
void ft_wall_up(int fd);
void ft_wall_down(int fd, struct s_len lines);
void ft_closed_wall(int fd, struct s_len length);
struct s_excolpos ft_ex_col_pos(int fd ,struct s_len length, struct s_excolpos vars);
void ft_verify_map();








#endif
