#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <select.h>
#include <resultwidght.h>
#include <pathwaywidget.h>
#include <modulewidget.h>
#include "mainwidget.h"
#include <QMouseEvent>
#include <QToolButton>`

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //隐藏菜单栏
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);

    int width=900; //获取界面的宽度

    //构建最小化、最大化、关闭按钮
    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);
    //获取最小化、关闭按钮图标
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    //设置最小化、关闭按钮在界面的位置
    minButton->setGeometry(width-46,5,20,20);
    closeButton->setGeometry(width-25,5,20,20);
    //设置鼠标移至按钮上的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    //设置最小化、关闭按钮的样式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");

    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

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
