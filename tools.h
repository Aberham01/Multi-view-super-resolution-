#include <iostream>
#include <glm/glm.hpp>
#include <vector>
class Tool {

public:
	void saveMat(std::string file,glm::mat4 mat,bool app);
	glm::mat4 getMat(std::string file);
	std::vector<glm::mat4> getMatrix(std::string file);
	void init(std::string file);
		
	

	

};
