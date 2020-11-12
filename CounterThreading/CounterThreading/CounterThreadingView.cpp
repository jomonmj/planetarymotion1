
// CounterThreadingView.cpp : implementation of the CCounterThreadingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CounterThreading.h"
#endif

#include "CounterThreadingDoc.h"
#include "CounterThreadingView.h"
#include "TestThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCounterThreadingView

IMPLEMENT_DYNCREATE(CCounterThreadingView, CView)

BEGIN_MESSAGE_MAP(CCounterThreadingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_START, &CCounterThreadingView::OnThreadStart)
	ON_COMMAND(ID_THREAD_PAUSE, &CCounterThreadingView::OnThreadPause)
	ON_COMMAND(ID_THREAD_RESUME, &CCounterThreadingView::OnThreadResume)
END_MESSAGE_MAP()

// CCounterThreadingView construction/destruction

CCounterThreadingView::CCounterThreadingView()
	
{
	m_iCounter = 0;
	 theta=0, a=200, b=190,p=295,q=240;
	
	 t = 3.14 / 180;
	 x = 350, y = 350;
	 x1 = 0, x2 = 0, x3 = 0, x4 = 0;
}

CCounterThreadingView::~CCounterThreadingView()
{
}

BOOL CCounterThreadingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCounterThreadingView drawing

void CCounterThreadingView::OnDraw(CDC* pDC)
{
	CCounterThreadingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//m_iCounter++;
	CString strCounter;
	strCounter.Format(L"The Counter is %d", m_iCounter);
	pDC->TextOut(700, 400, strCounter);



	//largest orbit

	CPen redpen;
    redpen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldpen1 = pDC->SelectObject(&redpen);
	pDC->Ellipse(10, 70, 600, 550);
    pDC->SelectObject(pOldpen1);



	//Smallest orbit

	CPen greenpen;
	greenpen.CreatePen(PS_SOLID, 2, RGB(0, 400, 0));
	CPen* pOldpen = pDC->SelectObject(&greenpen);
	pDC->Ellipse(100,120, 500, 500);
	pDC->SelectObject(pOldpen);



	//sun with black color

	CBrush brushblack(RGB(0, 0, 0));
	CBrush *pOldBrush = pDC->SelectObject(&brushblack);
	pDC->Ellipse(250, 250, 350, 350);
	pDC->SelectObject(pOldBrush);





	// smallest orbit rotation
	
	for (int i = 0; i < m_iCounter; i += 1)
	{
		theta = i;
		x = a * cos(t*theta);

		y = b* sin(t*theta);

	}
	for (int i = 0; i < m_iCounter; i += 1)
	{
		CBrush brushblue(RGB(0, 0, 255));
		CBrush *pOldBrush = pDC->SelectObject(&brushblue);


		pDC->Ellipse( 300+x + 20,   310+y + 20,300+  x - 20, 310+ y - 20);

	Invalidate();
	pDC->SelectObject(pOldBrush);


}


	
	// largest orbit rotation

	for (int i = 0; i < m_iCounter; i += 1)
	{
		theta = i;
		x = p * cos(t*theta);

		y = q * sin(t*theta);

	}
	for (int i = 0; i < m_iCounter; i += 1)
	{
		CBrush brushblue(RGB(0, 0, 0));
		CBrush *pOldBrush = pDC->SelectObject(&brushblue);


		pDC->Ellipse( x + 20,   y + 20,  x - 20,  y - 20);

		Invalidate();
		pDC->SelectObject(pOldBrush);


	}



}
	
	
	

	




// CCounterThreadingView printing

BOOL CCounterThreadingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCounterThreadingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCounterThreadingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCounterThreadingView diagnostics

#ifdef _DEBUG
void CCounterThreadingView::AssertValid() const
{
	CView::AssertValid();
}

void CCounterThreadingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCounterThreadingDoc* CCounterThreadingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCounterThreadingDoc)));
	return (CCounterThreadingDoc*)m_pDocument;
}
#endif //_DEBUG


// CCounterThreadingView message handlers


void CCounterThreadingView::OnThreadStart()
{
	pThread = AfxBeginThread(CTestThread::RunThreadFunction, this);
}


void CCounterThreadingView::OnThreadPause()
{
	pThread -> SuspendThread();
}


void CCounterThreadingView::OnThreadResume()
{
	pThread->ResumeThread();
}
