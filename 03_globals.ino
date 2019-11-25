// #define ledPin 13

const int analogExpressionPedalPin= 0;
const int expToeswitchPin= 12;
const int Vin= 5;
const float R1= 100000;
const int totalPresetPages = 3; // number of preset pages we are configuring
const int footSwitchCount = 8; // number of footswitches used
const int footSwitchPin[] = {9,8,7,6,5,4,3,2}; // pins for footswitch inputs
const bool footSwitchDown = LOW; //because we are using pullup resistor and switch to GND
const bool footSwitchUp = !footSwitchDown;



int currentPage=0;

