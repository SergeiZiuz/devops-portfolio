//
//  node.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/node.hpp"

EmptyNode::EmptyNode() { }
bool EmptyNode::Evaluate(const Date& date, const std::string& event) {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date): _comparison(cmp), _date(date) { }

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
    return ComparisonValue(_comparison, date, _date);
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const std::string& value): _comparison(cmp), _value(value) { }

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) {
    return ComparisonValue(_comparison, event, _value);
}

LogicalOperationNode::LogicalOperationNode (
                                            const LogicalOperation& logical_operation,
                                            const std::shared_ptr<Node>& left,
                                            const std::shared_ptr<Node>& right
                                            ): _logical_operation(logical_operation), _left(left), _right(right) { }

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) {
    switch (_logical_operation) {
        case LogicalOperation::Or:
            return _left->Evaluate(date, event) || _right->Evaluate(date, event);
        case LogicalOperation::And:
            return _left->Evaluate(date, event) && _right->Evaluate(date, event);
    }
    return false;
}
