# TS-FMOD-Plugin V2:

## 1.51
- **Updated to 1.51**
- Project Structure + Code Clean-up/Rework
 - Reworked Memory scanning
  - Easier to maintain and update
- Use of cvar values:
 - Volume level control is now done in-game | removed `sound_levels.txt`
 - Low air sound wont play if you have "Air brakes simulation" disabled
 - Reverse sound wont play if you have "Back-up beeper" disabled
 - Sound will play in background if you have "Play sound when the game is in background" enabled
 - Automatic game sound settings control
 - Use of navigation voices and menu music will now be determined by the value they were in your settings
- Full config format rework
- Feature to allow multiple bank files for multiple trucks at one
- "Directional" audio
- Volume fade-out on game loosing focus
- Improved cabin sound
- Fixed only left window affecting volume | Now both windows affects volume evenly
- Automatic `master.bank` handling
- Removed requirement for `master.strings.bank` file
- Fixed bug where windows named `Euro Truck Simulator 2` or `American Truck Simulator` would make the plugin play audio
- Added new interior events:
 - `event:/interior/system_warning1` *[Lane Assist Beep]*
 - `event:/interior/system_warning2`
 - `event:/interior/system_warning3`
- Added new truck effects events:
 - `event:/effects/air_brake`
 - `event:/effects/hook_attach`
 - `event:/effects/hook_detach`
 - `event:/effects/air_gear`
 - `event:/effects/gear_wrong`
 - `event:/effects/gear_grind`
 - `event:/effects/reverse`
- Added new paramaters:
 - `parameter:/trans_rpm`
 - `parameter:/cabin_type` *Value will always be `1`*
 - `parameter:/daytime`
 - `parameter:/air_pressure`
 - `parameter:/park_brake`

## 1.50
- Updated to 1.50

## 1.49 - 1.1
- New `sound_levels.txt` file format
- Fixed problem where it would try to load blank lines in `selected.bank.txt`

## 1.49 - 1.0
- Added audio mute on alt tab
- Fixed constant "echo" effect on the original ts-fmod plugin
- Better interior and exterior sound
- Added support for menu music [`event:/music/main_menu`]
- Added support for interior noise sounds [`event:/interior/noise`]
- Added support for start_bad sound [`event:/engine/start_bad`]
- Added support for wiper sounds [`event:/interior/wiper_up` (and down)] 


# TS-FMOD-Plugin V1:

## 1.49
- Updated to support 1.49
- Reverted window volume changes

## 1.48.5
- Updated to support 1.48.5
- Fixed air pressure warning sometimes getting stuck playing
- Added support for more interior events:
  - interior/window_move
  - interior/window_click

## 1.48.1
- Fixed issue with echo not working.

## 1.48
- Updated to support 1.48
- Support for navigation voice mods
- Added version check so plugin won't load on an unsupported game version

## 1.47.1
- Fixed issue with plugin not loading with Non-English characters in file path

## 1.47
- Updated to support 1.47
- Added some extra (error) logging

## 1.46
- Updated to support 1.46

## 1.45.1
- Updated for ATS 1.45.2.1 and ETS2 1.45.1.4

## 1.45
- Updated to support 1.45

## 1.44
- Updated to support 1.44

## 1.43.1
- Updated for ATS 1.43.3.3 and ETS2 1.43.3.40
  - Updated to FMOD v2.02.05

## 1.43
- Updated for 1.43
- Fixed plugin not loading when a non-used audio device could not be loaded.

## 1.41
- Updated for 1.41
- Support for loading multiple sound banks
  - Possible to add multiple sound banks on separate lines in selected.bank.txt.
  - Loads sound banks from top to bottom, will not load any sounds loaded by a previous sound bank.
- Fixed closed windows affecting sounds on exterior camera
- Fixed handbrake sounds being reversed

## 1.40.1
 - Updated for 1.40
 - Fixed engine brake
    - Stopped engine brake from playing when in neutral or when throttle/clutch is pressed
    - Added support for different levels of engine brake

## 1.39.6
 - Added rudimentary audio level customization
 - Fixed interior sounds being played when on an exterior view

## 1.39.5
 - Added support for more interior events:
    - interior/stick_hazard_warning
    - interior/stick_high_beam
    - interior/stick_light_horn
    - interior/stick_lights
    - interior/stick_wipers
 - Fixed so indicator event plays when switching between left/right indicator.
 - Switched to using busses to control volume/pause state instead of events individually

## 1.39.4
- Support for 1.39 turbo event, older sound mods that used the turbo parameter should still work but without turbo sounds

## 1.39.3
- Fixed playing incorrect event when indicator stick going back to default position

## 1.39.2
- Added support for the echo sounds when under bridges, in tunnels, etc...

## 1.39.1
- Initial Code commit
