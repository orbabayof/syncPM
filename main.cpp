#include "constants.h"
#include "color.h"

#include "util/util.h"

#include <iostream>

#include "packageManager/packageManager.h"


int main(int argc, char *argv[])
{
    packageManager pm {};

    pm.installPackage("rust");
    //pm.uninstallPackage("rust");





    return 0;
}
