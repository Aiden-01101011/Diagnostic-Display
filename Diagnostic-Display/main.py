import time
from liquidctl import find_liquidctl_devices
import serial


arduino = serial.Serial(port='COM10', baudrate=115200, timeout=3)

first = True

# find all connected and supported devices
devices = find_liquidctl_devices()


def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data.decode("utf-8")


for dev in devices:
    # connect to the device (here a context manager is used, but the
    # connection can also be manually managed)
    with dev.connect():
        print(f'{dev.description} at {dev.bus}:{dev.address}:')

        # devices should be initialized after every boot (here we assume
        # this has not been done before)
        init_status = dev.initialize()
        if dev.description != "Corsair Commander Pro":
            continue
        device = dev
        # print all data returned by initialize()
        if init_status:
            for key, value, unit in init_status:
                if 'Temperature' in key:
                    print(f'{key}: {value} {unit}')

        # get regular status information from the device
        status = dev.get_status()

        # print all data returned by get_status()
        for key, value, unit in status:
            if 'Temperature' in key:
                print(f'{key}: {value} {unit}')
        # 1 = coolant temp
        # 2 = rad out temp
        print(dev._get_temp(0))
        # for a particular device, set the pump LEDs to red

    # the context manager took care of automatically calling disconnect();
    # when manually managing the connection, disconnect() must be called at
    # some point even if an exception is raised

    if first:
        first = False
        print()  # add a blank line between each device
device.connect()
while True:
    num = str(device._get_temp(0))
    print(write_read(num))
    print(num)
    # time.sleep(0.5)
