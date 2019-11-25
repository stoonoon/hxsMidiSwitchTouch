void loop() {
  // put your main code here, to run repeatedly:
  nexLoop(nex_listen_list);
  readExpPedalCC();
  readExpToeswitch();
  readFootSwitches();
 
}
