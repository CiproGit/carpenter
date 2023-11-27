#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include "chair.h"
#include <QPainter>

namespace table {
	const int MIN_LENGTH = 100;
	const int MAX_LENGTH = 300;
	const int MIN_WIDTH = 100;
	const int MAX_WIDTH = 300;

	class Table {
	private:
		const QColor COLOR = QColor(129, 128, 255, 128);

		types::Ordered_pair<int> centre;

		int length;
		int width;

		int chair_length;
		int chair_width;
		int chair_distance;

		std::vector<chair::Chair *> chair_list;

		QRect *rect;

		void generate_chairs();
		void randomly_generate_chairs();
		void draw_chairs(QPainter *painter) const;

	public:
		Table(types::Ordered_pair<int> centre, int length, int width);
		Table(types::Ordered_pair<int> centre, int length, int width, int chair_length, int chair_width, int chair_distance);
		virtual ~Table();
		void draw(QPainter *painter) const;
		void highlight(QPainter *painter) const;
		bool clicked(types::Ordered_pair<int> click_position) const;
		types::Ordered_pair<int> get_centre() const;
		int get_length() const;
		int get_width() const;
		int get_chair_length() const;
		int get_chair_width() const;
		int get_chair_distance() const;
	};
} // namespace table

#endif // TABLE_H
