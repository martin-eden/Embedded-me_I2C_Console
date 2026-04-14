// [me_I2C] console interface

/*
  Author: Martin Eden
  Last mod.: 2026-04-14
*/

#pragma once

#include <me_Menu.h>

namespace me_I2C_Console
{
  void AddCommands(me_Menu::TMenu *);

  namespace Freetown
  {
    void Scan();
    void Read();
    void Write();
  }
}

/*
  2026-04-11
  2026-04-12
*/
