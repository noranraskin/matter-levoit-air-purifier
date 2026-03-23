```
$ idf.py set-target esp32
Adding "esp32"'s sdkconfig files to CMakeLists.txt...
Running cmake in directory /Users/[USERNAME]/Developer/matter-levoit-air-purifier/build
Executing "cmake -G Ninja -DPYTHON_DEPS_CHECKED=1 -DESP_PLATFORM=1 -DIDF_TARGET=esp32 -DCCACHE_ENABLE=1 /Users/[USERNAME]/Developer/matter-levoit-air-purifier"...
-- Found Git: /usr/bin/git (found version "2.39.2") 
-- ccache will be used for faster recompilation
-- The C compiler identification is GNU 13.2.0
-- The CXX compiler identification is GNU 13.2.0
-- The ASM compiler identification is GNU
-- Found assembler: /Users/[USERNAME]/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20230928/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Project is not inside a git repository, or git repository has no commits
-- Building ESP-IDF components for target esp32
Processing 2 dependencies:[1/2] idf (5.2.0)
[2/2] esp_matter (1.0.0)
-- Project sdkconfig file /Users/[USERNAME]/Developer/matter-levoit-air-purifier/sdkconfig

Loading defaults file /Users/[USERNAME]/Developer/matter-levoit-air-purifier/sdkconfig.defaults...
/Users/[USERNAME]/Developer/matter-levoit-air-purifier/sdkconfig.defaults:21: warning: symbol value 'y' invalid for ENABLE_WIFI_AP
/Users/[USERNAME]/Developer/matter-levoit-air-purifier/sdkconfig.defaults:25: warning: symbol value 'y' invalid for USE_TEST_SETUP_PIN_CODE
/Users/[USERNAME]/Developer/matter-levoit-air-purifier/sdkconfig.defaults:26: warning: symbol value 'y' invalid for USE_TEST_SETUP_DISCRIMINATOR
/Users/[USERNAME]/Developer/matter-levoit-air-purifier/sdkconfig.defaults:27: warning: symbol value 'y' invalid for SUPPORT_SUPPORT_WATER_HEATER

-- Compiler supported targets: xtensa-esp-elf
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Check size of time_t
-- Check size of time_t - done
-- Generating /Users/[USERNAME]/Developer/matter-levoit-air-purifier/build/x509_crt_bundle.S

CMake Error: Include directory
  '/Users/[USERNAME]/esp/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/ras/include'
  is not a directory.

-- Configuring incomplete, errors occurred!
See also "/Users/[USERNAME]/Developer/matter-levoit-air-purifier/build/CMakeFiles/CMakeOutput.log".
cmake failed with exit code 1, output of the command is in the /Users/[USERNAME]/Developer/matter-levoit-air-purifier/build/log/idf_py_stderr_output_60893
```