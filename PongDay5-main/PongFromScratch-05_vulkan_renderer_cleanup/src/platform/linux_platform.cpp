#include <xcb/xcb.h>
//#include <X11/keysym.h>
#include <X11/XKBlib.h>  // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/petermiller/Desktop/PongDay5-main/PongFromScratch-05_vulkan_renderer_cleanup/src/renderer/vk_renderer.cpp"







void initXWindow(xOrgWindInfo * winInfo){

int screenp = 0;
 winInfo->connection = xcb_connect(NULL, &screenp);
if (xcb_connection_has_error( winInfo->connection))
  printf("Failed to connect to X server using XCB.");

  xcb_screen_iterator_t iter =
    xcb_setup_roots_iterator(xcb_get_setup( winInfo->connection));

for (int s = screenp; s > 0; s--)
    xcb_screen_next(&iter);
     winInfo->screen = iter.data;
     winInfo->window = xcb_generate_id( winInfo->connection);
    uint32_t eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t valueList[] = {  winInfo->screen->black_pixel, 0 };
    xcb_create_window(  winInfo->connection, XCB_COPY_FROM_PARENT,  winInfo->window,  winInfo->screen->root, 0, 0, 
     winInfo->WINDOW_HEIGHT,  winInfo->WINDOW_WIDTH, 0,
  XCB_WINDOW_CLASS_INPUT_OUTPUT,  winInfo->screen->root_visual, eventMask, valueList);
const char * applicationName = "Hlll";
  xcb_change_property(
   winInfo->connection,
  XCB_PROP_MODE_REPLACE,
   winInfo->window,
  XCB_ATOM_WM_NAME,
  XCB_ATOM_STRING,
  8,
  strlen(applicationName),
  applicationName);
  
xcb_map_window( winInfo->connection,  winInfo->window);
xcb_flush( winInfo->connection);
xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
     winInfo->connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
    
xcb_intern_atom_cookie_t wmProtocolsCookie =
    xcb_intern_atom( winInfo->connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
xcb_intern_atom_reply_t *wmDeleteReply =
    xcb_intern_atom_reply( winInfo->connection, wmDeleteCookie, NULL);
xcb_intern_atom_reply_t *wmProtocolsReply =
    xcb_intern_atom_reply( winInfo->connection, wmProtocolsCookie, NULL);
 winInfo->wmDeleteWin = wmDeleteReply->atom;

 winInfo->wmProtocols = wmProtocolsReply->atom;

xcb_change_property( winInfo->connection, XCB_PROP_MODE_REPLACE,  winInfo->window,
                    wmProtocolsReply->atom, 4, 32, 1, &wmDeleteReply->atom);
                     xcb_map_window( winInfo->connection,  winInfo->window);
  xcb_flush( winInfo->connection);

};

void XWindowMainLoop(xOrgWindInfo * winInfo){
  
  winInfo->running = true;
  xcb_generic_event_t *event;
  xcb_client_message_event_t *cm;

  while (winInfo->running) {
    event = xcb_wait_for_event( winInfo->connection);

    switch (event->response_type & ~0x80) {
      case XCB_CLIENT_MESSAGE: {
        cm = (xcb_client_message_event_t *)event;

        if (cm->data.data32[0] ==  winInfo->wmDeleteWin)
           
          winInfo->running = false;
          

        break;
      }
    }

    free(event);
  }

  
 xcb_destroy_window( winInfo->connection,  winInfo->window);};

 int main()

{
   
    VkContext vkcontext = {};
    xOrgWindInfo windInfo = {};

    initXWindow(&windInfo);
    
    

    if (!vk_init(&vkcontext, &windInfo))
    {
        return -1;
    }

    windInfo.running = true;
    while (windInfo.running)
  
    {
       
         XWindowMainLoop(&windInfo);
        
        if (!vk_render(&vkcontext))
        {
            return -1;
        }
        
    }

    return 0;
}

