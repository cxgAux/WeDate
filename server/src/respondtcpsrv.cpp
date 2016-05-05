#include "unp.h"
#include "Log.h"
#include <time.h>
#include <vector>
#include <memory>


#define MAXLINE 1024

int main(int argc, char ** argv) {
	
	const static int ListenQueue = 5, Maxrecv = 1024, ratio = 3;
	Log::Initialise("test.log");	

	int listenfd = -1, connfd = -1;
	struct sockaddr_in servaddr;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		Log::Fatal("create stream socket error");
		Log::Finalise();
		abort();	
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(10024);

	if(bind(listenfd, (SA *) & servaddr, sizeof(servaddr)) < 0) {
		Log::Fatal("bind stream socket with the port error");
		Log::Finalise();
		abort();
	}

	if(listen(listenfd, ListenQueue) < 0) {
		Log::Fatal("start listen error");
		Log::Finalise();
		abort();
	}
	
	Log::Info("listen begins!");
	
	while(true) {
		if((connfd = accept(listenfd, (SA *)NULL, NULL)) < 0) {
			Log::Fatal("accept error");
			Log::Finalise();
			abort();
		}
		else {
			Log::Info("new comer with connfd : %d", connfd);
			char * buff = new char [Maxrecv];
			std::vector<char> vBuff(ratio * Maxrecv);
			int n = -1;
			while((n = read(connfd, buff, Maxrecv)) > 0) {
				for(int i = 0; i < n; ++ i) {
					vBuff.push_back(buff[i]);
				}
			}
			if(n < 0) {
				Log::Fatal("read error with connfd : %d", connfd);
				Log::Finalise();
				abort();
			}
			delete [] buff;
			buff =  new char [vBuff.size() + 1];
			for(int i = 0; i < vBuff.size(); ++ i) {
				buff[i] = vBuff[i];
			}
			buff[vBuff.size()] = 0;
			if(write(connfd, buff, strlen(buff)) < 0) {
				Log::Fatal("write error with connfd : %d", connfd);
				Log::Finalise();
				abort();
			}
			close(connfd);
			delete [] buff;
		}
	}


	Log::Finalise();
}
