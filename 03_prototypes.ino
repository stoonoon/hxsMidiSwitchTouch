/*
Class prototypes for MidiMessage and derived classes
*/

class MidiMessage { // this should probably be renamed FootswitchAction
    public:
        char label[2][(FOOTSWITCH_LABEL_MAX_LENGTH+1)];
        virtual void sendToMidi();
        bool isValidSingleMessage(); // used to prevent macro nesting 
    protected:
        enum MidiMsgType {CC=1, PC=2, MACRO=5, LOCAL=6, TOGGLER=7, NOT_KNOWN=99}; // may need to add SYSEX at some point?
        MidiMsgType msgType; // used for downcasting to specific subclass type
        void setLabel(char* destLabel, char* sourceLabel); //  checks length of incoming label and shortens it if required before copying   
};

class MidiNullMessage : public MidiMessage { // blank message used where no function allocated
    public:
        MidiNullMessage();
        void sendToMidi() override;
};//class MidiNullMessage

class MidiCCMessage : public MidiMessage { //Control Change Message Type
    public:
        MidiCCMessage(int ccn, int ccv, char* label1, char* label2);
        int controlNumber;
        int controlValue;
        void sendToMidi() override;
};

class MidiPCMessage : public MidiMessage { //Program Change Message Type
    public:
        MidiPCMessage(int pn, char* label1, char* label2);
        int programNumber;
        void sendToMidi() override;
};

class MidiMessageToggler : public MidiMessage { // Toggler - cycles between 2 (or more) MidiMessages
  public:
    MidiMessageToggler(MidiMessage * msgs[], int count);
    MidiMessageToggler(MidiMessage * msg0, MidiMessage * msg1);
    MidiMessage *commands[maxTogglerSize-1];
    int currentCmd;
    int cmdCount;
    void sendToMidi() override;
};

class LocalMessage : public MidiMessage {
/*
 * This is primarily to allow footswitch control of the current menu page, but could be useful later to allow control other aspects of controller operation
 * 
 * Given that this is not really a MidiMessage, it would probably make sense to refactor the code so MidiMessage is renamed ControllerAction or 
 * something similar. Would also need to rename sendToMidi() to do() or something similar. Leaving as is for now while I test if it works as expected
 * 
 */
  public:
    LocalMessage(byte cmd, char* label1, char* label2);
    int command;
    void sendToMidi() override;
};
  

class MidiMessageMacro : public MidiMessage { //container for multiple messages to be sent as one action
    public:
        int commandCount;
        MidiMessage *commands[MAX_MACRO_LENGTH];
        MidiMessageMacro(MidiMessage *msg1, MidiMessage *msg2, MidiMessage *msg3, char* label1, char* label2);
        void sendToMidi() override;
};//class MidiMessageMacro



/*
Function prototypes for functions using MidiMessage as parameter
*/

//07_footswitches.ino
void setAllPagesAction(int fs, individualActionType action, MidiMessage *msg);
void setWholePageActions(int page, individualActionType action, MidiMessage *msg[footSwitchCount]);
void setComboAction(int page, int fsA, int fsB, MidiMessage *msg);
