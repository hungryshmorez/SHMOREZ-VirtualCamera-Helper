#include "ExternalFrameSource.h"

#include <cstring>

namespace fuck_obs_vcam
{
    ExternalFrameSource::ExternalFrameSource() = default;

    ExternalFrameSource::~ExternalFrameSource() = default;

    bool ExternalFrameSource::TryGetLatestFrame(FrameBuffer& outFrame)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_latestFrame.bytes.empty())
        {
            return false;
        }

        outFrame = m_latestFrame;
        return true;
    }

    bool ExternalFrameSource::IsConnected() const
    {
        return m_connected;
    }

    bool ExternalFrameSource::IsValid() const
    {
        return m_valid;
    }

    void ExternalFrameSource::SetStandbyText(const wchar_t* text)
    {
        if (text == nullptr)
        {
            return;
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        m_standbyText.assign(text);
    }

    void ExternalFrameSource::SetConnected(bool connected)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_connected = connected;
    }

    void ExternalFrameSource::SetFrame(uint32_t width, uint32_t height, GUID subtype, const uint8_t* data, size_t dataLength)
    {
        if (data == nullptr || dataLength == 0)
        {
            return;
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        m_latestFrame.width = width;
        m_latestFrame.height = height;
        m_latestFrame.subtype = subtype;
        m_latestFrame.stride = width * 4;
        m_latestFrame.bytes.assign(data, data + dataLength);
        m_connected = true;
        m_valid = true;
    }

    void ExternalFrameSource::ClearFrame()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_latestFrame.bytes.clear();
        m_latestFrame.width = 0;
        m_latestFrame.height = 0;
        m_latestFrame.stride = 0;
    }
}
