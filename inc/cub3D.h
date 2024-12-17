/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:48:42 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:58:24 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/libmlx/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 640
# define HEIGHT 480

# define RAY_ERROR 0.000001f

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
	NoEventMask = 0L,
	KeyPressMask = 1L << 0
};

# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define ESC_KEY 53
# define KEY_Q 12

# define ANGLE_STEP 0.02f
# define LINEAR_STEP 0.3f
# define FOV 1.047f // Field Of Vision 60 degrees
# define MAP_SCALE 4

typedef enum e_err
{
	OK = 0,
	ERR = 1
}				t_err;

typedef struct s_ray
{
	float		delta_x;
	float		delta_y;
	int			step_x;
	int			step_y;
	float		horizontal_x;
	float		horizontal_y;
	float		vertical_x;
	float		vertical_y;
	float		vertical_distance;
	float		horizontal_distance;
	float		vertical_fraction;
	float		horizontal_fraction;
}				t_ray;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	char		*path;
	int			count;
	int			width;
	int			height;
}				t_img;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			count;
	char		*rgb_str;
	char		**rgb_str_arr;

}				t_color;

typedef struct s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_color		f;
	t_color		c;

}				t_texture;

typedef struct s_player
{
	int			x;
	int			y;
	char		direction;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		**map_h;
	t_texture	texture;
	char		*path;
	int			row;
	int			map_len;
	int			map_width;
	int			map_height;
	int			map_start;
	int			map_end;
	int			player_count;
	t_player	player;
}				t_map;

typedef struct s_image
{
	void		*east;
	void		*north;
	void		*south;
	void		*west;
}				t_image;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct s_game
{
	t_map		map;
	t_map		pure_map;
	t_map		map_last;
	t_image		image;
	t_mlx		mlx;
	t_img		img_w;
	float		pos_x;
	float		pos_y;
	float		angle_view;
	t_img		txt[4];
	int			txt_idx;
	float		txt_w;
	int			color_ceiling;
	int			color_floor;
	t_map		last_map;
}				t_game;

// cub3D.c
void			initialize_and_run_game(t_game *game);
t_err			run_map_checks(t_game *game, char *path);
t_game			*initialize_game(void);
int				main(int ac, char **av);

// control_map_items.c
t_err			map_control_set_player(t_map *map, int x, int y,
					char direction);
t_err			map_control_centrals_items(t_map *map, char *line, int x);
int				map_width(t_map *map);
t_err			control_player(t_map *map);

// control_map.c
t_err			validate_map_line(t_map *map, char *line, int row);
t_err			map_control_centrals(t_map *map);
t_err			validate_and_set_end(t_map *map);
t_err			map_control_boundaries(t_map *map);
t_err			map_control(t_map *map);

// control_map2.c
t_err			is_map_valid(char **map, char p);
t_err			validate_map_start(char **map, int *start_x, int *start_y,
					char p);
t_err			validate_map(char **map, char p);
t_err			validate_map_cell(t_map *map, int i, int j, char p);
t_err			map_control_part(t_map *map);

// dispose_helper.c
void			strr_arr_dispose(char **arr);
void			dispose_general(t_game *game);
void			dispose_maps(t_game *game);

// dispose.c
void			dispose_rgb_arrays(t_game *game);
void			dispose_texture_paths(t_game *game);
void			dispose_textures(t_game *game);
void			dispose(t_game *game);

// draw_and_ray_casting.c
void			line(t_game *game, int w, float dist);
void			ray_casting(t_game *game);
void			draw_ceiling_and_floor(t_game *game);

// err.c
t_err			perr(const char *func, const char *msg);

// game_utils.c
int				destroy_exit(t_game *game);

// helper.c
void			flood_fill(char **map, int x, int y, char p);
bool			is_one_or_space(char c);
bool			all_chars_are(char *str);

// init_texture_color.c
t_err			control_texture_color(t_color *color);
t_err			is_invalid_color(char **rgb_str_arr);
t_err			check_texture_color(char *line, t_map *map);

// init_texture.c
void			load_textures(t_game *game);
void			load_textures_addresses(t_game *game);
t_err			texture_init(t_map *map, char *path);

// init.c
t_err			map_path_control(char *path);
t_err			process_line(t_map *map, int fd, int *indices, bool *eof);
t_err			prepare_map_init_part2(t_map *map, int fd);
t_err			prepare_map_init_part1(t_map *map, char *path, int *fd);
t_err			prepare_map_init(t_map *map, char *path);

// key_hook.c
float			calculate_ray_distance(t_game *game, float v);
void			move(t_game *game, int direction);
int				key(int keycode, t_game *game);

// main_helper.c
void			set_player(t_game *game);
char			**pure_map(char **map, int height);
void			initialize_pure_map(t_game *game);

// map_h_fill.c
t_err			map_h_fill(t_map *map);
t_err			allocate_map_h(t_map *map);
t_err			map_h(t_map *map);

// ray_utils.c
float			ray_check_horizontal(t_game *game, t_ray *r);
float			ray_check_vertical(t_game *game, t_ray *r);
float			compute_ray_steps(t_game *game, t_ray *r);
float			initialize_ray(t_game *game, float v, t_ray *r);

// raycasting.c
int				sign(float f);
float			save_color(t_game *game, float dist, int color_idx, float w);
void			ray_next_step_calculation(t_game *game, t_ray *r);

// set_texture_color.c
void			set_texture_color_f(t_texture *texture);
void			set_texture_color_c(t_texture *texture);

// set_texture.c
t_err			control_texture_dir(t_texture *texture);
t_err			set_texture(char *line, t_map *map);
void			set_texture_for_direction(char *line, t_map *map,
					t_img *texture);
void			set_texture_dir(char *line, t_map *map);

// start_game.c
void			draw(t_game *game);
void			init_xpm(t_game *game);
void			set_angle_view(t_game *game);
void			set_position(t_game *game);
void			start_game(t_game *game);

// str_utils.c
bool			strevery(int (*func)(int c), const char *str);
bool			is_empty_line(char *line);
char			*ft_strtrim_a(const char *s1, const char *set);

// str_utils2.c
char			*copy_word(const char *s, char c, int *j);
char			**allocate_words(const char *s, char c, int word_count);
char			**ft_split_a(const char *s, char c);

#endif
