/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likiffel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:14:58 by likiffel          #+#    #+#             */
/*   Updated: 2024/04/25 03:15:45 by likiffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

struct s_len
{
    int line_len;
    int actual_line_len;
    int line_nb;
};


int	ft_close(int keycode, struct s_var *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit(0);
    }
    
    return (0);
}

int cross_close(struct s_var *vars)
{
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    exit(0);
    return(0);
}




int    ft_opening()
{
    int fd;
    char *name_map;
    
    name_map = "map_test.ber";
    fd = open(name_map, O_RDONLY);
    if(fd == -1)
    {
        perror("la map n'existe pas");
        exit(EXIT_FAILURE);
    }
    return (fd);
}
void ft_reading(int fd)
{
    char *gnl;
    struct s_len length;

    length.line_nb = 0;
    gnl=malloc(1024 * sizeof(char *));
    if(gnl == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        gnl = get_next_line(fd);
        if (gnl == NULL)
            break;
        printf("%s", gnl);
        length.line_nb++;
    }
    printf("\n nombre de ligne %d", length.line_nb);
    free(gnl);
    close(fd);
}
void ft_rectangular(int fd)
{
    struct s_len length;
    char *gnl;
    length.line_len = 0;   
    ft_opening();
    gnl=malloc(1024 * sizeof(char *));
    if (gnl == NULL)
        exit(EXIT_FAILURE);
    gnl = get_next_line(fd);
    if (gnl == NULL)
    {
        perror("map vide");
        exit(EXIT_FAILURE);
    }
    length.line_len = ft_strlen(gnl);
    length.line_len -= 1;   
    printf("\n nombres de caractere par ligne %d", length.line_len);
    if (length.line_len == length.line_nb)
    {
        perror("map non comforme");
        exit(EXIT_FAILURE);
    }
    printf("\n map rectangulaire");
    free(gnl);
}
void ft_same_len(int fd)
{
    struct s_len length;
    char *gnl;
    //int actual_line_len;

    length.actual_line_len = 0;
    gnl=malloc(1024 * sizeof(char *));
    if(gnl == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        gnl = get_next_line(fd);
        if(gnl == NULL)
            break;
        length.actual_line_len = ft_strlen(gnl) - 1;
        printf("gnl %s\n", gnl);
        printf("1rst line len = %d\n actual line len = %d\n", length.line_len , length.actual_line_len);
        if(length.line_len != length.actual_line_len)
        {
            //printf("1rst line len = %d\n actual line len = %d\n", length.line_len , actual_line_len);
            perror("\nligne incomplete");
            exit(EXIT_FAILURE);
        }
    }
    free(gnl);
    close(fd);
}
int 	ft_nb_of_c(const char *s, int c)
{
	int	i;
    int nb_of_one;

    nb_of_one = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			nb_of_one++;
		i++;
	}
	return (nb_of_one);
}

void ft_wall_updown(int fd)
{
    char *up_line;
    char *down_line;
    ft_opening();
    up_line=malloc(1024 * sizeof(char *));
    down_line=malloc(1024 * sizeof(char *)); 
    up_line = get_next_line(fd);
    printf("%d", ft_nb_of_c(up_line, '1'));
    if ((ft_strlen(up_line) -1 )!= ft_nb_of_c(up_line, '1'))
    {
       printf("%d", ft_nb_of_c(up_line, '1'));
       perror("intrue trouver");
       exit(EXIT_FAILURE);
    }
    while (1)
    {
        down_line = get_next_line(fd);
        if(down_line == NULL)
            break;
    }
    if ((ft_strlen(down_line) -1) != ft_nb_of_c(down_line, '1'))
    {
       perror("intrue trouveeeee");
       exit(EXIT_FAILURE);
    }
    free(up_line);
    free(down_line);
    printf("ligne du bas et du haut complettes");
}

void ft_verify_map()
{
    int fd;

    fd = ft_opening();
    ft_reading(fd);
    ft_rectangular(fd);
    ft_same_len(fd);
    //ft_wall_updown(fd);
    close(fd);
}



int main()
{
	struct s_var vars;
    struct s_data img; 

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1280, 720, "so_long");
    img.img = mlx_new_image(vars.mlx, 1280, 720);

    img.addresse = mlx_get_data_addr(img.img, &img.bit_par_pixel, &img.line_length, &img.endian);


    ft_verify_map();
    mlx_hook(vars.mlx_win, 2, 0, ft_close, &vars);
    mlx_hook(vars.mlx_win, 17, 0, cross_close, &vars);

	mlx_loop(vars.mlx);


}