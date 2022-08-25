//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	parameter config service procudure                          //
//	file				:	PrmConfigService.h                                          //
//	Description			:	use for parameter config service in servo system            //
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/08/17	|	   liu.g        |		2022 - 2030			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __PRMCONFIGSERVICE_H__
#define __PRMCONFIGSERVICE_H__


#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include "DspCpu.h"
#include "Cia402AppEmu.h"



class ConfigService
{
public:
    ConfigService(void);
    ~ConfigService(void);
public:
    bool load(const QString& filePath);
    bool write(const QString& filePath);
private:
    void parse(const QJsonObject& json);
    QJsonObject create();
};


void    ServoPrmLoadFromFile(const QJsonObject& json);
void    ServoPrmWriteToFile(QJsonObject& json);

void    ServoPrmLoadFromFileToFlash(const QJsonObject& json);
void    ServoPrmWriteFromFlashToFile(QJsonObject& json);
void    ServoPrmReadFromFlashToRam(void);


#endif





//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
