#include "pid.h"

pid_ctrl_block_handle_t init_pid(motor_side_t motor){
    pid_ctrl_parameter_t pid_param = { //configura com os parametros padroes
        .kp = kp(motor),     
        .ki = ki(motor),      
        .kd = kd(motor),
        .max_output = max_output(motor),
        .min_output = min_output(motor),
        .max_integral = max_integral(motor),
        .min_integral = min_integral(motor),
        .cal_type = PID_CAL_TYPE_INCREMENTAL 
    };

    pid_ctrl_config_t pid_ctrl_config = { // aplica os parametros
        .init_param = pid_param
    };

    pid_ctrl_block_handle_t pid;

    ESP_ERROR_CHECK(pid_new_control_block(&pid_ctrl_config, &pid));

    return pid;
}

esp_err_t pid_calculate(pid_ctrl_block_handle_t pid, motor_side_t motor, float target_vel, float* inc_value, pcnt_unit_handle_t encoder){
    float ratio = 0.00472; // proporção entre (rad/tick) 

    float vel = (get_encoder_ticks(encoder) * ratio)/ 0.1f; // qnts rads andou dsd a ultima leitura dividido pelo tempo(em segundo)
    pcnt_unit_clear_count(encoder);//limpa a contagem para o proximo ciclo

    float error = target_vel - vel;

    float value;

    ESP_ERROR_CHECK(pid_compute(pid, error, &value));

    *inc_value = +value; 

    update_motor(motor, *inc_value);

    return ESP_OK;
}