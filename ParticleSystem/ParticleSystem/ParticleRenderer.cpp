#include "ParticleRenderer.h"
#include "Graphics.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#include <random>
#include <time.h>   

#define NUM_PARTICLES 1024 * 1024
#define WORK_GROUP_SIZE 128
#define MAX_PARTICLES 1000

ParticleRenderer::ParticleRenderer()
{
	srand((unsigned)time(NULL));

	glGenBuffers(1, &particleVAO);

	for (int i = 0; i < MAX_PARTICLES; i++)
	{

		Particle thisParticle;

		thisParticle.position.x = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.position.y = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.position.z = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.position.w = 1.0f;		

		thisParticle.colour.x = (float)rand() / (float)RAND_MAX;
		thisParticle.colour.y = (float)rand() / (float)RAND_MAX;
		thisParticle.colour.z = (float)rand() / (float)RAND_MAX;
		thisParticle.colour.w = 1.0f;

		m_Vparticles.push_back(thisParticle);
	}

	glBindBuffer(GL_ARRAY_BUFFER, particleVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * m_Vparticles.size(), m_Vparticles.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleVAO);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(Particle), nullptr, GL_STATIC_DRAW);
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);
}

ParticleRenderer::~ParticleRenderer()
{
}

//void ParticleRenderer::Update(ShaderProgram particleShader)
//{
//	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);
//
//	particleShader.UseShader();
//	glDispatchCompute(NUM_PARTICLES / WORK_GROUP_SIZE, 1, 1);
//	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
//}

void ParticleRenderer::Draw(ShaderProgram particleShader)
{
	particleShader.UseShader();

	//glBindBuffer(GL_VERTEX_ARRAY, particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, particleVAO);


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(4 * sizeof(float)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, colour));

	glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);

	//glBindBuffer(GL_VERTEX_ARRAY, 0);
}
