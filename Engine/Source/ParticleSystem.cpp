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
    isActive = true;
    
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::SetEmitter(Emitter* emitter)
{
    emitters.push_back(emitter);
}

void ParticleSystem::Render()
{

}

bool ParticleSystem::Update(float dt) 
{
    for (int i = 0; i < emitters.size(); i++) {
        emitters[i]->Update(dt);
    }

    Render();

    return true;
}

void ParticleSystem::OnEditor()
{
    if (ImGui::CollapsingHeader("Particle System"))
    {
        ImGui::PushItemWidth(90);

        std::string playButtonName = isActive ? "Pause" : "Play";
        if (ImGui::Button(playButtonName.c_str()))
        {
            if (isActive)
                Stop();
            else
                Play();
        }

        ImGui::SameLine();
        ImGui::Text("Played for: %.2f", timer.ReadTime() * 0.001f);

        ImGui::Checkbox("Looping", &looping);
        ImGui::SliderFloat("Duration", &maxDuration, 0.0f, 10.0f);

        ImGui::Spacing();
        std::string guiName = "";
        std::string suffixLabel = "";
        for (int i = 0; i < emitters.size(); ++i)
        {
            suffixLabel = "##";
            suffixLabel += i;
            ImGui::Separator();
            ImGui::Spacing();

            emitters[i]->OnEditor(i);
        }

        ImGui::Separator();
    }
}

void ParticleSystem::Play()
{
    timer.Start();
    isActive = true;
    for (int i = 0; i < emitters.size(); ++i)
    {
        // TODO - emitters[i]->RestartEmitter();
    }
}

void ParticleSystem::Stop()
{
    timer.Stop();
    isActive = false;
}
