//EXP pedal and toeswitch
const int analogExpressionPedalPin= A1; //pin connected to wiper of Expression pedal potentiometer
const int expToeswitchPin= A0; // pin connected to expression pedal toeswitch
const int Vin= 5; // comparison voltage for expression pedal voltage divider
const float R1= 100000; // known resistor value for expression pedal voltage divider
enum EXPpedalOutput {BOTH, EXP1, EXP2};
EXPpedalOutput currentEXPpedal = BOTH; // Which EXP to send to on the Stomp - enum currentEXPpedal {BOTH, EXP1, EXP2};


//Footswitches
const bool WAIT_FOR_LONG_PRESS = true; // if true, prevents a long press on a switch triggering single click and long press events. If false, single click event will be triggered immediately, and long press will follow it if switch is held down for long enough. Recommend setting this to false if timing is sensitive.
const int longPressMillis = 1000; //how long a single switch must be held down for to trigger a long press event
const int doubleClickMillis = 500; //maximum time between consecutive clicks on a switch to trigger a double click event
const int footSwitchCount = 8; // number of footswitches used
const int footSwitchPin[] = {0,1,2,3,7,6,5,4}; // pins for footswitch inputs
const bool footSwitchDown = LOW; //because we are using pullup resistor and switch to GND
const bool footSwitchUp = !footSwitchDown;
const int individualActionTypeCount = 3; // number of types in above enum
enum individualActionType {SINGLE = 0, LONG=1, DOUBLE=2}; //different types of footswitch press available for any individual footswitch
bool footSwitchCurrentValue[footSwitchCount]; //for current state of footswitch state
Bounce fsDebouncers[footSwitchCount];


//Touchscreen menu
#define FOOTSWITCH_LABEL_MAX_LENGTH 6 //max characters per line for each footswitch label
#define MAX_MACRO_LENGTH 5
const int labelLinesPerSwitch =2; 

const int totalPresetPages = 7; // number of preset pages we are configuring

int currentPage=0; // menu preset page to load on boot
const int maxTogglerSize = 3; // max allowed number of commands in a MidiMessageToggler
