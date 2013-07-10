#include <log_class.h>

log_c::log_c()
{
	m_log = NULL;
}

log_c::~log_c()
{
	m_log = NULL;
}

bool log_c::log_init(char *config)
{
	try {
		log4cpp::PropertyConfigurator::configure(config);
		m_log =  &log4cpp::Category::getRoot();
	} catch (log4cpp::ConfigureFailure& f) {
		cout << "Configure Problem" << f.what() << endl;
		return false;
	}
	
	m_log->infoStream() << "Log4cpp init OK";
	return true;
}

log_stream log_c::debug_stream()
{
	return m_log->debugStream();
}

log_stream log_c::info_stream()
{
	return m_log->infoStream();
}

log_stream log_c::notice_stream()
{
	return m_log->noticeStream();
}

log_stream log_c::warn_stream()
{
	return m_log->warnStream();
}
log_stream log_c::error_stream()
{
	return m_log->errorStream();
}

log_stream log_c::crit_stream()
{
	return m_log->critStream();
}

log_stream log_c::alert_stream()
{
	return m_log->alertStream();
}

log_stream log_c::fatal_stream()
{
	return m_log->fatalStream();
}

