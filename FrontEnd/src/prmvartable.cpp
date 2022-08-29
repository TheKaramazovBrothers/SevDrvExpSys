//=========================================================================================================
// project		:	parameter & variable table realization
// File			:	prmVarTable.cpp
// discription	:	for parameter & varialbe table ui realization
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g/1487
// date			:	2022/08/
// copyright(C)	:	liu.g	(2022-2030)
//=========================================================================================================
#include <QHeaderView>
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include "prmvartable.h"

Qt::GlobalColor prm_var_tbl_col[3] =    {Qt::darkBlue, Qt::black, Qt::darkGreen};


SevPrmVarRamTable::SevPrmVarRamTable(QWidget *parent)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double dtmp;
    int row_num         =   (VAR_SERVO_OBJW_INX_MAX_NUM + PRM_SERVO_OBJW_INX_MAX_NUM);
    int colum_num       =   3;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QStringList headers;
    headers << "Index" << "value" << "Name";

    setRowCount(row_num);
    setColumnCount(colum_num);

    setHorizontalHeaderLabels(headers);
    setStyleSheet("background-color:rgb(255,255,255)");

    this->horizontalHeader()->setVisible(false);
    this->horizontalHeader()->setStretchLastSection(true);

    resizeColumnsToContents();
    setColumnWidth(0, 80);
    setColumnWidth(1, 160);

    for (int i = 0; i < VAR_SERVO_OBJW_INX_MAX_NUM; i++)
    {
        for (int j = 0; j < colum_num; j++)
        {
            setItem(i, j, new QTableWidgetItem());
            item(i,j)->setTextColor(prm_var_tbl_col[j]);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            QString str;
            if (j == 0)
            {
                str             =   tr("0x") + QString::number(DefCiA402VarObjDic[i].Index,16);
            }
            else if ( j == 1)
            {
                Uint16  inx     =   DefCiA402VarObjDic[i].Index - 0x3000;
                CpiReadRamVarByDicInx(inx, &dtmp);
                str             =   QString::number(dtmp);
            }
            else
            {
                str             =   (char *)(DefCiA402VarObjDic[i].pName);
            }

            item(i,j)->setText(str);

            item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        }
    }

    for (int i = VAR_SERVO_OBJW_INX_MAX_NUM; i < (VAR_SERVO_OBJW_INX_MAX_NUM + PRM_SERVO_OBJW_INX_MAX_NUM); i++)
    {
        for (int j = 0; j < colum_num; j++)
        {
            setItem(i, j, new QTableWidgetItem());
            item(i,j)->setTextColor(prm_var_tbl_col[j]);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            QString str;
            if (j == 0)
            {
                str             =     tr("0x") + QString::number(DefCiA402PrmObjDic[i-VAR_SERVO_OBJW_INX_MAX_NUM].Index,16);
            }
            else if ( j == 1)
            {
                Uint16  inx     =   DefCiA402PrmObjDic[i-VAR_SERVO_OBJW_INX_MAX_NUM].Index - 0x2000;
                CpiReadRamPrmByDicInx(inx, &dtmp);
                str             =   QString::number(dtmp);
            }
            else
            {
                str             =    (char *)(DefCiA402PrmObjDic[i-VAR_SERVO_OBJW_INX_MAX_NUM].pName);
            }

            item(i,j)->setText(str);

            item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        }
    }
}


SevPrmVarRamTable::~SevPrmVarRamTable()
{

}


void SevPrmVarRamTable::updatePrmVarTableData(void)
{
    double dtmp;
    QString str;
    for (int i = 0; i < VAR_SERVO_OBJW_INX_MAX_NUM; i++)
    {
        Uint16  inx     =   DefCiA402VarObjDic[i].Index - 0x3000;
        CpiReadRamVarByDicInx(inx, &dtmp);
        str             =   QString::number(dtmp);

        item(i,1)->setText(str);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }

    for (int i = VAR_SERVO_OBJW_INX_MAX_NUM; i < (VAR_SERVO_OBJW_INX_MAX_NUM + PRM_SERVO_OBJW_INX_MAX_NUM); i++)
    {
        Uint16  inx     =   DefCiA402PrmObjDic[i-VAR_SERVO_OBJW_INX_MAX_NUM].Index - 0x2000;
        CpiReadRamPrmByDicInx(inx, &dtmp);
        str             =   QString::number(dtmp);

        item(i,1)->setText(str);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}





SevPrmFlashTable::SevPrmFlashTable(QWidget *parent)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    int row_num         =   (VAR_SERVO_OBJW_INX_MAX_NUM + PRM_SERVO_OBJW_INX_MAX_NUM);
    int colum_num       =   3;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QStringList headers;
    headers << "Index" << "value" << "Name";

    setRowCount(row_num);
    setColumnCount(colum_num);

    setHorizontalHeaderLabels(headers);
    setStyleSheet("background-color:rgb(255,255,255)");

    this->horizontalHeader()->setVisible(false);
    this->horizontalHeader()->setStretchLastSection(true);

    resizeColumnsToContents();
    setColumnWidth(0, 80);
    setColumnWidth(1, 160);

    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
        for (int j = 0; j < colum_num; j++)
        {
            setItem(i, j, new QTableWidgetItem());
            item(i,j)->setTextColor(prm_var_tbl_col[j]);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            QString str;
            if (j == 0)
            {
                str             =   tr("0x") + QString::number(DefCiA402PrmObjDic[i].Index,16);
            }
            else if ( j == 1)
            {
                str             =   tr("0");
            }
            else
            {
                str             =   (char *)(DefCiA402PrmObjDic[i].pName);
            }

            item(i,j)->setText(str);

            if (j == 1)
            {
                item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
            }
            else
            {
                item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        }
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(this, &QTableWidget::cellChanged, this, &SevPrmFlashTable::OnTableCellChanged);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



SevPrmFlashTable::~SevPrmFlashTable()
{

}


void SevPrmFlashTable::OnTableCellChanged(int row, int column)
{
    Uint16  utmp;
    Uint32  lutmp;
    QString str;

    if (column == 1)
    {
        if (DefCiA402PrmObjDic[row].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            SclReadFramPrmByID32(DefCiA402PrmObjDic[row].NonVolatileOffset,&lutmp);
            str             =   QString::number(lutmp);
        }
        else
        {
            SclReadFramPrmByID16(DefCiA402PrmObjDic[row].NonVolatileOffset,&utmp);
            str             =   QString::number(utmp);
        }

        if (str != item(row,column)->text())
        {
            item(row,column)->setBackgroundColor(Qt::yellow);
        }
        else
        {
            item(row,column)->setBackgroundColor(Qt::white);
        }
    }
}



void SevPrmFlashTable::updateFlashTableData(void)
{
    Uint16  utmp;
    Uint32  lutmp;
    QString str;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            SclReadFramPrmByID32(DefCiA402PrmObjDic[i].NonVolatileOffset,&lutmp);
            str             =   QString::number(lutmp);
        }
        else
        {
            SclReadFramPrmByID16(DefCiA402PrmObjDic[i].NonVolatileOffset,&utmp);
            str             =   QString::number(utmp);
        }

        item(i,1)->setText(str);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
