#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    ENDFILE
};



class Token
{
private:
    TokenType type;
    std::string description;
    int line;
    std::string tokenTypeToString(TokenType type);

public:
    Token(TokenType type, std::string description, int line);
    std::string toString();


};

#endif // TOKEN_H

