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

struct s_patrack
{
    char **le_array;
};

struct s_len
{
    struct s_patrack tabs;
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



struct s_move
{
    struct s_excolpos statitik;
    int dir_coolomns[4];
    int dir_lines[4];
};

void	*ft_memset(void *b, int c, size_t len);
int	ft_close(int keycode, struct s_var *vars);
int cross_close(struct s_var *vars);
int    ft_opening();
struct s_len ft_reading(int fd);
struct s_len ft_rectangular(int fd);
int 	ft_nb_of_c(const char *s, int c);
void  ft_same_len(int fd, struct s_len length);
void ft_wall_up(int fd, struct s_len lines);
void ft_wall_down(int fd, struct s_len lines);
void ft_closed_wall(int fd, struct s_len length);
void ft_ex_col_pos(int fd ,struct s_len length);
struct s_len ft_double_array(int fd, struct s_len lines);
void ft_move_throuth_cllomns(int dir_coolomns[4]);
void ft_move_throuth_lines(int dir_lines[4]);
int ft_searching_col_and_exit(struct s_move move, struct s_len lines, int nouv_colonne, int nouv_lines, int nouveau_table[lines.line_nb][lines.line_len]);
int ft_can_play(struct s_move moving, struct s_len lines, int colonne, int lignes, int nouveau_table[lines.line_nb][lines.line_len]);
void ft_error_handle(struct s_len lines, struct s_move move, int colonne, int lignes, int nouveau_table[lines.line_nb][lines.line_len]);
void ft_find_le_p(struct s_len lines, struct s_move move);
int ft_can_or_not(struct s_move move, struct s_len lines, int nouv_colonne, int nouv_lines,int nouveau_table[lines.line_nb][lines.line_len]);
void ft_verify_playability(struct s_len lines, struct s_move move);
void ft_verify_map();







#endif
