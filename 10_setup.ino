void setup() {
  Serial.begin(250000);
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  pinMode(expToeswitchPin, INPUT);
  setupFootSwitches(); //configure pins and attach debouncers
  setupFootSwitchActions(); //initialise array with preset config
  nexInit();
  main_prev_page_button.attachPop(main_prev_page_Release, &main_prev_page_button);
  main_next_page_button.attachPop(main_next_page_Release, &main_next_page_button);
  other_prev_page_button.attachPop(other_prev_page_Release, &other_prev_page_button);
  other_next_page_button.attachPop(other_next_page_Release, &other_next_page_button);
  program_prev_page_button.attachPop(program_prev_page_Release, &program_prev_page_button);
  program_next_page_button.attachPop(program_next_page_Release, &program_next_page_button);
  delay(500); // delay to pause on Booting screen - just for visual confirmation of restart
  page_main.show();
  updateScreenLabels();
  
}
