/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:33:02 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 16:11:05 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <ctype.h>
# include  <limits.h>
# include "MLX42.h"


# define WIDTH 1280
# define HEIGHT 720

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define PI 3.141593

typedef unsigned int	t_u_int;

typedef struct s_i_xy
{
	int	x;
	int	y;
}	t_i_xy;

typedef struct s_d_xy
{
	double	x;
	double	y;
}	t_d_xy;

typedef struct s_dist
{
	t_d_xy	side;
	t_d_xy	delta;
}	t_dist;

typedef struct s_tex
{
	int	x;
	int	y;
	int	id;
}	t_tex;

typedef struct s_player
{
	t_d_xy	pos;
	t_d_xy	dir;
	t_d_xy	plane;
}	t_player;

typedef struct s_line
{
	int	height;
	int	start;
	int	end;
}	t_line;

typedef struct s_ray
{
	t_d_xy	dir;
	double	cam_rate;
	double	perp_wall_dist;
	t_line	line;
	int		side;
}	t_ray;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*cub_img;
	mlx_texture_t	*tex[4];
	char			*tex_path[4];
	t_u_int			ceil;
	t_u_int			floor;
    char			**map;
	t_i_xy			map_size;
	t_player		player;
}	t_data;

int		ft_cub_init(t_data *data, int argc, char **argv);
int		ft_cub_loop(t_data *data);

void	ft_cub(void *param);
void	ft_draw(t_data *data, t_ray *ray, t_i_xy *xy);

void	ft_move_player(void *param);

int		ft_iswall(t_data *data, double x, double y);
t_u_int	ft_color(t_u_int r, t_u_int g, t_u_int b, t_u_int a);

/* **************************** parcing ***************************** */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct	s_point
{
	int x;
	int y;
} t_point;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
} t_textures;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;


typedef struct s_config
{
	t_textures tex;
	t_color floor;
	t_color ceil;
	char **map;
	int player_x;
	int player_y;
	char player_dir;
	int y_rows;
	int x_cols;
} t_config;
	
//malloc_free;
void free_ptr(void *ptr);
void	free_all(void);
void	*gc_malloc(size_t size);
char *gc_strndup(const char *line, int start, int end);
char	*ft_strdup(char *s1);

//parcing
int main_parce(char **cub_file, t_config *data);
void	data_init(t_config *conf);
int parce_line(char **file, int fd,t_config *data);
int assign_color(char *start,char *line, int i, t_config *data);
int is_map(char *line);
int assign_tex(char *start,char *line, int i, t_config *data);
int negative_map_position(t_config *data);
int only_spaces(char *s);
int get_cont_line(char *file);
char *get_start(char *line, int i);
char *get_color(char *line, int i);

//utils
int	ft_isdigit(int v);
int	ft_atoi(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strcmp(char *s1, char *s2);
int is_space(char c);


//validation
int validation(t_config *data);
int is_player(char c);
int	flood_fill(char **map, t_point p, int height, int width);
int validation_char_map(t_config * data);
char **prepar_map(t_config *data);
int get_long(t_config *data);
int get_h(char**map);
int	fill_inside(char **map, t_point p, t_config *data);
int check_inside(char **map, t_config *data);
void assing_position(int y, int x, t_config *data);
void	find_and_replace_player(char **map, t_config *data);


//grtnext_line
char	*get_next_line(int fd);
char	*ft_read_to_left_str(int fd, char *left_str);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_get_line(char *left_str);
char	*ft_new_left_str(char *left_str);
t_config *parcing(int ac, char **av);

#endif