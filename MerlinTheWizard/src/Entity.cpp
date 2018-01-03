#include "Entity.h"

Entity::Entity()
{
	mShader = Shader();
	mModel = Model();
	mTranformation = { glm::mat4(), glm::mat4(), glm::mat4() };
	mModelMatrix = glm::mat4();
}

Entity::Entity(const char * fileName, Shader shader, Shader particleShader)
{
	mShader = shader;
	mParticleShader = particleShader;
	mTranformation = { glm::mat4(), glm::mat4(), glm::mat4() };
	mModelMatrix = glm::mat4();
	mModel = Model(fileName);
}

Entity::~Entity()
{
}

void Entity::Render()
{
	mShader.Use();
	mModelMatrix = mTranformation.TranslationMatrix * mTranformation.RotationMatrix * mTranformation.ScalingMatrix;
	glUniformMatrix4fv(glGetUniformLocation(mShader.GetID(), "ModelMatrix"), 1, GL_FALSE, &mModelMatrix[0][0]);
	mModel.Draw(mShader);
}

void Entity::RenderParticles(double deltatime, glm::vec3 cameraPos, glm::vec3 cameraUp, glm::vec3 cameraRight)
{
	for (unsigned int i = 0; i < this->particleSystemList.size(); i++) {
		this->particleSystemList[i].deltaTime = deltatime;
		this->particleSystemList[i].CreateParticles();
		this->particleSystemList[i].MainLoop(cameraPos);
		this->particleSystemList[i].Render(cameraRight, cameraUp);
	}

}

glm::mat4 Entity::GetModelMatrix()
{
	return mModelMatrix;
}

void Entity::Translate(glm::vec3 translateVec)
{
	mTranformation.TranslationMatrix = glm::translate(glm::mat4(), translateVec);
	this->position = translateVec;
	//mModelMatrix = mglm::translate(mModelMatrix, translateVec);
}

void Entity::Rotate(glm::vec3 rotateVec, float angle)
{
	mTranformation.RotationMatrix = glm::rotate(glm::mat4(), angle, rotateVec);
	this->rotation = rotateVec * angle; //?
										//mModelMatrix = glm::rotate(mModelMatrix, angle, rotateVec);
}

void Entity::Scale(glm::vec3 scaleVec)
{
	mTranformation.ScalingMatrix = glm::scale(glm::mat4(), scaleVec);
	this->scale = scaleVec;
	//mModelMatrix = glm::scale(mModelMatrix, scaleVec);
}

void Entity::AddParticleSystem(ParticleSystem sys) {

	this->particleSystemList.push_back(sys);
}