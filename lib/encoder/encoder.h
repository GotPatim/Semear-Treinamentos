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
    ENC_LEFT = 0,
    ENC_RIGHT = 1
} encoder_side_t;

//PCNT limites
#define PCNT_HIGH_LIMIT 1500
#define PCNT_LOW_LIMIT  -1500

//Portas encoders motor 1
#define CHA_ENCODER_1R 0
#define CHA_ENCODER_2R 0

//Portas encoders motor 2
#define CHA_ENCODER_1L 0
#define CHA_ENCODER_2L 0


/* Macro functions */
#define ENCODER_INPUT_A(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_1R : CHA_ENCODER_1L
#define ENCODER_INPUT_B(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_2R : CHA_ENCODER_2L

pcnt_unit_handle_t selected_encoder = NULL; // A unidade (o contador em si)



void init_encoder();