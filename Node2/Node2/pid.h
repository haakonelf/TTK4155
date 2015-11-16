#pragma once

void pid_init(float _kp, float _ki, float _kd);
float pid_generate(float r, float y, float dt);
int pid_find_max_encoder_value(void);