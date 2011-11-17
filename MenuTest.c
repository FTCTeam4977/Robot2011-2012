int MenuItem = 1;
int MenuSwitch = 1;
int Enter;
int Exit;
void Menu()
{

}



task main()
{
  nNxtButtonTask = -2;//takes full control of buttons and allows us to us exit button
  nNxtExitClicks = 3;// because we take control, we need a way the exit the program,with this we exit by hitiing exit three times
  while(true)
  {
    int nBtn;
    while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn != -1)
	  	  break;
	  }
	  switch (nBtn)
	  {
	  	case kLeftButton:	 --MenuItem;    		      	  break;
			case kRightButton: ++MenuItem;    	 	          break;
			case kEnterButton: Enter = 1;   MenuItem = 1;   break;
			case kExitButton:	 Exit = 1;     	  		        break;
		}
		nxtDisplayString(0,"%i",MenuItem);
		Menu();

	  while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn == -1)
	  	  break;
	  }

	}
}
