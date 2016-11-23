#pragma once

#include <base/printf.h>
#include <base/rpc_client.h>
#include <monitoring/monitoring_session.h>

struct Monitoring_session_client : Genode::Rpc_client<Monitoring_session>
{
	Monitoring_session_client(Genode::Capability<Monitoring_session> cap):
		Genode::Rpc_client<Monitoring_session>(cap) {}

	void update_info()
	{
		call<Rpc_update_info>();
	}

};
