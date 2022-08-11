//=========================================================================================================
// project		:	tab mode control module
// File			:	tabmodectl.cpp
// discription	:	for tab mode control
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g/1487
// date			:	2022/08/09
// copyright(C)	:	liu.g	(2022-2030)
//=========================================================================================================


#include <QKeyEvent>
#include "TuningCmd.h"
#include "tabmodectl.h"


TabModeCtl::TabModeCtl(QWidget *parent)
{
    setupUi(parent);
    setupIcons();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    usr_mode            =   IDLE_TABSM_WORK;

    ipa_curr_ref        =   0;
    ud_ref              =   0;
    uq_ref              =   0;

    ua_ref              =   0;
    ub_ref              =   0;
    uc_ref              =   0;

    id_ref              =   0;
    iq_ref              =   0;
    spd_ref             =   0;
    pos_ref             =   0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    mode_list   <<  tr("0IDLE")\
                <<  tr("1ADC")\
                <<  tr("2MIPA")\
                <<  tr("3MPSA")\
                <<  tr("4COLD")\
                <<  tr("5CCLD")\
                <<  tr("6VCLD")\
                <<  tr("7PFVELC")\
                <<  tr("8PFPOSC")\
                <<  tr("9PFCURC")\
                <<  tr("10CSVELC")\
                <<  tr("11CSPOSC")\
                <<  tr("12CSCURC")\
                <<  tr("13HOME");
    this->comboBox->addItems(mode_list);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    spinBox_mode_ipa->installEventFilter(this);
    spinBox_mode_uaref->installEventFilter(this);
    spinBox_mode_ubref->installEventFilter(this);
    spinBox_mode_ucref->installEventFilter(this);

    spinBox_mode_udref->installEventFilter(this);
    spinBox_mode_uqref->installEventFilter(this);
    spinBox_mode_idref->installEventFilter(this);
    spinBox_mode_iqref->installEventFilter(this);

    spinBox_mode_spd_ref->installEventFilter(this);
    spinBox_mode_prof_spd_ref->installEventFilter(this);
    spinBox_mode_prof_pos_ref->installEventFilter(this);
    spinBox_mode_prof_iq_ref->installEventFilter(this);
    spinBox_mode_cs_spd_ref->installEventFilter(this);

    tbtn_plot_servoOnMode->setCheckable(true);
    label_plot_servo_onoff->setText(tr("SEV OFF"));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(spinBox_mode_ipa,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_idref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_iqref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));

    connect(spinBox_mode_uaref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_ubref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_ucref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_udref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_uqref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));

    connect(spinBox_mode_spd_ref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_prof_spd_ref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_prof_pos_ref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_prof_iq_ref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
    connect(spinBox_mode_cs_spd_ref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onModeCtlPanelModeChanged(int)));
    connect(tbtn_plot_servoOnMode,SIGNAL(clicked(bool)),this,SLOT(onBtnServoOnClicked(bool)));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void TabModeCtl::setupIcons(void)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  QSize iconSize(100,100);
  QIcon servoOnIcon;
  servoOnIcon.addPixmap(QPixmap(":/res/images/soff.png"),QIcon::Selected,QIcon::Off);
  servoOnIcon.addPixmap(QPixmap(":/res/images/son.png"),QIcon::Selected,QIcon::On);

  tbtn_plot_servoOnMode->setIcon(servoOnIcon);
  tbtn_plot_servoOnMode->setIconSize(iconSize);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void TabModeCtl::onModeSpinBoxValueChanged(int value)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  Q_UNUSED(value);
  QSpinBox *box = qobject_cast<QSpinBox *>(sender());
  box->setStyleSheet("color:red");
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


bool TabModeCtl::eventFilter(QObject *obj, QEvent *event)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  if (event->type() == QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      if (obj == spinBox_mode_ipa)//3 初始化相位
      {
          ipa_curr_ref              =   spinBox_mode_ipa->value();
          spinBox_mode_ipa->setStyleSheet("color:black");
      }
      else if ( (obj == spinBox_mode_uaref) || (obj == spinBox_mode_ubref)\
              || (obj == spinBox_mode_ucref) || (obj == spinBox_mode_udref)\
              || (obj == spinBox_mode_udref) || (obj == spinBox_mode_uqref))        //4 电压开环调试
      {
          ua_ref                    =   spinBox_mode_uaref->value();
          ub_ref                    =   spinBox_mode_ubref->value();
          uc_ref                    =   spinBox_mode_ucref->value();
          ud_ref                    =   spinBox_mode_udref->value();
          uq_ref                    =   spinBox_mode_uqref->value();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
          VpiSetUdRef(ud_ref);
          VpiSetUqRef(uq_ref);
          VpiSetUaRef(ua_ref);
          VpiSetUbRef(ub_ref);
          VpiSetUcRef(uc_ref);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
          spinBox_mode_uaref->setStyleSheet("color:black");
          spinBox_mode_ubref->setStyleSheet("color:black");
          spinBox_mode_ucref->setStyleSheet("color:black");
          spinBox_mode_udref->setStyleSheet("color:black");
          spinBox_mode_uqref->setStyleSheet("color:black");
      }
      else if ((obj == spinBox_mode_idref) || (obj == spinBox_mode_iqref))          //5 电流闭环调试
      {
          id_ref                    =   spinBox_mode_idref->value();
          iq_ref                    =   spinBox_mode_iqref->value();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
          VpiSetIdRef(id_ref);
          VpiSetIqRef(iq_ref);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
          spinBox_mode_idref->setStyleSheet("color:black");
          spinBox_mode_iqref->setStyleSheet("color:black");
      }
      else if (obj == spinBox_mode_spd_ref)                                         //6 速度闭环调试
      {
          spd_ref                   =   spinBox_mode_spd_ref->value();
          VpiSetSpdRef(spd_ref);

          spinBox_mode_spd_ref->setStyleSheet("color:black");
      }
      else if (obj == spinBox_mode_prof_spd_ref)                                    // 7 轮廓速度跟踪
      {
          spd_ref                   =   spinBox_mode_prof_spd_ref->value();
          VpiSetSpdRef(spd_ref);
          spinBox_mode_prof_spd_ref->setStyleSheet("color:black");
      }
      else if (obj == spinBox_mode_prof_pos_ref)                                    //8 周期同步速度跟踪
      {
          pos_ref                   =   spinBox_mode_prof_pos_ref->value();
          VpiSetPosRef(pos_ref);
          spinBox_mode_prof_pos_ref->setStyleSheet("color:black");
      }
      else if (obj == spinBox_mode_prof_iq_ref)                                     //8 周期同步位置跟踪
      {
          iq_ref                    =   spinBox_mode_prof_iq_ref->value();
          VpiSetIqRef(iq_ref);
          spinBox_mode_prof_iq_ref->setStyleSheet("color:black");
      }
      else if (obj == spinBox_mode_cs_spd_ref)                                      //8 周期同步位置跟踪
      {
          spd_ref                    =   spinBox_mode_cs_spd_ref->value();
          VpiSetSpdRef(spd_ref);
          spinBox_mode_cs_spd_ref->setStyleSheet("color:black");
      }

      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void TabModeCtl::onModeCtlPanelModeChanged(int mode)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  if(mode < stackedWidget_plot_mode->count())
  {
    stackedWidget_plot_mode->setCurrentIndex(mode);

    VpiSetServoWorkMode((tSeqWorkMode)(mode));

    switch(mode)
    {
        case    IDLE_TABSM_WORK:
        {
            break;
        }
        case    AOA_TABSM_WORK:
        {
            break;
        }
        case    MIPA_TABSM_WORK:
        {
            spinBox_mode_ipa->setValue(ipa_curr_ref);
            spinBox_mode_ipa->setStyleSheet("color:black");
            break;
        }
        case    MPSA_TABSM_WORK:
        {
            break;
        }
        case    COLD_TABSM_WORK:
        {
            spinBox_mode_uaref->setValue(ua_ref);
            spinBox_mode_ubref->setValue(ub_ref);
            spinBox_mode_ucref->setValue(uc_ref);
            spinBox_mode_udref->setValue(ud_ref);
            spinBox_mode_uqref->setValue(uq_ref);

            spinBox_mode_uaref->setStyleSheet("color:black");
            spinBox_mode_ubref->setStyleSheet("color:black");
            spinBox_mode_ucref->setStyleSheet("color:black");
            spinBox_mode_udref->setStyleSheet("color:black");
            spinBox_mode_uqref->setStyleSheet("color:black");

            break;
        }
        case    CCLD_TABSM_WORK:
        {
            spinBox_mode_idref->setValue(id_ref);
            spinBox_mode_iqref->setValue(iq_ref);

            spinBox_mode_idref->setStyleSheet("color:black");
            spinBox_mode_iqref->setStyleSheet("color:black");
            break;
        }
        case    VCLD_TABSM_WORK:
        {
            spinBox_mode_spd_ref->setValue(spd_ref);
            spinBox_mode_spd_ref->setStyleSheet("color:black");
            break;
        }
        case    PROF_VELC_TABSM_WORK:
        {
            spinBox_mode_prof_spd_ref->setValue(spd_ref);
            spinBox_mode_prof_spd_ref->setStyleSheet("color:black");
            break;
        }
        case    PROF_POSC_TABSM_WORK:
        {
            spinBox_mode_prof_pos_ref->setValue(pos_ref);
            spinBox_mode_prof_pos_ref->setStyleSheet("color:black");
            break;
        }
        case    PROF_CURC_TABSM_WORK:
        {
            spinBox_mode_prof_iq_ref->setValue(iq_ref);
            spinBox_mode_prof_iq_ref->setStyleSheet("color:black");
            break;
        }
        case    CS_VELC_TABSM_WORK:
        {
            spinBox_mode_cs_spd_ref->setValue(spd_ref);
            spinBox_mode_cs_spd_ref->setStyleSheet("color:black");
            break;
        }
        case    CS_POSC_TABSM_WORK:
        {
            break;
        }
        case    CS_CURC_TABSM_WORK:
        {
            break;
        }
        case    HOME_TABSM_WORK:
        {
            break;
        }
    }
  }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



void TabModeCtl::onBtnServoOnClicked(bool checked)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (checked)
    {
        label_plot_servo_onoff->setText(tr("SEV ON"));
    }
    else
    {
        label_plot_servo_onoff->setText(tr("SEV OFF"));
    }

    VpiServoEnable(checked);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


TabModeCtl::~TabModeCtl()
{

}
