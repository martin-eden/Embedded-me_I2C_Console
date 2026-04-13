// [me_I2C] console interface implementation

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#include <me_I2C_Console.h>

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_Console.h>
#include <me_I2C.h>
#include <me_Menu.h>
#include <me_StreamsCollection.h>

using namespace me_I2C_Console;

/*
  Scan for available I2C devices

  Output: Addresses+
*/
void me_I2C_Console::Scan()
{
  me_I2C::TI2C_Master I2C;
  TUint_1 DeviceId;
  me_StreamsCollection::TZeroesInputStream DummyStream;

  const TUint_1
    StartId = 8,
    StopId = 119;

  I2C.Init();

  for (DeviceId = StartId; DeviceId <= StopId; ++DeviceId)
  {
    TBool IsPresent;

    IsPresent = I2C.Send(DeviceId, 0, &DummyStream);

    if (IsPresent)
      Console.Print(DeviceId);
  }
  Console.EndLine();

  I2C.Done();
}

/*
  [Internal] Handler to call Scan
*/
static void Scan_Command(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  Scan();
}

/*
  [Internal] Add Scan command
*/
static TBool AddScanCommand(
  me_Menu::TMenu * Menu
)
{
  const TAddress Unused = 0;

  return
    Menu->AddItem(
      me_Menu::Freetown::ToItem("s", "Scan", Scan_Command, Unused)
    );
}

/*
  Read data from device

  Input: DeviceAddress NumBytes
  Output: Bytes+
*/
void me_I2C_Console::Read()
{
  /*
    Before reading we are writing read address (zero)
  */

  /*
    Power of streams

    We do not need memory for received data.

    Implementation requires stream (which is merely pointer to Write()
    function), not pointer to RAM memory. And all our stream processing
    is printing byte values in ASCII. We have another stream for that
    task.
  */

  me_I2C::TI2C_Master I2C;
  TUint_1 DeviceId;
  TUint_2 NumBytes;

  me_StreamsCollection::TZeroesInputStream Zeroes;
  me_StreamsCollection::TByteToDecimalStream BytesAsciiStream;

  if (!Console.Read(&DeviceId)) return;
  if (!Console.Read(&NumBytes)) return;

  I2C.Init();
  I2C.Send(DeviceId, 1, &Zeroes);
  I2C.Receive(DeviceId, NumBytes, &BytesAsciiStream);
  I2C.Done();

  Console.EndLine();
}

/*
  [Internal] Handler to call Read
*/
static void Read_Command(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  Read();
}

/*
  [Internal] Add Read command
*/
static TBool AddReadCommand(
  me_Menu::TMenu * Menu
)
{
  const TAddress Unused = 0;

  return
    Menu->AddItem(
      me_Menu::Freetown::ToItem("r", "Read", Read_Command, Unused)
    );
}

/*
  Write data to device

  Input: DeviceAddress NumBytes Bytes+
*/
void me_I2C_Console::Write()
{
  /*
    Same as in Read() we're setting write address to zero first.
    That read/write address stuff is common but not supported by
    [me_I2C].
  */

  me_I2C::TI2C_Master I2C;

  TUint_1 DeviceId;
  TUint_2 NumBytes;

  me_StreamsCollection::TZeroesInputStream Zeroes;
  me_StreamsCollection::TDecimalToByteStream AsciiBytesStream;

  if (!Console.Read(&DeviceId)) return;
  if (!Console.Read(&NumBytes)) return;

  I2C.Init();
  I2C.Send(DeviceId, 1, &Zeroes);
  I2C.Send(DeviceId, NumBytes, &AsciiBytesStream);
  I2C.Done();
}

/*
  [Internal] Handler to call Write
*/
static void Write_Command(
  TUint_2 Addr1 [[gnu::unused]],
  TUint_2 Addr2 [[gnu::unused]]
)
{
  Write();
}

/*
  [Internal] Add Write command
*/
static TBool AddWriteCommand(
  me_Menu::TMenu * Menu
)
{
  const TAddress Unused = 0;

  return
    Menu->AddItem(
      me_Menu::Freetown::ToItem("w", "Write", Write_Command, Unused)
    );
}

/*
  Add our commands to menu
*/
void me_I2C_Console::AddCommands(
  me_Menu::TMenu * Menu
)
{
  AddScanCommand(Menu);
  AddReadCommand(Menu);
  AddWriteCommand(Menu);
}

/*
  2026-04-11
  2026-04-12
  2026-04-13
*/
