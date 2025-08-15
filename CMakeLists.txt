cmake_minimum_required(VERSION 3.31)
project(magdata_nopi)

set(CMAKE_C_STANDARD 11)

option(<option_variable> "Build  for use with the Pololu I2C interface " [TRUE])

add_executable(magdata_nopi cmdmgr.c
        magdata.c
        main.c
        i2c-pololu.h
        i2c-pololu.c
        i2c-pigpio.h
        i2c-pigpio.c
        i2c.c
        i2c.h
        i2c-lgpio.h)
