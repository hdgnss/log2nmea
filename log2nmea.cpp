 /*
 * Copyright (C) 2022 HDGNSS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "log2nmea.h"
#include <QDebug>
#include <QDir>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

Log2Nmea::Log2Nmea(QObject *parent) : QThread(parent)
{
}

void Log2Nmea::run()
{
    int ret = onConvertLog(mLogFile, mNmeaFile);
    emit onJobDone(ret);
}

void Log2Nmea::initThread(QString log, QString nmea)
{
    mLogFile = log;
    mNmeaFile = nmea;
}

int Log2Nmea::onConvertLog(QString input, QString output)
{
    QRegularExpression mNmeaRegular("(\\$[A-Z]{4,8},.*\\*[0-9a-fA-F]{2,2}$)");
    QRegularExpressionMatch mNmeaMatch;

    QFile mInputFile(input);
    QFile mOutputFile(output);

    if (!mInputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Input file can not open\n";
        return -1;
    }
        

    if (!mOutputFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Output file can not open\n";
        return -2;
    }

    QTextStream mInputStream(&mInputFile);
    QTextStream mOutputStream(&mOutputFile);

    while (!mInputStream.atEnd()) {
        QString line = mInputStream.readLine();
        mNmeaMatch = mNmeaRegular.match(line);
        if (mNmeaMatch.hasMatch()) {
            mOutputStream  << mNmeaMatch.captured(0) << "\n";
        }
    }
    return 0;
}