#ifndef CUB3D_H
# define CUB3D_H

# include "struct_cub3D.h"

/*Parsing*/

int sorting_map(char *map_map, t_param *param);

int ft_atoi_cub3d(char *str, int i, t_param *param);
char     **malloc_tab(t_param *param);
int find_str_beginning(char *s1, char *s2);
int find_str_end(char *s1, char *s2);
int	conversion_RGB_to_hexa(t_colour colour);

int ft_is_string(char *s1, char *s2);
int manage_errors(int argc, char **argv, t_param *param);
void print_error(t_param *param, char *str);
int file_is_cub(char *str, t_param *param);
t_param initialize_structure(t_param *param, char *argv);
int parsing_map(char *str, t_param *param);
int move_to_map(char *str);

int calculate_nb_chains(char *str);
int ft_biggest_line_len(char *str);
int read_map(int fd, char *str, char *map, t_param *param);
int read_next_line(char **tab_map, char **tab_param, char **line, int fd, t_param *param);
int check_map(char **map, int nb_lines, int max_length, t_param *param);
char *only_map(char *str, t_param *param);
char **save_map(char **str, int nb_lines, int length);
char **creation_table_map(char **str, t_param *param);
int check_end_walls(char *str, int length, t_param *param);
char	*check_space_in_map(char *str);
int check_symbols(char *str, t_param *param);
int	check_void_line_map(char *str, t_param *param);
int check_holes_walls(char **map, int nb_lines, int length, t_param *param);
int check_first_last_string_map(char *str, t_param *param);

int check_all_para(t_param *param, char **tab_param);
int p_orientation_position(char *map, t_param *param, int position, int i);
int	manage_perso(char **map, t_param *param);
int manage_param(char *str, t_param *param);
int parameters_map(char *str, t_param *param);
int	only_params(char *str, t_param *param);
int check_address_parameters(char *str, t_param *param);

char *save_param_numbers(char *str, char *res, int i);
int resolution_param(char *str, t_param *param);
//void print_params(t_param *param);
char *save_address_param(char *str, t_param *param);
int colour_params_ceiling(char *str, t_param *param);
int colour_params_floor(char *str, t_param *param);
void free_address_params(t_param *params);

/*Raycasting*/

int		raycasting(t_data *data, t_ray *ray);
void 	init(t_data *data);
int		print_ray(t_ray *ray);
int		initialisation_orientation(t_param *param, t_ray *ray);
//void    display(int x, double haut, double bas, t_colour color, char *img_data, int res);
t_param	initialize(int argc, char **argv);
void	ft_textures(t_data *data);

/*DRAW3D*/


/*Minilibx*/

int draw_minimap(t_data *data);
int draw_square(float i, float j, t_data *data, int color);
int draw_line(t_data *data, t_rect rect);
int draw_column(int beginning, int end, int pos_x, t_data *data);
int draw_ceiling(int beginning, int end, int pos_x, t_data *data);
int draw_floor(int beginning, int end, int pos_x, t_data *data);
int draw(t_data *data);
int draw_rect(t_img *img, t_rect rect);
void img_pix_put(t_img *img, int x, int y, int color);
int click_close(t_data *data);
int press_key(int key, t_data *data);
int release_key(int key, t_data *data);
int	initialize_mlx(t_data *data);
int	move_perso(t_data *data);
int	close_window(int key, t_data *data);
int	launch_hook(t_data *data);
int	initialize_mlx(t_data *data);
int	create_window(t_data *data);

#endif
