//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	dialog select curve ui                						//
//	file				:	dialogselectcurve.h                        					//
//	Description			:	use for curve select                                   		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/08/11	|	   liu.g        |		2022 - 2030			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DIALOGSELECTCURVE_H__
#define __DIALOGSELECTCURVE_H__


#include <QDialog>
#include "ui_dialogselectcurve.h"



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class DialogSelectCurve : public QDialog, public Ui::DialogSelectCurve
{
    Q_OBJECT
public:
    DialogSelectCurve(QWidget *parent = 0);
    ~DialogSelectCurve();
};



extern  Qt::GlobalColor tbl_col[20];



#endif





//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
