//EXP pedal and toeswitch
const int analogExpressionPedalPin= 0; //pin connected to wiper of Expression pedal potentiometer
const int expToeswitchPin= 12; // pin connected to expression pedal toeswitch
const int Vin= 5; // comparison voltage for expression pedal voltage divider
const float R1= 100000; // known resistor value for expression pedal voltage divider

//Footswitches
const int footSwitchCount = 8; // number of footswitches used
const int footSwitchPin[] = {9,8,7,6,5,4,3,2}; // pins for footswitch inputs
const bool footSwitchDown = LOW; //because we are using pullup resistor and switch to GND
const bool footSwitchUp = !footSwitchDown;

int footSwitchCurrentValue[footSwitchCount]; //for current state of footswitch state
int footSwitchLastValue[footSwitchCount]; //last known footswitch state so we know whether it has changed

enum individualActionType {SINGLE = 0, LONG=1, DOUBLE=2}; //different types of footswitch press available for any individual footswitch
const int individualActionTypeCount = 3; // number of types in above enum


//Touchscreen menu
#define FOOTSWITCH_LABEL_MAX_LENGTH 6 //max characters per line for each footswitch label
#define MAX_MACRO_LENGTH 5
const int labelLinesPerSwitch =2; 

const int totalPresetPages = 5; // number of preset pages we are configuring

int currentPage=0; // menu preset page to load on boot

