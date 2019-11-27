
Bounce fsDebouncers[footSwitchCount];

MidiMessage *individualSwitchAction[footSwitchCount][totalPresetPages][individualActionTypeCount];


void setupFootSwitches() { //configure pins and attach debouncers
  for (int i=0; i<footSwitchCount; i++) {
    fsDebouncers[i] = Bounce();
    pinMode(footSwitchPin[i], INPUT_PULLUP);
    fsDebouncers[i].attach(footSwitchPin[i]);
    fsDebouncers[i].interval(5); //interval in ms
    footSwitchCurrentValue[i] = footSwitchUp;
    footSwitchLastValue[i] = footSwitchUp;
  }//for loop
}//setupFootSwitches()

void setupFootSwitchActions() { //initialise individualSwitchAction array with preset config
    //start by initialising all action pointers to &blankMidiMsg
    for (int fs=0; fs<footSwitchCount; fs++) {
        for (int pg=0; pg<totalPresetPages; pg++) {
            for (int act=0; act<individualActionTypeCount; act++) {
                individualSwitchAction[fs][pg][act]=&blankMidiMsg;
            }//for(act)
        }//for (pg)
    }//for (fs)
    
    //set predefined actions
    MidiMessage *page0SingleActions[] = {&hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsPresetUpMacro, 
                            &hxsFS1, &hxsFS2, &hxsFS3, &hxsPresetDownMacro};
    setPageAction(0,SINGLE,page0SingleActions);
    
    MidiMessage *page1SingleActions[] = {&hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsFS5, 
                            &hxsFS1, &hxsFS2, &hxsFS3, &hxsFS4};
    setPageAction(1,SINGLE,page1SingleActions);
    
    MidiMessage *page2SingleActions[] = {&hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsPresetUpMacro, 
                            &hxsAllBypass, &hxsNoBypass, &hxsTuner, &hxsPresetDownMacro};
    setPageAction(2,SINGLE,page2SingleActions);
    
    MidiMessage *page3SingleActions[] = {&hxsLooperOverdub, &hxsLooperRec, &hxsLooperForward, &hxsLooperReverse, 
                            &hxsLooperStop, &hxsLooperPlay, &hxsLooperPlayOnce, &hxsLooperUndoRedo};
    setPageAction(3,SINGLE,page3SingleActions);
    
    MidiMessage *page4SingleActions[] = {&hxsLooperOverdub, &hxsLooperRec, &hxsLooperFullSpeed, &hxsLooperHalfSpeed,
                            &hxsLooperStop, &hxsLooperPlay, &hxsLooperPlayOnce, &hxsLooperUndoRedo};
    setPageAction(4,SINGLE,page4SingleActions);
    
}//setupFootSwitchActions()

void setPageAction(int page, individualActionType action, MidiMessage *msg[footSwitchCount]) { //set all FS actions for a single page and action type
    for (int fs=0; fs<footSwitchCount; fs++) {
        individualSwitchAction[fs][page][action]=msg[fs];
    }
}//setPageAction

void updateScreenLabels() { //update Nextion screen with text labels from current page single click action MidiMessages
    for (int sw =0; sw<footSwitchCount;sw++) {
        for (int line=0; line<labelLinesPerSwitch;line++) {
            footSwitchScreenLabels[sw][line]->setText( individualSwitchAction[sw][currentPage][SINGLE]->label[line] );
        }//for(line)
    } //for (sw)
}//updateScreenLabels()

bool fsIndexIsValid (int fsIndex){ //function to check if a given int is a valid footswitch index
        if ((fsIndex >= 0) && (fsIndex < footSwitchCount) ) { //then switchIndex is valid
            return true;
            }
        else {
            return false;
            }   
}// fsIndexIsValid



void readFootSwitches() { //check footswitches for any input
  for (int i=0; i<footSwitchCount; i++) {
    fsDebouncers[i].update();
    footSwitchCurrentValue[i] = fsDebouncers[i].read();
    if (fsDebouncers[i].fell()) { //then switch i has been pressed
        individualSwitchAction[i][currentPage][SINGLE]->sendToMidi(); //send MidiMessage for single press of switch i on current page
    }//if
  }//for loop
}//readFootswitches()

