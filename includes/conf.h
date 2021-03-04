#ifndef CONF_H
# define CONF_H

typedef struct  s_data 
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct	s_win
{
	void	*mlx;
	void	*win;
}				t_win;

typedef struct	s_res
{
	int X;
	int Y;
}				t_res;

typedef struct   s_conf
{
    t_data  *img;
    t_win   *vars;
    t_res   *res;
}               t_conf;

int     key_hook (int keycode, t_win *vars);
int     close_win(t_win *vars);
void	init_window(t_win *vars, t_res *RES, char *title);
void	init_img(t_data *data, t_win *vars, int width, int height);
#endif