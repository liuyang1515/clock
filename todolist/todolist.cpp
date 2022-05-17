#include"todolist.h"

#include<QLabel>
#include<QToolBar>
#include<QBoxLayout>
#include<qpushbutton.h>

CToDoList::CToDoList(){
    setMenuBar(nullptr);
    QWidget*pWidget=new QWidget(this);
    pWidget->setStyleSheet("background-color: #ECF0F1");
    setCentralWidget(pWidget);

    QVBoxLayout*pMainLayout=new QVBoxLayout();
    pWidget->setLayout(pMainLayout);

    QLabel*pwTitle=new QLabel(QString::fromLocal8Bit("待办事项"),this);
    pMainLayout->addWidget(pwTitle);
    pwTitle->setAlignment(Qt::AlignHCenter);
    pwTitle->setStyleSheet("font-size: 30pt;margin:10%");

    QHBoxLayout*pHlayoutlabels=new QHBoxLayout();
    pMainLayout->addLayout(pHlayoutlabels);

    QLabel*plblPending =new QLabel(QString::fromLocal8Bit("未完成"),this);
    plblPending->setStyleSheet("font-size:15pt;");
    pHlayoutlabels->addWidget(plblPending);

    QLabel*plblCompleted=new QLabel (QString::fromLocal8Bit("已完成"),this);
    plblCompleted->setStyleSheet("font-size:15pt;");
    pHlayoutlabels->addWidget(plblCompleted);

    QHBoxLayout*pHlayout=new QHBoxLayout();
    pMainLayout->addLayout(pHlayout);

    m_pwPending=new QListView(this);
    m_pwPending->setDragEnabled(true);
    m_pwPending->setAcceptDrops(true);
    m_pwPending->setDropIndicatorShown(true);
    m_pwPending->setDefaultDropAction(Qt::MoveAction);
    pHlayout->addWidget(m_pwPending);

    m_pwCompleted=new QListView(this);
    m_pwCompleted->setDragEnabled(true);
    m_pwCompleted->setAcceptDrops(true);
    m_pwCompleted->setDropIndicatorShown(true);
    m_pwCompleted->setDefaultDropAction(Qt::MoveAction);
    pHlayout->addWidget(m_pwCompleted);

    m_pwPending->setModel(new QStringListModel());
    m_pwCompleted->setModel(new QStringListModel());

    m_pwPending->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
             "QListView::item { background-color: #E74C3C; padding: 10%;"
             "border: 1px solid #C0392B; }"
             "QListView::item::hover { background-color: #C0392B }");

    m_pwCompleted->setStyleSheet
    ("QListView { font-size: 20pt; font-weight: bold;}"
     "QListView::item { background-color: #2ECC71; padding: 10%;"
     "border: 1px solid #27AE60;}"
     "QListView::item::hover{background-color:#27AE60}");

    QToolBar*pToolBar=new QToolBar(this);
    addToolBar(pToolBar);

//    m_pActAdd=new QAction(this);
//    m_pActAdd->setIcon(QIcon("add.jpeg"));
   QPushButton*temp1=new QPushButton(this);
   temp1->setText(QString::fromLocal8Bit("添加"));
    connect(temp1,&QPushButton::pressed,this,&CToDoList::onAdd);

//    m_pActRemove=new QAction(this);
//    m_pActRemove->setIcon(QIcon("remove.jpeg"));
    QPushButton*temp2=new QPushButton(this);
    temp2->setText(QString::fromLocal8Bit("删除"));
     temp2->move(100,0);
    connect(temp2,&QPushButton::pressed,this,&CToDoList::onRemove);

    pToolBar->addAction(m_pActAdd);
    pToolBar->addAction(m_pActRemove);
}

void CToDoList::onAdd()
{
    m_pwPending->model()->insertRow(m_pwPending->model()->rowCount());
    QModelIndex oIndex=m_pwPending->model()->index(
                m_pwPending->model()->rowCount()-1,0);

    m_pwPending->edit(oIndex);
}


void CToDoList::onRemove()
{
     QModelIndex oIndex=m_pwPending->currentIndex();
     m_pwPending->model()->removeRow(oIndex.row());
}

void CToDoList::closeEvent(QCloseEvent* event)
{
    emit function();
        this->hide();
        event->ignore();
}
