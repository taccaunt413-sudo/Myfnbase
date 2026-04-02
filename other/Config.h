#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "settings.hpp"

namespace config_system
{
    inline std::string config_folder = "configs\\";
    inline std::vector<std::string> config_list;
    inline int selected_config = -1;
    inline char new_config_name[64] = "";

    inline void refresh()
    {
        config_list.clear();

        if (!std::filesystem::exists(config_folder))
            std::filesystem::create_directory(config_folder);

        for (auto& entry : std::filesystem::directory_iterator(config_folder))
        {
            if (entry.path().extension() == ".cfg")
                config_list.push_back(entry.path().stem().string());
        }
    }

    inline void save(const std::string& name)
    {
        std::ofstream file(config_folder + name + ".cfg");
        if (!file.is_open()) return;

        file << settings::aimbot::enable << "\n";
        file << settings::aimbot::show_fov << "\n";
        file << settings::aimbot::fov << "\n";
        file << settings::aimbot::smoothness << "\n";
        file << settings::aimbot::current_aimkey << "\n";

        file << settings::visuals::enable << "\n";
        file << settings::visuals::CorneredBox << "\n";
        file << settings::visuals::fill_box << "\n";
        file << settings::visuals::Box << "\n";
        file << settings::visuals::Skeleton << "\n";
        file << settings::visuals::line << "\n";
        file << settings::visuals::distance << "\n";

        file << settings::visuals::BoxColor[0] << " " << settings::visuals::BoxColor[1] << " " << settings::visuals::BoxColor[2] << " " << settings::visuals::BoxColor[3] << "\n";
        file << settings::visuals::CornerBoxColor[0] << " " << settings::visuals::CornerBoxColor[1] << " " << settings::visuals::CornerBoxColor[2] << " " << settings::visuals::CornerBoxColor[3] << "\n";
        file << settings::visuals::SkeletonColor[0] << " " << settings::visuals::SkeletonColor[1] << " " << settings::visuals::SkeletonColor[2] << " " << settings::visuals::SkeletonColor[3] << "\n";
        file << settings::visuals::LineColor[0] << " " << settings::visuals::LineColor[1] << " " << settings::visuals::LineColor[2] << " " << settings::visuals::LineColor[3] << "\n";
        file << settings::visuals::DistanceColor[0] << " " << settings::visuals::DistanceColor[1] << " " << settings::visuals::DistanceColor[2] << " " << settings::visuals::DistanceColor[3] << "\n";

        file << settings::visuals::BoxThickness << "\n";
        file << settings::visuals::CornerBoxThickness << "\n";
        file << settings::visuals::SkeletonThickness << "\n";
        file << settings::visuals::LineThickness << "\n";

        file << settings::Features::Watermark << "\n";
        file << settings::Features::Rapidfire << "\n";
        file << settings::Features::Rapidfirevalue << "\n";
        file << settings::Features::Spinbot << "\n";
        file << settings::Features::Fovchanger << "\n";
        file << settings::Features::Fovvalue << "\n";
        file << settings::Features::Playersize << "\n";
        file << settings::Features::PlayersizeScale << "\n";
        file << settings::Features::Carfly << "\n";

        file.close();
    }

    inline void load(const std::string& name)
    {
        std::ifstream file(config_folder + name + ".cfg");
        if (!file.is_open()) return;

        file >> settings::aimbot::enable;
        file >> settings::aimbot::show_fov;
        file >> settings::aimbot::fov;
        file >> settings::aimbot::smoothness;
        file >> settings::aimbot::current_aimkey;

        file >> settings::visuals::enable;
        file >> settings::visuals::CorneredBox;
        file >> settings::visuals::fill_box;
        file >> settings::visuals::Box;
        file >> settings::visuals::Skeleton;
        file >> settings::visuals::line;
        file >> settings::visuals::distance;

        file >> settings::visuals::BoxColor[0] >> settings::visuals::BoxColor[1] >> settings::visuals::BoxColor[2] >> settings::visuals::BoxColor[3];
        file >> settings::visuals::CornerBoxColor[0] >> settings::visuals::CornerBoxColor[1] >> settings::visuals::CornerBoxColor[2] >> settings::visuals::CornerBoxColor[3];
        file >> settings::visuals::SkeletonColor[0] >> settings::visuals::SkeletonColor[1] >> settings::visuals::SkeletonColor[2] >> settings::visuals::SkeletonColor[3];
        file >> settings::visuals::LineColor[0] >> settings::visuals::LineColor[1] >> settings::visuals::LineColor[2] >> settings::visuals::LineColor[3];
        file >> settings::visuals::DistanceColor[0] >> settings::visuals::DistanceColor[1] >> settings::visuals::DistanceColor[2] >> settings::visuals::DistanceColor[3];

        file >> settings::visuals::BoxThickness;
        file >> settings::visuals::CornerBoxThickness;
        file >> settings::visuals::SkeletonThickness;
        file >> settings::visuals::LineThickness;

        file >> settings::Features::Watermark;
        file >> settings::Features::Rapidfire;
        file >> settings::Features::Rapidfirevalue;
        file >> settings::Features::Spinbot;
        file >> settings::Features::Fovchanger;
        file >> settings::Features::Fovvalue;
        file >> settings::Features::Playersize;
        file >> settings::Features::PlayersizeScale;
        file >> settings::Features::Carfly;

        file.close();
    }

    inline void remove(const std::string& name)
    {
        std::filesystem::remove(config_folder + name + ".cfg");
        refresh();
    }
}