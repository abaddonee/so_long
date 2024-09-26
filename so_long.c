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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_ptr;
	unsigned char	b_value;

	b_ptr = b;
	b_value = (unsigned char)c;
	while (len != '\0')
	{
		*b_ptr++ = b_value;
		len--;
	}
	return (b);
}

void ft_malloc_error(char * gnl)
{
    perror("Error\n malloc failed");
    free(gnl);
    exit(EXIT_FAILURE);
}

void ft_malloc_error_tab(char **tab, int size_tab)
{
    int i;

    i = 0;
    if (tab)
    {
        while (i < size_tab)
        {
            free(tab[i]);
            i++;
        }
        free(tab);
    }
    perror("Error\n malloc failed");
    exit(EXIT_FAILURE);
}


void ft_check_input(int argc, char **argv, struct s_len *lines)
{
    if (argc != 2)
    {
        perror("Error\n nombre d'argument incorrect");
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
    {
        perror("Error\n extension incorrect");
        exit(EXIT_FAILURE);
    }
    lines->name_map = argv[1];
    lines->name_map = argv[1];
    
    lines->name_map = argv[1];    
    
}

int    ft_opening(struct s_len lines)  
{
    int fd;
    char *name_map;
    
    name_map = lines.name_map;
    fd = open(name_map, O_RDONLY);
    if(fd == -1)
    {
        perror("Error\n la map n'existe pas");
        exit(EXIT_FAILURE);
    }
    return (fd);
}

void ft_reading(int fd, struct s_len *length)
{
    char *gnl;

    length->line_nb = 0;
    while (1)
    {
        gnl = get_next_line(fd);  
        if (gnl == NULL)
            break;  
        length->line_nb++;  

        free(gnl); 
    }
    free(gnl); 
    close(fd);  
}

 void ft_free_tab(char **tab, int size_tab) 
{
    int i;

    i = 0;
    if (tab) 
    {
        while( i < size_tab) 
        {
            free(tab[i]);
            i++;
        }
        free(tab);
    }
}

void ft_rectangular(int fd, struct s_len *lines)
{
    char *gnl;

    lines->line_len = 0;   
    ft_opening(*lines);
    gnl = get_next_line(fd);
    if (gnl == NULL)
    {
        perror("Error\n map vide");
        exit(EXIT_FAILURE);
    }
    lines->line_len = ft_strlen(gnl);
    lines->line_len -= 1;   
    if (lines->line_len == lines->line_nb)
    {
        perror("Error\n map non comforme");
        free(gnl);
        exit(EXIT_FAILURE);
    }
    free(gnl);
}
size_t ft_nb_of_c(const char *s, int c)
{
	int	i;
    size_t nb_of_one;

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
void  ft_same_len(int fd, struct s_len length)
{
    char *gnl;

    length.actual_line_len = 0;
    while(1)
    {
        gnl = get_next_line(fd);
        if(gnl == NULL)
            break;
        length.actual_line_len = ft_strlen(gnl);
        if(ft_nb_of_c(gnl, '\n'))
            length.actual_line_len--;
        if(length.line_len != length.actual_line_len)
        {
            perror("Error\nligne incomplete");
            free(gnl);
            exit(EXIT_FAILURE);
        }
    }
    free(gnl);
    close(fd);
}






void ft_wall_up(int fd, struct s_len lines)
{
    char *up_line;

    fd = ft_opening(lines);
    up_line = get_next_line(fd);
    if(up_line == NULL)
    {
        perror("Error\nmap vide");
        free(up_line);
        exit(EXIT_FAILURE);
    }
    if ((ft_strlen(up_line) -1 )!= ft_nb_of_c(up_line, '1'))
    {
        perror("Error\nintrue trouver");
        free(up_line);
        exit(EXIT_FAILURE);
    }
    free(up_line);
}


void ft_wall_down(int fd, struct s_len lines)
{
    char *down_line;
    size_t yesyoucan;
    int x;
    
    x = 1;
    yesyoucan = 0;
    while (1)
    {
        down_line = get_next_line(fd);
        if(x++ == lines.line_nb - 1)
            break;
    }
    yesyoucan = ft_strlen(down_line);
    if(ft_nb_of_c(down_line, '\n'))
            yesyoucan--;
    if ( yesyoucan != ft_nb_of_c(down_line, '1'))
    {
       perror("Error\n intrue trouveeeee");
       free(down_line);
       exit(EXIT_FAILURE);
    }
    free(down_line);
    close(fd);
}
   
   

void ft_closed_wall(int fd, struct s_len length)
{
    ft_opening(length);
    int last_pos;
    char *gnl;
    int i;

    i = 0;
    last_pos = length.line_len;
    last_pos--;
    while (1)
    {
        gnl = get_next_line(fd);
        if(i++ == length.line_nb - 1)
            break;
        if (gnl[0] != '1' || gnl[last_pos] != '1')
        {
            perror("Error\n probleme de mur");
            free(gnl);
            exit(EXIT_FAILURE);
        }   
    }
    free(gnl);
    close(fd);
}

void cleenbuffer(int fd, struct s_len length)
{
    char *gnl;
    ft_opening(length);
    while (1)
    {
        gnl = get_next_line(fd);
        if(gnl == NULL)
            break;
    }
    free(gnl);
    close(fd);
}

void extra_char(int fd, struct s_len length)
{
    ft_opening(length);
    char *gnl = NULL;  
    int i;

    while (1)  
    {
        gnl = get_next_line(fd);
        if (gnl == NULL)
            break;
        i = 0;  
        while (gnl[i] != '\0' && gnl[i] != '\n')  
        {
            if (gnl[i] != '1' && gnl[i] != '0' && gnl[i] != 'C' && gnl[i] != 'E' && gnl[i] != 'P')
            {
                perror("Error\n caractère non autorisé");
                free(gnl);  
                exit(EXIT_FAILURE);
            }
            i++;
        }
        free(gnl);  
    }
    free(gnl);  
    close(fd);  
}


struct s_excolpos ft_ex_col_pos(int fd ,struct s_len length, struct s_excolpos vars)
{
    ft_opening(length);
    vars.i = 0;
    vars.colectbles = 0;
    vars.exite = 0;
    vars.starting_block = 0;
    while (1)
    {
        vars.gnl = get_next_line(fd);
        if(vars.i++ == length.line_nb - 1)
            break;
        vars.colectbles += ft_nb_of_c(vars.gnl, 'C');
        vars.exite += ft_nb_of_c(vars.gnl, 'E');
        vars.starting_block += ft_nb_of_c(vars.gnl, 'P');
        free(vars.gnl);
    }  
    if (vars.exite != 1 || vars.starting_block != 1 || vars.colectbles == 0)
    {
            perror("Error\n trop / pas assez de sortie ou de pos de depart");
            free(vars.gnl);
            exit(EXIT_FAILURE);
    }
    free(vars.gnl);
    close(fd);
    return vars;
}





struct s_point pos_de_p(int fd, struct s_len length)
{
    ft_opening(length);
    struct s_point points;

    points.x = 0;  
    points.y = 0;
    while (points.y < length.line_nb) 
    {
        points.gnl = get_next_line(fd);
        if (points.gnl == NULL) 
            break;     
        points.x= 0;
        while (points.gnl[points.x] != '\0' && points.gnl[points.x] != '\n') 
        {
            if (points.gnl[points.x] == 'P')  
            {
                return points;
            }
            points.x++;
        }
        free(points.gnl);
        points.y++;  
    }
    free(points.gnl);
    close(fd);
    return points; 
}

struct s_size_bis ft_size_bis(struct s_len length, struct s_size_bis size)
{
    size.x = length.line_len;
    size.y = length.line_nb;
    return size;
}

struct s_tab ft_double_array(int fd, struct s_tab tabs, struct s_len lines) 
{
    ft_opening(lines);
    int i;
    char *gnl;

    i = 0;
    tabs.tab_bis = malloc(1024 * sizeof (char *));
    if(tabs.tab_bis == NULL)
        ft_malloc_error_tab(tabs.tab_bis, 1024);
    ft_memset(tabs.tab_bis, 0, 1024 * sizeof(char *));
    while (1)
    {
        gnl = get_next_line(fd);
        tabs.tab_bis[i] = gnl;
        i++;
        if (gnl == NULL || i == lines.line_nb)
            break;
    }
    close(fd);
    return(tabs);
}




 void fill(struct s_tab tabs, struct s_size_bis size, struct s_point *point)
{
    int row  = point->ybis;
    int col = point->xbis;
    if (row < 0 || col < 0 || row >= size.y || col >= size.x || tabs.tab_bis[row][col] == 'F' || tabs.tab_bis[row][col] == '1')
        return ;
    if (tabs.tab_bis[row][col] == 'C') 
        point -> nbr_collect_fill++;
    if (tabs.tab_bis[row][col] == 'E')
        point -> nbr_exit_fill++;
    if (tabs.tab_bis[row][col] == 'C' || tabs.tab_bis[row][col] == 'E' || tabs.tab_bis[row][col] == '0')
        tabs.tab_bis[row][col] = 'F';
    point->ybis = row - 1; 
    fill(tabs, size, point);  
    point->ybis = row + 1; 
    fill(tabs, size, point); 
    point->ybis = row; 
    point->xbis = col - 1; 
    fill(tabs, size, point);  
    point->xbis = col + 1; 
    fill(tabs, size, point); 
    point->xbis = col; 
}

struct s_point flood_fill(struct s_tab tabs, struct s_size_bis size, struct s_point starter)
{
    starter.nbr_collect_fill = 0;
    starter.nbr_exit_fill = 0;
    starter.xbis = starter.x;
    starter.ybis = starter.y;
    fill(tabs, size, &starter); 
    return starter;
}

void verify_fill(struct s_point point, struct s_excolpos vars, struct s_tab *tab)
{

    if (point.nbr_collect_fill != vars.colectbles || point.nbr_exit_fill != 1)
    {
        perror("Error\n map non jouable");
        ft_free_tab(tab->tab_bis, 1024);
        exit(EXIT_FAILURE);
    }
}



void ft_verify_map(struct s_point *points, struct s_len *lines, struct s_tab *tabs)
{
    struct s_excolpos vars = {0};
   
    struct s_size_bis size = {0};
    int fd;

    fd = ft_opening(*lines);
    ft_reading(fd, lines);
    ft_rectangular(fd, lines);
    ft_same_len(fd, *lines);
    ft_wall_up(fd, *lines);
    ft_wall_down(fd, *lines);
    ft_closed_wall(fd, *lines);
    cleenbuffer(fd, *lines);
    extra_char(fd, *lines);
    vars = ft_ex_col_pos(fd, *lines, vars);
    *points = pos_de_p(fd, *lines);
    size = ft_size_bis(*lines, size);
    cleenbuffer(fd, *lines);
    *tabs = ft_double_array(fd, *tabs, *lines);
    *points = flood_fill(*tabs, size, *points);
    verify_fill(*points, vars, tabs); 
    ft_free_tab(tabs->tab_bis, 1024);
    close(fd);
}




struct s_point ft_doubless_array(int fd, struct s_point tabs, struct s_len lines) 
{
    ft_opening(lines);
    int i = 0;
    char *gnl;

    tabs.tab_bis_bis = malloc(1024 * sizeof(char *)); 
    if (tabs.tab_bis_bis == NULL)
       ft_malloc_error_tab(tabs.tab_bis_bis, 1024);
    ft_memset(tabs.tab_bis_bis, 0, 1024 * sizeof(char *));
    while (1)
    {
        gnl = get_next_line(fd);
        tabs.tab_bis_bis[i] = gnl;
        i++;
        if(gnl == NULL || i == lines.line_nb + 1)
            break;
    }
    free(gnl);
    close(fd);
    return tabs;
}



void ft_data_map(struct s_point *player_position, struct s_len *lines, struct s_size_bis *size) //, struct s_var *vars
{
    
    
    int fd;

    fd = ft_opening(*lines);
    ft_reading(fd, lines);
    ft_rectangular(fd, lines);

    cleenbuffer(fd, *lines);
    *player_position = ft_doubless_array(fd, *player_position, *lines);

  

    size->x = lines->line_len;
    size->y = lines->line_nb;
    player_position->size = size;
    close(fd);
}

void ft_windowss(struct s_var *vars, struct s_point *player_position)
{   
    int x;
    int y;
    x = player_position->size->x * 40;
    y = player_position->size->y * 40;
    vars->mlx = mlx_init();
     
    vars->mlx_win = mlx_new_window(vars->mlx, x, y, "so_long");
    if (vars->mlx_win == NULL)
    {
        perror("Error\n fenetre non creer");
        ft_free_tab(player_position->tab_bis_bis, 1024);
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        free(vars->mlx);
        exit(EXIT_FAILURE);
    }
}





int ft_close(int keycode, struct s_point *player_position)
{
    if(keycode == 53)
    {
        ft_free_tab(player_position->tab_bis_bis, 1024);
        if (player_position->vars->mlx_win)
            mlx_destroy_window(player_position->vars->mlx, player_position->vars->mlx_win);
        if (player_position->vars->mlx)
            free(player_position->vars->mlx);
        if (player_position->vars->img)
            free(player_position->vars->img);
        exit(0);
        return 0;
    }
    return 0;
}
int ft_C(int x, int y, struct s_point *player_position)
{ 
        player_position->tab_bis_bis[y][x] = '0';
        player_position->nbr_collect_ramaser++;
        return 0;
}
int ft_E(struct s_point *player_position)
{
    if(player_position->nbr_collect_ramaser == player_position->nbr_collect_fill)
    {
        ft_close(53, player_position);
    }
    return -1;
}
void ft_put_sol(struct s_var *vars, int x, int y, struct s_point *player_position)
{
    int img_haut;
    int img_larg;
    char *sol;

    img_haut = 40;
    img_larg = 40;
    sol = "./sol.xpm";

    vars->img = mlx_xpm_file_to_image(vars->mlx, sol, &img_haut, &img_larg);
    if(vars->img == NULL)
    {
        perror("Error\n image non trouver");
        ft_free_tab(player_position->tab_bis_bis, 1024);
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, x, y);
    mlx_destroy_image(vars->mlx, vars->img);
    
}

void ft_sol_to_windows(struct s_var *vars, struct s_point *player_position)
{
    int x;
    int y;
    int i;
    int j;

    i = 0;
    x = 0;
    y = 0;
    while (i < player_position->size->y)
    {
        x = 0;
        j = 0;
        while (j < player_position->size->x)
        {
            ft_put_sol(vars, x, y, player_position);
            x += 40;
            j++;
        }
        y += 40;
        i++;
       
    }
}

void ft_put_wall(struct s_var *vars, int x, int y, struct s_point *player_position)
{
    int img_haut;
    int img_larg;
    char *wall;

    img_haut = 40;
    img_larg = 40;
    wall = "./wall.xpm";

    vars->img = mlx_xpm_file_to_image(vars->mlx, wall, &img_haut, &img_larg);
    if(vars->img == NULL)
    {
        perror("Error\n image non trouver");
        ft_free_tab(player_position->tab_bis_bis, 1024);
        free(vars->img);
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, x, y);
    mlx_destroy_image(vars->mlx, vars->img);
    
}

void ft_put_wall_to_windows(struct s_var *vars, struct s_point *player_position)
{
    int x;
    int y;
    int i;
    int j;

    i = 0;
    x = 0;
    y = 0;
    while (i < player_position->size->y)
    {
        x = 0;
        j = 0;
        while (j < player_position->size->x)
        {
            if(player_position->tab_bis_bis[i][j] == '1')
                ft_put_wall(vars, x, y, player_position);
            x += 40;
            j++;
        }
        y += 40;
        i++;
    }
}

void ft_put_collectible(struct s_var *vars, int x, int y, struct s_point *player_position)
{
    int img_haut;
    int img_larg;
    char *collectible;

    img_haut = 40;
    img_larg = 40;
    collectible = "./colect.xpm";

    vars->img = mlx_xpm_file_to_image(vars->mlx, collectible, &img_haut, &img_larg);
    if(vars->img == NULL)
    {
        perror("Error\n image non trouver");
        ft_free_tab(player_position->tab_bis_bis, 1024);
        free(vars->img);
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, x, y);
    mlx_destroy_image(vars->mlx, vars->img);
    
}

void ft_put_collectible_to_windows(struct s_var *vars, struct s_point *player_position)
{
    int x;
    int y;
    int i;
    int j;

    i = 0;
    x = 0;
    y = 0;
    while (i < player_position->size->y)
    {
        x = 0;
        j = 0;
        while (j < player_position->size->x)
        {
            if(player_position->tab_bis_bis[i][j] == 'C')
                ft_put_collectible(vars, x, y, player_position);
            x += 40;
            j++;
        }
        y += 40;
        i++;
    }
}

void ft_put_exit(struct s_var *vars, int x, int y, struct s_point *player_position)
{
    int img_haut;
    int img_larg;
    char *exite;

    img_haut = 40;
    img_larg = 40;
    exite = "./exit.xpm";

    vars->img= mlx_xpm_file_to_image(vars->mlx, exite, &img_haut, &img_larg);
    if(vars->img == NULL)
    {
        perror("Error\n image non trouver");
        ft_free_tab(player_position->tab_bis_bis, 1024);
        free(vars->img);
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, x, y);
    mlx_destroy_image(vars->mlx, vars->img);
    
}

void ft_put_exit_to_windows(struct s_var *vars, struct s_point *player_position)
{
    int x;
    int y;
    int i;
    int j;

    i = 0;
    x = 0;
    y = 0;
    while (i < player_position->size->y)
    {
        x = 0;
        j = 0;
        while (j < player_position->size->x)
        {
            if(player_position->tab_bis_bis[i][j] == 'E')
                ft_put_exit(vars, x, y, player_position);
            x += 40;
            j++;
        }
        y += 40;
        i++;
    }
}

void ft_put_player(struct s_var *vars, int x, int y, struct s_point *player_position)
{
    int img_haut;
    int img_larg;
    char *player;

    img_haut = 40;
    img_larg = 40;
    player = "./player.xpm";

    vars->img = mlx_xpm_file_to_image(vars->mlx, player, &img_haut, &img_larg);
    if(vars->img == NULL)
    {
        perror("Error\n image non trouver");
        ft_free_tab(player_position->tab_bis_bis, 1024);
        free(vars->img);
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, x, y);
    mlx_destroy_image(vars->mlx, vars->img);
    
}

void ft_put_player_to_windows(struct s_var *vars, struct s_point *player_position)
{
    int x;
    int y;
    int i;
    int j;

    i = 0;
    x = 0;
    y = 0;
    while (i < player_position->size->y)
    {
        x = 0;
        j = 0;
        while (j < player_position->size->x)
        {
            if(player_position->x == j && player_position->y == i)
                ft_put_player(vars, x, y, player_position);
            x += 40;
            j++;
        }
        y += 40;
        i++;
    }
}

void ft_replace_player_to_sol(struct s_var *vars, struct s_point *player_position)
{
    int x;
    int y;
    int i;
    int j;

    i = 0;
    x = 0;
    y = 0;
    while (i < player_position->size->y)
    {
        x = 0;
        j = 0;
        while (j < player_position->size->x)
        {
            if(player_position->x == j && player_position->y == i)
                ft_put_sol(vars, x, y, player_position);
            x += 40;
            j++;
        }
        y += 40;
        i++;
    }
}

int ft_verify_move(int x, int y, struct s_point *player_position)
{

    if (x < 0 || y < 0 || x >= player_position->size->x  || y >= player_position->size->y -1)
    {
        return -1;
    }

    if (player_position->tab_bis_bis[y][x] == '1')
    {
        return -1;
    }
    else if (player_position->tab_bis_bis[y][x] == 'C')
        return(ft_C(x, y, player_position));
    else if (player_position->tab_bis_bis[y][x] == 'E')
        return(ft_E(player_position));
    player_position->moves++;
    return 0;
}
void ft_up(int keycode, struct s_point *player_position)
{
    if (keycode == 126 || keycode == 13)
    {
        int temp_y = player_position->y - 1; 

        if(ft_verify_move(player_position->x, temp_y, player_position) == 0)
        {
            ft_put_sol(player_position->vars, player_position->x * 40, player_position->y * 40, player_position);
            player_position->y = temp_y;
            ft_put_player_to_windows(player_position->vars, player_position);

        }
    }
}
void ft_down(int keycode, struct s_point *player_position)
{
    if (keycode == 125 || keycode == 1)
    {
        int temp_y = player_position->y + 1;
        if(ft_verify_move(player_position->x, temp_y, player_position) == 0)
        {
            ft_put_sol(player_position->vars, player_position->x * 40, player_position->y * 40, player_position);
            player_position->y = temp_y;
            ft_put_player_to_windows(player_position->vars, player_position);
        }
    }
}
void ft_left(int keycode, struct s_point *player_position)
{
    if (keycode == 123 || keycode == 0)
    {
        int temp_x = player_position->x - 1;
        if(ft_verify_move(temp_x, player_position->y, player_position) == 0)
        {
            ft_put_sol(player_position->vars, player_position->x * 40, player_position->y * 40, player_position);
            player_position->x = temp_x;
            ft_put_player_to_windows(player_position->vars, player_position);

        }
    }
}
void ft_right(int keycode, struct s_point *player_position)
{
    if (keycode == 124 || keycode == 2)
    {
        int temp_x = player_position->x + 1;
        if(ft_verify_move(temp_x, player_position->y, player_position) == 0)
        {
            ft_put_sol(player_position->vars, player_position->x * 40, player_position->y * 40, player_position);
            player_position->x = temp_x;
            ft_put_player_to_windows(player_position->vars, player_position);

        }
    }
}

int key_handler(int keycode, struct s_point *player_position) // prblm je ne donne pas vars a key handler
{
    ft_down(keycode, player_position);
    ft_up(keycode, player_position);
    ft_left(keycode, player_position);
    ft_right(keycode, player_position);  
    if(keycode == 126 || keycode == 125 || keycode == 123 || keycode == 124 || keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
    {
        printf("Position du joueur : x = %d, y = %d\n", player_position->x, player_position->y);
    }
    return 0;
}





int cross_close(struct s_point *player_position)
{
    ft_free_tab(player_position->tab_bis_bis, 1024);
    if (player_position->vars->mlx_win)
        mlx_destroy_window(player_position->vars->mlx, player_position->vars->mlx_win);
    if (player_position->vars->mlx)
        free(player_position->vars->mlx);
    if(player_position->vars->img)
        free(player_position->vars->img);
    exit(0);
    return 0;
}

void ft_touche(struct s_point *player_position, struct s_var *vars)
{
    
   
    ft_windowss(vars, player_position);
    ft_sol_to_windows(vars, player_position);
    ft_put_wall_to_windows(vars, player_position);
    ft_put_collectible_to_windows(vars, player_position);
    ft_put_exit_to_windows(vars, player_position);
    ft_put_player_to_windows(vars, player_position);

    player_position->vars = vars;

    mlx_hook(vars->mlx_win, 17, 0, cross_close, player_position);
    mlx_key_hook(vars->mlx_win,ft_close, player_position);

    player_position->moves = 0;

    mlx_hook(vars->mlx_win, 2, 1L << 0, key_handler, player_position); 
    mlx_loop(vars->mlx);
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    free(vars->mlx);
}




int main(int argc, char **argv)
{
    struct s_tab tabs;
    struct s_point points;
    struct s_len lines;
    struct s_var vars;
    struct s_size_bis size;

    ft_check_input(argc, argv, &lines);
    ft_verify_map(&points, &lines, &tabs);


    ft_data_map(&points, &lines, &size);

    ft_touche(&points, &vars);
   
   
    return 0;
}


  























