
#include "cronoappender.h"
#include <comlog/xutils.h>
#include <comlog/xdebug.h>
#include <comlog/layout.h>
#include <comlog/event.h>
#include <comlog/namemg.h>

namespace comspace
{

int CronoAppender::syncid(void *p)
{
	time_t now = time(NULL);
	if (now == _last_check_time)
	{
		return 0;
	}
	int ret = 0;
	string new_path;
	pthread_mutex_lock(&_lock);
	_last_check_time = now;
	if (_id >= 0) {
		//检查id跟文件名是否对应
		struct stat fst;
		ret = stat(_path.c_str(), &fst);
		//文件不存在，open之
		if (ret != 0) {
			ret = open(p);
			goto end;
		}
		//文件存在，但是已经跟当前句柄不符合
		if (fst.st_ino != _stat.st_ino) {
			_com_debug("st_info din't equl");
			ret = open(p);
			goto end;
		} else {
			new_path = get_path(time(NULL));
			if (new_path != _path)
			{
				close(p);
				ret = open(new_path, true);
			}
		}
	} else {
		ret = open(p);
	}
end:
	pthread_mutex_unlock(&_lock);
	return ret;
}

int CronoAppender::open(void *p)
{
	_com_debug("before close / open id[%d]", _id);
	close(p);
	_mirror_path = _device.host + string("/") + _device.file;
	_path_format = _device.host + string("/") + _device.reserved1;
	return open(get_path(time(NULL)), false);
}
string CronoAppender::get_path(time_t t)
{
	struct tm local_tm;
	localtime_r(&t, &local_tm);
	string new_path;
	new_path.resize(1024);
	strftime(&new_path[0], new_path.size(), _path_format.c_str(), &local_tm);
	new_path.resize(strlen(new_path.c_str()));
	return new_path;
}
static string get_dir(const string& path)
{
	size_t slash = path.find_last_of('/');
	if (slash == string::npos)
	{
		return ".";
	}
	return path.substr(0, slash);
}
static bool create_dir_r(const string& path)
{
	size_t i = 0;
	i = path.find_first_of('/', i + 1);
	while (i != string::npos)
	{
		mkdir(path.substr(0, i).c_str(), 0755);
		i = path.find_first_of('/', i + 1);
	}
	mkdir(path.c_str(), 0755);
	struct stat dir_stat;
	if (stat(path.c_str(), &dir_stat) != 0)
	{
		return false;
	}
	return S_ISDIR(dir_stat.st_mode);
}

int CronoAppender::open(const string& new_path, bool trunc)
{
	_path = new_path;
	string dir = get_dir(_path);
	if (!create_dir_r(dir))
	{   
		_com_error("Create directory %s fail: %s", dir.c_str(), strerror(errno));
		return -1; 
	}   
	if (trunc)
	{   
		unlink(_path.c_str());
	}   
	int fd = ::open(_path.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0) {
		_com_error("can't open %s: %s", _path.c_str(), strerror(errno));
		return -1; 
	}   

	_id = fd;
	_com_debug("-----------open log %s id[%d]", _path.c_str(), _id);
	return fstat(_id, &_stat);
}

int CronoAppender::close(void *)
{
	if (_id < 0)
	{
		return 0;
	}
	::close(_id);
	_id = -1;
	memset(&_stat, 0, sizeof(_stat));
	return 0;
}

int CronoAppender::print(Event *evt)
{
	//_com_debug("in find id[%d]", _id);
	if (unInMask(evt->_log_level)) {
		//_com_debug("can't suport this level, [%d][%llx]", evt->_log_level, _mask);
		return 0;
	}
	_layout->format(evt);
	if (syncid(NULL) != 0) {
		_com_error("%s", evt->_render_msgbuf);
		close(NULL);
		return -1;
	}
	int ret = write(_id, evt->_render_msgbuf, evt->_render_msgbuf_len);
	if (ret != evt->_render_msgbuf_len) {
		_com_error("ret[%d] != len[%d] %m", ret, evt->_render_msgbuf_len);
		close(NULL);
		return -1;
	}
	return 0;
}

int CronoAppender::binprint(void *buf, int siz)
{
	if (syncid(NULL) != 0) {
		return -1;
	}
	int ret = write(_id, buf, siz);
	if (ret != siz) {
		return -1;
	}
	return 0;
}

CronoAppender::CronoAppender()
{
	memset(&_stat, 0, sizeof(_stat));
	_last_check_time = 0;
}

CronoAppender::~CronoAppender(){
	close(NULL);
}

Appender * CronoAppender::getAppender(com_device_t &dev)
{
	_com_debug("wanna get cronolog appender");

	char name[1024];
	snprintf(name, sizeof(name), "CRONOLOG:%s/%s", dev.host, dev.file);
	Appender *app = NULL;
	NameMg *nameMg = comlog_get_nameMg();
	app = (Appender *)nameMg->get(type_appender, name);
	if (app == NULL) {
 		app = new CronoAppender;
		app->setDeviceInfo(dev);
		if (app->syncid(NULL) != 0) {
			_com_error("syncid log[%s] err %m", name);
			delete app;
			return NULL;
		}
		nameMg->set(name, app);
	}
	_com_debug("get file appender");
	return app;
}

Appender * CronoAppender::tryAppender(com_device_t &dev)
{
	_com_debug("wanna get cronolog appender");

	char name[1024];
	snprintf(name, sizeof(name), "CRONOLOG:%s/%s", dev.host, dev.file);
	Appender *app = NULL;
	NameMg *nameMg = comlog_get_nameMg();
	if ( nameMg != NULL ) {
		app = (Appender *)nameMg->get(type_appender, name);
	}
	return app;
}

}
/* vim: set ts=4 sw=4 sts=4 tw=100 */
