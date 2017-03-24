//
//  DisplayImpl.h
//  Broadway_core
//
//  Created by Manuel Deneu on 27/01/15.
//  Copyright (c) 2015 Manuel Deneu. All rights reserved.
//

#ifndef __Broadway_core__DisplayImpl__
#define __Broadway_core__DisplayImpl__

#include <iostream>
#include <vector>


#ifdef TARGET_RASPBERRY_PI
    #include <bcm_host.h>
    #include <EGL/egl.h>
#endif

#include "../../GX/GXGeometry.hpp"

#ifdef USE_OPENMAXIL

    #include "OMXCore.h"   // def COMXCore
    #include "linux/RBP.h" // def CRBP

#endif /* USE_OPENMAXIL */

/*
    Actual implementation of Display operations.

 On raspberry Pi, performed with bcm_host.
 
 
 */

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

typedef enum
{
    Display_Invalid = -1,
    Display_SD      = 0,
    Display_HD      = 1
    
} DisplayType ;

typedef enum
{
    HDMI_Interlaced    = 0,
    HDMI_NonInterlaced = 1
} DisplayHDMIMode;


/* Notification flag passed to displayChangeNotification()  */
typedef enum
{
    /* 
        For now, those are the same than defined for the raspberry PI in bcm_host
        ( vc_sdtv.h and vc_hdmi.h )
     */
    HDMI_UNPLUGGED           = (1 << 0), // <HDMI cable is detached
    HDMI_ATTACHED            = (1 << 1), // <HDMI cable is attached but not powered on
    HDMI_DVI                 = (1 << 2), // <HDMI is on but in DVI mode (no audio)
    HDMI_HDMI                = (1 << 3), // <HDMI is on and HDMI mode is active
    HDMI_HDCP_UNAUTH         = (1 << 4), // <HDCP authentication is broken (e.g. Ri mismatched) or not active
    HDMI_HDCP_AUTH           = (1 << 5), // <HDCP is active
    HDMI_HDCP_KEY_DOWNLOAD   = (1 << 6), // <HDCP key download successful/fail
    HDMI_HDCP_SRM_DOWNLOAD   = (1 << 7), // <HDCP revocation list download successful/fail
    HDMI_CHANGING_MODE       = (1 << 8), // <HDMI is starting to change mode, clock has not yet been set
    
    SDTV_UNPLUGGED           = 1 << 16, //  <SDTV cable unplugged, subject to platform support
    SDTV_ATTACHED            = 1 << 17, //  <SDTV cable is plugged in
    SDTV_NTSC                = 1 << 18, //  <SDTV is in NTSC mode
    SDTV_PAL                 = 1 << 19, //  <SDTV is in PAL mode
    SDTV_CP_INACTIVE         = 1 << 20, //  <Copy protection disabled
    SDTV_CP_ACTIVE           = 1 << 21, //   <Copy protection enabled
    
    DISPLAY_ACTIVE           = 1 << 30
    
} DisplayNotification;






/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

//! POD containing display informations. Use getAvailableVideoMode() and getCurrentDisplayInformations() to get infos from current display
struct DisplayInformations
{
    static inline DisplayInformations make( bool native ,
                                     DisplayType type ,
                                     GXSize resolution ,
                                     int framerate ,
                                     float aspectRatio,
                                     DisplayHDMIMode hdmimode)
    {
        return { native , type , resolution , framerate , aspectRatio , hdmimode };
    }
    
    bool        native;
    
    DisplayType type;
    GXSize      size;
    
    int         framerate;
    float       aspectRatio;
    
    DisplayHDMIMode hdmiMode;
    
    bool isValid() const
    {
        return type != Display_Invalid;
    }
    
    static inline DisplayInformations makeInvalid()
    {
        return DisplayInformations::make(false, Display_Invalid, makeSizeNULL(), 0, 0, HDMI_Interlaced );
        //{ false, Display_Invalid , makeSize( 0,0) , 0 , 0.0f  };
    }

};

typedef enum
{
    FrameRate  = 0,
    Resolution = 1,
    ScanMode   = 2,

} DisplaySettingsMatch;


/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

class DisplayImpl
{
public:
    DisplayImpl();
    ~DisplayImpl();
    
    static bool initPlatform();
    static bool deInitPlatform(); // does nothing

    static void initializeEGL();    
    
    bool initDisplay();
    bool deInitDisplay();
    
    
    void checkErrors();
    
    
    /* Query informations about current display */
    
    const DisplayInformations getCurrentDisplayInformations() const ;
    
    const std::vector< DisplayInformations > getAvailableVideoMode() const ;
    
    
    //! Return the AV latency (in ms) for HDMI (lipsync)
    /* Only valid if HDMI is currently powered on,
    * otherwise you get zero. The latency is defined as the relative delay
    * of the video stream to the audio stream
    */
    int getAudioVideoLatency() const;
    
    void update();
    
    /* Commands to send to the display */
    
    bool setVideoModeTo( const DisplayInformations &mode , DisplaySettingsMatch match);
    
    bool showInfosOnDisplay( bool show ) const;
    
    bool sendTvPowerOff() const;
    bool sendTvPowerOn() const;
    
    
    bool screenShot(const std::string &tofile) const;
    
private:  /* attributes */
    
    bool _displayInitOk;
    
    DisplayInformations _currentMode;
    

    
#ifdef HAVE_EGL
    
	EGLDisplay _EGLdisplay; // init() et updateContext()
	EGLSurface _surface;    // init() et updateContext()
    EGLContext _context;
    
#endif

#ifdef TARGET_RASPBERRY_PI    
    // RPI callback from bcm_host
    static void tvCallback(void *userdata, uint32_t reason, uint32_t param1, uint32_t param2);
    
    static float get_display_aspect_ratio(HDMI_ASPECT_T aspect);
    static float get_display_aspect_ratio(SDTV_ASPECT_T aspect);
    
    bool canSupportAudioFormat( EDID_AudioFormat audio_format,
                               uint32_t num_channels,
                               EDID_AudioSampleRate fs,
                               uint32_t bitrate);

    EGL_DISPMANX_WINDOW_T _nativewindow; // rpi
#endif
    
#ifdef USE_OPENMAXIL 
    
    static CRBP     s_RBP;
    static COMXCore s_OMX;
    
    
#endif
    
    static bool s_EGLInitialized;
    

};

#endif /* defined(__Broadway_core__DisplayImpl__) */
