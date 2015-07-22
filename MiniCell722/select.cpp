#include "select.h"
#include "ui_select.h"
#include <QMessageBox>

Select::Select(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Select)
{
    ui->setupUi(this);
    QGridLayout *selectLayout = new QGridLayout(this);
    selectLayout->addWidget(ui->layoutWidget);
}

Select::~Select()
{
    delete ui;
}

void Select::on_notselected_doubleClicked(const QModelIndex &index)
{
    ui->selected->addItem(ui->notselected->currentItem()->text());
    QListWidgetItem * item = ui->notselected->takeItem(ui->notselected->currentRow());
    delete item;
    ui->selected->sortItems();
}

void Select::on_selected_doubleClicked(const QModelIndex &index)
{
    ui->notselected->addItem(ui->selected->currentItem()->text());
    QListWidgetItem * item = ui->selected->takeItem(ui->selected->currentRow());
    delete item;
    ui->notselected->sortItems();
}

void Select::on_submit_clicked()
{
    QList<QString> selectedList;
    int size = ui->selected->count();
    for(int i=0;i<size;i++){
       selectedList.append(ui->selected->item(i)->text());
    }
    if(size > 3){
        emit changeMainTab(1);
        emit send_selected_data(selectedList);
    }else{
        QMessageBox::warning(this, tr("Waring"),tr("Please select at least three oganisms!"),QMessageBox::Yes);
    }
}

void Select::on_pwBtn_clicked()
{
    QList<QString> selectedList;
    int size = ui->selected->count();
    for(int i=0;i<size;i++){
       selectedList.append(ui->selected->item(i)->text());
    }
    if(size > 3){
        emit changeMainTab(2);
        emit send_selected_data_pw(selectedList);
    }else{
        QMessageBox::warning(this, tr("Waring"),tr("Please select at least three oganisms!"),QMessageBox::Yes);
    }
}

void Select::on_mdBtn_clicked()
{
    QList<QString> selectedList;
    int size = ui->selected->count();
    for(int i=0;i<size;i++){
       selectedList.append(ui->selected->item(i)->text());
    }
    if(size > 3){
        emit changeMainTab(3);
        emit send_selected_data_md(selectedList);
    }else{
        QMessageBox::warning(this, tr("Waring"),tr("Please select at least three oganisms!"),QMessageBox::Yes);
    }
}
