/*
Class prototypes for MidiMessage and MidiMacro
*/

class MidiMessage {
    public:
        MidiMessage();
        static const int textLabelMaxLength = 6; //Max number of characters for each text label line - maybe change to vector so this can be passed from main part
        enum MidiMsgType {PC, CC, SYSEX, NOT_KNOWN};
        MidiMsgType msgType;       
        char buttonLabel1[(textLabelMaxLength+1)];
        char buttonLabel2[(textLabelMaxLength+1)];
};

class MidiCCMessage : public MidiMessage {
  public:
    MidiCCMessage(int ccn, int ccv, char* label1, char* label2);
    int controlNumber;
    int controlValue;
  protected:
};

class MidiMacro {
  public:
    static const int textLabelMaxLength = 6; //Max number of characters for each text label line - maybe change to vector so this can be passed from main part

    static const int maxMacroLength =5; //Maximum number of commands in a single macro;
    int commandCount; // number of commands in macro
    MidiMessage *commands[maxMacroLength]; //array of MidiMessage commands
    char buttonLabel1[(textLabelMaxLength+1)];
    char buttonLabel2[(textLabelMaxLength+1)];
    MidiMacro(MidiMessage *msg);
    MidiMacro(MidiMessage *msg1, MidiMessage *msg2, MidiMessage *msg3, char* label1, char* label2);
  
    /*
    void addCommand(MidiMessage msg); // add msg to end of command list
    void removeLastCommand(); // remove last item from command list
    */
};


/*
Function prototypes for functions using MidiMessage / MidiMacro as parameter
*/

//05_midi.ino
void sendMidiMessage(MidiMessage *msg);
void sendMidiMacro(MidiMacro *macro);

//07_footswitches.ino
void assignSingleClick(int switchIndex, MidiMacro *macro);
