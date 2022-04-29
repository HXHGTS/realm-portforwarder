# realm-portforwarder

基于realm的端口转发快速配置工具,支持BBR

#### 使用

`CentOS6/7/8:`
```
yum install gcc wget tar -y && wget https://raw.githubusercontent.com/HXHGTS/realm-portforwarder/main/portforwarder.c -O portforwarder.c && gcc -o portforwarder portforwarder.c && chmod +x portforwarder && ./portforwarder
```

`Debian9/10 OR Ubuntu16/18/20:`
```
apt-get install gcc wget tar -y && wget https://raw.githubusercontent.com/HXHGTS/realm-portforwarder/main/portforwarder.c -O portforwarder.c && gcc -o portforwarder portforwarder.c && chmod +x portforwarder && ./portforwarder
```
