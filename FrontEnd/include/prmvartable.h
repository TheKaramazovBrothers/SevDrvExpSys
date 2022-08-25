//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	parameter & variable table design in servo system			//
//	file				:	PrmVarTable.h                           					//
//	Description			:	parameter & variable table realization                 		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/08/15	|	   liu.g        |		2022 - 2030			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef PRMVARTABLE
#define PRMVARTABLE


#include <QTableWidget>
//#############################################################################################################################
// servo parameter & variable table
//#############################################################################################################################
class    SevPrmVarRamTable : public QTableWidget
{
    Q_OBJECT
public:
    SevPrmVarRamTable(QWidget *parent = 0);
    ~SevPrmVarRamTable();
public:
    void updatePrmVarTableData(void);
};



//#############################################################################################################################
// servo parameter table
//#############################################################################################################################
class    SevPrmFlashTable : public QTableWidget
{
    Q_OBJECT
public:
    SevPrmFlashTable(QWidget *parent = 0);
    ~SevPrmFlashTable();
public slots:
    void OnTableCellChanged(int row, int column);
public:
    void updateFlashTableData(void);
};






//#############################################################################################################################


















#endif // PRMVARTABLE

//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
