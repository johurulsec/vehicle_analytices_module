/********************************************************************************
** Form generated from reading UI file 'eula.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EULA_H
#define UI_EULA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_eula
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QLabel *label;
    QPushButton *agreeButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *eula)
    {
        if (eula->objectName().isEmpty())
            eula->setObjectName(QStringLiteral("eula"));
        eula->resize(424, 353);
        verticalLayout = new QVBoxLayout(eula);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser = new QTextBrowser(eula);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        label = new QLabel(eula);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        agreeButton = new QPushButton(eula);
        agreeButton->setObjectName(QStringLiteral("agreeButton"));

        verticalLayout->addWidget(agreeButton);

        cancelButton = new QPushButton(eula);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        verticalLayout->addWidget(cancelButton);


        retranslateUi(eula);

        QMetaObject::connectSlotsByName(eula);
    } // setupUi

    void retranslateUi(QDialog *eula)
    {
        eula->setWindowTitle(QApplication::translate("eula", "Dialog", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("eula", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&quot;WATCHCAM Surveillance Suite&quot; Trial</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Copyright (c) 2018 SIGMIND </p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">*** EN"
                        "D USER LICENSE AGREEMENT ***</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">IMPORTANT: PLEASE READ THIS LICENSE CAREFULLY BEFORE USING THIS SOFTWARE.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1. LICENSE</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">By receiving, opening the file package, a"
                        "nd/or using &quot;WATCHCAM Surveillance Suite&quot; Trial(&quot;Software&quot;) containing this software, you agree that this End User User License Agreement(EULA) is a legally binding and valid contract and agree to be bound by it. You agree to abide by the intellectual property laws and all of the terms and conditions of this Agreement.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Unless you have a different license agreement signed by SIGMIND your use of &quot;WATCHCAM Surveillance Suite&quot; Trial indicates your acceptance of this license agreement and warranty.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bo"
                        "ttom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Subject to the terms of this Agreement, SIGMIND grants to you a limited, non-exclusive, non-transferable license, without right to sub-license, to use &quot;WATCHCAM Surveillance Suite&quot; Trial in accordance with this Agreement and any other written agreement with SIGMIND. SIGMIND does not transfer the title of &quot;WATCHCAM Surveillance Suite&quot; Trial to you; the license granted to you is not a sale. This agreement is a binding legal agreement between SIGMIND and the purchasers or users of &quot;WATCHCAM Surveillance Suite&quot; Trial.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">If you do not agree to be bound by this agreement, remove &quot;WATCHCAM Surveillance Suite&quot; Tri"
                        "al from your computer now and, if applicable, promptly return to SIGMIND by mail any copies of &quot;WATCHCAM Surveillance Suite&quot; Trial and related documentation and packaging in your possession.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2. DISTRIBUTION</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&quot;WATCHCAM Surveillance Suite&quot; Trial and the license herein granted shall not be copied, shared, distributed, re-sold, offered for re-sale, transferred or sub-licensed in whole or in part except that you may make one co"
                        "py for archive purposes only. For information about redistribution of &quot;WATCHCAM Surveillance Suite&quot; Trial contact SIGMIND.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3. USER AGREEMENT</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.1 Use</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px"
                        ";\">Your license to use &quot;WATCHCAM Surveillance Suite&quot; Trial is limited to the number of licenses purchased by you. You shall not allow others to use, copy or evaluate copies of &quot;WATCHCAM Surveillance Suite&quot; Trial.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.2 Use Restrictions</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You shall use &quot;WATCHCAM Surveillance Suite&quot; Trial in compliance with all applicable laws and not for any unlawful purpose. Without limiting the foregoing, use, display or distribut"
                        "ion of &quot;WATCHCAM Surveillance Suite&quot; Trial together with material that is pornographic, racist, vulgar, obscene, defamatory, libelous, abusive, promoting hatred, discriminating or displaying prejudice based on religion, ethnic heritage, race, sexual orientation or age is strictly prohibited.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Each licensed copy of &quot;WATCHCAM Surveillance Suite&quot; Trial may be used on one single computer location by one user. Use of &quot;WATCHCAM Surveillance Suite&quot; Trial means that you have loaded, installed, or run &quot;WATCHCAM Surveillance Suite&quot; Trial on a computer or similar device. If you install &quot;WATCHCAM Surveillance Suite&quot; Trial onto a multi-user platform, server or network, each and every indivi"
                        "dual user of &quot;WATCHCAM Surveillance Suite&quot; Trial must be licensed separately.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You may make one copy of &quot;WATCHCAM Surveillance Suite&quot; Trial for backup purposes, providing you only have one copy installed on one computer being used by one person. Other users may not use your copy of &quot;WATCHCAM Surveillance Suite&quot; Trial . The assignment, sublicense, networking, sale, or distribution of copies of &quot;WATCHCAM Surveillance Suite&quot; Trial are strictly forbidden without the prior written consent of SIGMIND. It is a violation of this agreement to assign, sell, share, loan, rent, lease, borrow, network or transfer the use of &quot;WATCHCAM Surveillance Suite&quot; Trial. If any person other than yours"
                        "elf uses &quot;WATCHCAM Surveillance Suite&quot; Trial registered in your name, regardless of whether it is at the same time or different times, then this agreement is being violated and you are responsible for that violation!</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.3 Copyright Restriction</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This Software contains copyrighted material, trade secrets and other proprietary material. You shall not, and shall not attempt to, modify, reverse engineer, disassemble or decompile &quot;WAT"
                        "CHCAM Surveillance Suite&quot; Trial. Nor can you create any derivative works or other works that are based upon or derived from &quot;WATCHCAM Surveillance Suite&quot; Trial in whole or in part.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">SIGMIND's name, logo and graphics file that represents &quot;WATCHCAM Surveillance Suite&quot; Trial shall not be used in any way to promote products developed with &quot;WATCHCAM Surveillance Suite&quot; Trial . SIGMIND retains sole and exclusive ownership of all right, title and interest in and to &quot;WATCHCAM Surveillance Suite&quot; Trial and all Intellectual Property rights relating thereto.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; te"
                        "xt-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Copyright law and international copyright treaty provisions protect all parts of &quot;WATCHCAM Surveillance Suite&quot; Trial, products and services. No program, code, part, image, audio sample, or text may be copied or used in any way by the user except as intended within the bounds of the single user program. All rights not expressly granted hereunder are reserved for SIGMIND.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.4 Limitation of Responsibility</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
""
                        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You will indemnify, hold harmless, and defend SIGMIND , its employees, agents and distributors against any and all claims, proceedings, demand and costs resulting from or in any way connected with your use of SIGMIND's Software.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">In no event (including, without limitation, in the event of negligence) will SIGMIND , its employees, agents or distributors be liable for any consequential, incidental, indirect, special or punitive damages whatsoever (including, without limitation, damages for loss of profits, loss of use, business interruption, loss of information or data, or pecuniary loss), in connection with o"
                        "r arising out of or related to this Agreement, &quot;WATCHCAM Surveillance Suite&quot; Trial or the use or inability to use &quot;WATCHCAM Surveillance Suite&quot; Trial or the furnishing, performance or use of any other matters hereunder whether based upon contract, tort or any other theory including negligence.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">SIGMIND's entire liability, without exception, is limited to the customers' reimbursement of the purchase price of the Software (maximum being the lesser of the amount paid by you and the suggested retail price as listed by SIGMIND ) in exchange for the return of the product, all copies, registration papers and manuals, and all materials that constitute a transfer of license from the customer back to SIGMIND.</p>\n"
""
                        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.5 Warranties</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Except as expressly stated in writing, SIGMIND makes no representation or warranties in respect of this Software and expressly excludes all other warranties, expressed or implied, oral or written, including, without limitation, any implied warranties of merchantable quality or fitness for a particular purpose.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-i"
                        "ndent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.6 Governing Law</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This Agreement shall be governed by the law of the Bangladesh applicable therein. You hereby irrevocably attorn and submit to the non-exclusive jurisdiction of the courts of Bangladesh therefrom. If any provision shall be considered unlawful, void or otherwise unenforceable, then that provision shall be deemed severable from this License and not affect the validity and enforceability of any other provisions.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-i"
                        "ndent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.7 Termination</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Any failure to comply with the terms and conditions of this Agreement will result in automatic and immediate termination of this license. Upon termination of this license granted herein for any reason, you agree to immediately cease use of &quot;WATCHCAM Surveillance Suite&quot; Trial and destroy all copies of &quot;WATCHCAM Surveillance Suite&quot; Trial supplied under this Agreement. The financial obligations incurred by you shall survive the expiration or termination of this license.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px"
                        "; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4. DISCLAIMER OF WARRANTY</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">THIS SOFTWARE AND THE ACCOMPANYING FILES ARE SOLD &quot;AS IS&quot; AND WITHOUT WARRANTIES AS TO PERFORMANCE OR MERCHANTABILITY OR ANY OTHER WARRANTIES WHETHER EXPRESSED OR IMPLIED. THIS DISCLAIMER CONCERNS ALL FILES GENERATED AND EDITED BY &quot;WATCHCAM Surveillance Suite&quot; Trial AS WELL.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">5. CONSENT OF USE OF DATA</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You agree that SIGMIND may collect and use information gathered in any manner as part of the product support services provided to you, if any, related to &quot;WATCHCAM Surveillance Suite&quot; Trial.SIGMIND may also use this information to provide notices to you which may be of use or interest to you.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> 	</p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("eula", "By clicking \"I Accept\", you will agree and follow the EULA", Q_NULLPTR));
        agreeButton->setText(QApplication::translate("eula", "I Agree ", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("eula", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class eula: public Ui_eula {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EULA_H
