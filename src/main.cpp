#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

const char* ssid = "Redmi Note 14";
const char* password = "12345678";

// URL de tu Sentilo (cambia puerto si es otro)
String url = "http://147.83.83.21:8081/data/grup_1-102@Eficiencia_llum/sensor_de_llum/345";

// Token del provider creado en catálogo
String token = "e15a0aaa8d84c9bf7087e31fce2e23bc1fa3f8a64ce65914203a6648cb5df9fe";

// Simulamos un sensor (sustituye por tu lectura)
int pinSensor = 34;

void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando proceso");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado al WiFi!");
}

void loop() {
  int valor = 345;//analogRead(pinSensor);  // lectura del sensor (0-4095)
  float lux = valor * (10000.0 / 4095.0); // ejemplo de conversión
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);

    // Cabeceras
    //http.addHeader("Content-Type", "application/json");
    http.addHeader("IDENTITY_KEY", token);

    // JSON de envío
    // String json = "{\"observations\":[{\"value\":\"" + String(lux) + "\"}]}";

    int code = http.PUT("");
    Serial.print("Código respuesta Sentilo: ");
    Serial.println(code);
    String respuesta = http.getString(); // Aquí obtienes toda la respuesta
    Serial.println("Respuesta completa:");
    Serial.println(respuesta);


    http.end();
  }

  delay(5000); // cada 5 segundos
}
