//=========================================================================================================
// project		:	curve select dialog realization
// File			:	tabmodectl.cpp
// discription	:	for tab mode control
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g/1487
// date			:	2022/08/09
// copyright(C)	:	liu.g	(2022-2030)
//=========================================================================================================

#include "Cia402AppEmu.h"
#include "plotunitgraph.h"
#include "dialogselectcurve.h"


DialogSelectCurve::DialogSelectCurve(QWidget *parent):QDialog(parent)
{
    setupUi(this);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    setWindowIcon(QIcon(":/res/images/PHA.png"));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    int row_num         =   VAR_SERVO_OBJW_INX_MAX_NUM;
    int colum_num       =   2;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QStringList headers;
    headers << "Index" << "Name";

    tableWidget->setRowCount(row_num);
    tableWidget->setColumnCount(colum_num);

    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setStyleSheet("background-color:rgb(255,255,255)");

    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    tableWidget->resizeColumnsToContents();
    tableWidget->setColumnWidth(0, 80);


    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < colum_num; j++)
        {
            tableWidget->setItem(i, j, new QTableWidgetItem());
            tableWidget->item(i,j)->setTextColor(tbl_col[i%20]);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            QString str;
            if (j == 0)
            {
                str             =     tr("0x") + QString::number(DefCiA402VarObjDic[i].Index,16);
            }
            else
            {
                str             =    (char *)(DefCiA402VarObjDic[i].pName);
            }

            tableWidget->item(i,j)->setText(str);

            tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        }
    }
    tableWidget->show();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(tableWidget, &QTableWidget::cellDoubleClicked, \
            (PlotUnitGraph*)(parent), &PlotUnitGraph::OnWaveTableItemDoubleClicked);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

DialogSelectCurve::~DialogSelectCurve()
{

}



















//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
