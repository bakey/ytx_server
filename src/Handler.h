#ifndef _HANDLER_H_
#define _HANDLER_H_

class Configuration;
class ParseCenter;
class Handler {
public:
	Handler(){}
	virtual ~Handler(){}
	virtual bool handle_html(char *url, char *html) = 0 ;
	virtual void setParseCenter( ParseCenter *center ) = 0;
};
#endif
