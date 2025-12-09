#include <Wire.h>
#include "Adafruit_TCS34725.h"

// --- Configuración de Pines ---
// Puedes cambiar estos números según tu montaje real
#define I2C_SDA 9
#define I2C_SCL 8

// Inicializamos el sensor con un tiempo de integración de 50ms y ganancia 4x
// Esto ofrece un buen equilibrio entre velocidad y sensibilidad
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup()
{
    Serial.begin(115200);

    // Configurar pin del LED
    // pinMode(PIN_LED, OUTPUT);
    // digitalWrite(PIN_LED, LOW); // Apagado al inicio

    // Iniciar I2C manualmente en los pines elegidos para ESP32-S3
    Wire.begin(I2C_SDA, I2C_SCL);

    Serial.println("Iniciando sensor TCS34725...");

    if (tcs.begin())
    {
        Serial.println("Sensor encontrado correctamente.");
    }
    else
    {
        Serial.println("No se encuentra el TCS34725. Revisa las conexiones.");
        Serial.println("Asegúrate de que SDA y SCL no están intercambiados.");
        while (1)
            ; // Detener ejecución si falla
    }
}

void loop()
{
    uint16_t r, g, b, c, colorTemp, lux;

    // 1. Encender LED para iluminar la muestra
    // digitalWrite(PIN_LED, HIGH);
    delay(60); // Esperar un poco más que el tiempo de integración (50ms) para estabilizar

    // 2. Leer datos crudos
    tcs.getRawData(&r, &g, &b, &c);

    // 3. Apagar LED (opcional, para ahorrar energía o no molestar)
    // digitalWrite(PIN_LED, LOW);

    // 4. Calcular temperatura de color y lux (fórmulas de la librería)
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);

    // 5. Mostrar resultados
    Serial.print("Color Temp: ");
    Serial.print(colorTemp);
    Serial.print(" K - ");
    Serial.print("Lux: ");
    Serial.print(lux);
    Serial.print(" - ");
    Serial.print("R: ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print("G: ");
    Serial.print(g);
    Serial.print(" ");
    Serial.print("B: ");
    Serial.print(b);
    Serial.print(" ");
    Serial.print("C: ");
    Serial.print(c);
    Serial.println(" ");

    delay(1000); // Pausa antes de la siguiente lectura
}