#include "Node.hpp"

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

double Node::UCB1(int N, double C) const
{
	return w_ / n_ + C * std::sqrt(2 * log(N) / n_);
}

double Node::UCB1_Tuned(int N, double C) const
{
	const double mean = w_ / n_;
	const double dispersion = ww_ / n_ - mean * mean;
	const double V = dispersion * std::sqrt(2 * log(N) / n_);
	return mean + C * std::sqrt(log(N) / n_ * std::min(0.25, V));
}