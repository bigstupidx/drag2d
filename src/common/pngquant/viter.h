
#ifndef VITER_H
#define VITER_H

#include <vector>

typedef struct {
    double a, r, g, b, total;
} viter_state;

typedef void (*viter_callback)(hist_item *item, float diff);

void viter_init(const colormap *map, const int max_threads, const std::vector<viter_state>& state);
void viter_update_color(const f_pixel acolor, const float value, const colormap *map, const int match, const int thread, std::vector<viter_state>& state);
void viter_finalize(colormap *map, const int max_threads, const std::vector<viter_state>& state);
double viter_do_iteration(histogram *hist, colormap *const map, const float min_opaque_val, viter_callback callback);

#endif
