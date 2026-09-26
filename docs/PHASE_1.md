# Phase 1 - Build the Microsoft Sample Unmodified

This phase is mandatory and must be completed before any SHMOREZ-specific changes.

## Objective

Get the official Microsoft Windows-Camera VirtualCamera sample building cleanly in a Windows 11 toolchain without modifying the vendor sample logic.

## Required environment

- Windows 11
- Visual Studio 2022
- Windows 11 SDK 10.0.22000.0+
- Visual Studio Installer Projects extension
- Latest VC++ Redistributable

## Steps

1. Clone the official sample:
   - https://github.com/microsoft/Windows-Camera
   - Open `Samples/VirtualCamera/VirtualCameraSample.sln`
2. Restore NuGet packages if required by the solution.
3. Build the solution in Release x64.
4. Resolve any dependency or toolchain issues before changing any files.
5. Confirm the sample builds without source edits.
6. Record exact build commands and any toolchain modifications.

## Expected result

A successful Release build of the Microsoft sample with no custom code changes.

## Validation checklist

- `VirtualCameraMediaSource` builds
- `VirtualCamera_Installer` builds
- `VirtualCamera_MSI` builds
- `VirtualCameraSystray` builds (if applicable)
- `VirtualCameraTest` builds (if applicable)

## Important rule

Do not rename the camera or change the frame source during Phase 1. This phase is strictly about proving the sample builds cleanly.

## Notes

If the sample fails to build due to environment issues, fix the environment and document the issue, but do not patch the sample unless absolutely required for the toolchain.
