
Bounce fsDebouncers[footSwitchCount];

int footSwitchCurrentValue[footSwitchCount]; //for current state of footswitch state
int footSwitchLastValue[footSwitchCount]; //last known footswitch state so we know whether it has changed

MidiMacro *singleClickAction[footSwitchCount];
bool singleClickActionIsAssigned[footSwitchCount] = {0}; //initialize all to false

bool fsIndexIsValid (int fsIndex){ //function to check if a given int is a valid footswitch index
        if ((fsIndex >= -1) && (fsIndex < footSwitchCount) ) { //then switchIndex is valid
            return true;
            }
        else {
            return false;
            }   
}// fsIndexIsValid

void assignSingleClick(int switchIndex, MidiMacro *macro) {
    if (fsIndexIsValid(switchIndex) ) { 
        singleClickAction[switchIndex] = macro;
        singleClickActionIsAssigned[switchIndex] = true;
        //update screen text labels here
        switch (switchIndex) {
            case 0:
                t_fs0_line0.setText(macro->buttonLabel1);
                t_fs0_line1.setText(macro->buttonLabel2);
                break;
            case 1:
                t_fs1_line0.setText(macro->buttonLabel1);
                t_fs1_line1.setText(macro->buttonLabel2);
                break;
            case 2:
                t_fs2_line0.setText(macro->buttonLabel1);
                t_fs2_line1.setText(macro->buttonLabel2);
                break;
            case 3:
                t_fs3_line0.setText(macro->buttonLabel1);
                t_fs3_line1.setText(macro->buttonLabel2);
                break;
            case 4:
                t_fs4_line0.setText(macro->buttonLabel1);
                t_fs4_line1.setText(macro->buttonLabel2);
                break;
            case 5:
                t_fs5_line0.setText(macro->buttonLabel1);
                t_fs5_line1.setText(macro->buttonLabel2);
                break;
            case 6:
                t_fs6_line0.setText(macro->buttonLabel1);
                t_fs6_line1.setText(macro->buttonLabel2);
                break;
            case 7:
                t_fs7_line0.setText(macro->buttonLabel1);
                t_fs7_line1.setText(macro->buttonLabel2);
                break;
            
        }//switch
    }//if
    else {
        Serial.print("assignSingleClick called with out of range index : ");
        Serial.println(switchIndex);
        }//else
}//assignSingleClick

void updateFootSwitchAssignments() {
    for (int i=0; i<footSwitchCount; i++) {
        assignSingleClick(i,singleClickMacroPages[currentPage][i]);
    }//for
}//updateFootSwitchAssignments

void setupFootSwitches() {
  for (int i=0; i<footSwitchCount; i++) {
    fsDebouncers[i] = Bounce();
    pinMode(footSwitchPin[i], INPUT_PULLUP);
    fsDebouncers[i].attach(footSwitchPin[i]);
    fsDebouncers[i].interval(5); //interval in ms
    footSwitchCurrentValue[i] = footSwitchUp;
    footSwitchLastValue[i] = footSwitchUp;
  }//for loop
  assignSingleClick(0,&hxsSnap1Macro);
  assignSingleClick(1,&hxsSnap2Macro);
  assignSingleClick(2,&hxsSnap3Macro);
  assignSingleClick(3,&hxsPresetUpMacro);
  assignSingleClick(4,&hxsFS1Macro);
  assignSingleClick(5,&hxsFS2Macro);
  assignSingleClick(6,&hxsFS3Macro);
  assignSingleClick(7,&hxsPresetDownMacro);
  
}//setupFootSwitches()



void doSingleSwitchAction(int sw) {
    if (fsIndexIsValid(sw)) {
        if (singleClickActionIsAssigned[sw]) { //fs has an assigned macro
            sendMidiMacro(singleClickAction[sw]);
            //singleClickAction[sw]->sendToMidi();
        }// if assigned
    }// if fsIndexIsValid
}//singleSwitchAction

void readFootSwitches() {
  for (int i=0; i<footSwitchCount; i++) {
    fsDebouncers[i].update();
    footSwitchCurrentValue[i] = fsDebouncers[i].read();
    if (fsDebouncers[i].fell()) {
      doSingleSwitchAction(i);
    }//if
  }//for loop
}//readFootswitches()
