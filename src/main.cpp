#include <Arduino.h>
#include <WiFi.h>
#include <fstream>
#include <iostream>


/*---------------------Mapeamento de Hardware----------------------*/
#define pino_de_medicao 33

/*---------------------Constantes de Projeto ----------------------*/
#define valorAdc         4095
#define tensaoMaxima     16.5



const char * ssid = "tira_o_zoio";
const char * password = "jabuticaba";


/*---------------------Variáveis Globais    ----------------------*/
float tensao =0.0;
int dac12bits;
int porcentagem;

String header;






/*---------------------Constantes Cstring para Armazenar os códigos HTML ----------------------*/
const char *index1_html= "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"><title>Projeto07 - Nivel de Carga de bateria</title><script type = \"text/JavaScript\">       function AutoRefresh( t ) {   setTimeout(\"location.reload(true);\", t);}</script></head><style>html{color: #ffffff;font-family: Verdana;text-align: center;background-color: #0c0c27fd}h2{font-size: 30px;}p{font-size: 22px;}</style><body onload = \"JavaScript:AutoRefresh(1000);\"><h2>Monitoramento de Bateria IOT</h2><p> Tensao lida na bateria: ";
const char *index2_html= "</p><p> Porcentagem estimada: ";
const char *index3_html= "</p></body></html>";


/*---------------------Objetos-------------------------------------*/
WiFiServer server(80);



/*----------------------Declaração das Funções -------------------*/
void atualiza_leitura();//realiza a leitura da tensão e calcula a carga estimada

void imprime_serial();  //imprime os valores da tensão e da carga no monitor serial

void serverWifi();      //hospeda o servidor http



/*---------------------Setup Inicial        ----------------------*/
void setup() {
  Serial.begin(115200);           //inicializa Serial em 115200 baud rate
  Serial.print("Conectando-se a ");      //
  Serial.println(ssid);                  //
  WiFi.begin(ssid, password);     //conecta-se a rede wireless

  while(WiFi.status() != WL_CONNECTED)   //Espera até a conexão bem-sucedida
  {
    delay(500);                          //
    Serial.print(".");                   //imprime os pontos no monitor
  }

  Serial.println("");                    //mostra WiFi conectada
  Serial.println("WiFi conectada");      //
  Serial.println("Endereço de IP: ");    //
  Serial.println(WiFi.localIP());        //mostra o endereço IP no monitor

  server.begin();                        //Inicializa o Server

}


void loop() {
  while(WiFi.status() != WL_CONNECTED) //verifica se ainda está conectado wireless
  {
    WiFi.begin(ssid, password);        //tenta conectar denovo a cada 0.5 seg
    Serial.print(".");                   
    delay(500);                         
  }

  atualiza_leitura();
 // imprime_serial();
  serverWifi();
}

/*--------------------------Código das funções ---------------------*/

void atualiza_leitura()
{
  dac12bits = analogRead(pino_de_medicao);
  tensao = (dac12bits/valorAdc*tensaoMaxima); //como o valor medido de tensão é atenuado em 5 vezes,
                               // 16.5V na ponta de prova equivale a 3.3V no ESP.
                               // Para voltar ao valor original dividimos por
                               // 4095 (3.3V no ADC) multiplicado por 16.5V
  porcentagem = (tensao - 3.60)/0.005;
  if(porcentagem>100)
    porcentagem=100;
  if (porcentagem<0)
    porcentagem=0;
}

void imprime_serial()
{
  Serial.print("   Leitura DAC: ");
  Serial.print(dac12bits);
  Serial.print("   Tensão: ");
  Serial.print(tensao);
  Serial.print("   Carga Estimada: ");
  Serial.print(porcentagem);
  Serial.println("%");
}


void serverWifi()
{
  WiFiClient client = server.available();
  if (client) {                            
    Serial.println("Novo Cliente Conectado");        
    String currentLine = "";               
    while (client.connected()) {           
      if (client.available()) {            
        char c = client.read();            
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                 
          if (currentLine.length() == 0||currentLine=="\n") {

          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();

          Serial.println("Imprimindo pagina HTML");

          client.println(index1_html);
          client.println(tensao);
          client.println(index2_html);
          client.println(porcentagem);
          client.println(index3_html);
          client.println();
          break;
          }
          else currentLine = ""; //senão, impede string de fizer com espaços em branco
        }
        else if (c != '\r')  
          currentLine += c;      //adiciona caractere como parte da mensage
      }
    }
    header = "";                              //limpa header
    client.stop();                            //finaliza conexão
    Serial.println("Cliente desconectado"); 
    Serial.println("");  
  }
}