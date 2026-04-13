// [me_I2C] console interface implementation

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#include <me_I2C_Console.h>

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_Menu.h>

using namespace me_I2C_Console;

/*
  [Internal] Handler to call Scan
*/
static void Scan_Command(
  TAddress Instance [[gnu::unused]]
)
{
  Freetown::Scan();
}

/*
  [Internal] Handler to call Read
*/
static void Read_Command(
  TAddress Instance [[gnu::unused]]
)
{
  Freetown::Read();
}

/*
  [Internal] Handler to call Write
*/
static void Write_Command(
  TAddress Instance [[gnu::unused]]
)
{
  Freetown::Write();
}

// [Internal] Convenience menu item record
struct TMenuItem
{
  TAsciiz Command;
  TCallback Handler;
  TAsciiz Description;
};

/*
  [Internal] Add menu item. Function for code readability
*/
static void AddMenuItem(
  TMenuItem Item,
  me_Menu::TMenu * Menu
)
{
  using me_Menu::Freetown::ToItem;

  const TAddress Unused = 0;

  Menu->AddItem(
    ToItem(Item.Command, Item.Description, Item.Handler, Unused)
  );
}

/*
  Add our commands to menu
*/
void me_I2C_Console::AddCommands(
  me_Menu::TMenu * Menu
)
{
  const TUint_1 NumMenuItems = 3;
  const TMenuItem MenuItems[NumMenuItems] =
    {
      { "s", Scan_Command, "Scan" },
      { "r", Read_Command, "Read <Addr> <NumBytes>" },
      { "w", Write_Command, "Write <Addr> <NumBytes> <Bytes+>" },
    };

  for (TUint_1 Index = 0; Index < NumMenuItems; ++Index)
    AddMenuItem(MenuItems[Index], Menu);
}

/*
  2026-04-11
  2026-04-12
  2026-04-13
*/
