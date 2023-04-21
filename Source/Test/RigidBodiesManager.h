#ifndef __RIGIDBODIES_MANAGER_H__
#define __RIGIDBODIES_MANAGER_H__

#include "cocos2d.h"
#include "UtilityClasses.h"

USING_NS_CC;

class RigidBodyModel;
class EditorPanel;
class EditorPanelUI;

class RigidBodiesManager {

public:
    
private:
    //EditorPanel* _editPanel;
    EditorPanelUI* _editPanel;
public:

    std::vector <std::function<void(std::string)>> _onEntryAddedListenerList; //Push a func() to this list if you want to listen to this event.
    std::vector <std::function<void(std::string)>> onSelChangedListenerList; //Push a func() to this list if you want to listen to "OnSelectionChanged" event.
    std::vector <std::function<void(std::string)>> onEntryDeletedListenerList; //Push a func() to this list if you want to listen to "OnEntryDeleted" event.

    std::string PROP_SELECTION = "selection";

    cocos2d::Map<std::string, RigidBodyModel*> _rbModelsMap;
    Vector<RigidBodyModel*> _rbModels;
    
    std::string selectedModelName;
    RigidBodyModel* _selectedModel;
    
    RigidBodiesManager();

    RigidBodyModel* getSelectedModel() {
        return _selectedModel;
    }

    //Call "computePhysics()" on all rigidbody models
    void computeAllRigidBodies();

    void clearModels();

    void removeSelectedModel();

    void removeModel(std::string name);

    //Select model by name
    bool selectModel(std::string name);

    void selectModel(RigidBodyModel* model);

    void selectModelByIndex(int i);

    RigidBodyModel* getModel(std::string name);

    void renameSelectedModel(std::string new_name);

    void setInputModule(EditorPanel*);

    void setInputModuleUI(EditorPanelUI*);

    //Add a Rigidbody entry
    void addARigidBodyEntry(std::string name);
    //Add a Rigidbody entry with a existing model.
    void addARigidBodyEntry(std::string name, RigidBodyModel* model);

    //For error checking

private:
    //Check for name syntax errors
    //Rules:
    //i)Name must not start or end with ' '(Whitespace)
    //ii)That's it.
    bool isNameSyntaxOk(std::string);
public:
    //Check if given string is valid.
    bool isValidEntryName(std::string);
    //Returns an error message about the string which is denied by 'isValidEntryName()'.
    //Error messages:
    //->Empty name.
    //->Name must not start or end with ' '(Whitespace).
    //->Name already exists.
    std::string getErrorMessage(std::string);


    //Events

    void onMouseDownAtPosition(Vec2 pos);

    //Callbacks from Editor Panel

    void onMouseInteractionFromEditor(CustomMouseEvent);
    void onMouseInteractionFromEditor(CustomMouseEvent, EditorMode);

    //Actions on Mouse down at different modes

    void onMouseDownAtPositionCreate(Vec2 pos);

private:

    //List events

    void onEntryAdded(std::string);
    void onSelectionChanged(std::string);
    void onEntryDeleted(std::string); //On an entry deleted(Note: during this function selectedModel is still the one being deleted).

};
#endif // __RIGIDBODIES_MANAGER_H__
