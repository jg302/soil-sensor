// YL-39 + YL-69 humidity sensor
byte humidity_sensor_pin = A1;
byte humidity_sensor_vcc = 6;
const int pump_on = 9;

  const int wet = 450;
  const int dry = 46
  
  5;
  float results[5];
  const int times_to_check = 5;
  int counter = 0;
  int average_result = 0;

void setup() {
  // Init the humidity sensor board
  pinMode(humidity_sensor_vcc, OUTPUT);
  pinMode(pump_on, OUTPUT);
  digitalWrite(humidity_sensor_vcc, LOW);

  // Setup Serial
  while (!Serial);
  delay(1000);
  Serial.begin(9600);
}

int read_humidity_sensor() {
  digitalWrite(humidity_sensor_vcc, HIGH);
  delay(500);
  int value = analogRead(humidity_sensor_pin);
  digitalWrite(humidity_sensor_vcc, LOW);
  int new_value = 1023 - value;
  return new_value;
}

int read_average_humidity() {
  int sum;
  while (counter < times_to_check) {
    results[counter] = (read_humidity_sensor());
  Serial.print("Reading no");
  Serial.print(counter);
  Serial.print(" = ");
  Serial.println(results[counter]);
    sum = sum + results[counter];
    counter ++;
    delay(500);
  }
    counter = 0;
    average_result = sum / times_to_check;
  Serial.print("Average humidity Level (0-1023): ");
  return average_result;
}

void loop() {
  Serial.println(read_average_humidity()); 
  delay(1000);
    if (average_result < wet) {
    Serial.println("Too dry, running pump");
    digitalWrite(pump_on, HIGH);
    delay(100*100);
    Serial.print(".");
    delay(100*100);
    Serial.print(".");
    delay(100*100);
    Serial.print(".");
    delay(100*100);
    digitalWrite(pump_on, LOW);
    }
    else {
    Serial.println("Plants are good!");
    delay(100*100);
    delay(100*100);
  }
}
