// [me_I2C_Console] test

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#include <me_I2C_Console.h>

#include <me_Console.h>
#include <me_Menu.h>

void RunTest()
{
  me_Menu::TMenu Menu;

  Menu.AddBuiltinCommands();
  me_I2C_Console::AddCommands(&Menu);
  Menu.RunListCommand();
  Menu.Run();
}

void setup()
{
  Console.Init();

  Console.Print("I2C console");

  RunTest();

  Console.Print("Done");
}

void loop()
{
}

/*
  2026-04-11
  2026-04-13
*/
