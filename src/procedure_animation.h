#ifndef PROCEDURE_ANIMATION
#define PROCEDURE_ANIMATION
#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include <stdint.h>

void procedure_animation_half_fill_spin(i2c_port_t device_num,
                                        uint64_t refresh_rate_ms, int iter_num);
void procedure_animation_h_line_sequence(i2c_port_t device_num,
                                         uint64_t refresh_rate_ms,
                                         int iter_num);
void procedure_animation_v_line_sequence(i2c_port_t device_num,
                                         uint64_t refresh_rate_ms,
                                         int iter_num);
void procedure_animation_nested_rectangles(i2c_port_t device_num,
                                           uint64_t refresh_rate_ms,
                                           int iter_num);

#endif
