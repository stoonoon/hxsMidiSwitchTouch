// #define PEDAL_DEBUG

// pretty sure these next 3 can be made static variables within readExpPedalCC()
byte lastExpPedalCCsent = 0; // the last CC value we sent. (No point in sending more if the pedal hasn't moved!)
unsigned long lastExpPedalCCsentMillis = millis(); // the time we last sent a message. 
const unsigned int minExpPedalUpdateDelay = 4; // how many milliseconds we wait before sending another pedal position message


unsigned long currentMillis; // pretty sure this doesn't need to be a global as it should always be updated with millis() whenever we use it. Will change this next time I'm compiling & testing, but I'm just adding comments away from the IDE at the moment.

const int toeSwitchUpdateDebounceTime = 50; // minimum elapsed time in ms since last toeSwitch press before we consider acting on another one

const int maxR2 = 100000; // R2 value above which we consider pedal to be fully toe down. Reduce this to increase toedown deadzone (my max measured value was about 103000)
const int minR2 = 5000; // R2 value below which we consider pedal to be fully heel down. Reduce this to increase heeldown deadzone (my min measured value was about 100)


byte readPedalPos() { // should probably be renamed getCurrentPedalPosition()
/*
 *  Read value from expression pedal input pin, and return a 0-127 value for use as a MIDI CC
 *  
 *  This is a specific implementation based on my hardware, and may need to be changed substantially
 *  based on what expression pedal setup you use.
 *
 *  I have a pedal with a 100k ohm log pot and toeswitch connected to my controller via a single TRS cable
 *  so I have +5V going to one of the fixed ends of the track, and the wiper is connected to the input pin
 *  on the Arduino via a voltage divider circuit on my arduino shield.
 *
 *  If you are not planning on using a toeswitch, or plan to run a separate cable to your toeswitch, 
 *  then you could run +5V and GND to either end of the track and connect the wiper to the Arduino input
 *  pin without requiring the voltage divider circuit. 
 *
 *  If you are using a linear pot in your expression pedal (most will be, unless you're using a half-
 *  converted wah pedal like me) then you should be able to simplify the mapping from R2 to pdl
 *  as they should rise proportionally to each other through the full extent of any travel (give or
 *  take any exceptions for deadzones at end of travel)
*/
    float Vout= 0; // voltage divider output, as measured at analog input pin
    float R2= 0; // calculated resistance of variable pot in expression pedal
    float buffer= 0;
    int raw = analogRead(analogExpressionPedalPin);
    if(raw) {
        buffer = raw * Vin;
        Vout = buffer / 1024.0;
        buffer = (Vin/Vout) -1;
        R2 = R1 * buffer;
        float pdl;
        if (R2 > maxR2) { // then fully toe down (or within deadzone)
        pdl= 127;
    }
    else if (R2 < minR2) { //then fully heel down (or within deadzone)
        pdl= 0;
    }
    else if (R2 > 84000) { // then on toe down end of track
        pdl = mapf(R2, 88000, 100000, 66.6, 127);
    }
    else { // on heel down end of track
        pdl = mapf(R2, 97.75, 81000, 0, 54);
    }
    #ifdef PEDAL_DEBUG
    debugPedalInfo(R2, byte(pdl));
    #endif
    return byte(pdl);
    } //if(raw)
    else return 0;
}// byte readPedalPos()


void readExpPedalCC() { // should probably be renamed updateExpPedalPositionCC()
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


void readExpToeswitch() {
/*
 *
 *  This code is based on my hardware setup which uses a latching footswitch, and shares a TRS connection
 *  with the expression pedal pot... Hence no spare wire for a GNS connection, so I used the +5V on the 
 *  other pole of the switch, and a pulldown resistor on my arduino shield. 
 *
 *  If you have the toeswitch connected to GND instead of +5V, you can omit the external pulldown, and 
 *  connect the switch direct to the arduino input pin - but remember to set the internal pullup
 *
 *  If you are using a momentary switch then don't use this code - just use a "Bounce" debouncer as
 *  used for the rest of the footswitches
 *
 */
 
 
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
// maps value x from range (in_min to in_max) to range (out_min to out_max)
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
