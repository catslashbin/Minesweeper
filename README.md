
# Minesweeper

A Minesweeper game featuring Material Design, written with SFML.

## Screenshots

<table>
  <tr>
    <td>
      <img src="https://github.com/catslashbin/Minesweeper/assets/132267900/78f6f11d-3041-4a17-9e6b-7a1bacaee632" alt="Image 1">
    </td>
    <td>
      <img src="https://github.com/catslashbin/Minesweeper/assets/132267900/39494f0e-f06b-41b8-a652-788301afe58d" alt="Image 2">
    </td>
    <td>
      <img src="https://github.com/catslashbin/Minesweeper/assets/132267900/07ffc322-a0a3-484e-aa4f-99fa4d65f16d" alt="Image 3">
    </td>
  </tr>
  <tr>
    <td>
      <img src="https://github.com/catslashbin/Minesweeper/assets/132267900/8f90936a-3d23-4abb-988d-b2f97b288041" alt="Image 4">
    </td>
    <td>
      <img src="https://github.com/catslashbin/Minesweeper/assets/132267900/a7124cf2-740d-45c8-8088-27ba7f418d6b" alt="Image 5">
    </td>
    <td>
      <img src="https://github.com/catslashbin/Minesweeper/assets/132267900/92f68ade-0795-4255-822b-b3d24a5e5b8e" alt="Image 6">
    </td>
  </tr>
</table>



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
