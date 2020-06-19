# Objetos Inteligentes

**Projeto feito na matéria de Objetos Inteligentes conectados.**

**Descrição:**

Nosso projeto é uma solução que integra um sensor de temperatura e
um de umidade, um alarme para emitir som quando se atingir uma certa temperatura
ou umidade. Pode ser usado como um simples termômetro e sensor de umidade, possui
integração com redes Wi-Fi e envia esses dados para um celular ou pode ser usado
como um alarme de forma a alertar quando uma certa temperatura ou umidade forem
alcançadas em um local.

**Componentes de hardware utilizados:**

Placa ESP8266E
O microcontrolador ESP8266 é Um chip desenvolvido pela empresa chinesa Espressif.
O módulo Wifi ESP8266 NodeMCU é uma placa de desenvolvimento que combina o chip ESP8266, uma interface usb-serial e um regulador de tensão 3.3V. A programação pode ser feita usando LUA ou a IDE do Arduino, utilizando a comunicação via cabo micro-usb.

Módulo DTH11

Sensor de umidade e temperatura integrado em um só módulo de baixo custo. Este sensor
utiliza um termistor para medir a temperatura e um sensor capacitivo para medir a umidade
do ambiente. Este sensor é uma excelente opção para monitoramento e controle
climatização.
O DHT11 possui um controlador de 8 bits que converte o sinal de temperatura e
umidade dos sensores e um sinal serial e envia ao Arduino através do pino de dados
(Data).

 Relé 1 Canal Seco
 
É uma placa de interface que agiliza e simplifica o uso de relés em seus projetos. O módulo
relé 1 canal é usado para acionar cargas de variadas tensões e correntes. Com isso, pode-se
ligar e desligar aparelhos de quase todos os tipos, com limite de corrente de 10A. Pode ser
usado ligado diretamente a sensores, microcontroladores ou qualquer circuito que use
lógica TTL.
Ao se trabalhar com sistemas inteligentes, é comum a necessidade de se controlar cargas
das mais diversas potências, tal como: lâmpadas, motores, resistências, etc. O componente
mais usado para ligar e desligar esses aparelhos são o relés. O relés são responsáveis por
ligar e desligar equipamentos através de comandos.

Carregador Tomada Plug Adaptador Fonte Usb 5v 2.1a Bivolt

Adaptador de alta performance para carregamento de dispositivos com entrada USB, feito
em material resistente e durável. Indicado para dispositivos com cabos USB que necessitam
ligar na Tomada (100-240v).

A plataforma utilizada para desenvolvimento foi a Arduino Ide.

**Documentação do Protocolo MQTT:**

http://mqtt.org/documentation

**Funcionalidades:**

-float faz_leitura_temperatura(void)

Faz a leitura de temperatura utilizando o sensor.

-float faz_leitura_umidade(void)

Faz a leitura de umidade utilizando o sensor.

-void initWiFi(void)

Inicializa e conecta-se na rede WI-FI desejada

-void initMQTT(void)

inicializa parâmetros de conexão MQTT

-void mqtt_callback(char* topic, byte* payload, unsigned int length) 

Função de callback esta função é chamada toda vez que uma informação de um dos tópicos subescritos chega.

-void reconnectMQTT(void)

Reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.

-void VerificaConexoesWiFIEMQTT(void)

Verifica o estado das conexões WiFI e ao broker MQTT. 
Em caso de desconexão (qualquer uma das duas), a conexão é refeita

-void reconnectWiFi(void)

Reconecta-se ao WiFi

-void setup()

Função de setup

-void loop()

Loop principal

**Arquitetura do Projeto**

![diagramaprojeto](https://user-images.githubusercontent.com/11764088/84574131-f5392600-ad7a-11ea-8942-bcc8c42aaa9d.PNG)

