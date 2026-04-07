#pragma once

enum class TokenType{
    None = 'n',

    LBrace = '{',
    RBrace = '}',
    LBracket = '[',
    RBracket = ']' ,
    Comma = ',',
    Colon = ':',

    Int = 'i',
    Float = 'f',
    String = 's',
    Bool = 'b',

    Eof = '\0'
};

struct Token{
    TokenType type;
    std::string_view lexeme;

    Token(TokenType type,std::string_view lexeme):type(type),lexeme(lexeme){}

};