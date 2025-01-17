#pragma once

#include <hex/ui/popup.hpp>

#include <hex/api/localization_manager.hpp>

#include <string>

namespace hex::plugin::builtin {

    class PopupBlockingTask : public Popup<PopupBlockingTask> {
    public:
        PopupBlockingTask(TaskHolder &&task) : hex::Popup<PopupBlockingTask>("hex.builtin.popup.blocking_task.title", false), m_task(std::move(task)) { }

        void drawContent() override {
            ImGui::TextUnformatted("hex.builtin.popup.blocking_task.desc"_lang);
            ImGui::Separator();

            if (this->m_task.getProgress() == 0)
                ImGuiExt::TextSpinner("");
            else
                ImGui::ProgressBar(this->m_task.getProgress() / 100.0F);

            ImGui::NewLine();
            if (ImGui::ButtonEx("hex.builtin.common.cancel"_lang, ImVec2(ImGui::GetContentRegionAvail().x, 0)) || ImGui::IsKeyDown(ImGuiKey_Escape))
                this->m_task.interrupt();

            if (!this->m_task.isRunning()) {
                ImGui::CloseCurrentPopup();
            }
        }

        [[nodiscard]] ImGuiWindowFlags getFlags() const override {
            return ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;
        }

    private:
        TaskHolder m_task;
    };

}