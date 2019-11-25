MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);


const int midiDelayTime = 10; // time in ms between consecutive commands in macros
const int midiSendChannel = 1; // MIDI channel for outbound messages
const int textLabelMaxLength = 6; //Max number of characters for each text label line

MidiMessage::MidiMessage() { //default constructor
    strcpy(buttonLabel1, "undef");
    strcpy(buttonLabel2, "undef");
    msgType=NOT_KNOWN;
  }


MidiCCMessage::MidiCCMessage(int ccn, int ccv, char* label1, char* label2) : MidiMessage() {
  controlNumber = ccn;
  controlValue = ccv;
  msgType = CC;
  if (strlen(label1) > (textLabelMaxLength)) {
    strncpy(buttonLabel1, label1, (textLabelMaxLength-1));
    buttonLabel1[(textLabelMaxLength-1)]='?';
    buttonLabel1[textLabelMaxLength]='\0';
    
  }//if
  else {
    strcpy(buttonLabel1, label1);
    }//else
  if (strlen(label2) > (textLabelMaxLength)) {
    strncpy(buttonLabel2, label2, (textLabelMaxLength-1));
    buttonLabel2[(textLabelMaxLength-1)]='?';
    buttonLabel2[textLabelMaxLength]='\0';
  }//if
  else {
    strcpy(buttonLabel2, label2);
    }//else
}//MidiCCMessage::MidiCCMessage

MidiMacro::MidiMacro(MidiMessage *msg) { //constructor for single message macro
    commandCount=1;
    commands[0] = msg;
    strcpy(buttonLabel1,msg->buttonLabel1);
    strcpy(buttonLabel2,msg->buttonLabel2);
  }


MidiMacro::MidiMacro(MidiMessage *msg1, MidiMessage *msg2, MidiMessage *msg3, char* label1, char* label2) {
    commandCount=3;
    commands[0] = msg1;
    commands[1] = msg2;
    commands[2] = msg3;
    if (strlen(label1) > (textLabelMaxLength)) {
    strncpy(buttonLabel1, label1, (textLabelMaxLength-1));
    buttonLabel1[(textLabelMaxLength-1)]='?';
    buttonLabel1[textLabelMaxLength]='\0';
  }//if
  else {
    strcpy(buttonLabel1, label1);
    }//else
  if (strlen(label2) > (textLabelMaxLength)) {
    strncpy(buttonLabel2, label2, (textLabelMaxLength-1));
    buttonLabel2[(textLabelMaxLength-1)]='?';
    buttonLabel2[textLabelMaxLength]='\0';
  }//if
  else {
    strcpy(buttonLabel2, label2);
    }//else
  }
 
MidiCCMessage hxsFS1 = MidiCCMessage(49,0,"FS","1");
MidiCCMessage hxsFS2 = MidiCCMessage(50,0,"FS","2");
MidiCCMessage hxsFS3 = MidiCCMessage(51,0,"FS","3");
MidiCCMessage hxsFS4 = MidiCCMessage(52,0,"FS","4");
MidiCCMessage hxsFS5 = MidiCCMessage(53,0,"FS","5");

MidiMacro hxsFS1Macro = MidiMacro(&hxsFS1);
MidiMacro hxsFS2Macro = MidiMacro(&hxsFS2);
MidiMacro hxsFS3Macro = MidiMacro(&hxsFS3);
MidiMacro hxsFS4Macro = MidiMacro(&hxsFS4);
MidiMacro hxsFS5Macro = MidiMacro(&hxsFS5);

MidiCCMessage hxsSnap1 = MidiCCMessage(69,0,"SNAP","1");
MidiCCMessage hxsSnap2 = MidiCCMessage(69,1,"SNAP","2");
MidiCCMessage hxsSnap3 = MidiCCMessage(69,2,"SNAP","3");

MidiMacro hxsSnap1Macro = MidiMacro(&hxsSnap1);
MidiMacro hxsSnap2Macro = MidiMacro(&hxsSnap2);
MidiMacro hxsSnap3Macro = MidiMacro(&hxsSnap3);

MidiCCMessage hxsScrollMode = MidiCCMessage(71,1,"SCROLL","MODE");
MidiCCMessage hxsStompMode = MidiCCMessage(71,0,"STOMP","MODE");

MidiMacro hxsPresetUpMacro = MidiMacro(&hxsScrollMode, &hxsFS2, &hxsStompMode,"PRESET","UP");
MidiMacro hxsPresetDownMacro = MidiMacro(&hxsScrollMode, &hxsFS1, &hxsStompMode,"PRESET","DOWN");

MidiCCMessage hxsTuner = MidiCCMessage(68,0,"TUNER","MODE");
MidiCCMessage hxsTapTempo = MidiCCMessage(64,64,"TAP","TEMPO");
MidiCCMessage hxsAllBypass = MidiCCMessage(70,0,"ALL","BYPASS");
MidiCCMessage hxsNoBypass = MidiCCMessage(70,64,"NO","BYPASS");

MidiMacro hxsTunerMacro = MidiMacro(&hxsTuner);
MidiMacro hxsTapTempoMacro = MidiMacro(&hxsTapTempo);
MidiMacro hxsAllBypassMacro = MidiMacro(&hxsAllBypass);
MidiMacro hxsNoBypassMacro = MidiMacro(&hxsNoBypass);

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

MidiMacro hxsLooperOverdubMacro = MidiMacro(&hxsLooperOverdub);
MidiMacro hxsLooperRecMacro = MidiMacro(&hxsLooperRec);
MidiMacro hxsLooperStopMacro = MidiMacro(&hxsLooperStop);
MidiMacro hxsLooperPlayMacro = MidiMacro(&hxsLooperPlay);
MidiMacro hxsLooperPlayOnceMacro = MidiMacro(&hxsLooperPlayOnce);
MidiMacro hxsLooperUndoRedoMacro = MidiMacro(&hxsLooperUndoRedo);
MidiMacro hxsLooperForwardMacro = MidiMacro(&hxsLooperForward);
MidiMacro hxsLooperReverseMacro = MidiMacro(&hxsLooperReverse);
MidiMacro hxsLooperFullSpeedMacro = MidiMacro(&hxsLooperFullSpeed);
MidiMacro hxsLooperHalfSpeedMacro = MidiMacro(&hxsLooperHalfSpeed);





MidiMacro *singleClickMacroPages[totalPresetPages][footSwitchCount] = {
        {&hxsSnap1Macro, &hxsSnap2Macro, &hxsSnap3Macro, &hxsPresetUpMacro,
        &hxsFS1Macro, &hxsFS2Macro, &hxsFS3Macro, &hxsPresetDownMacro},

        {&hxsSnap1Macro, &hxsSnap2Macro, &hxsSnap3Macro, &hxsFS5Macro,
        &hxsFS1Macro, &hxsFS2Macro, &hxsFS3Macro, &hxsFS4Macro},

        {&hxsSnap1Macro, &hxsSnap2Macro, &hxsSnap3Macro, &hxsPresetUpMacro,
        &hxsAllBypassMacro, &hxsNoBypassMacro, &hxsTunerMacro, &hxsPresetDownMacro},
        
        {&hxsLooperOverdubMacro, &hxsLooperRecMacro, &hxsLooperForwardMacro, &hxsLooperReverseMacro, 
        &hxsLooperStopMacro, &hxsLooperPlayMacro, &hxsLooperPlayOnceMacro, &hxsLooperUndoRedoMacro},
        
        {&hxsLooperOverdubMacro, &hxsLooperRecMacro, &hxsLooperFullSpeedMacro, &hxsLooperHalfSpeedMacro, 
        &hxsLooperStopMacro, &hxsLooperPlayMacro, &hxsLooperPlayOnceMacro, &hxsLooperUndoRedoMacro}

    };


void sendMidiMessage(MidiMessage *msg) {
    midiDelay();
    switch(msg->msgType) {
        case MidiMessage::CC:
            MidiCCMessage* ccMsg = (MidiCCMessage*)(msg);
            MIDI.sendControlChange(ccMsg->controlNumber, ccMsg->controlValue,midiSendChannel);
            break;
    }//switch
}//sendMidiMessage

void sendMidiMacro(MidiMacro *macro) {
    for (int i=0; i<(macro->commandCount); i++) {
        sendMidiMessage(macro->commands[i]);
    }//for loop

}//sendMidiMacro


void midiDelay() { // adds a delay, if required, between consecutive Midi Messages
  static unsigned long nextAllowedMessageMillis = millis();
  unsigned long currentMillis = millis();
  if (nextAllowedMessageMillis > currentMillis) { // then not enough time has elapsed since last message
    delay (nextAllowedMessageMillis - currentMillis);
  }//if
  nextAllowedMessageMillis = millis() + midiDelayTime;
}//midiDelay()

