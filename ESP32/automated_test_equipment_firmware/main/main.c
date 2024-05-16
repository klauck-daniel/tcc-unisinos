// UDP SOCKET Server with WiFi connection communication via Socket

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <esp_system.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"

#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_mac.h"
#include "esp_eth.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "esp_http_client.h"
#include "esp_event.h"
#include "esp_system.h"

#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/ip_addr.h"

#include "nvs_flash.h"
#include "ping/ping_sock.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define PIN_03V GPIO_NUM_16
#define PIN_05V GPIO_NUM_17
#define PIN_12V GPIO_NUM_5
#define PIN_24V GPIO_NUM_18

#define PIN_02 GPIO_NUM_36
#define PIN_03 GPIO_NUM_39
#define PIN_04 GPIO_NUM_34
#define PIN_05 GPIO_NUM_35
#define PIN_06 GPIO_NUM_32
#define PIN_07 GPIO_NUM_33
#define PIN_08 GPIO_NUM_25
#define PIN_09 GPIO_NUM_26
#define PIN_10 GPIO_NUM_27 // PWM CH0
#define PIN_11 GPIO_NUM_14 // PWM CH1
#define PIN_12 GPIO_NUM_12 // PWM CH2
#define PIN_13 GPIO_NUM_13 // PWM CH3
#define PIN_18 GPIO_NUM_15
#define PIN_19 GPIO_NUM_2
#define PIN_20 GPIO_NUM_4
#define PIN_25 GPIO_NUM_19 // PWM CH4
#define PIN_26 GPIO_NUM_21 // PWM CH5
#define PIN_27 GPIO_NUM_3
// #define PIN_28 GPIO_NUM_1
#define PIN_29 GPIO_NUM_22 // PWM CH6
#define PIN_30 GPIO_NUM_23 // PWM CH7

// #define set_duty(duty) ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty)
// #define upt_duty ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0)

#define PORT 3333
static const char *TAG = "UDP SOCKET SERVER";

// Variáveis Globais
int frequency = 100;
int timer_bits = 8191; // 2^13

char test_vector_pin_6[12];
int hold_time_pin_6 = 0;

char test_vector_pin_7[12];
int hold_time_pin_7 = 0;

char test_vector_pin_8[12];
int hold_time_pin_8 = 0;

char test_vector_pin_9[12];
int hold_time_pin_9 = 0;

char test_vector_pin_10[12];
int hold_time_pin_10 = 0;

char test_vector_pin_11[12];
int hold_time_pin_11 = 0;

char test_vector_pin_12[12];
int hold_time_pin_12 = 0;

char test_vector_pin_13[12];
int hold_time_pin_13 = 0;

char test_vector_pin_18[12];
int hold_time_pin_18 = 0;

char test_vector_pin_19[12];
int hold_time_pin_19 = 0;

char test_vector_pin_20[12];
int hold_time_pin_20 = 0;

char test_vector_pin_25[12];
int hold_time_pin_25 = 0;

char test_vector_pin_26[12];
int hold_time_pin_26 = 0;

char test_vector_pin_27[12];
int hold_time_pin_27 = 0;

char test_vector_pin_29[12];
int hold_time_pin_29 = 0;

char test_vector_pin_30[12];
int hold_time_pin_30 = 0;

// Struct de configuração dos pinos
//[pin_number, output, frequencia, dutyCycle, vetorTeste, bitHoldTime]
typedef struct
{
    int pin;
    bool is_input;
    // int frequency;
    int duty_cycle;
    char test_vector[12];
    int bit_hold_time;
} PinConfig;

typedef struct
{
    int pin;
    int voltage;
} VoltageConfig;

void start_test()
{
    printf("START TESTE\n");

    TickType_t start_time_pin_6 = xTaskGetTickCount();
    int bit_index_pin_6 = 0;

    TickType_t start_time_pin_7 = xTaskGetTickCount();
    int bit_index_pin_7 = 0;

    TickType_t start_time_pin_8 = xTaskGetTickCount();
    int bit_index_pin_8 = 0;

    TickType_t start_time_pin_9 = xTaskGetTickCount();
    int bit_index_pin_9 = 0;

    TickType_t start_time_pin_10 = xTaskGetTickCount();
    int bit_index_pin_10 = 0;

    TickType_t start_time_pin_11 = xTaskGetTickCount();
    int bit_index_pin_11 = 0;

    TickType_t start_time_pin_12 = xTaskGetTickCount();
    int bit_index_pin_12 = 0;

    TickType_t start_time_pin_13 = xTaskGetTickCount();
    int bit_index_pin_13 = 0;

    TickType_t start_time_pin_18 = xTaskGetTickCount();
    int bit_index_pin_18 = 0;

    TickType_t start_time_pin_19 = xTaskGetTickCount();
    int bit_index_pin_19 = 0;

    TickType_t start_time_pin_20 = xTaskGetTickCount();
    int bit_index_pin_20 = 0;

    TickType_t start_time_pin_25 = xTaskGetTickCount();
    int bit_index_pin_25 = 0;

    TickType_t start_time_pin_26 = xTaskGetTickCount();
    int bit_index_pin_26 = 0;

    TickType_t start_time_pin_27 = xTaskGetTickCount();
    int bit_index_pin_27 = 0;

    TickType_t start_time_pin_29 = xTaskGetTickCount();
    int bit_index_pin_29 = 0;

    TickType_t start_time_pin_30 = xTaskGetTickCount();
    int bit_index_pin_30 = 0;

    if (hold_time_pin_6 != 0 && test_vector_pin_6[0] != 2)
    {
        if (test_vector_pin_6[bit_index_pin_6] == '1')
        {
            gpio_set_level(PIN_06, 1);
            printf("Pino 6 = 1 \n");
        }
        else if (test_vector_pin_6[bit_index_pin_6] == '0')
        {
            gpio_set_level(PIN_06, 0);
            printf("Pino 6 = 0 \n");
        }
        bit_index_pin_6++;
    }
    else
        bit_index_pin_6 = 13;

    if (hold_time_pin_7 != 0 && test_vector_pin_7[0] != '2')
    {

        if (test_vector_pin_7[bit_index_pin_7] == '1')
        {
            gpio_set_level(PIN_07, 1);
            printf("Pino 7 = 1 \n");
        }
        else if (test_vector_pin_7[bit_index_pin_7] == '0')
        {
            gpio_set_level(PIN_07, 0);
            printf("Pino 7 = 0 \n");
        }
        bit_index_pin_7++;
    }
    else
        bit_index_pin_7 = 13;

    if (hold_time_pin_8 != 0 && test_vector_pin_8[0] != 2)
    {

        if (test_vector_pin_8[bit_index_pin_8] == '1')
        {
            gpio_set_level(PIN_08, 1);
            printf("Pino 8 = 1 \n");
        }
        else if (test_vector_pin_8[bit_index_pin_8] == '0')
        {
            gpio_set_level(PIN_08, 0);
            printf("Pino 8 = 0 \n");
        }
        bit_index_pin_8++;
    }
    else
        bit_index_pin_8 = 13;

    if (hold_time_pin_9 != 0 && test_vector_pin_9[0] != 2)
    {

        if (test_vector_pin_9[bit_index_pin_9] == '1')
        {
            gpio_set_level(PIN_09, 1);
            printf("Pino 9 = 1 \n");
        }
        else if (test_vector_pin_9[bit_index_pin_9] == '0')
        {
            gpio_set_level(PIN_09, 0);
            printf("Pino 9 = 0 \n");
        }
        bit_index_pin_9++;
    }
    else
        bit_index_pin_9 = 13;

    if (hold_time_pin_10 != 0 && test_vector_pin_10[0] != 2)
    {

        if (test_vector_pin_10[bit_index_pin_10] == '1')
        {
            gpio_set_level(PIN_10, 1);
            printf("Pino 10 = 1 \n");
        }
        else if (test_vector_pin_10[bit_index_pin_10] == '0')
        {
            gpio_set_level(PIN_10, 0);
            printf("Pino 10 = 0 \n");
        }
        bit_index_pin_10++;
    }
    else
        bit_index_pin_10 = 13;

    if (hold_time_pin_11 != 0 && test_vector_pin_11[0] != 2)
    {

        if (test_vector_pin_11[bit_index_pin_11] == '1')
        {
            gpio_set_level(PIN_11, 1);
            printf("Pino 11 = 1 \n");
        }
        else if (test_vector_pin_11[bit_index_pin_11] == '0')
        {
            gpio_set_level(PIN_11, 0);
            printf("Pino 11 = 0 \n");
        }
        bit_index_pin_11++;
    }
    else
        bit_index_pin_11 = 13;

    if (hold_time_pin_12 != 0 && test_vector_pin_12[0] != 2)
    {

        if (test_vector_pin_12[bit_index_pin_12] == '1')
        {
            gpio_set_level(PIN_12, 1);
            printf("Pino 12 = 1 \n");
        }
        else if (test_vector_pin_12[bit_index_pin_12] == '0')
        {
            gpio_set_level(PIN_12, 0);
            printf("Pino 12 = 0 \n");
        }
        bit_index_pin_12++;
    }
    else
        bit_index_pin_12 = 13;

    if (hold_time_pin_13 != 0 && test_vector_pin_13[0] != 2)
    {

        if (test_vector_pin_13[bit_index_pin_13] == '1')
        {
            gpio_set_level(PIN_13, 1);
            printf("Pino 13 = 1 \n");
        }
        else if (test_vector_pin_13[bit_index_pin_13] == '0')
        {
            gpio_set_level(PIN_13, 0);
            printf("Pino 13 = 0 \n");
        }
        bit_index_pin_13++;
    }
    else
        bit_index_pin_13 = 13;

    if (hold_time_pin_18 != 0 && test_vector_pin_18[0] != 2)
    {

        if (test_vector_pin_18[bit_index_pin_18] == '1')
        {
            gpio_set_level(PIN_18, 1);
            printf("Pino 18 = 1 \n");
        }
        else if (test_vector_pin_18[bit_index_pin_18] == '0')
        {
            gpio_set_level(PIN_18, 0);
            printf("Pino 18 = 0 \n");
        }
        bit_index_pin_18++;
    }
    else
        bit_index_pin_18 = 13;

    if (hold_time_pin_19 != 0 && test_vector_pin_19[0] != 2)
    {

        if (test_vector_pin_19[bit_index_pin_19] == '1')
        {
            gpio_set_level(PIN_19, 1);
            printf("Pino 19 = 1 \n");
        }
        else if (test_vector_pin_19[bit_index_pin_19] == '0')
        {
            gpio_set_level(PIN_19, 0);
            printf("Pino 19 = 0 \n");
        }
        bit_index_pin_19++;
    }
    else
        bit_index_pin_19 = 13;

    if (hold_time_pin_20 != 0 && test_vector_pin_20[0] != 2)
    {

        if (test_vector_pin_20[bit_index_pin_20] == '1')
        {
            gpio_set_level(PIN_20, 1);
            printf("Pino 20 = 1 \n");
        }
        else if (test_vector_pin_20[bit_index_pin_20] == '0')
        {
            gpio_set_level(PIN_20, 0);
            printf("Pino 20 = 0 \n");
        }
        bit_index_pin_20++;
    }
    else
        bit_index_pin_20 = 13;

    if (hold_time_pin_25 != 0 && test_vector_pin_25[0] != 2)
    {

        if (test_vector_pin_25[bit_index_pin_25] == '1')
        {
            gpio_set_level(PIN_25, 1);
            printf("Pino 25 = 1 \n");
        }
        else if (test_vector_pin_25[bit_index_pin_25] == '0')
        {
            gpio_set_level(PIN_25, 0);
            printf("Pino 25 = 0 \n");
        }
        bit_index_pin_25++;
    }
    else
        bit_index_pin_25 = 13;

    if (hold_time_pin_26 != 0 && test_vector_pin_26[0] != 2)
    {

        if (test_vector_pin_26[bit_index_pin_26] == '1')
        {
            gpio_set_level(PIN_26, 1);
            printf("Pino 26 = 1 \n");
        }
        else if (test_vector_pin_26[bit_index_pin_26] == '0')
        {
            gpio_set_level(PIN_26, 0);
            printf("Pino 26 = 0 \n");
        }
        bit_index_pin_26++;
    }
    else
        bit_index_pin_26 = 13;

    if (hold_time_pin_27 != 0 && test_vector_pin_27[0] != 2)
    {

        if (test_vector_pin_27[bit_index_pin_27] == '1')
        {
            gpio_set_level(PIN_27, 1);
            printf("Pino 27 = 1 \n");
        }
        else if (test_vector_pin_27[bit_index_pin_27] == '0')
        {
            gpio_set_level(PIN_27, 0);
            printf("Pino 27 = 0 \n");
        }
        bit_index_pin_27++;
    }
    else
        bit_index_pin_27 = 13;

    if (hold_time_pin_29 != 0 && test_vector_pin_29[0] != 2)
    {

        if (test_vector_pin_29[bit_index_pin_29] == '1')
        {
            gpio_set_level(PIN_29, 1);
            printf("Pino 29 = 1 \n");
        }
        else if (test_vector_pin_29[bit_index_pin_29] == '0')
        {
            gpio_set_level(PIN_29, 0);
            printf("Pino 29 = 0 \n");
        }
        bit_index_pin_29++;
    }
    else
        bit_index_pin_29 = 13;

    if (hold_time_pin_30 != 0 && test_vector_pin_30[0] != 2)
    {
        gpio_set_direction(PIN_30, GPIO_MODE_OUTPUT);

        if (test_vector_pin_30[bit_index_pin_30] == '1')
        {
            gpio_set_level(PIN_30, 1);
            printf("Pino 30 = 1 \n");
        }
        else if (test_vector_pin_30[bit_index_pin_30] == '0')
        {
            gpio_set_level(PIN_30, 0);
            printf("Pino 30 = 0 \n");
        }
        bit_index_pin_30++;
    }
    else
        bit_index_pin_30 = 13;

    while (bit_index_pin_6 < 12 || bit_index_pin_7 < 12 || bit_index_pin_8 < 12 || bit_index_pin_9 < 12 || bit_index_pin_10 < 12 || bit_index_pin_11 < 12 || bit_index_pin_12 < 12 || bit_index_pin_13 < 12 || bit_index_pin_18 < 12 || bit_index_pin_19 < 12 || bit_index_pin_20 < 12 || bit_index_pin_25 < 12 || bit_index_pin_26 < 12 || bit_index_pin_27 < 12 || bit_index_pin_29 < 12 || bit_index_pin_30 < 12)
    {
        TickType_t current_time = xTaskGetTickCount();

        // Atualizar pino 6 se for hora e houver mais bits para enviar
        if (hold_time_pin_6 != 0 && test_vector_pin_6[0] != 2)
        {
            if (current_time - start_time_pin_6 >= (hold_time_pin_6 / portTICK_PERIOD_MS) && bit_index_pin_6 < 12)
            {
                if (test_vector_pin_6[bit_index_pin_6] == '1')
                {
                    gpio_set_level(PIN_06, 1);
                    printf("Pino 6 = 1 \n");
                }
                else if (test_vector_pin_6[bit_index_pin_6] == '0')
                {
                    gpio_set_level(PIN_06, 0);
                    printf("Pino 6 = 0 \n");
                }
                start_time_pin_6 = current_time;
                bit_index_pin_6++;
            }
        }

        // Atualizar pino 7 se for hora e houver mais bits para enviar
        if (hold_time_pin_7 != 0 && test_vector_pin_7[0] != '2')
        {
            if (current_time - start_time_pin_7 >= (hold_time_pin_7 / portTICK_PERIOD_MS) && bit_index_pin_7 < 12)
            {
                if (test_vector_pin_7[bit_index_pin_7] == '1')
                {
                    gpio_set_level(PIN_07, 1);
                    printf("Pino 7 = 1 \n");
                }
                else if (test_vector_pin_7[bit_index_pin_7] == '0')
                {
                    gpio_set_level(PIN_07, 0);
                    printf("Pino 7 = 0 \n");
                }
                start_time_pin_7 = current_time;
                bit_index_pin_7++;
            }
        }

        // Atualizar pino 8 se for hora e houver mais bits para enviar
        if (hold_time_pin_8 != 0 && test_vector_pin_8[0] != 2)
        {
            if (current_time - start_time_pin_8 >= (hold_time_pin_8 / portTICK_PERIOD_MS) && bit_index_pin_8 < 12)
            {
                if (test_vector_pin_8[bit_index_pin_8] == '1')
                {
                    gpio_set_level(PIN_08, 1);
                    printf("Pino 8 = 1 \n");
                }
                else if (test_vector_pin_8[bit_index_pin_8] == '0')
                {
                    gpio_set_level(PIN_08, 0);
                    printf("Pino 8 = 0 \n");
                }
                start_time_pin_8 = current_time;
                bit_index_pin_8++;
            }
        }

        // Atualizar pino 9 se for hora e houver mais bits para enviar
        if (hold_time_pin_9 != 0 && test_vector_pin_9[0] != 2)
        {
            if (current_time - start_time_pin_9 >= (hold_time_pin_9 / portTICK_PERIOD_MS) && bit_index_pin_9 < 12)
            {
                if (test_vector_pin_9[bit_index_pin_9] == '1')
                {
                    gpio_set_level(PIN_09, 1);
                    printf("Pino 9 = 1 \n");
                }
                else if (test_vector_pin_9[bit_index_pin_9] == '0')
                {
                    gpio_set_level(PIN_09, 0);
                    printf("Pino 9 = 0 \n");
                }
                start_time_pin_9 = current_time;
                bit_index_pin_9++;
            }
        }

        // Atualizar pino 10 se for hora e houver mais bits para enviar
        if (hold_time_pin_10 != 0 && test_vector_pin_10[0] != 2)
        {
            if (current_time - start_time_pin_10 >= (hold_time_pin_10 / portTICK_PERIOD_MS) && bit_index_pin_10 < 12)
            {
                if (test_vector_pin_10[bit_index_pin_10] == '1')
                {
                    gpio_set_level(PIN_10, 1);
                    printf("Pino 10 = 1 \n");
                }
                else if (test_vector_pin_10[bit_index_pin_10] == '0')
                {
                    gpio_set_level(PIN_10, 0);
                    printf("Pino 10 = 0 \n");
                }
                start_time_pin_10 = current_time;
                bit_index_pin_10++;
            }
        }

        // Atualizar pino 11 se for hora e houver mais bits para enviar
        if (hold_time_pin_11 != 0 && test_vector_pin_11[0] != 2)
        {
            if (current_time - start_time_pin_11 >= (hold_time_pin_11 / portTICK_PERIOD_MS) && bit_index_pin_11 < 12)
            {
                if (test_vector_pin_11[bit_index_pin_11] == '1')
                {
                    gpio_set_level(PIN_11, 1);
                    printf("Pino 11 = 1 \n");
                }
                else if (test_vector_pin_11[bit_index_pin_11] == '0')
                {
                    gpio_set_level(PIN_11, 0);
                    printf("Pino 11 = 0 \n");
                }
                start_time_pin_11 = current_time;
                bit_index_pin_11++;
            }
        }

        // Atualizar pino 12 se for hora e houver mais bits para enviar
        if (hold_time_pin_12 != 0 && test_vector_pin_12[0] != 2)
        {
            if (current_time - start_time_pin_12 >= (hold_time_pin_12 / portTICK_PERIOD_MS) && bit_index_pin_12 < 12)
            {
                if (test_vector_pin_12[bit_index_pin_12] == '1')
                {
                    gpio_set_level(PIN_12, 1);
                    printf("Pino 12 = 1 \n");
                }
                else if (test_vector_pin_12[bit_index_pin_12] == '0')
                {
                    gpio_set_level(PIN_12, 0);
                    printf("Pino 12 = 0 \n");
                }
                start_time_pin_12 = current_time;
                bit_index_pin_12++;
            }
        }

        // Atualizar pino 13 se for hora e houver mais bits para enviar
        if (hold_time_pin_13 != 0 && test_vector_pin_13[0] != 2)
        {
            if (current_time - start_time_pin_13 >= (hold_time_pin_13 / portTICK_PERIOD_MS) && bit_index_pin_13 < 12)
            {
                if (test_vector_pin_13[bit_index_pin_13] == '1')
                {
                    gpio_set_level(PIN_13, 1);
                    printf("Pino 13 = 1 \n");
                }
                else if (test_vector_pin_13[bit_index_pin_13] == '0')
                {
                    gpio_set_level(PIN_13, 0);
                    printf("Pino 13 = 0 \n");
                }
                start_time_pin_13 = current_time;
                bit_index_pin_13++;
            }
        }

        // Atualizar pino 18 se for hora e houver mais bits para enviar
        if (hold_time_pin_18 != 0 && test_vector_pin_18[0] != 2)
        {
            if (current_time - start_time_pin_18 >= (hold_time_pin_18 / portTICK_PERIOD_MS) && bit_index_pin_18 < 12)
            {
                if (test_vector_pin_18[bit_index_pin_18] == '1')
                {
                    gpio_set_level(PIN_18, 1);
                    printf("Pino 18 = 1 \n");
                }
                else if (test_vector_pin_18[bit_index_pin_18] == '0')
                {
                    gpio_set_level(PIN_18, 0);
                    printf("Pino 18 = 0 \n");
                }
                start_time_pin_18 = current_time;
                bit_index_pin_18++;
            }
        }

        // Atualizar pino 19 se for hora e houver mais bits para enviar
        if (hold_time_pin_19 != 0 && test_vector_pin_19[0] != 2)
        {
            if (current_time - start_time_pin_19 >= (hold_time_pin_19 / portTICK_PERIOD_MS) && bit_index_pin_19 < 12)
            {
                if (test_vector_pin_19[bit_index_pin_19] == '1')
                {
                    gpio_set_level(PIN_19, 1);
                    printf("Pino 19 = 1 \n");
                }
                else if (test_vector_pin_19[bit_index_pin_19] == '0')
                {
                    gpio_set_level(PIN_19, 0);
                    printf("Pino 19 = 0 \n");
                }
                start_time_pin_19 = current_time;
                bit_index_pin_19++;
            }
        }

        // Atualizar pino 20 se for hora e houver mais bits para enviar
        if (hold_time_pin_20 != 0 && test_vector_pin_20[0] != 2)
        {
            if (current_time - start_time_pin_20 >= (hold_time_pin_20 / portTICK_PERIOD_MS) && bit_index_pin_20 < 12)
            {
                if (test_vector_pin_20[bit_index_pin_20] == '1')
                {
                    gpio_set_level(PIN_20, 1);
                    printf("Pino 20 = 1 \n");
                }
                else if (test_vector_pin_20[bit_index_pin_20] == '0')
                {
                    gpio_set_level(PIN_20, 0);
                    printf("Pino 20 = 0 \n");
                }
                start_time_pin_20 = current_time;
                bit_index_pin_20++;
            }
        }

        // Atualizar pino 25 se for hora e houver mais bits para enviar
        if (hold_time_pin_25 != 0 && test_vector_pin_25[0] != 2)
        {
            if (current_time - start_time_pin_25 >= (hold_time_pin_25 / portTICK_PERIOD_MS) && bit_index_pin_25 < 12)
            {
                if (test_vector_pin_25[bit_index_pin_25] == '1')
                {
                    gpio_set_level(PIN_25, 1);
                    printf("Pino 25 = 1 \n");
                }
                else if (test_vector_pin_25[bit_index_pin_25] == '0')
                {
                    gpio_set_level(PIN_25, 0);
                    printf("Pino 25 = 0 \n");
                }
                start_time_pin_25 = current_time;
                bit_index_pin_25++;
            }
        }

        // Atualizar pino 26 se for hora e houver mais bits para enviar
        if (hold_time_pin_26 != 0 && test_vector_pin_26[0] != 2)
        {
            if (current_time - start_time_pin_26 >= (hold_time_pin_26 / portTICK_PERIOD_MS) && bit_index_pin_26 < 12)
            {
                if (test_vector_pin_26[bit_index_pin_26] == '1')
                {
                    gpio_set_level(PIN_26, 1);
                    printf("Pino 26 = 1 \n");
                }
                else if (test_vector_pin_26[bit_index_pin_26] == '0')
                {
                    gpio_set_level(PIN_26, 0);
                    printf("Pino 26 = 0 \n");
                }
                start_time_pin_26 = current_time;
                bit_index_pin_26++;
            }
        }

        // Atualizar pino 27 se for hora e houver mais bits para enviar
        if (hold_time_pin_27 != 0 && test_vector_pin_27[0] != 2)
        {
            if (current_time - start_time_pin_27 >= (hold_time_pin_27 / portTICK_PERIOD_MS) && bit_index_pin_27 < 12)
            {
                if (test_vector_pin_27[bit_index_pin_27] == '1')
                {
                    gpio_set_level(PIN_27, 1);
                    printf("Pino 27 = 1 \n");
                }
                else if (test_vector_pin_27[bit_index_pin_27] == '0')
                {
                    gpio_set_level(PIN_27, 0);
                    printf("Pino 27 = 0 \n");
                }
                start_time_pin_27 = current_time;
                bit_index_pin_27++;
            }
        }

        // Atualizar pino 29 se for hora e houver mais bits para enviar
        if (hold_time_pin_29 != 0 && test_vector_pin_29[0] != 2)
        {
            if (current_time - start_time_pin_29 >= (hold_time_pin_29 / portTICK_PERIOD_MS) && bit_index_pin_29 < 12)
            {
                if (test_vector_pin_29[bit_index_pin_29] == '1')
                {
                    gpio_set_level(PIN_29, 1);
                    printf("Pino 29 = 1 \n");
                }
                else if (test_vector_pin_29[bit_index_pin_29] == '0')
                {
                    gpio_set_level(PIN_29, 0);
                    printf("Pino 29 = 0 \n");
                }
                start_time_pin_29 = current_time;
                bit_index_pin_29++;
            }
        }

        // Atualizar pino 30 se for hora e houver mais bits para enviar
        if (hold_time_pin_30 != 0 && test_vector_pin_30[0] != 2)
        {
            if (current_time - start_time_pin_30 >= (hold_time_pin_30 / portTICK_PERIOD_MS) && bit_index_pin_30 < 12)
            {
                if (test_vector_pin_30[bit_index_pin_30] == '1')
                {
                    gpio_set_level(PIN_30, 1);
                    printf("Pino 30 = 1 \n");
                }
                else if (test_vector_pin_30[bit_index_pin_30] == '0')
                {
                    gpio_set_level(PIN_30, 0);
                    printf("Pino 30 = 0 \n");
                }
                start_time_pin_30 = current_time;
                bit_index_pin_30++;
            }
        }

        // Esperar um curto período antes de verificar novamente
        vTaskDelay(1);
    }
}

void config_freq(char *message)
{
    frequency = atoi(&message[6]);
    printf("Frequancia de %d Hz \n", frequency);
}

void reset_system()
{
    printf("\n REINICIANDO ESP... \n");
    esp_restart();
}

// ######### Funções PWM #########

// Canal 0
void config_pwm_0(char *message)
{
    int dutyCycle_ch0 = 0;
    int duty_ch0 = 0;
    double dutyCalc_ch0 = 0.0;

    printf("Configura PWM Canal 0\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch0 = atoi(&message[9]);
    dutyCalc_ch0 = (float)((dutyCycle_ch0 / 100.0) * timer_bits);
    duty_ch0 = (int)dutyCalc_ch0;

    printf("*****MENSAGEM DUTYCYCLE_ch0 de %d \n", dutyCycle_ch0);
    printf("*****DUTYCYCLE_ch0 de %f \n", dutyCalc_ch0);
    printf("*****DUTY de %d \n", duty_ch0);

    ledc_channel_config_t pwm_config_ch_0 = {
        .gpio_num = PIN_10,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_0,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_0,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_0);

    ledc_timer_config_t pwm_timer_config_ch_0 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_0,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_0);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty_ch0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

// Canal 1
void config_pwm_1(char *message)
{
    int dutyCycle_ch1 = 0;
    int duty_ch1 = 0;
    double dutyCalc_ch1 = 0.0;

    printf("Configura PWM Canal 1\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch1 = atoi(&message[9]);
    dutyCalc_ch1 = (float)((dutyCycle_ch1 / 100.0) * timer_bits);
    duty_ch1 = (int)dutyCalc_ch1;

    printf("*****MENSAGEM DUTYCYCLE_ch1 de %d \n", dutyCycle_ch1);
    printf("*****DUTYCYCLE_ch1 de %f \n", dutyCalc_ch1);
    printf("*****DUTY de %d \n", duty_ch1);

    ledc_channel_config_t pwm_config_ch_1 = {
        .gpio_num = PIN_11,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_1,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_0,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_1);

    ledc_timer_config_t pwm_timer_config_ch_1 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_0,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_1);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty_ch1);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}

// Canal 2
void config_pwm_2(char *message)
{
    int dutyCycle_ch2 = 0;
    int duty_ch2 = 0;
    double dutyCalc_ch2 = 0.0;

    printf("Configura PWM Canal 2\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch2 = atoi(&message[9]);
    dutyCalc_ch2 = (float)((dutyCycle_ch2 / 100.0) * timer_bits);
    duty_ch2 = (int)dutyCalc_ch2;

    printf("*****MENSAGEM DUTYCYCLE_ch2 de %d \n", dutyCycle_ch2);
    printf("*****DUTYCYCLE_ch2 de %f \n", dutyCalc_ch2);
    printf("*****DUTY de %d \n", duty_ch2);

    ledc_channel_config_t pwm_config_ch_2 = {
        .gpio_num = PIN_12,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_2,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_1,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_2);

    ledc_timer_config_t pwm_timer_config_ch_2 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_1,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_2);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, duty_ch2);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
}

// Canal 3
void config_pwm_3(char *message)
{
    int dutyCycle_ch3 = 0;
    int duty_ch3 = 0;
    double dutyCalc_ch3 = 0.0;

    printf("Configura PWM Canal 3\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch3 = atoi(&message[9]);
    dutyCalc_ch3 = (float)((dutyCycle_ch3 / 100.0) * timer_bits);
    duty_ch3 = (int)dutyCalc_ch3;

    printf("*****MENSAGEM DUTYCYCLE_ch3 de %d \n", dutyCycle_ch3);
    printf("*****DUTYCYCLE_ch3 de %f \n", dutyCalc_ch3);
    printf("*****DUTY de %d \n", duty_ch3);

    ledc_channel_config_t pwm_config_ch_3 = {
        .gpio_num = PIN_13,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_3,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_1,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_3);

    ledc_timer_config_t pwm_timer_config_ch_3 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_1,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_3);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, duty_ch3);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);
}

// Canal 4
void config_pwm_4(char *message)
{
    int dutyCycle_ch4 = 0;
    int duty_ch4 = 0;
    double dutyCalc_ch4 = 0.0;

    printf("Configura PWM Canal 4\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch4 = atoi(&message[9]);
    dutyCalc_ch4 = (float)((dutyCycle_ch4 / 100.0) * timer_bits);
    duty_ch4 = (int)dutyCalc_ch4;

    printf("*****MENSAGEM DUTYCYCLE_ch4 de %d \n", dutyCycle_ch4);
    printf("*****DUTYCYCLE_ch4 de %f \n", dutyCalc_ch4);
    printf("*****DUTY de %d \n", duty_ch4);

    ledc_channel_config_t pwm_config_ch_4 = {
        .gpio_num = PIN_25,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_4,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_2,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_4);

    ledc_timer_config_t pwm_timer_config_ch_4 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_2,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_4);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, duty_ch4);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
}

// Canal 5
void config_pwm_5(char *message)
{
    int dutyCycle_ch5 = 0;
    int duty_ch5 = 0;
    double dutyCalc_ch5 = 0.0;

    printf("Configura PWM Canal 5\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch5 = atoi(&message[9]);
    dutyCalc_ch5 = (float)((dutyCycle_ch5 / 100.0) * timer_bits);
    duty_ch5 = (int)dutyCalc_ch5;

    printf("*****MENSAGEM DUTYCYCLE_ch5 de %d \n", dutyCycle_ch5);
    printf("*****DUTYCYCLE_ch5 de %f \n", dutyCalc_ch5);
    printf("*****DUTY de %d \n", duty_ch5);

    ledc_channel_config_t pwm_config_ch_5 = {
        .gpio_num = PIN_26,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_5,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_2,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_5);

    ledc_timer_config_t pwm_timer_config_ch_5 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_2,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_5);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5, duty_ch5);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5);
}

// Canal 6
void config_pwm_6(char *message)
{
    int dutyCycle_ch6 = 0;
    int duty_ch6 = 0;
    double dutyCalc_ch6 = 0.0;

    printf("Configura PWM Canal 6\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch6 = atoi(&message[9]);
    dutyCalc_ch6 = (float)((dutyCycle_ch6 / 100.0) * timer_bits);
    duty_ch6 = (int)dutyCalc_ch6;

    printf("*****MENSAGEM DUTYCYCLE_ch6 de %d \n", dutyCycle_ch6);
    printf("*****DUTYCYCLE_ch6 de %f \n", dutyCalc_ch6);
    printf("*****DUTY de %d \n", duty_ch6);

    ledc_channel_config_t pwm_config_ch_6 = {
        .gpio_num = PIN_29,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_6,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_3,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_6);

    ledc_timer_config_t pwm_timer_config_ch_6 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_3,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_6);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6, duty_ch6);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6);
}

// Canal 7
void config_pwm_7(char *message)
{
    int dutyCycle_ch7 = 0;
    int duty_ch7 = 0;
    double dutyCalc_ch7 = 0.0;

    printf("Configura PWM Canal 7\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle_ch7 = atoi(&message[9]);
    dutyCalc_ch7 = (float)((dutyCycle_ch7 / 100.0) * timer_bits);
    duty_ch7 = (int)dutyCalc_ch7;

    printf("*****MENSAGEM DUTYCYCLE_ch7 de %d \n", dutyCycle_ch7);
    printf("*****DUTYCYCLE_ch7 de %f \n", dutyCalc_ch7);
    printf("*****DUTY de %d \n", duty_ch7);

    ledc_channel_config_t pwm_config_ch_7 = {
        .gpio_num = PIN_30,                 // varia conforme o pino
        .speed_mode = LEDC_LOW_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_7,          // até 8 canais
        .intr_type = LEDC_INTR_DISABLE,     // interrupção
        .timer_sel = LEDC_TIMER_3,          // pode variar timers
        .duty = 0                           // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_7);

    ledc_timer_config_t pwm_timer_config_ch_7 = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT, // Pode ter mais bits
        .timer_num = LEDC_TIMER_3,
        .freq_hz = frequency};
    ledc_timer_config(&pwm_timer_config_ch_7);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_7, duty_ch7);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_7);
}

// ########### PINOS DE LEITURA #########
void config_pin_02(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 2 será entrada de dados.\n");
        gpio_set_direction(PIN_02, GPIO_MODE_INPUT);
    }
    else
    {
        printf("Pino 2 sem uso. \n");
        gpio_set_direction(PIN_02, GPIO_MODE_DISABLE);
    }
}

void config_pin_03(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 3 será entrada de dados.\n");
        gpio_set_direction(PIN_03, GPIO_MODE_INPUT);
    }
    else
    {
        printf("Pino 3 sem uso. \n");
        gpio_set_direction(PIN_03, GPIO_MODE_DISABLE);
    }
}

void config_pin_04(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 4 será entrada de dados.\n");
        gpio_set_direction(PIN_04, GPIO_MODE_INPUT);
    }
    else
    {
        printf("Pino 4 sem uso. \n");
        gpio_set_direction(PIN_04, GPIO_MODE_DISABLE);
    }
}

void config_pin_05(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 5 será entrada de dados.\n");
        gpio_set_direction(PIN_05, GPIO_MODE_INPUT);
    }
    else
    {
        printf("Pino 5 sem uso. \n");
        gpio_set_direction(PIN_05, GPIO_MODE_DISABLE);
    }
}

void config_pin_06(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 6 será entrada de dados.\n");

        gpio_reset_pin(PIN_06);                       // Garantir reset do pino
        gpio_set_direction(PIN_06, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_06, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_6, '2', 12);             // Garante que não executa o vetor
        hold_time_pin_6 = 0;                          // Garante que não executa o vetor

        gpio_set_direction(PIN_06, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 6 sem uso. \n");
        gpio_reset_pin(PIN_06);
        gpio_set_direction(PIN_06, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_06, 0);
        memset(test_vector_pin_6, '2', 12); // Garante que não executa o vetor
        hold_time_pin_6 = 0;              // Garante que não executa o vetor
    }
    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_6, '2', 12); // Initialize the array with the value 2
        hold_time_pin_6 = 0;
        printf("Pino 6 terá vetor de teste. \n");
        gpio_set_direction(PIN_06, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_06, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_6[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_6 = hold_time_pin_6 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 6: %s\n", test_vector_pin_6);

        printf("Hold Time Pino 6: %d\n", hold_time_pin_6);
    }
}

void config_pin_07(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 7 será entrada de dados.\n");

        gpio_reset_pin(PIN_07);                       // Garantir reset do pino
        gpio_set_direction(PIN_07, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_07, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_7, '2', 12);             // garantir que não executa o vetor
        hold_time_pin_7 = 0;                          // garantir que não executa o vetor

        gpio_set_direction(PIN_07, GPIO_MODE_INPUT);
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 7 sem uso. \n");

        memset(test_vector_pin_7, '2', 12); //garantir que não executa o vetor
        hold_time_pin_7 = 0; //garantir que não executa o vetor

        gpio_reset_pin(PIN_07);
        gpio_set_direction(PIN_07, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_07, 0);
    }

    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_7, '2', 12);
        hold_time_pin_7 = 0;
        printf("Pino 7 terá vetor de teste. \n");
        gpio_set_direction(PIN_07, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_07, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_7[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_7 = hold_time_pin_7 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 7: %s\n", test_vector_pin_7);

        printf("Hold Time Pino 7: %d\n", hold_time_pin_7);
    }
}

void config_pin_08(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 8 será entrada de dados.\n");

        gpio_reset_pin(PIN_08);                       // Garantir reset do pino
        gpio_set_direction(PIN_08, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_08, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_8, '2', 12);             // garantir que não executa o vetor
        hold_time_pin_8 = 0;                          // garantir que não executa o vetor

        gpio_set_direction(PIN_08, GPIO_MODE_INPUT);
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 8 sem uso. \n");

        memset(test_vector_pin_8, '2', 12); // garantir que não executa o vetor
        hold_time_pin_8 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_08);
        gpio_set_direction(PIN_08, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_08, 0);
    }

    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_8, '2', 12); // Initialize the array with the value 2
        hold_time_pin_8 = 0;
        printf("Pino 8 terá vetor de teste. \n");
        gpio_set_direction(PIN_08, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_08, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_8[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_8 = hold_time_pin_8 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 8: %s\n", test_vector_pin_8);

        printf("Hold Time Pino 8: %d\n", hold_time_pin_8);
    }
}

void config_pin_09(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 9 será entrada de dados.\n");

        gpio_reset_pin(PIN_09);                       // Garantir reset do pino
        gpio_set_direction(PIN_09, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_09, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_9, '2', 12);             // garantir que não executa o vetor
        hold_time_pin_9 = 0;                          // garantir que não executa o vetor

        gpio_set_direction(PIN_09, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 9 sem uso. \n");

        memset(test_vector_pin_9, '2', 12); // garantir que não executa o vetor
        hold_time_pin_9 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_09);
        gpio_set_direction(PIN_09, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_09, 0);
    }

    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_9, '2', 12); // Initialize the array with the value 2
        hold_time_pin_9 = 0;
        printf("Vetor Teste Pino 9: %s\n", test_vector_pin_9);
        printf("Pino 9 terá vetor de teste. \n");
        gpio_set_direction(PIN_09, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_09, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_9[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_9 = hold_time_pin_9 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 9: %s\n", test_vector_pin_9);

        printf("Hold Time Pino 9: %d\n", hold_time_pin_9);
    }
}

void config_pin_10(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 10 será entrada de dados.\n");

        gpio_reset_pin(PIN_10);                       // Garantir reset do pino
        gpio_set_direction(PIN_10, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_10, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_10, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_10 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_10, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 10 usado para PWM. \n");
        
        memset(test_vector_pin_10, '2', 12); // garantir que não executa o vetor
        hold_time_pin_10 = 0;
        
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 10 sem uso. \n");

        memset(test_vector_pin_10, '2', 12); // garantir que não executa o vetor
        hold_time_pin_10 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_10);
        gpio_set_direction(PIN_10, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_10, 0);
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_10, '2', 12); // Initialize the array with the value 2
        hold_time_pin_10 = 0;
        printf("Vetor Teste Pino 10: %s\n", test_vector_pin_10);
        printf("Pino 10 terá vetor de teste. \n");
        gpio_set_direction(PIN_10, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_10, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_10[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_10 = hold_time_pin_10 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 10: %s\n", test_vector_pin_10);

        printf("Hold Time Pino 10: %d\n", hold_time_pin_10);
    }
}

void config_pin_11(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 11 será entrada de dados.\n");

        gpio_reset_pin(PIN_11);                       // Garantir reset do pino
        gpio_set_direction(PIN_11, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_11, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_11, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_11 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_11, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 11 usado para PWM. \n");

        memset(test_vector_pin_11, '2', 12); // garantir que não executa o vetor
        hold_time_pin_11 = 0;

    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 11 sem uso. \n");

        memset(test_vector_pin_11, '2', 12); // garantir que não executa o vetor
        hold_time_pin_11 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_11);
        gpio_set_direction(PIN_11, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_11, 0);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_11, '2', 12); // Initialize the array with the value 2
        hold_time_pin_11 = 0;
        printf("Pino 11 terá vetor de teste. \n");
        gpio_set_direction(PIN_11, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_11, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_11[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_11 = hold_time_pin_11 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 11: %s\n", test_vector_pin_11);

        printf("Hold Time Pino 11: %d\n", hold_time_pin_11);
    }
}

void config_pin_12(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 12 será entrada de dados.\n");

        gpio_reset_pin(PIN_12);                       // Garantir reset do pino
        gpio_set_direction(PIN_12, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_12, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_12, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_12 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_12, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 12 usado para PWM. \n");

        memset(test_vector_pin_12, '2', 12); // garantir que não executa o vetor
        hold_time_pin_12 = 0;

    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 12 sem uso. \n");

        memset(test_vector_pin_12, '2', 12); // garantir que não executa o vetor
        hold_time_pin_12 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_12);
        gpio_set_direction(PIN_12, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_12, 0);
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_12, '2', 12); // Initialize the array with the value 2
        hold_time_pin_12 = 0;
        printf("Pino 12 terá vetor de teste. \n");
        gpio_set_direction(PIN_12, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_12, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_12[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_12 = hold_time_pin_12 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 12: %s\n", test_vector_pin_12);

        printf("Hold Time Pino 12: %d\n", hold_time_pin_12);
    }
}

void config_pin_13(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 13 será entrada de dados.\n");

        gpio_reset_pin(PIN_13);                       // Garantir reset do pino
        gpio_set_direction(PIN_13, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_13, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_13, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_13 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_13, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 13 usado para PWM. \n");

        memset(test_vector_pin_13, '2', 12); // garantir que não executa o vetor
        hold_time_pin_13 = 0;

    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 13 sem uso. \n");

        memset(test_vector_pin_13, '2', 12); // garantir que não executa o vetor
        hold_time_pin_13 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_13);
        gpio_set_direction(PIN_13, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_13, 0);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_13, '2', 12); // Initialize the array with the value 2
        hold_time_pin_13 = 0;
        printf("Pino 13 terá vetor de teste. \n");
        gpio_set_direction(PIN_13, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_13, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_13[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_13 = hold_time_pin_13 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 13: %s\n", test_vector_pin_13);

        printf("Hold Time Pino 13: %d\n", hold_time_pin_13);
    }
}

void config_pin_18(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 18 será entrada de dados.\n");

        gpio_reset_pin(PIN_18);                       // Garantir reset do pino
        gpio_set_direction(PIN_18, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_18, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_18, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_18 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_18, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 18 sem uso. \n");

        memset(test_vector_pin_18, '2', 12); // garantir que não executa o vetor
        hold_time_pin_18 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_18);
        gpio_set_direction(PIN_18, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_18, 0);
    }
    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_18, '2', 12); // Initialize the array with the value 2
        hold_time_pin_18 = 0;
        printf("Pino 18 terá vetor de teste. \n");
        gpio_set_direction(PIN_18, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_18, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_18[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_18 = hold_time_pin_18 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 18: %s\n", test_vector_pin_18);

        printf("Hold Time Pino 18: %d\n", hold_time_pin_18);
    }
}

void config_pin_19(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 19 será entrada de dados.\n");

        gpio_reset_pin(PIN_19);                       // Garantir reset do pino
        gpio_set_direction(PIN_19, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_19, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_19, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_19 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_19, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 19 sem uso. \n");

        memset(test_vector_pin_19, '2', 12); // garantir que não executa o vetor
        hold_time_pin_19 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_19);
        gpio_set_direction(PIN_19, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_19, 0);
    }
    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_19, '2', 12); // Initialize the array with the value 2
        hold_time_pin_19 = 0;
        printf("Pino 19 terá vetor de teste. \n");
        gpio_set_direction(PIN_19, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_19, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_19[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_19 = hold_time_pin_19 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 19: %s\n", test_vector_pin_19);

        printf("Hold Time Pino 19: %d\n", hold_time_pin_19);
    }
}

void config_pin_20(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 20 será entrada de dados.\n");

        gpio_reset_pin(PIN_20);                       // Garantir reset do pino
        gpio_set_direction(PIN_20, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_20, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_20, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_20 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_20, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 20 sem uso. \n");

        memset(test_vector_pin_20, '2', 12); // garantir que não executa o vetor
        hold_time_pin_20 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_20);
        gpio_set_direction(PIN_20, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_20, 0);
    }
    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_20, '2', 12); // Initialize the array with the value 2
        hold_time_pin_20 = 0;
        printf("Pino 20 terá vetor de teste. \n");
        gpio_set_direction(PIN_20, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_20, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_20[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_20 = hold_time_pin_20 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 20: %s\n", test_vector_pin_20);

        printf("Hold Time Pino 20: %d\n", hold_time_pin_20);
    }
}

void config_pin_21(char *message)
{
    printf("Configura pino 21 \n");

    int voltage;
    sscanf(message + 4, "%dV", &voltage);
    gpio_set_direction(PIN_03V, GPIO_MODE_OUTPUT);
    if (voltage == 03)
    {
        printf("Enable 3V \n");
        gpio_set_level(PIN_03V, 1);
    }
    else
        gpio_set_level(PIN_03V, 0);
}

void config_pin_22(char *message)
{
    printf("Configura pino 22 \n");

    int voltage;
    sscanf(message + 4, "%dV", &voltage);
    gpio_set_direction(PIN_05V, GPIO_MODE_OUTPUT);
    if (voltage == 05)
    {
        printf("Enable 5V \n");
        gpio_set_level(PIN_05V, 1);
    }
    else
        gpio_set_level(PIN_05V, 0);
}

void config_pin_23(char *message)
{
    printf("Configura pino 23 \n");

    int voltage;
    sscanf(message + 4, "%dV", &voltage);
    gpio_set_direction(PIN_12V, GPIO_MODE_OUTPUT);
    if (voltage == 12)
    {
        printf("Enable 12V \n");
        gpio_set_level(PIN_12V, 1);
    }
    else
        gpio_set_level(PIN_12V, 0);
}

void config_pin_24(char *message)
{
    printf("Configura pino 24 \n");

    int voltage;
    sscanf(message + 4, "%dV", &voltage);
    gpio_set_direction(PIN_24V, GPIO_MODE_OUTPUT);
    if (voltage == 24)
    {
        printf("Enable 24V \n");
        gpio_set_level(PIN_24V, 1);
    }
    else
        gpio_set_level(PIN_24V, 0);
}

void config_pin_25(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 25 será entrada de dados.\n");

        gpio_reset_pin(PIN_25);                       // Garantir reset do pino
        gpio_set_direction(PIN_25, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_25, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_25, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_25 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_25, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 25 usado para PWM. \n");

        memset(test_vector_pin_25, '2', 12); // garantir que não executa o vetor
        hold_time_pin_25 = 0;

    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 25 sem uso. \n");

        memset(test_vector_pin_25, '2', 12); // garantir que não executa o vetor
        hold_time_pin_25 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_25);
        gpio_set_direction(PIN_25, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_25, 0);
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_25, '2', 12); // Initialize the array with the value 2
        hold_time_pin_25 = 0;
        printf("Pino 25 terá vetor de teste. \n");
        gpio_set_direction(PIN_25, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_25, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_25[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_25 = hold_time_pin_25 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 25: %s\n", test_vector_pin_25);

        printf("Hold Time Pino 25: %d\n", hold_time_pin_25);
    }
}

void config_pin_26(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 26 será entrada de dados.\n");

        gpio_reset_pin(PIN_26);                       // Garantir reset do pino
        gpio_set_direction(PIN_26, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_26, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_26, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_26 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_26, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 26 usado para PWM. \n");

        memset(test_vector_pin_26, '2', 12); // garantir que não executa o vetor
        hold_time_pin_26 = 0;

    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 26 sem uso. \n");

        memset(test_vector_pin_26, '2', 12); // garantir que não executa o vetor
        hold_time_pin_26 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_26);
        gpio_set_direction(PIN_26, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_26, 0);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_26, '2', 12); // Initialize the array with the value 2
        hold_time_pin_26 = 0;
        printf("Pino 26 terá vetor de teste. \n");
        gpio_set_direction(PIN_26, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_26, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_26[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_26 = hold_time_pin_26 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 26: %s\n", test_vector_pin_26);

        printf("Hold Time Pino 26: %d\n", hold_time_pin_26);
    }
}

void config_pin_27(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 27 será entrada de dados.\n");

        gpio_reset_pin(PIN_27);                       // Garantir reset do pino
        gpio_set_direction(PIN_27, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_27, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_27, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_27 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_27, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0')
    {
        printf("Pino 27 sem uso. \n");

        memset(test_vector_pin_27, '2', 12); // garantir que não executa o vetor
        hold_time_pin_27 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_27);
        gpio_set_direction(PIN_27, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_27, 0);
    }
    if (message[5] == '0' && message[9] != ',')
    {
        memset(test_vector_pin_27, '2', 12); // Initialize the array with the value 2
        hold_time_pin_27 = 0;
        printf("Pino 27 terá vetor de teste. \n");
        gpio_set_direction(PIN_27, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_27, 0);

        for (int i = 8; i <= 19; i++)
        {
            test_vector_pin_27[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_27 = hold_time_pin_27 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 27: %s\n", test_vector_pin_27);

        printf("Hold Time Pino 27: %d\n", hold_time_pin_27);
    }
}

void config_pin_29(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 29 será entrada de dados.\n");

        gpio_reset_pin(PIN_29);                       // Garantir reset do pino
        gpio_set_direction(PIN_29, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_29, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_29, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_29 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_29, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 29 usado para PWM. \n");

        memset(test_vector_pin_29, '2', 12); // garantir que não executa o vetor
        hold_time_pin_29 = 0;

    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 29 sem uso. \n");

        memset(test_vector_pin_29, '2', 12); // garantir que não executa o vetor
        hold_time_pin_29 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_29);
        gpio_set_direction(PIN_29, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_29, 0);
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_29, '2', 12); // Initialize the array with the value 2
        hold_time_pin_29 = 0;
        printf("Pino 29 terá vetor de teste. \n");
        gpio_set_direction(PIN_29, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_29, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_29[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_29 = hold_time_pin_29 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 29: %s\n", test_vector_pin_29);

        printf("Hold Time Pino 29: %d\n", hold_time_pin_29);
    }
}

void config_pin_30(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 30 será entrada de dados.\n");

        gpio_reset_pin(PIN_30);                       // Garantir reset do pino
        gpio_set_direction(PIN_30, GPIO_MODE_OUTPUT); // Garantir nível baixo no pino
        gpio_set_level(PIN_30, 0);                    // Garantir nível baixo no pino
        memset(test_vector_pin_30, '2', 12);            // garantir que não executa o vetor
        hold_time_pin_30 = 0;                         // garantir que não executa o vetor

        gpio_set_direction(PIN_30, GPIO_MODE_INPUT);
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 30 usado para PWM. \n");

        memset(test_vector_pin_30, '2', 12); // garantir que não executa o vetor
        hold_time_pin_30 = 0;
    
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11] == '0' && message[12] == ',')
    {
        printf("Pino 30 sem uso. \n");

        memset(test_vector_pin_30, '2', 12); // garantir que não executa o vetor
        hold_time_pin_30 = 0;              // garantir que não executa o vetor

        gpio_reset_pin(PIN_30);
        gpio_set_direction(PIN_30, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_30, 0);
    }

    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        memset(test_vector_pin_30, '2', 12); // Initialize the array with the value 2
        hold_time_pin_30 = 0;
        printf("Pino 30 terá vetor de teste. \n");
        gpio_set_level(PIN_30, 0);

        for (int i = 11; i <= 22; i++)
        {
            test_vector_pin_30[i - 11] = message[i];
        }

        int hold_time_index = 25; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9')
        {
            hold_time_pin_30 = hold_time_pin_30 * 10 + (message[hold_time_index] - '0');
            hold_time_index++;
        }

        printf("Vetor Teste Pino 30: %s\n", test_vector_pin_30);

        printf("Hold Time Pino 30: %d\n", hold_time_pin_30);
    }
}

void process_pin_config(char *message)
{
    printf("\n CONFIGURAR TESTE\n");
}

static void udp_server_task(void *pvParameters)
{
    char rx_buffer[1500];
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    struct sockaddr_in6 dest_addr;

    while (1)
    {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(PORT);
        ip_protocol = IPPROTO_IP;

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created");

        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0)
        {
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        }
        ESP_LOGI(TAG, "Socket bound, port %d", PORT);

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t socklen = sizeof(source_addr);

        while (1)
        {
            ESP_LOGI(TAG, "Waiting for data");
            int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);

            if (len > 0)
            {

                // Get the sender's ip address as string
                inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
                rx_buffer[len] = 0; // Null-terminate
                ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
                ESP_LOGI(TAG, "%s", rx_buffer);

                if (rx_buffer[1] == 'F' && rx_buffer[2] == 'R')
                {
                    config_freq(rx_buffer);
                }

                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '0' && rx_buffer[6] == '1')
                {
                    config_pwm_0(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '1' && rx_buffer[6] == '1')
                {
                    config_pwm_1(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '2' && rx_buffer[6] == '1')
                {
                    config_pwm_2(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '3' && rx_buffer[6] == '1')
                {
                    config_pwm_3(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '4' && rx_buffer[6] == '1')
                {
                    config_pwm_4(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '5' && rx_buffer[6] == '1')
                {
                    config_pwm_5(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '6' && rx_buffer[6] == '1')
                {
                    config_pwm_6(rx_buffer);
                }
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '7' && rx_buffer[6] == '1')
                {
                    config_pwm_7(rx_buffer);
                }

                if (rx_buffer[1] == '0' && rx_buffer[2] == '2')
                {
                    config_pin_02(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '3')
                {
                    config_pin_03(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '4')
                {
                    config_pin_04(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '5')
                {
                    config_pin_05(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '6')
                {
                    config_pin_06(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '7')
                {
                    config_pin_07(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '8')
                {
                    config_pin_08(rx_buffer);
                }
                if (rx_buffer[1] == '0' && rx_buffer[2] == '9')
                {
                    config_pin_09(rx_buffer);
                }
                if (rx_buffer[1] == '1' && rx_buffer[2] == '0')
                {
                    config_pin_10(rx_buffer);
                }
                if (rx_buffer[1] == '1' && rx_buffer[2] == '1')
                {
                    config_pin_11(rx_buffer);
                }
                if (rx_buffer[1] == '1' && rx_buffer[2] == '2')
                {
                    config_pin_12(rx_buffer);
                }
                if (rx_buffer[1] == '1' && rx_buffer[2] == '3')
                {
                    config_pin_13(rx_buffer);
                }
                if (rx_buffer[1] == '1' && rx_buffer[2] == '8')
                {
                    config_pin_18(rx_buffer);
                }
                if (rx_buffer[1] == '1' && rx_buffer[2] == '9')
                {
                    config_pin_19(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '0')
                {
                    config_pin_20(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '1')
                {
                    config_pin_21(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '2')
                {
                    config_pin_22(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '3')
                {
                    config_pin_23(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '4')
                {
                    config_pin_24(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '5')
                {
                    config_pin_25(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '6')
                {
                    config_pin_26(rx_buffer);
                }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '7')
                {
                    config_pin_27(rx_buffer);
                }
                // if (rx_buffer[1] == '2' && rx_buffer[2] == '8')
                // {
                //     config_pin_28(rx_buffer);
                // }
                if (rx_buffer[1] == '2' && rx_buffer[2] == '9')
                {
                    config_pin_29(rx_buffer);
                }
                if (rx_buffer[1] == '3' && rx_buffer[2] == '0')
                {
                    config_pin_30(rx_buffer);
                }

                if (strstr(rx_buffer, "START") != NULL)
                {
                    start_test();
                }

                if (strstr(rx_buffer, "RESET") != NULL)
                {
                    reset_system();
                }

                sendto(sock, rx_buffer, len, 0, (struct sockaddr *)&source_addr, sizeof(source_addr));
            }
            else
            {
                ESP_LOGI(TAG, "Did not received data");
            }
        }

        if (sock != -1)
        {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting WIFI_EVENT_STA_START ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected WIFI_EVENT_STA_CONNECTED ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection WIFI_EVENT_STA_DISCONNECTED ... \n");
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
        break;
    default:
        break;
    }
}

void wifi_connection()
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = "Daniel",
            .password = "laranjas"}};
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
    esp_wifi_connect();
}

void app_main(void)
{
    wifi_connection();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    xTaskCreate(udp_server_task, "udp_server", 4096, (void *)AF_INET, 5, NULL);
}