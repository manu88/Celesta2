//
//  FontManager.hpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef FontManager_hpp
#define FontManager_hpp

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_CACHE_MANAGER_H 
//#include <ftcache.h>

struct Font
{
    
};
class FontManager
{
public:
    FontManager();
    ~FontManager();
    
    FT_Face contains(const std::string& font) const ;

private:
    
    static FT_Error face_Requester( FTC_FaceID  face_id, FT_Library  library, FT_Pointer  req_data, FT_Face*    aface );
    FT_Library lib;
    FTC_Manager ftcManager;
    
    
    
};

#endif /* FontManager_hpp */
