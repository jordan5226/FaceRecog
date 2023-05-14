#if !defined(AFX_HtmlHlp_H__DCECC70A_859A_49ED_A5AE_F657AC700297__INCLUDED_)
#define AFX_HtmlHlp_H__DCECC70A_859A_49ED_A5AE_F657AC700297__INCLUDED_

#include <htmlhelp.h>

#pragma comment( lib, "htmlhelp.lib" )

void ShowContextHelp(CWnd *pWnd, POINT pt, CString strTextString)
{
	HH_POPUP hPop; // HTML Help popup structure
	
	// Initialize structure to NULLs	
	memset(&hPop, 0, sizeof(hPop)); 
	
	// Set size of structure
	hPop.cbStruct         = sizeof(hPop);		
	
	// Yellow background color
	hPop.clrBackground    = RGB(255, 255, 208);	
	
	hPop.clrForeground    = -1; // Font color	
	hPop.rcMargins.left   = -1;			 
	hPop.rcMargins.bottom = -1;
	hPop.rcMargins.right  = -1;
	hPop.rcMargins.top	  = -1;
	hPop.pt               = pt;	
	hPop.pszText          = strTextString; // Message from String Table
	hPop.pszFont          = NULL; // Font
    
	HtmlHelp( pWnd->GetSafeHwnd(), NULL, HH_DISPLAY_TEXT_POPUP, ( DWORD )( DWORD_PTR )&hPop );
}

void ShowContextHelp(CWnd *pWnd, POINT pt, int iCtrlID)
{
	CString s;
	 // Load help text from String Table
	 if(s.LoadString(iCtrlID))
	 {
		 ::ShowContextHelp(pWnd, pt, s);
		 /*
	  HH_POPUP hPop; // HTML Help popup structure

	  // Initialize structure to NULLs	
	  memset(&hPop, 0, sizeof(hPop)); 

	  // Set size of structure
	  hPop.cbStruct         = sizeof(hPop);		

	  // Yellow background color
	  hPop.clrBackground    = RGB(255, 255, 208);	

	  hPop.clrForeground    = -1; // Font color	
	  hPop.rcMargins.left   = -1;			 
	  hPop.rcMargins.bottom = -1;
	  hPop.rcMargins.right  = -1;
	  hPop.rcMargins.top	= -1;
	  hPop.pt               = pt;	
	  hPop.pszText          = s; // Message from String Table
	  hPop.pszFont          = NULL; // Font
    
	  HtmlHelp(pWnd->GetSafeHwnd(), NULL, 
	   HH_DISPLAY_TEXT_POPUP, (DWORD)&hPop);
	   */
	 } // End if found a help string for this request
}

#endif