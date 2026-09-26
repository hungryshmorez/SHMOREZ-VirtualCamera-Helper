# Phase 2 - Rename the Virtual Camera to "fuck OBS Virtual Camera"

## Objective

Rename the virtual camera at the edge of the Microsoft sample so it presents to Windows as:

`fuck OBS Virtual Camera`

## Scope

- Friendly camera name in the registration layer
- Installer branding
- Tray labels and status strings
- Any user-visible naming in the helper app

## Implementation notes

Use the same Media Foundation registration architecture as the sample. Do not rewrite the virtual camera pipeline.

The naming change should be limited to:

- `friendlyName`
- installer metadata
- any UI strings used by the tray app
- log prefixes

## Validation

After rebuild/install:

- Open Windows Camera settings
- Confirm `fuck OBS Virtual Camera` shows in the camera list
- Confirm the app is discoverable by video clients like Discord, Zoom, Teams, or Chrome

## Exit condition

Windows sees the camera as `fuck OBS Virtual Camera` and it is usable as a normal webcam input.
