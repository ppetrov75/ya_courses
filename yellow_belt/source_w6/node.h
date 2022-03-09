#ifndef YELLOW_BELT_NODE_H
#define YELLOW_BELT_NODE_H

#include <memory>
#include "date.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Equal,
    NotEqual,
    Greater,
    GreaterOrEqual
};

enum class LogicalOperation {
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class LogicalOperationNode : public Node {
    LogicalOperation opr_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
public:
    LogicalOperationNode(const LogicalOperation operation, std::shared_ptr<Node> left,
                         std::shared_ptr<Node> right) : opr_(operation), left_(left), right_(right) {}

    bool Evaluate(const Date &date, const std::string &event) const override;
};

class DateComparisonNode : public Node {
    Comparison cmp_;
    Date date_;

public:
    DateComparisonNode(Comparison comparison, Date date) : cmp_(comparison), date_(date) {}

    bool Evaluate(const Date &date, const std::string &) const override;
};

class EventComparisonNode : public Node {
    Comparison cmp_;
    std::string event_;
public:
    EventComparisonNode(Comparison comparison, const std::string &value) : cmp_(comparison), event_(value) {}

    bool Evaluate(const Date &, const std::string &event) const override;
};

#endif //YELLOW_BELT_NODE_H
