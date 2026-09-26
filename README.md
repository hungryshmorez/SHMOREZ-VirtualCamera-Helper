# SHMOREZ Virtual Camera Helper

A Windows 11 native application that bridges a browser-based studio's program output into a Windows virtual camera accessible from Discord, Zoom, OBS, Teams, Chrome, and other applications.

**Status**: Phase 1 - Build Microsoft sample unmodified

## Architecture

```
Browser Studio (Program Output)
    ↓
WebSocket Connection (ws://127.0.0.1:38476)
    ↓
SHMOREZ Virtual Camera Helper (Native Win32/WinRT)
    ↓
Media Foundation Virtual Camera
    ↓
Windows Camera Subsystem
    ↓
Applications (Discord, Zoom, OBS, Teams, etc.)
```

## Key Design Principles

1. **Preserve Microsoft's sample architecture** - Do not reinvent the wheel; use proven Media Foundation implementation
2. **Modular phases** - Build, test, and validate after each phase before proceeding
3. **Local-only security** - No network exposure; localhost WebSocket with authentication token
4. **Reliable fallback** - Standby frame when browser disconnected
5. **System tray integration** - Simple status monitoring and control
6. **Production-ready** - Proper logging, error handling, installer support

## System Requirements

- **OS**: Windows 11 (10.0.22000.0 or later)
- **SDK**: Windows SDK 10.0.22000.0 or later
- **IDE**: Visual Studio 2022 Community/Professional
- **Extensions**: 
  - Microsoft Visual Studio Installer Projects (for MSI creation)
- **Runtime**: Latest VC Runtime redistributable

## Project Structure

```
SHMOREZ-VirtualCamera-Helper/
├── docs/
│   ├── PHASE_1.md              # Build Microsoft sample unmodified
│   ├── PHASE_2.md              # Rename and verify in Windows
│   ├── PHASE_3.md              # Replace frame generator with test sender
│   ├── PHASE_4.md              # Connect real browser studio
│   └── ARCHITECTURE.md         # Detailed design documentation
├── src/
│   ├── VirtualCameraMediaSource/    # Media Foundation COM object
│   ├── VirtualCameraHelper/         # Win32 system tray app
│   ├── VirtualCameraWebSocketServer/ # Local WebSocket server (new)
│   ├── VirtualCameraInstaller/      # Setup/uninstall console app
│   └── VirtualCameraTest/           # Test harness
├── installer/
│   ├── VirtualCamera_MSI/           # WiX MSI project
│   └── scripts/
│       ├── Install.ps1
│       ├── Uninstall.ps1
│       └── Debug-FrameServer.ps1
├── thirdparty/
│   └── websocket/ (WebSocket++ or similar)
└── VirtualCameraSample.sln         # Master solution

```

## Build Output

- `VirtualCameraMediaSource.dll` - COM-registered Media Foundation source
- `VirtualCameraHelper.exe` - System tray application
- `VirtualCameraInstaller.exe` - MSI-executed installer
- `VirtualCamera.msi` - Installer package
- `VirtualCameraTest.exe` - Validation test suite

## Implementation Phases

### Phase 1: Build Microsoft Sample Unmodified ✓ (Current)
- [ ] Clone/reference Microsoft Windows-Camera VirtualCamera sample
- [ ] Verify build with Visual Studio 2022
- [ ] Build all projects (Release config)
- [ ] Test media source loads without errors
- [ ] Document any build issues and resolutions

**Deliverable**: Successful build with no modifications to sample code

### Phase 2: Rename Virtual Camera to "SHMOREZ Virtual Camera"
- [ ] Modify camera friendly name in VirtualCameraManager
- [ ] Update installer branding
- [ ] Update system tray app strings
- [ ] Rebuild MSI
- [ ] Install on test system
- [ ] Verify camera appears as "SHMOREZ Virtual Camera" in:
  - Windows Settings > Cameras
  - OBS Studio camera list
  - Zoom/Teams device settings
  - Chrome camera picker

**Deliverable**: Virtual camera discoverable as "SHMOREZ Virtual Camera" on system

### Phase 3: Replace Synthetic Frame Generator with Test WebSocket Client
- [ ] Create simple test WebSocket client (Node.js or Python)
- [ ] Implement WebSocket server skeleton in VirtualCameraMediaSource
- [ ] Modify SimpleMediaSource to accept external JPEG frames
- [ ] Create "Waiting for browser..." standby frame
- [ ] Test frame injection from test client
- [ ] Verify frames appear in OBS/camera test applications

**Deliverable**: Virtual camera receives external frames from test client

### Phase 4: Connect Real Browser Studio
- [ ] Integrate browser studio WebSocket client
- [ ] Implement frame format negotiation (JPEG → raw BGRA/NV12)
- [ ] Add CORS/origin validation
- [ ] Implement authentication token system
- [ ] Test with live program output
- [ ] Optimize frame rate (30 FPS, 60 FPS capability)

**Deliverable**: Functional end-to-end system bridging browser to Discord/Zoom/OBS

### Phase 5: Polish & Deployment
- [ ] Add diagnostic logging
- [ ] Create `/status` health endpoint
- [ ] Implement uninstall routine
- [ ] Create system tray UI (connected/disconnected states)
- [ ] Add command-line interface (Install/Uninstall/Start/Stop)
- [ ] Package MSI installer
- [ ] Write user documentation

## Getting Started

### Step 1: Clone Microsoft Sample

This project is based on the official Microsoft Windows-Camera VirtualCamera sample. Start by understanding its structure:

```bash
git clone https://github.com/microsoft/Windows-Camera
cd Windows-Camera/Samples/VirtualCamera
```

See [PHASE_1.md](docs/PHASE_1.md) for detailed build instructions.

### Step 2: Set Up This Repository

```bash
git clone https://github.com/hungryshmorez/SHMOREZ-VirtualCamera-Helper
cd SHMOREZ-VirtualCamera-Helper
```

### Step 3: Follow Phase 1 Implementation

See [PHASE_1.md](docs/PHASE_1.md) for building the Microsoft sample.

## Key Technologies

- **Media Foundation API** - Virtual camera registration and frame streaming
- **COM/ATL** - Component Object Model for media source
- **Win32 API** - System tray integration
- **WebSocket (WebSocket++)** - Lightweight frame input from browser
- **JPEG/WebP** - Initial proof-of-concept frame format
- **BGRA/NV12** - Optimized pixel formats for performance
- **WiX Toolset** - MSI installer creation
- **Windows Camera Framework** - Hardware abstraction

## Configuration

### WebSocket Server Settings

```
Host: 127.0.0.1 (localhost only, not exposed to network)
Port: 38476
Protocol: WebSocket (ws://, not wss://)
Authentication: Token-based (randomly generated, stored locally)
```

### Supported Resolutions & Frame Rates

**Phase 3+:**
- 1280×720 @ 30 FPS (primary)
- 1920×1080 @ 30 FPS (primary)
- 60 FPS support (infrastructure prepared for Phase 5)

### Standby Frame

When browser is disconnected, the virtual camera displays:

```
╔════════════════════════════════╗
║  SHMOREZ VIRTUAL CAMERA        ║
║                                ║
║  Waiting for browser studio…   ║
║                                ║
║  localhost:38476               ║
╚════════════════════════════════╝
```

## Logging

Logs written to: `%APPDATA%\SHMOREZ\VirtualCameraHelper\logs\`

- `mediasource.log` - Media Foundation initialization and frame events
- `websocket.log` - Connection, frame reception, drops
- `systray.log` - Application state transitions
- `installer.log` - Installation/uninstallation events

## Security Considerations

1. **No Network Exposure** - WebSocket bound to 127.0.0.1 only
2. **Origin Validation** - Only approved browser-studio origins accepted
3. **Authentication Token** - Randomly generated, stored in Windows Credential Manager
4. **CORS Headers** - Strictly limited to localhost

## Testing & Validation

### Automated Tests

```bash
# Build test suite
cd src/VirtualCameraTest
msbuild VirtualCameraTest.vcxproj /p:Configuration=Release

# Run all tests
VirtualCameraTest.exe

# Run specific test
VirtualCameraTest.exe --gtest_filter=VirtualCameraSimpleMediaSourceTest.*

# List available tests
VirtualCameraTest.exe --gtest_list_tests
```

### Manual Verification

1. **OBS Studio**
   - Add source → Video Capture Device
   - Select "SHMOREZ Virtual Camera"
   - Verify resolution options and frame preview

2. **Zoom/Teams**
   - Settings → Video
   - Select "SHMOREZ Virtual Camera"
   - Start test call, verify video feed

3. **Chrome**
   - Open camera test: `chrome://devices/`
   - Check "SHMOREZ Virtual Camera" enumeration
   - Test getUserMedia() API

## Troubleshooting

### Media Source Won't Load

Check Media Foundation registration:
```powershell
# List registered media sources
reg query "HKLM\SOFTWARE\Classes\CLSID" /s | findstr VirtualCamera
```

### Camera Doesn't Appear in Windows

Verify virtual camera registration:
```powershell
# Check Frame Server monitor service
Get-Service FrameServerMonitor | Select-Object Status

# View Frame Server logs
eventvwr.msc
# Navigate to: Windows Logs > System, filter by FrameServer
```

### WebSocket Connection Refused

Verify helper app is running:
```powershell
Get-Process VirtualCameraHelper
netstat -ano | findstr 38476
```

## FAQ

**Q: Can I use this with OBS Studio?**
A: Yes. OBS will see "SHMOREZ Virtual Camera" as a normal webcam source.

**Q: Does this require admin rights?**
A: Installation requires elevation. The running helper app can operate as standard user after installation.

**Q: What happens when the browser disconnects?**
A: The virtual camera remains active and displays a "Waiting for browser studio…" standby frame.

**Q: Can I run multiple instances?**
A: No, only one virtual camera instance per name is supported. The design uses a single named camera.

**Q: Is the WebSocket connection encrypted?**
A: Not in Phase 1-3 (ws://, not wss://). Local-only design and token authentication provide security. HTTPS/WSS can be added if needed.

**Q: How do I uninstall?**
A: Use Add/Remove Programs or run: `VirtualCamera.msi /uninstall`

## Contributing

This is a personal project. Modifications should follow the phased approach:
1. Build and test after each phase
2. Document changes in phase-specific files
3. Preserve Microsoft sample architecture
4. Maintain backward compatibility with installer/uninstaller

## License

MIT - See LICENSE file

## References

- [Microsoft Windows-Camera Repository](https://github.com/microsoft/Windows-Camera)
- [MFCreateVirtualCamera API Docs](https://learn.microsoft.com/en-us/windows/win32/api/mfvirtualcamera/nf-mfvirtualcamera-mfcreatevirtualcamera)
- [Media Foundation Custom Media Source](https://docs.microsoft.com/en-us/windows-hardware/drivers/stream/frame-server-custom-media-source)
- [Virtual Camera Windows 11 Announcement](https://blogs.windows.com/windowsdeveloper/)

---

**Last Updated**: Phase 1 Initialization
**Next Step**: See [PHASE_1.md](docs/PHASE_1.md) - Build Microsoft sample
