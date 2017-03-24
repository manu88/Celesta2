//
//  DisplayImpl.cpp
//  Broadway_core
//
//  Created by Manuel Deneu on 27/01/15.
//  Copyright (c) 2015 Manuel Deneu. All rights reserved.
//

#include <assert.h>

#ifdef TARGET_RASPBERRY_PI
    #include <bcm_host.h>
#endif

#include "shapes.h"
#include "DisplayImpl.hpp"
#include "../../GX/GXDefs.hpp"



bool DisplayImpl::s_EGLInitialized = false;

#ifdef USE_OPENMAXIL

CRBP     DisplayImpl::s_RBP = CRBP();
COMXCore DisplayImpl::s_OMX = COMXCore();

#endif

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

DisplayImpl::DisplayImpl() :

_displayInitOk ( false ),
_currentMode   ( DisplayInformations::makeInvalid() )
{
#ifdef TARGET_RASPBERRY_PI
    vc_tv_register_callback( tvCallback, this);
#endif
    
    
}

DisplayImpl::~DisplayImpl()
{
    
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool DisplayImpl::initDisplay()
{
#ifdef TARGET_RASPBERRY_PI

int width = 0;
int  height = 0;
init(&width, &height); 
#endif    
    return true;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool DisplayImpl::deInitDisplay()
{
#ifdef TARGET_RASPBERRY_PI
    
    eglDestroyContext(_EGLdisplay , _context );
    
#endif /*TARGET_RASPBERRY_PI*/
    
    return true;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

const DisplayInformations DisplayImpl::getCurrentDisplayInformations() const
{
#ifdef TARGET_RASPBERRY_PI
    
    TV_DISPLAY_STATE_T currentState = {0,0};
    
    if (vc_tv_get_display_state( &currentState) == 0)
    {
        DisplayType type = Display_Invalid;
        
        GXSize size = makeSizeNULL();
        
        int frate;
        float aspectRatio;
        DisplayHDMIMode hdmiMode = HDMI_Interlaced;
        
        
        // HD or DVI
        if (currentState.state  & ( VC_HDMI_HDMI | VC_HDMI_DVI ) )
        {
            type = Display_HD;
            
            HDMI_DISPLAY_STATE_T desc= ( HDMI_DISPLAY_STATE_T ) currentState.display.hdmi;
            
            size.width  = desc.width;
            size.height = desc.height;
            
            frate = desc.frame_rate;
            
            aspectRatio = get_display_aspect_ratio( (HDMI_ASPECT_T) currentState.display.hdmi.aspect_ratio);
        }
        
        // SD
        else
        {
            type = Display_SD;
            
            SDTV_DISPLAY_STATE_T desc= ( SDTV_DISPLAY_STATE_T ) currentState.display.sdtv;
            
            size.width  = desc.width;
            size.height = desc.height;
            
            frate = desc.frame_rate;
            
            aspectRatio = get_display_aspect_ratio( (SDTV_ASPECT_T) currentState.display.sdtv.display_options.aspect);
        }
        
        aspectRatio *= (float) currentState.display.hdmi.height / (float) currentState.display.hdmi.width;
        
        return DisplayInformations::make( false , type , size , frate , aspectRatio , hdmiMode);
        //{ false, type , size , frate , aspectRatio  };
    }
#elif defined __APPLE__
    
    return DisplayInformations::make(false, Display_HD, makeSize(1920, 1080), 0, 0, HDMI_Interlaced );
#endif
    
    return DisplayInformations::makeInvalid();// { false, Display_Invalid , makeSize( 0,0) , 0 , 0  };
    
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::vector< DisplayInformations > DisplayImpl::getAvailableVideoMode() const
{
    std::vector<DisplayInformations> ret;
    
#ifdef TARGET_RASPBERRY_PI
    
    /*
     HDMI_RES_GROUP_T ->
     HDMI_RES_GROUP_INVALID = 0, //< Initialised value
    HDMI_RES_GROUP_CEA = 1, //< CEA - HDMI device
    HDMI_RES_GROUP_DMT = 2, //< DMT - computer monitors
     */
    
    const int maxSize = 20;
    
    TV_SUPPORTED_MODE_NEW_T list[maxSize];
    
    int count = vc_tv_hdmi_get_supported_modes_new(/*HDMI_RES_GROUP_T*/ HDMI_RES_GROUP_CEA , list , maxSize , NULL , NULL  );
    

    
    /*
     TV_SUPPORTED_MODE_NEW_T:
     uint32_t scan_mode : 1; //<1 is interlaced, 0 for progressive
    uint32_t native : 1; /: <1 means native mode, 0 otherwise
    uint32_t group : 3; // <group
    uint32_t code : 7; // <mode code
    uint32_t pixel_rep : 3; // <pixel repetition (zero means no repetition)
    uint32_t aspect_ratio : 5; // <aspect ratio of the format
    uint16_t frame_rate; // <frame rate
    uint16_t width; // <frame width
    uint16_t height; // <frame height
    uint32_t pixel_freq; // <pixel clock in Hz
    uint32_t struct_3d_mask;// <3D structure supported for this mode, only valid if group == CEA. This is a bitmask of HDMI_3D_STRUCT_T

     */
    
    for (int i = 0 ; i<count ; i++)
    {
        ret.push_back( DisplayInformations::make(  (bool) list[i].native ,
                                                   Display_HD,
                                                   makeSize( list[i].width, list[i].height),
                                                   list[i].frame_rate,
                                                   get_display_aspect_ratio( (HDMI_ASPECT_T) list[i].aspect_ratio ),
                                                   list[i].scan_mode == 1? HDMI_Interlaced : HDMI_NonInterlaced
                                                 
                      ));
    }
    
    assert( count == (int) ret.size() );
    
#elif defined __APPLE__
    
    ret.push_back( DisplayInformations::make(true, Display_SD, makeSize( 640 , 800), 30, 1, HDMI_Interlaced) );
    ret.push_back( DisplayInformations::make(true, Display_HD, makeSize( 1920 , 1080), 30, 3, HDMI_Interlaced) );

    
#endif

    return ret;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

int DisplayImpl::getAudioVideoLatency() const
{
    int ret = 0;
    
#ifdef TARGET_RASPBERRY_PI
    ret = vc_tv_hdmi_get_av_latency();
#endif
    
    
    return ret;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

void DisplayImpl::update()
{

    /*
     typedef enum {
     VG_NO_ERROR                                 = 0,
     VG_BAD_HANDLE_ERROR                         = 0x1000,
     VG_ILLEGAL_ARGUMENT_ERROR                   = 0x1001,
     VG_OUT_OF_MEMORY_ERROR                      = 0x1002,
     VG_PATH_CAPABILITY_ERROR                    = 0x1003,
     VG_UNSUPPORTED_IMAGE_FORMAT_ERROR           = 0x1004,
     VG_UNSUPPORTED_PATH_FORMAT_ERROR            = 0x1005,
     VG_IMAGE_IN_USE_ERROR                       = 0x1006,
     VG_NO_CONTEXT_ERROR                         = 0x1007
     } VGErrorCode;*/

#ifdef HAVE_EGL
    VGErrorCode ret = vgGetError();
    
    /*
    if (ret !=  VG_NO_ERROR)
    {
        if (ret == VG_BAD_HANDLE_ERROR )
            printf("VG_BAD_HANDLE_ERROR");
        
        else if (ret == VG_ILLEGAL_ARGUMENT_ERROR )
            printf("VG_ILLEGAL_ARGUMENT_ERROR");
        
        else if (ret == VG_OUT_OF_MEMORY_ERROR )
            printf("VG_OUT_OF_MEMORY_ERROR");
        
        else if (ret ==VG_PATH_CAPABILITY_ERROR  )
            printf("VG_PATH_CAPABILITY_ERROR");
        
        else if (ret == VG_UNSUPPORTED_IMAGE_FORMAT_ERROR  )
            printf("VG_UNSUPPORTED_IMAGE_FORMAT_ERROR");
        
        else if (ret == VG_UNSUPPORTED_PATH_FORMAT_ERROR  )
            printf("VG_UNSUPPORTED_PATH_FORMAT_ERROR");
        
        else if (ret == VG_IMAGE_IN_USE_ERROR  )
            printf("VG_IMAGE_IN_USE_ERROR");
        
        else if (ret == VG_NO_CONTEXT_ERROR  )
            printf("VG_NO_CONTEXT_ERROR");

        
    }
     */

    
	eglSwapBuffers( _EGLdisplay, _surface);

	assert( eglGetError() == EGL_SUCCESS);
#endif
}

void DisplayImpl::checkErrors()
{
#ifdef TARGET_RASPBERRY_PI
    VGErrorCode ret = vgGetError();
    

        switch (ret)
    {
            case VG_BAD_HANDLE_ERROR:
                printf("\nVG_BAD_HANDLE_ERROR");
                break;
            case VG_ILLEGAL_ARGUMENT_ERROR:
                printf("\nVG_ILLEGAL_ARGUMENT_ERROR");
                break;
            case VG_OUT_OF_MEMORY_ERROR:
                printf("\nVG_OUT_OF_MEMORY_ERROR");
                break;
            case VG_PATH_CAPABILITY_ERROR:
                printf("\nVG_PATH_CAPABILITY_ERROR");
                break;
            case VG_UNSUPPORTED_IMAGE_FORMAT_ERROR:
                printf("\nVG_UNSUPPORTED_IMAGE_FORMAT_ERROR");
                break;
            case VG_UNSUPPORTED_PATH_FORMAT_ERROR:
                printf("\nVG_UNSUPPORTED_PATH_FORMAT_ERROR");
                break;
            case VG_IMAGE_IN_USE_ERROR:
                printf("\nVG_IMAGE_IN_USE_ERROR");
                break;
            case VG_NO_CONTEXT_ERROR:
                printf("\nVG_NO_CONTEXT_ERROR");
                break;
        
            case VG_NO_ERROR:
                //printf("\n NO ERRORS ");
                break;
        
            default:
                printf("\nUNKNOWN_ERROR");
        }


    
    
   // assert( ret == VG_NO_ERROR );
#endif
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool DisplayImpl::setVideoModeTo( const DisplayInformations &mode , DisplaySettingsMatch match)
{
    bool ret = false;
    
#ifdef TARGET_RASPBERRY_PI
    
    /* HDMI_INTERLACED_T =  HDMI_NONINTERLACED / HDMI_INTERLACED */
    
    /* EDID_MODE_MATCH_FLAG_T  = HDMI_MODE_MATCH_FRAMERATE HDMI_MODE_MATCH_RESOLUTION HDMI_MODE_MATCH_SCANMODE*/
    
    ret =  vc_tv_hdmi_power_on_best( mode.size.width  ,
                                     mode.size.height ,
                                     mode.framerate ,
                                     HDMI_INTERLACED ,
                                     HDMI_MODE_MATCH_RESOLUTION
                                    ) == 0 ;
#endif
    
    return ret;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool DisplayImpl::showInfosOnDisplay( bool show ) const
{
    return vc_tv_show_info( (uint32_t) show) == 0;
    
}

bool DisplayImpl::sendTvPowerOff() const
{
    bool ret = false;
    
#ifdef TARGET_RASPBERRY_PI
    ret = (bool) vc_tv_power_off();
#endif
    
    return ret;
}

bool DisplayImpl::sendTvPowerOn() const
{
    bool ret = false;

#ifdef TARGET_RASPBERRY_PI
    ret = vc_tv_hdmi_power_on_preferred() == 0;
    
#endif
    return ret;
}



bool DisplayImpl::screenShot(const std::string &tofile) const
{
    if( !getCurrentDisplayInformations().isValid())
        return false;

    bool ret = false;
#ifdef TARGET_RASPBERRY_PI
    
    const GXSize res = getCurrentDisplayInformations().size;

    FILE *fp = fopen( tofile.c_str() , "wb");
    
    if( fp == NULL)
        return false;

    void *ScreenBuffer = malloc( res.width * res.height * 4);
    
    vgReadPixels(ScreenBuffer, ( res.width * 4), VG_sABGR_8888, 0, 0, res.width, res.height );
    
    fwrite(ScreenBuffer, 1, res.width * res.height * 4, fp);
    
    free(ScreenBuffer);
    fclose(fp);
#endif
    
    return ret;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    
    Init Part
 
 */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool DisplayImpl::initPlatform()
{
    bool ret = false;
    
#ifdef USE_OPENMAXIL
    if( s_RBP.Initialize() )
    {
        if( s_OMX.Initialize() )
            ret = true;
        else
            Log::log("COMXCore init failed");
    }
    else
        Log::log("CRBP init failed");
#endif
    
    initializeEGL();

    
    
    return ret && s_EGLInitialized;
}

bool DisplayImpl::deInitPlatform()
{
    
    return true;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

/*static*/ void DisplayImpl::initializeEGL()
{
    if ( !s_EGLInitialized )
    {
#ifdef HAVE_EGL
        
        // bind OpenVG API
        EGLBoolean ret = eglBindAPI(EGL_OPENVG_API);
        assert(ret != EGL_FALSE);
#endif
        s_EGLInitialized = true;
    }

}


/* **** **** **** **** **** **** **** **** **** **** **** **** **** */
/*
 
    RaspberryPI ( bcmhost ) methods
 
 */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** */

#ifdef TARGET_RASPBERRY_PI
/*static*/ void DisplayImpl::tvCallback(void *userdata, uint32_t reason, uint32_t param1, uint32_t param2)
{
    DisplayImpl *self = static_cast< DisplayImpl*>( userdata );
    
    assert( self );
    
    /*
     Reason HDMI :
     VC_HDMI_UNPLUGGED = (1 << 0), //<HDMI cable is detached
     VC_HDMI_ATTACHED = (1 << 1), // <HDMI cable is attached but not powered on
     VC_HDMI_DVI = (1 << 2), // <HDMI is on but in DVI mode (no audio)
     VC_HDMI_HDMI = (1 << 3), // <HDMI is on and HDMI mode is active
     VC_HDMI_HDCP_UNAUTH = (1 << 4), //<HDCP authentication is broken (e.g. Ri mismatched) or not active
     VC_HDMI_HDCP_AUTH = (1 << 5), // <HDCP is active
     VC_HDMI_HDCP_KEY_DOWNLOAD = (1 << 6), // <HDCP key download successful/fail
     VC_HDMI_HDCP_SRM_DOWNLOAD = (1 << 7), //<HDCP revocation list download successful/fail
     VC_HDMI_CHANGING_MODE  = (1 << 8), //<HDMI is starting to change mode, clock has not yet been set
     
     SD:
     VC_SDTV_UNPLUGGED = 1 << 16, //<SDTV cable unplugged, subject to platform support
     VC_SDTV_ATTACHED = 1 << 17, //<SDTV cable is plugged in
     VC_SDTV_NTSC = 1 << 18, //<SDTV is in NTSC mode
     VC_SDTV_PAL = 1 << 19, //<SDTV is in PAL mode
     VC_SDTV_CP_INACTIVE = 1 << 20, //<Copy protection disabled
     VC_SDTV_CP_ACTIVE = 1 << 21 //<Copy protection enabled
     
     */
    
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** *****/

/*static*/ float DisplayImpl::get_display_aspect_ratio(HDMI_ASPECT_T aspect)
{
    float display_aspect;
    
    switch (aspect)
    {
        case HDMI_ASPECT_4_3:   display_aspect = 4.0/3.0;   break;
        case HDMI_ASPECT_14_9:  display_aspect = 14.0/9.0;  break;
        case HDMI_ASPECT_16_9:  display_aspect = 16.0/9.0;  break;
        case HDMI_ASPECT_5_4:   display_aspect = 5.0/4.0;   break;
        case HDMI_ASPECT_16_10: display_aspect = 16.0/10.0; break;
        case HDMI_ASPECT_15_9:  display_aspect = 15.0/9.0;  break;
        case HDMI_ASPECT_64_27: display_aspect = 64.0/27.0; break;
        default:                display_aspect = 16.0/9.0;  break;
    }
    
    return display_aspect;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** *****/
/*static*/ float DisplayImpl::get_display_aspect_ratio(SDTV_ASPECT_T aspect)
{
    float display_aspect;
    
    switch (aspect)
    {
        case SDTV_ASPECT_4_3:  display_aspect = 4.0/3.0;  break;
        case SDTV_ASPECT_14_9: display_aspect = 14.0/9.0; break;
        case SDTV_ASPECT_16_9: display_aspect = 16.0/9.0; break;
        default:               display_aspect = 4.0/3.0;  break;
    }
    
    
    return display_aspect;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** *****/

bool DisplayImpl::canSupportAudioFormat(EDID_AudioFormat audio_format,
                                              uint32_t num_channels,
                                              EDID_AudioSampleRate fs,
                                              uint32_t bitrate)
{
    return vc_tv_hdmi_audio_supported(audio_format, num_channels, fs, bitrate ) == 0;
}
#endif /*TARGET_RASPBERRY_PI*/



