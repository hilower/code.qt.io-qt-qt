/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QRectF>

#include <private/qdatabuffer_p.h>
#include <private/qvectorpath_p.h>
#include <private/qgl_p.h>

class QGLPoint
{
public:
    QGLPoint(GLfloat new_x, GLfloat new_y) :
        x(new_x), y(new_y) {};

    QGLPoint(QPointF p) :
        x(p.x()), y(p.y()) {};

    QGLPoint(const QPointF* p) :
        x(p->x()), y(p->y()) {};

    GLfloat x;
    GLfloat y;

    operator QPointF() {return QPointF(x,y);}
    operator QPointF() const {return QPointF(x,y);}
};

struct QGLRect
{
    QGLRect(QRectF r)
        :  left(r.left()), top(r.top()), right(r.right()), bottom(r.bottom()) {}

    QGLRect(GLfloat l, GLfloat t, GLfloat r, GLfloat b)
        : left(l), top(t), right(r), bottom(b) {}

    GLfloat left;
    GLfloat top;
    GLfloat right;
    GLfloat bottom;

    operator QRectF() {return QRectF(left, top, right-left, bottom-top);}
};

class QGL2PEXVertexArray
{
public:
    QGL2PEXVertexArray() :
        maxX(-2e10), maxY(-2e10), minX(2e10), minY(2e10),
        boundingRectDirty(true) {}

    void addPath(const QVectorPath &path, GLfloat curveInverseScale);
    void clear();

    QGLPoint*        data() {return vertexArray.data();}
    QVector<int>&   stops() {return vertexArrayStops;}
    QGLRect         boundingRect() const;

    void lineToArray(const GLfloat x, const GLfloat y);

private:
    QDataBuffer<QGLPoint> vertexArray;
    QVector<int>          vertexArrayStops;

    GLfloat     maxX;
    GLfloat     maxY;
    GLfloat     minX;
    GLfloat     minY;
    bool        boundingRectDirty;

    inline void curveToArray(const QGLPoint &cp1, const QGLPoint &cp2, const QGLPoint &ep, GLfloat inverseScale);
};
