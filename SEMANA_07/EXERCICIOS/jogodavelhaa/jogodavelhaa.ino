#include <WiFi.h>
#include <WebServer.h>


// SSID & Password
const char* ssid = "matues";  // Enter your SSID here
const char* password = "Matues123";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}

void loop() {
  server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html><html lang='en'><head>  <meta charset='UTF-8'>  <meta http-equiv='X-UA-Compatible' content='IE=edge'>  <meta name='viewport' content='width=device-width, initial-scale=1.0'>  <title>Jogo da velha</title></head><body>  <main>    <h1>JOGO DA VELHA</h1>    <hr />    <div class='game'>      <button data-i='1'></button>      <button data-i='2'></button>      <button data-i='3'></button>      <button data-i='4'></button>      <button data-i='5'></button>      <button data-i='6'></button>      <button data-i='7'></button>      <button data-i='8'></button>      <button data-i='9'></button>    </div>    <h2 class='currentPlayer'></h2>  </main></body><script>  const currentPlayer = document.querySelector('.currentPlayer');let selected;let player = 'X';let positions = [  [1, 2, 3],  [4, 5, 6],  [7, 8, 9],  [1, 4, 7],  [2, 5, 8],  [3, 6, 9],  [1, 5, 9],  [3, 5, 7],];function init() {  selected = [];  currentPlayer.innerHTML = `JOGADOR DA VEZ: ${player}`;  document.querySelectorAll('.game button').forEach((item) => {    item.innerHTML = '';    item.addEventListener('click', newMove);  });}init();function newMove(e) {  const index = e.target.getAttribute('data-i');  e.target.innerHTML = player;  e.target.removeEventListener('click', newMove);  selected[index] = player;  setTimeout(() => {    check();  }, [100]);  player = player === 'X' ? 'O' : 'X';  currentPlayer.innerHTML = `JOGADOR DA VEZ: ${player}`;}function check() {  let playerLastMove = player === 'X' ? 'O' : 'X';  const items = selected    .map((item, i) => [item, i])    .filter((item) => item[0] === playerLastMove)    .map((item) => item[1]);  for (pos of positions) {    if (pos.every((item) => items.includes(item))) {      alert('O JOGADOR ' + playerLastMove + ' GANHOU!');      init();      return;    }  }  if (selected.filter((item) => item).length === 9) {    alert('DEU EMPATE!');    init();    return;  }}</script><style>  * {    margin: 0;    padding: 0;    box-sizing: border-box;    font-family: cursive;  }    body {    height: 100vh;    display: flex;    align-items: center;    justify-content: center;    background: #f7f7f7;  }    main {    display: flex;    flex-direction: column;    gap: 5px;  }    h1 {    text-align: center;  }    hr {    font-weight: bold;    height: 3px;    background: black;    margin-bottom: 10px;  }    .game {    display: grid;    grid-template-columns: 1fr 1fr 1fr;  }    .game button {    width: 100px;    height: 100px;    margin: 5px;    cursor: pointer;    font-size: 50px;    background: #f7f7f7;  }</style></html>"




// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
