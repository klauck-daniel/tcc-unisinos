// UDP SOCKET Server with WiFi connection communication via Socket

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

#define PIN_06 GPIO_NUM_32

#define set_duty(duty) ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty)
#define upt_duty ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0)


#define PORT 3333
static const char *TAG = "UDP SOCKET SERVER";

//Variáveis Globais
int frequency = 0;

// void pwm_set(void);
// void pwm_update_duty(void);









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


// Função PWM
void pwm_set(int frequency){
//void pwm_set(int frequency, int channel, int duty, int pin){

    ledc_channel_config_t pwm_channel_config = {0};
    pwm_channel_config.gpio_num = PIN_06; //varia conforme o pino
    pwm_channel_config.speed_mode = LEDC_HIGH_SPEED_MODE; // pode ser escolhido
    pwm_channel_config.channel = LEDC_CHANNEL_0; // até 8 canais
    pwm_channel_config.intr_type = LEDC_INTR_DISABLE; //interrupção
    pwm_channel_config.timer_sel = LEDC_TIMER_0; //pode variar timers
    pwm_channel_config.duty = 0; // dutycicle inicial

    ledc_channel_config(&pwm_channel_config);


    ledc_timer_config_t pwm_timer_config = {0};
    pwm_timer_config.speed_mode = LEDC_HIGH_SPEED_MODE;
    pwm_timer_config.duty_resolution = LEDC_TIMER_12_BIT; //Pode ter mais bits
    pwm_timer_config.timer_num = LEDC_TIMER_0;
    pwm_timer_config.freq_hz = 5000;

    ledc_timer_config(&pwm_timer_config);

}



void start_test()
{
    printf("\n START TESTE\n");
}

void config_freq(char *message){
    frequency = atoi(&message[6]);
    printf("Frequancia de %d Hz \n", frequency);

    pwm_set(frequency);
    set_duty(4091);
    upt_duty;
    
}

void config_pin_02(char *message)
{
    printf("Configura pino 02 \n");
}
void config_pin_03(char *message)
{
    printf("Configura pino 03 \n");
}

void config_pin_04(char *message)
{
    printf("Configura pino 04 \n");
}

void config_pin_05(char *message)
{
    printf("Configura pino 05 \n");
}

void config_pin_06(char *message)
{
    printf("Configura pino 06 \n");
}
void config_pin_07(char *message)
{
    printf("Configura pino 07 \n");
}
void config_pin_08(char *message)
{
    printf("Configura pino 08 \n");
}
void config_pin_09(char *message)
{
    printf("Configura pino 09 \n");
}
void config_pin_10(char *message)
{
    printf("Configura pino 10 \n");
}
void config_pin_11(char *message)
{
    printf("Configura pino 11 \n");
}
void config_pin_12(char *message)
{
    printf("Configura pino 12 \n");
}
void config_pin_13(char *message)
{
    printf("Configura pino 13 \n");
}
void config_pin_18(char *message)
{
    printf("Configura pino 18 \n");
}
void config_pin_19(char *message)
{
    printf("Configura pino 19 \n");
}
void config_pin_20(char *message)
{
    printf("Configura pino 20 \n");
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
    printf("Configura pino 25 \n");
}
void config_pin_26(char *message)
{
    printf("Configura pino 26 \n");
}
void config_pin_27(char *message)
{
    printf("Configura pino 27 \n");
}
void config_pin_28(char *message)
{
    printf("Configura pino 28 \n");
}
void config_pin_29(char *message)
{
    printf("Configura pino 29 \n");
}
void config_pin_30(char *message)
{
    printf("Configura pino 30 \n");
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
                if (rx_buffer[1] == '2' && rx_buffer[2] == '8')
                {
                    config_pin_28(rx_buffer);
                }
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