#define ag1ro 10
#define ag1ge 3
#define ag1gr 4

#define ag2ro 5
#define ag2ge 6
#define ag2gr 7

#define fro 8
#define fgr 9

#define taster 2

#define t1 5000
#define t2 1000
#define t3 5000
#define t4 1000
#define t5 2000
#define t6 10000

int state;
int time;

bool taste = false;

unsigned int leds[8] = { ag1ro, ag1ge, ag1gr, ag2ro, ag2ge, ag2gr, fro, fgr };
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(taster), peasant, FALLING);
  time = 0;
  state = 1;
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(taster, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
    case 1:
      state1();
      state++;
      break;
    case 2:
      time = t2;
      state2();
      state++;
      break;
    case 3:
      time = t3;
      state3();
      state++;
      break;
    case 4:
      time = t4;
      state4();
      state++;
      break;
    case 5:
      time = t5;
      state5();
      if (taste)
      {
        fampel1();
      }
      state++;
      break;
case 6:
      time = t2;
      state6();
      state++;
      break;
    case 7:
      time = t3;
      state7();
      state++;
      break;
    case 8:
      time = t4;
      state8();
      state++;
      break;
    case 9:
      time = t5;
      state9();
      if(taste)
      {
        fampel1();
      }
      state = 2;
      break;
  }
  delay(time);
}

void fampel1()
{
  delay(t2);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag2ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  //FA
  digitalWrite(fro, HIGH);
  digitalWrite(fgr, LOW);
  //FA Ende
  delay(t5);
  fampel2();
}

void fampel2()
{
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag2ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
  taste = false;
}

void state1() {
  for(int i = 0; i<5; i++)
  {
    digitalWrite(ag1ro, HIGH);
    digitalWrite(ag2ro, HIGH);
    digitalWrite(ag1ge, LOW);
    digitalWrite(ag2ge, LOW);
    digitalWrite(ag1gr, HIGH);
    digitalWrite(ag2gr, HIGH);
    //FA
    digitalWrite(fro, LOW);
    digitalWrite(fgr, HIGH);
    //FA Ende
    delay(500);
    digitalWrite(ag1ge, HIGH);
    digitalWrite(ag2ge, HIGH);
    delay(500);
  }
}

void state2() {
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag1ge, LOW);
  digitalWrite(ag2ro, LOW);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void state3() {
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, LOW);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, HIGH);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ro, LOW);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void state4() {
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, HIGH);
  digitalWrite(ag1ge, LOW);
  digitalWrite(ag2ro, LOW);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void state5() {
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ro, LOW);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

oid state6() {
  digitalWrite(ag2ge, LOW);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ro, LOW);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void state7() {
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, LOW);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ro, HIGH);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void state8() {
  digitalWrite(ag2ge, LOW);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ro, HIGH);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void state9() {
  digitalWrite(ag2ge, HIGH);
  digitalWrite(ag1gr, HIGH);
  digitalWrite(ag2gr, HIGH);
  digitalWrite(ag1ro, LOW);
  digitalWrite(ag1ge, HIGH);
  digitalWrite(ag2ro, LOW);
  //FA
  digitalWrite(fro, LOW);
  digitalWrite(fgr, HIGH);
  //FA Ende
}

void peasant()
{
  taste = true;
}