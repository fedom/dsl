#include "parser.h"
#include "my_except.h"

Parser::Parser(Lexer *lexer, int k) : lexer_(lexer), size_(k), i_(0) {
	
	
	if (size_ <= 0) 
		size_ = 1;

	ct_ = new Token[size_];

	for (int i = 0; i < size_; i++) {
		ct_[i] = lexer_->GetNextToken();
	}
}

Parser::~Parser() {
	delete []ct_;
}


void Parser::Match(int token_type) {

	if (token_type == ct_[i_].type) {
		ct_[i_] = lexer_->GetNextToken();	
		i_ = (i_ + 1) % size_;
	} else {
		throw ParserUnwantedTokenException((ct_[i_].name + "given, expect " + lexer_->GetTokenName(token_type)).c_str(), __FILE__, __LINE__);
	}	
}

Token Parser::LA(int i) {
	// range is [1, size_]
	if (i > size_ || i <= 0) 
		throw LookAheadStepBeyondCapacity("", __FILE__, __LINE__);
		
	return ct_[(i_ - 1 + i) % size_];
}

int Parser::LT(int i) {
	return LA(i).type;
}
