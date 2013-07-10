#ifndef _HANDLER_FACTORY_H_
#define _HANDLER_FACTORY_H_
#endif
#include "Handler.h"
#include "xml_write.h" 

class HandlerFactory {
public:
	HandlerFactory();
	virtual ~HandlerFactory();
	static Handler *getHandler( const char *name , xml_write_ptr xptr );
	static void    releaseHandler( Handler *ptr );
	
};
