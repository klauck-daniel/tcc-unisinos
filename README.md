# Projeto de Conclusão de Curso - Engenharia da Computação, UNISINOS

**Autor:** Daniel Rodrigo Klauck

Este projeto foi desenvolvido para a Conclusão do Curso de Engenharia da Computação na Universidade UNISINOS.

## Firmware

O firmware é utilizado juntamente com a ESP-IDF instalada no VSCode. Para rodar a aplicação, siga os seguintes passos:

1. Instale a extensão ESP-IDF no VSCode.
2. Configure a porta COM em que o ESP32 está conectado.
3. Ajuste o SSID e a PASSWORD da rede Wi-Fi utilizada.

## Interface

A interface utiliza Python 3 com a biblioteca GuiZero. Para configurar a interface:

1. Instale o Python 3 e a biblioteca GuiZero.
2. No código Python, ajuste o IP de destino para o IP que o ESP32 obtiver na rede (o IP é exibido no terminal ao gravar o firmware no ESP32).

## Obtendo Arquivos de Log

Para obter os arquivos de log:

1. Feche o terminal aberto após gravar o firmware na placa.
2. Execute o arquivo `logger.py`.

Os arquivos de log são gerados após 60 segundos a partir do momento em que o ESP32 recebe a mensagem de START. Note que os arquivos de log são sobrescritos toda vez que o `logger.py` for executado.
