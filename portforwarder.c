#include <stdio.h>
#include <stdlib.h>

int run_mode;
FILE* config,*service;
int UserInterface();

int main() {
	UserInterface();
	if (run_mode == 1) {
		printf("正在新建并打开realm规则. . .\n");
		system("curl https://raw.githubusercontent.com/HXHGTS/realm-portforwarder/main/realm.json > /usr/bin/realm.json");
		system("curl https://raw.githubusercontent.com/HXHGTS/realm-portforwarder/main/realm.service > /etc/systemd/system/realm.service");
		system("vi /usr/bin/realm.json");
		printf("正在下载realm. . .\n");
		system("cd /usr/bin && wget https://github.com/zhboner/realm/releases/latest/download/realm -O realm && chmod +x realm");
		printf("正在打开启动realm转发. . .\n");
		system("systemctl enable --now realm");
		system("systemctl start realm");
	}
	else if (run_mode == 2) {
		printf("正在关闭realm转发. . .\n");
		system("systemctl stop realm");
		printf("正在打开realm规则. . .\n");
		system("vi /usr/bin/realm.json");
		printf("正在打开启动realm转发. . .\n");
		system("systemctl start realm");
	}
	else {
		exit(0);
	}
	return 0;
}

int UserInterface(){
	printf("1.安装realm\n\n2.编辑规则\n\n0.退出\n\n请输入:");
	scanf("%d", &run_mode);
	return 0;
}

