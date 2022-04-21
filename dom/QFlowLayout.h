#pragma once

#ifndef QFLOWLAYOUT_H
#define QFLOWLAYOUT_H
#include <QWidget>
#include <QLayout>
#include <QRect>
#include <QStyle>
#include <QRect>

/*
 * 自定义流式布局
 *
 *网址： https://blog.csdn.net/wtl1992/article/details/110562741
 *
 */
class QFlowLayout : public QLayout
{
public:
	explicit QFlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
	explicit QFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
	~QFlowLayout();

	void addItem(QLayoutItem *item) Q_DECL_OVERRIDE;
	int horizontalSpacing() const;
	int verticalSpacing() const;
	Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
	bool hasHeightForWidth() const Q_DECL_OVERRIDE;
	int heightForWidth(int) const Q_DECL_OVERRIDE;
	int count() const Q_DECL_OVERRIDE;
	QLayoutItem *itemAt(int index) const Q_DECL_OVERRIDE;
	QSize minimumSize() const Q_DECL_OVERRIDE;
	void setGeometry(const QRect &rect) Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
	QLayoutItem *takeAt(int index) Q_DECL_OVERRIDE;

private:
	int doLayout(const QRect &rect, bool testOnly) const;
	int smartSpacing(QStyle::PixelMetric pm) const;

private:
	QList<QLayoutItem *> x_itemList;
	int x_hSpace;
	int x_vSpace;
};

#endif // QFLOWLAYOUT_H
