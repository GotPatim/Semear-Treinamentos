#include <stdio.h>
#include "h_bridge/h_bridge.h"



void app_main(void)
{
    init_gpio();
    init_pwm();

    while (1) {
        //p/ frente
        //motor da esquerda
        update_motor(LEFT, 255); // 255 pq vai de 0-1023, ent é 25%
        // motor da direita
        update_motor(RIGHT, 255); // 255 pq vai de 0-1023, ent é 25%
        
        
        vTaskDelay(pdMS_TO_TICKS(5000));
        
        //p/ tras
        //motor da esquerda
        update_motor(LEFT, -255); // 255 pq vai de 0-1023, ent é 25%
        // motor da direita
        update_motor(RIGHT, -255); // 255 pq vai de 0-1023, ent é 25%
    }
}