import { useEffect, useState } from "react";
import reactLogo from "./assets/react.svg";
import viteLogo from "/vite.svg";

const SERVICE_UUID = 0xffe0;

function App() {
  const [device, setDevice] = useState<BluetoothDevice | null>(null);
  const [characteristic, setCharacteristic] =
    useState<BluetoothRemoteGATTCharacteristic | null>(null);

  useEffect(() => {
    if (device) {
      device.addEventListener("gattserverdisconnected", () => {
        setDevice(null);
        setCharacteristic(null);
        console.log("disconnected");
      });
    }
  }, [device]);

  useEffect(() => {
    if (characteristic) {
      characteristic.addEventListener("characteristicvaluechanged", (event) => {
        const value = (event.target as BluetoothRemoteGATTCharacteristic).value;
        const decoder = new TextDecoder();
        console.log(decoder.decode(value));
      });
    }
  }, [characteristic]);

  async function connect() {
    try {
      const device = await navigator.bluetooth.requestDevice({
        filters: [
          {
            services: [SERVICE_UUID],
          },
        ],
      });
      console.log(device.name);
      setDevice(device);

      const server = await device.gatt?.connect();

      const service = await server?.getPrimaryService(SERVICE_UUID);
      const characteristics = await service?.getCharacteristics();
      if (!characteristics) {
        return;
      }

      const characteristic = characteristics[0];
      setCharacteristic(characteristic);
    } catch (error) {
      console.error(error);
    }
  }

  async function writeValue(id: number) {
    if (!characteristic) {
      return;
    }

    const encoder = new TextEncoder();
    await characteristic.writeValue(encoder.encode(`Drink${id}`));
  }

  return (
    <div className="flex flex-col w-screen h-screen justify-start items-center bg-[#825cb4] font-[Times] text-black">
      <h1 className="py-10 font-bold text-4xl text-white">SMARTENDER</h1>

      <button
        onClick={() => connect()}
        className="mb-4 rounded-sm w-[100px] h-[40px] bg-white"
      >
        Connect
      </button>

      {[1, 2, 3, 4, 5, 6, 7, 8, 9, 10].map((drinkCode, index) => (
        <button
          key={index + 1}
          onClick={() => writeValue(drinkCode)}
          className={`my-2 rounded-sm w-[100px] h-[40px] ${
            characteristic === null ? "bg-gray-400" : "bg-white"
          }`}
        >{`Drink ${index + 1}`}</button>
      ))}
    </div>
  );
}

export default App;
