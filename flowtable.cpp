#include <iostream>
#include <string.h>
using namespace std;
string entry(string controller_ip, string switch_name, string in_port, string protocal, string tp_src, string tp_dst, string out_port)
{
	/*
	协议:
	ip_proto
	icmp:0x01 
	udp:0x06
	tcp:0x11
	SCTP:0x84
	
	端口(UDP/TCP/SCTP):
	tp_src
	tp_dst
	
	指令:
	sudo curl -d ‘{“switch”: “[sw_dpid]″, “name”:”flow-mod-1″, “cookie”:”0″, “priority”:”32768″, “ingress-port”:”2″,”active”:”true”, “actions”:”output=3″}’ http://<controller_ip>:8080/wm/staticflowentrypusher/json
	*/
	// 初始化curl指令
	string curlcmd = "curl -d \'{\"switch\":\"";
	// 添加switch名称
	curlcmd += switch_name;
	curlcmd += "\"";
	// 添加流表条目名称
	curlcmd += ",\"name\":\"flow-mod-1\"";
	// 添加cookie值
	curlcmd += ",\"cookie\":\"0\"";
	// 添加优先级
	curlcmd += ",\"priority\":\"32768\"";
	// 添加交换机入端口
	curlcmd += ",\"in_port\":\"";
	curlcmd += in_port;
	curlcmd += "\"";
	// 添加协议
	if(protocal == "icmp")
		curlcmd += ",\"ip_proto\":\"0x01\"";
	else if(protocal == "udp")
		curlcmd += ",\"ip_proto\":\"0x06\"";
	else if(protocal == "tcp")
		curlcmd += ",\"ip_proto\":\"0x11\"";
	else if(protocal == "sctp")
		curlcmd += ",\"ip_proto\":\"0x84\"";
	// 添加应用层端口组
	curlcmd += ",\"tp_src\":\"";
	curlcmd += tp_src;
	curlcmd += "\",\"tp_dst\":\"";
	curlcmd += tp_dst;
	curlcmd += "\"";
	// 添加active选项
	curlcmd += ",\"active\":\"true\"";
	// 添加动作 转发到出端口
	curlcmd += ",\"actions\":\"output=";
	curlcmd += out_port;
	curlcmd += "\"";
	// 添加最后的花括号
	curlcmd += "}\'";
	// 构造最后的控制器地址
	string table_add = " http://";
	table_add += controller_ip;
	string tmp = ":8080/wm/staticflowentrypusher/json";
	table_add += tmp;
	// 将最后的地址加到指令最后
	curlcmd += table_add;
	return curlcmd;
}
int main()
{
	string curlcmd = entry("192.168.1.1", "00:00:00:00:00:00:00:01", "1", "tcp", "12345", "54321", "2");
	cout << curlcmd << endl;
	return 0;
}