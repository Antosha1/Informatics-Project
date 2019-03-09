//---------------------------------------------------------------------------
//
// Name:        ffApp.h
// Author:      SotnikovA
// Created:     20.05.2018 18:56:54
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __FFFRMApp_h__
#define __FFFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class ffFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
