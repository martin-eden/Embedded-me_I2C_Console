// Console commands implementation

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#include <me_I2C_Console.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_I2C.h>
#include <me_StreamsCollection.h>

using namespace me_I2C_Console;

/*
  Scan for available I2C devices

  Output: Addresses+
*/
void Freetown::Scan()
{
  /*
    We're trying to send zero bytes to given address

    Fact that Send() succeeded means we have device at that address.
  */

  me_I2C::TI2C_Master I2C;
  TUint_1 DeviceId;
  me_StreamsCollection::TEmptyInputStream EmptyStream;

  const TUint_1
    StartId = 8,
    StopId = 119;

  I2C.Init();

  for (DeviceId = StartId; DeviceId <= StopId; ++DeviceId)
    if (I2C.Send(DeviceId, 0, &EmptyStream))
      Console.Print(DeviceId);

  Console.EndLine();

  I2C.Done();
}

/*
  Read data from device

  Input: DeviceId NumBytes
  Output: Bytes+
*/
void Freetown::Read()
{
  /*
    Before reading we are writing read address (zero)
  */

  /*
    Power of streams

    We do not need memory for received data.

    Implementation requires stream (which is merely a pointer to Write()
    function), not pointer to RAM memory. And all our stream processing
    is printing byte values in ASCII. We have stream for that purpose.
  */

  me_I2C::TI2C_Master I2C;
  TUint_1 DeviceId;
  TUint_2 NumBytes;

  me_StreamsCollection::TByteToDecimalStream BytesAsciiStream;

  if (!Console.Read(&DeviceId)) return;
  if (!Console.Read(&NumBytes)) return;

  I2C.Init();
  I2C.Receive(DeviceId, NumBytes, &BytesAsciiStream);
  I2C.Done();

  Console.EndLine();
}

/*
  Write data to device

  Input: DeviceId NumBytes Bytes+
*/
void Freetown::Write()
{
  me_I2C::TI2C_Master I2C;
  TUint_1 DeviceId;
  TUint_2 NumBytes;
  me_StreamsCollection::TDecimalToByteStream AsciiBytesStream;

  if (!Console.Read(&DeviceId)) return;
  if (!Console.Read(&NumBytes)) return;

  I2C.Init();
  I2C.Send(DeviceId, NumBytes, &AsciiBytesStream);
  I2C.Done();
}

/*
  2026-04-13
*/
