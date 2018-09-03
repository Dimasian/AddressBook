#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include<QLineEdit>
#include <QPushButton>

 class FindDialog : public QDialog
 {
     Q_OBJECT

 public:
     FindDialog(QWidget *parent = 0);
     QString getFindText();

 public slots:
     void findClicked();

 private:
     QPushButton *findButton;
     QLineEdit *lineEdit;
     QString findText;
 };

#endif
