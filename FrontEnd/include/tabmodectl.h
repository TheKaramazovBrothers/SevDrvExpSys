//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	tab mode control ui                   						//
//	file				:	tabModeCtl.h                              					//
//	Description			:	use for tab mode conrol                               		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/08/09	|	   liu.g        |		2022 - 2030			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TABMODECTL_H__
#define __TABMODECTL_H__


#include <QWidget>
#include "ui_tabmodectl.h"


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef	enum
{
    IDLE_TABSM_WORK             =	0,													// idle work mode in sequence control | IDLE_TASK_ID
    AOA_TABSM_WORK              =	1,													// adc offset adjust work mode in sequence control | AOA_TASK_ID
    MIPA_TABSM_WORK             =	2,													// motor initialize phase adjust work mode in sequence control | MIPA_TASK_ID
    MPSA_TABSM_WORK             =	3,													// motor parameter self acquire in sequence control | MPSA_TASK_ID
    COLD_TABSM_WORK             =	4,													// current open loop control work mode in sequence control | COLD_TASK_ID
    CCLD_TABSM_WORK             =	5,													// current closed loop control work mode in sequence control | CCLD_TASK_ID
    VCLD_TABSM_WORK             =	6,													// velocity closed loop control work mode in sequence control | VCLD_TASK_ID
    PROF_VELC_TABSM_WORK		=	7,													// open velocity control work mode in sequence control | POSCLD_TASK_ID
    PROF_POSC_TABSM_WORK        =	8,                                                  // close velocity control work mode in sequence control	| POSCLD_TASK_ID
    PROF_CURC_TABSM_WORK		=	9,			   										// fixed position control work mode in sequence control | POSCLD_TASK_ID
    CS_VELC_TABSM_WORK          =	10,													// track position control work mode in sequence control | POSCLD_TASK_ID
    CS_POSC_TABSM_WORK          =	11,													// stop velocity control work mode in sequence control | POSCLD_TASK_ID
    CS_CURC_TABSM_WORK          =	12,                                                 // motor torque discharge work mode in sequence control | POSCLD_TASK_ID
    HOME_TABSM_WORK             =   13,                                                 // mechanic home search and fix mode in sequence control | POSCLD_TASK_ID
    REV_TABSM_WORK_MODE         =	0x8000
}tTabSevCtlMode;


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class TabModeCtl : public QWidget, public Ui::TabModeCtl
{
    Q_OBJECT
public:
    TabModeCtl(QWidget *parent = 0);
    ~TabModeCtl();
protected:
    bool    eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
private slots:
    void    onModeCtlPanelModeChanged(int mode);
    void    onBtnServoOnClicked(bool checked);
    void    onModeSpinBoxValueChanged(int value);
private:
    void    setupIcons(void);
private:
    QStringList         mode_list;
    tTabSevCtlMode      usr_mode;
//*******************************************************************************************************
    qreal               ipa_curr_ref;

    qreal               ud_ref;
    qreal               uq_ref;

    qreal               ua_ref;
    qreal               ub_ref;
    qreal               uc_ref;

    qreal               id_ref;
    qreal               iq_ref;
    qreal               spd_ref;
    qreal               pos_ref;
//*******************************************************************************************************
};



#endif


//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
