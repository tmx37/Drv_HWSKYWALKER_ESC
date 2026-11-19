# Stm32_HwSkyWalkerEsc_Module
Driver module to handle Stm32 <-> Skywalker Esc communication.

In order to initialize the west versioning for the first time:
```shell
$ mkdir .west
$ touch .west/config
$ west config manifest.path .
$ west config manifest.file west.yml 
```

Then to keep the libraries updated:
```shell
$ west update
```

## Module Requirements
- 4x dedicated timers (20ms period, 50Hz)
 
## Usage
1. Configure module to correct Stm32 Tim instance references
2. Confiure all macros 

## Notes
- 

## TODOs
- Develop module
- 

