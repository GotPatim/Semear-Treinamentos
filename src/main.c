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
        
        //motor da esquerda
        update_motor(LEFT, vel_L );
        // motor da direita
        update_motor(RIGHT, vel_R);
        
        while(1){
            vTaskDelay(pdMS_TO_TICKS(5000));
            pcnt_unit_get_count(selected_encoder_L, &pulse_count_L);
            pcnt_unit_get_count(selected_encoder_R, &pulse_count_R);

            printf("Ticks-> L: %d | R: %d\n", pulse_count_L, pulse_count_R);
        }

        

    }