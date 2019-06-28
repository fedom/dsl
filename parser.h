#ifndef __PARSER_H__
#define __PARSER_H__
#include "lexer.h"
#include <stack>
#include <vector>
#include "utils/tree_node.h"


#define UPDATE_CURRENT_NODE(name)		TreeNode *old_node;\
   										do {\
											if (!IsSpeculating()) {\
												old_node = LinkNewNode(name);\
											}\
										} while(0)

#define RESTORE_CURRENT_NODE()			do {\
											if (!IsSpeculating()) current_node_ = old_node;\
										} while(0)

class Parser {
public:
	Parser(Lexer *lexer);
	virtual ~Parser();

	virtual void Parse() = 0;


protected:
	Token LA(int i);
	int LT(int i);

	void MarkBase();
	void RestoreBase();
	
	void Match(int token_type);
	void Consume();
	void Sync(int i);
	bool IsSpeculating();
	int CurPos();
	void SetPos(int i);

	TreeNode *LinkNewNode(const char *node_name);
	void RestoreCurrentNode(TreeNode *old);

	Lexer *lexer_;
	std::vector<Token> lookahead_tokens_;
	std::stack<int> base_i_;
	
	int i_;

	TreeNode *root_;
	TreeNode *current_node_;
};
#endif//__PARSER_H__
