#define LED       8
#define TASTER    9
#define BAUD_RATE 9600

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(TASTER, INPUT_PULLUP);
  Serial.begin(BAUD_RATE);
}


void loop() {
  static bool state = 0;

  if(!digitalRead(TASTER)){
    state ^= 1;
    Serial.print(String(state) + "\n");
    digitalWrite(LED, state);
    delay(100); //Entprellen...
    while (!digitalRead(TASTER));
  }
}
