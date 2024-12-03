## Membri del gruppo
- [Modonesi Alessio](https://github.com/alessiomodonesi)
- [Silvestrin Tommaso](https://github.com/tommasosilvestrin)

Cosa ha sviluppato **Modonesi Alessio**:
- **header** della classe LidarDriver
- metodo **get_scan()**
- metodo **clear_buffer()**
- funzione aggiuntiva **count_numbers()**
-  overload **operator<<**
- relativi **test**

Cosa ha sviluppato **Silvestrin Tommaso**:
- metodo **new_scan()**
- metodo **get_distance()**
- funzione aggiuntiva **update_position()**
- funzione aggiuntiva **round_angle()**
- relativi **test**

## Come compilare con Cmake
> ~/LiDAR-Project/$ cd build
>
> ~/LiDAR-Project/build/$ make
> 
> ~/LiDAR-Project/build/$ ./main

## Come compilare con g++
> ~/LiDAR-Project/$ cd include
> 
> ~/LiDAR-Project/include/$ mv LidarDriver.h ../src/LidarDriver.h
> 
> ~/LiDAR-Project/include/$ g++ LidarDriver.cpp main.cpp -o main
> 
> ~/LiDAR-Project/include/$ ./main

## Links utili
- [LidarDriver.h](./include/LidarDriver.h)
- [LidarDriver.cpp](./src/LidarDriver.cpp)
- [main.cpp](./src/main.cpp)
