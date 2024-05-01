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
#define PIN_10 GPIO_NUM_27 //PWM CH0
#define PIN_11 GPIO_NUM_14 //PWM CH1
#define PIN_12 GPIO_NUM_12 //PWM CH2
#define PIN_13 GPIO_NUM_13 //PWM CH3
#define PIN_18 GPIO_NUM_15
#define PIN_19 GPIO_NUM_2 
#define PIN_20 GPIO_NUM_4 
#define PIN_25 GPIO_NUM_19 //PWM CH4
#define PIN_26 GPIO_NUM_21 //PWM CH5
#define PIN_27 GPIO_NUM_3
//#define PIN_28 GPIO_NUM_1
#define PIN_29 GPIO_NUM_22 //PWM CH6
#define PIN_30 GPIO_NUM_23 //PWM CH7

// #define set_duty(duty) ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty)
// #define upt_duty ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0)


#define PORT 3333
static const char *TAG = "UDP SOCKET SERVER";

//Variáveis Globais
int frequency = 0;
int timer_bits = 8191; //2^13

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
    //int frequency;
    int duty_cycle;
    char test_vector[12];
    int bit_hold_time;
} PinConfig;

typedef struct
{
    int pin;
    int voltage;
} VoltageConfig;


// void start_test(){

//     printf("START TESTE\n");

//     if (hold_time_pin_6 != 0 && test_vector_pin_6[0] != 2)
//     {
//         TickType_t start_time = xTaskGetTickCount(); //1000
//         TickType_t elapsed_time = 0;

//         printf("START TIME: %ld \n", start_time);
        

//         for (int i = 0; i < 12; i++)
//         {
//             printf("TEST_VECTOR PIN 6: %c \n", test_vector_pin_6[i]);
//             if (test_vector_pin_6[i]=='1')
//             {
//                 gpio_set_level(PIN_06, 1);
//             }

//             if (test_vector_pin_6[i]=='0')
//             {
//                 gpio_set_level(PIN_06, 0);
//             }

//             elapsed_time = xTaskGetTickCount() - start_time;
//             printf("ELAPSED TIME: %ld \n", elapsed_time);

//             if (elapsed_time >= (hold_time_pin_6 * 1000) / portTICK_PERIOD_MS)
//             {
//                 start_time = xTaskGetTickCount();
//                 // Add any code here that needs to be executed every hold_time_pin_6 milliseconds
//             }
//         }
//     }   
// }

void start_test(){

    printf("START TESTE\n");

    if (hold_time_pin_6 != 0 && test_vector_pin_6[0] != 2){
        TickType_t start_time = xTaskGetTickCount();
        TickType_t elapsed_time = 0;

        for (int i = 0; i < 12; i++)
        {
            printf("START TIME: %ld \n", start_time);
            printf("TEST_VECTOR PIN 6: %c \n", test_vector_pin_6[i]);
            if (test_vector_pin_6[i]=='1'){
                gpio_set_level(PIN_06, 1);
            }

            if (test_vector_pin_6[i]=='0'){
                gpio_set_level(PIN_06, 0);
            }

            elapsed_time = xTaskGetTickCount() - start_time;

            if (elapsed_time >= hold_time_pin_6  / portTICK_PERIOD_MS){
                start_time = xTaskGetTickCount();
            }
            
            while ((xTaskGetTickCount() - start_time) < (hold_time_pin_6 / portTICK_PERIOD_MS)){
                vTaskDelay(1); // Espera 1 milissegundo, não sei como fazer para continuar o código sem esperar
            }
            printf("ELAPSED TIME: %ld \n", (xTaskGetTickCount() - start_time));
            // Atualize o tempo de início do loop atual
            start_time = xTaskGetTickCount();
        }
    }   
}

// add lógica ao pino 7 e tentar fazer o vetor funcionar


void config_freq(char *message){
    frequency = atoi(&message[6]);
    printf("Frequancia de %d Hz \n", frequency);    
}

void reset_system(){
    printf("\n REINICIANDO ESP... \n");
    esp_restart();
}

// ######### Funções PWM #########

// Canal 0
void config_pwm_0(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 0\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_0 = {
        .gpio_num = PIN_10, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_0, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_0);


    ledc_timer_config_t pwm_timer_config_ch_0 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_0);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);

}

// Canal 1
void config_pwm_1(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 1\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_1 = {
        .gpio_num = PIN_11, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_1, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_1);


    ledc_timer_config_t pwm_timer_config_ch_1 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_1);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
}

// Canal 2
void config_pwm_2(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 2\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_2 = {
        .gpio_num = PIN_12, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_2, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_2);


    ledc_timer_config_t pwm_timer_config_ch_2 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_2);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
}

// Canal 3
void config_pwm_3(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 3\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_3 = {
        .gpio_num = PIN_13, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_3, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_3);


    ledc_timer_config_t pwm_timer_config_ch_3 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_3);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
}

// Canal 4
void config_pwm_4(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 4\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_4 = {
        .gpio_num = PIN_25, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_4, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_4);


    ledc_timer_config_t pwm_timer_config_ch_4 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_4);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);
}

// Canal 5
void config_pwm_5(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 5\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_5 = {
        .gpio_num = PIN_26, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_5, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_5);


    ledc_timer_config_t pwm_timer_config_ch_5 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_5);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
}

// Canal 6
void config_pwm_6(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 6\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_6 = {
        .gpio_num = PIN_29, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_6, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_6);


    ledc_timer_config_t pwm_timer_config_ch_6 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_6);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
}

// Canal 7
void config_pwm_7(char *message){
    int dutyCycle = 0;
    int duty = 0;
    double dutyCalc = 0.0;

    printf("Configura PWM Canal 7\n");
    printf("Frequancia de %d Hz \n", frequency);

    dutyCycle = atoi(&message[9]);
    dutyCalc = (float)((dutyCycle/100.0)*timer_bits);
    duty = (int)dutyCalc;

    printf("*****MENSAGEM DUTYCYCLE de %d \n", dutyCycle);
    printf("*****DUTYCYCLE de %f \n", dutyCalc);
    printf("*****DUTY de %d \n", duty);

    ledc_channel_config_t pwm_config_ch_7 = {
        .gpio_num = PIN_30, //varia conforme o pino
        .speed_mode = LEDC_HIGH_SPEED_MODE, // pode ser escolhido
        .channel = LEDC_CHANNEL_7, // até 8 canais
        .intr_type = LEDC_INTR_DISABLE, //interrupção
        .timer_sel = LEDC_TIMER_0, //pode variar timers
        .duty = 0 // dutycicle inicial
    };
    ledc_channel_config(&pwm_config_ch_7);


    ledc_timer_config_t pwm_timer_config_ch_7 = {
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT, //Pode ter mais bits
    .timer_num = LEDC_TIMER_0,
    .freq_hz = frequency
    };
    ledc_timer_config(&pwm_timer_config_ch_7);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7);
}


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
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 6 sem uso. \n");
        gpio_reset_pin(PIN_06);
        gpio_set_direction(PIN_06, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_06, 0);
    }
    if (message[5] == '0' && message[9]!= ',')
    {
        memset(test_vector_pin_6, 2, 12); // Initialize the array with the value 2
        hold_time_pin_6 = 0;
        printf("Pino 6 terá vetor de teste. \n");
        gpio_set_direction(PIN_06, GPIO_MODE_OUTPUT);

        for (int i = 8; i <= 19; i++) {
            test_vector_pin_6[i - 8] = message[i];
        }

        int hold_time_index = 22; // Onde o valor do hold_time começa na mensagem
        while (message[hold_time_index] != '\0' && message[hold_time_index] != '\n' && message[hold_time_index] >= '0' && message[hold_time_index] <= '9') {
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
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 7 sem uso. \n");
        gpio_reset_pin(PIN_07);
        gpio_set_direction(PIN_07, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_07, 0);
    }
}
void config_pin_08(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 8 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 8 sem uso. \n");
        gpio_reset_pin(PIN_08);
        gpio_set_direction(PIN_08, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_08, 0);
    }
}
void config_pin_09(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 9 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 9 sem uso. \n");
        gpio_reset_pin(PIN_09);
        gpio_set_direction(PIN_09, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_09, 0);
    }
}

void config_pin_10(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 10 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 10 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 10 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 10 sem uso. \n");
        gpio_reset_pin(PIN_10);
        gpio_set_direction(PIN_10, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_10, 0);
    }
}

void config_pin_11(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 11 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 11 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 11 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 11 sem uso. \n");
        gpio_reset_pin(PIN_11);
        gpio_set_direction(PIN_11, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_11, 0);
    }
}

void config_pin_12(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 12 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 12 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 12 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 12 sem uso. \n");
        gpio_reset_pin(PIN_12);
        gpio_set_direction(PIN_12, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_12, 0);
    }
}

void config_pin_13(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 13 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 13 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 13 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 13 sem uso. \n");
        gpio_reset_pin(PIN_13);
        gpio_set_direction(PIN_13, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_13, 0);
    }
}

void config_pin_18(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 18 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 18 sem uso. \n");
        gpio_reset_pin(PIN_18);
        gpio_set_direction(PIN_18, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_18, 0);
    }
}
void config_pin_19(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 19 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 19 sem uso. \n");
        gpio_reset_pin(PIN_19);
        gpio_set_direction(PIN_19, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_19, 0);
    }
}
void config_pin_20(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 20 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 20 sem uso. \n");
        gpio_reset_pin(PIN_20);
        gpio_set_direction(PIN_20, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_20, 0);
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
    else gpio_set_level(PIN_03V, 0);
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
    else gpio_set_level(PIN_05V, 0);
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
    else gpio_set_level(PIN_12V, 0);
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
    else gpio_set_level(PIN_24V, 0);
}

void config_pin_25(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 25 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 25 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 25 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 25 sem uso. \n");
        gpio_reset_pin(PIN_25);
        gpio_set_direction(PIN_25, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_25, 0);
    }
}

void config_pin_26(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 26 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 26 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 26 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 26 sem uso. \n");
        gpio_reset_pin(PIN_26);
        gpio_set_direction(PIN_26, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_26, 0);
    }
}

void config_pin_27(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 27 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
        printf("Pino 27 sem uso. \n");
        gpio_reset_pin(PIN_27);
        gpio_set_direction(PIN_27, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_27, 0);
    }
}

// void config_pin_28(char *message)
// {
//     if (message[5] == '1')
//     {
//         printf("Pino 28 será entrada de dados.\n");
//     }
//     if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0'){
//         printf("Pino 28 sem uso. \n");
//     }
// }

void config_pin_29(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 29 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 29 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 29 com vetor de teste. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 29 sem uso. \n");
        gpio_reset_pin(PIN_29);
        gpio_set_direction(PIN_29, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_29, 0);
    }
}


void config_pin_30(char *message)
{
    if (message[5] == '1')
    {
        printf("Pino 30 será entrada de dados.\n");
    }
    if (message[5] == '0' && message[8] == '1')
    {
        printf("Pino 30 usado para PWM. \n");
    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[12] != ',')
    {
        printf("Pino 30 com vetor de teste. \n");

    }
    if (message[5] == '0' && message[8] == '0' && message[9] == ',' && message[11]== '0' && message[12] == ',')
    {
        printf("Pino 30 sem uso. \n");
        gpio_reset_pin(PIN_30);
        gpio_set_direction(PIN_30, GPIO_MODE_OUTPUT);
        gpio_set_level(PIN_30, 0);
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
                if (rx_buffer[1] == 'C' && rx_buffer[2] == 'H' && rx_buffer[3] == '7'&& rx_buffer[6] == '1' )
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