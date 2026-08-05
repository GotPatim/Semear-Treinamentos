    #include <stdio.h>
    #include "motor.h"
    #include "encoder.h"

    void app_main(void)
    {
        int pulse_count_L, pulse_count_R;
        int vel_final = 400;//de 0-1023, pois é o duty
        int vel_R = vel_final, vel_L = vel_final;
        init_gpio();
        init_pwm();
        init_encoder();
        // Codigo pro motor andar     
        ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder_L));
        ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder_R));
        while (1) {
            //p/ motor esqeurdo
            pcnt_unit_get_count(selected_encoder_L, &pulse_count_L);
            pcnt_unit_clear_count(selected_encoder_L);
            
            //p/ motor direito
            pcnt_unit_get_count(selected_encoder_R, &pulse_count_R);
            pcnt_unit_clear_count(selected_encoder_R);
            int vel_dif = pulse_count_L - pulse_count_R;

            if(vel_dif > 30){
                vel_L = vel_L; 
                if(vel_R < vel_final){
                    vel_R = vel_R + 10;  
                }
            } else if(vel_dif < -30){
                if(vel_L < vel_final){
                    vel_L = vel_L + 10; 
                }
                vel_R = vel_R; 
            }
            
            //motor da esquerda
            update_motor(LEFT, vel_L );
            // motor da direita
            update_motor(RIGHT, vel_R);
    
            vTaskDelay(pdMS_TO_TICKS(5000));

        }

    }