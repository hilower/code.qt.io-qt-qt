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

/*
 * KAsteroids - Copyright (c) Martin R. Jones 1997
 *
 * Part of the KDE project
 */

#ifndef __KAST_TOPLEVEL_H__
#define __KAST_TOPLEVEL_H__

#include <q3mainwindow.h>
#include <q3dict.h>
#include <qmap.h>
//Added by qt3to4:
#include <QShowEvent>
#include <QHideEvent>
#include <QKeyEvent>

#include "view.h"


class KALedMeter;
QT_BEGIN_NAMESPACE
class QLCDNumber;
QT_END_NAMESPACE

class KAstTopLevel : public Q3MainWindow
{
    Q_OBJECT
public:
    KAstTopLevel( QWidget *parent=0, const char *name=0 );
    virtual ~KAstTopLevel();

private:
    void playSound( const char *snd );
    void readSoundMapping();
    void doStats();

protected:
    virtual void showEvent( QShowEvent * );
    virtual void hideEvent( QHideEvent * );
    virtual void keyPressEvent( QKeyEvent *event );
    virtual void keyReleaseEvent( QKeyEvent *event );

private slots:
    void slotNewGame();

    void slotShipKilled();
    void slotRockHit( int size );
    void slotRocksRemoved();

    void slotUpdateVitals();

private:
    KAsteroidsView *view;
    QLCDNumber *scoreLCD;
    QLCDNumber *levelLCD;
    QLCDNumber *shipsLCD;

    QLCDNumber *teleportsLCD;
//    QLCDNumber *bombsLCD;
    QLCDNumber *brakesLCD;
    QLCDNumber *shieldLCD;
    QLCDNumber *shootLCD;
    KALedMeter *powerMeter;

    bool   sound;
    Q3Dict<QString> soundDict;

    // waiting for user to press Enter to launch a ship
    bool waitShip;
    bool isPaused;

    int shipsRemain;
    int score;
    int level;
    bool showHiscores;

    enum Action { Launch, Thrust, RotateLeft, RotateRight, Shoot, Teleport,
                    Brake, Shield, Pause, NewGame  };

    QMap<int,Action> actions;
};

#endif

