#ifdef WINDOWS_BUILD
#include <windows.h>
#include <memoryapi.h>

#include "/home/petermiller/Desktop/PongDay5-main/PongFromScratch-05_vulkan_renderer_cleanup/src/platform.h"

//#include "/home/petermiller/Desktop/PongDay5-main/PongFromScratch-05_vulkan_renderer_cleanup/src/renderer/vk_renderer.cpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*global_variable bool running = true;
global_variable HWND window;

LRESULT CALLBACK platform_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        running = false;
        break;
    }

    return DefWindowProcA(window, msg, wParam, lParam);
}

bool platform_create_window()
{
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASS wc = {};
    wc.lpfnWndProc = platform_window_callback;
    wc.hInstance = instance;
    wc.lpszClassName = "vulkan_engine_class";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        MessageBoxA(0, "Failed registering window class", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    window = CreateWindowExA(
        WS_EX_APPWINDOW,
        "vulkan_engine_class",
        "Pong",
        WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPED,
        100, 100, 1600, 720, 0, 0, instance, 0);

    if (window == 0)
    {
        MessageBoxA(0, "Failed creating window", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;
}

void platform_update_window(HWND window)
{
    MSG msg;

    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}
*/
int main()

{
   
   // VkContext vkcontext = {};
    xOrgWindInfo windInfo = {};
#ifdef WINDOWS_BUILD
    if (!platform_create_window())
    {
        return -1;
    }
    #else
    initXWindow(&windInfo);
    
    #endif

  //  if (!vk_init(&vkcontext, (xcb_window_t *)windInfo.window))
    //{
      //  return -1;
    //}
#ifdef WINDOWS_BUILD
    while (running)
    #else
    windInfo.running = true;
    while (windInfo.running)
    #endif
    {
        #ifdef WINDOWS_BUILD
        platform_update_window(window);
        #else
         XWindowMainLoop(&windInfo);
        #endif
       /* if (!vk_render(&vkcontext))
        {
            return -1;
        }
        */
    }

    return 0;
}
/*
// ########################################################################
//                   Implementation of exposed platform functions
// ########################################################################

void platform_get_window_size(uint32_t *width, uint32_t *heigth)
{
    RECT rect;
    GetClientRect(window, &rect);

    *width = rect.right - rect.left;
    *heigth = rect.bottom - rect.top;
}

char *platform_read_file(char *path, uint32_t *length)
{ char *result = 0;

    // This opens the file
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

    if (file != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER size;
        if (GetFileSizeEx(file, &size))
        {
            *length = size.QuadPart;
            //TODO: Suballocte from main allocation
            //result = new char[*length];
            result = (char *)malloc(*length);
           // result = (char *)VirtualAlloc(0, size.QuadPart, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
            DWORD bytesRead;
            if (ReadFile(file, result, *length, &bytesRead, 0) &&
                bytesRead == *length)
            {
                // TODO: What to do here?
                // Success
            }
            else
            {
                //TODO: Assert and error checking
                printf( "Failed to read file" );
            }
        }
        else
        {
            //TODO: Assert and error checking
            printf( "Failed to get file size");
        }
    }
    else
    {
        // TODO: Asserts, get error code
        printf( "Failed to open the file" );
    }
//VirtualFree(file, 0, MEM_RELEASE);
    return result;
}
*/
#endif