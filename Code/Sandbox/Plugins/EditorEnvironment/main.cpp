// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "stdafx.h"

#include <CryCore/Platform/platform_impl.inl>

#include <IEditor.h>
#include <IPlugin.h>

#include "QtViewPane.h"
#include "EditorEnvironmentWindow.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

class CEditorEnvironment : public IPlugin
{
public:
	CEditorEnvironment()
	{
		char szEngineRootDir[_MAX_PATH];
		CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
		string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
		QString translationFile = "EditorEnvironment.qm";
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

	int32       GetPluginVersion() override                          { return 1; }
	const char* GetPluginName() override                             { return "Environment Editor"; }
	const char* GetPluginDescription() override						 { return ""; }
};

REGISTER_PLUGIN(CEditorEnvironment);

