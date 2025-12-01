#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>
#include <Adafruit_TCS34725.h>

// I2C: Ambos sensores se comunican usando I2C.
// Las direcciones I2C predeterminadas suelen ser 0x39.
// Las direcciones se configuran en el constructor o begin().

// 1. Configuración del sensor TSL2561 (Luminosidad)
// Puedes especificar la dirección I2C (TSL2561_ADDR_FLOAT, TSL2561_ADDR_LOW, TSL2561_ADDR_HIGH)
Adafruit_TSL2561 tsl = Adafruit_TSL2561(TSL2561_ADDR_FLOAT);

// 2. Configuración del sensor TCS34725 (Color RGB)
// El constructor no toma argumentos para la dirección I2C por defecto.
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);
// Puedes ajustar el tiempo de integración y la ganancia si es necesario.

void setup(void)
{
    Serial.begin(115200);

    // Inicialización del sensor TSL2561
    if (!tsl.begin())
    {
        Serial.println("¡Error! TSL2561 no encontrado. Verifica las conexiones I2C.");
        while (1)
            ;
    }
    // Configurar la ganancia y el tiempo de integración para el TSL2561
    tsl.setGain(TSL2561_GAIN_16X);                // O TSL2561_GAIN_1X
    tsl.setTiming(TSL2561_INTEGRATIONTIME_402MS); // O TSL2561_INTEGRATIONTIME_13MS / 101MS
    Serial.println("TSL2561 iniciado.");

    // Inicialización del sensor TCS34725
    if (!tcs.begin())
    {
        Serial.println("¡Error! TCS34725 no encontrado. Verifica las conexiones I2C.");
        while (1)
            ;
    }
    Serial.println("TCS34725 iniciado.");
}

void loop(void)
{
    // --- LECTURA DEL TSL2561 (Luminosidad) ---

    // Obtener los datos del canal Visible (broadband) e Infrarrojo (ir)
    uint16_t broadband, ir;
    tsl.getLuminosity(&broadband, &ir);

    // Calcular el nivel de iluminación (Lux)
    uint32_t lux = tsl.calculateLux(broadband, ir);

    // Mostrar la luminosidad
    Serial.print("Luminosidad (Lux): ");
    Serial.println(lux);

    // Nota: 'broadband' también representa la luz visible (más que ir),
    // pero el valor 'lux' ya está calibrado.

    // --- LECTURA DEL TCS34725 (Color RGB) ---

    // Variables para los valores R, G, B y Clear (luminosidad total)
    uint16_t r, g, b, c;

    // Leer los valores de color sin bloqueo
    tcs.getRawData(&r, &g, &b, &c);

    // Opcional: convertir los valores a escala de 8 bits (0-255)
    uint32_t sum = c;
    float rf, gf, bf;
    rf = (float)r / sum;
    gf = (float)g / sum;
    bf = (float)b / sum;

    // Multiplicar por 256 o 255 para obtener un valor 8-bit (0-255)
    uint8_t red_8bit = rf * 256;
    uint8_t green_8bit = gf * 256;
    uint8_t blue_8bit = bf * 256;

    // Mostrar los valores separados R, G, B
    Serial.println("--- Valores de Color RGB ---");
    Serial.print("R (Raw): ");
    Serial.print(r);
    Serial.print(" | R (8-bit): ");
    Serial.println(red_8bit);
    Serial.print("G (Raw): ");
    Serial.print(g);
    Serial.print(" | G (8-bit): ");
    Serial.println(green_8bit);
    Serial.print("B (Raw): ");
    Serial.print(b);
    Serial.print(" | B (8-bit): ");
    Serial.println(blue_8bit);
    Serial.print("C (Clear/Luminosidad): ");
    Serial.println(c);
    Serial.println("----------------------------");

    // --- Preparación para Sentilo ---
    // Estos son los datos que deberás formatear y enviar a la API de Sentilo.
    // Por ejemplo, usando una conexión WiFi y una petición HTTP POST/PUT.
    /*
    Datos a enviar a Sentilo:
    - Luminosidad: lux
    - Componente R: red_8bit (o r)
    - Componente G: green_8bit (o g)
    - Componente B: blue_8bit (o b)
    */

    delay(2000); // Esperar 2 segundos antes de la siguiente lectura
}