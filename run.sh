#!/bin/sh
echo loading.....
g++ main.cpp -Dcimg_use_png -lpng -lz -lX11 -lpthread
echo "   _____ _   _  ____ ______   ______ _____ ___"  
echo "  | ____| \ | |/ ___|  _ \ \ / /  _ \_   _/ _ \ "
echo "  |  _| |  \| | |   | |_) \ V /| |_) || || | | |"
echo "  | |___| |\  | |___|  _ < | | |  __/ | || |_| |"
echo "  |_____|_| \_|\____|_| \_\|_| |_|    |_| \___/ "
./a.out