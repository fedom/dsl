#include "parser.h"
#include "my_except.h"

Parser::Parser(Lexer *lexer) : lexer_(lexer), i_(0) {
}

Parser::~Parser() {
}


void Parser::Match(int token_type) {

	if (token_type == LA(1).type) {
		Consume();
	} else {
		throw ParserUnwantedTokenException((lookahead_tokens_[i_].name + "given, expect " + lexer_->GetTokenName(token_type)).c_str(), __FILE__, __LINE__);
	}	
}

Token Parser::LA(int i) {
	Sync(i);
	return lookahead_tokens_[i_ + i - 1];
}

int Parser::LT(int i) {
	return LA(i).type;
}

void Parser::MarkBase() {
	base_i_.push(i_);
}

void Parser::RestoreBase() {
	i_ = base_i_.top();
	base_i_.pop();
}

void Parser::Sync(int i) {
	int need_num = i_ + i - lookahead_tokens_.size();

	for (int j = 0; j < need_num; j++) {
		lookahead_tokens_.push_back(lexer_->GetNextToken());
	}
}

void Parser::Consume() {
	i_++;
	if (i_ == lookahead_tokens_.size() && !IsSpeculating()) {
		i_ = 0;	
		lookahead_tokens_.clear();	
	}

	Sync(1);
}

bool Parser::IsSpeculating() {
	return !base_i_.empty();
}


int Parser::CurPos() {
	return i_;
}
void Parser::SetPos(int i) {
	i_ = i;
}
