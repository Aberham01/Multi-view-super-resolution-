#include <iostream>
#include <fstream>
#include <sstream>
#include "chapter1.h"
#include "chapter2.h"
#include<glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>

int main()
{



	glm::mat4 a(0.0);
	int chap;
	std::cout << "Choose the chapter(1,2)" << "\n";
	//int iu;
	std::cin >> chap;
	
	if (chap==1) {
		chapter1 chap = chapter1();
		chap.run();
	}
	else {
	chapter2 chap = chapter2();
	chap.run();
	}
	
	return 0;
}
