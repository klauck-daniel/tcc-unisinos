import serial

def logger():
    port = "COM3"
    baudRate = 115200
    arquivo = "logger.csv"

    serialPort = serial.Serial(port, baudRate)
    serialPort.flushInput()
    print("Abrindo Serial")

    amostra = 10
    linha = 0
    while linha <= amostra:
        data = serialPort.readline().decode("utf-8").strip()  # Decodifica bytes para string e remove espaços em branco
        print(data)
        if 'START' in data:
            with open(arquivo, "a") as file:  # Usando 'with' para garantir que o arquivo seja fechado automaticamente
                file.write(data + "\n")  # Adiciona uma nova linha após cada escrita
            linha += 1

    print("Final de leituras")

logger()