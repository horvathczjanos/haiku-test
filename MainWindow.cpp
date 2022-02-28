#include "MainWindow.h"

#include <Application.h>
#include <Button.h>
#include <String.h>
#include <StringView.h>
#include <LayoutBuilder.h>


BButton* TestButton;
BStringView* TestString;
enum{TEST};

int32 clickNumber = 0;


MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,500,400),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	TestButton = new BButton("testButton", "Test", new BMessage(TEST));
	
	TestString = new BStringView("testString", "Hello");
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_ITEM_SPACING)
		.SetInsets(B_USE_WINDOW_INSETS)
		.AddGroup(B_HORIZONTAL)
			.Add(TestButton)
			.AddGlue()
			.Add(TestString)
			.AddGlue()
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
			} break;
		
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}


bool
MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
