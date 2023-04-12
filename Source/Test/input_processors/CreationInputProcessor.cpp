#include "CreationInputProcessor.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "Test/UI/EditorScreenInterface.h"
#include "../EditorManager.h"
#include "../PointSpaceNode.h"
#include "Test/OverallManager.h"

void CreationInputProcessor::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);
}

void CreationInputProcessor::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    processPanning(e);

    //_editorPanel->_drawNode->_nearestPoint.set(0, 0);///////////////////!!!!!!!!!

    RigidBodyModel* model = editManager->rbManager->getSelectedModel();
    if (model == nullptr) return;
    
    auto shapes = model->_shapes;
    
    ShapeModel* lastShape = shapes.empty() ? nullptr : shapes.at(shapes.size() - 1);
    
    if (lastShape != nullptr&&lastShape->type==ShapeModel::Type::POLYGON) {
        auto vs = ((PolygonModel*)lastShape)->_vertices;
    
        if (!lastShape->isClosed() && vs.size() >= 3) {
            
            Vec2 t = e.mEvent->getLocationInView();
            //_editorPanel->oManager->spaceConv->applyTInv(&t);//Apply transform
            
            Vec2 w = vs.at(0);
            _editorPanel->oManager->spaceConv->applyT(&w);//Apply transform
    
            if (w.distance(t) < 25.f)
            {
                //_editorPanel->_drawNode->_nearestPoint.set(vs.at(0));!!!!!!!!!!!
                editManager->setNearestClosingPt(true, vs.at(0));
            }
            else
            {
                editManager->setNearestClosingPt(false, Vec2::ZERO);
            }
        }
    }
}

void CreationInputProcessor::onMouseDown(CustomMouseEvent e)
{
    EditorInputProcessor::onMouseDown(e);

    if (e.mEvent->getMouseButton() != EventMouse::MouseButton::BUTTON_LEFT)
        return;

    RigidBodyModel* model = editManager->rbManager->getSelectedModel();
    if (model == nullptr) return;
    
    cocos2d::Vector<ShapeModel*>& shapes = model->_shapes;
    
    ShapeModel* lastShape = shapes.empty() ? nullptr : shapes.at(shapes.size() - 1);
    
    //If last shape is nullptr or closed
    if (lastShape == nullptr || lastShape->isClosed()) {
        ShapeModel::Type type = ShapeModel::Type::POLYGON;
        lastShape = new ShapeModel(type);
    
        Vec2 wMid = _editorPanel->getWorldViewPortMidpoint();
        //Vec2 norm = e.mEvent->getLocationInView() - wMid;
        Vec2 norm = e.mEvent->getLocationInView();
        //_editorPanel->oManager->buffDelegate->applyNewInvTransform(&norm);
        _editorPanel->oManager->spaceConv->applyTInv(&norm);
        //lastShape->_vertices.push_back(e.mEvent->getLocationInView());
        lastShape->_vertices.push_back(norm);
        shapes.pushBack(lastShape);
    
    }
    else {
        std::vector<Vec2>& vs = lastShape->_vertices;
        //Vec2 np = screen.nearestPoint;
        Vec2 np;
        ShapeModel::Type type = lastShape->getType();
    
        if (type == ShapeModel::Type::POLYGON && vs.size() >= 3) {
    
            Vec2 wMid = _editorPanel->getWorldViewPortMidpoint();
            Vec2 norm = e.mEvent->getLocationInView();
            _editorPanel->oManager->spaceConv->applyTInv(&norm);
            //If close the shape
    
            Vec2 w = vs.at(0);
            _editorPanel->oManager->spaceConv->applyT(&w);//Apply transform
    
            if (w.distance(e.mEvent->getLocationInView()) < 25.f)
            {
                lastShape->close();
            }
            else
            {
                vs.push_back(norm);
            }
            //model.computePhysics();
            //screen.buildBody();
        }
        else
        {
            Vec2 wMid = _editorPanel->getWorldViewPortMidpoint();
            Vec2 norm = e.mEvent->getLocationInView() ;
            //_editorPanel->oManager->buffDelegate->applyNewInvTransform(&norm);
            _editorPanel->oManager->spaceConv->applyTInv(&norm);
            vs.push_back(norm);
        }
    }
    
    editManager->setNearestClosingPt(false, Vec2::ZERO);
    //Set model as save dirty
    model->setSaveDirty(true);
    model->_isPhysDirty = true;
}

void CreationInputProcessor::onMouseScroll(CustomMouseEvent e)
{
    processZooming(e);
}

void CreationInputProcessor::processPanning(CustomMouseEvent e)
{
    if (_editorPanel->_screenInterface->isRMBPressed())
    {
        //auto pN = editManager->pointsNode;
        Vec2 delta = e.mEvent->getLocationInView() - editManager->prevMousePoint;

        float sc = _editorPanel->oManager->spaceConv->scale;

        //pN->setPosition(pN->getPosition() + delta);
        //_editorPanel->oManager->buffDelegate->addOffset(delta * sc);
        //_editorPanel->oManager->buffDelegate->refreshMat();
        //_editorPanel->oManager->buffDelegate->validateNewTransform();

        //New!
        _editorPanel->oManager->spaceConv->addOffset(delta * (1 / sc));
        _editorPanel->oManager->spaceConv->validateMatrices();
    }
}

void CreationInputProcessor::processZooming(CustomMouseEvent e)
{
    //CCLOG("Scroll y: %f", e.mEvent->getScrollY());
    auto pN = editManager->pointsNode;
    
    float scrDt = e.mEvent->getScrollY() * -0.1f * 2;//<-Scroll speed multiplier
    //float sc = pN->getScale() + scrDt;
    
    float sc = _editorPanel->oManager->spaceConv->scale + scrDt;
    
    sc = max(0.1f, sc);
    sc = min(10.0f, sc);
    
    //CCLOG("%f",sc);
    
    //pN->setScale(sc);
    
    //_editorPanel->oManager->buffDelegate->applyScale(sc);
    //_editorPanel->oManager->buffDelegate->refreshMat();
    //_editorPanel->oManager->buffDelegate->validateNewTransform();
    
    //New!
    _editorPanel->oManager->spaceConv->applyScale(sc);
    _editorPanel->oManager->spaceConv->validateMatrices();

}
