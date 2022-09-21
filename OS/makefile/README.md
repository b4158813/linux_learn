steps for build a static link library:

1. `gcc -c a.c b.c xxx.c ...`

2. `ar rcs libxxx.a a.o b.o ... -I ./include_dir -L ./lib_dir -lxxx`

3. complie the main code (don't forget to add -I and -L)
