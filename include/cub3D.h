#ifndef CUB3D_H
# define CUB3D_H

# include "struct_cub3d.h"

/*
 ** Parsing
*/

int		sorting_map(char *map_map, t_param *param);
int		ft_atoi_cub3d(char *str, int i, t_param *param);
char	**malloc_tab(t_param *param);
int		find_str_beginning(char *s1, char *s2);
int		find_str_end(char *s1, char *s2);
int		conversion_rgb_to_hexa(t_colour colour);

int		manage_errors(int argc, char **argv, t_param *param);
void	print_error(t_param *param, char *str);
int		file_is_cub(char *str, t_param *param);
t_param	initialize_structure(t_param *param, char *argv);
int		parsing_map(char *str, t_param *param);
int		move_to_map(char *str);

int		calculate_nb_chains(char *str);
int		ft_biggest_line_len(char *str);
int		read_map(int fd, char *str, char *map, t_param *param);
int		read_next_line(char **tab_param, char **line, int fd,
		t_param *param);
int		check_map(char **map, int nb_lines, int max_length, t_param *param);
char	*only_map(char *str, t_param *param);
char	**save_map(char **str, int nb_lines, int length);
char	**creation_table_map(char **str, t_param *param);
void	free_str(char **str, t_param *param);
int		check_end_walls(char *str, int length, t_param *param);
char	*check_space_in_map(char *str);
int		check_symbols(char *str, t_param *param);
int		check_void_line_map(char *str, t_param *param);
int		check_holes_walls(char **map, int nb_lines, int length, t_param *param);
int		check_first_last_string_map(char *str, t_param *param);

int		check_all_para(t_param *param, char **tab_param);
int		p_orientation_position(char *map, t_param *param, int position, int i);
int		manage_perso(char **map, t_param *param);
int		manage_param(char *str, t_param *param);
int		parameters_map(char *str, t_param *param);
int		only_params(char *str, t_param *param);
int		check_address_parameters(char *str, t_param *param);

char	*save_param_numbers(char *str, char *res, int i);
int		resolution_param(char *str, t_param *param);
char	*save_address_param(char *str, t_param *param);
int		colour_params_ceiling(char *str, t_param *param);
int		colour_params_floor(char *str, t_param *param);
void	free_address_params(t_param *params);
int		ft_number_sprites(char *str);
t_param	initialize(int argc, char **argv);

/*
 ** Raycasting
*/

void	raycasting(t_data *data, t_ray *ray);
void	calculation_for_raycasting(t_data *data, t_ray *ray);
void	display_raycasting(t_data *data, t_ray *ray, int x);
void	wall_collision(t_data *data, t_ray *ray);
void	initialize_data_for_raycasting(t_ray *ray);
void	init(t_data *data);
void	initialisation_orientation(t_param *param, t_ray *ray);
void	orientation_north_south(t_param *param, t_ray *ray);

/*
 ** Texture
*/

void	ft_textures(t_data *data);
void	get_textures(t_data *data);
void	ft_get_addr_textures(t_data *data);
void	draw_texture_walls(t_data *data, int pos_x);
void	free_textures(t_data *data);
void	direction_texture(t_data *data);
void	get_sprites2_img(t_data *data);
void	initialize_before_drawing(t_data *data);

/*
 ** Sprites
*/

void	get_sprites_info(t_data *data);
void	ft_sprites(t_data *data);
void	order_sprites(t_data *data, int nb_sprites);
void	sort_sprites(t_data *data);
void	initialize_data_for_sprites(t_data *data, t_sprite *sprite);
void	calculate_sprites(t_data *data, t_sprite *sprite);
void	draw_sprites(t_data *data, int stripe, int text_x, t_sprite *sprite);
void	allocate_memory_for_sprites(t_data *data);
void	free_sprites(t_data *data);
int			initialize_sprite(int i, int j, t_sprite *sprite, char type);
void	get_image_by_sprite(t_data *data, t_sprite *sprite);
void 	draw_sprites_2(t_data *data, t_sprite *sprite, int img_c, int sprite_c);


/*
 ** Minilibx
*/

int		draw_minimap(t_data *data);
int		draw_square(float i, float j, t_data *data, int color);
int		draw_line(t_data *data, t_rect rect);
int		draw_ceiling(int beginning, int end, int pos_x, t_data *data);
int		draw_floor(int beginning, int end, int pos_x, t_data *data);
int		draw(t_data *data);
int		draw_rect(t_img *img, t_rect rect);
void	img_pix_put(t_img *img, int x, int y, int color);
int		press_key(int key, t_data *data);
int		release_key(int key, t_data *data);
int		initialize_mlx(t_data *data);
int		move_perso(t_data *data);
int		close_window(int key, t_data *data);
int		launch_hook(t_data *data);
int		initialize_mlx(t_data *data);
void	initialize_parameters_for_mlx(t_data *data);
int		create_window(t_data *data);
void	rotate_camera_left(t_data *data);
void	rotate_camera_right(t_data *data);
int		close_game(t_data *data);
void	forward_backward_movement(int nega, t_perso *perso);
void	left_right_movement(int nega, t_perso *perso);
void	general_case(int nega, t_perso *perso);

/*
 ** Save_image
*/

int		create_image(t_data *data);
void	create_file_header(int fd, t_data *data, int *nbr_bits);
void	create_info_header(int fd, t_data *data, int *nbr_bits);
void	create_pixel_on_bmp(int fd, t_data *data, int *nbr_bits);
int		close_bmp_file(int fd, int nbr_bits, t_data *data);

/*
 ** Bonus
*/

int		health_management(t_data *data);
void	get_health_level(t_data *data);
void	draw_life_bar(t_data *data, int i);
void	convert_health_level(t_data *data);
void	put_health_bar_on_image(t_data *data, int i, int y, int z);
void	get_ceiling_textures(t_data *data);
void	get_floor_textures(t_data *data);
void	draw_texture_ceiling(t_data *data, int pos_x);
void	draw_texture_floor(t_data *data, int pos_x);
void	free_floor_bonus(t_data *data);
void	free_textures_bonus(t_data *data);
void	check_sprite2(char *str, t_param *param);
int 	play_music(t_data *data);
int 	init_music(t_data *data);
double	shadow_texture(double distance, char addr);


#endif
