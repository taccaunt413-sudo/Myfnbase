#include "esp.h"
#include "../../render/imgui/imgui.h"
#include "../../other/Config.h"
#include "../../other/settings.hpp"
#include "../../sdk and offsets/sdk.hpp"

void draw_filled_rect(int x, int y, int w, int h, const ImColor color)
{
    ImGui::GetForegroundDrawList()->AddRectFilled(
        ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void draw_cornered_box(int x, int y, int w, int h)
{
    auto* dl = ImGui::GetForegroundDrawList();
    ImColor color = TO_IMCOLOR(settings::visuals::CornerBoxColor);
    float   thickness = settings::visuals::CornerBoxThickness;

    dl->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), color, thickness);
    dl->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), color, thickness);
    dl->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), color, thickness);
    dl->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), color, thickness);
    dl->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), color, thickness);
    dl->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), color, thickness);
    dl->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), color, thickness);
    dl->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), color, thickness);
}

void Skeleton(uintptr_t mesh, float /*distance*/)
{
    const int boneIndices[] = { 110,3,66,9,38,10,39,11,40,78,71,79,72,75,82,67 };
    Vector2 bonePositions[16];
    for (int i = 0; i < 16; ++i)
        bonePositions[i] = project_world_to_screen(get_entity_bone(mesh, boneIndices[i]));

    std::pair<int, int> bonePairs[] = {
        {1,2},{3,4},{4,3},{5,3},{6,4},{5,7},{6,8},
        {10,1},{9,1},{12,10},{11,9},{13,12},{14,11},{2,15},{15,0}
    };

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    for (auto& bp : bonePairs)
    {
        ImVec2 s(bonePositions[bp.first].x, bonePositions[bp.first].y);
        ImVec2 e(bonePositions[bp.second].x, bonePositions[bp.second].y);
        if (s.x && s.y && e.x && e.y)
            dl->AddLine(s, e,
                TO_IMCOLOR(settings::visuals::SkeletonColor),
                settings::visuals::SkeletonThickness);
    }
}

void Box(int X, int Y, int W, int H)
{
    auto* dl = ImGui::GetForegroundDrawList();
    ImColor color = TO_IMCOLOR(settings::visuals::BoxColor);
    float thickness = settings::visuals::BoxThickness;

    dl->AddLine(ImVec2(X, Y), ImVec2(X + W, Y), color, thickness);
    dl->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + H), color, thickness);
    dl->AddLine(ImVec2(X, Y + H), ImVec2(X + W, Y + H), color, thickness);
    dl->AddLine(ImVec2(X, Y), ImVec2(X, Y + H), color, thickness);
}

void draw_line(Vector2 target)
{
    ImGui::GetForegroundDrawList()->AddLine(
        ImVec2(settings::screen_center_x, settings::height),
        ImVec2(target.x, target.y),
        TO_IMCOLOR(settings::visuals::LineColor),
        settings::visuals::LineThickness);
}

void draw_distance(Vector2 location, float distance)
{
    char dist[64];
    sprintf_s(dist, "%.fm", distance);
    ImVec2 ts = ImGui::CalcTextSize(dist);
    ImGui::GetForegroundDrawList()->AddText(
        ImVec2(location.x - ts.x / 2, location.y - ts.y / 2),
        TO_IMCOLOR(settings::visuals::DistanceColor), dist);
}