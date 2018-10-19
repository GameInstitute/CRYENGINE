// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include <CryCore/Platform/platform_impl.inl>
#include "IPlugin.h"
#include "EquipPack/EquipPackDialog.h"
#include "EquipPack/EquipPackLib.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

//DECLARE_PYTHON_MODULE(gamesdk);

class EditorGameSDK : public IPlugin
{
public:

	EditorGameSDK()
	{
		GetIEditor()->RegisterDeprecatedPropertyEditor(ePropertyEquip, 
			std::function<bool(const string&, string&)>([](const string& oldValue, string& newValueOut)->bool
		{
			CEquipPackDialog dlg;
			dlg.SetCurrEquipPack(oldValue.GetString());
			if (dlg.DoModal() == IDOK)
			{
				newValueOut = dlg.GetCurrEquipPack().GetString();
				return true;
			}
			return false;
		}));

		CEquipPackLib::GetRootEquipPack().LoadLibs(true);

		char szEngineRootDir[_MAX_PATH];
		CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
		string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
		QString translationFile = "EditorGameSDK.qm";
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

	int32       GetPluginVersion() override { return 1; }
	const char* GetPluginName() override    { return "EditorGameSDK"; }
	const char* GetPluginDescription() override { return "Game SDK specific editor extensions"; }
};

REGISTER_PLUGIN(EditorGameSDK);
