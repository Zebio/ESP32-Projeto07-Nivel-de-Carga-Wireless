#include <Arduino.h>
#include <WiFi.h>

/*---------------------Mapeamento de Hardware----------------------*/
#define pino_de_medicao 33


/*---------------------Constantes de Projeto ----------------------*/
const char * ssid = "nome_da_rede";
const char * password = "nome_da_senha";


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
  Serial.println(tensao);
  delay(1000);

///4095)*16.5);
  // put your main code here, to run repeatedly:
}