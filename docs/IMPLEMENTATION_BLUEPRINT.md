# This document captures the exact implementation strategy for the browser-to-virtual-camera bridge.

# Goal

Build a lightweight Windows 11 virtual camera that exits OBS from the architecture and keeps the browser app as the studio.

# Required architecture

Browser Studio
  -> local canvas/program output
  -> `ws://127.0.0.1:38476`
  -> native helper
  -> Media Foundation virtual camera
  -> Windows camera subsystem
  -> Discord / Zoom / Teams / Chrome / other apps

# Critical rule

Do not rewrite the Microsoft sample architecture. Preserve the official Media Foundation virtual-camera registration and installer flow. Replace only the synthetic frame source with a browser-driven frame source.

# Exact integration points

The sample currently generates synthetic frames in:
- `Samples/VirtualCamera/VirtualCameraMediaSource/SimpleFrameGenerator.cpp`
- `Samples/VirtualCamera/VirtualCameraMediaSource/SimpleMediaSource.cpp`

The camera registration and friendly name live in:
- `Samples/VirtualCamera/VirtualCamera_Installer/main.cpp`

# Required change pattern

1. Keep the sample VMF stream lifecycle.
2. Add a frame-source abstraction behind SimpleFrameGenerator.
3. Feed latest received frame bytes into the generator output buffer.
4. If no browser frame is available, generate a standby frame that says:
   `fuck OBS Virtual Camera`
   `Waiting for browser studio...`
5. Keep the virtual camera valid and discoverable even when disconnected.

# Supported proof-of-concept transport

- WebSocket: `ws://127.0.0.1:38476`
- initial payload: JPEG / WebP
- local-only binding to `127.0.0.1`
- token-based auth and origin filtering
- no network exposure beyond localhost

# Status endpoint

`http://127.0.0.1:38476/status`

Return JSON such as:

```json
{
  "installed": true,
  "connected": true,
  "cameraRunning": true,
  "width": 1280,
  "height": 720,
  "fps": 30,
  "framesReceived": 1234,
  "framesDropped": 8,
  "version": "1.0.0"
}
```

# Naming to use

- App name: `fuck OBS Virtual Camera`
- Camera friendly name: `fuck OBS Virtual Camera`
- Tray strings: `fuck OBS Virtual Camera`

# Build flow in the real Windows environment

1. Open the official sample solution in Visual Studio 2022.
2. Build the sample in Release x64 without source changes.
3. Rename the camera in the registration flow.
4. Replace synthetic frame generation with a frame queue fed by browser bytes.
5. Add local WebSocket listener and fallback standby frame.
6. Add tray app and status epdoint.
7. Validate in Discord, Zoom, Teams, and Chrome.

# Important constraints

- No OBS in the architecture.
- No Electron.
- No browser-based video editor.
- No broad network exposure.
- Keep the Media Foundation sample architecture intact.

# Recommended next code patch

Add a `FrameQueue` to `SimpleFrameGenerator.cpp` and a minimal `IFrameSource` implementation. This is the narrowest edit path and preserves the sample’s media-source lifecycle.
