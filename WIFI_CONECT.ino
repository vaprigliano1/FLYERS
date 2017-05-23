#include <ESP8266WiFi.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 
const char* ssid = "XT1097 8373"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
//const char* password = "victor1234"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR


 
int id = 1; //Identificação de qual conjunto de sensores está sendo enviado aquela informação

WiFiServer server(80); 
void setup() {
Serial.begin(9600); 
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
int sensorValue = analogRead(A0);

Serial.println("Valor LDR1:");
Serial.println(sensorValue); //mostra o valor do LDR
delay(1000);              
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
client.println("<body>");
client.println("<form>");
client.println("<h1><center>V5 SENSORS</center></h1>"); //ESCREVE ALGO NA PÁGINA
client.println("<center><font size='5'>Verifique as salas a baixo: </center>"); 
client.println("<center><font size='7'>SALA 1:</center>"); 
client.println("");
client.println("");
client.println("");
client.println("");
if (sensorValue <30  )
  client.println ("<center><font size='5'>Sala Livre</center>"); // Sala Dísponivel pois a luz é menor que 400, supomos que a sala está apagada. 
else
  client.println ("<center><font size='5'>Sala Ocupada</center>"); // Sala Ocupada pois a uz é maior que 400, assumimos que a luz esta acessa
//client.println( "<html><head> <meta http-equiv='refresh' content='3'></head><body><center>");
client.println("</html>"); //FECHA A TAG "html"
delay(1); //INTERVALO DE 1 MILISEGUNDO
Serial.println("Cliente desconectado"); //ESCREVE O TEXTO NA SERIAL
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
}
