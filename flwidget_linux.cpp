#include "flwidget_linux.h"
#include <QLayout>
#include <QMouseEvent>

namespace
{
	#define ResizeHandleWidth 10
}

FLWidget_Linux::FLWidget_Linux(QWidget *parent) : QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setStyleSheet("background-color:red;");

	QHBoxLayout* layoutMain = new QHBoxLayout(this);
	layoutMain->setContentsMargins(ResizeHandleWidth, ResizeHandleWidth, ResizeHandleWidth, ResizeHandleWidth);
	this->setLayout(layoutMain);
	resizingCornerEdge = XUtils::CornerEdge::kInvalid;
	setMouseTracking(true);

	XUtils::SetMouseTransparent(this, true);

	setAttribute(Qt::WA_ShowModal);

	resize(400, 400);
}


void FLWidget_Linux::mouseMoveEvent(QMouseEvent *event)
{
#ifdef Q_OS_LINUX
	const int x = event->x();
	const int y = event->y();

	if (resizingCornerEdge == XUtils::CornerEdge::kInvalid)
	{
		XUtils::UpdateCursorShape(this, x, y, this->layout()->contentsMargins(), ResizeHandleWidth);
	}
#endif

	return QWidget::mouseMoveEvent(event);
}

void FLWidget_Linux::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_LINUX
	const int x = event->x();
	const int y = event->y();
	if (event->button() == Qt::LeftButton)
	{
		const XUtils::CornerEdge ce = XUtils::GetCornerEdge(this, x, y, this->layout()->contentsMargins(), ResizeHandleWidth);
		if (ce != XUtils::CornerEdge::kInvalid)
		{
			resizingCornerEdge = ce;
			//send x11 move event dont send mouserrelease event
			XUtils::SendButtonRelease(this, event->pos(), event->globalPos());
			XUtils::StartResizing(this, QCursor::pos(), ce);
		}
	}
#endif
	return QWidget::mousePressEvent(event);
}

void FLWidget_Linux::resizeEvent(QResizeEvent *e)
{
#ifdef Q_OS_LINUX
	int resizeHandleWidth = ResizeHandleWidth;
	XUtils::SetWindowExtents(this, this->layout()->contentsMargins(), resizeHandleWidth);
#endif
	return QWidget::resizeEvent(e);
}

void FLWidget_Linux::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef Q_OS_LINUX
	resizingCornerEdge = XUtils::CornerEdge::kInvalid;
#endif
	return QWidget::mouseReleaseEvent(event);
}

