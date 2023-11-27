#include "drawing_area.h"
#include "utils.h"
#include <QPainter>

Drawing_area::Drawing_area(QWidget *parent) : QWidget(parent) {
	this->click_position.x = 0;
	this->click_position.y = 0;

	this->selected_table_index = -1; // Nothing selected

	srand(static_cast<unsigned>(time(nullptr)));
}

Drawing_area::~Drawing_area() {
	for (table::Table *table : this->table_list) {
		delete table;
	}
}

/*!
 * \brief If user clicked a table, it returns the corresponding index; otherwise it returns -1
 * \param click_position
 * \return
 */
int Drawing_area::table_clicked(types::Ordered_pair<int> click_position) const {
	if (this->table_list.size() == 0) return -1;

	int table_index = 0;

	// Check click in every table
	for (table::Table *table : this->table_list) {
		if (table->clicked(click_position)) {
			return table_index;
		}
		table_index++;
	}

	return -1;
}

void Drawing_area::toggle_selection(int table_index) {
	if (table_index == this->selected_table_index) this->selected_table_index = -1; // Deselect the clicked table
	else this->selected_table_index = table_index; // Select the clicked table

	emit(table_selection(this->selected_table_index));
}

void Drawing_area::randomly_generate_table() {
	int length = random_number(table::MIN_LENGTH, table::MAX_LENGTH);
	int width = random_number(table::MIN_WIDTH, table::MAX_WIDTH);

	this->table_list.push_back(new table::Table(this->click_position, length, width));
}

void Drawing_area::paintEvent(QPaintEvent *event) {
	QPen pen(Qt::black);
	pen.setWidth(PEN_WIDTH);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(pen);

	// Draw all tables
	for (table::Table *table : this->table_list) {
		table->draw(&painter);
	}

	// Highlight selected table
	if (this->selected_table_index != -1) {
		this->table_list.at(this->selected_table_index)->highlight(&painter);
	}
}

void Drawing_area::mousePressEvent(QMouseEvent *event) {
	this->click_position.x = event->position().x();
	this->click_position.y = event->position().y();

	int table_index = table_clicked(this->click_position);
	if (table_index == -1) { // Clicked in the void
		randomly_generate_table(); // Create a new table
	}
	else { // Clicked inside a table
		toggle_selection(table_index);
	}

	update(); // Call paintEvent
}

table::Table *Drawing_area::get_table(unsigned int table_index) const {
	return this->table_list.at(table_index);
}

/*!
 * \brief It modifies the dimensions of table and its chairs
 * \param length
 * \param width
 * \param chair_length
 * \param chair_width
 * \param chair_distance
 */
void Drawing_area::edit_table(int length, int width, int chair_length, int chair_width, int chair_distance) {
	if (this->selected_table_index != -1) {
		types::Ordered_pair<int> centre = this->table_list.at(this->selected_table_index)->get_centre();

		delete this->table_list.at(this->selected_table_index);
		this->table_list.at(this->selected_table_index) = new table::Table(centre, length, width, chair_length, chair_width, chair_distance);

		update();
	}
}
