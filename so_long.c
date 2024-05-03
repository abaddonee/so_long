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

/*struct s_data
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
};*/



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
//-----------------------verifictation de la map----------------------------------------

// ferme la fenetre quand esc est apuiyyer
int	ft_close(int keycode, struct s_var *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit(0);
    }
    
    return (0);
}
//ferme la fenetre quand la croix rouge est apuyyer
int cross_close(struct s_var *vars)
{
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    exit(0);
    return(0);
}



//ouvre le fichier avec la map.ber
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
// lit toute la map avec gnl
struct s_len ft_reading(int fd)
{
    char *gnl;
    struct s_len length;

    length.line_nb = 0;
    gnl=malloc(1024 * sizeof(char *));
    if(gnl == NULL)
        exit(EXIT_FAILURE);
    while (1)
    {
        gnl = get_next_line(fd);
        printf("%s", gnl);
        if (gnl == NULL)
            break;
        length.line_nb++;
    }
    free(gnl);
    close(fd);
    return (length);
}
// verifie si la map est rectangulaire 
struct s_len ft_rectangular(int fd)
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
    if (length.line_len == length.line_nb)
    {
        perror("map non comforme");
        exit(EXIT_FAILURE);
    }
    free(gnl);
    return(length);
}
// compte le nombre d'un cahr donnee
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
// verifier que toute les ligne sont de la meme longueure
void  ft_same_len(int fd, struct s_len length)
{
    char *gnl;

    length.actual_line_len = 0;
    gnl=malloc(1024 * sizeof(char *));
    if(gnl == NULL)
        exit(EXIT_FAILURE);
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
            perror("\nligne incomplete");
            exit(EXIT_FAILURE);
        }
    }
    free(gnl);
    close(fd);
}



//verifie si la ligne du haut est uniquement faite de 1



void ft_wall_up(int fd, struct s_len lines)
{
    char *up_line;

    fd = ft_opening();
    up_line=malloc(1024 * sizeof(char *));
    if (up_line == NULL)
        exit(EXIT_FAILURE);
    up_line = get_next_line(fd);
    if(up_line == NULL)
        exit(EXIT_FAILURE);
    if ((ft_strlen(up_line) -1 )!= ft_nb_of_c(up_line, '1'))
    {
       perror("intrue trouver");
       exit(EXIT_FAILURE);
    }
    free(up_line);
}

//verifie si la ligne du  bas est uniquement faite de 1

void ft_wall_down(int fd, struct s_len lines)
{
    char *down_line;
    int yesyoucan;
    int x;
    
    x = 1;
    yesyoucan = 0;
    down_line=malloc(1024 * sizeof(char *)); 
    if (down_line == NULL)
        exit(EXIT_FAILURE);
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
       perror("intrue trouveeeee");
       exit(EXIT_FAILURE);
    }
    free(down_line);
    close(fd);
}
   
   
    // verifier si il y a un 1 a la premiere et derniere position de chaque ligne

void ft_closed_wall(int fd, struct s_len length)
{
    ft_opening();
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
        if (gnl[0] != '1')
        {
            perror("first one probleme");
            exit(EXIT_FAILURE);
        }
        if (gnl[last_pos] != '1')
        {
            perror("last one probleme");
            exit(EXIT_FAILURE);
        }        
    }
    close(fd);
    

}

// verifier le nombre de collectible(au moin 1) , de sortie (1) et de depars (1)

void ft_ex_col_pos(int fd ,struct s_len length)
{
    ft_opening();
    struct s_excolpos vars;
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
    }  
    if (vars.exite != 1 || vars.starting_block != 1)
    {
            perror("trop / pas assez de sortie ou de pos de depart");
            exit(EXIT_FAILURE);
    }
    if (vars.colectbles == 0)
    {
            perror("pas de collectible :(");
            exit(EXIT_FAILURE);
    }
}

//---Backtracking pour verifier que le joueur peut recuperer les collectible et sortir-----

struct s_len ft_double_array(int fd, struct s_len lines)
{
    int i;

    i = 0;
    //printf("\n %d", lines.line_nb);
    lines.tabs.le_array = malloc(1024 * sizeof (char *));
    if(lines.tabs.le_array == NULL)
    {
        perror("memory probleme");
        exit(EXIT_FAILURE);
    }
     while (1)
    {
        lines.tabs.le_array[i]= get_next_line(fd);

        if(i == lines.line_nb - 1)
            break;
        i++;
    }
    close(fd);
    printf("le array %c", lines.tabs.le_array[3][1]);
    //printf("%d \n ", lines.line_len);
    return(lines);

}

// je dois trouver le p (valeur a garder) memeset d'un tableau similaire a le array



void ft_move_throuth_cllomns(int dir_coolomns[4])
{
    dir_coolomns[0] = 0;
    dir_coolomns[1] = 0;
    dir_coolomns[2] = -1;
    dir_coolomns[3] = 1;
}

void ft_move_throuth_lines(int dir_lines[4])
{
    dir_lines[0] = -1; 
    dir_lines[1] = 1;
    dir_lines[2] = 0;
    dir_lines[3] = 0;
}

int ft_searching_col_and_exit(struct s_move move, struct s_len lines, int nouv_colonne, int nouv_lines, int nouveau_table[lines.line_nb][lines.line_len])
{
    printf("%s", lines.tabs.le_array[3]);
    if(ft_can_or_not(move, lines, nouv_colonne, nouv_lines, nouveau_table))
    {
        if (lines.tabs.le_array[nouv_lines][nouv_colonne] == 'C')
        {
            move.statitik.get_collectibles++;
            lines.tabs.le_array[nouv_lines][nouv_colonne] = '0';
        }
        if (lines.tabs.le_array[nouv_lines][nouv_colonne] == 'E' || lines.tabs.le_array[nouv_lines][nouv_colonne] == '0')
        {
           if (ft_can_play(move, lines, nouv_colonne, nouv_lines, nouveau_table))
           {
             return(1);
           }
        }
    }
    return(0);
}


int ft_can_play(struct s_move moving, struct s_len lines, int colonne, int lignes, int nouveau_table[lines.line_nb][lines.line_len])
{

    ft_move_throuth_cllomns(moving.dir_coolomns);
    ft_move_throuth_lines(moving.dir_lines);
    int i;
    int nouv_colonne;
    int nouv_lines;
    int result;

    i = 0;
    nouveau_table[lignes][colonne] = 1;
    if (lines.tabs.le_array[lignes][colonne] == 'E')
    {
        return(1);
    }
    while(i < 4)
    {
        nouv_colonne = colonne + moving.dir_coolomns[i];
        nouv_lines = lignes + moving.dir_lines[i];
        result = ft_searching_col_and_exit(moving, lines, nouv_colonne, nouv_lines, nouveau_table);
        if(result)
        {
            return(1);
        }
        i++;
    }
    return(0);
}


void ft_error_handle(struct s_len lines, struct s_move move, int colonne, int lignes, int nouveau_table[lines.line_nb][lines.line_len])
{
    move.statitik.get_collectibles = 0;
    if(ft_can_play(move, lines, colonne, lignes, nouveau_table))
    {
        perror("exit et collectible are reachable");
    }
    else
    {
        perror("exit and collectible are not reachable");   
    } 
}
void ft_find_le_p(struct s_len lines, struct s_move move)
{
    int ligne;
    int colonne;
    int i;
    int j;
    int nouveau_table[lines.line_nb][lines.line_len];

    i = 0;
    while(i < lines.line_nb)
    {
        j = 0;
        while(j < lines.line_len)
        {
            if(lines.tabs.le_array[i][j] == 'P') 
            {
                ligne = i;
                colonne = j;
                break;
            }
            j++;
        }
        i++;
    }
    ft_memset(nouveau_table, 0, sizeof(nouveau_table));
    ft_error_handle(lines, move, colonne, ligne, nouveau_table);

} 

int ft_can_or_not(struct s_move move, struct s_len lines, int nouv_colonne, int nouv_lines,int nouveau_table[lines.line_nb][lines.line_len])
{
    int is_libre;
    int not_visited;

    is_libre = lines.tabs.le_array[nouv_lines][nouv_colonne] != '1';
    not_visited = !nouveau_table[nouv_lines][nouv_colonne];

    return(is_libre && not_visited);
}










void ft_verify_playability(struct s_len lines, struct s_move move)
{
    int fd;
    fd = ft_opening();
    ft_double_array(fd, lines);
    //ft_find_le_p(lines, move);
    //ft_can_play(move, lines);




}


// faire en sorte que apres le backtracking les colectible et exit soit toujours present.



// fonction principale qui execute toute les autre fonction

void ft_verify_map()
{
    struct s_len lines;
    struct s_patrack arraying;
    struct s_move move;
    int fd;

    fd = ft_opening();
    lines = ft_reading(fd);
    lines = ft_rectangular(fd);
    ft_same_len(fd, lines);
    ft_wall_up(fd, lines);
    ft_wall_down(fd, lines);
    ft_closed_wall(fd, lines);
    ft_ex_col_pos(fd, lines);
   // ft_verify_playability(lines, move);
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