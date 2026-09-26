# Phase 3 - Replace Synthetic Generator with a Simple Local Sender

## Objective

Remove the synthetic sample frame source and feed frames from a local sender instead.

## Required milestones

- Build a local WebSocket listener on `ws://127.0.0.1:38476`
- Accept browser or test-client frame input
- Support initial JPEG/WebP payloads for proof-of-concept
- Keep the camera valid even when no sender is connected
- Show a standby frame when the browser is disconnected

## Standby frame text

`fuck OBS Virtual Camera`
`Waiting for browser studio...`

## Frame processing

1. Receive JPEG/WebP bytes from a localhost sender
2. Decode to a raw pixel representation
3. Convert to the Media Foundation frame format used by the sample
4. Push frames into the existing virtual-camera media source sample pipeline

## Validation

- A simple test sender can inject frames successfully
- The virtual camera streams frames to a test app such as OBS, Teams, or Chrome
- The standby frame remains visible during disconnect

## Important rule

Do not attempt to build high-performance shared-memory or BGRA/NV12 transport in this phase. Keep the first working version simple and stable.
