// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

// CryEngine Source File.
// Copyright (C), Crytek, 1999-2014.

#include "StdAfx.h"
#include "TrackViewPlugin.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

#include <CryCore/Platform/platform_impl.inl>

#include "AnimationContext.h"
#include "TrackViewWindow.h"
#include "QtViewPane.h"
#include "Controls/DynamicPopupMenu.h"
#include "TrackViewSequenceManager.h"
#include "Objects/SequenceObject.h"
#include "Objects/EntityObject.h"
#include "TrackViewExporter.h"

REGISTER_VIEWPANE_FACTORY(CTrackViewWindow, "Track View", "Tools", false)

REGISTER_PLUGIN(CTrackViewPlugin)

CTrackViewExporter* CTrackViewPlugin::ms_pExporter;
CAnimationContext* CTrackViewPlugin::ms_pAnimationContext;
CTrackViewSequenceManager* CTrackViewPlugin::ms_pSequenceManager;

CTrackViewPlugin::CTrackViewPlugin()
{
	GetIEditor()->RegisterObjectContextMenuExtension(functor(*this, &CTrackViewPlugin::OnOpenObjectContextMenu));

	ms_pSequenceManager = new CTrackViewSequenceManager();
	ms_pAnimationContext = new CAnimationContext();
	ms_pExporter = new CTrackViewExporter();

	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
	QString translationFile = "EditorTrackView.qm";
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

CTrackViewPlugin::~CTrackViewPlugin()
{
	delete ms_pAnimationContext;
	delete ms_pSequenceManager;
	delete ms_pExporter;
}

CAnimationContext* CTrackViewPlugin::GetAnimationContext()
{
	return ms_pAnimationContext;
}

CTrackViewSequenceManager* CTrackViewPlugin::GetSequenceManager()
{
	return ms_pSequenceManager;
}

CTrackViewExporter* CTrackViewPlugin::GetExporter()
{
	return ms_pExporter;
}

void CTrackViewPlugin::OnOpenObjectContextMenu(CPopupMenuItem* pMenu, const CBaseObject* pObject)
{
	if (!pObject->IsKindOf(RUNTIME_CLASS(CEntityObject)))
	{
		return;
	}

	const CEntityObject* pEntityObject = static_cast<const CEntityObject*>(pObject);

	// TrackView sequences
	CTrackViewAnimNodeBundle bundle = CTrackViewPlugin::GetSequenceManager()->GetAllRelatedAnimNodes(pEntityObject);

	if (bundle.GetCount() > 0)
	{
		pMenu->AddSeparator();

		CPopupMenuItem& sequenceMenu = pMenu->Add("Track View Sequences");

		const unsigned int nodeListCount = bundle.GetCount();
		for (unsigned int nodeIndex = 0; nodeIndex < nodeListCount; ++nodeIndex)
		{
			CTrackViewSequence* pSequence = bundle.GetNode(nodeIndex)->GetSequence();

			if (pSequence)
			{
				sequenceMenu.Add(pSequence->GetName(), functor(*this, &CTrackViewPlugin::OnMenuOpenTrackView), bundle.GetNode(nodeIndex));
			}
		}
	}
}

void CTrackViewPlugin::OnMenuOpenTrackView(CTrackViewAnimNode* pAnimNode)
{
	GetIEditor()->OpenView("Track View");
	std::vector<CTrackViewWindow*> windows = CTrackViewWindow::GetTrackViewWindows();
	for (CTrackViewWindow* pWindow : windows)
	{
		// TODO
		//pWindow->ShowNode(pAnimNode);
	}
}

void CTrackViewPlugin::OnMove(const Vec3 targetPos, Vec3 sourcePos, bool bIsCopy)
{
	if (bIsCopy)
	{
		return;
	}

	const Vec3 offset = targetPos - sourcePos;

	const CTrackViewSequenceManager* pSequenceManager = CTrackViewPlugin::GetSequenceManager();
	const unsigned int numSequences = pSequenceManager->GetCount();

	for (unsigned int sequenceIndex = 0; sequenceIndex < numSequences; ++sequenceIndex)
	{
		CTrackViewSequence* pSequence = pSequenceManager->GetSequenceByIndex(sequenceIndex);
		CTrackViewTrackBundle trackBundle = pSequence->GetAllTracks();

		const unsigned int numTracks = trackBundle.GetCount();
		for (unsigned int trackIndex = 0; trackIndex < numTracks; ++trackIndex)
		{
			CTrackViewTrack* pTrack = trackBundle.GetTrack(trackIndex);
			if (pTrack->GetParameterType() != eAnimParamType_Position)
			{
				continue;
			}

			CTrackViewAnimNode* pAnimNode = pTrack->GetAnimNode();
			if (pAnimNode)
			{
				CEntityObject* pEntityObject = pAnimNode->GetNodeEntity();
				if (pEntityObject && pEntityObject->GetParent())
				{
					// If entity object of the node is parented to something then do not move the keys,
					// because the parent will be moved and therefore the object with it.
					continue;
				}
			}

			pTrack->OffsetKeys(TMovieSystemValue(offset));
		}
	}
}

