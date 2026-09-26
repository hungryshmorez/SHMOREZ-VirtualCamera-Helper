#pragma once

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

namespace fuck_obs_vcam
{
    struct BrowserFramePacket
    {
        std::string format; // jpeg, webp, rgb32, nv12
        uint32_t width = 0;
        uint32_t height = 0;
        std::vector<uint8_t> payload;
        bool hasAlpha = false;
    };

    class LocalFrameBridge
    {
    public:
        LocalFrameBridge() = default;
        virtual ~LocalFrameBridge() = default;

        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual bool IsRunning() const = 0;
    };
}
