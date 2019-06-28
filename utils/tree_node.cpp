#include "tree_node.h"
#include <cstdio>

TreeNode::TreeNode(std::string name) : name_(name) {

}

TreeNode::~TreeNode() {
	for (auto iter = children_.begin(); iter != children_.end(); ++iter) {
		delete *iter;	
	}
}

void TreeNode::AddChild(TreeNode *node) {
	children_.push_back(node);
}

void TreeNode::PrintTree(const std::string &prefix, bool is_tail) {
	printf("%s\n",(prefix + (is_tail ? "└── " : "├── ") + name_).c_str());

	if (!children_.empty()) {
	
		for (int i = 0; i < children_.size() - 1; i++) {
			children_[i]->PrintTree(prefix + (is_tail ? "    " : "│   "), false);
		}
	
		children_[children_.size() - 1]->PrintTree(prefix + (is_tail ? "    " : "│   "), true);
	}
}
