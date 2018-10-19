// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once
#include "IPlugin.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

class CVehicleEditorPlugin : public IPlugin
{
public:
	CVehicleEditorPlugin() 
	{
		char szEngineRootDir[_MAX_PATH];
		CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
		string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
		QString translationFile = "VehicleEditor.qm";
		QString translationFilesPath;
		QString editorSettingsFile = engineRootDir.c_str() + QString("/editor.ini");
		QSettings *pEditorSetting = new QSettings(editorSettingsFile, QSettings::IniFormat);
		QString editorLang = pEditorSetting->value("/Sandbox/Language").toString();
		if (!editorLang.isNull())
		{
			translationFilesPath = engineRootDir.c_str() + QString("/Editor/UI/Translations/") + editorLang + QString("/");
		}
		else
		{
			translationFilesPath = engineRootDir.c_str() + QString("/Editor/UI/Translations/") + QLocale::system().name().toLower() + QString("/");
		}
		QTranslator translator;
		translator.load(translationFile, translationFilesPath);
		QCoreApplication::installTranslator(&translator);
	}
	~CVehicleEditorPlugin() { /* exit point of the plugin, perform cleanup */ }

	int32       GetPluginVersion() { return 1; };
	const char* GetPluginName() { return "Sample Plugin"; };
	const char* GetPluginDescription() { return "Plugin used as a code sample to demonstrate Sandbox's plugin system"; };

private:
};
