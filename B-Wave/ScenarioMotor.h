#ifndef SCENARIOMOTOR_H
#define SCENARIOMOTOR_H

#include "ControllerEvent.h"
#include "Scenario.h"

class ScenarioMotor
{
public:
    ScenarioMotor();
    ~ScenarioMotor();

    void                    initialize();
    void                    printScenario(Scenario *scenario);
    void                    printTrigger(t_trigger *trigger);
    void                    printAction(t_action *action);

    t_trigger               *createTrigger(double uniqueID, int deviceID, int instanceID, int sensorID,
                                           int typeID, std::string typeName, std::string triggerName,
                                           std::shared_ptr<BoxAPI::ICommand>);
    t_action                *createAction(double uniqueID, int deviceID, int instanceID, int sensorID,
                                          int typeID, bool default_bin_value, int default_value, bool binary_value, int value,
										  std::string typeName, std::string actionName, std::shared_ptr<BoxAPI::ICommand> cmd);
    t_condition             *createCondition(int value, int value2, bool boolean, char sym, char sym2, char sym3);
    Scenario                *createScenario(int id, std::string scenarioName, std::string expression,
                                            std::vector<t_action*> actions, TriggerTree *_tree);

    void                    addScenario(Scenario *newScenario);

    std::vector<Scenario*>  getScenarios();
    std::vector<t_trigger*> getTriggers();
    std::vector<t_action*>  getActions();
	std::vector<std::pair<double, std::shared_ptr<BoxAPI::ICommand>>>	&getPairIdDevice();

    void                    setDisabledScenario(int i, bool disabled);
    void                    setDisabledScenario(std::string name, bool disabled);

    void                    triggerTriggered(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> cmd);
    void                    triggerEvent(double triggerID);
    void                    executeScenario(Scenario *scenario, bool scenario_state);

    double                  generateUniqueID(int dev, int ins, int sen, int typ);

    //void                  jsonWrite();
    //void                  jsonRead();

private:
    std::vector<Scenario*>  vecScenario;
    std::vector<t_trigger*> vecTriggers;
    std::vector<t_action*>  vecActions;
    std::vector<std::pair<double, std::shared_ptr<BoxAPI::ICommand>>>    vecPairIdDevices;
};

#endif // SCENARIOMOTOR_H
