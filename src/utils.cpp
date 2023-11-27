#include "utils.h"
#include <cstdlib>

/*!
 * \brief It returns a random number between a and b
 * \param a
 * \param b
 * \return
 */
int random_number(int a, int b) {
	int offset = a;
	int range = b - a + 1;

	return offset + rand() % range;
}
