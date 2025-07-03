#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Core/Utility/log.h"

namespace lu
{
    namespace graphics
    {

        extern FT_Library ftLib; /**< Freetype library */

        inline const char *FT_getErrorMessage(FT_Error err)
        {
#undef __FTERRORS_H__
#define FT_ERRORDEF(e, v, s)                                                   \
    case e:                                                                    \
        return s;
#define FT_ERROR_START_LIST                                                    \
    switch (err)                                                               \
    {
#define FT_ERROR_END_LIST }
#include FT_ERRORS_H
            return "(Unknown error)";
        }

        inline bool initText()
        {
            FT_Error err = FT_Init_FreeType(&ftLib);
            if (err)
            {
                lu::core::log(
                  "Failed to initialize FreeType library, FT error: " +
                    std::string(FT_getErrorMessage(err)),
                  lu::core::LOG_ERROR);
                return false;
            }
            return true;
        }

    }
}