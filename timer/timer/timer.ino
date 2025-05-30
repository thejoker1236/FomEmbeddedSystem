#define DIGIT_DELAY 2
char numbers[10] = {B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111}; 
volatile int shownumber;

void setup() {
  // put your setup code here, to run once:
  DDRB = B00001111;
  DDRD = B11111111;
  shownumber = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  showNumber(9999-millis()/100);

}

void showNumber(unsigned int volume) {
  //PB3 ... PB0
  unsigned char mask = 0xf7;
  for(unsigned int i = 0; i < 4; i++)
  {
    PORTB = mask;
    PORTD = numbers[volume % 10];
    volume = volume / 10;
    delay(DIGIT_DELAY);
    mask >>= 1;
  }

}