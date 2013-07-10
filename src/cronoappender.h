
#ifndef  __FILEAPPENDER_H_
#define  __FILEAPPENDER_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
using namespace std;

#include <comlog/appender/appender.h>
#include "namemg.h"

namespace comspace 
{
extern NameMg * g_nameMg;

class CronoAppender : public Appender
{
	struct stat _stat;
	string		_path_format;
	string		_path;
	string		_mirror_path;
	time_t		_last_check_time;

public:
	int open(void *);
	int close(void *);
	int print(Event *evt);
	int binprint(void *, int siz);
	~CronoAppender();
protected:
	int syncid(void *);

	CronoAppender();
	string get_path(time_t t);
	int open(const string& new_path, bool trunc);

public:
	static Appender *getAppender(com_device_t &dev);
	static Appender *tryAppender(com_device_t &dev);
protected:
	friend class Appender;
	//friend class UlCronoAppender;
	friend class UlLogAppender;
	friend class NetAppender;
};

};












#endif  //__FILEAPPENDER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
