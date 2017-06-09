#include "stdafx.h"
#include "Command.h"
#include "TriggerTree.h"


TriggerTree::TriggerTree(std::pair<std::shared_ptr<BoxAPI::ICommand>, t_condition*> &pair)
{
    this->pair_device_condition = pair;
    this->symbol = 0;
	this->treeB = nullptr;
    this->treeA = nullptr;
	isCondition = true;
}

TriggerTree::TriggerTree(TriggerTree *_treeA, char symbol, TriggerTree *_treeB)
{
    this->treeA = _treeA;
    this->symbol = symbol;
    this->treeB = _treeB;
	isCondition = false;
}

TriggerTree::~TriggerTree()
{
    if (this->treeB != 0)
        delete this->treeB;
}

bool        TriggerTree::getBoolResult()
{
    if (!isCondition)
    {
        if (symbol == '&')
            return (treeA->getBoolResult() && treeB->getBoolResult());
        else
            return (treeA->getBoolResult() || treeB->getBoolResult());
    }

    bool    value = this->checkConditions(this->pair_device_condition.first, this->pair_device_condition.second);
	return (value);
}

bool                        TriggerTree::checkConditions(std::shared_ptr<BoxAPI::ICommand> trigger, t_condition *conditions)
{
    int                     value = 0;
    bool                    state = false;
    bool                    multilevel = false;
    bool                    binary = false;

    if (trigger->getType() == BoxAPI::ICommand::ZSensorMultiLevel)
    {
        std::shared_ptr<BoxAPI::Command::ZSensorMultiLevel> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorMultiLevel>(trigger);
        value = sensor->getValue();
        multilevel = true;
    }
    else if (trigger->getType() == BoxAPI::ICommand::ZSensorBinary)
    {
        std::shared_ptr<BoxAPI::Command::ZSensorBinary> zswitch = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(trigger);
        state = zswitch->getValue();
        binary = true;
    }
    if (multilevel)
    {
        bool                a = this->valueComparison(value, conditions->symbol[0], conditions->value[0]);
        bool                b = this->valueComparison(value, conditions->symbol[1], conditions->value[1]);

        if ((conditions->symbol[1] != '!' && a && b) || (conditions->symbol[1] == '!' && a))
            return (true);
    }
    else if (binary)
    {
        if (binary == conditions->boolean)
            return (true);
    }
    return (false);
}

bool                        TriggerTree::boolOperation(bool a, char op, bool b)
{
    if (op == '&')
        return (a && b);
    else if (op == '|')
        return (a || b);
    return (false);
}

bool                        TriggerTree::valueComparison(int value, char op, int value2)
{
    if (op == '<')
        if (value < value2)
            return (true);
    if (op == '>')
        if (value > value2)
            return (true);
    if (op == '=')
        if (value == value2)
            return (true);
    if (op == '-')
        if (value <= value2)
            return (true);
    if (op == '+')
        if (value >= value2)
            return (true);
    if (op == '.')
        if (value != value2)
            return (true);
    return (false);
}

