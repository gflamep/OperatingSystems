#include "types.h"
#include "user.h"
#include "stat.h"

int main()
{

	ps(0);

	int success = setnice(1, 3);
	printf(1, "New Nice: %d\n", getnice(1));
	ps(1);

	printf(1, "no pid ps\n");
	ps(100);

	printf(1, "out of bound value : %d\n", setnice(1, 100));
	exit();
}