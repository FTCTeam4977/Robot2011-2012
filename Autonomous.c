#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     gyro,                sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     htproto,             sensorI2CCustom9V)
#pragma config(Motor,  motorA,          rightArmSpin,  tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          leftArmSpin,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     armClaw,       tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armWrist,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ballCollector, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftDrive,     tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armBase,       tmotorNormal, openLoop)

#define GYRO S2
#include "autonoLib.c"
#include "JoystickDriver.c"
#include "autonoBluLeft.c"
#include "autonoBluRight.c"
#include "autonoRedLeft.c"
#include "autonoRedRight.c"

#define Wait(t) wait1Msec(t*1000)

int MenuItem = 1;   //int for to change the menu item with the buttons.
int MenuNum = 1;    //int to manage what menu your in.
int Enter;          //int to find out when the "Enter" button was press.
int Exit;           //int to find out when the "Exit" button was press.
char Color;         //char to store color choice.
string ColorDisplay;//string to display color.
char Side;          //char to store side choice.
string SideDisplay; //string to display side.
char Auto;          //char to store auto choice.
string AutoDisplay; //string to display auto.
int Delay = 1;      //int to store Delay time.
int ExitProgram = 1;//int to find out how many

void convert()  // function that converts the chars to string
{
    if(Color == 'b')
        ColorDisplay = "Blue";
    if(Color == 'r')
        ColorDisplay = "Red";
    if(Side == '1')
        SideDisplay = "Left";
    if(Side == '2')
        SideDisplay = "Right";
    if(Auto == 'b')
        AutoDisplay = "bowlingbowl";
    if(Auto == 'd')
        AutoDisplay = "Drive";
    if(Auto == 'c')
        AutoDisplay = "Go crazy";
}

void GoBack()
{
    if (Exit)
    {
        Exit = false;
        --MenuNum;
    }
}

void Menu()     // function that handles the menu
{
    switch (MenuNum) // switches wich menu to be in
    {
        case 1: //color select
            switch (MenuItem) // swithes the item selected
        {
            case 0: // fixes if the user hits to far left
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
            case 3: // fixes if the user hits to far left
                MenuItem = 1;
                break;

        }
            if (Enter) // when user hits enter
            {
              Enter = false; // set enter back to
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
                        break;
                }
            }
            break;
        case 2://ramp side
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
            if (Enter)
            {
                Enter = false;
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
                break;
                }
            }
            break;
        case 3://autoamous type
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
            if (Enter)
            {
                Enter = false;
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
            eraseDisplay();
            nxtDisplayString(1,"Wait for %i seconds",Delay);
            switch (MenuItem)
        {
            case 0:
                MenuItem = 1;
                if (Delay > 0)
                --Delay;
                break;
            case 2:
                MenuItem = 1;
                if (Delay < 30)
                ++Delay;
                break;
        }
            if (Enter)
            {
                Enter = false;
                MenuNum = 5;
            }
            break;
        case 5:
            nxtDisplayString(1,"Is this correct?");
            nxtDisplayString(2,"Color :%s",ColorDisplay);
            nxtDisplayString(3,"side: %s",SideDisplay);
            nxtDisplayString(4,"Auto: %s",AutoDisplay);
            nxtDisplayString(5,"Delay: %i",Delay);
            switch (MenuItem)
        {
            case 0:
                MenuItem = 2;
                break;

            case 1:
                nxtDisplayString(6,"<Yes>");
                nxtDisplayString(7,"No");
                break;

            case 2:
                nxtDisplayString(6,"Yes");
                nxtDisplayString(7,"<No>");
                break;

            case 3:
                MenuItem = 1;
                break;
        }
            if (Enter)
            {
                Enter = false;
                switch (MenuItem)
                {
                    case 1:
                        MenuNum = 6;
                        MenuItem = 1;
                        eraseDisplay();
                        ExitProgram = 1;

                        break;

                    case 2:
                        Color = ' ';
                        Side = ' ';
                        Auto = ' ';
                        Delay = 0;
                        MenuNum = 1;
                        MenuItem = 1;
                        eraseDisplay();
                        ExitProgram = 1;
                        break;

                }
            }
            break;
        case 6:
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
                            nxtDisplayString(3,"left");
                            nxtDisplayString(4,"get the bowl ball");

                            waitForStart();
                            Wait(Delay);
                            //code for blue side1 get bowling ball
                            BluLeftBall();
                            return;
                        case 'd':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"left");
                            nxtDisplayString(4,"drive straight");

                            waitForStart();
                            Wait(Delay);
                            //code for blue side1 drive straight
                            return;
                        case 'c':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"left");
                            nxtDisplayString(4,"go crazy");
                            return;

                            waitForStart();
                            Wait(Delay);
                            //code for blue side1 go strange
                    }
                    case '2':
                    switch (Auto)
                    {
                        case 'b':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"right");
                            nxtDisplayString(4,"get the bowl ball");

                            waitForStart();
                            Wait(Delay);
                            //code for blue side2 get the bowling ball
                            BluRightBall();
                            return;
                        case 'd':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"right");
                            nxtDisplayString(4,"drive straight");

                            waitForStart();
                            Wait(Delay);
                            //code for blue side2 drive straight


                            return;
                        case 'c':
                            nxtDisplayString(2,"blue");
                            nxtDisplayString(3,"right");
                            nxtDisplayString(4,"go crazy");

                            waitForStart();
                            Wait(Delay);
                            //code for blue side2 go crazy

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
                            nxtDisplayString(3,"left");
                            nxtDisplayString(4,"get the bowl ball");

                            waitForStart();
                            Wait(Delay);
                            //code for red side1 get the bowling ball
                            RedLeftBall();

                            return;
                        case 'd':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"left");
                            nxtDisplayString(4,"drive straight");

                            waitForStart();
                            Wait(Delay);
                            //code for red side1 drive straight


                            return;
                        case 'c':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"left");
                            nxtDisplayString(4,"go crazy");

                            waitForStart();
                            Wait(Delay);
                            //code for red side1 go crazy

                            return;
                    }
                    case '2':
                        switch (Auto)
                    {
                        case 'b':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"right");
                            nxtDisplayString(4,"get the bowl ball");

                            waitForStart();
                            Wait(Delay);
                            //code for red side2 get the bowling ball
                            RedRightBall();

                            return;
                        case 'd':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"right");
                            nxtDisplayString(4,"drive straight");

                            waitForStart();
                            Wait(Delay);
                            //code for red side2 get drive straight

                            return;
                        case 'c':
                            nxtDisplayString(2,"red");
                            nxtDisplayString(3,"right");
                            nxtDisplayString(4,"go crazy");

                            waitForStart();
                            Wait(Delay);
                            //code for red side2 go crazy

                            return;

                    }

                }


            }
             default:
                MenuNum = 1;
                break;
}
}
task main()
{
  nNxtButtonTask = -2;//takes full control of buttons and allows us to us exit button
  nNxtExitClicks = 3;// because we take control, we need a way the exit the program,with this we exit by hitiing exit three times
  nxtDisplayString(1,"AutonomousSelect");
  nxtDisplayString(2,"left up");
  nxtDisplayString(3,"right down");
  nxtDisplayString(4,"enter to choose");
  nxtDisplayString(5,"brown to go back");
  wait1Msec(5000);
  eraseDisplay();
  while(true)
  {
    int nBtn;
      Menu();
      convert();
	nxtDisplayString(0,"C:%c S:%c A:%c",Color,Side,Auto);
    while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn != -1)
	  	  break;
	  }
	  switch (nBtn)
	  {

      case kLeftButton:        --MenuItem;                     break;
			case kRightButton: ++MenuItem;    	 	           break;
			case kEnterButton: Enter = true;    ++ExitProgram; break;
            case kExitButton:  Exit = true;     --ExitProgram; break;
    }

		nxtDisplayString(0,"C:%c S:%c A:%c",Color,Side,Auto);
      Menu();
      GoBack();
      convert();
	  while (true)
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn == -1)
	  	  break;
	  }

	}
}
