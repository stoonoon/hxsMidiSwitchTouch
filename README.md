# hxsMidiSwitchTouch
v2 of hxsMidiSwitcher - This time with touchscreen and expression pedal input

Still in the very early stages of how to go about this, so doubtless lots will change.

At the moment the only touchscreen functionality is to cycle between preset pages, but the 8 switches are working and sending midi messages over to the stomp. Expression pedal and toeswitch is working fairly well... I'm currently using a slightly modified crybaby wah with some dupont M-F wires between the circuit board and potentiometer/toeswitch harness... Not ideal as it's a log pot rather than a linear one but with some software compensation it seems good enough for testing for now.

## Working so far
- Touchscreen
-- << and >> buttons cycle between preset pages
-- Footswitch labels update as preset page changes
-- Touching the footswitch label triggers a FS short click action for that switch
- Midi
-- PC / CC messages
-- macro of several messages sent in a chain (needed for preset up/down functionality without relying on FS4/FS5 being dedicated to it in the Stomp global settings)
- Expression pedal
-- Converts resistance from 100kOhm log pot to MIDI byte
-- Sends to Stomp as either EXP1, EXP2 or both
-- Checks for changes in latching toeswitch & sends FS5 to Stomp
- switch preset page from footswitches
- toggle mode (FS function & label changes to next in list after press) - see looper Fwd/Rev and Full/Half speed for an example

## Still to do:
- Refactor the code so it plays nicely in VSCode - it doesn't seem to like multiple .ino files
- Programming screen on nextion & associated code on arduino
- Ability to save/load custom programs to/from eeprom
- Document the calculations for the expression pedal log pot compensation
- Document the wiring adapter for the wah pedal to expression pedal conversion.
- configurable for log/lin EXP pedal pots
- configurable for latching/momentary toeswitch
- All the other stuff I can't remember at the moment or haven't thought of yet

## Maybe considering, but probably not until v3
- power capacitor needed for nextion screen? seems OK without.. will see if it holds up
- activate long press/double FS actions from touchscreen 
- USB host midi capability - to be able to control Zoom B3/G3n/MS60B type pedals etc
- extra MIDI in/out ports
- bluetooth
- self-hovering
