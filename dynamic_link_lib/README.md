steps for build a dynamic link library:

1. `gcc -c -fpic a.c b.c xxx.c ...`

2. `gcc -shared a.o b.o ... -o libxxx.so`

3. complie the main code (don't forget to add -I and -L)

4. add lib path to env:

- user: add `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:absolute_lib_path` to `~/.bashrc` and `source ~/.bashrc`

- root: add `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:absolute_lib_path` to `/etc/profile` and `source /etc/profile`
  
