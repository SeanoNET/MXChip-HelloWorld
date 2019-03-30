#include <OledDisplay.h>
#include <HTS221Sensor.h>

DevI2C *i2c;
HTS221Sensor *sensor;

float humidity = 0;
float temperature = 0;

unsigned char id;

const int DELAY_MS = 1000;

void setup()
{
    // Setup sensor
    i2c = new DevI2C(D14, D15);
    sensor = new HTS221Sensor(*i2c);

    // init sensor
    sensor->init(NULL);

    Screen.init();
    printWelcome();
}

void printWelcome()
{
    Screen.print("Welcome Iot", false);
    delay(3000);

    // Clean screen
    Screen.clean();
    delay(1000);
}


void loop()
{
    char buff[100];

    // Enable sensor
    sensor->enable();

    // Get id
    sensor->readId(&id);
    Serial.printf("ID: %d\r\n", id);

    // Get humidity
    sensor->getHumidity(&humidity);
    Serial.print("Humidity: ");
    Serial.println(humidity);
   
    // Get temperature
    sensor->getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.println(temperature);
  
    sprintf(buff, "Output:\r\n Humidity: %.2f\n Temp: %.2f", humidity, temperature);
    Screen.print(buff, true);


    // Disable and reset the sensor
    sensor->disable();
    sensor->reset();
   
    delay(DELAY_MS);
    Screen.clean();
}