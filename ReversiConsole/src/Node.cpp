#include "Node.hpp"
//Point action_;
//double w_;
//int n_;
//std::vector<Node*> children_;
Node::Node()
	: action_()
	, w_(0)
	, ww_(0)
	, n_(0)
	, children_()
{
}

Node::Node(const Node& node)
	: action_(node.action_)
	, w_(node.w_)
	, ww_(node.ww_)
	, n_(node.n_)
	, children_(node.children_)
{
}
