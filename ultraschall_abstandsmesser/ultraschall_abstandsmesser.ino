#include <TimerFive.h>
#define DIGIT_DELAY 2

#define ECHO_PIN      10
#define IO            PORTB
#define IODDR         DDRB

#define BAUDRATE      9600

#define PC4MASK       B00010000
#define PB5MASK       B00100000

#define SAMPLES       10
#define DISPLAYREP    100

#define ANODEPORT     PORTF
#define ANODEDDR      DDRF

#define KATHODEPORT   PORTK
#define KATHODEDDR    DDRK

#define BEEPER        B01000000
#define BEEPINTERVAL  400L
#define THRESHOLD     150

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

volatile beep(){
  IO ^= BEEPER;
}

void setup() {
  //Serial.begin(BAUDRATE);
  IODDR = B01100000;
  KATHODEDDR = B00101111;
  ANODEDDR = B11111111;

  Timer5.attachInterrupt(beep);
  Timer5.initialize(1000L * BEEPINTERVAL);
  Timer5.stop();
}

void loop() {
  static float duration, distance;
  static bool timerstate = false;
  unsigned long sum = 0;
  duration = 0;

  for (int i = 0; i < SAMPLES; i++) {
  //for(;;){  
    IO |= PB5MASK;
    delayMicroseconds(2);
    IO &= ~PB5MASK;
    delayMicroseconds(10);
    IO |= PB5MASK;

    duration += pulseIn(ECHO_PIN, HIGH);
  }
  duration /= SAMPLES;
  distance = (duration * .0343) / 2 * 10 ;

  if (distance <= THRESHOLD && !timerstate){
    Timer5.start();
    timerstate = true;
  }
  else if (distance > THRESHOLD && timerstate){
    Timer5.stop();
    IO &= ~BEEPER;
    timerstate = false;
  }

  for(int i = 0; i < DISPLAYREP; i++)
    showNumber((unsigned int) distance);

}

void showNumber(unsigned int value) {
  //PB3 ... PB0
  unsigned char mask = 0xf7;
  for(unsigned int i = 0; i < 4; i++)
  {
    KATHODEPORT = mask;
    ANODEPORT = numbers[value % 10];
    value /= 10;
    delay(DIGIT_DELAY);
    mask >>= 1;
  }
}



