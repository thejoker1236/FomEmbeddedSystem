 // Blink mit direktem Portzugriff
void setup() {
  // put your setup code here, to run once:
  DDRB = B00000001; // PB0 ist ein Ausgangsport
}

void loop() {
  while(1){
    PORTB = B00000001;
    delay(500);
    PORTB = B00000000;
    delay(500);
  }
}
