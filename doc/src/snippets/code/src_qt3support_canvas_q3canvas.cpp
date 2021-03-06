/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
QPrinter pr;
if (pr.setup()) {
    QPainter p(&pr);
    canvas.drawArea(canvas.rect(), &p);
}
//! [0]


//! [1]
void MyCanvasView::contentsMousePressEvent(QMouseEvent* e)
{
    Q3CanvasItemList l = canvas()->collisions(e->pos());
    for (Q3CanvasItemList::Iterator it=l.begin(); it!=l.end(); ++it) {
        if ((*it)->rtti() == Q3CanvasRectangle::RTTI)
            qDebug("A Q3CanvasRectangle lies somewhere at this point");
    }
}
//! [1]


//! [2]
QMatrix wm;
wm.scale(2, 2);   // Zooms in by 2 times
wm.rotate(90);    // Rotates 90 degrees counter clockwise
                  // around the origin.
wm.translate(0, -canvas->height());
                  // moves the canvas down so what was visible
                  // before is still visible.
myCanvasView->setWorldMatrix(wm);
//! [2]


//! [3]
QRect rc = QRect(myCanvasView->contentsX(), myCanvasView->contentsY(),
                 myCanvasView->visibleWidth(), myCanvasView->visibleHeight());
QRect canvasRect = myCanvasView->inverseWorldMatrix().mapRect(rc);
//! [3]


//! [4]
Q3CanvasItem* item;
// Find an item, e.g. with Q3CanvasItem::collisions().
...
if (item->rtti() == MySprite::RTTI) {
    MySprite* s = (MySprite*)item;
    if (s->isDamagable()) s->loseHitPoints(1000);
    if (s->isHot()) myself->loseHitPoints(1000);
    ...
}
//! [4]
