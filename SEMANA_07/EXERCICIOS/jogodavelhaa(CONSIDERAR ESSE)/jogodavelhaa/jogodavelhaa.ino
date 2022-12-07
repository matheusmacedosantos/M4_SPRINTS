//atividade de programacao semana 7 Matheus Macedo Santos
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define led_verde  15
#define led_vermelho 16

int pontop1 = 0;
int pontop2 = 0;

int pergtotal = 0;

const char *ssid = "matues"; //Digite o nome da sua rede aqui
const char *password = "Matues123"; //Digite a senha da rede, deve conter no mínimo 8 caractéres se não dá erro.

WebServer server(80);

void setup() {

  Serial.begin(115200);

  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);

  WiFi.softAP(ssid, password); // remova "password" caso não queria que o Wi-Fi tenha senha
  IPAddress ESP_IP = WiFi.softAPIP();
  Serial.print("Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("IP: "); // O IP que aparecer aqui coloque no navegador para acessar a página web do ESP32 que será criada logo abaixo.
  Serial.println(ESP_IP);
  server.begin();
  Serial.println("Servidor Iniciado.");
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
  void handleRoot(){
    String html = "";
    html += "<meta charset='UTF-8'>";
    html += "<body style='background: linear-gradient(90deg, rgb(2, 3, 0) 0%, rgb(89, 84, 75) 100%);'>";
    html += "<h1 style=' font-family: cursive; color: rgb(214, 40, 40); padding: 36px 50px; margin-top: 30px; margin-left: 50px;'>Player 1</h1>";
    html += "<h1 style=' font-family: cursive; color: rgb(214, 40, 40); padding: 36px 50px; margin-top: -60px; margin-left: 50px;'>Pontos: ";
    html += pontop1;
    html += "</h1>";
    html += "<h1 style=' font-family: cursive;  color: rgb(214, 40, 40); padding: 36px 50px; margin-top: -200px; margin-left: 950px;'>Player 2</h1>";
    html += "<h1 style=' font-family: cursive;  color: rgb(214, 40, 40); padding: 36px 50px; margin-top: -65px; margin-left: 950px;'>Pontos: ";
    html += pontop2;
    html += "</h1>";
    html += "<h1    style=' font-family: cursive; color: white; text-align: center; padding: 36px 50px; margin-top: 30px;'>Teste de matematica</h1>";
    html += "<h2  style=' text-align: center; font-family: cursive; color: white; margin-left: 540px';> 1) Resultado de 9x2? </h2> <br><br><br>";
    html += "<h2><a href=\"/on\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 18</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 24</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 8</a></h2><br><br><br>";
    
    html += "<h2 style='text-align: center; font-family: cursive; color: white; margin-left: 540px';> 2) Resultado de 2+5x7? </h2> <br><br><br>";
    html += "<h2><a href=\"/off\" style=' text-align: center; font-family: cursive;  background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 49</a></h2><br><br><br>";
    html += "<h2><a href=\"/on\" style=' text-align: center; font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 37</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 33</a></h2><br><br><br>";

    html += "<h2 style='text-align: center;  font-family: cursive; color: white; margin-left: 540px';> 3) Qual numero mais proximo de pi? </h2> <br><br><br>";
    html += "<h2><a href=\"/off\" style=' text-align: center; font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 3</a></h2><br><br><br>";
    html += "<h2><a href=\"/on\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 3,15</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 3,5</a></h2><br><br><br>";

    html += "<h2 style='text-align: center;  font-family: cursive; color: white; margin-left: 540px';> 4) Se uma pessoa esta vindo em velocidade constante por 500m e demora 2 minuto para chegar ao ponto final, qual é a sua velocidade aproximadamente? </h2> <br><br><br>";
    html += "<h2><a href=\"/on\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 4m/s</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 5m/s</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 6m/s</a></h2><br><br><br>";

    html += "<h2><a href=\"/off\" style='text-align: center;  font-family: cursive; background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 485px;'>Proximo jogador</a></h2><br><br><br>";

    html += "</body>";
    server.send(200, "text/html", html);
  }

  void handleOn(){
    if(pergtotal >= 4){
    digitalWrite(led_verde, HIGH);
    pontop2 += 1;
    pergtotal += 1;
    delay(2000);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    handleRoot();
    } else{    
    digitalWrite(led_verde, HIGH);
    pontop1 += 1;
    pergtotal += 1;
    delay(2000);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    handleRoot();
    }
  }
  void handleOff(){
    digitalWrite(led_vermelho, HIGH);
    delay(2000);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_verde, LOW);
    pergtotal +=1;
    handleRoot();
  }
  void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; 
  }
  server.send(404, "text/plain", message);
}

void loop() {
  server.handleClient();
  if (pergtotal >= 8){
    delay(2000);
    pontop1 = 0;
    pontop2 = 0;
    pergtotal = 0;
    delay(2000); 
  }
  delay(2);
} 
