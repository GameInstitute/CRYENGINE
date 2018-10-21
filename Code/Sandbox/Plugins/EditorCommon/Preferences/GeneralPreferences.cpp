// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#include <StdAfx.h>

#include "GeneralPreferences.h"

#include <CrySerialization/yasli/decorators/Range.h>
#include <CrySerialization/Color.h>

EDITOR_COMMON_API SEditorGeneralPreferences gEditorGeneralPreferences;
REGISTER_PREFERENCES_PAGE_PTR(SEditorGeneralPreferences, &gEditorGeneralPreferences)

EDITOR_COMMON_API SEditorFilePreferences gEditorFilePreferences;
REGISTER_PREFERENCES_PAGE_PTR(SEditorFilePreferences, &gEditorFilePreferences)

//////////////////////////////////////////////////////////////////////////
// General Preferences
//////////////////////////////////////////////////////////////////////////
SEditorGeneralPreferences::SEditorGeneralPreferences()
	: SPreferencePage("General", "General/General")
	, m_enableSourceControl(false)
	, m_saveOnlyModified(true)
	, m_freezeReadOnly(true)
	, m_showTimeInConsole(false)
	, showWindowsInTaskbar(true)
{
}

bool SEditorGeneralPreferences::Serialize(yasli::Archive& ar)
{
	// General
	ar.openBlock("generalSettings", gettext("General"));
	ar(m_enableSourceControl, "enableSourceControl", gettext("Enable Source Control"));
	ar(m_saveOnlyModified, "saveOnlyModified", gettext("External layers: Save only Modified"));
	ar(m_freezeReadOnly, "freezeReadOnly", gettext("Freeze Read-only external layer on Load"));
	ar(showWindowsInTaskbar, "showWindowsInTaskbar", gettext("Show all windows in taskbar (requires restart)"));
	ar.closeBlock();

	ar.openBlock("Console", gettext("Console"));
	ar(m_showTimeInConsole, "showTimeInConsole", gettext("Show Time In Console"));
	ar.closeBlock();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// File Preferences
//////////////////////////////////////////////////////////////////////////
SEditorFilePreferences::SEditorFilePreferences()
	: SPreferencePage("File", "General/File")
	, openCSharpSolution(true)
	, textEditorCSharp("devenv.exe")
	, textEditorScript("notepad++.exe")
	, textEditorShaders("notepad++.exe")
	, textEditorBspaces("notepad++.exe")
	, textureEditor("Photoshop.exe")
	, animEditor("")
	, strStandardTempDirectory("Temp")
	, m_autoSaveTime(10)
	, autoSaveMaxCount(3)
	, autoSaveEnabled(false)
	, filesBackup(true)
{
}

bool SEditorFilePreferences::Serialize(yasli::Archive& ar)
{
	auto prevAutoSavetime = m_autoSaveTime;
	ar.openBlock("files", gettext("Files"));
	ar(filesBackup, "filesBackup", gettext("Backup on Save"));
	ar.closeBlock();

	ar.openBlock("textEditors", gettext("Text Editors"));
	ar(openCSharpSolution, "openCSharSolution", gettext("Open C# solution instead of files"));
	ar(textEditorCSharp, "textEditorCSharp", gettext("C# Text Editor"));
	ar(textEditorScript, "textEditorScript", gettext("Scripts Text Editor"));
	ar(textEditorShaders, "textEditorShaders", gettext("Shaders Text Editor"));
	ar(textEditorBspaces, "textEditorBspaces", gettext("BSpace Text Editor"));
	ar(strStandardTempDirectory, "strStandardTempDirectory", gettext("Standard Temporary Directory"));
	ar(textureEditor, "textureEditor", gettext("Texture Editor"));
	ar(animEditor, "animEditor", gettext("Animation Editor"));
	ar.closeBlock();

	// Autobackup table.
	ar.openBlock("autoBackup", gettext("Auto Back-up"));
	ar(autoSaveEnabled, "autoSaveEnabled", gettext("Enable"));
	ar(yasli::Range(m_autoSaveTime, 2, 10000), "autoSaveTime", gettext("Auto Backup Interval (Minutes)"));
	ar(yasli::Range(autoSaveMaxCount, 1, 100), "autoSaveMaxCount", gettext("Maximum Auto Backups"));
	ar.closeBlock();

	if (ar.isInput() && prevAutoSavetime != m_autoSaveTime)
	{
		autoSaveTimeChanged();
	}

	return true;
}

