MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int midiDelayTime = 10; // time in ms between consecutive commands in macros
const int midiSendChannel = 1; // MIDI channel for outbound messages

/*
 * MidiMessage base class functions
 */

void MidiMessage::setLabel(char* destLabel, char* sourceLabel) {
    if (strlen(sourceLabel) > (FOOTSWITCH_LABEL_MAX_LENGTH)) { // then sourceLabel is too long
        strncpy(destLabel, sourceLabel, (FOOTSWITCH_LABEL_MAX_LENGTH-1)); // copy in as many characters that will fit (less one)
        destLabel[(FOOTSWITCH_LABEL_MAX_LENGTH-1)]='?'; // Add ? to indicate label has been truncated
        destLabel[FOOTSWITCH_LABEL_MAX_LENGTH]='\0'; // Add null character to denote end of string
    }//if
    else { // just copy the whole thing
        strcpy(destLabel, sourceLabel);
    }//else
}//MidiMessage::setLabel

bool MidiMessage::isValidSingleMessage() { // used to prevent macro nesting 
    if ((msgType == MACRO) or (msgType == NOT_KNOWN)) {
        return false;
    }
    else {
        return true;
    }
}//MidiMessage::isValidSingleMessage

/*
 * MidiNullMessage constructor and functions
 */

MidiNullMessage::MidiNullMessage() : MidiMessage() { //constructor for MidiNullMessage
    char nullLabel1[] = "NO";
    char nullLabel2[] = "ASSIGN";
    setLabel(label[0], nullLabel1);
    setLabel(label[1], nullLabel2);
}//MidiNullMessage::MidiNullMessage()

void MidiNullMessage::sendToMidi() {
    //nothing to send
}//sendToMidi

/*
 * MidiCCMessage constructor and functions
 */

MidiCCMessage::MidiCCMessage(int ccn, int ccv, char* label1, char* label2) : MidiMessage() { // constructor for MIDI CC message
    controlNumber = ccn;
    controlValue = ccv;
    msgType = CC;
    setLabel(label[0], label1);
    setLabel(label[1], label2);
}//MidiCCMessage::MidiCCMessage

void MidiCCMessage::sendToMidi() {
    MIDI.sendControlChange(controlNumber,controlValue,midiSendChannel);
}//sendToMidi

/*
 * MidiPCMessage constructor and functions
 */

MidiPCMessage::MidiPCMessage(int pn, char* label1, char* label2) : MidiMessage() { // constructor for MIDI PC message
    programNumber = pn;
    msgType = PC;
    setLabel(label[0], label1);
    setLabel(label[1], label2);
}//MidiPCMessage::MidiPCMessage

void MidiPCMessage::sendToMidi() {
    MIDI.sendProgramChange(programNumber,midiSendChannel);
}//sendToMidi



/*
 * MidiMessageMacro constructor and functions
 */
 
MidiMessageMacro::MidiMessageMacro(MidiMessage *msg1, MidiMessage *msg2, MidiMessage *msg3, char* label1, char* label2) : MidiMessage() { //constructor for 3x message macro
    msgType = MACRO;
    if ((msg1->isValidSingleMessage()) and (msg2->isValidSingleMessage()) and (msg3->isValidSingleMessage())) { //check for macro recursion or any invalid messages
        msgType = MACRO;
        commandCount = 3;
        commands[0] = msg1;
        commands[1] = msg2;
        commands[2] = msg3;
        setLabel(label[0], label1);
        setLabel(label[1], label2);
    }
    else {
        commandCount = 0;
        char errLabel1[] = "MACRO";
        char errLabel2[] = "ERROR";
        setLabel(label[0], errLabel1);
        setLabel(label[1], errLabel2);
    }
    
}//MidiMessageMacro 3x message constructor

void MidiMessageMacro::sendToMidi() {
    for (int i=0; i<commandCount; i++) {
        midiDelay();
        commands[i]->sendToMidi();
    }//for loop
}//MidiMessageMacro::sendToMidi()

MidiNullMessage blankMidiMsg = MidiNullMessage();

MidiCCMessage hxsFS1 = MidiCCMessage(49,0,"FS","1");
MidiCCMessage hxsFS2 = MidiCCMessage(50,0,"FS","2");
MidiCCMessage hxsFS3 = MidiCCMessage(51,0,"FS","3");
MidiCCMessage hxsFS4 = MidiCCMessage(52,0,"FS","4");
MidiCCMessage hxsFS5 = MidiCCMessage(53,0,"FS","5");
MidiCCMessage hxsSnap1 = MidiCCMessage(69,0,"SNAP","1");
MidiCCMessage hxsSnap2 = MidiCCMessage(69,1,"SNAP","2");
MidiCCMessage hxsSnap3 = MidiCCMessage(69,2,"SNAP","3");
MidiCCMessage hxsScrollMode = MidiCCMessage(71,1,"SCROLL","MODE");
MidiCCMessage hxsStompMode = MidiCCMessage(71,0,"STOMP","MODE");
MidiCCMessage hxsTuner = MidiCCMessage(68,0,"TUNER","MODE");
MidiCCMessage hxsTapTempo = MidiCCMessage(64,64,"TAP","TEMPO");
MidiCCMessage hxsAllBypass = MidiCCMessage(70,0,"ALL","BYPASS");
MidiCCMessage hxsNoBypass = MidiCCMessage(70,64,"NO","BYPASS");
MidiCCMessage hxsLooperOverdub = MidiCCMessage(60,0,"LOOPER","OVRDUB");
MidiCCMessage hxsLooperRec = MidiCCMessage(60,64,"LOOPER","RECORD");
MidiCCMessage hxsLooperStop = MidiCCMessage(61,0,"LOOPER","STOP");
MidiCCMessage hxsLooperPlay = MidiCCMessage(61,64,"LOOPER","PLAY");
MidiCCMessage hxsLooperPlayOnce = MidiCCMessage(62,64,"LOOPER","PLAYx1");
MidiCCMessage hxsLooperUndoRedo = MidiCCMessage(63,64,"LP UN/","REDO");
MidiCCMessage hxsLooperForward = MidiCCMessage(65,0,"LOOPER","FWD");
MidiCCMessage hxsLooperReverse = MidiCCMessage(65,64,"LOOPER","REV");
MidiCCMessage hxsLooperFullSpeed = MidiCCMessage(66,0,"FULL","SPEED");
MidiCCMessage hxsLooperHalfSpeed = MidiCCMessage(66,64,"HALF","SPEED");

MidiMessageMacro hxsPresetUpMacro = MidiMessageMacro(&hxsScrollMode, &hxsFS2, &hxsStompMode,"PRESET","UP");
MidiMessageMacro hxsPresetDownMacro = MidiMessageMacro(&hxsScrollMode, &hxsFS1, &hxsStompMode,"PRESET","DOWN");

MidiPCMessage hxsPC01A = MidiPCMessage(0,"PRESET","01A");
MidiPCMessage hxsPC01B = MidiPCMessage(1,"PRESET","01B");
MidiPCMessage hxsPC01C = MidiPCMessage(2,"PRESET","01C");
MidiPCMessage hxsPC02A = MidiPCMessage(3,"PRESET","02A");
MidiPCMessage hxsPC02B = MidiPCMessage(4,"PRESET","02B");
MidiPCMessage hxsPC02C = MidiPCMessage(5,"PRESET","02C");




void midiDelay() { // adds a delay, if required, between consecutive Midi Messages
  static unsigned long nextAllowedMessageMillis = millis();
  unsigned long currentMillis = millis();
  if (nextAllowedMessageMillis > currentMillis) { // then not enough time has elapsed since last message
    delay (nextAllowedMessageMillis - currentMillis);
  }//if
  nextAllowedMessageMillis = millis() + midiDelayTime;
}//midiDelay()

