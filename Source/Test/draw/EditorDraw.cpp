#include "EditorDraw.h"
#include "Test/EditorManager.h"
#include "Test/OverallManager.h"

USING_NS_CC;

bool EditorDraw::init()
{
    scheduleUpdate();

    _vertDraw = DrawNode::create();
    addChild(_vertDraw, 1);
	_selectionDraw = DrawNode::create();
	addChild(_selectionDraw, 1);
    _trDraw = DrawNode::create();
    addChild(_trDraw, 10);

    //Add three vertices sprites

    v00 = Sprite::create("Sprites/v00.png");
    v00->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    v00->setScale(0.75f);
    v00->setColor(Color3B::GRAY);
    addChild(v00);

    v10 = Sprite::create("Sprites/v10.png");
    v10->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    v10->setScale(0.75f);
    v10->setColor(Color3B::GRAY);
    addChild(v10);
    
    v01 = Sprite::create("Sprites/v01.png");
    v01->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    v01->setScale(0.75f);
    v01->setColor(Color3B::GRAY);
    addChild(v01);

	return true;
}

void EditorDraw::update(float dt)
{
	clearDrawNodes();
    if (!_pauseDraw)
    {
        drawModels();
    }
    positionSprites();
}

void EditorDraw::clearDrawNodes()
{
    _vertDraw->clear();
	_selectionDraw->clear();
    _trDraw->clear();
}

void EditorDraw::drawModels()
{
    drawSelectedVerts();
    drawSelectionBox();
    drawUnitVectors();
    drawMousePointers();

    //Draw nearest point to the mouse pointer
    if (editManager->nearestPoint != nullptr) {
        Vec2 t = *editManager->nearestPoint;
        editManager->oManager->spaceConv->applyT(&t);
        _vertDraw->drawDot(t, 7, Color4F::GREEN); //11
    }

    if (editManager->_hasNearClosePt)
    {
        Vec2 t = editManager->nearClosePt;
        editManager->oManager->spaceConv->applyT(&t);
        _vertDraw->drawDot(t, 7, Color4F::GREEN); //11
    }

}

void EditorDraw::drawSelectionBox()
{
    if (editManager->mSel.isValid())
    {
        Vec2 a = editManager->mSel.p1;
        Vec2 b = editManager->mSel.p2;

        _selectionDraw->drawRect(a, b, Color4F::GREEN);
        _selectionDraw->drawSolidRect(a, b, Color4F(0, 1, 0, 0.40f));
    }
}

void EditorDraw::positionSprites()
{
    Vec2 a;

    editManager->oManager->spaceConv->applyT(&a);
    v00->setPosition(a);

    a.set(500, 0);
    editManager->oManager->spaceConv->applyT(&a);
    v10->setPosition(a);

    a.set(0, 500);
    editManager->oManager->spaceConv->applyT(&a);
    v01->setPosition(a);

}

void EditorDraw::drawMousePointers()
{
    if (editManager->_mode != EditorMode::CREATE)return;

    //Draw mouse pointer
    Vec2 a = editManager->mouseLocation;
    Size dotSize(5, 5);
    _vertDraw->drawRect(a - dotSize, a + dotSize, Color4F::BLUE);

}

void EditorDraw::drawSelectedVerts()
{
    std::vector<Vec2*>& points = editManager->selectedPoints;

    for (auto point : points)
    {
        Vec2 v(*point);
        editManager->oManager->spaceConv->applyT(&v);
        _vertDraw->drawDot(v, 5, Color4F::GREEN);

    }
}

void EditorDraw::drawUnitVectors()
{
    Vec2 a, b;
    _trDraw->clear();
    _trDraw->setLineWidth(3);
    //Draw X axis
    {
        b.set(500, 0);
        editManager->oManager->spaceConv->applyT(&a);
        editManager->oManager->spaceConv->applyT(&b);
        _trDraw->drawLine(a, b, Color4F::GRAY);
        _trDraw->drawLine(b, b + Vec2(-10, -10), Color4F::GRAY);
        _trDraw->drawLine(b, b + Vec2(-10, 10), Color4F::GRAY);
    }
    //Draw Y axis
    {
        b.set(0, 500);
        editManager->oManager->spaceConv->applyT(&b);
        _trDraw->drawLine(a, b, Color4F::GRAY);
        _trDraw->drawLine(b, b + Vec2(-10, -10), Color4F::GRAY);
        _trDraw->drawLine(b, b + Vec2(10, -10), Color4F::GRAY);
    }
}

void EditorDraw::pauseDrawing(bool val)
{
    if (val)
    {
        _pauseDraw = true;
        v00->setVisible(false);
        v10->setVisible(false);
        v01->setVisible(false);
    }
    else
    {
        _pauseDraw = false;
        v00->setVisible(true);
        v10->setVisible(true);
        v01->setVisible(true);
    }
}