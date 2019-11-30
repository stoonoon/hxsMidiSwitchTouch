//#define PEDAL_DEBUG
byte lastExpPedalCCsent = 0;
unsigned long lastExpPedalCCsentMillis = millis();
const unsigned int minExpPedalUpdateDelay = 4;
unsigned long currentMillis;

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
        float pdl;
        if (R2 > 100000) {
        pdl= 127;
    }
    else if (R2 < 500) {
        pdl= 0;
    }
    else if (R2 > 84000) {
        pdl = mapf(R2, 88000, 100000, 66.6, 127);
    }
    else {
        pdl = mapf(R2, 97.75, 81000, 0, 54);
    }
    #ifdef PEDAL_DEBUG
    debugPedalInfo(R2, byte(pdl));
    #endif
    return byte(pdl);
    } //if(raw)
    else return 0;
}// byte readPedalPos()


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

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



#ifdef PEDAL_DEBUG
void debugPedalInfo(float R, byte p) {// debug tester to report measured values of R2 to aid in pedal calibration}
    const int updatePeriod = 1000; // delay time between reports
    unsigned long currentMillis = millis();
    static unsigned long lastResistanceDisplay = currentMillis;
    if ((currentMillis-lastResistanceDisplay) > updatePeriod) {
        Serial.print("EXP pedal measured resistance = ");
        Serial.print(R);
        Serial.print(", calculated MIDI value: ");
        Serial.println(p);
        lastResistanceDisplay=millis();
        }
}//printR2
#endif
