#include <stdio.h>
#include <stdlib.h>

int run_mode;
FILE* config,*service;
int UserInterface();

int main() {
	Menu:UserInterface();
	if (run_mode == 1) {
		printf("正在关闭并卸载防火墙. . .\n");
		system("systemctl disable iptables");
		system("systemctl stop iptables");
		system("systemctl disable firewalld");
		system("systemctl stop firewalld");
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
	else if (run_mode == 3) {
		printf("正在重启realm转发. . .\n");
		system("systemctl stop realm");
		system("systemctl start realm");
	}
	else if (run_mode == 4) {
		printf("正在关闭realm转发. . .\n");
		system("systemctl stop realm");
		system("systemctl disable realm");
	}
	else {
		exit(0);
	}
	goto Menu;
	return 0;
}

int UserInterface(){
	system("clear");
	printf("-----------------------------------------------\n");
	printf("---------------realm端口转发控制台-------------\n");
	printf("-----------------------------------------------\n");
	printf("1.安装realm\n\n2.编辑规则\n\n3.重启realm\n\n4.关闭realm\n\n0.退出\n\n请输入:");
	scanf("%d", &run_mode);
	return 0;
}

