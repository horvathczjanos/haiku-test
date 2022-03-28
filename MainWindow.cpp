#include "MainWindow.h"

#include <Application.h>
#include <Button.h>
#include <String.h>
#include <StringView.h>
#include <LayoutBuilder.h>
#include <TimeFormat.h>
#include <MessageRunner.h>



BButton* TestButton;
BStringView* TestString;
enum{TEST,TICK = 'ctik'};

BView* TestView;
BStringView* tmpTime;

int32 clickNumber = 0;
BMessageRunner* tmrTick;

MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,500,400),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE)
{
	TestButton = new BButton("testButton", "Test", new BMessage(TEST));
	
	TestString = new BStringView("testString", "Hello");
	
	TestView = new BView("TestClock", B_WILL_DRAW);
	
	tmpTime = new BStringView("tmpTime","10:28");
	
	tmrTick = new BMessageRunner(this, new BMessage(TICK), 10000);
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_ITEM_SPACING)
		.SetInsets(B_USE_WINDOW_INSETS)
		.AddGroup(B_HORIZONTAL)
			.Add(TestButton)
			.AddGlue()
			.Add(TestString)
			.AddGlue()
			.Add(tmpTime)
			.End();
			
	
			
}


void
MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case TEST:
		{
			clickNumber++; 
			
			BString tmpString("Clicking number is "); 
			tmpString << clickNumber;
			
			TestString->SetText(tmpString.String());	
			
			Tick();
			
			
		}break;
		
		case TICK:
		{
			Tick();
		}break;
			
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}




void MainWindow::Tick()
{
	time_t curTime = time(NULL);
	
	BString formatted;
	BTimeFormat fmTime;
	
	fmTime.Format(formatted, curTime, B_MEDIUM_TIME_FORMAT);
	tmpTime->SetText(formatted);
}


bool
MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
