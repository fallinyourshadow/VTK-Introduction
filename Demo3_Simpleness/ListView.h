#pragma once
#include <qlistview.h>
#include <qstandarditemmodel.h>
class ListView :
    public QListView
{
    Q_OBJECT
public:
    explicit ListView( QWidget* parent );
signals:
    void itemClicked(QStandardItem* item);
protected:
   virtual void  mousePressEvent( QMouseEvent* event ) override;
};

