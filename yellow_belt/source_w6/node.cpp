#include "node.h"

template<typename T>
bool compare(T left, Comparison cmp, T right) {
    switch (cmp) {
        case Comparison::Less:
            return left < right;
            break;
        case Comparison::LessOrEqual:
            return left <= right;
            break;
        case Comparison::Equal:
            return left == right;
            break;
        case Comparison::NotEqual:
            return left != right;
            break;
        case Comparison::Greater:
            return left > right;
            break;
        case Comparison::GreaterOrEqual:
            return left >= right;
            break;
    }
    throw std::logic_error("unknown compare operation: " + (int)cmp);
}

bool EmptyNode::Evaluate(const Date &date, const std::string &event) const {
    return true;
}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    if(opr_ == LogicalOperation::And)
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    else if (opr_ == LogicalOperation::Or)
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    throw std::logic_error("unknown logical operation: " + (int)opr_);
}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &) const {
    return compare(date, cmp_, date_);
}

bool EventComparisonNode::Evaluate(const Date &, const std::string &event) const {
    return compare(event, cmp_, event_);
}
