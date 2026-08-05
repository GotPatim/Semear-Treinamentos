#include "encoder.h"

pcnt_unit_handle_t selected_encoder_L;
pcnt_unit_handle_t selected_encoder_R;

void init_encoder(){
    selected_encoder_L = NULL; // A unidade (o contador em si)
    selected_encoder_R = NULL; // A unidade (o contador em si)
    pcnt_channel_handle_t pcnt_chan_a_L = NULL, pcnt_chan_b_L = NULL;
    pcnt_channel_handle_t pcnt_chan_a_R = NULL, pcnt_chan_b_R = NULL;
    //Definição da configuração da unidade com os limites máximos e mínimos de contagem dos encoders
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder_L));
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder_R));

    //Definição do filtro em nanosegundos
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder_L, &filter_config));//Configuração filtro
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder_R, &filter_config));//Configuração filtro

    //Definição da configuração do canal a do encoder
    pcnt_chan_config_t chan_a_config_L = {
        .edge_gpio_num = ENCODER_INPUT_A(ENC_LEFT), //Pino do canal a do encoder esquerdo
        .level_gpio_num = ENCODER_INPUT_B(ENC_LEFT), //Pino do canal b do encoder esquerdo
    };
    pcnt_chan_config_t chan_a_config_R = {
        .edge_gpio_num = ENCODER_INPUT_A(ENC_RIGHT), //Pino do canal a do encoder direito
        .level_gpio_num = ENCODER_INPUT_B(ENC_RIGHT), //Pino do canal b do encoder direito
    };

    //Configuração do canal
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder_L, &chan_a_config_L, &pcnt_chan_a_L));
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder_R, &chan_a_config_R, &pcnt_chan_a_R));

    
    //Definição da configuração do canal b do encoder
    pcnt_chan_config_t chan_b_config_L = {
        .edge_gpio_num = ENCODER_INPUT_B(ENC_LEFT),
        .level_gpio_num = ENCODER_INPUT_A(ENC_LEFT),
    };
    pcnt_chan_config_t chan_b_config_R = {
        .edge_gpio_num = ENCODER_INPUT_B(ENC_RIGHT),
        .level_gpio_num = ENCODER_INPUT_A(ENC_RIGHT),
    };

    //Configuração do canal
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder_L, &chan_b_config_L, &pcnt_chan_b_L));
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder_R, &chan_b_config_R, &pcnt_chan_b_R));

    //Faz o processo para os canais a dos encoders
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a_L, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a_L, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a_R, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a_R, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    //Faz o processo para os canais b dos encoders
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b_L, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b_L, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b_R, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b_R, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

}