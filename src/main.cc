#include "MyConf.h"
#include "inetAddr.h"
#include "TcpServer.h"
#include "TcpConnect.h"
#include "MyTimer.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <map>
#include <functional>

void Connectfunc(const TcpConnectPtr & con);
void Messagefunc(const TcpConnectPtr & con);

void test()
{
    std::cout << "hello" << std::endl;
}

int main()
{
/*
    char *cs = getcwd(NULL,0);
    if(!cs)
    {
        std::cout << "faulted pathname" << std::endl;
        return -1;
    }
    std::string css(cs);
//    std::cout << css << std::endl;
 
    css += "/conf/my.conf";
    MyConf myconf(css);
    bool flag = myconf.init();
    if(!flag)
        return -1;
    myconf.show();
    std::map<std::string,std::string> &map_conf = myconf.getMap();
    std::string ip = map_conf["my_ip"];
    std::istringstream iss(map_conf["my_port"]);
    int port;
    iss >> port;
    inetAddr inet(ip,port);
 
    TcpServer server(inet);
    server.setConnectCB(&Connectfunc);
    server.setMessageCB(&Messagefunc);
    server.start();
    
    
    while(1)
    {
      sock.bindAddress(inet);
      sock.listen();
      int fd = sock.accept();
      std::cout << fd << std::endl;
    }
*/
    MyTimer timer(1,3,std::bind(&test));
    timer.start();
    while(1);
    return 0;

}
/*
void Connectfunc(const TcpConnectPtr & con)
{
    std::cout << "welcome connect" << std::endl;
}

void Messagefunc(const TcpConnectPtr & con)
{
    std::string msg(con->receive());
    Task task(msg,con->fd(),Mydic_);
    thpool_ -> addTask(task);
}

*/
