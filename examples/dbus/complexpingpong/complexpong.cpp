/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
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

#include <stdio.h>
#include <stdlib.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtDBus/QtDBus>

#include "ping-common.h"
#include "complexpong.h"

// the property
QString Pong::value() const
{
    return m_value;
}

void Pong::setValue(const QString &newValue)
{
    m_value = newValue;
}

void Pong::quit()
{
    QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));
}

QDBusVariant Pong::query(const QString &query)
{
    QString q = query.toLower();
    if (q == "hello")
        return QDBusVariant("World");
    if (q == "ping")
        return QDBusVariant("Pong");
    if (q.indexOf("the answer to life, the universe and everything") != -1)
        return QDBusVariant(42);
    if (q.indexOf("unladen swallow") != -1) {
        if (q.indexOf("european") != -1)
            return QDBusVariant(11.0);
        return QDBusVariant(QByteArray("african or european?"));
    }

    return QDBusVariant("Sorry, I don't know the answer");
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QObject obj;
    Pong *pong = new Pong(&obj);
    pong->connect(&app, SIGNAL(aboutToQuit()), SIGNAL(aboutToQuit()));
    pong->setProperty("value", "initial value");
    QDBusConnection::sessionBus().registerObject("/", &obj);

    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));        
        exit(1);
    }
    
    app.exec();
    return 0;
}

