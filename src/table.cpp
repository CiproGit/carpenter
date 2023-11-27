#include "table.h"
#include "utils.h"

namespace table {
	Table::Table(types::Ordered_pair<int> centre, int length, int width) {
		this->centre = centre;

		this->length = length;
		this->width = width;

		this->rect = new QRect(this->centre.x - this->length / 2, this->centre.y - this->width / 2, this->length, this->width); // There will be a small graphical glitch for odd numbers, due to integer division. I will ignore it

		randomly_generate_chairs();
	}

	Table::Table(types::Ordered_pair<int> centre, int length, int width, int chair_length, int chair_width, int chair_distance) {
		this->centre = centre;

		this->length = length;
		this->width = width;

		this->rect = new QRect(this->centre.x - this->length / 2, this->centre.y - this->width / 2, this->length, this->width); // There will be a small graphical glitch for odd numbers, due to integer division. I will ignore it

		this->chair_length = chair_length;
		this->chair_width = chair_width;
		this->chair_distance = chair_distance;

		generate_chairs();
	}

	Table::~Table() {
		for (chair::Chair *chair : this->chair_list) {
			delete chair;
		}

		delete this->rect;
	}

	/*!
	 * \brief It generates chairs surrounding the table
	 */
	void Table::generate_chairs() {
		// South
		{
			int a = this->length + this->chair_distance;
			int b = this->chair_length + this->chair_distance;

			int chair_number = a / b;
			int reminder = a % b;

			types::Ordered_pair<int> chair_centre;
			chair_centre.x = this->centre.x - this->length / 2 + this->chair_length / 2 + reminder / 2;
			chair_centre.y = this->centre.y + this->width / 2 + this->chair_width / 2;

			for (int i = 0; i < chair_number; i++) {
				this->chair_list.push_back(new chair::Chair(chair_centre, this->chair_length, this->chair_width, chair::Orientation::UP));
				chair_centre.x += this->chair_length + this->chair_distance;
			}
		}

		// East
		{
			int a = this->width + this->chair_distance;
			int b = this->chair_length + this->chair_distance;

			int chair_number = a / b;
			int reminder = a % b;

			types::Ordered_pair<int> chair_centre;
			chair_centre.x = this->centre.x + this->length / 2 + this->chair_width / 2;
			chair_centre.y = this->centre.y - this->width / 2 + this->chair_length / 2 + reminder / 2;

			for (int i = 0; i < chair_number; i++) {
				this->chair_list.push_back(new chair::Chair(chair_centre, this->chair_length, this->chair_width, chair::Orientation::LEFT));
				chair_centre.y += this->chair_length + this->chair_distance;
			}
		}

		// North
		{
			int a = this->length + this->chair_distance;
			int b = this->chair_length + this->chair_distance;

			int chair_number = a / b;
			int reminder = a % b;

			types::Ordered_pair<int> chair_centre;
			chair_centre.x = this->centre.x - this->length / 2 + this->chair_length / 2 + reminder / 2;
			chair_centre.y = this->centre.y - this->width / 2 - this->chair_width / 2;

			for (int i = 0; i < chair_number; i++) {
				this->chair_list.push_back(new chair::Chair(chair_centre, this->chair_length, this->chair_width, chair::Orientation::DOWN));
				chair_centre.x += this->chair_length + this->chair_distance;
			}
		}

		// West
		{
			int a = this->width + this->chair_distance;
			int b = this->chair_length + this->chair_distance;

			int chair_number = a / b;
			int reminder = a % b;

			types::Ordered_pair<int> chair_centre;
			chair_centre.x = this->centre.x - this->length / 2 - this->chair_width / 2;
			chair_centre.y = this->centre.y - this->width / 2 + this->chair_length / 2 + reminder / 2;

			for (int i = 0; i < chair_number; i++) {
				this->chair_list.push_back(new chair::Chair(chair_centre, this->chair_length, this->chair_width, chair::Orientation::RIGHT));
				chair_centre.y += this->chair_length + this->chair_distance;
			}
		}
	}

	void Table::randomly_generate_chairs() {
		this->chair_length = random_number(chair::MIN_LENGTH, chair::MAX_LENGTH);
		this->chair_width = random_number(chair::MIN_WIDTH, chair::MAX_WIDTH);
		this->chair_distance = random_number(chair::MIN_DISTANCE, chair::MAX_DISTANCE);

		generate_chairs();
	}

	void Table::draw_chairs(QPainter *painter) const {
		for (chair::Chair *chair : this->chair_list) {
			chair->draw(painter);
		}
	}

	void Table::draw(QPainter *painter) const {
		painter->drawRect(*this->rect);
		painter->fillRect(*this->rect, COLOR);

		draw_chairs(painter);
	}

	void Table::highlight(QPainter *painter) const {
		painter->fillRect(*this->rect, COLOR);
	}

	/*!
	 * \brief It returns true if the mouse click is inside the table
	 * \param click_position
	 * \return
	 */
	bool Table::clicked(types::Ordered_pair<int> click_position) const {
		//	D ----- C
		//	|		|
		//	A ----- B

		types::Ordered_pair<int> a, c;

		a.x = this->centre.x - this->length / 2;
		a.y = this->centre.y + this->width / 2;

		c.x = this->centre.x + this->length / 2;
		c.y = this->centre.y - this->width / 2;

		if ((a.x <= click_position.x && click_position.x <= c.x) &&
			(c.y <= click_position.y && click_position.y <= a.y)) return true;
		else return false;
	}

	types::Ordered_pair<int> Table::get_centre() const {
		return this->centre;
	}

	int Table::get_length() const {
		return this->length;
	}

	int Table::get_width() const {
		return this->width;
	}

	int Table::get_chair_length() const {
		return this->chair_length;
	}

	int Table::get_chair_width() const {
		return this->chair_width;
	}

	int Table::get_chair_distance() const {
		return chair_distance;
	}
} // namespace table
