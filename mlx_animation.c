/* mlx_animation.c
 * مثال كامل على animation ب MLX42
 * - نافذة وحدة 800x600
 * - frames من ./frames/frame0.png, frame1.png, ...
 * - كل frame كيبان بوحدو، animation smooth بحال فيديو
 * - SPACE: إيقاف/تشغيل
 * - ESC: خروج
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "MLX42/MLX42.h"

#define FRAMES_DIR "./frames"
#define TARGET_FPS 60.0
#define ANIM_FPS 10.0
#define MAX_PATH 512

typedef struct s_anim {
    mlx_t *mlx;
    mlx_image_t **frames; // array ديال frames
    size_t frame_count;
    size_t current;
    int counter;
    int frame_delay;
    int win_w;
    int win_h;
    bool playing;
    mlx_image_t *screen; // buffer image
} t_anim;

// بناء path بحال "./frames/frame0.png"
static char *build_frame_path(size_t idx) {
    char *buf = malloc(MAX_PATH);
    if (!buf) return NULL;
    snprintf(buf, MAX_PATH, "%s/frame%zu.png", FRAMES_DIR, idx);
    return buf;
}

// تحميل frames
static mlx_image_t **load_frames(mlx_t *mlx, size_t *out_count) {
    size_t cap = 32;
    size_t count = 0;
    mlx_image_t **arr = calloc(cap, sizeof(mlx_image_t *));
    if (!arr) return NULL;

    for (size_t i = 0;; ++i) {
        char *path = build_frame_path(i);
        if (!path) break;
        mlx_texture_t *tex = mlx_load_png(path);
        free(path);
        if (!tex) break;
        mlx_image_t *img = mlx_texture_to_image(mlx, tex);
        mlx_delete_texture(tex);
        if (!img) break;
        if (count >= cap) {
            cap *= 2;
            mlx_image_t **tmp = realloc(arr, cap * sizeof(mlx_image_t *));
            if (!tmp) break;
            arr = tmp;
        }
        arr[count++] = img;
    }
    if (count == 0) {
        free(arr);
        *out_count = 0;
        return NULL;
    }
    *out_count = count;
    return arr;
}

// loop ديال animation
static void loop(void *param) {
    t_anim *anim = (t_anim *)param;
    if (!anim || !anim->frames || !anim->screen) return;

    if (!anim->playing) return;

    anim->counter++;
    if (anim->counter < anim->frame_delay) return;
    anim->counter = 0;

    // مسح كامل النافذة
    memset(anim->screen->pixels, 0, anim->win_w * anim->win_h * 4); // أسود كامل

    // current frame
    mlx_image_t *img = anim->frames[anim->current];
    if (img) {
        double scale = 0.5; // نصف الحجم الأصلي
        int new_w = (int)(img->width * scale);
        int new_h = (int)(img->height * scale);

        int x_start = (anim->win_w - new_w) / 2;           // مركز أفقي
        int y_start = anim->win_h - new_h;                // bottom

        // نسخ pixels مصغرة
        for (int y = 0; y < new_h; ++y) {
            for (int x = 0; x < new_w; ++x) {
                int src_x = (int)(x / scale);
                int src_y = (int)(y / scale);
                uint32_t *dst = (uint32_t*)anim->screen->pixels + (y_start + y) * anim->win_w + (x_start + x);
                uint32_t *src = (uint32_t*)img->pixels + src_y * img->width + src_x;
                *dst = *src;
            }
        }
    }

    anim->current = (anim->current + 1) % anim->frame_count;

    // ارسم buffer مرة وحدة
    mlx_image_to_window(anim->mlx, anim->screen, 0, 0);
}

// كيبورد
static void keyhook(mlx_key_data_t keydata, void *param) {
    t_anim *anim = (t_anim *)param;
    if (!anim) return;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) {
        mlx_terminate(anim->mlx);
    }
    if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS) {
        anim->playing = !anim->playing;
        anim->counter = 0;
    }
}

int main(void) {
    int win_w = 800;
    int win_h = 600;

    mlx_t *mlx = mlx_init(win_w, win_h, "Animation", true);
    if (!mlx) {
        fprintf(stderr, "فشل تهيئة MLX.\n");
        return 1;
    }

    t_anim anim = {0};
    anim.mlx = mlx;
    anim.win_w = win_w;
    anim.win_h = win_h;
    anim.current = 0;
    anim.counter = 0;
    anim.frame_delay = (int)(TARGET_FPS / ANIM_FPS);
    anim.playing = true;

    size_t frame_count = 0;
    mlx_image_t **frames = load_frames(mlx, &frame_count);
    if (!frames || frame_count == 0) {
        fprintf(stderr, "ما لقا حتى frame ف %s. دير frame0.png, frame1.png, ...\n", FRAMES_DIR);
        mlx_terminate(mlx);
        return 1;
    }

    anim.frames = frames;
    anim.frame_count = frame_count;

    // buffer واحد للشاشة
    anim.screen = mlx_new_image(mlx, win_w, win_h);

    // key hook
    mlx_key_hook(mlx, &keyhook, &anim);

    // loop hook
    mlx_loop_hook(mlx, &loop, &anim);

    // run
    mlx_loop(mlx);

    // cleanup
    for (size_t i = 0; i < anim.frame_count; ++i) {
        if (anim.frames[i])
            mlx_delete_image(mlx, anim.frames[i]);
    }
    free(anim.frames);
    mlx_delete_image(mlx, anim.screen);

    return 0;
}
