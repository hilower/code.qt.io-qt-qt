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

#include <QImage>
#include <QList>
#include <QThread>
#include <QDebug>
#include <QApplication>
#include <qtconcurrentmap.h>

#ifndef QT_NO_CONCURRENT

QImage scale(const QImage &image)
{
    qDebug() << "Scaling image in thread" << QThread::currentThread();
    return image.scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const int imageCount = 20;

    // Create a list containing imageCount images.
    QList<QImage> images;
    for (int i = 0; i < imageCount; ++i)
        images.append(QImage(1600, 1200, QImage::Format_ARGB32_Premultiplied));

    // Use QtConcurrentBlocking::mapped to apply the scale function to all the
    // images in the list.
    QList<QImage> thumbnails = QtConcurrent::blockingMapped(images, scale);

    return 0;
}

#else

int main()
{
	qDebug() << "Qt Concurrent is not yet supported on this platform";
}

#endif
