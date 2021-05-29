  /*=======================================
  $FILE: $
  $DATE: $
  $REVISION: $
  $CREATOR: George Nagy $
  =========================================*/

#include <windows.h>

LRESULT CALLBACK
MainWindowCallback(HWND Window,
                   UINT Message,
                   WPARAM WParam,
                   LPARAM LParam)
{
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_SIZE:
        {
            OutputDebugStringA("WM_SIZE\n");
        } break;

        case WM_DESTROY:
        {
            OutputDebugStringA("WM_DESTROY\n");
        } break;

        case WM_CLOSE:
        {
            OutputDebugStringA("WM_CLOSE\n");
        } break;
        
        case WM_PAINT:
        {
          PAINTSTRUCT Paint;
          HDC DeviceContext = BeginPaint(Window, &Paint);
          int X = Paint.rcPaint.left;
          int Y = Paint.rcPaint.top;
          int Width = Paint.rcPaint.right - Paint.rcPaint.left;
          int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
          PatBlt(DeviceContext, X, Y, Width, Height, BLACKNESS);
          EndPaint(Window, &Paint);
        } break;

        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        } break;

        default:
        {
//          OutputDebugStringA("WM_DFEAULT\n");
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }

    return(Result);
}


int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR     Commandline,
        int       ShowCode)
{
    WNDCLASS WindowClass = {};


    // TODO: Check if HREDRAW/VREDRAW/OWNDC still matter
    WindowClass.style = CS_PARENTDC|CS_VREDRAW|CS_HREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
//  WindowClass.hIcon;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if(RegisterClass(&WindowClass))
    {
        HWND WindowHandle =
            CreateWindowEx(
                0,
                WindowClass.lpszClassName,
                "HandmadeHero",
                WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_SIZEBOX,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                Instance,
                0);

        if(WindowHandle)
        {
            MSG Message;
            for (;;)
            {
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if(MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            // TODO Logging
        }
    }
    else
    {
        // TODO Logging
    }

  return(0);
}