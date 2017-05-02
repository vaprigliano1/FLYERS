#include <ESP8266WiFi.h>
 
const char* ssid = ""; //Escrever o nome da rede
const char* password = ""; //senha
 
int ldr = 0; //definindo LDR na porta A0 da placa
int valorldr = 0;//armazenando as infos do LDR
 
int id = 1; //Identificação de qual conjunto de sensores está sendo enviado aquela informação
//(Caso você deseje aplicar mais de um conjunto de sensores)
 
String myIPAddrStr; //Variável para armazenamento do IP gerado para acesso do Webservice.
// Se quiser criar um IP fixo (vamos tentar),só precisa descomentar as linhas 14,15,16.
//IPAddress ip(192,168,72,171); //Alterar aqui para o IP Desejado
//IPAddress gateway(192,168,72,1); //Gateway da rede
//IPAddress subnet(255,255,255,0);//Mascara da rede
 
WiFiServer server(80); //Definição para o webservice utilizar a porta 80.
 
void setup() {
Serial.begin(9600);
delay(10);
 
// inicia a conexão com a rede
Serial.println();
Serial.println();
Serial.print("ESP8266 Conectando à ");
Serial.println(ssid);
 
WiFi.begin(ssid, password); //Inicia a conexão WiFi
//WiFi.config(ip, gateway, subnet); //se usar IP fixo, descomentar essa linha
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("Conectado");
server.begin();
myIPAddrStr = String(WiFi.localIP().toString());
Serial.println(WiFi.localIP()); //utilizar o IP gerado aqui.
}
 
void loop() {
delay(2000);
valorldr = analogRead(ldr);
 
WiFiClient client = server.available(); // Comparação se o cliente Wifi, está disponível
if (!client) {
return;
}
 
Serial.println("Webserver gerado.");
while(!client.available()){
delay(1);
}
String req = client.readStringUntil('\r');
Serial.println(req);
client.flush();
String url = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
//Geração da página HTML
url += "<html>\r\n";
url += "<title>Monitoramento de Salas de Estudo</title>";
url += "<center><h1>Acompanhe as salas de estudo:</h1>";
url += "<br/>";
url += "<br/>";
url += "<br/>";
url += "<b>Sala 1 = </b>"; //adicionar : if luminosidade > x (print:indisponivel)
url += valorldr;
url += "<br/>";
url += "<b>Intens. Sinal = </b> "; 
url += "<br/>";
url += "<b>IP = </b>";
url += String(myIPAddrStr);
url += "<br/>";
url += "<input type=""button"" value=""Atualizar"" onClick=""history.go(0)"">" ; //Essa linha gera um botão p/ atualizar a página do webservice.
url += "<br/>";
url += "<br/>";
url += "<br/>";
url += "<br/>";
url += "<br/>";
url += "<br/>";
url += "<b>Obrigado por usar a V5. Bons Estudos! </b> ";
url += "</center></html>\n";
client.print(url);
 
Serial.println();
Serial.println("Fechando a conexão");
delay(30000); //Espera 30 segundos e recomeça o loop.
}
