#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
 
/* Definições do LED */
#define PIN_LED  4
 
/* Definicoes do sensor DHT22 */
#define DHTPIN 2     //GPIO que está ligado o pino de dados do sensor
 
#define DHTTYPE DHT11 //sensor em utilização: DHT11

 
/* Defines do MQTT */
#define TOPICO_SUBSCRIBE_LED         "topico_liga_desliga_ledmu"
#define TOPICO_PUBLISH_TEMPERATURA   "topico_sensor_temperaturamu" 
#define TOPICO_PUBLISH_UMIDADE       "topico_sensor_umidademu" 
 
#define ID_MQTT  "testemu"     //id mqtt (para identificação de sessão)
            //Nota: este ID deve ser unico, a duplicidade de ID no broker pode levar a erro no sistema 

float leTemp; // variavel para controlar o rele
 
/* Variaveis, constantes e objetos globais */
DHT dht(DHTPIN, DHTTYPE);
 
const char* SSID = "Bruno e Camila"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "rioclaro2020"; // Senha da rede WI-FI que deseja se conectar
 
const char* BROKER_MQTT = "test.mosquitto.org"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
   
//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
 
/* Prototypes */
float faz_leitura_temperatura(void);
float faz_leitura_umidade(void);
void initWiFi(void);
void initMQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void VerificaConexoesWiFIEMQTT(void);
 
/*
 * Implementações
 */
 
/* Função: faz a leitura de temperatura (sensor DHT22)
 * Parametros: nenhum
 * Retorno: temperatura (graus Celsius)
 */
float faz_leitura_temperatura(void)
{
    float t = dht.readTemperature();
    float result;
    leTemp = t;
    
    if (leTemp>30){digitalWrite(PIN_LED, LOW);}
    if (leTemp<28){digitalWrite(PIN_LED, HIGH);} 
    
    if (! (isnan(t)) )
        result = t;
    else
        result = -99.99;
 
    return result;
}
 
/* Função: faz a leitura de umidade relativa do ar (sensor DHT22)
 * Parametros: nenhum
 * Retorno: umidade (0 - 100%)
 */
float faz_leitura_umidade(void)
{
    float h = dht.readHumidity();    
    float result;
     
    if (! (isnan(h)) )
        result = h;
    else
        result = -99.99;
 
    return result;
}
 
/* Função: inicializa e conecta-se na rede WI-FI desejada
*  Parâmetros: nenhum
*  Retorno: nenhum
*/
void initWiFi(void) 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
      
    reconnectWiFi();
}
 
/* Função: inicializa parâmetros de conexão MQTT(endereço do 
 *         broker, porta e seta função de callback)
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void initMQTT(void) 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
 
/* Função: função de callback 
 *         esta função é chamada toda vez que uma informação de 
 *         um dos tópicos subescritos chega)
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
  
    /* obtem a string do payload recebido */
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
 
    Serial.print("Chegou a seguinte string via MQTT: ");
    Serial.println(msg);
    
    /* toma ação dependendo da string recebida */

}
 
/* Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
 *         em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void reconnectMQTT(void) 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE_LED); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}
 
/* Função: verifica o estado das conexões WiFI e ao broker MQTT. 
 *         Em caso de desconexão (qualquer uma das duas), a conexão
 *         é refeita.
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
      
     reconnectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
 
/* Função: reconecta-se ao WiFi
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void reconnectWiFi(void) 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
          
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
      
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
    
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}
  
/* Função de setup */
void setup() 
{
    Serial.begin(115200);  
 
    /* Configuração do pino ligado ao LED como output 
       e inicialização do mesmo em LOW */
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED,LOW);
 
    /* Inicializacao do sensor de temperatura */
    dht.begin();  
 
    /* Inicializa a conexao wi-fi */
    initWiFi();
 
    /* Inicializa a conexao ao broker MQTT */
    initMQTT();
}
 
/* Loop principal */
void loop() 
{
    char temperatura_str[10] = {0};
    char umidade_str[10]     = {0};
    Serial.print("Temperatura atual: ");
    Serial.println(leTemp); 
    /* garante funcionamento das conexões WiFi e ao broker MQTT */
    VerificaConexoesWiFIEMQTT();
 
    /* Compoe as strings a serem enviadas pro dashboard (campos texto) */
    sprintf(temperatura_str,"%.2fC", faz_leitura_temperatura());
    sprintf(umidade_str,"%.2f", faz_leitura_umidade());
 
    /*  Envia as strings ao dashboard MQTT */
    MQTT.publish(TOPICO_PUBLISH_TEMPERATURA, temperatura_str);
    MQTT.publish(TOPICO_PUBLISH_UMIDADE, umidade_str);
   
    /* keep-alive da comunicação com broker MQTT */
    MQTT.loop();
 
    /* Refaz o ciclo após 2 segundos */
    delay(5500);
}
