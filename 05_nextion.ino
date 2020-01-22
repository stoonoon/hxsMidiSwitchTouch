NexPage page_boot = NexPage(0,0,"page_boot");
NexPage page_main = NexPage(1,0,"page_main");
NexPage page_other = NexPage(2,0,"page_other");
NexPage page_program = NexPage(3,0,"page_program");
NexPage page_error = NexPage(4,0,"page_error");

NexText t_fs0_line0 = NexText(1,1,"t_fs0_line0"); // text label for FS0, line 0 on page 1
NexText t_fs0_line1 = NexText(1,2,"t_fs0_line1"); // text label for FS0, line 1 on page 1
NexText t_fs1_line0 = NexText(1,3,"t_fs1_line0"); // text label for FS1, line 0 on page 1
NexText t_fs1_line1 = NexText(1,4,"t_fs1_line1"); // text label for FS1, line 1 on page 1
NexText t_fs2_line0 = NexText(1,5,"t_fs2_line0"); // text label for FS2, line 0 on page 1
NexText t_fs2_line1 = NexText(1,6,"t_fs2_line1"); // text label for FS2, line 1 on page 1
NexText t_fs3_line0 = NexText(1,7,"t_fs3_line0"); // text label for FS3, line 0 on page 1
NexText t_fs3_line1 = NexText(1,8,"t_fs3_line1"); // text label for FS3, line 1 on page 1
NexText t_fs4_line0 = NexText(1,9,"t_fs4_line0"); // text label for FS4, line 0 on page 1
NexText t_fs4_line1 = NexText(1,10,"t_fs4_line1"); // text label for FS4, line 1 on page 1
NexText t_fs5_line0 = NexText(1,11,"t_fs5_line0"); // text label for FS5, line 0 on page 1
NexText t_fs5_line1 = NexText(1,12,"t_fs5_line1"); // text label for FS5, line 1 on page 1
NexText t_fs6_line0 = NexText(1,13,"t_fs6_line0"); // text label for FS6, line 0 on page 1
NexText t_fs6_line1 = NexText(1,14,"t_fs6_line1"); // text label for FS6, line 1 on page 1
NexText t_fs7_line0 = NexText(1,15,"t_fs7_line0"); // text label for FS7, line 0 on page 1
NexText t_fs7_line1 = NexText(1,16,"t_fs7_line1"); // text label for FS7, line 1 on page 1

NexText *footSwitchScreenLabels[footSwitchCount][labelLinesPerSwitch] = { //array for footswitchLabels pointers to make them accessible in iterated functions
    {&t_fs0_line0, &t_fs0_line1},
    {&t_fs1_line0, &t_fs1_line1},
    {&t_fs2_line0, &t_fs2_line1},
    {&t_fs3_line0, &t_fs3_line1},
    {&t_fs4_line0, &t_fs4_line1},
    {&t_fs5_line0, &t_fs5_line1},
    {&t_fs6_line0, &t_fs6_line1},
    {&t_fs7_line0, &t_fs7_line1},
    };

NexButton main_prev_page_button = NexButton(1,17,"b_prev_page"); // << button on page 1
NexButton main_next_page_button = NexButton(1,18,"b_next_page"); // >> button on page 1
//NexButton other_prev_page_button = NexButton(2,1,"b0");
//NexButton other_next_page_button = NexButton(2,2,"b1");
//NexButton program_prev_page_button = NexButton(3,1,"b0");
//NexButton program_next_page_button = NexButton(3,2,"b1");

NexHotspot m_fs0 = NexHotspot(1, 19, "m_fs0");   // hotspot for fs0 on page 1
NexHotspot m_fs1 = NexHotspot(1, 20, "m_fs1");  // hotspot for fs1 on page 1
NexHotspot m_fs2 = NexHotspot(1, 21, "m_fs2");  // hotspot for fs2 on page 1
NexHotspot m_fs3 = NexHotspot(1, 22, "m_fs3");  // hotspot for fs3 on page 1
NexHotspot m_fs4 = NexHotspot(1, 23, "m_fs4");  // hotspot for fs4 on page 1
NexHotspot m_fs5 = NexHotspot(1, 24, "m_fs5");  // hotspot for fs5 on page 1
NexHotspot m_fs6 = NexHotspot(1, 25, "m_fs6");  // hotspot for fs6 on page 1
NexHotspot m_fs7 = NexHotspot(1, 26, "m_fs7");  // hotspot for fs7 on page 1

NexTouch *nex_listen_list[] =  {
  &main_prev_page_button, &main_next_page_button,
  &m_fs0, &m_fs1, &m_fs2, &m_fs3, 
  &m_fs4, &m_fs5, &m_fs6, &m_fs7, 
//  &other_prev_page_button, &other_next_page_button,
//  &program_prev_page_button, &program_next_page_button,
  NULL  
};

void setupTouchscreen() {
    nexInit();
    main_prev_page_button.attachPop(main_prev_page_Release, &main_prev_page_button);
    main_next_page_button.attachPop(main_next_page_Release, &main_next_page_button);
    m_fs0.attachPush(m_fs0_Press);
    m_fs1.attachPush(m_fs1_Press);
    m_fs2.attachPush(m_fs2_Press);
    m_fs3.attachPush(m_fs3_Press);
    m_fs4.attachPush(m_fs4_Press);
    m_fs5.attachPush(m_fs5_Press);
    m_fs6.attachPush(m_fs6_Press);
    m_fs7.attachPush(m_fs7_Press);
    //other_prev_page_button.attachPop(other_prev_page_Release, &other_prev_page_button);
    //other_next_page_button.attachPop(other_next_page_Release, &other_next_page_button);
    //program_prev_page_button.attachPop(program_prev_page_Release, &program_prev_page_button);
    //program_next_page_button.attachPop(program_next_page_Release, &program_next_page_button);
    delay(100); // delay to pause on Booting screen - just for visual confirmation of restart
    page_main.show();
    updateScreenLabels();
}//setupTouchscreen()

void main_prev_page_Release(void *ptr) {
    Serial.println("main_prev_page_Release");
    if (currentPage > 0) {
        currentPage--;
    }
    else {
        currentPage = totalPresetPages-1;
    }
    updateScreenLabels();
}

void main_next_page_Release(void *ptr) {
    Serial.println("main_next_page_Release");
    currentPage++;
    if (currentPage >= totalPresetPages) {
        currentPage =0;
    }
    updateScreenLabels();
}

void m_fs0_Press(void *ptr){
    individualSwitchAction[0][currentPage][SINGLE]->sendToMidi();
} //void m_fs_0_press

void m_fs1_Press(void *ptr){
    individualSwitchAction[1][currentPage][SINGLE]->sendToMidi();
} //void m_fs_1_press

void m_fs2_Press(void *ptr){
    individualSwitchAction[2][currentPage][SINGLE]->sendToMidi();
} //void m_fs_2_press

void m_fs3_Press(void *ptr){
    individualSwitchAction[3][currentPage][SINGLE]->sendToMidi();
} //void m_fs_3_press

void m_fs4_Press(void *ptr){
    individualSwitchAction[4][currentPage][SINGLE]->sendToMidi();
} //void m_fs_4_press

void m_fs5_Press(void *ptr){
    individualSwitchAction[5][currentPage][SINGLE]->sendToMidi();
} //void m_fs_5_press

void m_fs6_Press(void *ptr){
    individualSwitchAction[6][currentPage][SINGLE]->sendToMidi();
} //void m_fs_6_press

void m_fs7_Press(void *ptr){
    individualSwitchAction[7][currentPage][SINGLE]->sendToMidi();
} //void m_fs_7_press

