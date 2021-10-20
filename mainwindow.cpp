/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDateTime>
//#include <QtMqtt/QMqttClient>
#include <QtMqtt/qmqttclient.h>
#include <QtWidgets/QMessageBox>
#include <QSettings>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_client = new QMqttClient(this);
    m_client->setHostname(ui->lineEditHost->text());
    m_client->setPort(ui->spinBoxPort->value());

    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        ui->buttonPing->setEnabled(true);
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
    });

    connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    updateLogStateChange();
    readConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->lineEditHost->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);
        ui->buttonConnect->setText(tr("Disconnect"));
        m_client->connectToHost();
    } else {
        ui->lineEditHost->setEnabled(true);
        ui->spinBoxPort->setEnabled(true);
        ui->buttonConnect->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::on_buttonQuit_clicked()
{
    QApplication::quit();
}

void MainWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
    ui->editLog->insertPlainText(content);
}

void MainWindow::brokerDisconnected()
{
    ui->lineEditHost->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
    ui->buttonConnect->setText(tr("Connect"));
}

void MainWindow::setClientPort(int p)
{
    m_client->setPort(p);
}

void MainWindow::on_buttonPublish_1_clicked()
{
    if (m_client->publish(ui->lineEditTopic_1->text(), ui->lineEditMessage_1->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_1_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_2_clicked()
{
    if (m_client->publish(ui->lineEditTopic_2->text(), ui->lineEditMessage_2->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_2_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_3_clicked()
{
    if (m_client->publish(ui->lineEditTopic_3->text(), ui->lineEditMessage_3->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_3_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_4_clicked()
{
    if (m_client->publish(ui->lineEditTopic_4->text(), ui->lineEditMessage_4->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_4_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_5_clicked()
{
    if (m_client->publish(ui->lineEditTopic_5->text(), ui->lineEditMessage_5->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_5_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_6_clicked()
{
    if (m_client->publish(ui->lineEditTopic_6->text(), ui->lineEditMessage_6->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_6_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_7_clicked()
{
    if (m_client->publish(ui->lineEditTopic_7->text(), ui->lineEditMessage_7->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_7_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_8_clicked()
{
    if (m_client->publish(ui->lineEditTopic_8->text(), ui->lineEditMessage_8->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_8_clicked" << std::endl;
}

void MainWindow::on_buttonPublish_9_clicked()
{
    if (m_client->publish(ui->lineEditTopic_9->text(), ui->lineEditMessage_9->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));

    }
    std::cout << "on_buttonPublish_9_clicked" << std::endl;
}

void MainWindow::on_buttonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    std::cout << "on_buttonSubscribe_clicked" << std::endl;
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}

void MainWindow::on_buttonPing_clicked()
{
    ui->buttonPing->setEnabled(false);
    m_client->requestPing();
}

void MainWindow::readConfig()
{
    auto iniFile = new QSettings("cmd.ini",QSettings::IniFormat);
    ui->lineEditHost->setText(iniFile->value("sys/host").toString() );
    ui->spinBoxPort->setValue(iniFile->value("sys/port").toInt() );
    ui->lineEditTopic->setText(iniFile->value("topic/0").toString() );
    ui->lineEditTopic_1->setText(iniFile->value("topic/1").toString() );
    ui->lineEditTopic_2->setText(iniFile->value("topic/2").toString() );
    ui->lineEditTopic_3->setText(iniFile->value("topic/3").toString() );
    ui->lineEditTopic_4->setText(iniFile->value("topic/4").toString() );
    ui->lineEditTopic_5->setText(iniFile->value("topic/5").toString() );
    ui->lineEditTopic_6->setText(iniFile->value("topic/6").toString() );
    ui->lineEditTopic_7->setText(iniFile->value("topic/7").toString() );
    ui->lineEditTopic_8->setText(iniFile->value("topic/8").toString() );
    ui->lineEditTopic_9->setText(iniFile->value("topic/9").toString() );

    ui->lineEditMessage_1->setText(iniFile->value("message/1").toString() );
    ui->lineEditMessage_2->setText(iniFile->value("message/2").toString() );
    ui->lineEditMessage_3->setText(iniFile->value("message/3").toString() );
    ui->lineEditMessage_4->setText(iniFile->value("message/4").toString() );
    ui->lineEditMessage_5->setText(iniFile->value("message/5").toString() );
    ui->lineEditMessage_6->setText(iniFile->value("message/6").toString() );
    ui->lineEditMessage_7->setText(iniFile->value("message/7").toString() );
    ui->lineEditMessage_8->setText(iniFile->value("message/8").toString() );
    ui->lineEditMessage_9->setText(iniFile->value("message/9").toString() );

}

void MainWindow::updateConfigToUi()
{

}

void MainWindow::updateUiToConfigFile()
{
    //TODO
}

