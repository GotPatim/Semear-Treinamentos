#include <stdio.h>
#include "motor.h"
#include "encoder.h"
#include "pid.h"


void app_main(void)
{
    init_gpio();
    init_pwm();
    pid_ctrl_block_handle_t pid_left = init_pid(LEFT_MOTOR);
    pid_ctrl_block_handle_t pid_right = init_pid(RIGHT_MOTOR);

    pcnt_unit_handle_t encoder_left = init_encoder(LEFT_ENC);
    pcnt_unit_handle_t encoder_right = init_encoder(RIGHT_ENC);
    
    float target_vel = 3;
    float inc_value = 0.0f;

    while(1){
        vTaskDelay(pdMS_TO_TICKS(100)); // 0,1s
        pid_calculate(pid_left, LEFT_MOTOR, target_vel, &inc_value, encoder_left);
        pid_calculate(pid_right, RIGHT_MOTOR, target_vel, &inc_value, encoder_right);
    }
}