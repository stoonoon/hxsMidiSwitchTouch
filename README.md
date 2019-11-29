# hxsMidiSwitchTouch
v2 of hxsMidiSwitcher - This time with touchscreen and expression pedal input

Still in the very early stages of how to go about this, so doubtless lots will change.

At the moment the only touchscreen functionality is to cycle between preset pages, but the 8 switches are working and sending midi messages over to the stomp. Expression pedal and toeswitch is working fairly well... I'm currently using a slightly modified crybaby wah with some dupont M-F wires between the circuit board and potentiometer/toeswitch harness... Not ideal as it's a log pot rather than a linear one but with some software compensation it seems good enough for testing for now.

## Still to do:

- switch preset page from footswitches
- Programming screen on nextion & associated code on arduino
- Ability to save/load custom programs to/from eeprom
- power capacitor needed for nextion screen?
- Document the calculations for the expression pedal log pot compensation
- Document the wiring adapter for the wah pedal to expression pedal conversion.
- Design an enclosure for it
- All the other stuff I can't remember at the moment or haven't thought of yet

## Maybe considering, but probably not until v3

- switch double-click detection
- USB host midi capability - to be able to control Zoom B3/G3n/MS60B type pedals etc
- extra MIDI in/out ports
- bluetooth
- self-hovering
