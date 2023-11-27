#include "main_window.h"
#include "./ui_main_window.h"

Main_window::Main_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Main_window) {
	ui->setupUi(this);

	this->drawing_area = new Drawing_area();
	ui->horizontalLayout->addWidget(this->drawing_area);

	connect(this->drawing_area, SIGNAL(table_selection(int)), this, SLOT(on_table_selection(int)));
	connect(ui->edit_pushButton, SIGNAL(clicked()), this, SLOT(on_edit()));
}

Main_window::~Main_window() {
	delete this->drawing_area;
	delete ui;
}

void Main_window::on_table_selection(int selected_table_index) {
	if (selected_table_index == -1) {
		ui->table_text->setText("nothing");
		ui->table_length_text->setText(NO_VALUE);
		ui->table_width_text->setText(NO_VALUE);

		ui->table_length_spinBox->setValue(table::MIN_LENGTH);
		ui->table_width_spinBox->setValue(table::MIN_WIDTH);

		ui->chair_length_text->setText(NO_VALUE);
		ui->chair_width_text->setText(NO_VALUE);
		ui->chair_distance_text->setText(NO_VALUE);

		ui->chair_length_spinBox->setValue(chair::MIN_LENGTH);
		ui->chair_width_spinBox->setValue(chair::MIN_WIDTH);
		ui->chair_distance_spinBox->setValue(chair::MIN_DISTANCE);
	}
	else {
		table::Table *table = this->drawing_area->get_table(selected_table_index);

		ui->table_text->setText(QString::number(selected_table_index));
		ui->table_length_text->setText(QString::number(table->get_length()));
		ui->table_width_text->setText(QString::number(table->get_width()));

		ui->table_length_spinBox->setValue(table->get_length());
		ui->table_width_spinBox->setValue(table->get_width());

		ui->chair_length_text->setText(QString::number(table->get_chair_length()));
		ui->chair_width_text->setText(QString::number(table->get_chair_width()));
		ui->chair_distance_text->setText(QString::number(table->get_chair_distance()));

		ui->chair_length_spinBox->setValue(table->get_chair_length());
		ui->chair_width_spinBox->setValue(table->get_chair_width());
		ui->chair_distance_spinBox->setValue(table->get_chair_distance());
	}
}

void Main_window::on_edit() {
	this->drawing_area->edit_table(ui->table_length_spinBox->value(),
								   ui->table_width_spinBox->value(),
								   ui->chair_length_spinBox->value(),
								   ui->chair_width_spinBox->value(),
								   ui->chair_distance_spinBox->value());
}
