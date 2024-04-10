from enviaMensagemUDP import envia_mensagem_udp
from guizero import App, Text, PushButton, CheckBox, TextBox, Slider, Box

#Variáveis Globais
esp_ip = "192.168.1.25" 
esp_porta = 3333
pinos_valores = {}

freq_min = 100
freq_max = 2000

# Pinos disponíveis
available_pins = [2,  3,  6,  7,
                  8,  9,  10, 11,
                  12, 13, 18, 19,
                  20, 23, 24, 25,
                  26, 27, 28]


# Functions
def start_test():
    print("Iniciando teste.")
    configuracao_pino_2()
    configuracao_pino_3()
    configuracao_pino_6()
    configuracao_pino_7()
    configuracao_pino_8()
    configuracao_pino_9()
    configuracao_pino_10()
    configuracao_pino_11()
    configuracao_pino_12()
    configuracao_pino_13()
    configuracao_pino_18()
    configuracao_pino_20()
    configuracao_pino_23()
    configuracao_pino_24()
    configuracao_pino_25()
    configuracao_pino_26()
    configuracao_pino_27()
    configuracao_pino_28()
    
    envia_mensagem_udp(esp_ip, esp_porta, pinos_valores)

# App
app = App(title="ATE DRK", width=1600, height=900)
app.full_screen = False

# Title Box
title_box = Box(app, width="fill", align="top", border=True)
Text(title_box, text="Parametrização do Teste")

# Content Box
content_box = Box(app, align = "top", layout = "grid", grid = [0, 0], width = "fill", border = True)

# Tensão
voltage_box = Box(content_box,
                  layout = "grid",
                  grid = [0, 0],
                  width = "fill",
                  align = "left",
                  border = True)
Text(voltage_box, text = "Tensões Disponíveis:", grid = [0, 0], align = "left")

# Pinos 4, 5, 21, 22 serão para selecionar a tensão
voltage_options = ["3V", "5V", "12V", "24V"]
voltage_checkboxes = [
    CheckBox(
        voltage_box,
        text=voltage,
        align="left",
        grid = [i + 1, 0] ) for i, voltage in enumerate(voltage_options)
]

# Parametros
parametros_box = Box(content_box, layout="grid", width="fill", height="fill",
                     align="left", border=True, grid=[0, 1])
Text(parametros_box, text="Parâmetros dos Pinos:", grid=[0, 0], align="left")

# Pinos disponíveis
available_pins = [2,  3,  6,  7,
                  8,  9,  10, 11,
                  12, 13, 18, 19,
                  20, 23, 24, 25,
                  26, 27, 28]


### Configuração Pino 2 ####
pin_box_2 = Box(parametros_box, layout="grid", grid=[0, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_2, width = 15, text="Pino 2:", grid=[0, 0], align="left")

Text(pin_box_2, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_2 = CheckBox(pin_box_2, text="", align="left", grid=[1, 2])

Text(pin_box_2, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_2 = CheckBox(
    pin_box_2, text="", align="left", grid=[1, 3])

Text(pin_box_2, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_2 = TextBox(pin_box_2, width=5, grid=[1, 4], align="left")

Text(pin_box_2, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_2 = Slider(
    pin_box_2, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_2, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_2 = TextBox(pin_box_2, width = 20, grid = [1, 6], align="left")

Text(pin_box_2, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_2 = TextBox(pin_box_2, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_2, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_2():
    app.after(1500, valida_frequencia_2)

def valida_frequencia_2():
    try:
        freq = int(freq_input_2.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 2: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_2.value = ""  

freq_input_2.when_key_pressed = schedule_frequency_validation_2

def configuracao_pino_2():
    pin_saida_2 = 1 if pin_output_checkbox_2.value else 0
    pin_leitura_2 = 1 if result_pin_output_checkbox_2.value else 0
    duty_cycle_2 = int(duty_cycle_slider_2.value)
    config_pino_2 = [
        pin_saida_2,
        pin_leitura_2,
        freq_input_2.value if freq_input_2.value else 0,
        duty_cycle_2,
        test_vector_input_2.value if test_vector_input_2.value else 0,
        bit_hold_time_2.value if bit_hold_time_2.value else 0
    ]
    pinos_valores["pino_2"] = config_pino_2


#### Configuração Pino 3 ####
pin_box_3 = Box(parametros_box, layout="grid", grid=[0, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_3, width = 15, text="Pino 3:", grid=[0, 0], align="left")

Text(pin_box_3, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_3 = CheckBox(pin_box_3, text="", align="left", grid=[1, 2])

Text(pin_box_3, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_3 = CheckBox(
    pin_box_3, text="", align="left", grid=[1, 3])

Text(pin_box_3, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_3 = TextBox(pin_box_3, width=5, grid=[1, 4], align="left")

Text(pin_box_3, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_3 = Slider(
    pin_box_3, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_3, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_3 = TextBox(pin_box_3, width = 20, grid = [1, 6], align="left")

Text(pin_box_3, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_3 = TextBox(pin_box_3, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_3, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_3():
    app.after(1500, valida_frequencia_3)

def valida_frequencia_3():
    try:
        freq = int(freq_input_3.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 3: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_3.value = ""  

freq_input_3.when_key_pressed = schedule_frequency_validation_3

def configuracao_pino_3():
    pin_saida_3 = 1 if pin_output_checkbox_3.value else 0
    pin_leitura_3 = 1 if result_pin_output_checkbox_3.value else 0
    duty_cycle_3 = int(duty_cycle_slider_3.value)
    config_pino_3 = [
        pin_saida_3,
        pin_leitura_3,
        freq_input_3.value if freq_input_3.value else 0,
        duty_cycle_3,
        test_vector_input_3.value if test_vector_input_3.value else 0,
        bit_hold_time_3.value if bit_hold_time_3.value else 0
    ]
    pinos_valores["pino_3"] = config_pino_3


#### Configuração Pino 6 ####
pin_box_6 = Box(parametros_box, layout="grid", grid=[0, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_6, width = 15, text="Pino 6:", grid=[0, 0], align="left")

Text(pin_box_6, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_6 = CheckBox(pin_box_6, text="", align="left", grid=[1, 2])

Text(pin_box_6, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_6 = CheckBox(
    pin_box_6, text="", align="left", grid=[1, 3])

Text(pin_box_6, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_6 = TextBox(pin_box_6, width=5, grid=[1, 4], align="left")

Text(pin_box_6, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_6 = Slider(
    pin_box_6, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_6, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_6 = TextBox(pin_box_6, width = 20, grid = [1, 6], align="left")

Text(pin_box_6, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_6 = TextBox(pin_box_6, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_6, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_6():
    app.after(1500, valida_frequencia_6)

def valida_frequencia_6():
    try:
        freq = int(freq_input_6.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 6: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_6.value = ""  

freq_input_6.when_key_pressed = schedule_frequency_validation_6

def configuracao_pino_6():
    pin_saida_6 = 1 if pin_output_checkbox_6.value else 0
    pin_leitura_6 = 1 if result_pin_output_checkbox_6.value else 0
    duty_cycle_6 = int(duty_cycle_slider_6.value)
    config_pino_6 = [
        pin_saida_6,
        pin_leitura_6,
        freq_input_6.value if freq_input_6.value else 0,
        duty_cycle_6,
        test_vector_input_6.value if test_vector_input_6.value else 0,
        bit_hold_time_6.value if bit_hold_time_6.value else 0
    ]
    pinos_valores["pino_6"] = config_pino_6


#### Configuração Pino 7 ####
pin_box_7 = Box(parametros_box, layout="grid", grid=[0, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_7, width = 15, text="Pino 7:", grid=[0, 0], align="left")

Text(pin_box_7, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_7 = CheckBox(pin_box_7, text="", align="left", grid=[1, 2])

Text(pin_box_7, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_7 = CheckBox(
    pin_box_7, text="", align="left", grid=[1, 3])

Text(pin_box_7, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_7 = TextBox(pin_box_7, width=5, grid=[1, 4], align="left")

Text(pin_box_7, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_7 = Slider(
    pin_box_7, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_7, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_7 = TextBox(pin_box_7, width = 20, grid = [1, 6], align="left")

Text(pin_box_7, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_7 = TextBox(pin_box_7, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_7, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_7():
    app.after(1500, valida_frequencia_7)

def valida_frequencia_7():
    try:
        freq = int(freq_input_7.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 7: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_7.value = ""  

freq_input_7.when_key_pressed = schedule_frequency_validation_7

def configuracao_pino_7():
    pin_saida_7 = 1 if pin_output_checkbox_7.value else 0
    pin_leitura_7 = 1 if result_pin_output_checkbox_7.value else 0
    duty_cycle_7 = int(duty_cycle_slider_7.value)
    config_pino_7 = [
        pin_saida_7,
        pin_leitura_7,
        freq_input_7.value if freq_input_7.value else 0,
        duty_cycle_7,
        test_vector_input_7.value if test_vector_input_7.value else 0,
        bit_hold_time_7.value if bit_hold_time_7.value else 0
    ]
    pinos_valores["pino_7"] = config_pino_7


#### Configuração Pino 8 ####
pin_box_8 = Box(parametros_box, layout="grid", grid=[1, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_8, width = 15, text="Pino 8:", grid=[0, 0], align="left")

Text(pin_box_8, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_8 = CheckBox(pin_box_8, text="", align="left", grid=[1, 2])

Text(pin_box_8, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_8 = CheckBox(
    pin_box_8, text="", align="left", grid=[1, 3])

Text(pin_box_8, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_8 = TextBox(pin_box_8, width=5, grid=[1, 4], align="left")

Text(pin_box_8, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_8 = Slider(
    pin_box_8, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_8, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_8 = TextBox(pin_box_8, width = 20, grid = [1, 6], align="left")

Text(pin_box_8, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_8 = TextBox(pin_box_8, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_8, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_8():
    app.after(1500, valida_frequencia_8)

def valida_frequencia_8():
    try:
        freq = int(freq_input_8.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 8: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_8.value = ""  

freq_input_8.when_key_pressed = schedule_frequency_validation_8

def configuracao_pino_8():
    pin_saida_8 = 1 if pin_output_checkbox_8.value else 0
    pin_leitura_8 = 1 if result_pin_output_checkbox_8.value else 0
    duty_cycle_8 = int(duty_cycle_slider_8.value)
    config_pino_8 = [
        pin_saida_8,
        pin_leitura_8,
        freq_input_8.value if freq_input_8.value else 0,
        duty_cycle_8,
        test_vector_input_8.value if test_vector_input_8.value else 0,
        bit_hold_time_8.value if bit_hold_time_8.value else 0
    ]
    pinos_valores["pino_8"] = config_pino_8


#### Configuração Pino 9 ####
pin_box_9 = Box(parametros_box, layout="grid", grid=[1, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_9, width = 15, text="Pino 9:", grid=[0, 0], align="left")

Text(pin_box_9, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_9 = CheckBox(pin_box_9, text="", align="left", grid=[1, 2])

Text(pin_box_9, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_9 = CheckBox(
    pin_box_9, text="", align="left", grid=[1, 3])

Text(pin_box_9, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_9 = TextBox(pin_box_9, width=5, grid=[1, 4], align="left")

Text(pin_box_9, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_9 = Slider(
    pin_box_9, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_9, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_9 = TextBox(pin_box_9, width = 20, grid = [1, 6], align="left")

Text(pin_box_9, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_9 = TextBox(pin_box_9, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_9, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_9():
    app.after(1500, valida_frequencia_9)

def valida_frequencia_9():
    try:
        freq = int(freq_input_9.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 9: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_9.value = ""  

freq_input_9.when_key_pressed = schedule_frequency_validation_9

def configuracao_pino_9():
    pin_saida_9 = 1 if pin_output_checkbox_9.value else 0
    pin_leitura_9 = 1 if result_pin_output_checkbox_9.value else 0
    duty_cycle_9 = int(duty_cycle_slider_9.value)
    config_pino_9 = [
        pin_saida_9,
        pin_leitura_9,
        freq_input_9.value if freq_input_9.value else 0,
        duty_cycle_9,
        test_vector_input_9.value if test_vector_input_9.value else 0,
        bit_hold_time_9.value if bit_hold_time_9.value else 0
    ]
    pinos_valores["pino_9"] = config_pino_9


#### Configuração Pino 10 ####
pin_box_10 = Box(parametros_box, layout="grid", grid=[1, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_10, width = 15, text="Pino 10:", grid=[0, 0], align="left")

Text(pin_box_10, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_10 = CheckBox(pin_box_10, text="", align="left", grid=[1, 2])

Text(pin_box_10, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_10 = CheckBox(
    pin_box_10, text="", align="left", grid=[1, 3])

Text(pin_box_10, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_10 = TextBox(pin_box_10, width=5, grid=[1, 4], align="left")

Text(pin_box_10, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_10 = Slider(
    pin_box_10, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_10, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_10 = TextBox(pin_box_10, width = 20, grid = [1, 6], align="left")

Text(pin_box_10, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_10 = TextBox(pin_box_10, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_10, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_10():
    app.after(1500, valida_frequencia_10)

def valida_frequencia_10():
    try:
        freq = int(freq_input_10.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 10: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_10.value = ""  

freq_input_10.when_key_pressed = schedule_frequency_validation_10

def configuracao_pino_10():
    pin_saida_10 = 1 if pin_output_checkbox_10.value else 0
    pin_leitura_10 = 1 if result_pin_output_checkbox_10.value else 0
    duty_cycle_10 = int(duty_cycle_slider_10.value)
    config_pino_10 = [
        pin_saida_10,
        pin_leitura_10,
        freq_input_10.value if freq_input_10.value else 0,
        duty_cycle_10,
        test_vector_input_10.value if test_vector_input_10.value else 0,
        bit_hold_time_10.value if bit_hold_time_10.value else 0
    ]
    pinos_valores["pino_10"] = config_pino_10


#### Configuração Pino 11 ####
pin_box_11 = Box(parametros_box, layout="grid", grid=[1, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_11, width = 15, text="Pino 11:", grid=[0, 0], align="left")

Text(pin_box_11, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_11 = CheckBox(pin_box_11, text="", align="left", grid=[1, 2])

Text(pin_box_11, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_11 = CheckBox(
    pin_box_11, text="", align="left", grid=[1, 3])

Text(pin_box_11, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_11 = TextBox(pin_box_11, width=5, grid=[1, 4], align="left")

Text(pin_box_11, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_11 = Slider(
    pin_box_11, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_11, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_11 = TextBox(pin_box_11, width = 20, grid = [1, 6], align="left")

Text(pin_box_11, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_11 = TextBox(pin_box_11, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_11, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_11():
    app.after(1500, valida_frequencia_11)

def valida_frequencia_11():
    try:
        freq = int(freq_input_11.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 11: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_11.value = ""  

freq_input_11.when_key_pressed = schedule_frequency_validation_11

def configuracao_pino_11():
    pin_saida_11 = 1 if pin_output_checkbox_11.value else 0
    pin_leitura_11 = 1 if result_pin_output_checkbox_11.value else 0
    duty_cycle_11 = int(duty_cycle_slider_11.value)
    config_pino_11 = [
        pin_saida_11,
        pin_leitura_11,
        freq_input_11.value if freq_input_11.value else 0,
        duty_cycle_11,
        test_vector_input_11.value if test_vector_input_11.value else 0,
        bit_hold_time_11.value if bit_hold_time_11.value else 0
    ]
    pinos_valores["pino_11"] = config_pino_11


#### Configuração Pino 12 ####
pin_box_12 = Box(parametros_box, layout="grid", grid=[2, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_12, width = 15, text="Pino 12:", grid=[0, 0], align="left")

Text(pin_box_12, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_12 = CheckBox(pin_box_12, text="", align="left", grid=[1, 2])

Text(pin_box_12, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_12 = CheckBox(
    pin_box_12, text="", align="left", grid=[1, 3])

Text(pin_box_12, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_12 = TextBox(pin_box_12, width=5, grid=[1, 4], align="left")

Text(pin_box_12, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_12 = Slider(
    pin_box_12, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_12, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_12 = TextBox(pin_box_12, width = 20, grid = [1, 6], align="left")

Text(pin_box_12, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_12 = TextBox(pin_box_12, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_12, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_12():
    app.after(1500, valida_frequencia_12)

def valida_frequencia_12():
    try:
        freq = int(freq_input_12.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 12: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_12.value = ""  

freq_input_12.when_key_pressed = schedule_frequency_validation_12

def configuracao_pino_12():
    pin_saida_12 = 1 if pin_output_checkbox_12.value else 0
    pin_leitura_12 = 1 if result_pin_output_checkbox_12.value else 0
    duty_cycle_12 = int(duty_cycle_slider_12.value)
    config_pino_12 = [
        pin_saida_12,
        pin_leitura_12,
        freq_input_12.value if freq_input_12.value else 0,
        duty_cycle_12,
        test_vector_input_12.value if test_vector_input_12.value else 0,
        bit_hold_time_12.value if bit_hold_time_12.value else 0
    ]
    pinos_valores["pino_12"] = config_pino_12


#### Configuração Pino 13 ####
pin_box_13 = Box(parametros_box, layout="grid", grid=[2, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_13, width = 15, text="Pino 13:", grid=[0, 0], align="left")

Text(pin_box_13, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_13 = CheckBox(pin_box_13, text="", align="left", grid=[1, 2])

Text(pin_box_13, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_13 = CheckBox(
    pin_box_13, text="", align="left", grid=[1, 3])

Text(pin_box_13, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_13 = TextBox(pin_box_13, width=5, grid=[1, 4], align="left")

Text(pin_box_13, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_13 = Slider(
    pin_box_13, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_13, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_13 = TextBox(pin_box_13, width = 20, grid = [1, 6], align="left")

Text(pin_box_13, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_13 = TextBox(pin_box_13, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_13, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_13():
    app.after(1500, valida_frequencia_13)

def valida_frequencia_13():
    try:
        freq = int(freq_input_13.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 13: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_13.value = ""  

freq_input_13.when_key_pressed = schedule_frequency_validation_13

def configuracao_pino_13():
    pin_saida_13 = 1 if pin_output_checkbox_13.value else 0
    pin_leitura_13 = 1 if result_pin_output_checkbox_13.value else 0
    duty_cycle_13 = int(duty_cycle_slider_13.value)
    config_pino_13 = [
        pin_saida_13,
        pin_leitura_13,
        freq_input_13.value if freq_input_13.value else 0,
        duty_cycle_13,
        test_vector_input_13.value if test_vector_input_13.value else 0,
        bit_hold_time_13.value if bit_hold_time_13.value else 0
    ]
    pinos_valores["pino_13"] = config_pino_13

#### Configuração Pino 18 ####
pin_box_18 = Box(parametros_box, layout="grid", grid=[2, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_18, width = 15, text="Pino 18:", grid=[0, 0], align="left")

Text(pin_box_18, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_18 = CheckBox(pin_box_18, text="", align="left", grid=[1, 2])

Text(pin_box_18, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_18 = CheckBox(
    pin_box_18, text="", align="left", grid=[1, 3])

Text(pin_box_18, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_18 = TextBox(pin_box_18, width=5, grid=[1, 4], align="left")

Text(pin_box_18, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_18 = Slider(
    pin_box_18, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_18, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_18 = TextBox(pin_box_18, width = 20, grid = [1, 6], align="left")

Text(pin_box_18, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_18 = TextBox(pin_box_18, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_18, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_18():
    app.after(1500, valida_frequencia_18)

def valida_frequencia_18():
    try:
        freq = int(freq_input_18.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 18: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_18.value = ""  

freq_input_18.when_key_pressed = schedule_frequency_validation_18

def configuracao_pino_18():
    pin_saida_18 = 1 if pin_output_checkbox_18.value else 0
    pin_leitura_18 = 1 if result_pin_output_checkbox_18.value else 0
    duty_cycle_18 = int(duty_cycle_slider_18.value)
    config_pino_18 = [
        pin_saida_18,
        pin_leitura_18,
        freq_input_18.value if freq_input_18.value else 0,
        duty_cycle_18,
        test_vector_input_18.value if test_vector_input_18.value else 0,
        bit_hold_time_18.value if bit_hold_time_18.value else 0
    ]
    pinos_valores["pino_18"] = config_pino_18


#### Configuração Pino 19 ####
pin_box_19 = Box(parametros_box, layout="grid", grid=[2, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_19, width = 15, text="Pino 19:", grid=[0, 0], align="left")

Text(pin_box_19, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_19 = CheckBox(pin_box_19, text="", align="left", grid=[1, 2])

Text(pin_box_19, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_19 = CheckBox(
    pin_box_19, text="", align="left", grid=[1, 3])

Text(pin_box_19, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_19 = TextBox(pin_box_19, width=5, grid=[1, 4], align="left")

Text(pin_box_19, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_19 = Slider(
    pin_box_19, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_19, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_19 = TextBox(pin_box_19, width = 20, grid = [1, 6], align="left")

Text(pin_box_19, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_19 = TextBox(pin_box_19, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_19, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_19():
    app.after(1500, valida_frequencia_19)

def valida_frequencia_19():
    try:
        freq = int(freq_input_19.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 19: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_19.value = ""  

freq_input_19.when_key_pressed = schedule_frequency_validation_19

def configuracao_pino_19():
    pin_saida_19 = 1 if pin_output_checkbox_19.value else 0
    pin_leitura_19 = 1 if result_pin_output_checkbox_19.value else 0
    duty_cycle_19 = int(duty_cycle_slider_19.value)
    config_pino_19 = [
        pin_saida_19,
        pin_leitura_19,
        freq_input_19.value if freq_input_19.value else 0,
        duty_cycle_19,
        test_vector_input_19.value if test_vector_input_19.value else 0,
        bit_hold_time_19.value if bit_hold_time_19.value else 0
    ]
    pinos_valores["pino_19"] = config_pino_19


#### Configuração Pino 20 ####
pin_box_20 = Box(parametros_box, layout="grid", grid=[3, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_20, width = 15, text="Pino 20:", grid=[0, 0], align="left")

Text(pin_box_20, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_20 = CheckBox(pin_box_20, text="", align="left", grid=[1, 2])

Text(pin_box_20, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_20 = CheckBox(
    pin_box_20, text="", align="left", grid=[1, 3])

Text(pin_box_20, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_20 = TextBox(pin_box_20, width=5, grid=[1, 4], align="left")

Text(pin_box_20, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_20 = Slider(
    pin_box_20, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_20, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_20 = TextBox(pin_box_20, width = 20, grid = [1, 6], align="left")

Text(pin_box_20, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_20 = TextBox(pin_box_20, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_20, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_20():
    app.after(1500, valida_frequencia_20)

def valida_frequencia_20():
    try:
        freq = int(freq_input_20.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 20: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_20.value = ""  

freq_input_20.when_key_pressed = schedule_frequency_validation_20

def configuracao_pino_20():
    pin_saida_20 = 1 if pin_output_checkbox_20.value else 0
    pin_leitura_20 = 1 if result_pin_output_checkbox_20.value else 0
    duty_cycle_20 = int(duty_cycle_slider_20.value)
    config_pino_20 = [
        pin_saida_20,
        pin_leitura_20,
        freq_input_20.value if freq_input_20.value else 0,
        duty_cycle_20,
        test_vector_input_20.value if test_vector_input_20.value else 0,
        bit_hold_time_20.value if bit_hold_time_20.value else 0
    ]
    pinos_valores["pino_20"] = config_pino_20


#### Configuração Pino 23 ####
pin_box_23 = Box(parametros_box, layout="grid", grid=[3, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_23, width = 15, text="Pino 23:", grid=[0, 0], align="left")

Text(pin_box_23, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_23 = CheckBox(pin_box_23, text="", align="left", grid=[1, 2])

Text(pin_box_23, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_23 = CheckBox(
    pin_box_23, text="", align="left", grid=[1, 3])

Text(pin_box_23, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_23 = TextBox(pin_box_23, width=5, grid=[1, 4], align="left")

Text(pin_box_23, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_23 = Slider(
    pin_box_23, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_23, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_23 = TextBox(pin_box_23, width = 20, grid = [1, 6], align="left")

Text(pin_box_23, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_23 = TextBox(pin_box_23, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_23, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_23():
    app.after(1500, valida_frequencia_23)

def valida_frequencia_23():
    try:
        freq = int(freq_input_23.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 23: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_23.value = ""  

freq_input_23.when_key_pressed = schedule_frequency_validation_23

def configuracao_pino_23():
    pin_saida_23 = 1 if pin_output_checkbox_23.value else 0
    pin_leitura_23 = 1 if result_pin_output_checkbox_23.value else 0
    duty_cycle_23 = int(duty_cycle_slider_23.value)
    config_pino_23 = [
        pin_saida_23,
        pin_leitura_23,
        freq_input_23.value if freq_input_23.value else 0,
        duty_cycle_23,
        test_vector_input_23.value if test_vector_input_23.value else 0,
        bit_hold_time_23.value if bit_hold_time_23.value else 0
    ]
    pinos_valores["pino_23"] = config_pino_23


#### Configuração Pino 24 ####
pin_box_24 = Box(parametros_box, layout="grid", grid=[3, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_24, width = 15, text="Pino 24:", grid=[0, 0], align="left")

Text(pin_box_24, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_24 = CheckBox(pin_box_24, text="", align="left", grid=[1, 2])

Text(pin_box_24, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_24 = CheckBox(
    pin_box_24, text="", align="left", grid=[1, 3])

Text(pin_box_24, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_24 = TextBox(pin_box_24, width=5, grid=[1, 4], align="left")

Text(pin_box_24, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_24 = Slider(
    pin_box_24, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_24, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_24 = TextBox(pin_box_24, width = 20, grid = [1, 6], align="left")

Text(pin_box_24, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_24 = TextBox(pin_box_24, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_24, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_24():
    app.after(1500, valida_frequencia_24)

def valida_frequencia_24():
    try:
        freq = int(freq_input_24.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 24: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_24.value = ""  

freq_input_24.when_key_pressed = schedule_frequency_validation_24

def configuracao_pino_24():
    pin_saida_24 = 1 if pin_output_checkbox_24.value else 0
    pin_leitura_24 = 1 if result_pin_output_checkbox_24.value else 0
    duty_cycle_24 = int(duty_cycle_slider_24.value)
    config_pino_24 = [
        pin_saida_24,
        pin_leitura_24,
        freq_input_24.value if freq_input_24.value else 0,
        duty_cycle_24,
        test_vector_input_24.value if test_vector_input_24.value else 0,
        bit_hold_time_24.value if bit_hold_time_24.value else 0
    ]
    pinos_valores["pino_24"] = config_pino_24


#### Configuração Pino 25 ####
pin_box_25 = Box(parametros_box, layout="grid", grid=[3, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_25, width = 15, text="Pino 25:", grid=[0, 0], align="left")

Text(pin_box_25, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_25 = CheckBox(pin_box_25, text="", align="left", grid=[1, 2])

Text(pin_box_25, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_25 = CheckBox(
    pin_box_25, text="", align="left", grid=[1, 3])

Text(pin_box_25, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_25 = TextBox(pin_box_25, width=5, grid=[1, 4], align="left")

Text(pin_box_25, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_25 = Slider(
    pin_box_25, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_25, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_25 = TextBox(pin_box_25, width = 20, grid = [1, 6], align="left")

Text(pin_box_25, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_25 = TextBox(pin_box_25, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_25, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_25():
    app.after(1500, valida_frequencia_25)

def valida_frequencia_25():
    try:
        freq = int(freq_input_25.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 25: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_25.value = ""  

freq_input_25.when_key_pressed = schedule_frequency_validation_25

def configuracao_pino_25():
    pin_saida_25 = 1 if pin_output_checkbox_25.value else 0
    pin_leitura_25 = 1 if result_pin_output_checkbox_25.value else 0
    duty_cycle_25 = int(duty_cycle_slider_25.value)
    config_pino_25 = [
        pin_saida_25,
        pin_leitura_25,
        freq_input_25.value if freq_input_25.value else 0,
        duty_cycle_25,
        test_vector_input_25.value if test_vector_input_25.value else 0,
        bit_hold_time_25.value if bit_hold_time_25.value else 0
    ]
    pinos_valores["pino_25"] = config_pino_25


#### Configuração Pino 26 ####
pin_box_26 = Box(parametros_box, layout="grid", grid=[4, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_26, width = 15, text="Pino 26:", grid=[0, 0], align="left")

Text(pin_box_26, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_26 = CheckBox(pin_box_26, text="", align="left", grid=[1, 2])

Text(pin_box_26, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_26 = CheckBox(
    pin_box_26, text="", align="left", grid=[1, 3])

Text(pin_box_26, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_26 = TextBox(pin_box_26, width=5, grid=[1, 4], align="left")

Text(pin_box_26, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_26 = Slider(
    pin_box_26, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_26, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_26 = TextBox(pin_box_26, width = 20, grid = [1, 6], align="left")

Text(pin_box_26, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_26 = TextBox(pin_box_26, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_26, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_26():
    app.after(1500, valida_frequencia_26)

def valida_frequencia_26():
    try:
        freq = int(freq_input_26.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 26: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_26.value = ""  

freq_input_26.when_key_pressed = schedule_frequency_validation_26

def configuracao_pino_26():
    pin_saida_26 = 1 if pin_output_checkbox_26.value else 0
    pin_leitura_26 = 1 if result_pin_output_checkbox_26.value else 0
    duty_cycle_26 = int(duty_cycle_slider_26.value)
    config_pino_26 = [
        pin_saida_26,
        pin_leitura_26,
        freq_input_26.value if freq_input_26.value else 0,
        duty_cycle_26,
        test_vector_input_26.value if test_vector_input_26.value else 0,
        bit_hold_time_26.value if bit_hold_time_26.value else 0
    ]
    pinos_valores["pino_26"] = config_pino_26


#### Configuração Pino 27 ####
pin_box_27 = Box(parametros_box, layout="grid", grid=[4, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_27, width = 15, text="Pino 27:", grid=[0, 0], align="left")

Text(pin_box_27, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_27 = CheckBox(pin_box_27, text="", align="left", grid=[1, 2])

Text(pin_box_27, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_27 = CheckBox(
    pin_box_27, text="", align="left", grid=[1, 3])

Text(pin_box_27, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_27 = TextBox(pin_box_27, width=5, grid=[1, 4], align="left")

Text(pin_box_27, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_27 = Slider(
    pin_box_27, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_27, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_27 = TextBox(pin_box_27, width = 20, grid = [1, 6], align="left")

Text(pin_box_27, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_27 = TextBox(pin_box_27, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_27, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_27():
    app.after(1500, valida_frequencia_27)

def valida_frequencia_27():
    try:
        freq = int(freq_input_27.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 27: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_27.value = ""  

freq_input_27.when_key_pressed = schedule_frequency_validation_27

def configuracao_pino_27():
    pin_saida_27 = 1 if pin_output_checkbox_27.value else 0
    pin_leitura_27 = 1 if result_pin_output_checkbox_27.value else 0
    duty_cycle_27 = int(duty_cycle_slider_27.value)
    config_pino_27 = [
        pin_saida_27,
        pin_leitura_27,
        freq_input_27.value if freq_input_27.value else 0,
        duty_cycle_27,
        test_vector_input_27.value if test_vector_input_27.value else 0,
        bit_hold_time_27.value if bit_hold_time_27.value else 0
    ]
    pinos_valores["pino_27"] = config_pino_27


#### Configuração Pino 28 ####
pin_box_28 = Box(parametros_box, layout="grid", grid=[4, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_28, width = 15, text="Pino 28:", grid=[0, 0], align="left")

Text(pin_box_28, text="Pin Saída:", grid=[0, 2], align="left")
pin_output_checkbox_28 = CheckBox(pin_box_28, text="", align="left", grid=[1, 2])

Text(pin_box_28, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_28 = CheckBox(
    pin_box_28, text="", align="left", grid=[1, 3])

Text(pin_box_28, text="Frequência (Hz):", grid=[0, 4], align="left")
freq_input_28 = TextBox(pin_box_28, width=5, grid=[1, 4], align="left")

Text(pin_box_28, text="Duty Cycle (%):", grid=[0, 5], align="left")
duty_cycle_slider_28 = Slider(
    pin_box_28, start=0, end=100, grid=[1, 5], align="left")

Text(pin_box_28, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_28 = TextBox(pin_box_28, width = 20, grid = [1, 6], align="left")

Text(pin_box_28, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_28 = TextBox(pin_box_28, width = 5, grid = [1, 7], align="left")

# Descrição do Pinos
Text(pin_box_28, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

#Validação da frequência
def schedule_frequency_validation_28():
    app.after(1500, valida_frequencia_28)

def valida_frequencia_28():
    try:
        freq = int(freq_input_28.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 28: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input_28.value = ""  

freq_input_28.when_key_pressed = schedule_frequency_validation_28

def configuracao_pino_28():
    pin_saida_28 = 1 if pin_output_checkbox_28.value else 0
    pin_leitura_28 = 1 if result_pin_output_checkbox_28.value else 0
    duty_cycle_28 = int(duty_cycle_slider_28.value)
    config_pino_28 = [
        pin_saida_28,
        pin_leitura_28,
        freq_input_28.value if freq_input_28.value else 0,
        duty_cycle_28,
        test_vector_input_28.value if test_vector_input_28.value else 0,
        bit_hold_time_28.value if bit_hold_time_28.value else 0
    ]
    pinos_valores["pino_28"] = config_pino_28


# Error Message Box
error_message_box = Box(app, width="fill", align="bottom", border=True)
error_message = Text(error_message_box, text="", color="red", align="bottom")

# Start Button
start_button = PushButton(app, command=start_test,
                          text="START", align="bottom")



# Display
app.display()


