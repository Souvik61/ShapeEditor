#include "Test/EventManager.h"
#include "Test/OverallManager.h"
#include "Utils/FileDialogs.h"
#include "Test/UI/PlayTabLayout.h"
#include "ShapesDrawNode.h"
#include "NewShapesDrawNode.h"
#include "AppDelegate.h"
#include "StateTracker.h"
#include "EditorManager.h"

//------------------------
//Event Manager
//------------------------

EventManager::EventManager() :
	_dialogSystem(nullptr), oManager(nullptr), currentState(State::NONE)
{
	panelUI = nullptr;
	//currentState = State::NONE;
}

bool EventManager::init()
{
	//scheduleUpdate();
	return true;
}

void EventManager::update(float dt)
{
	Node::update(dt);
	
}

void EventManager::onEnter()
{
	Node::onEnter();

	oManager->editSystem->resetPointSpace();

	_listener = EventListenerCustom::create("close", [this](EventCustom* event) {
		this->onWinCloseBtnPressed();
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

}

void EventManager::onExit()
{
	_eventDispatcher->removeEventListener(_listener);

	Node::onExit();
}

void EventManager::setDialogWindowSystem(DialogWindowSystem* dS)
{
	_dialogSystem = dS;
	_dialogSystem->onRenameWindowBtnEvent = CC_CALLBACK_1(EventManager::onBtnPressFromWindow, this);
}

//------------------
//RbPanel Events
//------------------

void EventManager::onButtonPressFromRbPanel(std::string btnName)
{
	//If no project loaded
	if (!oManager->prjManager->isProjectLoaded()) {
		oManager->uiSystem->notifSys->showNotification("No project loaded.");
		return;
	}

	if (btnName == "btn_add")
	{
		//Add an entry to list
		onAddButtonPressedOnRbPanel();
	}
	else if (btnName == "btn_del")
	{
		//Remove selected model
		//oManager->rbManager->removeSelectedModel();
		onDelButtonPressedOnRbPanel();
	}
	else if (btnName == "btn_ren")
	{
		//Rename
		onRenButtonPressedOnRbPanel();
	}
}

void EventManager::onAListingClickedFromRbPanel(std::string n)
{
	oManager->rbManager->selectModel(n);
}

void EventManager::onSpwnButtonFromRbPanel(std::string n)
{
	//Spawn n in b2d world :-)
	//CCLOG("Spawn %s",n.c_str());
	
	bool res = oManager->spwnManager->spawnBody(n, Vec2(500, 500));

	if (!res) {
		//CCLOG("Error in shape data!");
		oManager->uiSystem->notifSys->showNotification("Error in shape data!");
	}

}

void EventManager::onAddButtonPressedOnRbPanel()
{
	if (oManager->prjManager->isProjectLoaded())
	{
		_dialogSystem->showRenameDialog();
		//oManager->uiSystem->editPanelUI->pauseInput(true);
		currentState = State::WAIT_FOR_ADD;
	}
}

void EventManager::onDelButtonPressedOnRbPanel()
{
	if (oManager->prjManager->isProjectLoaded())
	{
		oManager->rbManager->removeSelectedModel();
	}
}

void EventManager::onRenButtonPressedOnRbPanel()
{
	if (oManager->prjManager->isProjectLoaded())
	{
		_dialogSystem->showRenameDialog();
		//oManager->editorPanel->pauseInput(true);
		//oManager->uiSystem->editPanelUI->pauseInput(true);
		currentState = State::WAIT_FOR_REN;
	}
}

//-----------------------
//Project panel events
//-----------------------

void EventManager::onBtnPressedFromPrjPanel(std::string btnName)
{
	if (btnName == "ic_save")
	{
		onSaveBtnPressed();
	}
	else if (btnName == "ic_load")//"ic_open" is now "ic_load"
	{
		onLoadBtnPressed();
	}
	else if (btnName == "ic_new")
	{
		onNewBtnPressed();
	}
	else if (btnName == "ic_fopen")
	{
		onOpenInExplorer();
	}
	else if (btnName == "ic_help")
	{
		//Display help message
		dynamic_cast<AppDelegate*>(Application::getInstance())->displayHelpText();
	}
}

void EventManager::onSaveBtnPressed()
{
	onSaveToDisk();
}

void EventManager::onLoadBtnPressed()
{
	//Prompt windows file dialog
	//FileDialogs::saveFile("JSON (*.json)\0*.json\0");
	onLoadFromDisk();
}

void EventManager::onNewBtnPressed()
{
	onNewProject();
}

void EventManager::onOpenInExplorer()
{
	if (!oManager->prjManager->isProjectLoaded()) {
		oManager->uiSystem->notifSys->showNotification("No project loaded.");
		return;
	}
		auto url = oManager->prjManager->prjFilePath;
		Application::getInstance()->openURL(url);////Open build folder by default, later change it.
	
}

//----------------------
//RenameWindow events
//----------------------

void EventManager::onBtnPressFromWindow(std::string s)
{
	if (s == "ok")
		onRenameOkBtnPress();
	else
		onRenameCancelBtnPress();
}

void EventManager::onRenameOkBtnPress()
{
	if (currentState == State::WAIT_FOR_ADD)
	{
		addRbEntry();
	}
	else if (currentState == State::WAIT_FOR_REN)
	{
		renRbEntry();
	}
	//currentState = State::NONE;
}

void EventManager::onRenameCancelBtnPress()
{
	_dialogSystem->closeRenameDialog();
	//oManager->editorPanel->pauseInput(false);
	//oManager->uiSystem->editPanelUI->pauseInput(false);
	currentState = State::NONE;
}

//---------------

void EventManager::onTabChanged(int index)
{
	if (index == 1) { //Change to play tab
	
		//oManager->uiSystem->editPanelUI->changeModeDisabled();//Disable editor panel
		
		oManager->uiSystem->editPanelUI->changeModeUI(EditorMode::TEST);//Disable editor panel

		//((NewShapesDrawNode*)oManager->uiSystem->editPanelUI->_drawNode)->pauseDrawing(true);//Pause drawing
		oManager->editSystem->onChangeToPlayMode();

		oManager->b2dManager->activateWorld();
		
		//Need to see this!!!!!!!!!!!!!!!!!!!!!
		//oManager->uiSystem->rbPanelUI->_rbListController->enableSpawnMode(true);

		//Patch!!
		oManager->backGrid->setVisible(false);

	}
	else { //Change to edit tab
	
		oManager->b2dManager->deactivateWorld();
		

		//((NewShapesDrawNode*)oManager->uiSystem->editPanelUI->_drawNode)->pauseDrawing(false);//Resume drawing
		oManager->editSystem->onChangeFromPlayMode();

		oManager->uiSystem->editPanelUI->changeToModeFromPlay();//Enable Editor panel

		//Need to see this!!!!!!!!!!!!!!!!!!!!!
		//oManager->uiSystem->rbPanelUI->_rbListController->enableSpawnMode(false);

		//Patch!!
		oManager->backGrid->setVisible(true);

	}
}

void EventManager::onPlayTabCtrlEvent(std::string btnName)
{
	//Clear physics world button pressed
	if (btnName == "clear") {
	
		oManager->b2dManager->clearWorld();
	}
}

//-------------------
//Core Events
//-------------------

void EventManager::onWinCloseBtnPressed()
{
	//If not dirty return
	if (!oManager->sTracker->isSaveDirty())
	{
		_director->end();
		return;
	}
	
	int id = savePromptRoutine();

	if (id == IDYES)
	{
		CCLOG("Yes");
		onSaveToDisk();
		_director->end();
	}
	else if (id == IDNO)
	{
		CCLOG("No");
		_director->end();
	}
	else if (id == IDCLOSE || id == IDCANCEL)
	{
		CCLOG("Close/Cancel");
		//Do nothing
	}

}

void EventManager::onShowRenameDialog()
{
}

void EventManager::onHideRenameDialog()
{
	//oManager->editorPanel->pauseInput(false);
	//oManager->uiSystem->editPanelUI->pauseInput(false);
}

//------------------
//--Project Events
//------------------

void EventManager::onNewProject()
{

	if (oManager->sTracker->isSaveDirty()) {

		int id = savePromptRoutine();

		if (id == IDYES)
		{
			onSaveToDisk();
		}
		else if (id == IDNO)
		{
		}
		else if (id == IDCLOSE || id == IDCANCEL)
		{
			//Do nothing
			return;
		}
	}

	std::string fP = FileDialogs::saveFile("JSON (*.json)\0*.json\0");
	//CCLOG(fP.c_str());
	if (!fP.empty())
	{
		oManager->rbManager->clearModels();//Clear existing models in buffer.
		oManager->prjManager->setProjectPath(fP);
		std::string a = oManager->prjManager->projectName;
		oManager->uiSystem->prjPanelUI->setProjectNameText(a);
	}
}

void EventManager::onSaveToDisk()
{
	//oManager->jsonIo->exportToFile();

	//If no project loaded
	if (!oManager->prjManager->isProjectLoaded()) {

		oManager->uiSystem->notifSys->showNotification("No project loaded.");
		return;
	}

	//Validate all rigid body model before saving
	oManager->rbManager->computeAllRigidBodies();

	oManager->prjManager->saveFile();

	oManager->sTracker->setAllModelClean();

	//Show saved notification
	oManager->uiSystem->notifSys->showNotification("Saved.");
}

void EventManager::onLoadFromDisk()
{
	//oManager->jsonIo->importFromFile();
	//oManager->prjManager->loadFile();
	//std::string a = oManager->prjManager->projectName;
	//oManager->prjPanelSys->showSelectedProjectName(a);
	std::string fP = FileDialogs::openFile("JSON (*.json)\0*.json\0");

	if (!fP.empty())
	{
		oManager->rbManager->clearModels();
		oManager->prjManager->loadFileNew(fP);
		
		//Set ui panel display of project name
		std::string a = oManager->prjManager->projectName;
		oManager->uiSystem->prjPanelUI->setProjectNameText(a);

		oManager->rbManager->selectModelByIndex(0);
	}

}

////------------------
////--Project Events -end
////------------------

void EventManager::addRbEntry()
{
	//Determine if given name is valid. If valid add to list else show an error.
		//Get string from rename window
	auto g = oManager->dialogWindowSystem->getCurrentDialog()->_promptWindow->_textField->getString();
	
	std::string n{ g };

	bool valid = oManager->rbManager->isValidEntryName(n);
	if (valid)
	{
		oManager->rbManager->addARigidBodyEntry(n);
		oManager->dialogWindowSystem->closeRenameDialog();
		//oManager->editorPanel->pauseInput(false);
		//oManager->uiSystem->editPanelUI->pauseInput(false);
		currentState = State::NONE;
	}
	else
	{
		auto msg = oManager->rbManager->getErrorMessage(n);
		std::string msgStr{ msg };

		oManager->dialogWindowSystem->getCurrentDialog()->_promptWindow->showWarning(msgStr);
		currentState = State::WAIT_FOR_ADD;
	}
}

void EventManager::renRbEntry()
{
	//Determine if given name is valid. If valid rename else show an error.
	//Get string from rename window
	auto g = oManager->dialogWindowSystem->getCurrentDialog()->_promptWindow->_textField->getString();
	
	std::string gStr{ g };

	if (g == oManager->rbManager->selectedModelName)//No need to rename
	{
		oManager->dialogWindowSystem->closeRenameDialog();
		return;
	}


	bool valid = oManager->rbManager->isValidEntryName(gStr);
	if (valid)
	{
		oManager->rbManager->renameSelectedModel(gStr);
		//oManager->rbManager->selectModel(g);
		oManager->dialogWindowSystem->closeRenameDialog();
		//oManager->editorPanel->pauseInput(false);
		//oManager->uiSystem->editPanelUI->pauseInput(false);
		currentState = State::NONE;
	}
	else
	{
		auto msg = oManager->rbManager->getErrorMessage(gStr);
		oManager->dialogWindowSystem->getCurrentDialog()->_promptWindow->showWarning(msg);
		currentState = State::WAIT_FOR_REN;
	}
}


//-----------
//Others
//-----------

int EventManager::savePromptRoutine()
{
	int id = dynamic_cast<AppDelegate*>(Application::getInstance())->displayConfirmSaveAsMessageBox();

	return id;
	/*
	if (id == IDYES)
	{
		CCLOG("Yes");
		onSaveToDisk();
		_director->end();
	}
	else if (id == IDNO)
	{
		CCLOG("No");
		_director->end();
	}
	else if (id == IDCLOSE || id == IDCANCEL)
	{
		CCLOG("Close/Cancel");
		//Do nothing
	}
	*/
}

