int MenuItem = 1;
int MenuNum = 1;
int Enter = 0;
int Exit;
void Menu()
{
    switch (MenuNum)
    {
        case 1:
            switch (MenuItem)
        {
            case 1:
                nxtDisplayString(1,"<Test Code>");
                nxtDisplayString(2,"Edit Code");
                nxtDisplayString(3,"Exit");
                break;
            case 2:
                nxtDisplayString(1,"Test Code");
                nxtDisplayString(2,"<Edit Code>");
                nxtDisplayString(3,"Exit");
                break;
            case 3:
                nxtDisplayString(1,"Test Code");
                nxtDisplayString(2,"Edit Code");
                nxtDisplayString(3,"<Exit>");
                break;
            default:
                nxtDisplayString(1,"<Test Code>");
                nxtDisplayString(2,"Edit Code");
                nxtDisplayString(3,"Exit");
                break;

            }
            if (Enter == 1)
            {
              Enter = 0;
                switch (MenuItem)
                {
                    case 1:
                        MenuNum = 2;
                        MenuItem = 1;
                        break;
                }
            }
            break;
        case 2:
            switch (MenuItem)
        {
                case 1:
                    nxtDisplayString(1,"Run code Menu");
                    break;

                default:
                    break;
            }
    }
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
			case kEnterButton: Enter = 1;                   break;
			case kExitButton:	 Exit = 1;                      break;
		}
		nxtDisplayString(0,"MI%i MN%i",MenuItem ,MenuNum);
		Menu();

	  while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn == -1)
	  	  break;
	  }

	}
}
