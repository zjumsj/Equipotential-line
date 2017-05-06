// UseDoc.cpp : implementation of the CUseDoc class
//

#include "stdafx.h"
#include "Use.h"

#include "UseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseDoc

IMPLEMENT_DYNCREATE(CUseDoc, CDocument)

BEGIN_MESSAGE_MAP(CUseDoc, CDocument)
	//{{AFX_MSG_MAP(CUseDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseDoc construction/destruction

CUseDoc::CUseDoc()
{
	// TODO: add one-time construction code here

}

CUseDoc::~CUseDoc()
{
}

BOOL CUseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUseDoc serialization

void CUseDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CUseDoc diagnostics

#ifdef _DEBUG
void CUseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUseDoc commands

