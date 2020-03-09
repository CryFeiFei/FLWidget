#ifndef FLWIDGET_LINUX_H
#define FLWIDGET_LINUX_H

#include <QWidget>
#include "xutil.h"

class FLWidget_Linux : public QWidget
{
	Q_OBJECT
public:
	explicit FLWidget_Linux(QWidget *parent = nullptr);

signals:

public slots:

public:
	void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;

public:
	XUtils::CornerEdge resizingCornerEdge;
	Qt::WindowFlags     dwindowFlags;
};

#endif // FLWIDGET_LINUX_H
