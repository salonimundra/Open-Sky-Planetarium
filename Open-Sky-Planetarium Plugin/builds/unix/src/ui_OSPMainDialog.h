/********************************************************************************
** Form generated from reading UI file 'OSPMainDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSPMAINDIALOG_H
#define UI_OSPMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Dialog.hpp"

QT_BEGIN_NAMESPACE

class Ui_OSPMainDialog
{
public:
    QVBoxLayout *verticalLayout;
    BarFrame *TitleBar;
    QHBoxLayout *_2;
    QSpacerItem *leftSpacer;
    QLabel *stelWindowTitle;
    QSpacerItem *rightSpacer;
    QPushButton *closeStelWindow;
    QTabWidget *tabWidg;
    QWidget *calTab;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *laserDirControl;
    QGridLayout *gridLayout;
    QPushButton *mvDown;
    QPushButton *mvUp;
    QPushButton *mvRight;
    QPushButton *mvLeft;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *reset;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QSlider *intensity;
    QGroupBox *laserlightControl;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *laserOn;
    QRadioButton *laserOff;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *configDevice;
    QVBoxLayout *verticalLayout_5;
    QPushButton *selectDev;
    QPushButton *startCal;
    QPushButton *goTo;
    QGroupBox *refStatus;
    QVBoxLayout *verticalLayout_7;
    QPushButton *setRef;
    QLineEdit *refStat;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *scriptTab;
    QSplitter *splitter;
    QSlider *volumeChanged;
    QPushButton *playui;
    QPushButton *stopui;
    QPushButton *openScript;
    QPushButton *saveScript;
    QPushButton *compScript;
    QPushButton *execScript;
    QSplitter *splitter_2;
    QPushButton *gt;
    QPushButton *pl;
    QPushButton *wt;
    QPushButton *lo;
    QTextEdit *scriptEdit;
    QWidget *abtTab;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *textBrowser;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *OSPMainDialog)
    {
        if (OSPMainDialog->objectName().isEmpty())
            OSPMainDialog->setObjectName(QStringLiteral("OSPMainDialog"));
        OSPMainDialog->resize(510, 444);
        OSPMainDialog->setFocusPolicy(Qt::ClickFocus);
        verticalLayout = new QVBoxLayout(OSPMainDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        TitleBar = new BarFrame(OSPMainDialog);
        TitleBar->setObjectName(QStringLiteral("TitleBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TitleBar->sizePolicy().hasHeightForWidth());
        TitleBar->setSizePolicy(sizePolicy);
        TitleBar->setMinimumSize(QSize(0, 25));
        TitleBar->setMaximumSize(QSize(16777215, 30));
        TitleBar->setFocusPolicy(Qt::NoFocus);
        TitleBar->setAutoFillBackground(false);
        TitleBar->setFrameShape(QFrame::StyledPanel);
        _2 = new QHBoxLayout(TitleBar);
        _2->setSpacing(6);
        _2->setObjectName(QStringLiteral("_2"));
        _2->setContentsMargins(0, 0, 4, 0);
        leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(leftSpacer);

        stelWindowTitle = new QLabel(TitleBar);
        stelWindowTitle->setObjectName(QStringLiteral("stelWindowTitle"));

        _2->addWidget(stelWindowTitle);

        rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(rightSpacer);

        closeStelWindow = new QPushButton(TitleBar);
        closeStelWindow->setObjectName(QStringLiteral("closeStelWindow"));
        closeStelWindow->setMinimumSize(QSize(16, 16));
        closeStelWindow->setMaximumSize(QSize(16, 16));
        closeStelWindow->setFocusPolicy(Qt::NoFocus);

        _2->addWidget(closeStelWindow);


        verticalLayout->addWidget(TitleBar);

        tabWidg = new QTabWidget(OSPMainDialog);
        tabWidg->setObjectName(QStringLiteral("tabWidg"));
        tabWidg->setTabPosition(QTabWidget::North);
        tabWidg->setTabShape(QTabWidget::Rounded);
        tabWidg->setMovable(false);
        tabWidg->setTabBarAutoHide(false);
        calTab = new QWidget();
        calTab->setObjectName(QStringLiteral("calTab"));
        horizontalLayout_4 = new QHBoxLayout(calTab);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        laserDirControl = new QGroupBox(calTab);
        laserDirControl->setObjectName(QStringLiteral("laserDirControl"));
        gridLayout = new QGridLayout(laserDirControl);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mvDown = new QPushButton(laserDirControl);
        mvDown->setObjectName(QStringLiteral("mvDown"));
        mvDown->setEnabled(false);

        gridLayout->addWidget(mvDown, 2, 2, 1, 1);

        mvUp = new QPushButton(laserDirControl);
        mvUp->setObjectName(QStringLiteral("mvUp"));
        mvUp->setEnabled(false);

        gridLayout->addWidget(mvUp, 0, 2, 1, 1);

        mvRight = new QPushButton(laserDirControl);
        mvRight->setObjectName(QStringLiteral("mvRight"));
        mvRight->setEnabled(false);

        gridLayout->addWidget(mvRight, 1, 3, 1, 1);

        mvLeft = new QPushButton(laserDirControl);
        mvLeft->setObjectName(QStringLiteral("mvLeft"));
        mvLeft->setEnabled(false);

        gridLayout->addWidget(mvLeft, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        reset = new QPushButton(laserDirControl);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setEnabled(false);

        gridLayout->addWidget(reset, 1, 2, 1, 1);


        verticalLayout_8->addWidget(laserDirControl);

        groupBox = new QGroupBox(calTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        intensity = new QSlider(groupBox);
        intensity->setObjectName(QStringLiteral("intensity"));
        intensity->setEnabled(false);
        intensity->setMinimum(50);
        intensity->setMaximum(255);
        intensity->setValue(50);
        intensity->setSliderPosition(50);
        intensity->setTracking(false);
        intensity->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(intensity);


        verticalLayout_8->addWidget(groupBox);

        laserlightControl = new QGroupBox(calTab);
        laserlightControl->setObjectName(QStringLiteral("laserlightControl"));
        laserlightControl->setContextMenuPolicy(Qt::PreventContextMenu);
        laserlightControl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalLayout_3 = new QHBoxLayout(laserlightControl);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        laserOn = new QRadioButton(laserlightControl);
        buttonGroup = new QButtonGroup(OSPMainDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(laserOn);
        laserOn->setObjectName(QStringLiteral("laserOn"));
        laserOn->setEnabled(false);
        laserOn->setFocusPolicy(Qt::StrongFocus);
        laserOn->setChecked(false);

        horizontalLayout_3->addWidget(laserOn);

        laserOff = new QRadioButton(laserlightControl);
        buttonGroup->addButton(laserOff);
        laserOff->setObjectName(QStringLiteral("laserOff"));
        laserOff->setEnabled(false);
        laserOff->setChecked(true);

        horizontalLayout_3->addWidget(laserOff);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_8->addWidget(laserlightControl);


        horizontalLayout_4->addLayout(verticalLayout_8);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        configDevice = new QGroupBox(calTab);
        configDevice->setObjectName(QStringLiteral("configDevice"));
        verticalLayout_5 = new QVBoxLayout(configDevice);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        selectDev = new QPushButton(configDevice);
        selectDev->setObjectName(QStringLiteral("selectDev"));
        selectDev->setEnabled(true);

        verticalLayout_5->addWidget(selectDev);

        startCal = new QPushButton(configDevice);
        startCal->setObjectName(QStringLiteral("startCal"));
        startCal->setEnabled(false);

        verticalLayout_5->addWidget(startCal);

        goTo = new QPushButton(configDevice);
        goTo->setObjectName(QStringLiteral("goTo"));
        goTo->setEnabled(false);

        verticalLayout_5->addWidget(goTo);


        verticalLayout_6->addWidget(configDevice);

        refStatus = new QGroupBox(calTab);
        refStatus->setObjectName(QStringLiteral("refStatus"));
        verticalLayout_7 = new QVBoxLayout(refStatus);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        setRef = new QPushButton(refStatus);
        setRef->setObjectName(QStringLiteral("setRef"));
        setRef->setEnabled(false);

        verticalLayout_7->addWidget(setRef);

        refStat = new QLineEdit(refStatus);
        refStat->setObjectName(QStringLiteral("refStat"));
        refStat->setEnabled(true);
        refStat->setAlignment(Qt::AlignCenter);
        refStat->setReadOnly(true);

        verticalLayout_7->addWidget(refStat);


        verticalLayout_6->addWidget(refStatus);

        groupBox_2 = new QGroupBox(calTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_6->addWidget(groupBox_2);


        horizontalLayout_4->addLayout(verticalLayout_6);

        tabWidg->addTab(calTab, QString());
        scriptTab = new QWidget();
        scriptTab->setObjectName(QStringLiteral("scriptTab"));
        splitter = new QSplitter(scriptTab);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(341, 41, 101, 291));
        splitter->setOrientation(Qt::Vertical);
        volumeChanged = new QSlider(splitter);
        volumeChanged->setObjectName(QStringLiteral("volumeChanged"));
        volumeChanged->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(volumeChanged->sizePolicy().hasHeightForWidth());
        volumeChanged->setSizePolicy(sizePolicy1);
        volumeChanged->setCursor(QCursor(Qt::BusyCursor));
        volumeChanged->setValue(50);
        volumeChanged->setOrientation(Qt::Horizontal);
        splitter->addWidget(volumeChanged);
        playui = new QPushButton(splitter);
        playui->setObjectName(QStringLiteral("playui"));
        playui->setEnabled(false);
        splitter->addWidget(playui);
        stopui = new QPushButton(splitter);
        stopui->setObjectName(QStringLiteral("stopui"));
        stopui->setEnabled(true);
        splitter->addWidget(stopui);
        openScript = new QPushButton(splitter);
        openScript->setObjectName(QStringLiteral("openScript"));
        splitter->addWidget(openScript);
        saveScript = new QPushButton(splitter);
        saveScript->setObjectName(QStringLiteral("saveScript"));
        splitter->addWidget(saveScript);
        compScript = new QPushButton(splitter);
        compScript->setObjectName(QStringLiteral("compScript"));
        splitter->addWidget(compScript);
        execScript = new QPushButton(splitter);
        execScript->setObjectName(QStringLiteral("execScript"));
        execScript->setEnabled(true);
        splitter->addWidget(execScript);
        splitter_2 = new QSplitter(scriptTab);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(10, 10, 431, 23));
        splitter_2->setOrientation(Qt::Horizontal);
        gt = new QPushButton(splitter_2);
        gt->setObjectName(QStringLiteral("gt"));
        splitter_2->addWidget(gt);
        pl = new QPushButton(splitter_2);
        pl->setObjectName(QStringLiteral("pl"));
        splitter_2->addWidget(pl);
        wt = new QPushButton(splitter_2);
        wt->setObjectName(QStringLiteral("wt"));
        splitter_2->addWidget(wt);
        lo = new QPushButton(splitter_2);
        lo->setObjectName(QStringLiteral("lo"));
        splitter_2->addWidget(lo);
        scriptEdit = new QTextEdit(scriptTab);
        scriptEdit->setObjectName(QStringLiteral("scriptEdit"));
        scriptEdit->setGeometry(QRect(13, 42, 321, 291));
        scriptEdit->setAutoFillBackground(true);
        scriptEdit->setInputMethodHints(Qt::ImhLowercaseOnly|Qt::ImhMultiLine|Qt::ImhNoAutoUppercase);
        scriptEdit->setFrameShape(QFrame::StyledPanel);
        scriptEdit->setReadOnly(false);
        tabWidg->addTab(scriptTab, QString());
        abtTab = new QWidget();
        abtTab->setObjectName(QStringLiteral("abtTab"));
        verticalLayout_4 = new QVBoxLayout(abtTab);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        textBrowser = new QTextBrowser(abtTab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_4->addWidget(textBrowser);

        tabWidg->addTab(abtTab, QString());

        verticalLayout->addWidget(tabWidg);


        retranslateUi(OSPMainDialog);

        tabWidg->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OSPMainDialog);
    } // setupUi

    void retranslateUi(QWidget *OSPMainDialog)
    {
        OSPMainDialog->setWindowTitle(QApplication::translate("OSPMainDialog", "Form", Q_NULLPTR));
        stelWindowTitle->setText(QApplication::translate("OSPMainDialog", "Open Sky Planetarium", Q_NULLPTR));
        closeStelWindow->setText(QString());
        laserDirControl->setTitle(QApplication::translate("OSPMainDialog", "LASER Direction Control", Q_NULLPTR));
        mvDown->setText(QApplication::translate("OSPMainDialog", "down", Q_NULLPTR));
        mvUp->setText(QApplication::translate("OSPMainDialog", "up", Q_NULLPTR));
        mvRight->setText(QApplication::translate("OSPMainDialog", "right", Q_NULLPTR));
        mvLeft->setText(QApplication::translate("OSPMainDialog", "left", Q_NULLPTR));
        reset->setText(QApplication::translate("OSPMainDialog", "reset", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("OSPMainDialog", "LASER Intensity Control", Q_NULLPTR));
        laserlightControl->setTitle(QApplication::translate("OSPMainDialog", "LASER Switching Control", Q_NULLPTR));
        laserOn->setText(QApplication::translate("OSPMainDialog", "Turn ON", Q_NULLPTR));
        laserOff->setText(QApplication::translate("OSPMainDialog", "Turn OFF", Q_NULLPTR));
        configDevice->setTitle(QApplication::translate("OSPMainDialog", "Device Configuration", Q_NULLPTR));
        selectDev->setText(QApplication::translate("OSPMainDialog", "Select", Q_NULLPTR));
        startCal->setText(QApplication::translate("OSPMainDialog", "Start Calibrate", Q_NULLPTR));
        goTo->setText(QApplication::translate("OSPMainDialog", "GoTo", Q_NULLPTR));
        refStatus->setTitle(QApplication::translate("OSPMainDialog", "Reference Status", Q_NULLPTR));
        setRef->setText(QApplication::translate("OSPMainDialog", "Set Ref.", Q_NULLPTR));
        refStat->setText(QApplication::translate("OSPMainDialog", "0/3", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("OSPMainDialog", "Current Coordinates", Q_NULLPTR));
        label->setText(QApplication::translate("OSPMainDialog", "X:", Q_NULLPTR));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("OSPMainDialog", "Y:", Q_NULLPTR));
        label_4->setText(QString());
        tabWidg->setTabText(tabWidg->indexOf(calTab), QApplication::translate("OSPMainDialog", "Calibration", Q_NULLPTR));
        playui->setText(QApplication::translate("OSPMainDialog", "Play", Q_NULLPTR));
        stopui->setText(QApplication::translate("OSPMainDialog", "Stop", Q_NULLPTR));
        openScript->setText(QApplication::translate("OSPMainDialog", "Open", Q_NULLPTR));
        saveScript->setText(QApplication::translate("OSPMainDialog", "Save", Q_NULLPTR));
        compScript->setText(QApplication::translate("OSPMainDialog", "Build", Q_NULLPTR));
        execScript->setText(QApplication::translate("OSPMainDialog", "Build + Run", Q_NULLPTR));
        gt->setText(QApplication::translate("OSPMainDialog", "Goto", Q_NULLPTR));
        pl->setText(QApplication::translate("OSPMainDialog", "Audio", Q_NULLPTR));
        wt->setText(QApplication::translate("OSPMainDialog", "WAIT", Q_NULLPTR));
        lo->setText(QApplication::translate("OSPMainDialog", "LASER ON/OFF", Q_NULLPTR));
        tabWidg->setTabText(tabWidg->indexOf(scriptTab), QApplication::translate("OSPMainDialog", "ScriptEngine", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("OSPMainDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:20pt; font-weight:600; text-decoration: underline;\">OpenSkyPlanetarium</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">An Open Source Initiative by IIT Bombay to bring interesting objects in the OpenSky closer to the common masses and school childrens.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">Contact: IIT Bombay</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-"
                        "indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">Email: openskyplanetarium@fossee.in</span></p></body></html>", Q_NULLPTR));
        tabWidg->setTabText(tabWidg->indexOf(abtTab), QApplication::translate("OSPMainDialog", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSPMainDialog: public Ui_OSPMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSPMAINDIALOG_H
