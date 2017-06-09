#include "stdafx.h"
#include "Command.h"
#include "Scenario.h"

Scenario::Scenario()
{

}

Scenario::Scenario(std::string _name, std::string express)
{
    this->setName(_name);
    this->setExpression(express);
    this->setDisabled(false);
}

Scenario::~Scenario()
{
    /*std::cout << "Deleting scenario " << this->name << "...";       // DEBUG

    if (this->name != NULL)
        delete this->name;
    for (unsigned int i = 0; i < this->vecTriggers.size(); ++i)
    {
        if (std::get<0>(this->vecTriggers[i]) != NULL)
            delete std::get<0>(this->vecTriggers[i]);
        if (std::get<1>(this->vecTriggers[i]) != NULL)
            delete std::get<1>(this->vecTriggers[i]);
    }
    for (unsigned int i = 0; i < this->vecAction.size(); ++i)
    {
        if (this->vecAction[i] != NULL)
            delete this->vecAction[i];
    }
    for (unsigned int i = 0; i < this->vecExpression.size(); ++i)
    {
        if (this->vecExpression[i] != NULL)
            delete this->vecExpression[i];
    }
    this->vecTriggers.clear();
    this->vecAction.clear();
    this->vecExpression.clear();

    std::cout << "completed." << std::endl;                         // DEBUG*/
}

void                                                Scenario::setName(std::string _name)
{
    this->name = _name;
}

void                                                Scenario::setID(int _id)
{
    this->id = _id;
}

void                                                Scenario::setExpression(std::string express)
{
    // FRAGMENTER L'EXPRESSION ICI
    // TEMPORARY:
    this->vecExpression.push_back(new std::string(express));
}

void                                                Scenario::setDisabled(bool _disabled)
{
    this->disabled = _disabled;
}

void                                                Scenario::setTriggerTree(TriggerTree *_tree)
{
    this->tree = _tree;
}

void                                                Scenario::addTrigger(double triggerID, t_condition *condition)
{
    std::pair<int, t_condition*>                    newPair(triggerID, condition);

    this->vecTriggersID.push_back(newPair);
}

void                                                Scenario::addAction(double actionID)
{
    this->vecActionsID.push_back(actionID);
}


std::string                                         Scenario::getName()
{
    return (this->name);
}

int                                                 Scenario::getID()
{
    return (this->id);
}

std::vector<std::pair<double, t_condition*>>           Scenario::getTriggers()
{
    return (this->vecTriggersID);
}

std::vector<double>                                    Scenario::getActions()
{
    return (this->vecActionsID);
}

std::vector<std::string*>                           Scenario::getFragExpression()
{
    return (this->vecExpression);
}

std::string                                         Scenario::getExpression()
{
    // ICI RECOLLER LES FRAGMENTS ET RETOURNER EN UNE CHAINE
    // TEMPORARY:
    return (*this->vecExpression[0]);
}

bool                                                Scenario::getDisabled()
{
    return (this->disabled);
}

TriggerTree                                         *Scenario::getTree()
{
    return (this->tree);
}
