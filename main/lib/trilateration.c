#include "triangulation.h"

 void update_distance(uint8_t *uuid, float d){
        for(int i = 0; i<3; i++){
            if(memcmp(uuid,fixed_nodes[i].uuid,16) == 0) {
                fixed_nodes[i].distance = d;
                //ESP_LOG_BUFFER_HEX("TRILA",fixed_nodes[i].uuid,16);
                //ESP_LOG_BUFFER_HEX("TRILA",uuid,16);
                ESP_LOGI("TRILA","Dispositivo: %d Distance: %f",i,d);
            }
        }
}

// TODO modificare calcolo stima x e y del beacon

void estimate_position(){
    float a[3], b[3], c[3];
    float x;
    float y;
    a[0] = 2 * (fixed_nodes[1].x - fixed_nodes[0].x)
    a[1] = 2 * (fixed_nodes[2].x - fixed_nodes[0].x)
    a[2] = 2 * (fixed_nodes[2].x - fixed_nodes[1].x)

    b[0] = 2 * (fixed_nodes[1].y - fixed_nodes[0].y)
    b[1] = 2 * (fixed_nodes[2].y - fixed_nodes[0].y)
    b[2] = 2 * (fixed_nodes[2].y - fixed_nodes[1].y)

    // C1 = d1^2 - d2^2 + x2^2 -x1^2 + y2^2 - y1^2
    c[0] = (fixed_nodes[0].distance * fixed_nodes[0].distance) - (fixed_nodes[1].distance * fixed_nodes[1].distance) + (fixed_nodes[1].x * fixed_nodes[1].x) - (fixed_nodes[0].x * fixed_nodes[0].x) + (fixed_nodes[1].y * fixed_nodes[1].y) - (fixed_nodes[0].y * fixed_nodes[0].y)
    // C2 = d1^2 - d3^2 + x3^2 -x1^2 + y3^2 - y1^2
    c[1] = (fixed_nodes[0].distance * fixed_nodes[0].distance) - (fixed_nodes[2].distance * fixed_nodes[2].distance) + (fixed_nodes[2].x * fixed_nodes[2].x) - (fixed_nodes[0].x * fixed_nodes[0].x) + (fixed_nodes[2].y * fixed_nodes[2].y) - (fixed_nodes[0].y * fixed_nodes[0].y)
    // C3 = d2^2 - d3^2 + x3^2 -x2^2 + y3^2 - y2^2
    c[2] = (fixed_nodes[1].distance * fixed_nodes[1].distance) - (fixed_nodes[3].distance * fixed_nodes[3].distance) + (fixed_nodes[2].x * fixed_nodes[2].x) - (fixed_nodes[1].x * fixed_nodes[1].x) + (fixed_nodes[2].y * fixed_nodes[2].y) - (fixed_nodes[1].y * fixed_nodes[1].y)



    /*for (int i = 0; i < 3; i++) {
        a[i] = -2 * fixed_nodes[i].x;
        b[i] = -2 * fixed_nodes[i].y;
        c[i] = fixed_nodes[i].x * fixed_nodes[i].x + fixed_nodes[i].y * fixed_nodes[i].y -
               fixed_nodes[i].distance * fixed_nodes[i].distance;
    }
    x = ((c[1] - c[0]) * (b[1] - b[2]) - (c[2] - c[1]) * (b[0] - b[1])) /
        ((a[0] - a[1]) * (b[1] - b[2]) - (a[1] - a[2]) * (b[0] - b[1]));
    y = ((c[2] - c[1]) * (a[0] - a[1]) - (c[1] - c[0]) * (a[1] - a[2])) /
        ((a[0] - a[1]) * (b[1] - b[2]) - (a[1] - a[2]) * (b[0] - b[1]));
    */

    ESP_LOGI("TRILAT", "Estimated Beacon position: X: %f, Y: %f", x, y);
    mqtt_publish(x, y, fixed_nodes[0].distance, fixed_nodes[1].distance, fixed_nodes[2].distance);
}