// [me_I2C] console interface

/*
  Author: Martin Eden
  Last mod.: 2026-04-12
*/

#pragma once

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>
#include <me_Menu.h>

namespace me_I2C_Console
{
  void Scan();
  void Read();
  void Write();

  void AddCommands(me_Menu::TMenu *);
}

/*
  2026-04-11
  2026-04-12
*/
