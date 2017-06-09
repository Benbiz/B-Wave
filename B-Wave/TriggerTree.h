#ifndef TRIGGERTREE_H
#define TRIGGERTREE_H

typedef struct  s_condition
{
    int         value[2];               // Hold informations relative to the values the sensor must be <, >, = or >< to. value[1] is only for ><
    bool        boolean;                // Hold information relative to the state the sensor must be in order to be considered activated
    char        symbol[3];              // Hold informations relative to value[2] and boolean. Can be >, <, = or ! (! means to be ignored)

}               t_condition;

class TriggerTree
{
public:
    TriggerTree(std::pair<std::shared_ptr<BoxAPI::ICommand>, t_condition*> &);
    TriggerTree(TriggerTree *_treeA, char symbol, TriggerTree *_treeB);
    ~TriggerTree();

    bool        getBoolResult();
    bool        checkConditions(std::shared_ptr<BoxAPI::ICommand> trigger, t_condition *conditions);
    bool        boolOperation(bool a, char op, bool b);
    bool        valueComparison(int value, char op, int value2);


private:
    std::pair<std::shared_ptr<BoxAPI::ICommand>, t_condition*>  pair_device_condition;
    char        symbol;
    TriggerTree *treeB;
    TriggerTree *treeA;
	bool		isCondition;
};

#endif // TRIGGERTREE_H
