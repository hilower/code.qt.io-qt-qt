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
QSslSocket *socket = new QSslSocket(this);
connect(socket, SIGNAL(encrypted()), this, SLOT(ready()));

socket->connectToHostEncrypted("imap.example.com", 993);
//! [0]


//! [1]
void SslServer::incomingConnection(int socketDescriptor)
{
    QSslSocket *serverSocket = new QSslSocket;
    if (serverSocket->setSocketDescriptor(socketDescriptor)) {
        connect(serverSocket, SIGNAL(encrypted()), this, SLOT(ready()));
        serverSocket->startServerEncryption();
    } else {
        delete serverSocket;
    }
}
//! [1]


//! [2]
QSslSocket socket;
socket.connectToHostEncrypted("http.example.com", 443);
if (!socket.waitForEncrypted()) {
    qDebug() << socket.errorString();
    return false;
}

socket.write("GET / HTTP/1.0\r\n\r\n");
while (socket.waitForReadyRead())
    qDebug() << socket.readAll().data();
//! [2]


//! [3]
QSslSocket socket;
connect(&socket, SIGNAL(encrypted()), receiver, SLOT(socketEncrypted()));

socket.connectToHostEncrypted("imap", 993);
socket->write("1 CAPABILITY\r\n");
//! [3]


//! [4]
QSslSocket socket;
socket.setCiphers("DHE-RSA-AES256-SHA:DHE-DSS-AES256-SHA:AES256-SHA");
//! [4]


//! [5]
socket->connectToHostEncrypted("imap", 993);
if (socket->waitForEncrypted(1000))
    qDebug("Encrypted!");
//! [5]
