#include <stdio.h>
#include "motor.h"
#include "encoder.h"



void app_main(void)
{
    int pulse_count;
    init_gpio();
    init_pwm();
    // Codigo pro motor andar     
    ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder));
    while (1) {
        //p/ frente
        ESP_ERROR_CHECK(pcnt_unit_clear_count(selected_encoder));
        do{
            ESP_ERROR_CHECK(pcnt_unit_get_count(selected_encoder, &pulse_count)); //Salva em pulse_count o número de contagens.
            
            //motor da esquerda
            update_motor(LEFT, 255); // 255 pq vai de 0-1023, ent é 25%
            // motor da direita
            update_motor(RIGHT, 255); // 255 pq vai de 0-1023, ent é 25%
            
        } while(pulse_count <= PCNT_HIGH_LIMIT);
        
        vTaskDelay(pdMS_TO_TICKS(5000));
        
        ESP_ERROR_CHECK(pcnt_unit_clear_count(selected_encoder));
        //p/ tras
        do{
            ESP_ERROR_CHECK(pcnt_unit_get_count(selected_encoder, &pulse_count)); //Salva em pulse_count o número de contagens.
            
            //motor da esquerda
            update_motor(LEFT, -255); // 255 pq vai de -1023-1023, ent é 25%
            // motor da direita
            update_motor(RIGHT, -255); // 255 pq vai de 0-1023, ent é 25%
            
        } while(pulse_count >= PCNT_LOW_LIMIT);
        
    }


}