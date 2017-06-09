#include "stdafx.h"
#include "Command.h"
#include "ControllerEvent.h"
#include "BWave.h"
#include "ScenarioMotor.h"


ScenarioMotor::ScenarioMotor()
{
    std::setprecision(10);
}

ScenarioMotor::~ScenarioMotor()
{
    //this->jsonWrite();
}

void                        ScenarioMotor::initialize()
{
    //this->jsonRead();

	BoxAPI::ControllerEvent::CommandSubscriber	cmd(std::bind(&ScenarioMotor::triggerTriggered, this, std::placeholders::_1));
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(cmd);

    for (unsigned int i = 0; i < this->vecScenario.size(); ++i)
        this->printScenario(this->vecScenario[i]);

    for (unsigned int i = 0; i < this->vecActions.size(); ++i)
        this->printAction(this->vecActions[i]);

    for (unsigned int i = 0; i < this->vecTriggers.size(); ++i)
        this->printTrigger(this->vecTriggers[i]);
}

t_trigger                   *ScenarioMotor::createTrigger(double uniqueID, int deviceID, int instanceID, int sensorID,
                                                          int typeID, std::string typeName, std::string triggerName,
                                                          std::shared_ptr<BoxAPI::ICommand> cmd)
{
    if (uniqueID == -1)
        uniqueID = this->generateUniqueID(deviceID, instanceID, sensorID, typeID);
    for (unsigned int i = 0; i < this->vecTriggers.size(); ++i)
    {
        if (this->vecTriggers[i]->uniqueID == uniqueID)
            return (this->vecTriggers[i]);
    }

    t_trigger                                               *trigger = new t_trigger;
    std::pair<double, std::shared_ptr<BoxAPI::ICommand>>    pair;

    pair.first = uniqueID;
    pair.second = cmd;

    *trigger = {uniqueID, deviceID, instanceID, sensorID, typeID, typeName, triggerName};
    this->vecTriggers.push_back(trigger);
    this->vecPairIdDevices.push_back(pair);
    return (trigger);
}

t_action                    *ScenarioMotor::createAction(double uniqueID, int deviceID, int instanceID, int sensorID,
                                                         int typeID, bool default_bin_value, int default_value, bool binary_value, int value,
														 std::string typeName, std::string actionName, std::shared_ptr<BoxAPI::ICommand> cmd)
{
    if (uniqueID == -1)
        uniqueID = this->generateUniqueID(deviceID, instanceID, sensorID, typeID);
    for (unsigned int i = 0; i < this->vecActions.size(); ++i)
    {
        if (this->vecActions[i]->uniqueID == uniqueID)
            return (this->vecActions[i]);
    }

    t_action                *action = new t_action;

    *action = {uniqueID, deviceID, instanceID, sensorID, typeID, default_bin_value, default_value, binary_value, value, typeName, actionName};
    this->vecActions.push_back(action);
	std::pair<double, std::shared_ptr<BoxAPI::ICommand>>    pair;
	pair.first = uniqueID;
	pair.second = cmd;
	this->vecPairIdDevices.push_back(pair);
    return (action);
}

t_condition                 *ScenarioMotor::createCondition(int value, int value2, bool boolean, char sym, char sym2, char sym3)
{
    t_condition             *condition = new t_condition;

    condition->value[0] = value;
    condition->value[1] = value2;
    condition->boolean = boolean;
    condition->symbol[0] = sym;
    condition->symbol[1] = sym2;
    condition->symbol[2] = sym3;

    return (condition);
}

Scenario                    *ScenarioMotor::createScenario(int id, std::string scenarioName, std::string expression,
                                                           std::vector<t_action*> actions, TriggerTree *_tree)
{
    for (unsigned int i = 0; i < this->vecScenario.size(); ++i)
    {
        if (this->vecScenario[i]->getID() == id)
            return (this->vecScenario[i]);
    }

    Scenario                *scenario = new Scenario(scenarioName, expression);

    //for (unsigned int i = 0; i < triggers.size(); ++i)
        //scenario->addTrigger(triggers[i].first->uniqueID, triggers[i].second);
    scenario->setID(id);
    scenario->setTriggerTree(_tree);

    for (unsigned int i = 0; i < actions.size(); ++i)
        scenario->addAction(actions[i]->uniqueID);

    this->addScenario(scenario);
    return (scenario);
}

std::vector<Scenario*>      ScenarioMotor::getScenarios()
{
    return (this->vecScenario);
}

std::vector<t_trigger*>     ScenarioMotor::getTriggers()
{
    return (this->vecTriggers);
}

std::vector<t_action*>      ScenarioMotor::getActions()
{
    return (this->vecActions);
}

std::vector<std::pair<double, std::shared_ptr<BoxAPI::ICommand>>>	&ScenarioMotor::getPairIdDevice()
{
	return vecPairIdDevices;
}

void                        ScenarioMotor::setDisabledScenario(int i, bool disabled)
{
    if (i < this->vecScenario.size())
        this->vecScenario[i]->setDisabled(disabled);
}

void                        ScenarioMotor::setDisabledScenario(std::string name, bool disabled)
{
    for (unsigned int i = 0; i < this->vecScenario.size(); ++i)
    {
        if (name == this->vecScenario[i]->getName())
        {
            this->vecScenario[i]->setDisabled(disabled);
            return ;
        }
    }
}

void                        ScenarioMotor::printScenario(Scenario *scenario)
{
    std::cout << "Scenario name: " << scenario->getName() << std::endl;

    std::cout << "\tTriggers:\n";
    for (unsigned int l = 0; l < scenario->getTriggers().size(); ++l)
    {
        std::cout << "\t\tID: " << scenario->getTriggers()[l].first
                  << " \tConditions: " << scenario->getTriggers()[l].second->symbol[0]
                  << " " << scenario->getTriggers()[l].second->symbol[1]
                  << " " << scenario->getTriggers()[l].second->symbol[2]
                  << " bool= " << scenario->getTriggers()[l].second->boolean
                  << " value= " << scenario->getTriggers()[l].second->value[0]
                  << " " << scenario->getTriggers()[l].second->value[1] << std::endl;
    }

    std::cout << "\tActions:\n";
    for (unsigned int n = 0; n < scenario->getActions().size(); ++n)
        std::cout << "\t\tID: " << scenario->getActions()[n] << std::endl;

    std::cout << "\tExpression:\n" << "\t\t" << scenario->getExpression() << std::endl;
}

void                        ScenarioMotor::printTrigger(t_trigger *trigger)
{
    std::cout << "\nTrigger details:\n";
    std::cout << "\tUnique ID: " << trigger->uniqueID << std::endl;
    std::cout << "\tDevice ID: " << trigger->deviceID << std::endl;
    std::cout << "\tInstance ID: " << trigger->instanceID << std::endl;
    std::cout << "\tSensor ID: " << trigger->sensorID << std::endl;
    std::cout << "\tType ID: " << trigger->typeID << std::endl;
    std::cout << "\tType Name: " << trigger->typeName << std::endl;
    std::cout << "\tTrigger Name: " << trigger->triggerName << std::endl << std::endl;
}

void                        ScenarioMotor::printAction(t_action *action)
{
    std::cout << "\nActions details:\n";
    std::cout << "\tUnique ID: " << action->uniqueID << std::endl;
    std::cout << "\tDevice ID: " << action->deviceID << std::endl;
    std::cout << "\tInstance ID: " << action->instanceID << std::endl;
    std::cout << "\tSensor ID: " << action->sensorID << std::endl;
    std::cout << "\tType ID: " << action->typeID << std::endl;

    std::cout << "\tDefault binary value: " << action->default_bin_value << std::endl;
    std::cout << "\tDefault value: " << action->default_value << std::endl;
    std::cout << "\tBinary value: " << action->bin_value << std::endl;
    std::cout << "\tValue: " << action->value << std::endl;

    std::cout << "\tType Name: " << action->typeName << std::endl;
    std::cout << "\tAction Name: " << action->actionName << std::endl << std::endl;
}

void                        ScenarioMotor::addScenario(Scenario *newScenario)
{
    this->vecScenario.push_back(newScenario);
}


void						ScenarioMotor::triggerTriggered(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> cmd)
{
    std::cout << "Trigger triggered: ID = " << cmd->data->getDeviceId() << std::endl;
    if (cmd->type == BoxAPI::ControllerEvent::Data::EventType::Remove)
    {
        for (unsigned int i = 0; i < this->vecPairIdDevices.size(); ++i)
        {
            if (cmd->data == this->vecPairIdDevices[i].second)
                this->vecPairIdDevices[i].second = nullptr;
        }
    }
    if (cmd->type == BoxAPI::ControllerEvent::Data::EventType::Update)
    {
        for (unsigned int i = 0; i < this->vecPairIdDevices.size(); ++i)
        {
            if (cmd->data == this->vecPairIdDevices[i].second)
                this->triggerEvent(this->vecPairIdDevices[i].first);
        }
    }
}

void                        ScenarioMotor::triggerEvent(double triggerID)
{
    std::cout << "Trigger event: " << triggerID << std::endl;
    // Find all scenarios containing this triggerID
    for(unsigned int i = 0; i < this->vecScenario.size(); ++i)
    {
        std::cout << "Debug: Scenario " << this->vecScenario[i]->getName() << ": ";
        this->executeScenario(this->vecScenario[i], this->vecScenario[i]->getTree()->getBoolResult());
    }
}

void                        ScenarioMotor::executeScenario(Scenario *scenario, bool scenario_state)
{
    std::cout <<"Scenario executed: " << scenario->getName() << std::endl;

    bool            binary_value = true;
    int             value = 125;

    for (unsigned int i = 0; i < scenario->getActions().size(); ++i)
    {
        for (unsigned int l = 0; l < this->vecActions.size(); ++l)
        {
            if (this->vecActions[l]->uniqueID == scenario->getActions()[i])
            {
                    binary_value = this->vecActions[l]->bin_value;
                    value = this->vecActions[l]->value;
            }
        }
        for (unsigned int n = 0; n < this->vecPairIdDevices.size(); ++n)
        {
            if (scenario->getActions()[i] == this->vecPairIdDevices[n].first)
            {
                
                if (this->vecPairIdDevices[n].second->getType() == BoxAPI::ICommand::ZSwitchBinary)
                {
                    std::shared_ptr<BoxAPI::Command::ZSwitchBinary> ptr = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchBinary>(this->vecPairIdDevices[n].second);
					if (ptr->getSwitch() == binary_value)
						continue;
					std::cout << "executed binary (" << ptr->getSwitch() << " != " << binary_value << std::endl;
                    ptr->setSwitch(binary_value);
                }
                else if (this->vecPairIdDevices[n].second->getType() == BoxAPI::ICommand::ZSwitchMultiLevel)
                {
                    std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> ptr = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(this->vecPairIdDevices[n].second);
					if (ptr->getLevel() == value)
						continue;
					std::cout << "executed multilevel\n";
                    ptr->setLevel(value);
                }
                else if (this->vecPairIdDevices[n].second->getType() == BoxAPI::ICommand::ZSwitchColor)
                {
                    std::shared_ptr<BoxAPI::Command::ZSwitchColor> ptr = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(this->vecPairIdDevices[n].second);
					if (ptr->getValue() == value)
						continue;
					std::cout << "executed color\n";
                    ptr->setValue(value);
                }
            }
        }
    }
}

double                      ScenarioMotor::generateUniqueID(int dev, int ins, int sen, int typ)
{
    std::string str;
    str += std::to_string(dev) + std::to_string(ins) + std::to_string(sen) + std::to_string(typ);
    return (std::atof(str.c_str()));
}

/*void						ScenarioMotor::jsonWrite()
{
    std::cout << "\nWRITING ON FILE" << std::endl;
    Json::StyledWriter		styledWriter;

    Json::Value				allEntries;
    Json::Value				scenarioNames;
    Json::Value                         listTriggers;
    Json::Value                         listActions;
    Json::Value                         listScenarios;

    std::string				jsonToStr;
    std::ofstream			scenarioFile;


    // WRITE LIST OF TRIGGERS
    for (unsigned int iTrig = 0; iTrig < this->vecTriggers.size(); ++iTrig)
    {
        t_trigger           *currentTrigger = this->vecTriggers[iTrig];
        Json::Value         trigger;

        trigger["UniqueID"] = currentTrigger->uniqueID;
        trigger["DeviceID"] = currentTrigger->deviceID;
        trigger["InstanceID"] = currentTrigger->instanceID;
        trigger["SensorID"] = currentTrigger->sensorID;
        trigger["TypeID"] = currentTrigger->typeID;
        trigger["TypeName"] = currentTrigger->typeName;
        trigger["Name"] = currentTrigger->triggerName;

        listTriggers.append(trigger);
    }

    // WRITE LIST OF ACTIONS
    for (unsigned int iAct = 0; iAct < this->vecActions.size(); ++iAct)
    {
        t_action           *currentAction = this->vecActions[iAct];
        Json::Value         action;

        action["UniqueID"] = currentAction->uniqueID;
        action["DeviceID"] = currentAction->deviceID;
        action["InstanceID"] = currentAction->instanceID;
        action["SensorID"] = currentAction->sensorID;
        action["TypeID"] = currentAction->typeID;
        action["DefaultBinaryValue"] = currentAction->default_bin_value;
        action["DefaultValue"] = currentAction->default_value;
        action["BinaryValue"] = currentAction->bin_value;
        action["Value"] = currentAction->value;
        action["TypeName"] = currentAction->typeName;
        action["Name"] = currentAction->actionName;

        listActions.append(action);
    }

    // WRITE SUMMARY OF SCENARIO AND LIST OF SCENARIOS
    for (unsigned int i = 0; i < this->vecScenario.size(); ++i)
    {
        Scenario            *currentScenario = this->vecScenario[i];
        Json::Value         scenario;
        Json::Value         listConditions;
        Json::Value         listScenarioActions;

        // GET TRIGGER AND ASSOCIATED CONDITIONS
        for (unsigned int iCond = 0; iCond < currentScenario->getTriggers().size(); ++iCond)
        {
            int             currentTriggerID = std::get<0>(currentScenario->getTriggers()[iCond]);
            t_condition     *currentCondition = std::get<1>(currentScenario->getTriggers()[iCond]);
            Json::Value     condition;
            Json::Value     value;
            Json::Value     symbol;

            value.append(currentCondition->value[0]);
            value.append(currentCondition->value[1]);
            value.append(currentCondition->boolean);
            symbol.append(currentCondition->symbol[0]);
            symbol.append(currentCondition->symbol[1]);
            symbol.append(currentCondition->symbol[2]);

            condition["TriggerID"] = currentTriggerID;
            condition["Value"] = value;
            condition["Symbol"] = symbol;

            listConditions.append(condition);
        }

        // GET ACTIONS
        for (unsigned int iAct = 0; iAct < currentScenario->getActions().size(); ++iAct)
            listScenarioActions.append(currentScenario->getActions()[iAct]);

        // GATHER EXPRESSION, TRIGGER, CONDITIONS, ACTION, AND WRITE SUMMARY
        scenarioNames.append(currentScenario->getName());
        scenario["Expression"] = currentScenario->getExpression();
        scenario["Conditions"] = listConditions;
        scenario["Actions"] = listScenarioActions;

        listScenarios[currentScenario->getName()] = scenario;
    }

    // GATHER ALL INFORMATIONS
    allEntries["Summary of scenario name"] = scenarioNames;
    allEntries["List of triggers"] = listTriggers;
    allEntries["List of actions"] = listActions;
    allEntries["List of scenarios"] = listScenarios;


    // WRITE ALL ENTRIES ON THE FILE
    jsonToStr = styledWriter.write(allEntries);
    scenarioFile.open("files/scenariosList.json", std::ofstream::out | std::ofstream::trunc);
    if (!scenarioFile.is_open())
        std::cout << "Couldn't open files/scenariosList; function jsonWrite\n";
    else
    {
        scenarioFile << jsonToStr << "\n";
        scenarioFile.close();
    }
}

void                        ScenarioMotor::jsonRead()
{
    Json::Value					rootScenario;
    Json::Reader				reader;
    std::ifstream				scenarioFile("files/scenariosList.json", std::ifstream::binary);


    std::cout << "ScenarioMotor: parsing..." << std::endl;                                      // DEBUG

    if (!reader.parse(scenarioFile, rootScenario))
    {
        std::cout << "Error: " << reader.getFormattedErrorMessages() << "\n";
        return ;
    }


    Json::Value                 rawScenarioNames = rootScenario["Summary of scenario name"];        //
    Json::Value                 rawListTriggers = rootScenario["List of triggers"];                 //  SOURCE
    Json::Value                 rawListActions = rootScenario["List of actions"];                   //
    Json::Value                 rawListScenarios = rootScenario["List of scenarios"];               //

    std::vector<std::string>    refinedScenarioNames;



    // REFINE RAW LIST OF SCENARIOS NAMES
    std::cout << "scenario names..." << std::endl;                                              // DEBUG
    for (unsigned int i = 0; i < rawScenarioNames.size(); ++i)
        refinedScenarioNames.push_back(rawScenarioNames.get(i, "NONE").asString());


    // REFINE RAW LIST OF TRIGGERS
    std::cout << "list triggers..." << std::endl;                                               // DEBUG
    for (unsigned int i = 0; i < rawListTriggers.size(); ++i)
    {
        t_trigger               *newTrigger = new t_trigger;
        Json::Value             currentRawTrigger = rawListTriggers.get(i, "NONE");

        newTrigger->uniqueID     = currentRawTrigger.get("UniqueID", "NONE").asDouble();
        newTrigger->deviceID     = currentRawTrigger["DeviceID"].asInt();
        newTrigger->instanceID   = currentRawTrigger["InstanceID"].asInt();
        newTrigger->sensorID     = currentRawTrigger["SensorID"].asInt();;
        newTrigger->typeID       = currentRawTrigger["TypeID"].asInt();
        newTrigger->typeName     = currentRawTrigger["TypeName"].asString();
        newTrigger->triggerName  = currentRawTrigger["Name"].asString();

        this->vecTriggers.push_back(newTrigger);
    }


    // REFINE RAW LIST OF ACTIONS
    std::cout << "list actions..." << std::endl;                                                        // DEBUG
    for (unsigned int i = 0; i < rawListActions.size(); ++i)
    {
        t_action               *newAction = new t_action;
        Json::Value             currentRawAction = rawListActions.get(i, "NONE");

        newAction->uniqueID     = currentRawAction["UniqueID"].asDouble();
        newAction->deviceID     = currentRawAction["DeviceID"].asInt();
        newAction->instanceID   = currentRawAction["InstanceID"].asInt();
        newAction->sensorID     = currentRawAction["SensorID"].asInt();;
        newAction->typeID       = currentRawAction["TypeID"].asInt();

        newAction->default_bin_value    = currentRawAction["DefaultBinaryValue"].asBool();
        newAction->default_value        = currentRawAction["DefaultValue"].asInt();
        newAction->bin_value            = currentRawAction["BinaryValue"].asBool();
        newAction->value                = currentRawAction["Value"].asInt();

        newAction->typeName     = currentRawAction["TypeName"].asString();
        newAction->actionName   = currentRawAction["Name"].asString();

        this->vecActions.push_back(newAction);
    }


    // CREATE SCENARIOS
    std::cout << "scenarios..." << std::endl;                                                          // DEBUG
    for (unsigned int i = 0; i < refinedScenarioNames.size(); ++i)
    {
        std::cout << "create scenario...";                                                              // DEBUG

        Scenario            *newScenario = new Scenario();
        Json::Value         currentRawScenario = rawListScenarios[refinedScenarioNames[i]];
        Json::Value         rawConditions = currentRawScenario["Conditions"];
        Json::Value         rawActions = currentRawScenario["Actions"];

        newScenario->setName(refinedScenarioNames[i]);
        newScenario->setExpression(currentRawScenario["Expression"].asString());


        // REFINE RAW CONDITIONS
        for (unsigned int iCond = 0; iCond < rawConditions.size(); ++iCond)
        {
            std::cout << "create condition...";                                                          // DEBUG
            t_condition     *newCondition = new t_condition;
            Json::Value     currentRawCondition = rawConditions.get(iCond, "NONE");
            unsigned int    arrayValue = 0;

            newCondition->value[0]  = currentRawCondition["Value"].get(arrayValue, "NONE").asInt();
            newCondition->value[1]  = currentRawCondition["Value"].get(arrayValue + 1, "NONE").asInt();
            newCondition->boolean   = currentRawCondition["Value"].get(arrayValue + 2, "NONE").asBool();
            newCondition->symbol[0] = currentRawCondition["Symbol"].get(arrayValue, "NONE").asInt();
            newCondition->symbol[1] = currentRawCondition["Symbol"].get(arrayValue + 1, "NONE").asInt();
            newCondition->symbol[2] = currentRawCondition["Symbol"].get(arrayValue + 2, "NONE").asInt();

            newScenario->addTrigger(currentRawCondition["TriggerID"].asInt(), newCondition);
        }

        // REFINE RAW ACTIONS
        for (unsigned int iAct = 0; iAct < rawActions.size(); ++iAct)
        {
            std::cout << "create action...";                                                          // DEBUG
            newScenario->addAction(rawActions.get(iAct, "NONE").asInt());
        }

        std::cout << "done. Adding scenario to motor." << std::endl;                                  // DEBUG
        this->addScenario(newScenario);
    }
    std::cout << "Scenario Motor: parsing ended successfully." << std::endl;                          // DEBUG
}*/
