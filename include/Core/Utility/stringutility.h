/**
 * \file stringutility.h
 *
 * \brief Some useful functions for using strings
 */
#pragma once

#include <iostream>
#include <string>

#include "log.h"

namespace lu
{
    namespace core
    {

        namespace string
        {
            /**
             * \brief Find and replace some text in a string, returns an empty
             * string on failure
             *
             * @param source String to replace text in
             * @param toReplace String to find that should be replaced
             * @param replaceWith String that should replace toReplace
             */
            inline std::string replace(const std::string &source,
                                       const std::string &toReplace,
                                       const std::string &replaceWith)
            {
                std::string workable = source;
                unsigned int pos = workable.find(toReplace);

                // Failed to find any matches
                if (pos == workable.npos || pos > workable.size() ||
                    pos >= 4'294'967'295)
                {
                    lu::core::log(
                      LU_AT,
                      "Could not find match to replace. Replacement: \"" +
                        replaceWith + "\" To be replaced: \"" + toReplace +
                        "\"",
                      LOG_WARNING);
                    return std::string("");
                }

                workable =
                  workable.replace(pos, toReplace.length(), replaceWith);
                return workable;
            }
        }

    }
}