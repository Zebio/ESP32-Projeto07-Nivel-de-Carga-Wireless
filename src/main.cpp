#include <Arduino.h>
#include <WiFi.h>

/*---------------------Mapeamento de Hardware----------------------*/
#define carga 5


/*---------------------Constantes de Projeto ----------------------*/
const char * ssid = "nome_da_rede";
const char * password = "senha_da_rede";


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
  // put your main code here, to run repeatedly:
}