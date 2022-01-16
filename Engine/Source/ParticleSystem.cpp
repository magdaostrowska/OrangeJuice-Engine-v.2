#include "ParticleSystem.h"
#include "Globals.h"
#include "Emitter.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include <cassert>
#include <GL/glew.h>
#include "Dialogs.h"

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


bool ParticleSystem::Update(float dt) 
{
    if (isActive && (((float)timer.GetTime())/1000.0f < maxDuration || looping == true))
    {
        for (int i = 0; i < emitters.size(); i++) {
            emitters[i]->Update(dt);
        }
    }
    
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

        if (ImGui::Button("Save template"))
        {
            if (app->scene->SceneDirectory().empty())
            {
                std::string filePath = Dialogs::SaveFile("Orange Juice Scene (*.orangeJuice)\0*.orangeJuice\0");
                if (!filePath.empty()) app->scene->SaveScene(filePath.c_str());
            }
            else app->scene->SaveScene(app->scene->SceneDirectory().c_str());
        }

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

        if (ImGui::Button("Create Emitter")) {
            Emitter* emitter = new Emitter(owner);
            emitters.push_back(emitter);
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
        // TODO: emitters[i]->RestartEmitter();
    }
}

void ParticleSystem::Stop()
{
    timer.Stop();
    isActive = false;
}

bool ParticleSystem::OnLoad(JsonParsing& node)
{
    isActive = node.GetJsonBool("PS: Is Active");
    looping = node.GetJsonBool("PS: Max Duration");
    maxDuration = node.GetJsonNumber("PS: Max Duration");

    for (int i = 0; i < emitters.size(); i++)
    {
        emitters[i]->OnLoad(node);
    }

    return false;
}

bool ParticleSystem::OnSave(JsonParsing& node, JSON_Array* array)
{
    JsonParsing file = JsonParsing();
    file.SetNewJsonBool(file.ValueToObject(file.GetRootValue()), "PS: Is Active", isActive);
    file.SetNewJsonBool(file.ValueToObject(file.GetRootValue()),"PS: Looping", looping);
    file.SetNewJsonNumber(file.ValueToObject(file.GetRootValue()), "PS: Max Duration", maxDuration);
    node.SetValueToArray(array, file.GetRootValue());

    for (int i = 0; i < emitters.size(); i++)
    {
        emitters[i]->OnSave(node, array);
    }

    return true;
}
