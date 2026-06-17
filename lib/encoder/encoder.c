#include "encoder.h"

void init_encoder(){
    selected_encoder = NULL; // A unidade (o contador em si)
    pcnt_channel_handle_t pcnt_chan_a = NULL;   // O canal A do encoder
    pcnt_channel_handle_t pcnt_chan_b = NULL;   // O canal B do encoder

    //Definição da configuração da unidade com os limites máximos e mínimos de contagem dos encoders
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder));

    //Definição do filtro em nanosegundos
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder, &filter_config));//Configuração filtro

    //Definição da configuração do canal a do encoder
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = ENCODER_INPUT_A(CHA_ENCODER_1L), //Pino do canal a do encoder
        .level_gpio_num = ENCODER_INPUT_B(CHA_ENCODER_2L), //Pino do canal b do encoder
    };

    //Configuração do canal
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_a_config, &pcnt_chan_a));

    //Definição da configuração do canal b do encoder
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = ENCODER_INPUT_B(CHA_ENCODER_1L),
        .level_gpio_num = ENCODER_INPUT_A(CHA_ENCODER_2L),
    };

    //Configuração do canal
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_b_config, &pcnt_chan_b));

    //O unico parâmetro que controlamos é o pcnt_chan_a e pctn_chan_b definidos acima
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));

    //Faz o processo para os canais a e b do encoder
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

}