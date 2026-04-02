#include "aimbot.h"
#include <algorithm>
#include <cstdint>
#include "../../render/imgui/imgui.h"
#include "../../other/Config.h"
#include "../../other/settings.hpp"
#include "../../sdk and offsets/sdk.hpp"
#include "../../driver/driver.hpp"


bool memory_event(Vector3 newpos)
{
    write<Vector3>(cache::player_controller + 0x530, newpos);
    return true;
}

void aimbot(uintptr_t target_mesh)
{
    if (!target_mesh) return;

    float smooth = std::clamp(settings::aimbot::smoothness, 4.0f, 25.0f);
    Vector3 head3D = get_entity_bone(target_mesh, 110);
    Vector2 head2D = project_world_to_screen(head3D);

    if (head2D.x == 0.f && head2D.y == 0.f) return;

    float centerX = settings::width * 0.5f;
    float centerY = settings::height * 0.5f;
    float deltaX = head2D.x - centerX;
    float deltaY = head2D.y - centerY;

    Vector3 new_rotation = {
        -deltaY / smooth / 5.0f,
         deltaX / smooth / 5.0f,
         0.0f
    };

    memory_event(new_rotation);
}