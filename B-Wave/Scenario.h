#ifndef SCENARIO_H
#define SCENARIO_H

#include "TriggerTree.h"

typedef struct  s_trigger
{
    double      uniqueID;               // Allow us to differentiate Triggers; is a simple concatenation of all others IDs; if = 0 = time trigger
    int		deviceID;
    int		instanceID;
    int		sensorID;
    int		typeID;

    std::string	typeName;
    std::string triggerName;            // Optionnal

}               t_trigger;

typedef struct  s_action
{
    double      uniqueID;               // Same as struct Triggers; is a simple concatenation of all others IDs
    int		deviceID;
    int		instanceID;
    int		sensorID;
    int		typeID;

    bool        default_bin_value;      // Default ZSwitchBinary value
    int         default_value;          // Default ZSwitchColor or ZSwitchMultiLevel value

    bool        bin_value;              // For ZSwitchBinary
    int         value;                  // For ZSwitchColor or ZSwitchMultiLevel

    std::string	typeName;
    std::string actionName;             // Optionnal
}               t_action;


class Scenario
{
public:
    Scenario();
    Scenario(std::string _name, std::string express);
    ~Scenario();

    void                                            setName(std::string _name);
    void                                            setID(int _id);
    void                                            setExpression(std::string express);
    void                                            setDisabled(bool _disabled);
    void                                            setTriggerTree(TriggerTree *_tree);

    void                                            addTrigger(t_trigger *trig, t_condition *cond);     // TO DELETE ?
    void                                            addTrigger(double triggerID, t_condition *condition);
    void                                            addAction(t_action *action);                        // TO DELETE ?
    void                                            addAction(double actionID);


    std::string                                     getName();              // Returns scenarioName
    int                                             getID();                // Returns scenarioID
    //std::vector<std::pair<t_trigger*, t_condition*>>    getTriggers();    // TO DELETE ?
    std::vector<std::pair<double, t_condition*>>    getTriggers();          // Returns vecTriggers containing triggers and associated conditions
    //std::vector<t_action*>                        getActions();           // TO DELETE ?
    std::vector<double>                             getActions();           // Returns vecAction containing actions
    std::vector<std::string*>                       getFragExpression();    // Returns vecExpression containing all the parts of the initial expression
    std::string                                     getExpression();        // Returns vecExpression in one std::string
    bool                                            getDisabled();
    TriggerTree                                     *getTree();

private:
    std::string                                     name;                   // Used to identify the scenario; if dopplegangers are allowed, use ID instead;
    int                                             id;                     // ID to identify the scenario if the name isn't sufficient;

    //std::vector<std::pair<t_trigger*, t_condition*>>    vecTriggers;      // TO DELETE ?
    std::vector<std::pair<double, t_condition*>>    vecTriggersID;          // Contains differents triggers and associated conditions
    //std::vector<t_action*>                        vecAction;              // TO DELETE ?
    std::vector<double>                             vecActionsID;           // Contains differents action to be executed when scenario is completed.
    std::vector<std::string*>                       vecExpression;          // ex: "(triggerID && triggerID2)" -> vec[0] == "(", vec[1] == "triggerID", vec[2] == "&&", etc.
    bool                                            disabled;
    TriggerTree                                     *tree;
};

#endif // SCENARIO_H
