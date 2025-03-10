#include <HTTP_Method.h>
#include <Middlewares.h>
#include <Uri.h>
#include <WebServer.h>

#include <WiFi.h>

// pin del LED a encender/apagar
const int pinLED = 2;

// Puerto http del servidor
WebServer Server(80);

const char * ssid = "NOMBRE DE LA RED WIFI";
const char * contrasena = "654321";

void setup() {
  // put your setup code here, to run once:

  // Pin modo salida
  pinMode(pinLED, OUTPUT);

  Serial.begin(115200); // recomendado para esp32
  WiFi.begin(ssid, contrasena);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  // Cuando ya se haya conectado
  Serial.println("Conectado a WiFi");
  Serial.println("Direccion IP del ESP32: ");
  // Mostramos la IP en consola (Utilizada para realizar las requests desde Django)
  Serial.println(WiFi.localIP());


  // Inicializar el servidor web
  Server.begin();
  // Utilizando el servidor para que maneje petición GET y encender el led
  Server.on("/led/on", HTTP_GET, []() {
    digitalWrite(pinLED, HIGH); // ENCENDER LED
    Serial.println("1");
    // Enviar un ok
    Server.send(200, "text/plain", "LED esta encendido");

  });

  // Utilizando el servidor para que maneje petición GET y apagar el led
  Server.on("/led/off", HTTP_GET, []() {
    digitalWrite(pinLED, LOW); // APAGAR LED
    Serial.println("2");
    // Enviar un ok
    Server.send(200, "text/plain", "LED esta apagado");

  });

}

void loop() {
  // put your main code here, to run repeatedly:
  // Código cuando ya esté conectado pa que se repita
  Server.handleClient(); // El cliente será el usuario de HTML 
  
}
