/*
 * GitHub:https://github.com/SouthWind017/
 * Created by SouthWind017 on 2021/3/23 0023.
 * @copyright (c) SoHttp All Rights Reserved
 */
#include <iostream>
#include "SoHttpRequest.h"
using namespace std;
int main(void)
{

    SoHttp server(80);
    server.connect();

    return(0);
}
