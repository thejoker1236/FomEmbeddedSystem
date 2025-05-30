#define DIGIT_DELAY 2
#define ECHO_PIN    12
#define BAUDRATE    9600
#define PC4MASK     B00010000
#define SAMPLES     10
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
float duration, distance;

void setup() {
  //Serial.begin(BAUDRATE);
  DDRB = B00101111;
  DDRC |= PC4MASK;
  DDRD = B11111111;
  shownumber = 0;
}

void loop() {
  PORTB |= PC4MASK;
  delayMicroseconds(2);
  PORTB &= ~PC4MASK;
  delayMicroseconds(10);
  PORTB |= PC4MASK;

  unsigned int sum = 0;
  for (int i = 0; i< SAMPLES; i++){
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * .0343) / 2 * 10;
    sum += distance;
  }
  
  for(int i = 0; i < DISPLAYREP; i++)
  {
    showNumber(sum/100);
  }
  //if(sum/100 < 100)
  //{
  //beep_on();
  //}
}

void showNumber(unsigned int volume) {
  //PB3 ... PB0
  unsigned char mask = 0xf7;
  for(unsigned int i = 0; i < 4; i++)
  {
    PORTB = mask;
    PORTD = numbers[volume % 10];
    volume /= 10;
    delay(DIGIT_DELAY);
    mask >>= 1;
  }
}
  void beep_on()
  {
    PORTC |= PC4Mask;
  }