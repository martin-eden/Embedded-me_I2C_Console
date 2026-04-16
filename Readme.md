## What

(2026-04)

![Boot screen][Image_Boot]

Text interface for I2C protocol. ATmega328 library.

This is text communication for I2C devices connected to Arduino Uno.
Communication via UART at 115200 bps.

More important than details is idea.

Idea is clean ASCII text messages designed to be easy to parse and
compile by another program. You can still use it manually if you want.


## Install/remove and requirements

* Software

  * Upload binary

    * Linux
    * Bash
    * `avrdude`

  * Compile

    * `arduino-cli` (`avr-gcc`)

* Hardware

  * Arduino Uno (ATmega328)
  * I2C devices connected to I2C pins

* Install

  * Clone repo
  * If you want to upload [`binary`][binary]
    * Go to [`bin/`][bin]
    * Run [`Upload.sh`][Upload.sh]
  * If you want to compile code
    * Clone other required libraries ([`GetLibs`][GetLibs])
    * Compile with `arduino-cli` (I use my wrapper [`ino.pile`][ino])

* Remove

  * Delete directory with repo
  * If you compiled code
    * Delete additional libraries (`me_` directory name prefix)

## Code

* [Program][Program]
* [Interface][Interface]
* Implementation
  * [Core][Core]
  * [Menu items][MenuItems]

## Commands

Below are input and output for available commands.

### ? - List commands
```
?
( ?
  ? - List commands
  ^ - Exit
  s - Scan
  r - Read <DeviceId> <NumBytes>
  w - Write <DeviceId> <Bytes+>
)
```

| Text input | Description           | Notes                          |
| :---       | :---                  | :---                           |
| `?↵`       | List menu items       | Note that text output format   |

### ^ - Exit
```
^
( ^
)
Done
```

| Text input | Description           | Notes                          |
| :---       | :---                  | :---                           |
| `^↵`       | Exit current menu     | Program stops until board reset |


### s - Scan
```
s
( s
  087 104
)
```
| Text input | Description           | Notes                          |
| :---       | :---                  | :---                           |
| `s↵`       | Scan I2C bus          | Lists all devices found. List may be empty |


### r - Read `<`DeviceId`>` `<`NumBytes`>`
```
r
( r
104
10
  006 005 005 005 028 136 000 027 000 005
)
```

| Text input  | Description                       | Notes                          |
| :---        | :---                              | :---                           |
| `r↵104↵10↵` | Read `10` bytes from device `104` | Typically read position depends of R/W pointer |


### w - Write `<`DeviceId`>` `<`NumBytes`>` `<`Bytes+`>`

```
w
( w
104
2
5
3
)
```

| Text input  | Description                            | Notes                          |
| :---        | :---                                   | :---                           |
| `w↵104↵2↵5↵3↵` | Write two bytes: `5` `3` to device `104` | Sets sixth byte to 3 for RTC DS3231. |


## Notes

Use case is channel to I2C device from desktop/laptop/microcontroller.

Parsing/compiling binary data is easier in more suitable languages than C++.
(I love Lua for doing that.)


## See also

  * [CLI client][Lua_I2C_Console_Client]
  * [`me_I2C` module][me_I2C]
  * [`me_Console` module][me_Console]
  * [`me_Menu` module][me_Menu]
  * [My other embedded libraries][Embedded]
  * [My other projects][Repos]

[Image_Boot]: images/me_I2C_Console.Boot.png

[binary]: bin/Code.hex
[bin]: bin/
[Upload.sh]: bin/Upload.sh
[ino]: https://github.com/martin-eden/Bash-ArduinoCliWrappers

[Program]: examples/me_I2C_Console/me_I2C_Console.ino
[Interface]: src/me_I2C_Console.h
[Core]: src/Freetown.cpp
[MenuItems]: src/me_I2C_Console.cpp

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Lua_I2C_Console_Client]: https://github.com/martin-eden/Lua-I2C_Console
[me_I2C]: https://github.com/martin-eden/Embedded-me_I2C
[me_Console]: https://github.com/martin-eden/Embedded-me_Console
[me_Menu]: https://github.com/martin-eden/Embedded-me_Menu
[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
