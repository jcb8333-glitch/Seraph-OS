#include "boot.h"
#include "boot_io.h"

struct port_io_ops p_io_ops;

void main(void){
    /* Init std io */
    init_default_io_ops();

    /* Get boot header */

    /* Init console */

    /* Init heap */

    /* Check CPU and set mode */

    /* Detect memory */

    /* Exit boot services / perform last steps*/
}