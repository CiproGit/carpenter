#include "chair.h"

namespace chair {
	Chair::Chair(types::Ordered_pair<int> centre, int length, int width, Orientation orientation) {
		this->centre = centre;

		this->length = length;
		this->width = width;

		this->orientation = orientation;

		if (this->orientation == Orientation::RIGHT) {
			this->seat = new QRect(this->centre.x - this->width / 2, this->centre.y - this->length / 2, this->width, this->length); // Draw chair seat
			this->back = new QRect(this->centre.x - this->width / 2, this->centre.y - this->length / 2, BACK_WIDTH, this->length); // Draw chair back
		}
		else if (this->orientation == Orientation::UP) {
			this->seat = new QRect(this->centre.x - this->length / 2, this->centre.y - this->width / 2, this->length, this->width); // Draw chair seat
			this->back = new QRect(this->centre.x - this->length / 2, this->centre.y + this->width / 2 - BACK_WIDTH, this->length, BACK_WIDTH); // Draw chair back
		}
		else if (this->orientation == Orientation::LEFT) {
			this->seat = new QRect(this->centre.x - this->width / 2, this->centre.y - this->length / 2, this->width, this->length); // Draw chair seat
			this->back = new QRect(this->centre.x + this->width / 2 - BACK_WIDTH, this->centre.y - this->length / 2, BACK_WIDTH, this->length); // Draw chair back
		}
		else if (this->orientation == Orientation::DOWN) {
			this->seat = new QRect(this->centre.x - this->length / 2, this->centre.y - this->width / 2, this->length, this->width); // Draw chair seat
			this->back = new QRect(this->centre.x - this->length / 2, this->centre.y - this->width / 2, this->length, BACK_WIDTH); // Draw chair back
		}
	}

	Chair::~Chair() {
		delete this->seat;
		delete this->back;
	}

	void Chair::draw(QPainter *painter) const {
		painter->drawRect(*this->seat);
		painter->fillRect(*this->seat, COLOR);

		painter->drawRect(*this->back);
		painter->fillRect(*this->back, COLOR);
	}
}
