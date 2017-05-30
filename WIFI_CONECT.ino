#include <ESP8266WiFi.h> //BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 
const char* ssid = "XT1097 8373"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
//const char* password = " "; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR 
 
int id = 1; //identifica o numero de sensores

WiFiServer server(80); 
void setup() {
Serial.begin(9600); //velocidade 
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
 
Serial.print("IP para se conectar ao NodeMCU: "); //utilizar o IP gerado aqui para entrar no webserver.
Serial.print("http://"); 
Serial.println(WiFi.localIP()); 
}
void loop() {
int sensorValue = analogRead(A0);
Serial.println("Valor LDR1:"); //valor que o sensor LDR (luminosidade) está lendo (0-1023).
Serial.println(sensorValue); //mostra o valor do LDR
delay(1000);              
WiFiClient client = server.available(); //verifica se tem alguem conectado
if (!client) { 
return; 
}
Serial.println("Novo cliente se conectou!"); 
while(!client.available()){ 
delay(1); 
}
String request = client.readStringUntil('\r'); 
Serial.println(request); 
client.flush(); 
client.println("HTTP/1.1 200 OK"); //escreve para o usuario a versao do HTTP
client.println("Content-Type: text/html"); //tipo de conteudo(texto/html)
client.println("");
client.println("<!DOCTYPE HTML>"); 
client.println("<html>"); //abre "html" 
client.println("<body bgcolor='9A9595'>"); //define a cor de fundo 
client.println("<form>");
client.println("<h1><center>V5 SENSORS</center></h1>"); //titulo
client.println("<br>"); //espaçamento 
client.println("<br>");
client.println("<br>");
client.println("<br>");
client.println("<center><font size='5'>Verifique as salas a baixo: </center>"); 
client.println("<br>");
client.println("<center><font size='5'>SALA 1:</center>"); 
if (sensorValue <30  ) //define se irá aparecer sala livre ou ocupada de acordo com a leitura do sensor
  client.println ("<center><font color='green'><font size='6'>LIVRE</center>"); // Sala Dísponivel pois a luz é menor que 30, supomos que a sala está apagada. 
else
  client.println ("<center><font color='red'><font size='6'> OCUPADA</center>"); // Sala Ocupada pois a uz é maior que 30, assumimos que a luz esta acessa
client.println("<br>");
client.println("<br>");
client.println("<br>");
client.println("<br>");
client.println("<br>");
client.println("<br>");
client.println ("<center><font color='black'><font size='3'> Obrigado por usar a V5!</center>");
client.println("</body>");
client.println("</html>"); //fecha "html"
delay(1); //intervalo de 1 mili segundo
Serial.println("Cliente desconectado"); //ESCREVE O TEXTO NA SERIAL
Serial.println("");
}
