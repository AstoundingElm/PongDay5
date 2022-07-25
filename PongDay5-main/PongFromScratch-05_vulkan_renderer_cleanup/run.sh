cd src
cd platform
g++ linux_platform.cpp -D LINUX_BUILD -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lX11 -lXi -lXrandr -lxcb -g
./a.out
