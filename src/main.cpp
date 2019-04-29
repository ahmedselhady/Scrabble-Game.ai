#include "./Brain.hpp"
#include "./Definitions.hpp"

int main()
{
	GameBrain *brain = new GameBrain();
	brain->work_computer_vs_computer();

	system("pause");
	return 0;
}