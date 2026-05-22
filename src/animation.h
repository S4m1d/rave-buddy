#ifndef ANIMATION_H
#define ANIMATION_H

#include "hal/i2c_types.h"

void animation_static_frame(i2c_port_t device_num,char *path);
void animation_play(i2c_port_t device_num,char *path, int iter_count);

#endif
