#include "memo.h"
#include "ui_memo.h"

memo::memo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::memo)
{
    ui->setupUi(this);
       setWindowTitle("memo");
select();
        connect(ui->pushButton,&QPushButton::pressed,[=](){
            int curRow = ui->tableView->currentIndex().row();     //鼠标选择删除第几行
            QModelIndex index = ui->tableView->currentIndex();
            int id=index.sibling(curRow,0).data().toInt();
            QSqlQuery query;
            query.prepare("select  *from reminder4 where id= :id ");  //like模糊查询没成功
            query.bindValue(":id",id);
            query.exec();
            while (query.next()) {
                    QString temp = query.value(2).toString();
                    ui->textEdit_2->clear();
                    ui->textEdit_2->insertPlainText( temp );
            }
        });


   // ui->setupUi(this);
}

memo::~memo()
{
    db.close();
    delete ui;
}
void memo::on_save_clicked()
{

  if( ui->textEdit->text()==""){
      QMessageBox::information(this,tr("提示"),tr("你还没有设定主题"),QMessageBox::Ok);
  }
  else{
          QSqlQuery query;
      query.prepare("insert into reminder4 (id,theme,content)values(1:theme , :content )"); //id自动增加，先从1起，之后无需手动插入
       query.prepare("insert into reminder4(id,theme,content)values(:id,:theme , :content )");
       query.bindValue(":theme",ui->textEdit->text());            //从输入框插入数据
       query.bindValue(":content",ui->textEdit_2->toPlainText());
       query.exec();
        select();//显示表格
        ui->textEdit->clear();
        ui->textEdit_2->clear();
  }




}

void memo::on_del_clicked()
{
    QSqlQuery query;

    int curRow = ui->tableView->currentIndex().row();     //鼠标选择删除第几行

    QModelIndex index = ui->tableView->currentIndex();

    int id=index.sibling(curRow,0).data().toInt();

    query.prepare("delete from reminder4 where id = :id");
    query.bindValue(":id",id);
    query.exec();
    select();

 }

void memo::select()
{  //将sql表格显示到tableView里
    QSqlQueryModel *model = new QSqlQueryModel;
   model->setQuery("select * from reminder4");
   ui->tableView   ->setModel(model);
        ui->tableView->show();
}

 void memo::on_search_clicked()
 {    QSqlQuery query;
     ui -> tableView -> clearSpans(); //tableview清空
     QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);

      query.prepare("select  *from reminder4 where theme= :theme ");  //like模糊查询没成功
      query.bindValue(":theme",ui->textEdit_3->text());

      query.exec();


      model->setQuery(query);



       model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("theme"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("content"));


        ui->tableView->setModel(model);
 }

  void memo::on_back_clicked()

    {
       select();

    }
  void memo::closeEvent(QCloseEvent* event)
  {
      emit function();
          this->hide();
       event->ignore();
  }
