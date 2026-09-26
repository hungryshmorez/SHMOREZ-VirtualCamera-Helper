# ExternalFrameSource.h

#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>
#include <vector>

#include <mfapi.h>
#include <mfobjects.h>
#include <mfidl.h>

namespace fuck_obs_vcam
{
    struct FrameBuffer
    {
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t stride = 0;
        GUID subtype = MFVideoFormat_RGB32;
        std::vector<uint8_t> bytes;
    };

    class IFrameSource
    {
    public:
        virtual ~IFrameSource() = default;

        virtual bool TryGetLatestFrame(FrameBuffer& outFrame) = 0;
        virtual bool IsConnected() const = 0;
        virtual bool IsValid() const = 0;
        virtual void SetStandbyText(const wchar_t* text) = 0;
    };

    class ExternalFrameSource final : public IFrameSource
    {
    public:
        ExternalFrameSource();
        ~ExternalFrameSource() override;

        bool TryGetLatestFrame(FrameBuffer& outFrame) override;
        bool IsConnected() const override;
        bool IsValid() const override;
        void SetStandbyText(const wchar_t* text) override;

        void SetConnected(bool connected);
        void SetFrame(uint32_t width, uint32_t height, GUID subtype, const uint8_t* data, size_t dataLength);
        void ClearFrame();

    private:
        mutable std::mutex m_mutex;
        FrameBuffer m_latestFrame;
        bool m_connected = false;
        bool m_valid = true;
        std::wstring m_standbyText = L"fuck OBS Virtual Camera\nWaiting for browser studio...";
    };
}
