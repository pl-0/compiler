#pragma once
#include <string>
#include <unordered_map>
#include "RegularExpressionConverter.h"

using std::string;

enum class CodeTokenType {
    //keyword
    Program,            //program 0
    Const,
    Var,
    Procedure,
    Begin,
    End,
    If,
    Then,
    Else,
    While,
    Do,
    Call,
    Read,
    Write,
    Odd,
    True,
    False,

    Id,                 // identifier 17
    Integer,
    Float,

    //operator
    Not,                // !
    And,                // &&
    Or,                 // ||
    LT,					// <
    GT,					// >
    LE,					// <=
    GE,					// >=
    EQ,					// =
    NE,					// <>
    Assign,             // :=  29
    Add,				// +  
    Sub,				// -
    Mul,				// *
    Div,				// / 
    Mod,				// %
    OpenParenthesis,		// (  35
    CloseParenthesis,		// )
    Comma,				//,
    Semicolon,				//;  38

    WhiteSpace,
    LineBreaker,    // \n or \r\n
    Comment,			// -- xxxx
    Unknown,
    Eof,
};

struct CodeToken {
    CodeTokenType tokenType;
    string value;
    int rowIndex = -1;
    
    CodeToken() = default;
    CodeToken(CodeTokenType type, const string& str, int rowIndex = -1);
    CodeToken(CodeTokenType type, string&& str, int rowIndex = -1);
    CodeToken(CodeTokenType type, const char* str, int rowIndex = -1);
    CodeToken(const CodeToken&) = default;
    CodeToken& operator=(const CodeToken&) = default;
    CodeToken(CodeToken&& token) noexcept;
    CodeToken& operator=(CodeToken&& token) noexcept;
};

class TokenInfo {
public:
    NFAModel createNFA(RegularExpressionConverter& converter) const;

    TokenInfo(RegularExpression* re, CodeTokenType tokenType);

    CodeTokenType getCodeTokenType() const
    {
        return tokenType;
    }
private:
    unique_ptr<RegularExpression> regex;
    
    CodeTokenType tokenType;
};