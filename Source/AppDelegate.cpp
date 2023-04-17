#include "AppDelegate.h"
#include <timeapi.h>
#include "HelloWorldScene.h"
#include "UIScene.h"
#include "TestScenes/TestScene8.h"
#include "TestScenes/TestScene9.h"
#include "TestScenes/TestScene10.h"
#include "TestScenes/TestScene11.h"
#include "TestScenes/TestScene12.h"
#include "TestScenes/TestScene13.h"


// #define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
static cocos2d::Size hdResolutionSize = cocos2d::Size(1280, 720);

/**
@brief    This function change the PVRFrame show/hide setting in register.
@param  bEnable If true show the PVRFrame window, otherwise hide.
*/
static void PVRFrameEnableControlWindow(bool bEnable);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{

#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

int AppDelegate::run1()
{
    PVRFrameEnableControlWindow(false);

    ///////////////////////////////////////////////////////////////////////////
    /////////////// changing timer resolution
    ///////////////////////////////////////////////////////////////////////////
    UINT TARGET_RESOLUTION = 1; // 1 millisecond target resolution
    TIMECAPS tc;
    UINT wTimerRes = 0;
    if (TIMERR_NOERROR == timeGetDevCaps(&tc, sizeof(TIMECAPS)))
    {
        wTimerRes = std::min(std::max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
        timeBeginPeriod(wTimerRes);
    }

    // Main message loop:
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceCounter(&nLast);

    initGLContextAttrs();

    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return 1;
    }

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // Retain glview to avoid glview being released in the while loop
    glview->retain();

    LONGLONG interval = 0LL;
    LONG waitMS = 0L;

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    //Goto
P1:

    while (!glview->windowShouldClose())
    {
        QueryPerformanceCounter(&nNow);
        interval = nNow.QuadPart - nLast.QuadPart;
        if (interval >= _animationInterval.QuadPart)
        {
            nLast.QuadPart = nNow.QuadPart;
            director->mainLoop();
            glview->pollEvents();
        }
        else
        {
            // The precision of timer on Windows is set to highest (1ms) by 'timeBeginPeriod' from above code,
            // but it's still not precise enough. For example, if the precision of timer is 1ms,
            // Sleep(3) may make a sleep of 2ms or 4ms. Therefore, we subtract 1ms here to make Sleep time shorter.
            // If 'waitMS' is equal or less than 1ms, don't sleep and run into next loop to
            // boost CPU to next frame accurately.
            waitMS = static_cast<LONG>((_animationInterval.QuadPart - interval) * 1000LL / freq.QuadPart - 1L);
            if (waitMS > 1L)
                Sleep(waitMS);
        }
    }

    if (glview->isOpenGLReady())
    {
        glfwSetWindowShouldClose(dynamic_cast<GLViewImpl*>(glview)->getWindow(), 0);//Set windowshouldclose flag 0
        applicationShouldClose(); //App should close callback
        goto P1;
    }
    glview->release();

    ///////////////////////////////////////////////////////////////////////////
    /////////////// restoring timer resolution
    ///////////////////////////////////////////////////////////////////////////
    if (wTimerRes != 0)
    {
        timeEndPeriod(wTimerRes);
    }
    return 0;
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("NewProject_12", cocos2d::Rect(0, 0, hdResolutionSize.width, hdResolutionSize.height));
#else
        glview = GLViewImpl::create("NewProject_12");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(hdResolutionSize.width, hdResolutionSize.height, ResolutionPolicy::NO_BORDER);

    register_all_packages();

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    //auto scene = UIScene::createScene();
    //auto scene = TestScene8::createScene();
    //auto scene = TestScene9::createScene();
    //auto scene = TestScene10::createScene();
    //auto scene = TestScene11::createScene();
    //auto scene = TestScene12::createScene();
    auto scene = TestScene13::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}

void AppDelegate::applicationShouldClose()
{
    //CCLOG("Close button pressed");
    auto d = Director::getInstance();

    EventCustom event("close");
    d->getEventDispatcher()->dispatchEvent(&event);

    //Director::getInstance()->end();
}

int AppDelegate::displayConfirmSaveAsMessageBox()
{
    auto hnd = Director::getInstance()->getOpenGLView()->getWin32Window();
    //Display message box
    int msgboxID = MessageBox(hnd, L"Unsaved changes remain, save before exiting?", L"Confirm Action", MB_ICONEXCLAMATION | MB_YESNOCANCEL);

    return msgboxID;
}

int AppDelegate::displayHelpText()
{
    auto hnd = Director::getInstance()->getOpenGLView()->getWin32Window();
    auto msg = L"Press M to change Mode.\nPress Del to delete selected vertices.";

    int msgboxID = MessageBox(
        hnd,
        msg,
        L"Help",
        MB_ICONINFORMATION | MB_OK
    );

    return msgboxID;
}

// Local function
static void PVRFrameEnableControlWindow(bool bEnable)
{
    HKEY hKey = 0;

    // Open PVRFrame control key, if not exist create it.
    if (ERROR_SUCCESS != RegCreateKeyExW(HKEY_CURRENT_USER,
        L"Software\\Imagination Technologies\\PVRVFRame\\STARTUP\\",
        0,
        0,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        0,
        &hKey,
        nullptr))
    {
        return;
    }

    const WCHAR* wszValue = L"hide_gui";
    const WCHAR* wszNewData = (bEnable) ? L"NO" : L"YES";
    WCHAR wszOldData[256] = { 0 };
    DWORD   dwSize = sizeof(wszOldData);
    LSTATUS status = RegQueryValueExW(hKey, wszValue, 0, nullptr, (LPBYTE)wszOldData, &dwSize);
    if (ERROR_FILE_NOT_FOUND == status              // the key not exist
        || (ERROR_SUCCESS == status                 // or the hide_gui value is exist
            && 0 != wcscmp(wszNewData, wszOldData)))    // but new data and old data not equal
    {
        dwSize = sizeof(WCHAR) * (wcslen(wszNewData) + 1);
            RegSetValueEx(hKey, wszValue, 0, REG_SZ, (const BYTE*)wszNewData, dwSize);
    }

    RegCloseKey(hKey);
    }