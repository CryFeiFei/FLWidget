#ifndef FLWIDGET_H
#define FLWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class FLWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FLWidget(QWidget *parent = nullptr);
	~FLWidget();

public:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;

private:
	int m_bouderWidth;
	QPoint m_curPos;

signals:

};

#endif // FLWIDGET_H
