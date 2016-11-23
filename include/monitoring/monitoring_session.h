#pragma once

#include <session/session.h>
#include <base/rpc.h>
#include <ram_session/ram_session.h>
#include <string>

struct Monitoring_session : Genode::Session
{
	static const char *service_name() { return "monitoring"; }

	virtual void update_info() = 0;

	GENODE_RPC(Rpc_update_info, void, update_info);

	GENODE_RPC_INTERFACE(Rpc_update_info);
};
