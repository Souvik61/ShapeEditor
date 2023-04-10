#include "RigidBodiesManager.h"
#include "RigidBodyModel.h"
#include "Test/UI/EditorPanelUI.h"
#include "ShapeModel.h"


RigidBodiesManager::RigidBodiesManager() :_selectedModel(nullptr), selectedModelName("")
{

}

RigidBodyModel* RigidBodiesManager::getModel(string name)
{
    for (auto it = _rbModelsMap.begin(); it != _rbModelsMap.end(); it++)
    {
        if ((*it).second->getName() == name)
            return (*it).second;
    }
    return nullptr;
}


void RigidBodiesManager::renameSelectedModel(std::string n)
{
    auto selModel = getSelectedModel();//Get current selected model
    addARigidBodyEntry(n, selModel);//Add existing model with new name
    removeModel(selectedModelName);//Remove old entry
    selectModel(n);//Select new entry
}

void RigidBodiesManager::setInputModule(EditorPanel* panel)
{
    //panel->setRigidBodyManager(this);
    //_editPanel = panel;
}

void RigidBodiesManager::setInputModuleUI(EditorPanelUI* panel)
{
    //panel->setRigidBodyManager(this);
    _editPanel = panel;
}

void RigidBodiesManager::computeAllRigidBodies()
{
    for (auto it = _rbModelsMap.begin(); it != _rbModelsMap.end(); it++)
    {
        if ((*it).second->_isPhysDirty)
        {
            (*it).second->computePhysics();
        }
    }
}

void RigidBodiesManager::clearModels()
{
    while (!selectedModelName.empty())
    {
        removeSelectedModel();
    }
}

bool RigidBodiesManager::selectModel(std::string name)
{
    if (name == "")
    {
        selectedModelName = "";
        _selectedModel = nullptr;
        return false;
    }

    if (_rbModelsMap.find(name) != _rbModelsMap.end()) {
        selectedModelName = name;
        _selectedModel = _rbModelsMap.at(name);

        onSelectionChanged(name);
        return true;
    }
    return false;
}

void RigidBodiesManager::removeSelectedModel()
{
    if (selectedModelName.empty())
        return;

    _rbModelsMap.erase(selectedModelName);
    onEntryDeleted(selectedModelName);
    selectedModelName = "";
    
    if (_rbModelsMap.size() != 0)
    {
        //After deletion select a model
        selectModel((*_rbModelsMap.begin()).first);
    }
    else
        selectModel("");
}

void RigidBodiesManager::removeModel(std::string name)
{
    _rbModelsMap.erase(name);
    onEntryDeleted(name);

    if (_rbModelsMap.size() != 0)
    {
        //After deletion select a model
        selectModel((*_rbModelsMap.begin()).first);
    }
    else
        selectModel("");
}

//Add entry
void RigidBodiesManager::addARigidBodyEntry(string name)
{
    auto model = RigidBodyModel::create();
    model->name = name;
    _rbModels.pushBack(model);
    _rbModelsMap.insert(name, model);

    selectedModelName = name;

    //Callback all listeners
    onEntryAdded(name);
}

void RigidBodiesManager::addARigidBodyEntry(std::string name, RigidBodyModel* model)
{
    model->name = name;
    _rbModels.pushBack(model);
    _rbModelsMap.insert(name, model);

    //Callback all listeners
    onEntryAdded(name);
}

bool RigidBodiesManager::isNameSyntaxOk(std::string name)
{
    if (name.length() == 0)
        return false;
    if (name.back() == ' ')
        return false;
    if (name.front() == ' ')
        return false;

    return true;
}

bool RigidBodiesManager::isValidEntryName(std::string name)
{
    if (isNameSyntaxOk(name))
    {
        if (_rbModelsMap.find(name) == _rbModelsMap.end())//If the name is not found on the list
        {
            return true;
        }
    }
    return false;
}

std::string RigidBodiesManager::getErrorMessage(std::string name)
{
    std::string m;

    if (isValidEntryName(name))
    {
        return m;//Return empty string.
    }

    if (name.length() == 0)
    {
        m = "Empty name!";
    }
    else if (name.back() == ' ' || name.front() == ' ')
    {
        m = "Name must not start or end with (Whitespace)";
    }
    else if (_rbModelsMap.find(name) != _rbModelsMap.end())
    {
        m = "Name already exists.";
    }

    return m;
}

//Events

void RigidBodiesManager::onMouseInteractionFromEditor(CustomMouseEvent mEvent)
{
    CCLOG("Mouse Interaction!");

    switch (mEvent.type)
    {
    case CustomMouseEvent::EventType::DOWN:
    {
        CCLOG("Down");
        onMouseDownAtPosition(mEvent.mEvent->getLocationInView());
    }
    break;
    case CustomMouseEvent::EventType::MOVED:
        CCLOG("Moved");
        break;
    case CustomMouseEvent::EventType::UP:
        CCLOG("Up");
        break;
    default:
        break;
    };

}

void RigidBodiesManager::onMouseInteractionFromEditor(CustomMouseEvent mEvent,EditorMode mode)
{
    switch (mode)
    {
    case EditorMode::VIEW:
        break;
    case EditorMode::CREATE:
    {
        if (mEvent.type == CustomMouseEvent::EventType::DOWN)
        {
            onMouseDownAtPositionCreate(mEvent.mEvent->getLocationInView());
        }
    }
        break;
    case EditorMode::EDIT:
        break;
    case EditorMode::TEST:
        break;
    default:
        break;
    }

}

void RigidBodiesManager::onMouseDownAtPosition(Vec2 pos)
{
    auto model = getSelectedModel();

    if (model == nullptr) return;

    Vector<ShapeModel*>& shapes = model->_shapes;

    ShapeModel* lastShape = (shapes.size() == 0) ? nullptr : shapes.at(shapes.size() - 1);

    if (lastShape == nullptr || lastShape->isClosed()) {
        PolygonModel::Type type = ShapeModel::Type::POLYGON;
        lastShape = new ShapeModel(type);
        //lastShape->vertices.push_back(pos);
        
        shapes.pushBack(lastShape);

    }
    else {
        vector<Vec2>& vs = lastShape->_vertices;
        Vec2 np = pos;
        ShapeModel::Type type = lastShape->getType();

        if (vs.size() >= 3 && np == vs.at(0)) {
            lastShape->close();
            //model.computePhysics();
            //screen.buildBody();
        }
        else {
            vs.push_back(pos);
        }
    }
}

void RigidBodiesManager::onMouseDownAtPositionCreate(Vec2 pos)
{
    auto model = getSelectedModel();

    if (model == nullptr) return;

    Vector<ShapeModel*>& shapes = model->_shapes;

    ShapeModel* lastShape = (shapes.size() == 0) ? nullptr : shapes.at(shapes.size() - 1);

    if (lastShape == nullptr || lastShape->isClosed()) {
        ShapeModel::Type type = ShapeModel::Type::POLYGON;
        lastShape = new ShapeModel(type);
        lastShape->_vertices.push_back(pos);
        shapes.pushBack(lastShape);

    }
    else {
        vector<Vec2>& vs = lastShape->_vertices;
        Vec2 np = pos;
        ShapeModel::Type type = lastShape->getType();

        if (vs.size() >= 3 && np == vs.at(0)) {
            lastShape->close();
            //model.computePhysics();
            //screen.buildBody();
        }
        else {
            vs.push_back(pos);
        }
    }

}

//List events

void RigidBodiesManager::onEntryAdded(string n)
{
    for (int i = 0; i < _onEntryAddedListenerList.size(); i++)
    {
        _onEntryAddedListenerList[i](n);
    }
}

void RigidBodiesManager::onSelectionChanged(std::string n)
{
    for (int i = 0; i < onSelChangedListenerList.size(); i++)
    {
        onSelChangedListenerList[i](n);
    }
}

void RigidBodiesManager::onEntryDeleted(std::string n)
{
    for (int i = 0; i < onEntryDeletedListenerList.size(); i++)
    {
        onEntryDeletedListenerList[i](n);
    }
}
