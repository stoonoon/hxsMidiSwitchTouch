/*
Class prototypes for MidiMessage and derived classes
*/

class MidiMessage {
    public:
        char label[2][(FOOTSWITCH_LABEL_MAX_LENGTH+1)];
        virtual void sendToMidi();
        bool isValidSingleMessage(); // used to prevent macro nesting 
    protected:
        enum MidiMsgType {CC=1, MACRO=5, NOT_KNOWN=99}; // may need to add PC, SYSEX
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
void setPageAction(int page, individualActionType action, MidiMessage *msg[footSwitchCount]);


