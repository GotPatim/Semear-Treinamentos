#ifndef ENCODER_H
#define ENCODER_H

#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/pulse_cnt.h"


/* Enum */
typedef enum {
    LEFT_ENC = 0,
    RIGHT_ENC = 1
} encoder_side_t;

//PCNT limites
#define PCNT_HIGH_LIMIT 10000
#define PCNT_LOW_LIMIT  -10000

//Portas encoders motor 1
#define CHA_ENCODER_1R 4
#define CHA_ENCODER_2R 16

//Portas encoders motor 2
#define CHA_ENCODER_1L 2
#define CHA_ENCODER_2L 15


/* Macro functions */ //redireciona para os pinos com=nforme o motor q esta sendo tratado
#define ENCODER_INPUT_A(NUM) NUM == (RIGHT_ENC) ? CHA_ENCODER_1R : CHA_ENCODER_1L
#define ENCODER_INPUT_B(NUM) NUM == (RIGHT_ENC) ? CHA_ENCODER_2R : CHA_ENCODER_2L

extern pcnt_unit_handle_t selected_encoder_L; // A unidade (o contador em si) // extern pq se nn ele define outra vez qnd eu chamar o arquivo ddnv?
extern pcnt_unit_handle_t selected_encoder_R; // A unidade (o contador em si) // extern pq se nn ele define outra vez qnd eu chamar o arquivo ddnv?

int get_encoder_ticks(pcnt_unit_handle_t handler); 
int get_encoder_position(pcnt_unit_handle_t handler);

pcnt_unit_handle_t init_encoder(encoder_side_t side);

#endif