/**
* \file stringutility.h
*
* \brief Some useful functions for using strings
*/
#pragma once

#include <string>
#include <iostream>

#include "log.h"

namespace ce { namespace core {

	namespace string
	{
		/**
		* \brief Find and replace some text in a string
		*
		* @param source String to replace text in
		* @param toReplace String to find that should be replaced
		* @param replaceWith String that should replace toReplace
		*/
		inline std::string replace(const std::string &source, const std::string &toReplace, const std::string &replaceWith)
		{
			std::string workable = source;
			unsigned int pos = workable.find(toReplace);

			// Failed to find any matches
			if (pos == workable.npos || pos > workable.size())
			{
				ce::core::log(CE_AT, "Could not find match to replace. Replacement: \"" + replaceWith + "\" To be replaced: \"" + toReplace + "\"", LOG_WARNING);
				return workable;
			}

			workable = workable.replace(pos, toReplace.length(), replaceWith);
			return workable;
		}
	}

}}