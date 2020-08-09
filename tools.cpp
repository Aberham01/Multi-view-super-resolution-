#include "tools.h"
#include <glm\gtc\type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <vector>

void Tool::saveMat(std::string file,glm::mat4 mat,bool app)
{

	std::ofstream outfile;
	if (app) {
		outfile.open(file,std::ios_base::app);
	}
	else {
		outfile.open(file);
	}
	
	outfile.clear();
	outfile << "Mat" << " ";
	const float* pSource = (const float*)glm::value_ptr(mat);
	for (int i = 0; i < 16; ++i) {

		outfile << pSource[i] << " ";
	}
	outfile << "\n";
	outfile.close();

}
glm::mat4 Tool::getMat(std::string f) {
	std::ifstream file(f);
	float x;
	float matrix[16];
	
	for (std::string line; std::getline(file, line); )   //read stream line by line
	{
		std::istringstream in(line);      //make a stream for the line itself
		
		std::string type;
		in >> type;                  //and read the first whitespace-separated token

		if (type == "Mat")       //and check its value
		{
			
			for (int i = 0; i < 16; i++)
			{
				in >> x;
				//std::cout << x << "\n";
				matrix[i] = x;
			}

			    //now read the whitespace-separated floats
		}
		

	}
	//std::cout << "\n" << x << "\n";
	return glm::make_mat4(matrix);
}

std::vector<glm::mat4> Tool::getMatrix(std::string f) {
	std::ifstream file(f);
	float x;
	float matrix[16];
	std::vector<glm::mat4> mats;
	for (std::string line; std::getline(file, line); )   //read stream line by line
	{
		std::istringstream in(line);      //make a stream for the line itself

		std::string type;
		in >> type;                  //and read the first whitespace-separated token

		if (type == "Mat")       //and check its value
		{

			for (int i = 0; i < 16; i++)
			{
				in >> x;
				//std::cout << x << "\n";
				matrix[i] = x;
			}

			//now read the whitespace-separated floats
		}

		mats.push_back(glm::make_mat4(matrix));
	}
	//std::cout << "\n" << x << "\n";
	return mats;
}

void Tool::init(std::string f) {
	std::ofstream outfile;
	outfile.open(f);


	outfile.clear();
	outfile << "";
	

	outfile.close();
}