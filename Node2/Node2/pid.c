#include "motor_driver.h"
#include <util/delay.h>
#include <stdint.h>

float kp;
float ki;
float kd;

float reference;
float integral;
float prev_error;

void pid_init(float _kp, float _ki, float _kd){
	kp = _kp;
	ki = _ki;
	kd = _kd;
	
	reference	= 0;
	integral	= 0;
	prev_error	= 0;

}


float pid_generate(float r, float y, float dt){
	
	float error = r - y;
	integral += error * dt;
	float derivative = (error - prev_error) / dt;
	
	prev_error = error;
	
	return kp*error + ki*integral + kd*derivative;
}

uint16_t pid_find_max_encoder_value(void){
		uint16_t enc_val = 0, prev_enc_val = -1;
		motor_speed(75);
		
		//Stop at left end
		while(enc_val != prev_enc_val){
			printf("In while\n");
			enc_val = motor_encoder_read();
			_delay_ms(100);
			prev_enc_val = motor_encoder_read();
		}
		printf("Out of while\n");
		motor_speed(0);
		motor_encoder_reset();
		
		//Stop at right end and set max
		motor_speed(-75);
		enc_val = 0, prev_enc_val = -1;
		while(enc_val != prev_enc_val){
			enc_val = motor_encoder_read();
			_delay_ms(100);
			prev_enc_val = motor_encoder_read();
		}
		motor_speed(0);
		
		//Max value of encoder.
		return enc_val;
}