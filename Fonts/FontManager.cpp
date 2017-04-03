//
//  FontManager.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "FontManager.hpp"
#include <iostream>
#include <GroundBase.hpp>
#include "StringOperations.hpp"

typedef struct
{
    const char*  file_path;
    int          face_index;
    
} MyFace;

FontManager::FontManager()
{
    int ret = FT_Init_FreeType(&lib);
    DEBUG_ASSERT(ret == 0);
    
    const FT_ULong maxBytes = 0;
    const FT_UInt maxFaces  = 0;
    const FT_UInt maxSizes  = 0;
    ret = FTC_Manager_New(lib, maxFaces, maxSizes, maxBytes, face_Requester, this, &ftcManager);
    DEBUG_ASSERT(ret == 0);

    
}
FontManager::~FontManager()
{
    FTC_Manager_Done(ftcManager);
    
    int ret = FT_Done_FreeType( lib );
    DEBUG_ASSERT(ret == 0);
    
    
    
    
}

FT_Face FontManager::contains(const std::string& font) const
{
    
    FT_Face face;
    MyFace *id =(MyFace *) malloc(sizeof(MyFace));
    
    id->file_path = font.c_str();

    
    FT_Error err = FTC_Manager_LookupFace(ftcManager, id, &face);
    //FT_Err_Ok
    
    if( err == FT_Err_Ok)
    {
        DEBUG_ASSERT(face);

        return face ;
    }
    else
    {
        printf("Error code %i \n" , err);
    }
    
    return NULL;
}

/*static*/ FT_Error FontManager::face_Requester( FTC_FaceID  face_id, FT_Library  library, FT_Pointer  req_data, FT_Face*    aface )
{
    FontManager* self = static_cast<FontManager*>(req_data);
    DEBUG_ASSERT(self);
    
    
    MyFace*  face = static_cast<MyFace*>( face_id);
    //printf("face_Requester for '%s' \n" , face->file_path);
    return FT_New_Face( library, face->file_path, face->face_index, aface );
}
