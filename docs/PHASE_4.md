# Phase 4 - Connect the Real Browser Studio

## Objective

Connect the browser studio application to the helper app using a local-only socket connection.

## Communication contract

- Host: `127.0.0.1`
- Port: `38476`
- Scheme: `ws://`
- No network exposure beyond localhost

## Security requirements

- Bind to localhost only
- Validate allowed origins
- Validate authentication token
- Permit only local development origins and approved browser studio origins
- Do not expose the helper to arbitrary websites

## Status endpoint

`http://127.0.0.1:38476/status`

Return JSON with:

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

## Validation

- Browser app connects successfully
- Camera remains live while browser is active
- Standby frame appears when browser disconnects
- Metrics update in the status endpoint and tray UI

## Exit condition

The browser studio can stream program output to the virtual camera without requiring OBS.
