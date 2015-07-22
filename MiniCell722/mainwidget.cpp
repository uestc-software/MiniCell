#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <select.h>
#include <resultwidght.h>
#include <pathwaywidget.h>
#include <modulewidget.h>
#include "mainwidget.h"
#include <QMouseEvent>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);

    //new widget
    Select *selcWidget = new Select(ui->tab_select);
    ResultWidght *rsltWidget = new ResultWidght(ui->tab_result);
    PathwayWidget *pwWidget = new PathwayWidget(ui->tab_pathway);
    ModuleWidget *mdWidget = new ModuleWidget(ui->tab_module);
    //set Layout to deal with Responsive Layout
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ui->gridLayoutWidget);    
    QGridLayout *tab0Layout = new QGridLayout(ui->tab_select);
    tab0Layout->addWidget(selcWidget);
    QGridLayout *tab1Layout = new QGridLayout(ui->tab_result);
    tab1Layout->addWidget(rsltWidget);
    QGridLayout *tab2Layout = new QGridLayout(ui->tab_pathway);
    tab2Layout->addWidget(pwWidget);
    QGridLayout *tab3Layout = new QGridLayout(ui->tab_module);
    tab3Layout->addWidget(mdWidget);
    //set connect
    connect(selcWidget,SIGNAL(changeMainTab(int)),ui->tabWidget,SLOT(setCurrentIndex(int)));
    connect(selcWidget,SIGNAL(send_selected_data(QList<QString>)),rsltWidget,SLOT(fetch_selected_data(QList<QString>)));
    connect(selcWidget,SIGNAL(send_selected_data_pw(QList<QString>)),pwWidget,SLOT(fetch_selected_data_pw(QList<QString>)));
    connect(selcWidget,SIGNAL(send_selected_data_md(QList<QString>)),mdWidget,SLOT(fetch_selected_data_md(QList<QString>)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
      mouse_press = true;
      //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
      move_point = event->pos();;
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

       //移动主窗体位置
       this->move(move_pos - move_point);
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mouse_press = false;
}
