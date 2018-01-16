#include "Light.h"

Light::Light() {

	this->position = glm::vec4(0, 15, -10, 1);
	this->colour = glm::vec4(1, 1, 1, 1);
}
void Light::Render(Shader shader) {


	shader.Use();
	glUniform4fv(glGetUniformLocation(shader.GetID(), "LightPosition"), 1, &position[0]);
	glUniform4fv(glGetUniformLocation(shader.GetID(), "LightColor"), 1, &colour[0]);
}

void Light::Translate(glm::vec4 position){

	this->position = position;
}

void Light::ChangeColour(glm::vec4 colour) {

	this->colour = colour;
}

void Light::Input(int key) {

	if (key == GLFW_KEY_1) {
		this->position.z -= 0.1;
	}
	if (key == GLFW_KEY_2) {
		this->position.z += 0.1;
	}
	if (key == GLFW_KEY_3) {
		this->position.x -= 0.1;
	}
	if (key == GLFW_KEY_4) {
		this->position.x += 0.1;
	}
}