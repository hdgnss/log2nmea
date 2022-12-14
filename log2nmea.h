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

#ifndef LOG2NMEA_H
#define LOG2NMEA_H

#include <QThread>

class Log2Nmea : public QThread
{
    Q_OBJECT
public:
    explicit Log2Nmea(QObject *parent = 0);
    void run();
    void initThread(QString log, QString nmea);
    int onConvertLog(QString input, QString output);

private:
    QString mLogFile = "";
    QString mNmeaFile = "";

signals:
    void onJobDone(int value);

public slots:
    
};
#endif // LOG2NMEA_H