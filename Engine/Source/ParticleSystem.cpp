#include "ParticleSystem.h"
#include "Emitter.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include <cassert>
#include "Globals.h"
#include <GL/glew.h>

ParticleSystem::ParticleSystem(GameObject* own, TransformComponent* trans, uint numParticles)
{
    type = ComponentType::PARTICLE_SYSTEM;
    transform = trans;
    //localToGlobalMatrix = Mat4x4(1, 1, 1, 1);
    textureId = 0;
    Resize(numParticles);
    
}

ParticleSystem::~ParticleSystem()
{
	particlesBuffer.clear();
}

void ParticleSystem::EmitParticles()
{
    for (size_t i = 0; i < emitters.size(); i++)
    {
        //emitters[i]->Emit();
    }
}

void ParticleSystem::BuildVertex()
{
    Quat cameraRotation;

    vertexBuffer.resize(particlesBuffer.size() * 4, Vertex());
    //float3 test = cameraRotation.ToEulerXYZ();

    for (int i = 0; i < particlesBuffer.size(); i++)
    {
        Particle& particle = particlesBuffer[i];
        //Quat rotation = glm::angleAxis;

        uint vertexIndex = i * 4;
        Vertex& v0 = vertexBuffer[vertexIndex + 0];   // Bottom-left
        Vertex& v1 = vertexBuffer[vertexIndex + 1];   // Bottom-right
        Vertex& v2 = vertexBuffer[vertexIndex + 2];   // Top-right
        Vertex& v3 = vertexBuffer[vertexIndex + 3];   // Top-left

         // Bottom-left
        v0.pos = particle.position;
        v0.tex = Vec2(0, 1);
        v0.diff = particle.color;

        // Bottom-right
        v1.pos = particle.position;
        v1.tex = Vec2(1, 1);
        v1.diff = particle.color;

        // Top-right
        v2.pos = particle.position;
        v2.tex = Vec2(1, 0);
        v2.diff = particle.color;

        // Top-left
        v3.pos = particle.position;
        v3.tex = Vec2(0, 0);
        v3.diff = particle.color;
    }
}

void ParticleSystem::SetEmitter(Emitter* emitter)
{
    emitters.push_back(emitter);
}

void ParticleSystem::Render()
{
    /*if (vertexBuffer.size() == 0)
        return;

    glDisable(GL_DEPTH_TEST);           // Disables Depth Testing
    glEnable(GL_BLEND);                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Type Of Blending To Perform
    glEnable(GL_TEXTURE_2D);            // Enable textures

    glPushMatrix();
    glMultMatrixf(transform->GetGlobalTransform().Transposed().ptr());

    glBindTexture(GL_TEXTURE_2D, textureId);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(vertexBuffer[0].pos));
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(vertexBuffer[0].tex));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(vertexBuffer[0].diff));

    glDrawArrays(GL_QUADS, 0, vertexBuffer.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 0);*/
}

bool ParticleSystem::Update(float dt) 
{
    for (int i = 0; i < emitters.size(); i++) {
        emitters[i]->Update(dt);
    }

    //g_Camera.ApplyViewTransform();

    //DrawAxis(20.0f, g_Camera.GetPivot());
    EmitParticles();
    BuildVertex();
    Render();

    return true;
}

void ParticleSystem::OnEditor()
{
    if (ImGui::CollapsingHeader("Particle System"))
    {
        ImGui::PushItemWidth(90);

        ImGui::Separator();
    }
}

void ParticleSystem::Resize(uint particlesNumber)
{
    particlesBuffer.resize(particlesNumber, Particle());
    vertexBuffer.resize(particlesNumber * 4, Vertex());
}
