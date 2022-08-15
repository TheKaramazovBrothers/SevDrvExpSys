/********************************************************************************
** Form generated from reading UI file 'plotunitgraph.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTUNITGRAPH_H
#define UI_PLOTUNITGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gtplot.h"
#include "tabmodectl.h"

QT_BEGIN_NAMESPACE

class Ui_PlotUnitGraph
{
public:
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_plot_curve;
    QWidget *widget_plotGraph_left;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_plot_tab;
    QWidget *widget_plot_up;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *tbtn_plot_startSampling;
    QToolButton *tbtn_plot_auto;
    QToolButton *tbtn_plot_fit;
    QToolButton *tbtn_plot_mea_vertical;
    QToolButton *tbtn_plot_mea_horizontal;
    QToolButton *tbtn_plot_open;
    QToolButton *tbtn_plot_save;
    QToolButton *tbtn_plot_show_all;
    QToolButton *tbtn_plot_fft;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *tbtn_plot_floatin;
    GtPlot *plot;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *label_plot_x;
    QLabel *label_plot_y;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *label_plot_dx;
    QLabel *label_plot_dy;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_plot_down;
    TabModeCtl *widget;
    QWidget *widget_plotGraph_right;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QComboBox *comboBox_plot_sampling;
    QTableWidget *tableWidget_plot_curve;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *tbtn_plot_curveAll;
    QToolButton *tbtn_plot_curveAdd;
    QToolButton *tbtn_plot_curveRemove;
    QToolButton *tbtn_plot_curveClear;

    void setupUi(QWidget *PlotUnitGraph)
    {
        if (PlotUnitGraph->objectName().isEmpty())
            PlotUnitGraph->setObjectName(QStringLiteral("PlotUnitGraph"));
        PlotUnitGraph->resize(942, 463);
        verticalLayout_4 = new QVBoxLayout(PlotUnitGraph);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter_plot_curve = new QSplitter(PlotUnitGraph);
        splitter_plot_curve->setObjectName(QStringLiteral("splitter_plot_curve"));
        splitter_plot_curve->setOrientation(Qt::Horizontal);
        splitter_plot_curve->setHandleWidth(0);
        widget_plotGraph_left = new QWidget(splitter_plot_curve);
        widget_plotGraph_left->setObjectName(QStringLiteral("widget_plotGraph_left"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_plotGraph_left->sizePolicy().hasHeightForWidth());
        widget_plotGraph_left->setSizePolicy(sizePolicy);
        widget_plotGraph_left->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(widget_plotGraph_left);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter_plot_tab = new QSplitter(widget_plotGraph_left);
        splitter_plot_tab->setObjectName(QStringLiteral("splitter_plot_tab"));
        splitter_plot_tab->setMinimumSize(QSize(0, 0));
        splitter_plot_tab->setOrientation(Qt::Vertical);
        splitter_plot_tab->setHandleWidth(0);
        widget_plot_up = new QWidget(splitter_plot_tab);
        widget_plot_up->setObjectName(QStringLiteral("widget_plot_up"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(widget_plot_up->sizePolicy().hasHeightForWidth());
        widget_plot_up->setSizePolicy(sizePolicy1);
        widget_plot_up->setMinimumSize(QSize(0, 200));
        widget_plot_up->setMaximumSize(QSize(16777215, 16777215));
        widget_plot_up->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(widget_plot_up);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tbtn_plot_startSampling = new QToolButton(widget_plot_up);
        tbtn_plot_startSampling->setObjectName(QStringLiteral("tbtn_plot_startSampling"));
        tbtn_plot_startSampling->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_startSampling);

        tbtn_plot_auto = new QToolButton(widget_plot_up);
        tbtn_plot_auto->setObjectName(QStringLiteral("tbtn_plot_auto"));
        tbtn_plot_auto->setMinimumSize(QSize(30, 30));
        tbtn_plot_auto->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(tbtn_plot_auto);

        tbtn_plot_fit = new QToolButton(widget_plot_up);
        tbtn_plot_fit->setObjectName(QStringLiteral("tbtn_plot_fit"));
        tbtn_plot_fit->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_fit);

        tbtn_plot_mea_vertical = new QToolButton(widget_plot_up);
        tbtn_plot_mea_vertical->setObjectName(QStringLiteral("tbtn_plot_mea_vertical"));
        tbtn_plot_mea_vertical->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_mea_vertical);

        tbtn_plot_mea_horizontal = new QToolButton(widget_plot_up);
        tbtn_plot_mea_horizontal->setObjectName(QStringLiteral("tbtn_plot_mea_horizontal"));
        tbtn_plot_mea_horizontal->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_mea_horizontal);

        tbtn_plot_open = new QToolButton(widget_plot_up);
        tbtn_plot_open->setObjectName(QStringLiteral("tbtn_plot_open"));
        tbtn_plot_open->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_open);

        tbtn_plot_save = new QToolButton(widget_plot_up);
        tbtn_plot_save->setObjectName(QStringLiteral("tbtn_plot_save"));
        tbtn_plot_save->setMinimumSize(QSize(30, 30));
        tbtn_plot_save->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(tbtn_plot_save);

        tbtn_plot_show_all = new QToolButton(widget_plot_up);
        tbtn_plot_show_all->setObjectName(QStringLiteral("tbtn_plot_show_all"));
        tbtn_plot_show_all->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_show_all);

        tbtn_plot_fft = new QToolButton(widget_plot_up);
        tbtn_plot_fft->setObjectName(QStringLiteral("tbtn_plot_fft"));
        tbtn_plot_fft->setMinimumSize(QSize(30, 30));
        tbtn_plot_fft->setCheckable(true);

        horizontalLayout_2->addWidget(tbtn_plot_fft);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        tbtn_plot_floatin = new QToolButton(widget_plot_up);
        tbtn_plot_floatin->setObjectName(QStringLiteral("tbtn_plot_floatin"));
        tbtn_plot_floatin->setMinimumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(tbtn_plot_floatin);


        verticalLayout_2->addLayout(horizontalLayout_2);

        plot = new GtPlot(widget_plot_up);
        plot->setObjectName(QStringLiteral("plot"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(10);
        sizePolicy2.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy2);
        plot->setMinimumSize(QSize(0, 150));
        plot->setMaximumSize(QSize(16777215, 16777215));
        plot->setStyleSheet(QStringLiteral("background-color:white;"));

        verticalLayout_2->addWidget(plot);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_6 = new QLabel(widget_plot_up);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        label_plot_x = new QLabel(widget_plot_up);
        label_plot_x->setObjectName(QStringLiteral("label_plot_x"));
        label_plot_x->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(label_plot_x);

        label_plot_y = new QLabel(widget_plot_up);
        label_plot_y->setObjectName(QStringLiteral("label_plot_y"));
        label_plot_y->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(label_plot_y);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label = new QLabel(widget_plot_up);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        label_plot_dx = new QLabel(widget_plot_up);
        label_plot_dx->setObjectName(QStringLiteral("label_plot_dx"));
        label_plot_dx->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(label_plot_dx);

        label_plot_dy = new QLabel(widget_plot_up);
        label_plot_dy->setObjectName(QStringLiteral("label_plot_dy"));
        label_plot_dy->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(label_plot_dy);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        splitter_plot_tab->addWidget(widget_plot_up);
        widget_plot_down = new QWidget(splitter_plot_tab);
        widget_plot_down->setObjectName(QStringLiteral("widget_plot_down"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_plot_down->sizePolicy().hasHeightForWidth());
        widget_plot_down->setSizePolicy(sizePolicy3);
        widget_plot_down->setMinimumSize(QSize(0, 0));
        widget_plot_down->setMaximumSize(QSize(16777215, 16777215));
        widget_plot_down->setStyleSheet(QStringLiteral(""));
        widget = new TabModeCtl(widget_plot_down);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 686, 79));
        splitter_plot_tab->addWidget(widget_plot_down);

        verticalLayout->addWidget(splitter_plot_tab);

        splitter_plot_curve->addWidget(widget_plotGraph_left);
        widget_plotGraph_right = new QWidget(splitter_plot_curve);
        widget_plotGraph_right->setObjectName(QStringLiteral("widget_plotGraph_right"));
        widget_plotGraph_right->setMinimumSize(QSize(0, 463));
        widget_plotGraph_right->setMaximumSize(QSize(16777215, 16777215));
        widget_plotGraph_right->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(widget_plotGraph_right);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_11 = new QLabel(widget_plotGraph_right);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_11);

        comboBox_plot_sampling = new QComboBox(widget_plotGraph_right);
        comboBox_plot_sampling->setObjectName(QStringLiteral("comboBox_plot_sampling"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBox_plot_sampling->sizePolicy().hasHeightForWidth());
        comboBox_plot_sampling->setSizePolicy(sizePolicy4);
        comboBox_plot_sampling->setMaxVisibleItems(16);

        horizontalLayout_6->addWidget(comboBox_plot_sampling);

        horizontalLayout_6->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_6);

        tableWidget_plot_curve = new QTableWidget(widget_plotGraph_right);
        tableWidget_plot_curve->setObjectName(QStringLiteral("tableWidget_plot_curve"));

        verticalLayout_3->addWidget(tableWidget_plot_curve);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tbtn_plot_curveAll = new QToolButton(widget_plotGraph_right);
        tbtn_plot_curveAll->setObjectName(QStringLiteral("tbtn_plot_curveAll"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(tbtn_plot_curveAll->sizePolicy().hasHeightForWidth());
        tbtn_plot_curveAll->setSizePolicy(sizePolicy5);
        tbtn_plot_curveAll->setMinimumSize(QSize(30, 30));
        tbtn_plot_curveAll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(tbtn_plot_curveAll);

        tbtn_plot_curveAdd = new QToolButton(widget_plotGraph_right);
        tbtn_plot_curveAdd->setObjectName(QStringLiteral("tbtn_plot_curveAdd"));
        sizePolicy5.setHeightForWidth(tbtn_plot_curveAdd->sizePolicy().hasHeightForWidth());
        tbtn_plot_curveAdd->setSizePolicy(sizePolicy5);
        tbtn_plot_curveAdd->setMinimumSize(QSize(30, 30));
        tbtn_plot_curveAdd->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(tbtn_plot_curveAdd);

        tbtn_plot_curveRemove = new QToolButton(widget_plotGraph_right);
        tbtn_plot_curveRemove->setObjectName(QStringLiteral("tbtn_plot_curveRemove"));
        sizePolicy5.setHeightForWidth(tbtn_plot_curveRemove->sizePolicy().hasHeightForWidth());
        tbtn_plot_curveRemove->setSizePolicy(sizePolicy5);
        tbtn_plot_curveRemove->setMinimumSize(QSize(30, 30));
        tbtn_plot_curveRemove->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(tbtn_plot_curveRemove);

        tbtn_plot_curveClear = new QToolButton(widget_plotGraph_right);
        tbtn_plot_curveClear->setObjectName(QStringLiteral("tbtn_plot_curveClear"));
        sizePolicy5.setHeightForWidth(tbtn_plot_curveClear->sizePolicy().hasHeightForWidth());
        tbtn_plot_curveClear->setSizePolicy(sizePolicy5);
        tbtn_plot_curveClear->setMinimumSize(QSize(30, 30));
        tbtn_plot_curveClear->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(tbtn_plot_curveClear);


        verticalLayout_3->addLayout(horizontalLayout_5);

        splitter_plot_curve->addWidget(widget_plotGraph_right);

        verticalLayout_4->addWidget(splitter_plot_curve);


        retranslateUi(PlotUnitGraph);

        QMetaObject::connectSlotsByName(PlotUnitGraph);
    } // setupUi

    void retranslateUi(QWidget *PlotUnitGraph)
    {
        PlotUnitGraph->setWindowTitle(QApplication::translate("PlotUnitGraph", "Form", 0));
        tbtn_plot_startSampling->setText(QApplication::translate("PlotUnitGraph", "ON", 0));
        tbtn_plot_auto->setText(QApplication::translate("PlotUnitGraph", "auto", 0));
        tbtn_plot_fit->setText(QApplication::translate("PlotUnitGraph", "fit", 0));
        tbtn_plot_mea_vertical->setText(QApplication::translate("PlotUnitGraph", "vert", 0));
        tbtn_plot_mea_horizontal->setText(QApplication::translate("PlotUnitGraph", "hori", 0));
        tbtn_plot_open->setText(QApplication::translate("PlotUnitGraph", "open", 0));
        tbtn_plot_save->setText(QApplication::translate("PlotUnitGraph", "save", 0));
        tbtn_plot_show_all->setText(QApplication::translate("PlotUnitGraph", "all", 0));
        tbtn_plot_fft->setText(QApplication::translate("PlotUnitGraph", "fft", 0));
        tbtn_plot_floatin->setText(QApplication::translate("PlotUnitGraph", "floatin", 0));
        label_6->setText(QApplication::translate("PlotUnitGraph", "XYCood:", 0));
        label_plot_x->setText(QApplication::translate("PlotUnitGraph", "X", 0));
        label_plot_y->setText(QApplication::translate("PlotUnitGraph", "Y", 0));
        label->setText(QApplication::translate("PlotUnitGraph", "Measure:", 0));
        label_plot_dx->setText(QApplication::translate("PlotUnitGraph", "dx", 0));
        label_plot_dy->setText(QApplication::translate("PlotUnitGraph", "dy", 0));
        label_11->setText(QApplication::translate("PlotUnitGraph", "  Sampling(TS X):", 0));
        comboBox_plot_sampling->clear();
        comboBox_plot_sampling->insertItems(0, QStringList()
         << QApplication::translate("PlotUnitGraph", "1", 0)
         << QApplication::translate("PlotUnitGraph", "2", 0)
         << QApplication::translate("PlotUnitGraph", "3", 0)
         << QApplication::translate("PlotUnitGraph", "4", 0)
         << QApplication::translate("PlotUnitGraph", "5", 0)
         << QApplication::translate("PlotUnitGraph", "6", 0)
         << QApplication::translate("PlotUnitGraph", "7", 0)
         << QApplication::translate("PlotUnitGraph", "8", 0)
         << QApplication::translate("PlotUnitGraph", "9", 0)
         << QApplication::translate("PlotUnitGraph", "10", 0)
         << QApplication::translate("PlotUnitGraph", "11", 0)
         << QApplication::translate("PlotUnitGraph", "12", 0)
         << QApplication::translate("PlotUnitGraph", "13", 0)
         << QApplication::translate("PlotUnitGraph", "14", 0)
         << QApplication::translate("PlotUnitGraph", "15", 0)
         << QApplication::translate("PlotUnitGraph", "16", 0)
        );
        tbtn_plot_curveAll->setText(QApplication::translate("PlotUnitGraph", "All", 0));
        tbtn_plot_curveAdd->setText(QApplication::translate("PlotUnitGraph", "add", 0));
        tbtn_plot_curveRemove->setText(QApplication::translate("PlotUnitGraph", "rev", 0));
        tbtn_plot_curveClear->setText(QApplication::translate("PlotUnitGraph", "clr", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotUnitGraph: public Ui_PlotUnitGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTUNITGRAPH_H
