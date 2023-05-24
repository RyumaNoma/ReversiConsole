#include "Node.hpp"
// ビットボード関連
#include "BitBoard.hpp"
// ゲームAI関連
#include "GameAIFunction.hpp"
// 汎用
#include "Random.hpp"

Node::Node()
	: action_()
	, w_(0)
	, ww_(0)
	, n_(0)
	, children_()
{
}

Node::Node(const Point& action)
	: action_(action)
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

double Node::Evaluate(BitBoard& copy, Allocator<Node>& allocator, Random& random)
{
	double result;
	if (copy.IsFinish())
	{
		result = copy.Result();
		w_ += result;
		ww_ += result * result;
		++n_;
		return result;
	}
	if (children_.empty())
	{
		if (n_ == EXPAND_THRESHOLD_ - 1)
		{
			Expand(copy, allocator);
		}
		result = GameAIFunction::Playout(&copy, &random);
		w_ += result;
		ww_ += result * result;
		++n_;
		return result;
	}
	else
	{
		Node* child = SelectChildren();
		copy.Act(child->action_);
		result = 1.0 - child->Evaluate(copy, allocator, random);
		w_ += result;
		ww_ += result * result;
		++n_;
		return result;
	}
	return result;
}

void Node::Expand(const BitBoard& board, Allocator<Node>& allocator)
{
	auto legal_actions = board.LegalActions();
	for (const auto& action : legal_actions)
	{
		Node* ptr = allocator.Allocate();
		if (ptr == nullptr)
		{
			std::cout << "NULL POINTER" << std::endl;
			exit(-1);
		}
		new(ptr) Node(action);
		children_.push_back(ptr);
	}
}

Node* Node::SelectChildren() const
{
	Node* best_child = nullptr;
	double best_value = -1;
	for (Node* child : children_)
	{
		double value = child->UCB1_Tuned(n_);
		if (value > best_value)
		{
			best_value = value;
			best_child = child;
		}
	}
	return best_child;
}

Point Node::SelectBestAction() const
{
	Point best_action = Point(-1, -1);
	double best_value = -1;
	for (Node* child : children_)
	{
		if (child->n_ > best_value)
		{
			best_value = child->n_;
			best_action = child->action_;
		}
	}
	return best_action;
}

double Node::UCB1(int N) const
{
	if (N == 0 || n_ == 0) return 10000;
	return (1.0 - w_ / n_) + C_ * std::sqrt(2 * log(N) / n_);
}

double Node::UCB1_Tuned(int N) const
{
	if (N == 0 || n_ == 0) return 10000;
	const double mean = (1 - w_ / n_);
	const double dispersion = (1 - ww_ / n_) - mean * mean;
	const double V = dispersion + std::sqrt(2 * log(N) / n_);
	return mean + C_ * std::sqrt(log(N) / n_ * std::min(0.25, V));
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	double mean;
	os << "action:" << node.action_ << std::endl
		<< "n:" << node.n_ << std::endl
		<< "w:" << node.w_ << std::endl
		<< "ww:" << node.ww_ << std::endl
		<< "children:" << node.children_.size() << std::endl
		<< "平均:" << (mean = 1 - node.w_ / node.n_) << std::endl
		<< "標準偏差:" << std::sqrt((1 - node.ww_ / node.n_) - mean * mean);
	return os;
}
