#include "ListView.h"

#include <QDebug>
#include "PreDefine.h"
#include "PrismItem.h"

ListView::ListView(QWidget* parent):QListView(parent)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
}

void ListView::mousePressEvent(QMouseEvent* event)
{
	QAbstractItemView::mousePressEvent(event);
	
	QModelIndexList indexes = selectedIndexes();
	QStandardItem* item = nullptr;
	
	if (indexes.size() > 0)
	{
		QStandardItemModel* pModel = qobject_cast<QStandardItemModel*>(model());
		item = pModel->itemFromIndex(selectedIndexes().at(0));
	}

	Q_EMIT itemClicked(item);
	selectionModel()->clear();
}
