# adplug-opl3duo

This Arduino program, along with the [adplug-serial] and [adplay-unix-serial]
forks, allow adplay to use an [OPL3 Duo!] board by sending register writes to
the Arduino over the serial port.

Now with dosbox support via a [dosbox-opl3duo] fork!

[adplug-serial]: https://github.com/cknave/adplug-serial
[adplay-unix-serial]: https://github.com/cknave/adplay-unix-serial
[OPL3 Duo!]: https://cheerful.nl/OPL3Duo/index.html
[dosbox-opl3duo]: https://github.com/cknave/dosbox-opl3duo

## Arduino setup

1. Connect the OPL3 Duo! board to the Arduino as the instructions indicate
2. In the Arduino IDE, install the OPL2 library (Sketch > Include Library >
   Manage Libraries... > Arduino OPL2)
3. Open [opl3serial.ino] in the Arduino IDE
4. Upload to your device

[opl3serial.ino]: opl3serial/opl3serial.ino

## Adplay

### Setup

In this example, I'm going to install `adplay` to `$HOME/.local/`:

```shell
export PREFIX=$HOME/.local
```

1. If you don't have [libbinio] installed, build and install it first:

```shell
git clone https://github.com/adplug/libbinio.git 
cd libbinio
autoreconf --install
./configure --prefix=$PREFIX
make && make install
```

2. Build the adplug-serial fork:

```shell
git clone https://github.com/cknave/adplug-serial.git
cd adplug-serial
autoreconf --install
./configure --prefix=$PREFIX PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig
make && make install
```

3. Build the adplay-serial fork:

```shell
git clone https://github.com/cknave/adplay-unix-serial.git
cd adplay-serial
autoreconf --install
./configure --prefix=$PREFIX PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig
make && make install
```

[libbinio]: https://github.com/adplug/libbinio


### Usage

Assuming adplay is installed to `$PREFIX/bin` and your Arduino serial port is
`/dev/ttyACM0`:

```shell
$PREFIX/bin/adplay -O serial -d /dev/ttyACM0 <file>
```

## Dosbox

1. Build dosbox:

```shell
git clone https://github.com/cknave/dosbox-opl3duo
cd dosbox-opl3duo
./autogen.sh
./configure --prefix=$PREFIX PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig
make && make install
```

2. Update your dosbox.conf file (`~/.dosbox/dosbox-SVN.conf` by default)
`sblaster` section with `oplemu` and `oplserialport`:

```
[sblaster]
oplemu=serial
oplserialport=/dev/ttyACM0
```

3. Run dosbox! It should initialize the OPL3 Duo! on startup.

```shell
$PREFIX/bin/dosbox
```
