#include <Arduino.h>
#include <WiFi.h>

/*---------------------Mapeamento de Hardware----------------------*/
#define pino_de_medicao 33



/*---------------------Constantes de Projeto ----------------------*/
#define valorAdc         4095
#define tensaoMaxima     16.5



const char * ssid = "tira_o_zoio";
const char * password = "jabuticaba";


/*---------------------Variáveis Globais    ----------------------*/
float tensao =0.0;

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

}

void loop() {
  tensao = analogRead(pino_de_medicao);
  Serial.print("Valor DAC: ");
  Serial.print(tensao);
  Serial.print("   Valor em Tensão");
  tensao = (tensao/valorAdc*tensaoMaxima); //como o valor medido de tensão é atenuado em 5 vezes,
                               // 16.5V na ponta de prova equivale a 3.3V no ESP.
                               // Para voltar ao valor original dividimos por
                               // 4095 (3.3V no ADC) multiplicado por 16.5V
   Serial.println(tensao);
   tensao += (tensao*0.1);
   Serial.print("   Valor Corrigido");
   Serial.println(tensao);
  
  delay(1000);

///4095)*16.5);
  // put your main code here, to run repeatedly:
}