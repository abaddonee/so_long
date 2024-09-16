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
      //  printf("%s", gnl);
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



void ft_wall_up(int fd)
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
    size_t yesyoucan;
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

void cleenbuffer(int fd)
{
    char *gnl;
    ft_opening();
    gnl = malloc(1024 * sizeof(char *));
    if(gnl == NULL)
        exit(EXIT_FAILURE);
    while (gnl != NULL)
    {
        gnl = get_next_line(fd);
        free(gnl);
    }
    close(fd);
}

void extra_char(int fd)
{
    ft_opening();
    char *gnl = NULL;  // Initialiser à NULL
    int i;

    while (1)  // Lire chaque ligne
    {
        gnl = get_next_line(fd);
        if (gnl == NULL)
            break;
        i = 0;  // Réinitialiser `i` à chaque nouvelle ligne
        while (gnl[i] != '\0' && gnl[i] != '\n')  // Lire chaque caractère de la ligne
        {
            if (gnl[i] != '1' && gnl[i] != '0' && gnl[i] != 'C' && gnl[i] != 'E' && gnl[i] != 'P')
            {
                perror("caractère non autorisé");
                free(gnl);  // Libérer la mémoire avant de quitter
                exit(EXIT_FAILURE);
            }
            i++;
        }
        free(gnl);  // Libérer la mémoire après chaque ligne
    }
    close(fd);  // Fermer le fichier
}

// verifier le nombre de collectible(au moin 1) , de sortie (1) et de depars (1)

struct s_excolpos ft_ex_col_pos(int fd ,struct s_len length, struct s_excolpos vars)
{
    ft_opening();
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
    if (vars.exite != 1 || vars.starting_block != 1 || vars.colectbles == 0)
    {
            perror("trop / pas assez de sortie ou de pos de depart");
            exit(EXIT_FAILURE);
    }
    close(fd);
    return vars;
}




// trouver la position de p pour le floodfilldelamort 

struct s_point pos_de_p(int fd, struct s_len length)
{
    ft_opening();
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
    close(fd);
    return points; 
}
// mettre la taille du tableau dans s_size_bis

struct s_size_bis ft_size_bis(struct s_len length, struct s_size_bis size)
{
    size.x = length.line_len;
    size.y = length.line_nb;
    return size;
}

// cree un double tableau pour le floodfilldelamort
struct s_tab ft_double_array(int fd, struct s_tab tabs, struct s_len lines) 
{
    ft_opening();
    int i;
    char *gnl;

    i = 0;
    tabs.tab_bis = malloc(1024 * sizeof (char *));
    if(tabs.tab_bis == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while (gnl != NULL && i < lines.line_nb)
    {
        gnl = get_next_line(fd);
        printf("\n %s", gnl);
        tabs.tab_bis[i] = gnl;
        i++;
    }
    close(fd);
    return(tabs);
}



//flood fill

 void fill(struct s_tab tabs, struct s_size_bis size, struct s_point *point, int row, int col)
{
    if (row < 0 || col < 0 || row >= size.y || col >= size.x)
        return ;
    if (tabs.tab_bis[row][col] == 'F')
        return ;
    if (tabs.tab_bis[row][col] == '1')
        return ;
    if (tabs.tab_bis[row][col] == 'C') 
    {
        point -> nbr_collect_fill++;
        tabs.tab_bis[row][col] = 'F';
    }
    if (tabs.tab_bis[row][col] == 'E')
    {
        point -> nbr_exit_fill++;
        tabs.tab_bis[row][col] = 'F';
    }
    if (tabs.tab_bis[row][col] == '0') {
        tabs.tab_bis[row][col] = 'F';
    }
    fill(tabs, size, point, row - 1, col);  
    fill(tabs, size, point, row + 1, col); 
    fill(tabs, size, point, row, col - 1);  
    fill(tabs, size, point, row, col + 1);  
}

struct s_point flood_fill(struct s_tab tabs, struct s_size_bis size, struct s_point starter)
{
    starter.nbr_collect_fill = 0;
    starter.nbr_exit_fill = 0;
    starter.xbis = starter.x;
    starter.ybis = starter.y;
    fill(tabs, size, &starter, starter.y, starter.x); 
    return starter;
}

// Vérification si le nombre de collectables et de sorties est correct
void verify_fill(struct s_point point, struct s_excolpos vars)
{
    printf ("nbr collectible de base : %d\n", vars.colectbles);
    printf("nbr_collect_fill: %d\n", point.nbr_collect_fill);
    printf("nbr_exit_fill: %d\n", point.nbr_exit_fill);
    if (point.nbr_collect_fill != vars.colectbles || point.nbr_exit_fill != 1)
    {
        perror("map non jouable");
        exit(EXIT_FAILURE);
    }
}


// fonction principale qui execute toute les autre fonction

void ft_verify_map()
{
    struct s_len lines;
    struct s_excolpos vars;
    struct s_tab tabs;
    struct s_point points;
    struct s_size_bis size;
    int fd;

    fd = ft_opening();
    lines = ft_reading(fd);
    lines = ft_rectangular(fd);
    ft_same_len(fd, lines);
    ft_wall_up(fd);
    ft_wall_down(fd, lines);
    ft_closed_wall(fd, lines);
    cleenbuffer(fd);
    extra_char(fd);
    vars = ft_ex_col_pos(fd, lines, vars);
    points = pos_de_p(fd, lines);
    size = ft_size_bis(lines, size);
    cleenbuffer(fd);
    tabs = ft_double_array(fd, tabs, lines);
    points = flood_fill(tabs, size, points);
    //printf("size x = %d, size y = %d\n", size.x, size.y);
    verify_fill(points, vars);  
    close(fd);
}

//-------------------------------------------------------------------------------------------------------------------------   
// mouvement du personnage 


struct s_point ft_doubless_array(int fd, struct s_point tabs, struct s_len lines) 
{
    ft_opening();
    int i = 0;
    char *gnl;

    tabs.tab_bis_bis = malloc(1024 * sizeof(char *)); // Allocation en fonction du nombre de lignes
    if (tabs.tab_bis_bis == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while (gnl != NULL && i < lines.line_nb)
    {
        gnl = get_next_line(fd);
        printf("\n %s", gnl);
        tabs.tab_bis_bis[i] = gnl;
        i++;
    }
    close(fd);
    return tabs;
}
// Fonction de gestion des événements clavier
int key_handler(int keycode, struct s_point player_position, struct s_size_bis size, char **map)
{
    int new_x = player_position.xbis;
    int new_y = player_position.ybis;

    if (keycode == 126)        // Touche 'haut'
        new_y--;
    else if (keycode == 125)   // Touche 'bas'
        new_y++;
    else if (keycode == 123)   // Touche 'gauche'
        new_x--;
    else if (keycode == 124)   // Touche 'droite'
        new_x++; 

    // Vérifier les limites et les obstacles ('1')
    if (new_x < 0 || new_y < 0 || new_x >= size.x || new_y >= size.y || map[new_y][new_x] == '1')
        return -1;

    // Mettre à jour la position du joueur
    player_position.xbis = new_x;
    player_position.ybis = new_y;

    printf("x = %d, y = %d\n", player_position.xbis, player_position.ybis);
    return 0;
}

// Fonction de déplacement du joueur
int ft_move(void *param) {
    struct s_move_data *data = (struct s_move_data *)param;

    // Access the members of data
    mlx_hook(data->vars->mlx_win, 2, 0, key_handler, data->player_position);

    return 0;  // Since mlx_loop_hook expects an int return value
}

void ft_game()
{
    struct s_var vars;
    struct s_point player_position;
    struct s_data img;
    struct s_len lines;
    struct s_size_bis size;
    int fd;

    // Ouvrir le fichier et lire les dimensions de la carte
    fd = ft_opening();
    lines = ft_reading(fd);
    lines = ft_rectangular(fd);
      // Lire la carte et obtenir les dimensions
      // Définir le nombre de lignes (à partir de `ft_reading`)

    // Charger la carte dans un tableau 2D
    cleenbuffer(fd);
    player_position = ft_doubless_array(fd, player_position, lines);

    // Définir la taille de la carte
    size.x = lines.line_len;
    size.y = lines.line_nb;
    printf("Taille de la carte : %d x %d\n", size.x, size.y);

    // Créer la fenêtre et initialiser la bibliothèque graphique
    
}

void ft_windowss(struct s_var vars, struct s_data img)
{   
    vars.mlx = mlx_init();
    vars.mlx_win = mlx_new_window(vars.mlx, 1280, 720, "so_long");
   // img.img = mlx_new_image(vars.mlx, 1280, 720);
    //img.addresse = mlx_get_data_addr(img.img, &img.bit_par_pixel, &img.line_length, &img.endian);
    
    mlx_loop(vars.mlx);
}

void ft_gameloop() {
    struct s_var vars;
    struct s_data img;
    struct s_point player_position;
    struct s_size_bis size;
    char **map;
    map = player_position.tab_bis_bis;

    // Create and initialize the move data structure
    struct s_move_data move_data = {&vars, &player_position, size, map};

    ft_windowss(vars, img);
   
    // Hook the move function to the loop
    mlx_loop_hook(vars.mlx_win, ft_move, &move_data);
    
    // Other hooks
    mlx_loop_hook(vars.mlx_win, ft_close, &vars);
    mlx_loop_hook(vars.mlx_win, cross_close, &vars);
    
    // Start the graphics loop
    
    mlx_loop(vars.mlx);
}



int main()
{
    ft_verify_map();
   
    ft_game();
    ft_gameloop();
   
    return 0;
}




  
























