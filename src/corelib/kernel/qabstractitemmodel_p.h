/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QABSTRACTITEMMODEL_P_H
#define QABSTRACTITEMMODEL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QAbstractItemModel*.  This header file may change from version
// to version without notice, or even be removed.
//
// We mean it.
//
//

#include "private/qobject_p.h"
#include "QtCore/qstack.h"
#include "QtCore/qset.h"
#include "QtCore/qhash.h"

QT_BEGIN_NAMESPACE

class Q_CORE_EXPORT QPersistentModelIndexData
{
public:
    QPersistentModelIndexData() : model(0) {}
    QPersistentModelIndexData(const QModelIndex &idx) : index(idx), model(idx.model()) {}
    QModelIndex index;
    QAtomicInt ref;
    const QAbstractItemModel *model;
    static QPersistentModelIndexData *create(const QModelIndex &index);
    static void destroy(QPersistentModelIndexData *data);
};

class Q_CORE_EXPORT QAbstractItemModelPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QAbstractItemModel)

public:
    QAbstractItemModelPrivate() : QObjectPrivate(), supportedDragActions(-1) {}
    void removePersistentIndexData(QPersistentModelIndexData *data);
    void rowsAboutToBeInserted(const QModelIndex &parent, int first, int last);
    void rowsInserted(const QModelIndex &parent, int first, int last);
    void rowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void rowsRemoved(const QModelIndex &parent, int first, int last);
    void columnsAboutToBeInserted(const QModelIndex &parent, int first, int last);
    void columnsInserted(const QModelIndex &parent, int first, int last);
    void columnsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void columnsRemoved(const QModelIndex &parent, int first, int last);
    static QAbstractItemModel *staticEmptyModel();

    inline QModelIndex createIndex(int row, int column, void *data = 0) const {
        return q_func()->createIndex(row, column, data);
    }

    inline QModelIndex createIndex(int row, int column, int id) const {
        return q_func()->createIndex(row, column, id);
    }

    inline bool indexValid(const QModelIndex &index) const {
         return (index.row() >= 0) && (index.column() >= 0) && (index.model() == q_func());
    }

    inline void invalidatePersistentIndexes() {
        foreach (QPersistentModelIndexData *data, persistent.indexes) {
            data->index = QModelIndex();
            data->model = 0;
        }
        persistent.indexes.clear();
    }

    /*!
      \internal
      clean the QPersistentModelIndex relative to the index if there is one.
      To be used before an index is invalided
      */
    inline void invalidatePersistentIndex(const QModelIndex &index) {
        QHash<QModelIndex, QPersistentModelIndexData *>::iterator it = persistent.indexes.find(index);
        if(it != persistent.indexes.end()) {
            QPersistentModelIndexData *data = *it;
            persistent.indexes.erase(it);
            data->index = QModelIndex();
            data->model = 0;
        }
    }

    struct Change {
        Change() : first(-1), last(-1) {}
        Change(const Change &c) : parent(c.parent), first(c.first), last(c.last) {}
        Change(const QModelIndex &p, int f, int l) : parent(p), first(f), last(l) {}
        QModelIndex parent;
        int first, last;
    };
    QStack<Change> changes;

    struct Persistent {
        Persistent() {}
        QHash<QModelIndex, QPersistentModelIndexData *> indexes;
        QStack<QVector<QPersistentModelIndexData *> > moved;
        QStack<QVector<QPersistentModelIndexData *> > invalidated;
        void insertMultiAtEnd(const QModelIndex& key, QPersistentModelIndexData *data);
    } persistent;

    Qt::DropActions supportedDragActions;
};

QT_END_NAMESPACE

#endif // QABSTRACTITEMMODEL_P_H
