float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

byte readPedalPos() {
  float Vout= 0;
  float R2= 0;
  float buffer= 0;
  int raw = analogRead(analogExpressionPedalPin);
  if(raw) {
      buffer = raw * Vin;
      Vout = buffer / 1024.0;
      buffer = (Vin/Vout) -1;
      R2 = R1 * buffer;
      if (R2 > 102000) {
        return 127;
        }
      else if (R2 < 500) {
        return 0;
        }
      else if (R2 > 84000) {
        float pdl = mapf(R2, 88000, 103175, 66.6, 100);
        return byte(pdl);
        }
      else {
        float pdl = mapf(R2, 97.75, 81000, 0, 54);
        return byte(pdl);
        }
  } //if(raw)
  else return 0;
}// byte readPedalPos()

byte lastExpPedalCCsent = 0;
byte currentEXPpedal = 0; // 1 is EXP1, 2 is EXP2
enum currentEXPpedal {BOTH, EXP1, EXP2};
unsigned long lastExpPedalCCsentMillis = millis();
const unsigned int minExpPedalUpdateDelay = 4;
unsigned long currentMillis;

void readExpPedalCC() {
  byte currentExpPedalCC = readPedalPos();
  if (currentExpPedalCC != lastExpPedalCCsent) { // then pedal has moved
    currentMillis = millis();
    if ( currentMillis > (lastExpPedalCCsentMillis + minExpPedalUpdateDelay) ) { //then enough time has elapsed since last CC sent
        if (currentEXPpedal == BOTH | EXP1) {
            MIDI.sendControlChange(1,currentExpPedalCC,1);
        }
        if (currentEXPpedal == BOTH | EXP2) {
            MIDI.sendControlChange(2,currentExpPedalCC,1);
        }
      lastExpPedalCCsent = currentExpPedalCC;
      lastExpPedalCCsentMillis = currentMillis;
    }
  } 
} //readExpPedalCC()

const int toeSwitchUpdateDebounceTime = 50;

void readExpToeswitch() {
  static int lastToeSwitchState = digitalRead(expToeswitchPin);
  static unsigned long lastToeSwitchUpdateSentMillis = millis();
  int currentToeSwitchState = digitalRead(expToeswitchPin);
  if (lastToeSwitchState != currentToeSwitchState) { // switch has been pressed since last update sent
    currentMillis = millis();
    if ( currentMillis > (lastToeSwitchUpdateSentMillis + toeSwitchUpdateDebounceTime)) {
      MIDI.sendControlChange(53,0,1);//FS5
      lastToeSwitchState = currentToeSwitchState;
      lastToeSwitchUpdateSentMillis = currentMillis;
    }
  }
}
