/********************************************************************************
** Form generated from reading UI file 'ProfileEditorPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEEDITORPAGE_H
#define UI_PROFILEEDITORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileEditorPage
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *lblName;
    QLabel *lblTargetBG;
    QLabel *lblCorrection;
    QLabel *lblCarbRatio;
    QLineEdit *leName;
    QDoubleSpinBox *sbCarbRatio;
    QDoubleSpinBox *sbCorrection;
    QSpinBox *sbTargetBG;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSave;
    QPushButton *btnCancel;

    void setupUi(QWidget *ProfileEditorPage)
    {
        if (ProfileEditorPage->objectName().isEmpty())
            ProfileEditorPage->setObjectName(QString::fromUtf8("ProfileEditorPage"));
        ProfileEditorPage->resize(733, 334);
        formLayoutWidget = new QWidget(ProfileEditorPage);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(180, 30, 541, 181));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lblName = new QLabel(formLayoutWidget);
        lblName->setObjectName(QString::fromUtf8("lblName"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblName);

        lblTargetBG = new QLabel(formLayoutWidget);
        lblTargetBG->setObjectName(QString::fromUtf8("lblTargetBG"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblTargetBG);

        lblCorrection = new QLabel(formLayoutWidget);
        lblCorrection->setObjectName(QString::fromUtf8("lblCorrection"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblCorrection);

        lblCarbRatio = new QLabel(formLayoutWidget);
        lblCarbRatio->setObjectName(QString::fromUtf8("lblCarbRatio"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblCarbRatio);

        leName = new QLineEdit(formLayoutWidget);
        leName->setObjectName(QString::fromUtf8("leName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leName);

        sbCarbRatio = new QDoubleSpinBox(formLayoutWidget);
        sbCarbRatio->setObjectName(QString::fromUtf8("sbCarbRatio"));
        sbCarbRatio->setDecimals(1);
        sbCarbRatio->setMinimum(0.100000000000000);
        sbCarbRatio->setMaximum(50.000000000000000);
        sbCarbRatio->setSingleStep(0.100000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, sbCarbRatio);

        sbCorrection = new QDoubleSpinBox(formLayoutWidget);
        sbCorrection->setObjectName(QString::fromUtf8("sbCorrection"));
        sbCorrection->setDecimals(1);
        sbCorrection->setMinimum(0.100000000000000);
        sbCorrection->setMaximum(50.000000000000000);
        sbCorrection->setSingleStep(0.100000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, sbCorrection);

        sbTargetBG = new QSpinBox(formLayoutWidget);
        sbTargetBG->setObjectName(QString::fromUtf8("sbTargetBG"));
        QFont font;
        font.setPointSize(10);
        sbTargetBG->setFont(font);
        sbTargetBG->setMinimum(3);
        sbTargetBG->setMaximum(15);

        formLayout->setWidget(3, QFormLayout::FieldRole, sbTargetBG);

        horizontalLayoutWidget = new QWidget(ProfileEditorPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(430, 240, 291, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnSave = new QPushButton(horizontalLayoutWidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout->addWidget(btnSave);

        btnCancel = new QPushButton(horizontalLayoutWidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        retranslateUi(ProfileEditorPage);

        QMetaObject::connectSlotsByName(ProfileEditorPage);
    } // setupUi

    void retranslateUi(QWidget *ProfileEditorPage)
    {
        ProfileEditorPage->setWindowTitle(QCoreApplication::translate("ProfileEditorPage", "Form", nullptr));
        lblName->setText(QCoreApplication::translate("ProfileEditorPage", "Profile Name:", nullptr));
        lblTargetBG->setText(QCoreApplication::translate("ProfileEditorPage", "Target BG (mmol/L):", nullptr));
        lblCorrection->setText(QCoreApplication::translate("ProfileEditorPage", "Correction Factor:", nullptr));
        lblCarbRatio->setText(QCoreApplication::translate("ProfileEditorPage", "Carb Ratio (g/U):", nullptr));
        btnSave->setText(QCoreApplication::translate("ProfileEditorPage", "Save", nullptr));
        btnCancel->setText(QCoreApplication::translate("ProfileEditorPage", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfileEditorPage: public Ui_ProfileEditorPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEEDITORPAGE_H
