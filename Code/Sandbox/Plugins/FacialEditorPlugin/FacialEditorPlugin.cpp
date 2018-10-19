// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "FacialEditorPlugin.h"

#include <CryCore/Platform/platform_impl.inl>

#include "Vicon/Vicon_ClientCodes.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>	

REGISTER_PLUGIN(CFacialEditorPlugin);

CFacialEditorPlugin::CFacialEditorPlugin()
{
#ifndef DISABLE_VICON
	
	REGISTER_CVAR(m_fViconScale, 1.0f, VF_NULL, "Scale from Vicon to our Joystick system");
	REGISTER_CVAR(m_fViconBend, 0.001f, VF_NULL, "Bending biped spine (Vicon)");
	REGISTER_CVAR(m_fViconScale, 1.0f, VF_NULL, "Scale from Vicon to our Joystick system");
	m_ViconClient = new CViconClient(this);
#endif

	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
	QString translationFile = "FacialEditorPlugin.qm";
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

void CFacialEditorPlugin::OnEditorNotifyEvent(EEditorNotifyEvent event)
{
#ifndef DISABLE_VICON
	if (m_ViconClient && event == eNotify_OnIdleUpdate)
	{
		m_ViconClient->Update();
	}
#endif
}

#ifndef DISABLE_VICON
namespace Commands
{
	void ViconConnect()
	{
		if (!CFacialEditorPlugin::GetInstance()->GetViconClient()->Connect(nullptr))
			CryLog("<Vicon Client> Connection to Vicon server failed.");
		else
			CryLog("<Vicon Client> Connection to Vicon server succedeed.");
	}

	void ViconDisconnect()
	{
		CFacialEditorPlugin::GetInstance()->GetViconClient()->Disconnect();
	}
}

REGISTER_PYTHON_COMMAND_WITH_EXAMPLE(&Commands::ViconConnect, vicon, connect, "Connects Vicon", "");
REGISTER_PYTHON_COMMAND_WITH_EXAMPLE(&Commands::ViconDisconnect, vicon, disconnect,"Connects Vicon", "");
#endif

