# Minesweeper

A Minesweeper game featuring Material Design, written with SFML.

## Build & Run

We have tested the game on Ubuntu 22.04 & macOS 13.0.  
Win version is not tested, but should act well after some deployments.

### Linux (Debian)

1. Setup C++ env
   ```bash
   sudo apt-get install gcc build-essential make cmake
   ```
2. Install game deps
   ```bash
   sudo apt-get libsfml-dev libspdlog-dev
   ```
3. Build the game
   ```bash
   sh ./build.sh
   ```
4. Run Minesweeper
   ```
   cd build
   ./Minesweeper
   ```

### macOS

1. Download SFML and refer to the [official tutorial](https://www.sfml-dev.org/tutorials/2.5/start-osx.php) for installation.

2. Install the `x86_64` version of Homebrew and then install the `x86_64` version of spdlog.  
   If you are using a device with an M1 chip, please refer to the guide available [here](https://medium.com/mkdir-awesome/how-to-install-x86-64-homebrew-packages-on-apple-m1-macbook-54ba295230f#).

3. Compile and run using the following command.
   ```bash
   ./build-macos.sh
   cd build
   ./Minesweeper
   ```

## License

MIT