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

#include <QApplication>
#include <QUiLoader>
#include <QtScript>
#include <QWidget>
#include <QFile>
#include <QMainWindow>
#include <QLineEdit>

#ifndef QT_NO_SCRIPTTOOLS
#include <QScriptEngineDebugger>
#endif

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(calculator);

    QApplication app(argc, argv);
//! [0a]
    QScriptEngine engine;
//! [0a]

#ifndef QT_NO_SCRIPTTOOLS
    QScriptEngineDebugger debugger;
    debugger.attachTo(&engine);
    QMainWindow *debugWindow = debugger.standardWindow();
    debugWindow->resize(1024, 640);
#endif

//! [0b]
    QString scriptFileName(":/calculator.js");
    QFile scriptFile(scriptFileName);
    scriptFile.open(QIODevice::ReadOnly);
    engine.evaluate(scriptFile.readAll(), scriptFileName);
    scriptFile.close();
//! [0b]

//! [1]
    QUiLoader loader;
    QFile uiFile(":/calculator.ui");
    uiFile.open(QIODevice::ReadOnly);
    QWidget *ui = loader.load(&uiFile);
    uiFile.close();
//! [1]

//! [2]
    QScriptValue ctor = engine.evaluate("Calculator");
    QScriptValue scriptUi = engine.newQObject(ui, QScriptEngine::ScriptOwnership);
    QScriptValue calc = ctor.construct(QScriptValueList() << scriptUi);
//! [2]

#ifndef QT_NO_SCRIPTTOOLS
    QLineEdit *display = qFindChild<QLineEdit*>(ui, "display");
    QObject::connect(display, SIGNAL(returnPressed()),
                     debugWindow, SLOT(show()));
#endif
//! [3]
    ui->show();
    return app.exec();
//! [3]
}
