#include "mainwindow.h"
#include "ui_mainwindow.h"
  #include <QFileDialog>
#include <warning.h>
  #include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
  #include <QColorDialog>
  #include <QErrorMessage>
#include <QProgressDialog>
  #include <QThread>
  #include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // connect(ui->pushButton_3,SIGNAL(clicked()),e,SLOT(showMessage("1111")));

    // ...existing code...
    auto *e = new QErrorMessage();
    connect(ui->pushButton_3, &QPushButton::clicked,
            [e]() { e->showMessage("1111"); });
    // ...existing code...




    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //新建文件
    QString fileName = QFileDialog::getSaveFileName(this, tr("新建文件"), QDir::currentPath(), 
    tr("Text Files (*.txt);;CSV Files (*.csv);;All Files (*)"));
    
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法创建文件: %1").arg(file.errorString()));
        return;
    }
    //写入文件
    QTextStream out(&file);
    out << "Hello, World!" ;
    out << "This is a new file." ;
    out << "You can add more content here." ;
    out << "Goodbye!" ;
    file.close();
    //提示用户文件创建成功
    QMessageBox::information(this, tr("成功"), tr("文件创建成功: %1").arg(fileName));

}


void MainWindow::on_pushButton_2_clicked()
{
    auto color =  QColorDialog::getColor();
    qDebug()<<color.red()<<color.green()<<color.blue();

}





void MainWindow::on_pushButton_4_clicked()
{
    int numFiles = 1000;
    QProgressDialog progress("Copying files...", "Abort Copy", 0, numFiles, this);
    progress.setWindowModality(Qt::WindowModal);

    for (int i = 0; i < numFiles; i++) {
        progress.setValue(i);

        // 添加一些延迟来模拟文件操作
        QThread::msleep(10);  // 睡眠10毫秒

        // 处理事件，使界面保持响应
        QApplication::processEvents();

        if (progress.wasCanceled())
            break;
        //... copy one file
    }
    progress.setValue(numFiles);
}



void MainWindow::on_pushButton_5_clicked()
{
    bool ok;
    // First get username
    QString username = QInputDialog::getText(this, 
        tr("Login"),
        tr("Username:"), 
        QLineEdit::Normal,
        QDir::home().dirName(), 
        &ok);
    
    if (ok && !username.isEmpty()) {
        // Then get password 
        QString password = QInputDialog::getText(this,
            tr("Login"),
            tr("Password:"),
            QLineEdit::Password,
            QString(),
            &ok);
            
        if (ok && !password.isEmpty()) {
            // Handle login credentials here
            qDebug() << "Username:" << username;
            qDebug() << "Password: [hidden]";
        }
    }
}

