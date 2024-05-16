import socket, time

def envia_mensagem_udp(ip_destino, porta_destino, pino_valor):
    # Cria um socket UDP
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Divide o dicionário em conjuntos de três itens
    conjuntos = [list(pino_valor.items())[i:i+1] for i in range(0, len(pino_valor), 1)]

    # Itera sobre cada conjunto de três itens
    for conjunto in conjuntos:
        # Monta a mensagem com os valores dos pinos para este conjunto
        mensagem = ""
        for pino, valores in conjunto:
            mensagem += f"\n{pino}: {', '.join(str(valor) for valor in valores)}"
        
        # Envia a mensagem para o endereço IP e porta especificados
        udp_socket.sendto(mensagem.encode(), (ip_destino, porta_destino))
        time.sleep(0.250)

        #Printa mensagem
        print(mensagem)

    # Fecha o socket
    udp_socket.close()

def envia_start_mensagem_udp(ip_destino, porta_destino, mensagem):
    # Cria um socket UDP
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    mensagem = mensagem

    udp_socket.sendto(mensagem.encode(), (ip_destino, porta_destino))
    
    # Fecha o socket
    udp_socket.close()

