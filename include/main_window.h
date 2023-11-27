#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "drawing_area.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Main_window; }
QT_END_NAMESPACE

class Main_window : public QMainWindow {
	Q_OBJECT

private:
	const QString NO_VALUE = "-";

	Ui::Main_window *ui;
	Drawing_area *drawing_area;

public:
	Main_window(QWidget *parent = nullptr);
	~Main_window();

public slots:
	void on_table_selection(int selected_table);
	void on_edit();
};
#endif // MAIN_WINDOW_H
