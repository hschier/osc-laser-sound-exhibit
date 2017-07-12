#ifndef Func_h
#define Func_h

LIDARLite LIDAR;

int LIDAR_read_count = 0;

float LIDARread() {
    LIDAR_read_count++;
    if (LIDAR_read_count > 99) {
        LIDAR_read_count = 0;
        return LIDAR.distance();
    } else {
        return LIDAR.distance(0); // no bias correction
    }
}



#endif
