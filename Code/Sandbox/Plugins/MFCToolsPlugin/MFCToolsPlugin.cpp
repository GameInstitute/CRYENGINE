// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "MFCToolsPlugin.h"

#include "IPlugin.h"
#include <CryCore/Platform/platform_impl.inl>

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

static IEditor* g_editor = nullptr;
IEditor* GetIEditor() { return g_editor; }

PLUGIN_API void MFCToolsPlugin::SetEditor(IEditor* editor)
{
	g_editor = editor;
	auto system = GetIEditor()->GetSystem();
	gEnv = system->GetGlobalEnvironment();
}

PLUGIN_API void MFCToolsPlugin::Initialize()
{
	ModuleInitISystem(GetIEditor()->GetSystem(), "MFCToolsPlugin");
	RegisterPlugin();

	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
	QString translationFile = "MFCToolsPlugin.qm";
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

PLUGIN_API void MFCToolsPlugin::Deinitialize()
{
	UnregisterPlugin();
	g_editor = nullptr;
	gEnv = nullptr;
}

