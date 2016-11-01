#define RELAY1 2
#define RELAY2 4

unsigned long startTime = millis();

void setup() {
  // Set up pin outputs for relays
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  // Default relay to off
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  // Initialize thermocouples

  // Call menu
  

}

void loop() {
    delay(10000);
    // LOW turns coils ON
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
}

int getTemp() {
  double temp;
  
  // read timer


  // calculate target temp
  

}

