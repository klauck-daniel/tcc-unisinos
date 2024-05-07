from enviaMensagemUDP import envia_mensagem_udp, envia_start_mensagem_udp
from guizero import App, Text, PushButton, CheckBox, TextBox, Slider, Box

#Variáveis Globais
esp_ip = "192.168.1.24" 
esp_porta = 3333
pinos_valores = {}

freq_min = 1
freq_max = 5000

hold_time_min = 100
hold_time_max = 2000

ms_valida = 1500


# Functions
def start_test():
    print("Iniciando Teste.")  
    envia_start_mensagem_udp(esp_ip, esp_porta, "START")

def reset_system():
    print("Reiniciando ESP...")
    envia_start_mensagem_udp(esp_ip, esp_porta, "RESET")

def send_test_config():
    print("Enviando Configuração.")
    configuracao_frequencia()

    configuracao_canal_0()
    configuracao_canal_1()
    configuracao_canal_2()
    configuracao_canal_3()
    configuracao_canal_4()
    configuracao_canal_5()
    configuracao_canal_6()
    configuracao_canal_7()

    configuracao_pino_2()
    configuracao_pino_3()
    configuracao_pino_4()
    configuracao_pino_5()
    configuracao_pino_6()
    configuracao_pino_7()
    configuracao_pino_8()
    configuracao_pino_9()
    configuracao_pino_10()
    configuracao_pino_11()
    configuracao_pino_12()
    configuracao_pino_13()
    configuracao_pino_18()
    configuracao_pino_19()
    configuracao_pino_20()

    configuracao_pino_21("00V" if "03V" not in [
        voltage_options[i] for i, checkbox in enumerate(
            voltage_checkboxes) if checkbox.value] else "03V")
    configuracao_pino_22("00V" if "05V" not in [
        voltage_options[i] for i, checkbox in enumerate(
            voltage_checkboxes) if checkbox.value] else "05V")
    configuracao_pino_23("00V" if "12V" not in [
        voltage_options[i] for i, checkbox in enumerate(
            voltage_checkboxes) if checkbox.value] else "12V")
    configuracao_pino_24("00V" if "24V" not in [
        voltage_options[i] for i, checkbox in enumerate(
            voltage_checkboxes) if checkbox.value] else "24V")
    
    configuracao_pino_25()
    configuracao_pino_26()
    configuracao_pino_27()
    configuracao_pino_29()
    configuracao_pino_30()

    envia_mensagem_udp(esp_ip, esp_porta, pinos_valores)

# App
app = App(title="ATE DRK", width=1350, height=980)
app.full_screen = False

# Title Box
title_box = Box(app, width="fill", align="top", border=True)
Text(title_box, text="Parametrização do Teste")

# Content Box
content_box = Box(app, align = "top", layout = "grid", grid = [0, 0], width = "fill", border = True)

################ TENSÃO #################

# Tensão
voltage_box = Box(content_box,
                  layout = "grid",
                  grid = [0, 0],
                  width = "fill",
                  align = "left",
                  border = True)
Text(voltage_box, text = "Tensões Disponíveis:", grid = [0, 0], align = "left")

# Função para configurar o pino 4 com a tensão especificada
def configuracao_pino_21(tensao):
    pinos_valores["21"] = [tensao]

# Função para configurar o pino 5 com a tensão especificada
def configuracao_pino_22(tensao):
    pinos_valores["22"] = [tensao]

# Função para configurar o pino 21 com a tensão especificada
def configuracao_pino_23(tensao):
    pinos_valores["23"] = [tensao]

# Função para configurar o pino 22 com a tensão especificada
def configuracao_pino_24(tensao):
    pinos_valores["24"] = [tensao]

# Pinos 4, 5, 21, 22 serão para selecionar a tensão
voltage_options = ["03V", "05V", "12V", "24V"]
voltage_checkboxes = []
for i, voltage in enumerate(voltage_options):
    checkbox = CheckBox(voltage_box, text=voltage, align="left", grid=[i + 1, 0])
    voltage_checkboxes.append(checkbox)


################ FREQUENCIA #################

# Configuração da caixa de input da frequencia
config_frequency_box = Box(content_box, layout="grid", width="fill", height="fill",
                     align="left", border=True, grid=[0, 1])

Text(config_frequency_box, text="Frequência dos sinais (Hz):", grid=[0, 0], align="left")

freq_input = TextBox(config_frequency_box, width=5, grid=[1, 0], align="left" )

def schedule_frequency_validation():
    app.after(ms_valida, valida_frequencia)

def valida_frequencia():
    try:
        freq = int(freq_input.value)
        if freq < freq_min or freq > freq_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"ERRO: Frequência deve estar entre {freq_min} Hz e {freq_max} Hz."
        freq_input.value = ""  

freq_input.when_key_pressed = schedule_frequency_validation

def configuracao_frequencia():
    config_freq = [freq_input.value if freq_input.value else 0]
    pinos_valores["FRQ"] = config_freq


################ DEMAIS PARÂMETROS #################

# Parametros
parametros_box = Box(content_box, layout="grid", width="fill", height="fill",
                     align="left", border=True, grid=[0, 3])


### Configuração Pino 2 ####
pin_box_2 = Box(parametros_box, layout="grid", grid=[0, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_2, width = 15, text="Pino 2:", grid=[0, 0], align="left")

Text(pin_box_2, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_2 = CheckBox(
    pin_box_2, text="", align="left", grid=[1, 3])

# Descrição do Pinos
Text(pin_box_2, text = "INPUT ONLY, ADC, GPIO36", grid = [0, 1], align="left")

def configuracao_pino_2():
    pin_leitura_2 = 1 if result_pin_output_checkbox_2.value else 0
    config_pino_2 = [
        pin_leitura_2
    ]
    pinos_valores["02"] = config_pino_2


#### Configuração Pino 3 ####
pin_box_3 = Box(parametros_box, layout="grid", grid=[0, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_3, width = 15, text="Pino 3:", grid=[0, 0], align="left")

Text(pin_box_3, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_3 = CheckBox(
    pin_box_3, text="", align="left", grid=[1, 3])

# Descrição do Pinos
Text(pin_box_3, text = "INPUT ONLY, ADC, GPIO39", grid = [0, 1], align="left")

def configuracao_pino_3():
    pin_leitura_3 = 1 if result_pin_output_checkbox_3.value else 0
    config_pino_3 = [
        pin_leitura_3,
    ]
    pinos_valores["03"] = config_pino_3


#### Configuração Pino 4 ####
pin_box_4 = Box(parametros_box, layout="grid", grid=[0, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_4, width = 15, text="Pino 4:", grid=[0, 0], align="left")

Text(pin_box_4, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_4 = CheckBox(
    pin_box_4, text="", align="left", grid=[1, 3])

# Descrição do Pinos
Text(pin_box_4, text = "INPUT ONLY, ADC, GPIO34", grid = [0, 1], align="left")

def configuracao_pino_4():
    pin_leitura_4 = 1 if result_pin_output_checkbox_4.value else 0
    config_pino_4 = [
        pin_leitura_4,
    ]
    pinos_valores["04"] = config_pino_4

#### Configuração Pino 5 ####
pin_box_5 = Box(parametros_box, layout="grid", grid=[0, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_5, width = 15, text="Pino 5:", grid=[0, 0], align="left")

Text(pin_box_5, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_5 = CheckBox(
    pin_box_5, text="", align="left", grid=[1, 3])

# Descrição do Pinos
Text(pin_box_5, text = "INPUT ONLY, ADC, GPIO35", grid = [0, 1], align="left")

def configuracao_pino_5():
    pin_leitura_5 = 1 if result_pin_output_checkbox_5.value else 0
    config_pino_5 = [
        pin_leitura_5,
    ]
    pinos_valores["05"] = config_pino_5


#### Configuração Pino 6 ####
pin_box_6 = Box(parametros_box, layout="grid", grid=[1, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_6, width = 15, text="Pino 6:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_6, text = "ADC, GPIO32", grid = [0, 1], align="left")

Text(pin_box_6, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_6 = CheckBox(
    pin_box_6, text="", align="left", grid=[1, 2])

Text(pin_box_6, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_6 = TextBox(pin_box_6, width = 13, grid = [1, 6], align="left")

Text(pin_box_6, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_6 = TextBox(pin_box_6, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_6():
    app.after(ms_valida*3, valida_test_vector_6)

def schedule_hold_time_6():
    app.after(ms_valida, valida_hold_time_6)

def valida_test_vector_6():
    try:
        test_vector = test_vector_input_6.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 6: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_6.value = ""

test_vector_input_6.when_key_pressed = schedule_test_vector_6

def valida_hold_time_6():
    try:
        hold_time = int(bit_hold_time_6.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 6: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_6.value = ""  

bit_hold_time_6.when_key_pressed = schedule_hold_time_6

def configuracao_pino_6():
    pin_leitura_6 = 1 if result_pin_output_checkbox_6.value else 0
    config_pino_6 = [
        pin_leitura_6,
        test_vector_input_6.value if test_vector_input_6.value else 0,
        bit_hold_time_6.value if bit_hold_time_6.value else 0
    ]
    pinos_valores["06"] = config_pino_6


#### Configuração Pino 7 ####
pin_box_7 = Box(parametros_box, layout="grid", grid=[1, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_7, width = 15, text="Pino 7:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_7, text = "ADC, GPIO33", grid = [0, 1], align="left")

Text(pin_box_7, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_7 = CheckBox(
    pin_box_7, text="", align="left", grid=[1, 2])

Text(pin_box_7, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_7 = TextBox(pin_box_7, width = 13, grid = [1, 6], align="left")

Text(pin_box_7, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_7 = TextBox(pin_box_7, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_7():
    app.after(ms_valida*3, valida_test_vector_7)

def schedule_hold_time_7():
    app.after(ms_valida, valida_hold_time_7)

def valida_test_vector_7():
    try:
        test_vector = test_vector_input_7.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 7: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_7.value = ""

test_vector_input_7.when_key_pressed = schedule_test_vector_7

def valida_hold_time_7():
    try:
        hold_time = int(bit_hold_time_7.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 7: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_7.value = ""  

bit_hold_time_7.when_key_pressed = schedule_hold_time_7

def configuracao_pino_7():
    pin_leitura_7 = 1 if result_pin_output_checkbox_7.value else 0
    config_pino_7 = [
        pin_leitura_7,
        test_vector_input_7.value if test_vector_input_7.value else 0,
        bit_hold_time_7.value if bit_hold_time_7.value else 0
    ]
    pinos_valores["07"] = config_pino_7


#### Configuração Pino 8 ####
pin_box_8 = Box(parametros_box, layout="grid", grid=[1, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_8, width = 15, text="Pino 8:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_8, text = "DAC, ADC, GPIO25", grid = [0, 1], align="left")

Text(pin_box_8, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_8 = CheckBox(
    pin_box_8, text="", align="left", grid=[1, 2])

Text(pin_box_8, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_8 = TextBox(pin_box_8, width = 13, grid = [1, 6], align="left")

Text(pin_box_8, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_8 = TextBox(pin_box_8, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_8():
    app.after(ms_valida*3, valida_test_vector_8)

def schedule_hold_time_8():
    app.after(ms_valida, valida_hold_time_8)

def valida_test_vector_8():
    try:
        test_vector = test_vector_input_8.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 8: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_8.value = ""

test_vector_input_8.when_key_pressed = schedule_test_vector_8

def valida_hold_time_8():
    try:
        hold_time = int(bit_hold_time_8.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 8: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_8.value = ""  

bit_hold_time_8.when_key_pressed = schedule_hold_time_8

def configuracao_pino_8():
    pin_leitura_8 = 1 if result_pin_output_checkbox_8.value else 0
    config_pino_8 = [
        pin_leitura_8,
        test_vector_input_8.value if test_vector_input_8.value else 0,
        bit_hold_time_8.value if bit_hold_time_8.value else 0
    ]
    pinos_valores["08"] = config_pino_8


#### Configuração Pino 9 ####
pin_box_9 = Box(parametros_box, layout="grid", grid=[1, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_9, width = 15, text="Pino 9:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_9, text = "DAC, ADC, GPIO26", grid = [0, 1], align="left")

Text(pin_box_9, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_9 = CheckBox(
    pin_box_9, text="", align="left", grid=[1, 2])

Text(pin_box_9, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_9 = TextBox(pin_box_9, width = 13, grid = [1, 6], align="left")

Text(pin_box_9, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_9 = TextBox(pin_box_9, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_9():
    app.after(ms_valida*3, valida_test_vector_9)

def schedule_hold_time_9():
    app.after(ms_valida, valida_hold_time_9)

def valida_test_vector_9():
    try:
        test_vector = test_vector_input_9.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 9: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_9.value = ""

test_vector_input_9.when_key_pressed = schedule_test_vector_9

def valida_hold_time_9():
    try:
        hold_time = int(bit_hold_time_9.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 9: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_9.value = ""  

bit_hold_time_9.when_key_pressed = schedule_hold_time_9

def configuracao_pino_9():
    pin_leitura_9 = 1 if result_pin_output_checkbox_9.value else 0
    config_pino_9 = [
        pin_leitura_9,
        test_vector_input_9.value if test_vector_input_9.value else 0,
        bit_hold_time_9.value if bit_hold_time_9.value else 0
    ]
    pinos_valores["09"] = config_pino_9


#### Configuração Pino 10 ####
pin_box_10 = Box(parametros_box, layout="grid", grid=[2, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_10, width = 15, text="Pino 10:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_10, text = "PWM CH0, ADC, GPIO27", grid = [0, 1], align="left")

Text(pin_box_10, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_10 = CheckBox(
    pin_box_10, text="", align="left", grid=[1, 2])

Text(pin_box_10, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_10 = CheckBox(pin_box_10, text="", align="left", grid=[1, 3])

Text(pin_box_10, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_10 = Slider(
    pin_box_10, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_0():
    enable_pwm_ch_0 = 1 if enable_pwm_pin_10.value else 0
    duty_cycle_ch_0 = int(duty_cycle_pin_10.value)
    config_channel_0 = [
        enable_pwm_ch_0,
        duty_cycle_ch_0,
    ]
    pinos_valores["CH0"] = config_channel_0

Text(pin_box_10, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_10 = TextBox(pin_box_10, width = 13, grid = [1, 5], align="left")

Text(pin_box_10, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_10 = TextBox(pin_box_10, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_10():
    app.after(ms_valida*3, valida_test_vector_10)

def schedule_hold_time_10():
    app.after(ms_valida, valida_hold_time_10)

def valida_test_vector_10():
    try:
        test_vector = test_vector_input_10.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 10: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_10.value = ""

test_vector_input_10.when_key_pressed = schedule_test_vector_10

def valida_hold_time_10():
    try:
        hold_time = int(bit_hold_time_10.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 10: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_10.value = ""  

bit_hold_time_10.when_key_pressed = schedule_hold_time_10

def configuracao_pino_10():
    pin_leitura_10 = 1 if result_pin_output_checkbox_10.value else 0
    enable_pwm_ch_0 = 1 if enable_pwm_pin_10.value else 0
    config_pino_10 = [
        pin_leitura_10,
        enable_pwm_ch_0,
        test_vector_input_10.value if test_vector_input_10.value else 0,
        bit_hold_time_10.value if bit_hold_time_10.value else 0
    ]
    pinos_valores["10"] = config_pino_10


#### Configuração Pino 11 ####
pin_box_11 = Box(parametros_box, layout="grid", grid=[2, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_11, width = 15, text="Pino 11:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_11, text = "PWM CH1, ADC, GPIO14", grid = [0, 1], align="left")

Text(pin_box_11, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_11 = CheckBox(
    pin_box_11, text="", align="left", grid=[1, 2])

Text(pin_box_11, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_11 = CheckBox(pin_box_11, text="", align="left", grid=[1, 3])

Text(pin_box_11, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_11 = Slider(
    pin_box_11, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_1():
    enable_pwm_ch_1 = 1 if enable_pwm_pin_11.value else 0
    duty_cycle_ch_1 = int(duty_cycle_pin_11.value)
    config_channel_1 = [
        enable_pwm_ch_1,
        duty_cycle_ch_1,
    ]
    pinos_valores["CH1"] = config_channel_1

Text(pin_box_11, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_11 = TextBox(pin_box_11, width = 13, grid = [1, 5], align="left")

Text(pin_box_11, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_11 = TextBox(pin_box_11, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_11():
    app.after(ms_valida*3, valida_test_vector_11)

def schedule_hold_time_11():
    app.after(ms_valida, valida_hold_time_11)

def valida_test_vector_11():
    try:
        test_vector = test_vector_input_11.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 11: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_11.value = ""

test_vector_input_11.when_key_pressed = schedule_test_vector_11

def valida_hold_time_11():
    try:
        hold_time = int(bit_hold_time_11.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 11: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_11.value = ""  

bit_hold_time_11.when_key_pressed = schedule_hold_time_11

def configuracao_pino_11():
    pin_leitura_11 = 1 if result_pin_output_checkbox_11.value else 0
    enable_pwm_ch_1 = 1 if enable_pwm_pin_11.value else 0
    config_pino_11 = [
        pin_leitura_11,
        enable_pwm_ch_1,
        test_vector_input_11.value if test_vector_input_11.value else 0,
        bit_hold_time_11.value if bit_hold_time_11.value else 0
    ]
    pinos_valores["11"] = config_pino_11


#### Configuração Pino 12 ####
pin_box_12 = Box(parametros_box, layout="grid", grid=[2, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_12, width = 15, text="Pino 12:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_12, text = "PWM CH2, ADC, GPIO12", grid = [0, 1], align="left")

# Text(pin_box_12, text="Pin Leitura:", grid=[0, 2], align="left")
# result_pin_output_checkbox_12 = CheckBox(
#     pin_box_12, text="", align="left", grid=[1, 2])

Text(pin_box_12, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_12 = CheckBox(pin_box_12, text="", align="left", grid=[1, 3])

Text(pin_box_12, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_12 = Slider(
    pin_box_12, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_2():
    enable_pwm_ch_2 = 1 if enable_pwm_pin_12.value else 0
    duty_cycle_ch_2 = int(duty_cycle_pin_12.value)
    config_channel_2 = [
        enable_pwm_ch_2,
        duty_cycle_ch_2,
    ]
    pinos_valores["CH2"] = config_channel_2

Text(pin_box_12, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_12 = TextBox(pin_box_12, width = 13, grid = [1, 5], align="left")

Text(pin_box_12, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_12 = TextBox(pin_box_12, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_12():
    app.after(ms_valida*3, valida_test_vector_12)

def schedule_hold_time_12():
    app.after(ms_valida, valida_hold_time_12)

def valida_test_vector_12():
    try:
        test_vector = test_vector_input_12.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 12: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_12.value = ""

test_vector_input_12.when_key_pressed = schedule_test_vector_12

def valida_hold_time_12():
    try:
        hold_time = int(bit_hold_time_12.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 12: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_12.value = ""  

bit_hold_time_12.when_key_pressed = schedule_hold_time_12

def configuracao_pino_12():
    pin_leitura_12 = 0 #1 if result_pin_output_checkbox_12.value else 0
    enable_pwm_ch_2 = 1 if enable_pwm_pin_12.value else 0
    config_pino_12 = [
        pin_leitura_12,
        enable_pwm_ch_2,
        test_vector_input_12.value if test_vector_input_12.value else 0,
        bit_hold_time_12.value if bit_hold_time_12.value else 0
    ]
    pinos_valores["12"] = config_pino_12


#### Configuração Pino 13 ####
pin_box_13 = Box(parametros_box, layout="grid", grid=[2, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_13, width = 15, text="Pino 13:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_13, text = "PWM CH3, ADC, GPIO13", grid = [0, 1], align="left")

Text(pin_box_13, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_13 = CheckBox(
    pin_box_13, text="", align="left", grid=[1, 2])

Text(pin_box_13, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_13 = CheckBox(pin_box_13, text="", align="left", grid=[1, 3])

Text(pin_box_13, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_13 = Slider(
    pin_box_13, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_3():
    enable_pwm_ch_3 = 1 if enable_pwm_pin_13.value else 0
    duty_cycle_ch_3 = int(duty_cycle_pin_13.value)
    config_channel_3 = [
        enable_pwm_ch_3,
        duty_cycle_ch_3,
    ]
    pinos_valores["CH3"] = config_channel_3

Text(pin_box_13, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_13 = TextBox(pin_box_13, width = 13, grid = [1, 5], align="left")

Text(pin_box_13, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_13 = TextBox(pin_box_13, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_13():
    app.after(ms_valida*3, valida_test_vector_13)

def schedule_hold_time_13():
    app.after(ms_valida, valida_hold_time_13)

def valida_test_vector_13():
    try:
        test_vector = test_vector_input_13.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 13: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_13.value = ""

test_vector_input_13.when_key_pressed = schedule_test_vector_13

def valida_hold_time_13():
    try:
        hold_time = int(bit_hold_time_13.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 13: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_13.value = ""  

bit_hold_time_13.when_key_pressed = schedule_hold_time_13

def configuracao_pino_13():
    pin_leitura_13 = 1 if result_pin_output_checkbox_13.value else 0
    enable_pwm_ch_3 = 1 if enable_pwm_pin_13.value else 0
    config_pino_13 = [
        pin_leitura_13,
        enable_pwm_ch_3,
        test_vector_input_13.value if test_vector_input_13.value else 0,
        bit_hold_time_13.value if bit_hold_time_13.value else 0
    ]
    pinos_valores["13"] = config_pino_13

#### Configuração Pino 18 ####
pin_box_18 = Box(parametros_box, layout="grid", grid=[3, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_18, width = 15, text="Pino 18:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_18, text = "ADC, GPIO15", grid = [0, 1], align="left")

# Text(pin_box_18, text="Pin Leitura:", grid=[0, 3], align="left")
# result_pin_output_checkbox_18 = CheckBox(
#     pin_box_18, text="", align="left", grid=[1, 3])

Text(pin_box_18, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_18 = TextBox(pin_box_18, width = 13, grid = [1, 6], align="left")

Text(pin_box_18, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_18 = TextBox(pin_box_18, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_18():
    app.after(ms_valida*3, valida_test_vector_18)

def schedule_hold_time_18():
    app.after(ms_valida, valida_hold_time_18)

def valida_test_vector_18():
    try:
        test_vector = test_vector_input_18.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 18: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_18.value = ""

test_vector_input_18.when_key_pressed = schedule_test_vector_18

def valida_hold_time_18():
    try:
        hold_time = int(bit_hold_time_18.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 18: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_18.value = ""  

bit_hold_time_18.when_key_pressed = schedule_hold_time_18

def configuracao_pino_18():
    pin_leitura_18 = 0 #1 if result_pin_output_checkbox_18.value else 0
    config_pino_18 = [
        pin_leitura_18,
        test_vector_input_18.value if test_vector_input_18.value else 0,
        bit_hold_time_18.value if bit_hold_time_18.value else 0
    ]
    pinos_valores["18"] = config_pino_18


#### Configuração Pino 19 ####
pin_box_19 = Box(parametros_box, layout="grid", grid=[3, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_19, width = 15, text="Pino 19:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_19, text = "ADC, GPIO2", grid = [0, 1], align="left")

# Text(pin_box_19, text="Pin Leitura:", grid=[0, 3], align="left")
# result_pin_output_checkbox_19 = CheckBox(
#     pin_box_19, text="", align="left", grid=[1, 3])

Text(pin_box_19, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_19 = TextBox(pin_box_19, width = 13, grid = [1, 6], align="left")

Text(pin_box_19, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_19 = TextBox(pin_box_19, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_19():
    app.after(ms_valida*3, valida_test_vector_19)

def schedule_hold_time_19():
    app.after(ms_valida, valida_hold_time_19)

def valida_test_vector_19():
    try:
        test_vector = test_vector_input_19.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 19: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_19.value = ""

test_vector_input_19.when_key_pressed = schedule_test_vector_19

def valida_hold_time_19():
    try:
        hold_time = int(bit_hold_time_19.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 19: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_19.value = ""  

bit_hold_time_19.when_key_pressed = schedule_hold_time_19

def configuracao_pino_19():
    pin_leitura_19 = 0 #1 if result_pin_output_checkbox_19.value else 0
    config_pino_19 = [
        pin_leitura_19,
        test_vector_input_19.value if test_vector_input_19.value else 0,
        bit_hold_time_19.value if bit_hold_time_19.value else 0
    ]
    pinos_valores["19"] = config_pino_19


#### Configuração Pino 20 ####
pin_box_20 = Box(parametros_box, layout="grid", grid=[3, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_20, width = 15, text="Pino 20:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_20, text = "ADC, GPIO4", grid = [0, 1], align="left")

Text(pin_box_20, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_20 = CheckBox(
    pin_box_20, text="", align="left", grid=[1, 3])

Text(pin_box_20, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_20 = TextBox(pin_box_20, width = 13, grid = [1, 6], align="left")

Text(pin_box_20, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_20 = TextBox(pin_box_20, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_20():
    app.after(ms_valida*3, valida_test_vector_20)

def schedule_hold_time_20():
    app.after(ms_valida, valida_hold_time_20)

def valida_test_vector_20():
    try:
        test_vector = test_vector_input_20.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 20: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_20.value = ""

test_vector_input_20.when_key_pressed = schedule_test_vector_20

def valida_hold_time_20():
    try:
        hold_time = int(bit_hold_time_20.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 20: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_20.value = ""  

bit_hold_time_20.when_key_pressed = schedule_hold_time_20

def configuracao_pino_20():
    pin_leitura_20 = 1 if result_pin_output_checkbox_20.value else 0
    config_pino_20 = [
        pin_leitura_20,
        test_vector_input_20.value if test_vector_input_20.value else 0,
        bit_hold_time_20.value if bit_hold_time_20.value else 0
    ]
    pinos_valores["20"] = config_pino_20


#### Configuração Pino 25 ####
pin_box_25 = Box(parametros_box, layout="grid", grid=[3, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_25, width = 15, text="Pino 25:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_25, text = "PWM CH4, GPIO19", grid = [0, 1], align="left")

Text(pin_box_25, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_25 = CheckBox(
    pin_box_25, text="", align="left", grid=[1, 3])

Text(pin_box_25, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_25 = CheckBox(pin_box_25, text="", align="left", grid=[1, 3])

Text(pin_box_25, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_25 = Slider(
    pin_box_25, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_4():
    enable_pwm_ch_4 = 1 if enable_pwm_pin_25.value else 0
    duty_cycle_ch_4 = int(duty_cycle_pin_25.value)
    config_channel_4 = [
        enable_pwm_ch_4,
        duty_cycle_ch_4,
    ]
    pinos_valores["CH4"] = config_channel_4

Text(pin_box_25, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_25 = TextBox(pin_box_25, width = 13, grid = [1, 6], align="left")

Text(pin_box_25, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_25 = TextBox(pin_box_25, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_25():
    app.after(ms_valida*3, valida_test_vector_25)

def schedule_hold_time_25():
    app.after(ms_valida, valida_hold_time_25)

def valida_test_vector_25():
    try:
        test_vector = test_vector_input_25.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 25: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_25.value = ""

test_vector_input_25.when_key_pressed = schedule_test_vector_25

def valida_hold_time_25():
    try:
        hold_time = int(bit_hold_time_25.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 25: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_25.value = ""  

bit_hold_time_25.when_key_pressed = schedule_hold_time_25

def configuracao_pino_25():
    pin_leitura_25 = 1 if result_pin_output_checkbox_25.value else 0
    enable_pwm_ch_4 = 1 if enable_pwm_pin_25.value else 0
    config_pino_25 = [
        pin_leitura_25,
        enable_pwm_ch_4,
        test_vector_input_25.value if test_vector_input_25.value else 0,
        bit_hold_time_25.value if bit_hold_time_25.value else 0
    ]
    pinos_valores["25"] = config_pino_25


#### Configuração Pino 26 ####
pin_box_26 = Box(parametros_box, layout="grid", grid=[4, 0], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_26, width = 15, text="Pino 26:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_26, text = "PWM CH5, GPIO21", grid = [0, 1], align="left")

Text(pin_box_26, text="Pin Leitura:", grid=[0, 3], align="left")
result_pin_output_checkbox_26 = CheckBox(
    pin_box_26, text="", align="left", grid=[1, 3])

Text(pin_box_26, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_26 = CheckBox(pin_box_26, text="", align="left", grid=[1, 3])

Text(pin_box_26, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_26 = Slider(
    pin_box_26, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_5():
    enable_pwm_ch_5 = 1 if enable_pwm_pin_26.value else 0
    duty_cycle_ch_5 = int(duty_cycle_pin_26.value)
    config_channel_5 = [
        enable_pwm_ch_5,
        duty_cycle_ch_5,
    ]
    pinos_valores["CH5"] = config_channel_5

Text(pin_box_26, text="Vetor de Teste:", grid=[0, 6], align="left")
test_vector_input_26 = TextBox(pin_box_26, width = 13, grid = [1, 6], align="left")

Text(pin_box_26, text="Bit Hold Time [ms]:", grid=[0, 7], align="left")
bit_hold_time_26 = TextBox(pin_box_26, width = 5, grid = [1, 7], align="left")

#Validações
def schedule_test_vector_26():
    app.after(ms_valida*3, valida_test_vector_26)

def schedule_hold_time_26():
    app.after(ms_valida, valida_hold_time_26)

def valida_test_vector_26():
    try:
        test_vector = test_vector_input_26.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 26: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_26.value = ""

test_vector_input_26.when_key_pressed = schedule_test_vector_26

def valida_hold_time_26():
    try:
        hold_time = int(bit_hold_time_26.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 26: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_26.value = ""  

bit_hold_time_26.when_key_pressed = schedule_hold_time_26

def configuracao_pino_26():
    pin_leitura_26 = 1 if result_pin_output_checkbox_26.value else 0
    enable_pwm_ch_5 = 1 if enable_pwm_pin_26.value else 0
    config_pino_26 = [
        pin_leitura_26,
        enable_pwm_ch_5,
        test_vector_input_26.value if test_vector_input_26.value else 0,
        bit_hold_time_26.value if bit_hold_time_26.value else 0
    ]
    pinos_valores["26"] = config_pino_26


#### Configuração Pino 27 ####
pin_box_27 = Box(parametros_box, layout="grid", grid=[4, 1], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_27, width = 15, text="Pino 27:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_27, text = "GPIO3", grid = [0, 1], align="left")

Text(pin_box_27, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_27 = CheckBox(
    pin_box_27, text="", align="left", grid=[1, 2])

Text(pin_box_27, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_27 = TextBox(pin_box_27, width = 13, grid = [1, 5], align="left")

Text(pin_box_27, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_27 = TextBox(pin_box_27, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_27():
    app.after(ms_valida*3, valida_test_vector_27)

def schedule_hold_time_27():
    app.after(ms_valida, valida_hold_time_27)

def valida_test_vector_27():
    try:
        test_vector = test_vector_input_27.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 27: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_27.value = ""

test_vector_input_27.when_key_pressed = schedule_test_vector_27

def valida_hold_time_27():
    try:
        hold_time = int(bit_hold_time_27.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 27: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_27.value = ""  

bit_hold_time_27.when_key_pressed = schedule_hold_time_27

def configuracao_pino_27():
    pin_leitura_27 = 1 if result_pin_output_checkbox_27.value else 0
    config_pino_27 = [
        pin_leitura_27,
        test_vector_input_27.value if test_vector_input_27.value else 0,
        bit_hold_time_27.value if bit_hold_time_27.value else 0
    ]
    pinos_valores["27"] = config_pino_27


#### Configuração Pino 29 ####
pin_box_29 = Box(parametros_box, layout="grid", grid=[4, 2], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_29, width = 15, text="Pino 29:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_29, text = "PWM CH6, GPIO22", grid = [0, 1], align="left")

Text(pin_box_29, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_29 = CheckBox(
    pin_box_29, text="", align="left", grid=[1, 2])

Text(pin_box_29, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_29 = CheckBox(pin_box_29, text="", align="left", grid=[1, 3])

Text(pin_box_29, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_29 = Slider(
    pin_box_29, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_6():
    enable_pwm_ch_6 = 1 if enable_pwm_pin_29.value else 0
    duty_cycle_ch_6 = int(duty_cycle_pin_29.value)
    config_channel_6 = [
        enable_pwm_ch_6,
        duty_cycle_ch_6,
    ]
    pinos_valores["CH6"] = config_channel_6

Text(pin_box_29, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_29 = TextBox(pin_box_29, width = 13, grid = [1, 5], align="left")

Text(pin_box_29, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_29 = TextBox(pin_box_29, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_29():
    app.after(ms_valida*3, valida_test_vector_29)

def schedule_hold_time_29():
    app.after(ms_valida, valida_hold_time_29)

def valida_test_vector_29():
    try:
        test_vector = test_vector_input_29.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 29: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_29.value = ""

test_vector_input_29.when_key_pressed = schedule_test_vector_29

def valida_hold_time_29():
    try:
        hold_time = int(bit_hold_time_29.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 29: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_29.value = ""  

bit_hold_time_29.when_key_pressed = schedule_hold_time_29

def configuracao_pino_29():
    pin_leitura_29 = 1 if result_pin_output_checkbox_29.value else 0
    enable_pwm_ch_6 = 1 if enable_pwm_pin_29.value else 0
    config_pino_29 = [
        pin_leitura_29,
        enable_pwm_ch_6,
        test_vector_input_29.value if test_vector_input_29.value else 0,
        bit_hold_time_29.value if bit_hold_time_29.value else 0
    ]
    pinos_valores["29"] = config_pino_29


#### Configuração Pino 30 ####
pin_box_30 = Box(parametros_box, layout="grid", grid=[4, 3], width="fill", height="fill",
                  align="left", border = True)

Text(pin_box_30, width = 15, text="Pino 30:", grid=[0, 0], align="left")

# Descrição do Pinos
Text(pin_box_30, text = "PWM CH7, GPIO23", grid = [0, 1], align="left")

Text(pin_box_30, text="Pin Leitura:", grid=[0, 2], align="left")
result_pin_output_checkbox_30 = CheckBox(
    pin_box_30, text="", align="left", grid=[1, 2])

Text(pin_box_30, text="Enable PWM:", grid=[0, 3], align="left")
enable_pwm_pin_30 = CheckBox(pin_box_30, text="", align="left", grid=[1, 3])

Text(pin_box_30, text="Duty Cycle (%):", grid=[0, 4], align="left")
duty_cycle_pin_30 = Slider(
    pin_box_30, start=0, end=100, grid=[1, 4], align="left")

def configuracao_canal_7():
    enable_pwm_ch_7 = 1 if enable_pwm_pin_30.value else 0
    duty_cycle_ch_7 = int(duty_cycle_pin_30.value)
    config_channel_7 = [
        enable_pwm_ch_7,
        duty_cycle_ch_7,
    ]
    pinos_valores["CH7"] = config_channel_7

Text(pin_box_30, text="Vetor de Teste:", grid=[0, 5], align="left")
test_vector_input_30 = TextBox(pin_box_30, width = 13, grid = [1, 5], align="left")

Text(pin_box_30, text="Bit Hold Time [ms]:", grid=[0, 6], align="left")
bit_hold_time_30 = TextBox(pin_box_30, width = 5, grid = [1, 6], align="left")

#Validações
def schedule_test_vector_30():
    app.after(ms_valida*3, valida_test_vector_30)

def schedule_hold_time_30():
    app.after(ms_valida, valida_hold_time_30)

def valida_test_vector_30():
    try:
        test_vector = test_vector_input_30.value.strip()

        if test_vector != "":
            if len(test_vector) != 12 or not all(char in '01' for char in test_vector):
                raise ValueError("Vetor de teste em formato inválido")
            error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro Pino 30: Vetor de Teste deve ser um valor binário de 12 bits."
        test_vector_input_30.value = ""

test_vector_input_30.when_key_pressed = schedule_test_vector_30

def valida_hold_time_30():
    try:
        hold_time = int(bit_hold_time_30.value)
        if hold_time < hold_time_min or hold_time > hold_time_max:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = f"Erro Pino 30: Bit Hold Time deve estar entre {hold_time_min} ms e {hold_time_max} ms."
        bit_hold_time_30.value = ""  

bit_hold_time_30.when_key_pressed = schedule_hold_time_30

def configuracao_pino_30():
    pin_leitura_30 = 1 if result_pin_output_checkbox_30.value else 0
    enable_pwm_ch_7 = 1 if enable_pwm_pin_30.value else 0
    config_pino_30 = [
        pin_leitura_30,
        enable_pwm_ch_7,
        test_vector_input_30.value if test_vector_input_30.value else 0,
        bit_hold_time_30.value if bit_hold_time_30.value else 0
    ]
    pinos_valores["30"] = config_pino_30

# Error Message Box
error_message_box = Box(app, width="fill", align="bottom", border=True)
error_message = Text(error_message_box, text="", color="red", align="bottom")

################ BOTÕES DE AÇÃO #################

# Configuração botões de comando
config_btn_box = Box(content_box, layout="grid", width="fill", height="fill",
                     align="left", border=True, grid=[0, 4])

# Send Configuration Button
send_config_button = PushButton(config_btn_box, command=send_test_config,
                          text="SEND CONFIGURATION", grid=[0,0], align="left")

# Start Button
start_button = PushButton(config_btn_box, command=start_test,
                          text="START TEST", grid=[1,0], align="left")

# Reset System
reset_button = PushButton(config_btn_box, command=reset_system,
                          text="RESET ESP", grid=[2,0], align="left")


# Display
app.display()


