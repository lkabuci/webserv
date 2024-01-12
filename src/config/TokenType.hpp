#pragma once

#ifndef __TOKEN_TYPE_HPP__
#define __TOKEN_TYPE_HPP__

enum TokenType {
    SERVER,
    LOCATION,
    LISTEN,
    SERVER_NAME,
    ROOT,
    INDEX,
    CLIENT_MAX_BODY_SIZE,
    ERROR_PAGE,
    AUTOINDEX,
    RETURN,
    ALLOW_METHODS,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    PARAMETER,

    //  Separators
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_ANGLE,
    RIGHT_ANGLE,
    AT_SIGN,
    COMMA,
    COLON,
    BACK_SLASH,
    QUOTE,
    SLASH,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    QUESTION_MARK,
    EQUAL,
    CR_LF,
    SP,
    HT,
    CR_,
    TOKEN,
    CRLF_CRLF,

    QUOTED_STRING,
    QUOTED_PAIR,

    END
};

#endif
