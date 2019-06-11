#ifndef __LEXER_H__
#define __LEXER_H__
#include <string>

#define CHAR_EOF			0

#define TOKEN_EOF			0
#define TOKEN_INVALID		1


struct Token {
	Token() {}
	Token(int _type, const std::string &_name) : type(_type), name(_name) {}

	int type;
	std::string name;
};


class Lexer {
public:
	Lexer(const char *s);
	virtual ~Lexer();

	virtual Token GetNextToken() = 0;
	virtual const char *GetTokenName(int token_type) = 0;
	
protected:

	void Consume();
	void WS();
	bool IsLetter(char ch) const;
	bool IsDigit(char ch) const;
	bool IsWhiteSpace(char ch) const;

	std::string s_;
	int index_;
	char c_;
};
#endif//__LEXER_H__
