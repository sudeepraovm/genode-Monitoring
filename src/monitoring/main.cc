#include <base/env.h>
#include <base/printf.h>
#include <base/rpc_server.h>
#include <base/sleep.h>
#include <os/server.h>

#include "monitoring_session_component.h"

struct Main
{
	Monitoring_root_component monitoring_root;

	Main(Server::Entrypoint& ep) :
		monitoring_root(&ep, Genode::env()->heap())
	{
		PDBG("monitoring: Hello!\n");
		Genode::env()->parent()->announce(ep.rpc_ep().manage(&monitoring_root));
	}
};

/************
 ** Server **
 ************/

namespace Server
{
	char const *name()             { return "monitoring";      }
	size_t stack_size()            { return 64*1024*sizeof(long); }
	void construct(Entrypoint& ep) { static Main server(ep);     }
}
