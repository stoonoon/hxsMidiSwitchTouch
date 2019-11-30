void setup() {
  Serial.begin(250000);
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  pinMode(expToeswitchPin, INPUT);
  setupFootSwitches(); //configure pins and attach debouncers
  setupFootSwitchActions(); //initialise array with preset config
  setupTouchscreen();
}
