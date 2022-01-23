#ifndef TASKSDIALOG_H
#define TASKSDIALOG_H
#include <QDialog>
#include<scanner.h>


namespace Ui {
class TasksDialog;
}

class TasksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TasksDialog(QWidget *parent = nullptr, Scanner *scanner = nullptr);
    ~TasksDialog();
    void update();
    void edit();


private slots:
    void apply();

private:
    Ui::TasksDialog *ui;
    Scanner* scanner;
};

#endif // TASKSDIALOG_H
