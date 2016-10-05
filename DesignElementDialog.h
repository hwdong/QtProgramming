#pragma once
//Refer to : http://zetcode.com/gui/qt4/widgets/
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QLineEdit>
#include < QComboBox>
#include <QStringList.h>

#include <QDialog>
class DesignElementDialog : public QDialog
//class DesignElementDialog : public QWidget
{
	Q_OBJECT

public:
	DesignElementDialog(QDialog *parent = 0, char *name = 0) :QDialog(parent)
//	DesignElementDialog(QWidget *parent = 0, char *name = 0) :QWidget(parent) 
	{
		QLabel *x = new QLabel("x:", this);
		x->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		QLabel *y = new QLabel("y:", this);
		y->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		QLabel *d = new QLabel("d:", this);
		d->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		QLabel *k = new QLabel("k:", this);
		k->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	

		QLabel *type = new QLabel("type:", this);
		type->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		lineEdit_x = new QLineEdit(this);
		lineEdit_y = new QLineEdit(this);
		lineEdit_d = new QLineEdit(this);
		lineEdit_k = new QLineEdit(this);
		comboBox_type = new QComboBox(this);

		QStringList options = {"source","sing","sandle","center","regular"};
		comboBox_type->addItems(options);

		set_data(0.5,0.5,0.0001,1,2);
		QGridLayout *grid = new QGridLayout();

		grid->addWidget(x, 0, 0);
		grid->addWidget(lineEdit_x, 0, 1);
		grid->addWidget(y, 1, 0);
		grid->addWidget(lineEdit_y, 1, 1);
		grid->addWidget(d, 2, 0);
		grid->addWidget(lineEdit_d, 2, 1);
		grid->addWidget(k, 3, 0);
		grid->addWidget(lineEdit_k, 3, 1);
		grid->addWidget(type, 4, 0);
		grid->addWidget(comboBox_type, 4, 1);

		setLayout(grid);

		setWindowTitle("DesignElementDlg");

	}
//	void get_data(double &x, double &y, double &d, double &k, QString &design_element_type)
	void get_data(double &x, double &y, double &d, double &k, int &design_element_type)
	{
		x = lineEdit_x->text().toDouble();
		y = lineEdit_y->text().toDouble();
		d = lineEdit_d->text().toDouble();
		k = lineEdit_k->text().toDouble();
		design_element_type = comboBox_type->currentIndex();
	}
	void set_data(const double &x, const  double &y, const double &d, const double &k, const int &design_element_type)
	{
		lineEdit_x->setText(QString("%1").arg(x));
		lineEdit_y->setText(QString("%1").arg(y));
		lineEdit_d->setText(QString("%1").arg(d));
		lineEdit_k->setText(QString("%1").arg(k));

		comboBox_type->setCurrentIndex(design_element_type);
	}
private:
	QLineEdit *lineEdit_x=0, *lineEdit_y=0, *lineEdit_d=0, *lineEdit_k=0;
	QComboBox *comboBox_type=0;	
};
