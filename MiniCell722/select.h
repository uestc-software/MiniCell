#ifndef SELECT_H
#define SELECT_H

#include <QWidget>

namespace Ui {
class Select;
}

class Select : public QWidget
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = 0);
    ~Select();

signals:
    void changeMainTab(int index);
    void send_selected_data(QList<QString> list);
    void send_selected_data_pw(QList<QString> list);
    void send_selected_data_md(QList<QString> list);

private:
    Ui::Select *ui;

private slots:
    void on_notselected_doubleClicked(const QModelIndex &index);
    void on_selected_doubleClicked(const QModelIndex &index);
    void on_submit_clicked();
    void on_pwBtn_clicked();
    void on_mdBtn_clicked();
};

#endif // SELECT_H
