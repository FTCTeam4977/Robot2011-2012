int MenuItem = 1;
int MenuNum = 1;
int Enter = 0;

char Color;
char Side;
char Auto;
void Menu();
void Menu()
{
    switch (MenuNum)
    {

        case 1: //color select
            nxtDisplayString(3,"");
            nxtDisplayString(4,"");
            nxtDisplayString(5,"");
            switch (MenuItem)
        {
            case 0:
                MenuItem = 2;
                break;
            case 1:
                nxtDisplayString(1,"<Blue>");
                nxtDisplayString(2,"Red");
                break;
            case 2:
                nxtDisplayString(1,"Blue");
                nxtDisplayString(2,"<Red>");
                break;
            case 3:
                MenuItem = 1;
                break;

        }
            if (Enter == 1)
            {
              Enter = 0;
                switch (MenuItem)
                {
                    case 1:
                        Color = 'b';
                        MenuNum = 2;
                        MenuItem = 1;
                        break;
                    case 2:
                        Color = 'r';
                        MenuNum = 2;
                        MenuItem = 1;
                }
            }
            break;
        case 2://ramp side
            nxtDisplayString(3,"");
            nxtDisplayString(4,"");
            nxtDisplayString(5,"");
            switch (MenuItem)
        {
            case 0:
                MenuItem = 2;
                break;

            case 1:
                nxtDisplayString(1,"<side 1>");
                nxtDisplayString(2,"side 2");
                    break;

            case 2:
                nxtDisplayString(1,"side 1");
                nxtDisplayString(2,"<side 2>");
                break;

            case 3:
                MenuItem = 1;
                break;
            }
            if (Enter == 1)
            {
                Enter = 0;
                switch (MenuItem)
                {
            case 1:
                Side = '1';
                MenuNum = 3;
                MenuItem = 1;
                break;
            case 2:
                Side = '2';
                MenuNum = 3;
                MenuItem = 1;
                }
            }
            break;
        case 3://autoamous type

            nxtDisplayString(4,"");
            nxtDisplayString(5,"");
            switch (MenuItem)
        {
            case 0:
                MenuItem = 3;
                break;
            case 1:
                nxtDisplayString(1,"<Get bowlingball>");
                nxtDisplayString(2,"Drive strange");
                nxtDisplayString(3,"Go crazy");
                break;
            case 2:
                nxtDisplayString(1,"Get bowling ball");
                nxtDisplayString(2,"<Drive strange>");
                nxtDisplayString(3,"Go crazy");
                break;
            case 3:
                nxtDisplayString(1,"Get bowling ball");
                nxtDisplayString(2,"Drive strange");
                nxtDisplayString(3,"<Go crazy>");
                break;
            case 4:
                MenuItem = 1;
                break;

        }
            if (Enter == 1)
            {
                Enter = 0;
                switch (MenuItem)
                {
            case 1:
                Auto = 'b';
                MenuNum = 4;
                MenuItem = 1;
                break;
            case 2:
                Auto = 'd';
                MenuNum = 4;
                MenuItem = 1;
                break;
            case 3:
                Auto = 'c';
                MenuNum = 4;
                MenuItem = 1;
                break;
                }
            }
            break;
        case 4:
            nxtDisplayString(3,"Color :%c",Color);
            nxtDisplayString(4,"side: %c",Side);
            nxtDisplayString(5,"Auto:%c",Auto);
            switch (MenuItem)
        {
            case 0:
                MenuItem = 2;
                break;

            case 1:
                nxtDisplayString(1,"<Yes>");
                nxtDisplayString(2,"No");
                break;

            case 2:
                nxtDisplayString(1,"Yes");
                nxtDisplayString(2,"<No>");
                break;

            case 3:
                MenuItem = 1;
                break;
        }
            if (Enter == 1)
            {
                Enter = 0;
                switch (MenuItem)
                {
                    case 1:
                        MenuNum = 5;
                        MenuItem = 1;
                        break;
                    case 2:
                        Color = ' ';
                        Side = ' ';
                        Auto = ' ';
                        MenuNum = 1;
                        MenuItem = 1;
                }
            }

            break;
        case 5:
            eraseDisplay();
            nxtDisplayString(1,"waiting for start");
            switch (Color)
            {
                case 'b':
                switch (Side)
                {
                    case '1':
                    switch (Auto)
                    {
                        case 'b':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"side 1");
                            nxtDisplayString(4,"get the bowl ball");
                            return;
                        case 'd':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"side 1");
                            nxtDisplayString(4,"drive straight");
                            return;
                        case 'c':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"side 1");
                            nxtDisplayString(4,"go crazy");
                            return;
                    }
                    case '2':
                    switch (Auto)
                    {
                        case 'b':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"side 2");
                            nxtDisplayString(4,"get the bowl ball");
                            return;
                        case 'd':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"side 2");
                            nxtDisplayString(4,"drive straight");
                            return;
                        case 'c':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"side 2");
                            nxtDisplayString(4,"go crazy");
                            return;
                    }

                }
                    break;
                case 'r':
                    switch (Side)
                {
                    case '1':
                        switch (Auto)
                    {
                        case 'b':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"side 1");
                            nxtDisplayString(4,"get the bowl ball");
                            return;
                        case 'd':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"side 1");
                            nxtDisplayString(4,"drive straight");
                            return;
                        case 'c':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"side 1");
                            nxtDisplayString(4,"go crazy");
                            return;
                    }
                    case '2':
                        switch (Auto)
                    {
                        case 'b':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"side 2");
                            nxtDisplayString(4,"get the bowl ball");
                            return;
                        case 'd':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"side 2");
                            nxtDisplayString(4,"drive straight");
                            return;
                        case 'c':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"side 2");
                            nxtDisplayString(4,"go crazy");
                            return;
                    }

                }


            }

}


}
task main()
{
  nNxtButtonTask = -2;//takes full control of buttons and allows us to us exit button
  nNxtExitClicks = 1;// because we take control, we need a way the exit the program,with this we exit by hitiing exit three times
  while(true)
  {
    int nBtn;
      Menu();
	nxtDisplayString(0,"C:%c S:%c A:%c",Color,Side,Auto);
    while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn != -1)
	  	  break;
	  }
	  switch (nBtn)
	  {
            case kLeftButton:  --MenuItem;                    break;
			case kRightButton: ++MenuItem;    	 	          break;
			case kEnterButton:  Enter = 1;                    break;
      }
		nxtDisplayString(0,"C:%c S:%c A:%c",Color,Side,Auto);
      Menu();

	  while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn == -1)
	  	  break;
	  }

	}
}
