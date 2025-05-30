#define DIGIT_DELAY 2
#define ECHO_PIN    10
#define BAUDRATE    9600
#define PC4MASK     B00010000
#define PB5MASK     B00100000
#define SAMPLES     1
#define DISPLAYREP  10

char numbers[10] = {
    B00111111,
    B00000110,
    B01011011,
    B01001111,
    B01100110,
    B01101101,
    B01111101,
    B00000111,
    B01111111,
    B01101111
}; 

volatile int shownumber;

void setup() {
  //Serial.begin(BAUDRATE);
  DDRB = B00100000;
  DDRK = B00101111;
  DDRC |= PC4MASK;
  DDRF = B11111111;
  shownumber = 0;
}

void loop() {
  static float duration, distance;
  unsigned int sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
  //for(;;){  
    PORTB |= PB5MASK;
    delayMicroseconds(2);
    PORTB &= ~PB5MASK;
    delayMicroseconds(10);
    PORTB |= PB5MASK;

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * .0343) / 2 * 10; // In Millimetern
    sum += distance;
  }

  for(int i = 0; i < DISPLAYREP; i++)
    showNumber(sum/100);

//  beep_on();
}

void showNumber(unsigned int value) {
  //PB3 ... PB0
  unsigned char mask = 0xf7;
  for(unsigned int i = 0; i < 4; i++)
  {
    PORTK = mask;
    PORTF = numbers[value % 10];
    value /= 10;
    delay(DIGIT_DELAY);
    mask >>= 1;
  }
}
void beep_on()
{
  PORTC |= PC4MASK;
}
