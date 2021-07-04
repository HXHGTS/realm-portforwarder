#include <stdio.h>
#include <stdlib.h>

int run_mode;
FILE* config,*service;

int main() {
	int UserInterface();
	if (run_mode == 1) {
		printf("正在新建并打开realm规则. . .\n");
		config = fopen("/usr/bin/realm.json","w");
		fprintf(config,"{\n    \"listening_addresses\": [\"0.0.0.0\"],\n    \"listening_ports\": [\"10000-10001\"],\n    \"remote_addresses\": [\"8.8.8.8\", \"8.8.4.4\"],\n    \"remote_ports\": [\"443\", \"853\"]\n}\n\n");
		fclose(config);
		service = fopen("/etc/systemd/system/realm.service", "w");
		fprintf(service, "[Unit]\nDescription=realm\nAfter=network-online.target\nWants=network-online.target systemd-networkd-wait-online.service\n\n[Service]\nType=simple\nUser=root\nRestart=on-failure\nRestartSec=5s\nDynamicUser=true\nExecStart=/usr/bin/realm -c /usr/bin/realm.json\n\n[Install]\nWantedBy=multi-user.target\n\n");
		fclose(service);
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
}

int UserInterface(){
	printf("1.安装realm\n\n2.编辑规则\n\n0.退出\n\n请输入:");
	scanf("%d", &run_mode);
	return 0;
}
