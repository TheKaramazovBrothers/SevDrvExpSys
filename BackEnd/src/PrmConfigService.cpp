//=========================================================================================================
// project		:	parameter config service
// File			:	PrmConfigService.cpp
// discription	:	use for parameter config service
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g/1487
// date			:	2022/08/17
// copyright(C)	:	liu.g	(2022-2030)
//=========================================================================================================
#include    "SevCtlPrmTblDef.h"
#include    "PrmConfigService.h"

ConfigService::ConfigService(void)
{

}



ConfigService::~ConfigService(void)
{

}



bool ConfigService::load(const QString& filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    auto data = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));

    if(jsonDoc.isNull())
    {
        return false;
    }

    parse(jsonDoc.object());

    return true;
}

bool ConfigService::write(const QString& filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QJsonDocument doc(create());
    return file.write(doc.toJson());
}


void ConfigService::parse(const QJsonObject& json)
{
//    ServoPrmLoadFromFile(json);
    ServoPrmLoadFromFileToFlash(json);
    ServoPrmReadFromFlashToRam();
}



QJsonObject ConfigService::create()
{
    QJsonObject cObj;

//    ServoPrmWriteToFile(cObj);
    ServoPrmWriteFromFlashToFile(cObj);
    return cObj;
}


void    ServoPrmLoadFromFile(const QJsonObject& json)
{
    Uint16  utmp;
    Uint32  lutmp;

    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        double  dtmp;
        QString str;
        str             =   (char *)(DefCiA402PrmObjDic[i].pName);

        dtmp            =   json[str].toDouble();

        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            lutmp                                               =   dtmp;
            *((Uint32 *)(DefCiA402PrmObjDic[i].pVarPtr))        =   lutmp;
        }
        else
        {
            utmp                                                =   dtmp;
            *((Uint16 *)(DefCiA402PrmObjDic[i].pVarPtr))        =   utmp;
        }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }

}

void    ServoPrmWriteToFile(QJsonObject& json)
{
    double  dtmp;
    Uint16  utmp;
    Uint32  lutmp;
    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        QString str;
        str             =   (char *)(DefCiA402PrmObjDic[i].pName);

        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            lutmp           =   *((Uint32 *)(DefCiA402PrmObjDic[i].pVarPtr));
            dtmp            =   lutmp;
        }
        else
        {
            utmp            =   *((Uint16 *)(DefCiA402PrmObjDic[i].pVarPtr));
            dtmp            =   utmp;
        }

        json[str]           =   dtmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}



void    ServoPrmLoadFromFileToFlash(const QJsonObject& json)
{
    Uint16  utmp;
    Uint32  lutmp;

    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        double  dtmp;
        QString str;
        str             =   (char *)(DefCiA402PrmObjDic[i].pName);

        dtmp            =   json[str].toDouble();

        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            lutmp                                               =   dtmp;

            SclWriteFramPrmByID32(&lutmp, DefCiA402PrmObjDic[i].NonVolatileOffset);
        }
        else
        {
            utmp                                                =   dtmp;
            SclWriteFramPrmByID16(&utmp, DefCiA402PrmObjDic[i].NonVolatileOffset);
        }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}



void    ServoPrmWriteFromFlashToFile(QJsonObject& json)
{
    double  dtmp;
    Uint16  utmp;
    Uint32  lutmp;
    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        QString str;
        str             =   (char *)(DefCiA402PrmObjDic[i].pName);

        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            SclReadFramPrmByID32(DefCiA402PrmObjDic[i].NonVolatileOffset,&lutmp);
            dtmp            =   lutmp;
        }
        else
        {
            SclReadFramPrmByID16(DefCiA402PrmObjDic[i].NonVolatileOffset,&utmp);
            dtmp            =   utmp;
        }

        json[str]           =   dtmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}




void    ServoPrmReadFromFlashToRam(void)
{
    Uint16  utmp;
    Uint32  lutmp;
    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            SclReadFramPrmByID32(DefCiA402PrmObjDic[i].NonVolatileOffset,&lutmp);
            *((Uint32 *)(DefCiA402PrmObjDic[i].pVarPtr))            =   lutmp;
        }
        else
        {
            SclReadFramPrmByID16(DefCiA402PrmObjDic[i].NonVolatileOffset,&utmp);
            *((Uint16 *)(DefCiA402PrmObjDic[i].pVarPtr))            =   utmp;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}














//////////////////////////////////////////////// no more //////////////////////////////////////////////////
