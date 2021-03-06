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
		printf("正在尝试开启BBR. . .\n");
		system("echo net.core.default_qdisc = fq > /etc/sysctl.conf");
		system("echo net.ipv4.tcp_congestion_control = bbr >> /etc/sysctl.conf");
		system("sysctl -p");
		printf("正在新建并打开realm规则. . .\n");
		system("mkdir -p /etc/realm");
		system("curl -sSL https://raw.githubusercontent.com/HXHGTS/realm-portforwarder/main/realm.toml > /etc/realm/realm.toml");
		system("curl -sSL https://raw.githubusercontent.com/HXHGTS/realm-portforwarder/main/realm.service > /etc/systemd/system/realm.service");
		system("vi /etc/realm/realm.toml");
		printf("正在下载realm. . .\n");
		system("wget https://github.com/zhboner/realm/releases/latest/download/realm-x86_64-unknown-linux-gnu.tar.gz -O /root/realm-x86_64-unknown-linux-gnu.tar.gz");
		system("tar -zxvf realm-x86_64-unknown-linux-gnu.tar.gz");
		system("rm -f realm-x86_64-unknown-linux-gnu.tar.gz");
		system("mv -f /root/realm /usr/bin/realm");
		system("chmod +x /usr/bin/realm");
		printf("正在打开启动realm转发. . .\n");
		system("systemctl enable --now realm");
		system("systemctl start realm");
		printf("已开启realm转发!\n");
	}
	else if (run_mode == 2) {
		printf("正在关闭realm转发. . .\n");
		system("systemctl stop realm");
		printf("正在打开realm规则. . .\n");
		system("vi /usr/bin/realm.json");
		printf("正在打开启动realm转发. . .\n");
		system("systemctl start realm");
		printf("已开启realm转发!\n");
	}
	else if (run_mode == 3) {
		printf("正在重启realm转发. . .\n");
		system("systemctl stop realm");
		system("systemctl start realm");
		printf("已重启realm转发!\n");
	}
	else if (run_mode == 4) {
		printf("正在关闭realm转发. . .\n");
		system("systemctl stop realm");
		system("systemctl disable realm");
		printf("已关闭realm转发!\n");
	}
	else if (run_mode == 5) {
		system("systemctl status realm -l");
	}
	else if (run_mode == 6) {
		printf("正在关闭realm转发. . .\n");
		system("systemctl stop realm");
		system("systemctl disable realm");
		printf("正在卸载realm转发. . .\n");
		system("rm -f /usr/bin/realm.json");
		system("rm -f /etc/systemd/system/realm.service");
		system("rm -f /usr/bin/realm");
		printf("已卸载realm转发!\n");
	}
	else {
		exit(0);
	}
	goto Menu;
	return 0;
}

int UserInterface(){
	printf("-----------------------------------------------\n");
	printf("---------------realm端口转发控制台-------------\n");
	printf("-----------------------------------------------\n");
	printf("1.安装realm\n\n2.编辑规则\n\n3.重启realm\n\n4.关闭realm\n\n5.realm运行状态\n\n6.卸载realm\n\n0.退出\n\n请输入:");
	scanf("%d", &run_mode);
	return 0;
}

