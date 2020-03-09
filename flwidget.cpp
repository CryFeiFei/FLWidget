#include "flwidget.h"
#ifdef Q_OS_WIN
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#endif

namespace
{
	constexpr int BOUDERWIDTH = 10;
}

FLWidget::FLWidget(QWidget *parent) : QWidget(parent), m_bouderWidth(BOUDERWIDTH)
{
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setStyleSheet("background:red");

	setAttribute(Qt::WA_ShowModal);
	resize(500, 500);
}

FLWidget::~FLWidget()
{

}

void FLWidget::mousePressEvent(QMouseEvent *e)
{
#ifdef Q_OS_WIN
	if (e->button() == Qt::LeftButton)
		m_curPos = e->pos();
#endif
	return QWidget::mousePressEvent(e);
}
void FLWidget::mouseMoveEvent(QMouseEvent *e)
{
#ifdef Q_OS_WIN
	if (e->buttons() & Qt::LeftButton)
		move(e->pos() + pos() - m_curPos);
#endif
	return QWidget::mouseMoveEvent(e);
}

bool FLWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#ifdef Q_OS_WIN
	MSG* msg = (MSG*)message;
	switch(msg->message)
	{
		case WM_NCHITTEST:
			int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
			int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
			int nUseFulWidth = width() - m_bouderWidth;
			int nUseFulHeight = height() - m_bouderWidth;
			if (xPos < m_bouderWidth && yPos < m_bouderWidth)	//左上角
				*result = HTTOPLEFT;
			else if (xPos>= nUseFulWidth && yPos < m_bouderWidth)	//右上角
				*result = HTTOPRIGHT;
			else if (xPos < m_bouderWidth && yPos >= nUseFulHeight)	//左下角
				*result = HTBOTTOMLEFT;
			else if (xPos >= nUseFulWidth && yPos >= nUseFulHeight)	//右下角
				*result = HTBOTTOMRIGHT;
			else if (xPos < m_bouderWidth)	//左边
				*result =  HTLEFT;
			else if (xPos >= nUseFulWidth)	//右边
				*result = HTRIGHT;
			else if (yPos < m_bouderWidth)	//上边
				*result = HTTOP;
			else if (yPos >= nUseFulHeight)	//下边
				*result = HTBOTTOM;
			else
				return false;

			return true;
		}
#endif
	return QWidget::nativeEvent(eventType, message, result);	//此处返回false，留给其他事件处理器处理

}


