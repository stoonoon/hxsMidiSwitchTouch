NexPage page_boot = NexPage(0,0,"page_boot");
NexPage page_main = NexPage(1,0,"page_main");
NexPage page_other = NexPage(2,0,"page_other");
NexPage page_program = NexPage(3,0,"page_program");
NexPage page_error = NexPage(4,0,"page_error");


NexText t_fs0_line0 = NexText(1,1,"t_fs0_line0");
NexText t_fs0_line1 = NexText(1,5,"t_fs0_line1");
NexText t_fs1_line0 = NexText(1,2,"t_fs1_line0");
NexText t_fs1_line1 = NexText(1,6,"t_fs1_line1");
NexText t_fs2_line0 = NexText(1,3,"t_fs2_line0");
NexText t_fs2_line1 = NexText(1,7,"t_fs2_line1");
NexText t_fs3_line0 = NexText(1,4,"t_fs3_line0");
NexText t_fs3_line1 = NexText(1,8,"t_fs3_line1");
NexText t_fs4_line0 = NexText(1,9,"t_fs4_line0");
NexText t_fs4_line1 = NexText(1,13,"t_fs4_line1");
NexText t_fs5_line0 = NexText(1,10,"t_fs5_line0");
NexText t_fs5_line1 = NexText(1,14,"t_fs5_line1");
NexText t_fs6_line0 = NexText(1,11,"t_fs6_line0");
NexText t_fs6_line1 = NexText(1,15,"t_fs6_line1");
NexText t_fs7_line0 = NexText(1,12,"t_fs7_line0");
NexText t_fs7_line1 = NexText(1,16,"t_fs7_line1");

NexText *footSwitchScreenLabels[footSwitchCount][labelLinesPerSwitch] = {
    {&t_fs0_line0, &t_fs0_line1},
    {&t_fs1_line0, &t_fs1_line1},
    {&t_fs2_line0, &t_fs2_line1},
    {&t_fs3_line0, &t_fs3_line1},
    {&t_fs4_line0, &t_fs4_line1},
    {&t_fs5_line0, &t_fs5_line1},
    {&t_fs6_line0, &t_fs6_line1},
    {&t_fs7_line0, &t_fs7_line1},
    };

NexButton main_prev_page_button = NexButton(1,17,"b_prev_page");
NexButton main_next_page_button = NexButton(1,18,"b_next_page");
NexButton other_prev_page_button = NexButton(2,1,"b0");
NexButton other_next_page_button = NexButton(2,2,"b1");
NexButton program_prev_page_button = NexButton(3,1,"b0");
NexButton program_next_page_button = NexButton(3,2,"b1");

NexTouch *nex_listen_list[] =  {
  &main_prev_page_button, &main_next_page_button,
  &other_prev_page_button, &other_next_page_button,
  &program_prev_page_button, &program_next_page_button,
  NULL  
};

void main_prev_page_Release(void *ptr) {
  //page_program.show();
    if (currentPage > 0) {
        currentPage--;
    }
    else {
        currentPage = totalPresetPages-1;
    }
    updateScreenLabels();
}

void main_next_page_Release(void *ptr) {
  //page_other.show();
  currentPage++;
  if (currentPage >= totalPresetPages) {
    currentPage =0;
  }
  updateScreenLabels();
}

void other_prev_page_Release(void *ptr) {
  page_main.show();
}

void other_next_page_Release(void *ptr) {
  page_program.show();
}

void program_prev_page_Release(void *ptr) {
  page_other.show();
}

void program_next_page_Release(void *ptr) {
  page_main.show();
}
