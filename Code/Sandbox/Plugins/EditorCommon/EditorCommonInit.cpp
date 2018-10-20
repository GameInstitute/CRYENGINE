// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "EditorCommonInit.h"
#include "IPlugin.h"

#include <CryCore/Platform/platform_impl.inl>

#include <QMetaType>
#include "ProxyModels/ItemModelAttribute.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

static IEditor* g_editor = nullptr;

IEditor* GetIEditor() { return g_editor; }

void InitialTranslator(const char* domain, const char* qtTranslationFilename)
{
	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);

	string domainTranslationFilesPath;
	domainTranslationFilesPath = engineRootDir + "/Editor/UI/Languages/";

	setlocale(LC_ALL, "");
	bindtextdomain(domain, domainTranslationFilesPath.c_str());
	textdomain(domain);

	QString qtTranslationFilesPath;
	QString editorSettingsFile = engineRootDir.c_str() + QString("/editor.ini");
	QSettings *pEditorSetting = new QSettings(editorSettingsFile, QSettings::IniFormat);
	QString editorLang = pEditorSetting->value("/Sandbox/Language").toString();
	if (!editorLang.isNull())
	{
		qtTranslationFilesPath = engineRootDir.c_str() + QString("/Editor/UI/Translations/") + editorLang + QString("/");
		CryWarning(VALIDATOR_MODULE_EDITOR, VALIDATOR_WARNING, "Read editor.ini successfully, editor folder is %s", qtTranslationFilesPath.toLocal8Bit().constData());
	}
	else
	{
		qtTranslationFilesPath = engineRootDir.c_str() + QString("/Editor/UI/Translations/") + QLocale::system().name().toLower() + QString("/");
		CryWarning(VALIDATOR_MODULE_EDITOR, VALIDATOR_WARNING, "Read editor.ini failed, but use system language, editor folder is %s", qtTranslationFilesPath.toLocal8Bit().constData());
	}
	QTranslator translator;
	if (translator.load(qtTranslationFilename, qtTranslationFilesPath))
	{
		QCoreApplication::installTranslator(&translator);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_EDITOR, VALIDATOR_WARNING, "Install Qt Translator failed!");
	}
}

void EDITOR_COMMON_API EditorCommon::SetIEditor(IEditor* editor)
{
	g_editor = editor;
	auto system = GetIEditor()->GetSystem();
	gEnv = system->GetGlobalEnvironment();
}

void EDITOR_COMMON_API EditorCommon::Initialize()
{
	ModuleInitISystem(GetIEditor()->GetSystem(), "EditorCommon");

	InitialTranslator("EditorCommon", "EditorCommon.qm");

	RegisterPlugin();

	QMetaType::registerComparators<CItemModelAttribute*>();
}

void EDITOR_COMMON_API EditorCommon::Deinitialize()
{
	UnregisterPlugin();
	g_editor = nullptr;
	gEnv = nullptr;
}

