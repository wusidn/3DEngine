#include <iostream>
#include "Appaction.h"

using namespace std;
using namespace engine;


int main(int argc, char ** argv)
{
	Appaction::instance().run(argc, argv);
	return 0;
}