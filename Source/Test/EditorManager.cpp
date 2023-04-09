#include "EditorManager.h"
#include "PointSpaceNode.h"
#include "EditorPanelUI.h"
#include "RigidBodyModel.h"
#include "RigidBodiesManager.h"
#include "EditorScreenInterface.h"
#include "OverallManager.h"
#include "draw/EditorDraw.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool EditorManager::init()
{
	//_pointsNode = PointSpaceNode::create();
	//addChild(_pointsNode);

    nearestPoint = nullptr;
    _hasNearClosePt = false;
	
	return true;
}

void EditorManager::resetPointSpace()
{
	pointsNode->setPosition(editorUI->getWorldViewPortMidpoint());
}

void EditorManager::validateNearestPoint(const Vec2& pt)
{
    RigidBodyModel* model = editorUI->_rbManager->getSelectedModel();
    if (model == nullptr) return;

    Vec2 p = pt;

    //if (editorUI->_screenInterface->nearestPoint != nullptr)
    //{
    //    Vec2** a = &_editorPanel->_screenInterface->nearestPoint;
    //    *a = nullptr;
    //}

    nearestPoint = nullptr;

    float dist = 100 * 1; //canvas.worldCamera.zoom;


    //for (Vec2* v : allPointsBuffer) {
    //
    //    Vec2 tV = *v;
    //
    //    if (tV.distanceSquared(p) < dist)
    //    {
    //        _editorPanel->_screenInterface->nearestPoint = v;
    //    }
    //
    //}

    for (ShapeModel* shape : model->_shapes) {

        for (int i = 0; i < shape->_vertices.size(); i++)
        {
            Vec2* v = &shape->_vertices.at(i);
            
            if (v->distanceSquared(p) < dist)
            {
                nearestPoint = v;
            }
        }
    }

}

bool EditorManager::isSelectedPointsContain(Vec2 p)
{
    size_t s = selectedPoints.size();

    for (size_t i = 0; i < s; i++)
    {
        if ((*selectedPoints[i]) == p) //Could be used fuzzy equals
            return true;
    }
    return false;
}

void EditorManager::selectedPointsReplaceBy(Vec2* p)
{
    selectedPoints.clear();
    selectedPoints.push_back(p);
}

void EditorManager::selectPointsInMouseSelection()
{
    RigidBodyModel* model = editorUI->_rbManager->getSelectedModel();

    //Not sure if its required
    selectedPoints.clear();

    Vec2 p1 = mSel.p1;
    Vec2 p2 = mSel.p2;

    //Convert both to logic space
    editorUI->oManager->spaceConv->applyTInv(&p1);
    editorUI->oManager->spaceConv->applyTInv(&p2);

    if (mSel.isValid()) 
    {
        Rect rect(
            min(p1.x, p2.x),
            min(p1.y, p2.y),
            abs(p2.x - p1.x),
            abs(p2.y - p1.y)
        );

        for (ShapeModel* shape : model->_shapes) {//for each shape

            for (int i = 0; i < shape->_vertices.size(); i++)
            {
                Vec2* p = &shape->_vertices.at(i);

                if (rect.containsPoint(*p))
                {
                    selectedPoints.push_back(p);
                }
            }
        }
    }
}

void EditorManager::removeSelectedPoints()
{
    if (!isRemoveEnabled())
        return;

    auto& shapes = oManager->rbManager->getSelectedModel()->_shapes;
    
    //Make a copy of the original selected points
    std::vector<Vec2> selCopy;
    selCopy.reserve(selectedPoints.size());
    for (Vec2* p : selectedPoints) 
    {
        selCopy.push_back(*p);
    }

    for (int i = shapes.size() - 1; i >= 0; i--) { //For each shape in selected rb
        ShapeModel* shape = shapes.at(i);

        for (Vec2 p : selCopy) { //For each selected point

            //Check if p is found in shapes vertices
            bool f = (std::find(shape->_vertices.begin(), shape->_vertices.end(), p) != shape->_vertices.end());

            if (f) {
                auto it = std::find(shape->_vertices.begin(), shape->_vertices.end(), p);
                shape->_vertices.erase(it);
            }
        }

        if (shape->_vertices.empty())
            shapes.erase(i);

    }

    selectedPoints.clear();
    oManager->rbManager->getSelectedModel()->computePhysics();

}

bool EditorManager::isRemoveEnabled()
{
    if (oManager->rbManager->getSelectedModel() == nullptr)
        return false;
    return !selectedPoints.empty();
}

void EditorManager::setNearestClosingPt(bool avail,const ax::Vec2& v)
{
    _hasNearClosePt = avail;
    nearClosePt = v;
}

//-------------------
//Events
//-------------------

void EditorManager::onChangeToPlayMode()
{
    drawer->pauseDrawing(true);
}

void EditorManager::onChangeFromPlayMode()
{
    drawer->pauseDrawing(false);
}
