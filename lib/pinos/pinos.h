
// --------------- Ricardo --------------- 
//Pinos Motor
// GPIOs of h-bridge for left motor
// pinos q mandam pro motor se vai pra frente ou pra tras
#define INPUT_LEFT_1   GPIO_NUM_32
#define INPUT_LEFT_2   GPIO_NUM_33

#define LEDC_OUTPUT_LEFT   GPIO_NUM_23 // define o pino q controla vel do motor

// GPIOs of h-bridge for right motor
// pinos q mandam pro motor se vai pra frente ou pra tras
#define INPUT_RIGHT_1   GPIO_NUM_27
#define INPUT_RIGHT_2   GPIO_NUM_14

#define LEDC_OUTPUT_RIGHT   GPIO_NUM_13 // define o pino q controla vel do motor

// Canais PWM para cada motor
// é basicamente por onde o relogio manda informação pro (pino PMW do) motor
#define LEDC_CHANNEL_LEFT   LEDC_CHANNEL_0
#define LEDC_CHANNEL_RIGHT  LEDC_CHANNEL_1

//Pinos Encoder
//Portas encoders motor 1
#define CHA_ENCODER_1R 17
#define CHA_ENCODER_2R 16

//Portas encoders motor 2
#define CHA_ENCODER_1L 18
#define CHA_ENCODER_2L 19




// --------------- Ricardo --------------- 