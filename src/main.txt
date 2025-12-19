#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// --- DATOS WIFI ---
const char *ssid = "Redmi Note 14";
const char *password = "12345678";

// --- DATOS SENTILO ---
String baseUrl = "http://147.83.83.21:8081/data/grup_1-102@Eficiencia_llum";
String token = "e15a0aaa8d84c9bf7087e31fce2e23bc1fa3f8a64ce65914203a6648cb5df9fe";

// --- CONFIGURACIÓN SENSOR ---
#define I2C_SDA 9
#define I2C_SCL 8
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// --- FUNCIÓN AUXILIAR PARA ENVIAR ---
void enviarASentilo(String nombreComponente, int valor)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        String urlCompleta = baseUrl + "/" + nombreComponente + "/" + String(valor);

        // Descomenta la siguiente línea si quieres ver también las URLs que se envían
        // Serial.println("Enviando a: " + urlCompleta);

        http.begin(urlCompleta);
        http.addHeader("IDENTITY_KEY", token);

        int code = http.PUT("");

        if (code > 0)
        {
            // Si quieres ver confirmación de cada envío, descomenta esto:
            // Serial.print("  -> Enviado " + nombreComponente + " (Código " + String(code) + ")");
        }
        else
        {
            Serial.print("  -> Error enviando " + nombreComponente + ": ");
            Serial.println(http.errorToString(code));
        }
        http.end();
    }
    else
    {
        Serial.println("Error: WiFi desconectado");
    }
}

void setup()
{
    Serial.begin(115200);

    // 1. Iniciar I2C y Sensor
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!tcs.begin())
    {
        Serial.println("¡ERROR GRAVE! No se encuentra el sensor TCS34725.");
        while (1)
            ;
    }
    Serial.println("Sensor TCS34725 encontrado OK.");

    // 2. Conectar WiFi
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado al WiFi!");
}

void loop()
{
    // --- A. LECTURA SENSOR ---
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    int lux = tcs.calculateLux(r, g, b);

    // --- DEBUG: MOSTRAR VALORES EN PANTALLA ---
    Serial.println("\n------------------------------------------------");
    Serial.println("LECTURA DEL SENSOR:");
    Serial.print("Rojo (R):  ");
    Serial.println(r);
    Serial.print("Verde (G): ");
    Serial.println(g);
    Serial.print("Azul (B):  ");
    Serial.println(b);
    Serial.print("Clear (C): ");
    Serial.println(c);
    Serial.print("Lux:       ");
    Serial.println(lux);
    Serial.println("------------------------------------------------");

    // --- B. ENVÍO DE LOS 4 COMPONENTES ---
    Serial.println("Iniciando subida a Sentilo...");

    enviarASentilo("sensor_de_llum", lux);
    delay(100);
    enviarASentilo("RGB_R", r);
    delay(100);
    enviarASentilo("RGB_G", g);
    delay(100);
    enviarASentilo("RGB_B", b);

    Serial.println("Subida finalizada. Esperando 5 segundos...");

    delay(5000);
}