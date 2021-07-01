#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"


USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Gravity Jump");
    eglView->setFrameSize(1280, 800);
    return CCApplication::sharedApplication()->run();
}
