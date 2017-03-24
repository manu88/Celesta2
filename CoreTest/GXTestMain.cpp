//
//  GXTestMain.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "GXElement.hpp"
#include "GXRenderer.hpp"
#include "GXPath.hpp"


#include <bcm_host.h>
#include <VG/openvg.h>
#include <VG/vgu.h>
#include <EGL/egl.h>

static float rotateN = 0.0f;
const float                     aspectRatio = 612.0f / 792.0f;
int                                     renderWidth = 0;
int                                     renderHeight = 0;
EGLDisplay                      egldisplay;
EGLConfig                       eglconfig;
EGLSurface                      eglsurface;
EGLContext                      eglcontext;

void render(int w, int h)
{

        if(renderWidth != w || renderHeight != h)
        {
                float clearColor[4] = {1,1,1,1};

                eglSwapBuffers(egldisplay, eglsurface); //force EGL to recognize resize

                vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
                vgClear(0, 0, w, h);

                vgLoadIdentity();
               
                renderWidth = w;
                renderHeight = h;
                 }
        eglSwapBuffers(egldisplay, eglsurface);
        assert(eglGetError() == EGL_SUCCESS);
}

void init(NativeWindowType window)
{
        static const EGLint s_configAttribs[] =
        {
                EGL_RED_SIZE,           8,
                EGL_GREEN_SIZE,         8,
                EGL_BLUE_SIZE,          8,
                EGL_ALPHA_SIZE,         8,
                EGL_LUMINANCE_SIZE, EGL_DONT_CARE,                      //EGL_DONT_CARE
                EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
                EGL_SAMPLES,            1,
                EGL_NONE
        };
        EGLint numconfigs;

        egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(egldisplay, NULL, NULL);
        assert(eglGetError() == EGL_SUCCESS);
        eglBindAPI(EGL_OPENVG_API);

        eglChooseConfig(egldisplay, s_configAttribs, &eglconfig, 1, &numconfigs);
        assert(eglGetError() == EGL_SUCCESS);
        assert(numconfigs == 1);

        eglsurface = eglCreateWindowSurface(egldisplay, eglconfig, window, NULL);
        assert(eglGetError() == EGL_SUCCESS);
        eglcontext = eglCreateContext(egldisplay, eglconfig, NULL, NULL);
        assert(eglGetError() == EGL_SUCCESS);
        eglMakeCurrent(egldisplay, eglsurface, eglsurface, eglcontext);
        assert(eglGetError() == EGL_SUCCESS);

}

void deinit(void)
{
        eglMakeCurrent(egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        assert(eglGetError() == EGL_SUCCESS);
        eglTerminate(egldisplay);
        assert(eglGetError() == EGL_SUCCESS);
        eglReleaseThread();
}

int test(void)
{
   uint32_t width, height;
   bcm_host_init();
   int s;

   static EGL_DISPMANX_WINDOW_T nativewindow;   
   DISPMANX_ELEMENT_HANDLE_T dispman_element;
   DISPMANX_DISPLAY_HANDLE_T dispman_display;
   DISPMANX_UPDATE_HANDLE_T dispman_update;
   VC_RECT_T dst_rect;
   VC_RECT_T src_rect;

   s = graphics_get_display_size(0 /* LCD */, &width, &height);
   assert( s >= 0 );

   dst_rect.x = 0;
   dst_rect.y = 0;
   dst_rect.width = width;
   dst_rect.height = height;
      
   src_rect.x = 0;
   src_rect.y = 0;
   src_rect.width = width << 16;
   src_rect.height = height << 16;        

   dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
   dispman_update = vc_dispmanx_update_start( 0 );
         
   dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
      1/*layer*/, &dst_rect, 0/*src*/,
      &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, (DISPMANX_TRANSFORM_T)0/*transform*/);
      
   nativewindow.element = dispman_element;
   nativewindow.width = width;
   nativewindow.height = height;
   vc_dispmanx_update_submit_sync( dispman_update );

   init(&nativewindow);

   while (1) {
      render(width, height);
      rotateN += 1.0f;
   }
   deinit();

   return 0;
}

int main(int argc, const char * argv[])
{
    GXElement mainElement;
    
    const GXRect b = makeRect(0, 0, 1920, 1080);
    mainElement.setBounds( b );
    assert(mainElement.getBounds() == b);
    
    GXElement child1;
    child1.setBounds(  makeRect(100, 50, 200, 100) );
    child1.setZPos(1);
    GXElement child2;
    child2.setBounds(  makeRect(140, 80, 200, 100) );
    child2.setZPos(0);
 
    mainElement.addChild(&child1);
    mainElement.addChild(&child2);
    
    GXRenderer renderer;
    renderer.setDisplayedElement(&mainElement);
    renderer.setBounds(  makeRect(0, 0, 1920, 1080) );
    renderer.update();

/**/

uint32_t width, height;
   bcm_host_init();
   int s;

   static EGL_DISPMANX_WINDOW_T nativewindow;

   DISPMANX_ELEMENT_HANDLE_T dispman_element;
   DISPMANX_DISPLAY_HANDLE_T dispman_display;
   DISPMANX_UPDATE_HANDLE_T dispman_update;
   VC_RECT_T dst_rect;
   VC_RECT_T src_rect;

   s = graphics_get_display_size(0 /* LCD */, &width, &height);
   assert( s >= 0 );

   dst_rect.x = 0;
   dst_rect.y = 0;
   dst_rect.width = width;
   dst_rect.height = height;
      
   src_rect.x = 0;
   src_rect.y = 0;
   src_rect.width = width << 16;
   src_rect.height = height << 16;        

   dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
   dispman_update = vc_dispmanx_update_start( 0 );
         
   dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
      1/*layer*/, &dst_rect, 0/*src*/,
      &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, (DISPMANX_TRANSFORM_T)0/*transform*/);
      
   nativewindow.element = dispman_element;
   nativewindow.width = width;
   nativewindow.height = height;
   vc_dispmanx_update_submit_sync( dispman_update );



    GXPath path(makeRect(140, 80, 200, 100));
    path.addRect(path.getBoundingRect());
    path.setFillColor( makeColor(255, 0, 0) );
    path.fill();


   init(&nativewindow);

   while (1) 
   {
      render(width, height);
      rotateN += 1.0f;
   }
   deinit();

    return 0;
}
