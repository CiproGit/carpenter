#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include "types.h"
#include "table.h"
#include <QWidget>
#include <QMouseEvent>
#include <vector>

class Drawing_area : public QWidget {
	Q_OBJECT

private:
	const int PEN_WIDTH = 1;

	types::Ordered_pair<int> click_position;
	std::vector<table::Table *> table_list;

	int selected_table_index;

	int table_clicked(types::Ordered_pair<int> click_position) const;
	void toggle_selection(int table_index);
	void randomly_generate_table();

public:
	Drawing_area(QWidget *parent = nullptr);
	~Drawing_area();
	virtual void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	table::Table *get_table(unsigned int table_index) const;
	void edit_table(int length, int width, int chair_length, int chair_width, int chair_distance);

signals:
	void table_selection(int selected_table_index);
};

#endif // DRAWING_AREA_H
