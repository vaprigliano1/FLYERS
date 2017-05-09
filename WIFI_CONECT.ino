#include <ESP8266WiFi.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 
const char* ssid = "XT1097 8373"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
//const char* password = "senha_da_sua_rede_WIFI"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR

int ldr = 0; //definindo LDR na porta A0 da placa
int valorldr = 0;//armazenando as infos do LDR
 
int id = 1; //Identificação de qual conjunto de sensores está sendo enviado aquela informação

WiFiServer server(80); 
void setup() {
valorldr = analogRead(ldr);
Serial.begin(115200); 
delay(10); 
Serial.println(""); //PULA LINHA
Serial.println(""); 
Serial.print("Conectando a "); 
Serial.print(ssid); 
 
WiFi.begin(ssid); 
 
while (WiFi.status() != WL_CONNECTED) { 
delay(500); 
Serial.print("."); 
}
Serial.println(""); 
Serial.print("Conectado a rede sem fio "); 
Serial.println(ssid); 
server.begin(); 
Serial.println("Servidor iniciado"); 
 
Serial.print("IP para se conectar ao NodeMCU: ");
Serial.print("http://"); 
Serial.println(WiFi.localIP()); 
}
void loop() {
WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR
if (!client) { 
return; 
}
Serial.println("Novo cliente se conectou!"); 
while(!client.available()){ 
delay(1); 
}
String request = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
Serial.println(request); 
client.flush(); 
 
client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
client.println("");
client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
client.println("<html>"); //ABRE A TAG "html"
client.println("<h1><center>V5 SENSORS</center></h1>"); //ESCREVE ALGO NA PÁGINA
client.println("<center><font size='5'>Verifique as salas a baixo: </center>"); 
client.println("");
client.println("");
client.println("");
client.println("");
client.println("");
client.println("<center><font size='10'>SALA 1:</center>"); 
client.println("");
client.println("");
client.println("");
client.println("");
if (valorldr < 200)
  client.println ("<center><font size='5'>Sala Livre</center>"); // "Sala Dísponivel"
else
  client.println ("<center><font size='5'>Sala Ocupada</center>"); // "Sala Ocupada"
client.println("</html>"); //FECHA A TAG "html"
delay(1); //INTERVALO DE 1 MILISEGUNDO
Serial.println("Cliente desconectado"); //ESCREVE O TEXTO NA SERIAL
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
}
