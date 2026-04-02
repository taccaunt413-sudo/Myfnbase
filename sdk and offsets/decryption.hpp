#pragma once

inline uint64_t rol64(uint64_t x, int r) {
    return (x << r) | (x >> (64 - r));
}
inline uint64_t DecryptWorld(uint64_t world)
{
    return ~rol64(world ^ 0xCF76574CULL, 48);
}
