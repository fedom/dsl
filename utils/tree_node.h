#include <string>
#include <vector>

//https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram

class TreeNode {
public:
	TreeNode(std::string name);
	virtual ~TreeNode();

	void AddChild(TreeNode *node);
	void PrintTree(const std::string &prefix, bool is_tail);

private:
	std::string name_;
	std::vector<TreeNode *> children_;
};
