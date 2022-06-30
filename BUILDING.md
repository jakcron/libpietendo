# Building
## Linux (incl. Windows Subsystem for Linux) & MacOS - Makefile
### Requirements
* `make`
* `doxygen`
* `graphviz`
* Terminal access
* Typical GNU compatible development tools (e.g. `clang`, `g++`, `c++`, `ar` etc) with __C++11__ support

### Using Makefile
* `make` (default) - Compile library & self-test program
* `make static_lib` - Compile library
* `make test_program` - Compile self-test program
* `make clean` - Remove all object files, compiled programs
* `make docs` - Generate documentation
* `make clean_docs` - Remove all documentation

## Native Win32 - Visual Studio
### Requirements
* [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) 2015 or 2017 or 2019
* [Doxygen](http://www.doxygen.nl/download.html#srcbin)
* [Graphviz](https://graphviz.gitlab.io/_pages/Download/Download_windows.html) (make sure to download the GUI)
	* Add the location of the Graphviz `bin` directory to `$(PATH)` or create a separate enviroment variable `$(DOT_PATH)` for it.

### Compiling Library & Self-Test Program
* Open `build/visualstudio/libpietendo.sln` in Visual Studio
* Select Target (e.g `Debug`|`Release` & `x86`|`x64`)
* Navigate to `Build`->`Build Solution`

### Including libpietendo in another VS Solution for static linking
* Clone `libpietendo` as a submodule into your project
* Navigate to the `Solution Explorer` window
* Right-click on the Solution Item and select `Add`->`Existing Project...`
* In the filesystem popup window open `<libpietendo location>/build/visualstudio/libpietendo/libpietendo.vcxproj`
* Update each dependant project's `References` to include libpietendo
* Update each dependant project's `Property Pages` so that for `All Configurations` and `All Platforms` the `Addition Include Directories` has the relative path to `<libpietendo location>/include`
* Update the `Project Build Order` so libpietendo is built before any of its dependants
* Update the `Project Dependencies` so that each dependant has the box checked for libpietendo

### Generating Doxygen Documentation
* Open `Doxywizard`
* Under `Step 1` specify the directory of libpietendo as the working directory
* This should open the Doxyfile and pre-fill all the configuration
* Under `Step 2` navigate to `Run` and press `Run doxygen`
