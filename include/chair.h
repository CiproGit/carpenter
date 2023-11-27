#ifndef CHAIR_H
#define CHAIR_H

#include "types.h"
#include <QPainter>

namespace chair {
	const int MIN_LENGTH = 20;
	const int MAX_LENGTH = 50;
	const int MIN_WIDTH = 20;
	const int MAX_WIDTH = 50;
	const int MIN_DISTANCE = 10;
	const int MAX_DISTANCE = 30;

	enum class Orientation : unsigned int {
		RIGHT = 0,
		UP = 90,
		LEFT = 180,
		DOWN = 270
	};

	class Chair {
	private:
		const QColor COLOR = QColor(200, 128, 100, 128);
		const int BACK_WIDTH = 5;

		types::Ordered_pair<int> centre;

		int length;
		int width;

		Orientation orientation;

		QRect *seat;
		QRect *back;

	public:
		Chair(types::Ordered_pair<int> centre, int length, int width, Orientation orientation);
		virtual ~Chair();
		void draw(QPainter *painter) const;
	};
} // namespace chair

#endif // CHAIR_H
