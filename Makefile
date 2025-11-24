MLX_REPO = https://github.com/codam-coding-college/MLX42.gitz

MLX = $(HOME)/MLX42

MLX_LIB = $(MLX)/lib/libmlx42.a

MLX_H_DIR = $(MLX)/include/MLX42

SRCS = src/cub3D.c src/ft_cub_init.c src/ft_cub_loop.c src/ft_cub.c src/ft_draw.c src/ft_move_player.c src/utils.c \
			src/parcing/get_next_line/get_next_line.c src/parcing/memori_manage/gc_malloc.c src/parcing/memori_manage/memory_util.c \
			src/parcing/parcer/main_p.c src/parcing/parcer/parce_1_.c src/parcing/parcer/parce_coler.c src/parcing/parcer/parce_map_utils.c \
			src/parcing/parcer/parce_map.c src/parcing/parcer/parce_utils.c src/parcing/parcer/validation_helper.c \
			src/parcing/parcer/validation_map.c src/parcing/parcing.c

OBJS= $(SRCS:.c=.o)

NAME = cub3D

SRCS_B = bonus/src/cub3D_bonus.c bonus/src/ft_cub_init_bonus.c bonus/src/ft_cub_loop_bonus.c bonus/src/ft_cub_bonus.c \
			bonus/src/ft_draw_bonus.c bonus/src/ft_move_player_bonus.c bonus/src/utils_bonus.c bonus/src/ft_mini_map_bonus.c bonus/src/ft_mouse_bonus.c \
			bonus/src/parcing/gc_malloc_bonus.c bonus/src/parcing/get_next_line_bonus.c bonus/src/parcing/parcing_bonus.c \
			bonus/src/parcing/main_p_bonus.c bonus/src/parcing/memory_util_bonus.c bonus/src/parcing/parce_1_bonus.c bonus/src/parcing/parce_coler_bonus.c \
			bonus/src/parcing/parce_map_bonus.c bonus/src/parcing/parce_map_utils_bonus.c bonus/src/parcing/parce_utils_bonus.c \
			bonus/src/parcing/validation_helper_bonus.c bonus/src/parcing/validation_map_bonus.c 

OBJS_B= $(SRCS_B:.c=.o)

NAME_B = cub3D_bonus

CC = cc -Wall -Wextra -Werror -fsanitize=address

RM = rm -f

%.o: %.c include/cub3D.h
	$(CC) -c $< -Iinclude -I$(MLX_H_DIR) -o $@

%_bonus.o: %_bonus.c bonus/include/cub3D_bonus.h
	$(CC) -c $< -Ibonus/include -I$(MLX_H_DIR) -o $@

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) -Iinclude $(MLX_LIB) -I$(MLX_H_DIR) -ldl -lglfw -pthread -lm -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(MLX_LIB) $(OBJS_B)
	$(CC) $(OBJS_B) -Ibonus/include $(MLX_LIB) -I$(MLX_H_DIR) -ldl -lglfw -pthread -lm -o $(NAME_B)

$(MLX_LIB): $(MLX)
	cmake $(MLX) -B $(MLX)/lib && make -C $(MLX)/lib -j4

$(MLX):
	git clone $(MLX_REPO) $(MLX)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)

re: fclean all

rebonus: fclean bonus

cleanall: fclean
	$(RM) -r $(MLX)