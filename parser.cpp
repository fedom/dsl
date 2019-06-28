#include "parser.h"
#include "my_except.h"
#include <cassert>

Parser::Parser(Lexer *lexer) : lexer_(lexer), i_(0) {
	root_ = new TreeNode("root");
	current_node_ = root_;
}

Parser::~Parser() {
	delete root_;
}


void Parser::Match(int token_type) {

	UPDATE_CURRENT_NODE(("\"" + LA(1).name + "\"").c_str());
	if (token_type == LA(1).type) {
		Consume();
	} else {
		throw ParserUnwantedTokenException((lookahead_tokens_[i_].name + "given, expect " + lexer_->GetTokenName(token_type)).c_str(), __FILE__, __LINE__);
	}	
	RESTORE_CURRENT_NODE();
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


TreeNode *Parser::LinkNewNode(const char *node_name) {
	assert(current_node_ != nullptr);

	TreeNode *new_node = new TreeNode(node_name);
	current_node_->AddChild(new_node);

	TreeNode *old_current = current_node_;
	current_node_ = new_node;

	return old_current;
}

void Parser::RestoreCurrentNode(TreeNode *old) {
	current_node_ = old;
}
