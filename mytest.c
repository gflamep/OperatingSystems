#include "types.h"
#include "user.h"
#include "stat.h"

int main()
{
	ps(0);
	setnice(2,10);
	ps(0);
	setnice(2, 200);
	ps(2);

	exit();
}