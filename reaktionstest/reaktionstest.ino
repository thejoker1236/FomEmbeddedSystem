#define LED_1 8
#define BUTTON_1 9
#define LED_2 7
#define BUTTON_2 10
#define BAUD_RATE 9600

unsigned long events = 0, sum = 0, min = -1, max = 0, leds[2] = { LED_1, LED_2 }, buttons[2] = { BUTTON_1, BUTTON_2 };

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }
  Serial.begin(BAUD_RATE);

  for (int i = 0; i < 2; digitalWrite(leds[i++], HIGH))
    ;  // Switch off both LEDs
  Serial.print("\n\n\nPress any key once to initalize the pseudo random number generator...\n");
  while (digitalRead(BUTTON_1) && digitalRead(BUTTON_2))
    ;                    // Wait for key pressed
  delay(500);            // Debounce the switch
  randomSeed(millis());  // Initialize the pseudorandom number generator
  Serial.print("Initalized...\n");
}

void loop() {
  delay(random(10, 50) * 100);

  int selector = random(0, 2);
  digitalWrite(leds[selector], LOW);    // Turn LED on
  unsigned long event_time = millis();  // Remember current time
  events++;

  while (digitalRead(buttons[selector]))
    ;  // Wait for button being pressed
  for (int i = 0; i < 2; digitalWrite(leds[i++], HIGH))
    ;  // Switch off both LEDs
  unsigned long delta_t = millis() - event_time;
  sum += delta_t;
  if (delta_t < min) min = delta_t;
  if (delta_t > max) max = delta_t;
  Serial.print("Reaktionszeit = " + String(delta_t) + "\tMean = " + String((float)sum / (float)events) + "\tMin = " + String(min) + "\tMax = " + String(max) + "\n");
}