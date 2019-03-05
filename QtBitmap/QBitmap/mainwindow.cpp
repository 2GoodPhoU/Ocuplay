#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QImageReader>
#include <QBitmap>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//practice to write to files
void MainWindow::on_pushButton_clicked()
{
    /*
    QFile file("C:/Users/erics/Desktop/QtBitmap/test.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title","file not open");
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
    */
}

//practice to find and read from a file
void MainWindow::on_pushButton_2_clicked()
{
    QString filter = "All File (*.*) ;; BMP File (*.bmp) ;; Text File (*.txt)";
    QString file_name = QFileDialog::getOpenFileName(this, "open a file", "C:/Users/erics/Desktop/QtBitmap", filter);

    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setPlainText(text);
    file.close();
}

//Finds a file, creates an image based on 1's and 0's in a file
void MainWindow::on_pushButton_3_clicked()
{
    //QString filter = "All File (*.*) ;; BMP File (*.bmp) ;; Text File (*.txt)";
    //QString file_name = QFileDialog::getOpenFileName(this, "open a file", "C:/Users/erics/Desktop/QtBitmap", filter);

    int sizeX = 600;
    int sizeY = 600;

    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB32);


    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
           image.setPixel(i, j, qRgb(10, 10, 255));
        }
    }

    QGraphicsScene *graphic = new QGraphicsScene(this);

    graphic->addPixmap( QPixmap::fromImage(image));

    ui->graphicsView->setScene(graphic);

}

//saves the text in the textedit box as a black and white bmp
void MainWindow::on_pushButton_4_clicked()
{
    //QString filter = "All File (*.*) ;; BMP File (*.bmp) ;; Text File (*.txt)";
    //QString file_name = QFileDialog::getOpenFileName(this, "open a file", "C:/Users/erics/Desktop/QtBitmap", filter);

    QString string = ui->textEdit->toPlainText();

    int sizeX = 600;
    int sizeY = 600;

    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB888);

    int sizeZ = sizeX * sizeY;
    for(int i = 0; i < sizeZ; i++)
    {
        QRgb rgb = string[i]=='0' ? qRgb(0,0,0) : qRgb(255,255,255);
        image.setPixel(i%sizeX, i/sizeY, rgb);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.bmp)"));
    if (!fileName.isEmpty())
    {
      image.save(fileName);
    }
}
