#include "handler_factory.h"
#include "Handler.h"
#include "handle_letv.h"
#include "handle_pps.h"
#include "handle_16fan.h"

Handler *HandlerFactory::getHandler( const char *name , xml_write_ptr xptr ) {
	Handler *ptr = NULL;
	if ( strcasecmp( name , "letv") == 0 ) {
		ptr = new handle_letv( xptr );
	}else if ( strcasecmp( name , "pps") == 0 ) {
		ptr = new handle_pps( xptr );
	}else if ( strcasecmp(name , "forum") == 0 ) {
		ptr = new handle_16fan( xptr );
	}
	return ptr;
}
void HandlerFactory::releaseHandler( Handler *ptr ) {
	if ( ptr != NULL ) {
		delete ptr;
		ptr = NULL;
	}
}

