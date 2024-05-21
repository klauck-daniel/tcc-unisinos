import serial
import re
import time
import os

def logger():
    port = "COM3"
    baudRate = 115200
    base_filename = "logger_PIN_{}.txt"
    
    # Expressão regular para extrair tempo e pino
    regex = re.compile(r"T: (\d+), PIN_(\d+): (\d+)")

    # Dicionário para armazenar as mensagens por pino
    dados_pinos = {i: [] for i in range(2, 10)}

    # Configuração da porta serial
    serialPort = serial.Serial(port, baudRate)
    serialPort.flushInput()
    print("Abrindo Serial")

    start_time = None
    duration = 60  # Duração de coleta em segundos
    coletando_dados = False

    while True:
        try:
            data = serialPort.readline().decode("utf-8").strip()  # Decodifica bytes para string e remove espaços em branco
            print(data)

            if 'START' in data and not coletando_dados:
                start_time = time.time()
                coletando_dados = True
                print("Iniciando coleta de dados.")
                print(f"Agaurde {duration} segundos.")

            if coletando_dados:
                match = regex.match(data)
                if match:
                    tempo, pino, valor = match.groups()
                    pino = int(pino)
                    tempo = int(tempo)
                    valor = int(valor)
                    if pino in dados_pinos:
                        dados_pinos[pino].append((tempo, valor))
                
                # Verifica se o tempo de coleta já atingiu a duração especificada
                if time.time() - start_time > duration:
                    break
        
        except Exception as e:
            print(f"Erro ao ler a linha: {e}")

    # Ordena os dados de cada pino pelo tempo
    for pino in dados_pinos:
        dados_pinos[pino].sort()

    # Cria e escreve os dados nos arquivos de log separados por pino
    for pino, entradas in dados_pinos.items():
        filename = base_filename.format(pino)
        with open(filename, "w") as file:
            file.write("Time\tValue\n")  # Cabeçalho do TXT
            for tempo, valor in entradas:
                file.write(f"{tempo}\t{valor}\n")
    
    print("Final de leituras e gravação nos arquivos de log")

logger()
