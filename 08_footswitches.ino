
//default config for footswitch single tap actions
MidiMessage *page0SingleActions[] = {&hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsTuner, 
                            &hxsFS1, &hxsFS2, &hxsFS3, &hxsTapTempo};
MidiMessage *page1SingleActions[] = {&hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsFS5, 
                        &hxsFS1, &hxsFS2, &hxsFS3, &hxsFS4};
MidiMessage *page2SingleActions[] = {&hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsPresetUpMacro, 
                        &hxsFS1, &hxsFS2, &hxsFS3, &hxsPresetDownMacro};
MidiMessage *page3SingleActions[] = {&hxsFS4, &hxsFS5, &hxsPresetDownMacro, &hxsPresetUpMacro, 
                        &hxsFS1, &hxsFS2, &hxsFS3, &hxsTapTempo};
MidiMessage *page4SingleActions[] = {&hxsFS4, &hxsFS5, &hxsPresetDownMacro, &hxsPresetUpMacro,
                        &hxsSnap1, &hxsSnap2, &hxsSnap3, &hxsTapTempo};
MidiMessage *page5SingleActions[] = {&hxsPC01A, &hxsPC01B, &hxsPC01C, &hxsTuner,
                        &hxsPC02A, &hxsPC02B, &hxsPC02C, &hxsTapTempo};
MidiMessage *page6SingleActions[] = {&hxsLooperOverdub, &hxsLooperRec, &hxsLooperRevToggle, &hxsLooperSpeedToggle,
                        &hxsLooperStop, &hxsLooperPlay, &hxsLooperPlayOnce, &hxsLooperUndoRedo};
    


void setupFootSwitches() { //configure pins and attach debouncers
  for (int i=0; i<footSwitchCount; i++) {
    fsDebouncers[i] = Bounce();
    pinMode(footSwitchPin[i], INPUT_PULLUP);
    fsDebouncers[i].attach(footSwitchPin[i]);
    fsDebouncers[i].interval(5); //interval in ms
    footSwitchCurrentValue[i] = footSwitchUp;
  }//for loop
}//setupFootSwitches()

void setupFootSwitchActions() { //initialise individualSwitchAction array with preset config
    //start by initialising all action pointers to &blankMidiMsg
    for (int fsA=0; fsA<footSwitchCount; fsA++) { //iterate over all footswitches
        for (int pg=0; pg<totalPresetPages; pg++) { //iterate over all preset pages
            for (int act=0; act<individualActionTypeCount; act++) { //iterate over all switch action types
                individualSwitchAction[fsA][pg][act]=&blankMidiMsg;
            }//for(act)
        }//for (pg)
        for (int fsB =0; fsB<footSwitchCount; fsB++) { //iterate over all switches again so all combinations are covered
            setComboAction(-1,fsA,fsB,&blankMidiMsg); //set blank action on all pages
        }//for(fsB)
    }//for (fsA)
    
    //set predefined actions
    setWholePageActions(0,SINGLE,page0SingleActions);
    setWholePageActions(1,SINGLE,page1SingleActions);
    setWholePageActions(2,SINGLE,page2SingleActions);
    setWholePageActions(3,SINGLE,page3SingleActions);
    setWholePageActions(4,SINGLE,page4SingleActions);
    setWholePageActions(5,SINGLE,page5SingleActions);
    setWholePageActions(6,SINGLE,page6SingleActions);
    
    //set predefined long press actions
    
    //individualSwitchAction[0][0][LONG]=&hxsTuner;
    setAllPagesAction(3, LONG, &hxsTuner);
    
    //set predefined combination actions
    setComboAction(-1, 0, 4, &hxsPresetDownMacro);
    setComboAction(-1, 3, 7, &hxsPresetUpMacro);
    setComboAction(-1, 6, 7, &hxsTuner);
    setComboAction(-1, 0, 1, &switcherPageDown);
    setComboAction(-1, 2, 3, &switcherPageUp);
        
}//setupFootSwitchActions()

void setAllPagesAction(int fs, individualActionType action, MidiMessage *msg) { // set an action which applies to all pages
  for (int p=0; p<totalPresetPages; p++) {
    individualSwitchAction[fs][p][action]=msg;
  }//for loop
} //setAllPagesAction

void setWholePageActions(int page, individualActionType action, MidiMessage *msg[footSwitchCount]) { //set all FS actions for a single page and action type
    for (int fs=0; fs<footSwitchCount; fs++) {
        individualSwitchAction[fs][page][action]=msg[fs];
    }
}//setWholePageActions

void setComboAction(int page, int fsA, int fsB, MidiMessage *msg) { //set an action for a 2x switch combination press
    //we need to sort the switches by index so we never have conficting settings with switch indexes swapped
    int lowestSwitchIndex; 
    int highestSwitchIndex;
    if (fsA<fsB) {
        lowestSwitchIndex=fsA;
        highestSwitchIndex=fsB;
        }
    else {
        lowestSwitchIndex=fsB;
        highestSwitchIndex=fsA;
        }
    if (page==-1) {//then apply this combo to all pages
        for (int p=0; p<totalPresetPages; p++) {
            comboSwitchAction[lowestSwitchIndex][highestSwitchIndex][p]=msg;
        }//for loop
    }//if (page==-1)
    else {//then only apply it to a single page
        comboSwitchAction[lowestSwitchIndex][highestSwitchIndex][page]=msg;
    }//else
}//setComboAction

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
    static int longPressWatcher = -1; //set to switch index of any potential long press candidate, or -1 if no valid candidate.
    static int totalFootSwitchesDown =0; //for tracking how many switches are pressed so we know whether to check for switch combination actions
    static unsigned long lastPressMillis[footSwitchCount] ={0}; //the last time the switch was pressed
    static unsigned long lastLastPressMillis[footSwitchCount] ={0}; //the last but one time the switch was pressed
    static unsigned long lastReleaseMillis[footSwitchCount] ={0}; //the last time the switch was released
    static unsigned long lastLongPressSentMillis[footSwitchCount]={0}; //the time a long press message was last sent
    unsigned long currentMillis = millis(); //time at start of loop
    static int comboActive = false; //set true if >1 switches pressed. ignore all further 
    static int comboUnsent = false; 
    
    for (int i=0; i<footSwitchCount; i++) { // iterate over all the switches
        fsDebouncers[i].update(); //update the Bounce debouncer object for each switch
        if (fsDebouncers[i].fell()) { //then footswitch i has been pressed
            footSwitchCurrentValue[i] = footSwitchDown;
            totalFootSwitchesDown++;//increase counter for how many switches we know are currently down
            lastLastPressMillis[i] = lastPressMillis[i];
            lastPressMillis[i] = currentMillis;
            if (comboActive==false) { //then we may need to act on a switch press
                if (totalFootSwitchesDown>1) {
                    comboActive = true;
                    if (totalFootSwitchesDown==2) {// check for valid combo and act accordingly
                        int fsA =-1;
                        int fsB =-1;
                        for (int fs =0; fs<footSwitchCount; fs++) {
                            if (footSwitchCurrentValue[fs]==footSwitchDown) { // we have found a pressed switch
                                if (fsA==-1) { //then this is the first switch found
                                    fsA=fs;
                                }
                                else { //this is the second switch found
                                    fsB=fs;
                                }//else
                            }//if (footSwitchCurrentValue[fs]==footSwitchDown)
                        }//for (int fs =0; fs<footSwitchCount; fs++)
                        comboSwitchAction[fsA][fsB][currentPage]->sendToMidi();//send MidiMessage for pressed combo
                    }//if (totalFootSwitchesDown==2)
                }//if (totalFootSwitchesDown>1))
                else { //only one switch is pressed - test for single/double click actions
                    if ((lastPressMillis-lastLastPressMillis) < doubleClickMillis) { // then trigger double click action
                        individualSwitchAction[i][currentPage][DOUBLE]->sendToMidi(); //send MidiMessage for double press action 
                    } //if ((lastPressMillis-lastLastPressMillis) < doubleClickMillis)
                    else { //could be single click or start of long press
                        if (WAIT_FOR_LONG_PRESS) {
                            longPressWatcher=i; //set this to keep track of a potential long press candidate
                        }//if (WAIT_FOR_LONG_PRESS)
                        else { //send single click action immediately
                            individualSwitchAction[i][currentPage][SINGLE]->sendToMidi(); //send MidiMessage for single press action 
                        }//else
                    }
                }//else
            }//if (comboActive==false)
            
        }//if (fsDebouncers[i].fell())
        if (fsDebouncers[i].rose()) { //then footswitch i has been released
            footSwitchCurrentValue[i] = footSwitchUp;
            totalFootSwitchesDown--;//increase counter for how many switches we know are currently down
            lastReleaseMillis[i] = currentMillis;
            
            
            if (comboActive==true) { //then we just need to check if all switches have been released
                if (totalFootSwitchesDown==0) {
                    comboActive=false;
                } //if (totalFootSwitchesDown==0)
            }//if (comboActive==true)
            else { // we need to check if we were waiting for a short press
                if (WAIT_FOR_LONG_PRESS) { //then we didn't send short press action immediately
                    if ((lastReleaseMillis[i]-lastPressMillis[i])<longPressMillis) { //switch was depressed for less than longPressMillis
                        individualSwitchAction[i][currentPage][SINGLE]->sendToMidi(); //send MidiMessage for single press action
                    }//if ((lastReleaseMillis[i]-lastPressMillis[i])<longPressMillis)
                }//if (WAIT_FOR_LONG_PRESS)
            }//else
        } //if (fsDebouncers[i].rose())
        
        if ((lastPressMillis[i] > lastReleaseMillis[i]) &&(currentMillis-lastPressMillis[i] > longPressMillis)) { //then switch has been held down long enough to trigger a long press
            if (not comboActive) { // (because we're ignoring switch presses while comboActive is still true)
                if (lastPressMillis[i] > lastLongPressSentMillis[i]) { //then we haven't yet sent a long press event
                    individualSwitchAction[i][currentPage][LONG]->sendToMidi(); //send MidiMessage for long press action
                    lastLongPressSentMillis[i] = currentMillis; // update last long press sent tracker so we don't send duplicate messages if switch is still held down next loop
                } //if (lastPressMillis > lastLongPressSentMillis)
            }//if (not comboActive)
        }//if ((lastPressMillis-lastReleaseMillis)>longPressMillis)
    }//for (int i=0; i<footSwitchCount; i++)
}//readFootswitches()
