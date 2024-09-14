# TS-FMOD-Plugin Improved/V2 - ETS2 / ATS

A telemetry plugin for ATS/ETS2 that includes an FMOD instance so that you can use FMOD sound mods.

# Whats different in v2?
- Added support for muting the audio when the game is running in the background [this cannot be disabled]
- Added more features and sounds
- Improved config and useability
- Fixed the echo effect in the original version
- Better cabin/exterior sound
- Much more (continue reading below)

# How to use
1.) Open Steam<br>
2.) Right click ETS2/ATS and go to `Manage > Browse Local Files`<br>
3.) Open `Bin > win_x64`<br>
4.) Download the plugin (https://github.com/Baldywaldy09/ts-fmod-plugin-v2/releases/latest)<br>
5.) Inside the downloaded zip extract the folder `plugins` into the folder you opened earlier<br>
6.) Download any sound mods you would like to use<br>
7.) Extract the `.bank` and `.bank.guids` from the .zip/.scs file usually located in: `/sound/truck/` [these files can be placed anywhere]<br>
8.) Back inside the plugin zip extract the folder `Config App`<br>
9.) Open the `.exe` file inside and and select your game [top right]<br>
10.) Press "Add Truck" and add the truck you want to add this sound to<br>
11.) Select the new truck and press "Add New Bank" and locate the `.bank` file you extracted earlier<br>
12.) Open/Restart your game and the sound should be applied<br>

### Some extra info
- Any bank files on the truck: "global" will be applied to all trucks, this can be used for things like navigation sounds
- Use the in-game volume slider to adjust the volume of this plugin

# Supported FMOD events and parameters
Events: [Truck]
- engine/engine
- engine/exhaust
- engine/turbo
- engine/start_bad [added in v2]
- effects/air_brake [added in v2]
- effects/hook_attach [added in v2]
- effects/hook_detach [added in v2]
- effects/air_gear [added in v2]
- effects/gear_wrong [added in v2]
- effects/gear_grind [added in v2]
- effects/reverse [added in v2]
- interior/air_warning
- interior/blinker_on (and off)
- interior/stick_blinker (and off)
- interior/stick_park_brake (and off)
- interior/wiper_up (and down) [added in v2]
- interior/stick_retarder
- interior/stick_hazard_warning
- interior/stick_high_beam
- interior/stick_light_horn
- interior/stick_lights
- interior/stick_wipers
- interior/window_move
- interior/window_click
- interior/noise [added in v2]
- interior/system_warning1 *[Lane Assist Beep]* [added in v2]
- interior/system_warning2 [added in v2]
- interior/system_warning3 [added in v2]

Events: [Other]
- music/main_menu [added in v2]

Events: [GPS]
- and_then_exit_left
- and_then_exit_right
- and_then_go_straight
- and_then_keep_left
- and_then_keep_right
- and_then_turn_left
- and_then_turn_right
- compound_exit_left
- compound_exit_right
- compound_go_straight
- compound_keep_left
- compound_keep_right
- compound_turn_left
- compound_turn_right
- exit_left
- exit_now
- exit_right
- finish
- go_straight
- keep_left
- keep_right
- prepare_exit_left
- prepare_exit_right
- prepare_turn_left
- prepare_turn_right
- recomputing
- roundabout_1
- roundabout_2
- roundabout_3
- roundabout_4
- roundabout_5
- roundabout_6
- speed_signal
- speed_warning
- start
- turn_left
- turn_right
- u_turn


Parameters:
- brake
- load
- rpm
- wnd_left (and right)
- surr_type
- cabin_rot
- cabin_out
- trans_rpm [added in v2]
- cabin_type *Value will always be `1`* [added in v2]
- daytime [added in v2]
- air_pressure [added in v2]
- park_brake [added in v2]
