/*
 * Head
 * Copyright ~
 */

#ifndef CXX_LOG_H
#define CXX_LOG_H

/*---------------------------------------------------------------------------*/
// Include files

#include <string>

/*---------------------------------------------------------------------------*/
// Value define

static std::string _CutParenthesesNTail(std::string&& prettyFuncon)
{
    auto pos = prettyFuncon.find('(');
    if(pos!=std::string::npos)
        prettyFuncon.erase(prettyFuncon.begin()+pos, prettyFuncon.end());

    return std::move(prettyFuncon);
}
#define __STR_FUNCTION__ _CutParenthesesNTail(std::string(__PRETTY_FUNCTION__))

// means function name + parentheses (P = parentheses)
#define __STR_FUNCTIONP__ __STR_FUNCTION__+"()"

// means function name + parentheses + colon (C = colon)
#define __STR_FUNCTIONPC__ __STR_FUNCTION__+"(): "

// means the head of one piece of log.
#define LOG_HEAD __STR_FUNCTIONPC__

/*---------------------------------------------------------------------------*/
#endif // CXX_LOG_H
/* EOF */
