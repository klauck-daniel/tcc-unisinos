from guizero import App, Text, PushButton, CheckBox, TextBox, Slider, Box

# Functions
def start_test():
    print("Iniciando teste.")
    # Aqui você pode adicionar o código para iniciar o teste com as configurações selecionadas


def validate_frequency():
    try:
        freq = int(freq_input.value)
        if freq < 100 or freq > 2000:
            raise ValueError("Fora do intervalo")
        error_message.value = ""  # Limpa a mensagem de erro se a validação passar
    except ValueError:
        error_message.value = "Erro: Frequência deve estar entre 100 e 2000 Hz."
        freq_input.value = ""  # Limpa o campo de entrada

# Função para agendar a validação da frequência após 1500 ms


def schedule_frequency_validation():
    app.after(1500, validate_frequency)


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

# Pinos 4, 5, 21, 22
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


# Criar caixas para cada pino disponível
for i, pin in enumerate(available_pins):
    # Configura o box de cada pino
    row = i % 4
    col = i // 4
    pin_box = Box(parametros_box, layout="grid", grid=[col, row], width="fill", height="fill",
                  align="left", border = True)
    
    # Valores de cada box
    Text(pin_box, width = 20, text=f"Pino {pin}:", grid=[0, 0], align="left")

    Text(pin_box, text="Pin Saída:", grid=[0, 2], align="left")
    pin_output_checkbox = CheckBox(pin_box, text="", align="left", grid=[1, 2])

    Text(pin_box, text="Pin Leitura:", grid=[0, 3], align="left")
    result_pin_output_checkbox = CheckBox(
        pin_box, text="", align="left", grid=[1, 3])

    Text(pin_box, text="Frequência (Hz):", grid=[0, 4], align="left")
    freq_input = TextBox(pin_box, width=5, grid=[1, 4], align="left")

    Text(pin_box, text="Duty Cycle (%):", grid=[0, 5], align="left")
    duty_cycle_slider = Slider(
        pin_box, start=0, end=100, grid=[1, 5], align="left")

    Text(pin_box, text="Vetor de Teste:", grid=[0, 6], align="left")
    test_vector_input = TextBox(pin_box, width = 20, grid = [1, 6], align="left")

    # Descrição dos Pinos
    if pin in [8, 9]:
        Text(pin_box, text = "DAC, ADC, GPIO, PWM", grid = [0, 1], align="left")

    elif pin in [2, 3, 6, 7, 10, 11, 12, 13, 18, 19, 20]:
        Text(pin_box, text = "ADC, GPIO, PWM", grid = [0, 1], align="left")

    elif pin in [23, 24, 25, 26, 27, 28, 29, 30]:
        Text(pin_box, text = "GPIO, PWM", grid = [0, 1], align = "left")


# Error Message Box
error_message_box = Box(app, width="fill", align="bottom", border=True)
error_message = Text(error_message_box, text="", color="red", align="bottom")

# Start Button
start_button = PushButton(app, command=start_test,
                          text="START", align="bottom")

# Valida Frequencia
#freq_input.when_key_pressed = schedule_frequency_validation

# Display
app.display()
