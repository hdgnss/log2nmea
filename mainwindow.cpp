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
#include "./ui_mainwindow.h"
#include "log2nmea.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLog2Nmea = new Log2Nmea(this);
    connect(mLog2Nmea, SIGNAL(onJobDone(int)), this, SLOT(onJobDone(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLog_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Log Files (*.log *.txt *.tmp)"));
    if (!fileName.isEmpty()) {
        ui->lineEditLog->setText(fileName);
        QFileInfo mLogFileInfo(fileName);
        QDir mLogDirectory(mLogFileInfo.absolutePath());
        QString mOutputNmea = mLogDirectory.absoluteFilePath(mLogFileInfo.baseName() + ".nmea");
        ui->lineEditNmea->setText(mOutputNmea);
    }
    
}

void MainWindow::on_pushButtonNmea_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("NMEA Files (*.nmea)"));
    if (!fileName.isEmpty()) {
        ui->lineEditNmea->setText(fileName);
    }
}


void MainWindow::on_pushButtonConvert_clicked()
{
    if(ui->lineEditNmea->text().isEmpty() || ui->lineEditLog->text().isEmpty()){
        ;
    }
    else{
        mLog2Nmea->initThread(ui->lineEditLog->text(), ui->lineEditNmea->text());
        mLog2Nmea->start();
        ui->pushButtonConvert->setEnabled(false);
    }
}


void MainWindow::onJobDone(int value)
{
    ui->statusBar->showMessage("Done with: " + QString::number(value));
    ui->pushButtonConvert->setEnabled(true);
}
