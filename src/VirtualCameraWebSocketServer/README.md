# VirtualCameraWebSocketServer

This folder is reserved for the localhost frame bridge server.

## Intended role

- bind to `127.0.0.1:38476`
- accept WebSocket connections from approved local origins only
- validate token or origin
- receive JPEG/WebP frames first
- route inbound frames to the media source

## Notes

This is intentionally not a public network service.
