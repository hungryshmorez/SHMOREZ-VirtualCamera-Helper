# Architecture Overview

## High-level flow

Browser Studio
→ local canvas/program output
→ local WebSocket client
→ fuck OBS Virtual Camera Helper
→ Media Foundation virtual camera
→ Windows camera subsystem
→ Discord / Zoom / Teams / Chrome / OBS consumers

## Core responsibilities

### 1. Media Foundation layer

This is based on the Microsoft sample architecture. It remains the authoritative virtual-camera implementation layer.

Responsibilities:
- register virtual camera
- create media source
- stream frames to the Windows camera subsystem
- maintain valid device state while disconnected

### 2. Helper app

This is the native Win32 tray application.

Responsibilities:
- start/stop camera
- monitor connection state
- host the local WebSocket server
- keep the device alive in standby mode
- expose health/status information
- expose installer actions

### 3. Browser bridge

The browser app sends final composited program output to the helper via a localhost WebSocket.

Initial implementation:
- JPEG/WebP payloads
- 30 FPS at 1280x720 and 1920x1080
- local-only, token-authenticated connection

Later optimization:
- BGRA/NV12 frames
- shared memory transport
- lower-latency motion path

## Security model

- Binding to `127.0.0.1` only
- `ws://127.0.0.1:38476`
- no external network exposure
- strict origin validation
- local auth token generation
- approved local development origins only

## Supported resolutions

- 1280x720 at 30 FPS
- 1920x1080 at 30 FPS
- design allows 60 FPS later without changing the architecture

## Standby behavior

When no browser sends frames:

- camera remains registered
- camera remains visible to apps
- output shows a standby frame indicating waiting state

## Logging

Important logging topics:

- Media Foundation initialization
- camera registration
- frame reception
- pixel conversion
- consumer connections
- startup failures
- registration failures
