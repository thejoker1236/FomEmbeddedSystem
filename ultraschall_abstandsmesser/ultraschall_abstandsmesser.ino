#include <TimerFive.h>
#define DIGIT_DELAY   2             // Delay between digits in ms

#define ECHO_PIN      10            // Ultrasound echo pin for pulseIn()
#define IO            PORTB         // Trigger (ultrasound) + beeper
#define IODDR         DDRB

#define PC4MASK       B00010000
#define PB5MASK       B00100000

#define SAMPLES       10            // Number of smaples to be averaged
#define DISPLAYREP    100           // Display n times to minimise flicker

#define ANODEPORT     PORTF         // Control the anodes ot the display
#define ANODEDDR      DDRF          

#define CATHODEPORT   PORTK         // Control the cathodes of the display
#define CATHODEDDR    DDRK

#define BEEPER        B01000000
#define BEEPINTERVAL  400L          // Time on / off
#define THRESHOLD     150           // First threshhold, interval beeping
#define THRESHOLD2    50            // Second threshhold, continous beeping

char numbers[10] = {                // Bit masks for the 7 segement display
    B00111111,                      // digit 0
    B00000110,                      // digit 1
    B01011011,                      // digit 2
    B01001111,                      // digit 3
    B01100110,                      // digit 4
    B01101101,                      // digit 5
    B01111101,                      // digit 6
    B00000111,                      // digit 7
    B01111111,                      // digit 8
    B01101111                       // digit 9
}; 

volatile beep() {                   // Toggle beeper on / off
  IO ^= BEEPER;
}

void showNumber(unsigned int value) {
  unsigned char mask = 0xf7;
  for(unsigned int i = 0; i < 4; i++)
  {
    CATHODEPORT = mask;
    ANODEPORT = numbers[value % 10];
    value /= 10;
    delay(DIGIT_DELAY);
    mask >>= 1;
  }
}

void setup() {
  IODDR      = B01100000;           // BP6 = beeper, PB5 = Ultrasound trigger
  CATHODEDDR = B00001111;           // Bit 0..3 control the cathodes
  ANODEDDR   = B11111111;           

  Timer5.attachInterrupt(beep);     // Timer5 controls the interval beeper
  Timer5.initialize(1000L * BEEPINTERVAL);
  Timer5.stop();                    // Make sure nothing beeps at first! :-)
}

void loop() {
  static float duration = 0,        // Return time for ultrasound impulse
    distance;                       // Distance in mm
  static bool timerstate = false;   // Timer5 off or on?

  for (int i = 0; i < SAMPLES; i++) {
    IO |= PB5MASK;                  // Generate an ultrasoud pulse
    delayMicroseconds(2);           // by toggling the IO pin off, on, off
    IO &= ~PB5MASK; 
    delayMicroseconds(10);
    IO |= PB5MASK;

    duration += pulseIn(ECHO_PIN, HIGH);    // How long did it take the
                                            // pulse to return?
  }
  duration /= SAMPLES;                      // Compute the arithmetic mean
  distance = (duration * .0343) / 2 * 10 ;  // Convert to mm

  if (distance <= THRESHOLD && distance > THRESHOLD2 && !timerstate){
    Timer5.start();                 // Turn on annoying beeping
    timerstate = true;              // Remember that it is turned on
  }
  else if (distance > THRESHOLD && timerstate){
    Timer5.stop();                  // Turn off the beeper timer
    IO &= ~BEEPER;                  // and make sure the beeper is off
    timerstate = false;             // and remember this
  } 
  else if (distance <= THRESHOLD2){
    Timer5.stop();                  // We are too cole: Beep continuously
    IO |= BEEPER;
    timerstate = false;
  } 
  else if(distance > THRESHOLD2 && !timerstate){
    Timer5.stop();                  // Stop continuous beeping
    IO &= ~BEEPER;
    timerstate = false;
  }

  for(int i = 0; i < DISPLAYREP; i++)   // Display the distance n times
    showNumber((unsigned int) distance);
}
