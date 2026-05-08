#ifndef PROCEDURE_ANIMATION
#define PROCEDURE_ANIMATION
#include "driver/i2c.h"
#include <stdint.h>

void procedure_animation_half_fill_spin(uint64_t refresh_rate_ms, int iter_num);
void procedure_animation_h_line_sequence(uint64_t refresh_rate_ms,
                                         int iter_num);
void procedure_animation_v_line_sequence(uint64_t refresh_rate_ms,
                                         int iter_num);
void procedure_animation_nested_rectangles(uint64_t refresh_rate_ms,
                                           int iter_num);

#endif
