#include "Node.hpp"
#include "BitBoard.hpp"
#include "GameAIFunction.hpp"
#include "Random.hpp"

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
		result = GameAIFunction::Playout(&copy, &random);
		w_ += result;
		ww_ += result * result;
		++n_;

		if (n_ == EXPAND_THRESHOLD_)
		{
			Expand(copy, allocator);
		}
		return result;
	}
	else
	{
		result = 1.0 - Evaluate(copy, allocator, random);
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
		Node* ptr = new(allocator.Allocate()) Node(action);
		children_.push_back(ptr);
	}
}

double Node::UCB1(int N, double C) const
{
	if (N == 0 || n_ == 0) return 10000;
	return w_ / n_ + C * std::sqrt(2 * log(N) / n_);
}

double Node::UCB1_Tuned(int N, double C) const
{
	if (N == 0 || n_ == 0) return 10000;
	const double mean = w_ / n_;
	const double dispersion = ww_ / n_ - mean * mean;
	const double V = dispersion * std::sqrt(2 * log(N) / n_);
	return mean + C * std::sqrt(log(N) / n_ * std::min(0.25, V));
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	// TODO: return ステートメントをここに挿入します
}
