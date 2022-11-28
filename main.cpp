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

#include "mainwindow.h"
#include "log2nmea.h"
#include <QDir>
#include <QList>
#include <QFileInfo>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QApplication>


int main(int argc, char *argv[])
{
    if(argc > 1){
        QCommandLineParser mCommandParser;

        QList<QString> mInputList;
        QList<QString> mOutputList;

        QCoreApplication app(argc, argv);
        QCoreApplication::setApplicationName("log2nmea");
        QCoreApplication::setApplicationVersion("0.1");

        mCommandParser.setApplicationDescription("GPS LOG TO NMEA");
        mCommandParser.addHelpOption();
        mCommandParser.addVersionOption();

        QCommandLineOption mInputOption(QStringList() << "i" << "input",
                                        QCoreApplication::translate("main", "Input GPS log file"),
                                        QCoreApplication::translate("main", "path"));
        mCommandParser.addOption(mInputOption);

        QCommandLineOption mOutputOption(QStringList() << "o" << "output",
                                        QCoreApplication::translate("main", "Output NMEA file"),
                                        QCoreApplication::translate("main", "path"));
        mCommandParser.addOption(mOutputOption);

        mCommandParser.process(app);

        mInputList = mCommandParser.values(mInputOption);
        mOutputList = mCommandParser.values(mOutputOption);

        if(mInputList.size() == 0){
            qDebug() << mCommandParser.helpText();
            return -1;
        }

        if ((mInputList.size() != mOutputList.size()) && mOutputList.size() != 0) {
            qDebug() << "Input and output files size not match\n";
            return -1;
        }
        Log2Nmea *mLog2Nmea = new Log2Nmea();
        if (mOutputList.size() == 0 ) {
            for (int i = 0; i < mInputList.size(); ++i) {
                QFileInfo mLogFileInfo(mInputList.at(i));
                QDir mLogDirectory(mLogFileInfo.absolutePath());
                QString mOutputNmea = mLogDirectory.absoluteFilePath(mLogFileInfo.baseName() + ".nmea");
                if (mLogFileInfo.isFile()) {
                    int ret = mLog2Nmea->onConvertLog(mInputList.at(i), mOutputNmea);
                    if (ret != 0) {
                        return ret;
                    }
                }
            }
        } else {
            for (int i = 0; i < mInputList.size(); ++i) {
                QFileInfo mLogFileInfo(mInputList.at(i));
                if (mLogFileInfo.isFile()) {
                    int ret = mLog2Nmea->onConvertLog(mInputList.at(i), mOutputList.at(i));
                    if (ret != 0) {
                        return ret;
                    }
                }
            }
        }
    }
    else{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
